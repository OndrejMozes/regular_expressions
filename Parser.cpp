#include "Parser.h"
#include "Node.h"


bool Parser::is_matching_string(const std::string& match,
		std::string::const_iterator& it, std::string::const_iterator& it_end) {
	auto matching_iterator = it;
	for (char c : match) {
		if (matching_iterator == it_end || *matching_iterator != c) return false;
		++matching_iterator;
	}
	// only update the iterator if we actually found a match
	// and also decrement by one since it will get incremented by one in the for loop
	it = --matching_iterator;
	return true;
}

bool Parser::is_unary_operator(char c) {
	return c == ITERATION_OPERATOR;
}
bool Parser::is_binary_operator(char c) {
	return c == ALTERNATIVE_OPERATOR || c == CONCATENATION_OPERATOR;
}

bool Parser::is_operator(char c) {
	// Currently in our program this function is pointless, 
	// but it could be useful if we expanded the program in the future
	return is_unary_operator(c) || is_binary_operator(c);
}

Node* Parser::create_binary_operand_node(std::stack<Node*>& operand_stack,
		std::stack<char>& operator_stack) {
	char o = operator_stack.top();
	operator_stack.pop();
	Node* r = operand_stack.top();
	operand_stack.pop();
	Node* l = operand_stack.top();
	operand_stack.pop();
	switch (o)
	{
	case ALTERNATIVE_OPERATOR:
		return new AlternativeNode(l, r);
		break;
	case CONCATENATION_OPERATOR:
		return new ConcatenationNode(l, r);
		break;
	default:
		return nullptr;
		break;
	}
}

Node* Parser::create_unary_operand_node(std::stack<Node*>& operand_stack, char o) {
	Node* p = operand_stack.top();
	operand_stack.pop();
	switch (o)
	{
	case ITERATION_OPERATOR:
		return new IterationNode(p);
		break;
	default:
		return nullptr;
		break;
	}
}

Precedence Parser::operator_precedence(char o) {
	switch (o)
	{
	case ALTERNATIVE_OPERATOR:
		return Precedence::LOW;
		break;
	case CONCATENATION_OPERATOR:
		return Precedence::MID;
		break;
	case ITERATION_OPERATOR:
		return Precedence::HIGH;
		break;
	default:
		throw "Not an operator: " + o;
		break;
	}	
}

bool Parser::operator_left_associative(char o) {
	// Currently in our program this check is pointless, 
	// but it could be useful if we expanded the program in the future
	switch (o)
	{
	case ALTERNATIVE_OPERATOR:
		return true;
		break;
	case CONCATENATION_OPERATOR:
		return true;
		break;
	case ITERATION_OPERATOR:
		return false;
		break;
	default:
		throw "Not an operator: " + o;
		break;
	}
}

bool Parser::more_binary_operands(char n,
	std::stack<Node*>& operand_stack, std::stack<char>& operator_stack) {
	return !operator_stack.empty() &&
		is_binary_operator(operator_stack.top()) &&
		(operator_precedence(operator_stack.top()) > operator_precedence(n) ||
			(operator_precedence(operator_stack.top()) >= operator_precedence(n) &&
				operator_left_associative(n)));
}

bool Parser::parse_it(bool& possible_implicit_concatenation, int& index,
	std::string::const_iterator& it, std::string::const_iterator& it_end,
	std::stack<Node*>& operand_stack, std::stack<char>& operator_stack) {
	char t = *it;
	if (possible_implicit_concatenation && (isalpha(t) || t == LEFT_PARENTHESES)) {
		--it;
		t = CONCATENATION_OPERATOR;
	}
	possible_implicit_concatenation = false;

	if (isalpha(t)) {
		possible_implicit_concatenation = true;
		index++;
		operand_stack.push(new SymbolNode(Symbol(t, index)));
	}
	else if (is_matching_string(EPSILON, it, it_end)) {
		operand_stack.push(new EmptyStringNode());
	}
	else if (is_matching_string(EMPTY_SET, it, it_end)) {
		operand_stack.push(new EmptyLanguageNode());
	}
	else if (t == LEFT_PARENTHESES) {
		operator_stack.push(LEFT_PARENTHESES);
	}
	else if (t == RIGHT_PARENTHESES) {
		possible_implicit_concatenation = true;
		while (!operator_stack.empty() && is_binary_operator(operator_stack.top())) {
			operand_stack.push(create_binary_operand_node(operand_stack, operator_stack));
		}
		if (operator_stack.top() != LEFT_PARENTHESES) return false;
		operator_stack.pop(); // remove (
	}
	else if (is_unary_operator(t)) {
		possible_implicit_concatenation = true;
		operand_stack.push(create_unary_operand_node(operand_stack, t));
	}
	else if (is_binary_operator(t)) {
		while (more_binary_operands(t, operand_stack, operator_stack)) {
			operand_stack.push(create_binary_operand_node(operand_stack, operator_stack));
		}
		operator_stack.push(t);
	}
	else {
		return false;
	}
	return true;
}

// returns nullptr on failure
Node* Parser::parse(const std::string& input) {
	std::stack<Node*> operand_stack;
	std::stack<char> operator_stack;
	std::string::const_iterator it_end = input.end();
	bool possible_implicit_concatenation = false;
	int index = 0;
	for (std::string::const_iterator it = input.cbegin(); it != it_end; ++it) {
		if (!parse_it(possible_implicit_concatenation, index, it, it_end, operand_stack, operator_stack))
			return nullptr;
	}
	while (!operator_stack.empty()) {
		operand_stack.push(Parser::create_binary_operand_node(operand_stack, operator_stack));
	}
	if (operand_stack.size() != 1) return nullptr;
	return operand_stack.top();
}
