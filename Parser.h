#ifndef __PARSER_H
#define __PARSER_H

#include "Node.h"
#include <string>
#include <stack>

enum class Precedence { LOW = 0, MID = 1, HIGH = 2 };

const char	ALTERNATIVE_OPERATOR = '+',
			CONCATENATION_OPERATOR = '.',
			ITERATION_OPERATOR = '*',
			LEFT_PARENTHESES = '(',
			RIGHT_PARENTHESES = ')';

const std::string EPSILON = "\\epsilon",
				  EMPTY_SET = "\\emptyset";
			


class Parser {
public:
	static Node* parse(const std::string& input);
private:
	static bool is_matching_string(const std::string& match,
		std::string::const_iterator& it, std::string::const_iterator& it_end);
	static bool is_operator(char c);
	static bool is_unary_operator(char c);
	static bool is_binary_operator(char c);
	static Node* create_binary_operand_node(std::stack<Node*>& operand_stack,
		std::stack<char>& operator_stack);
	static Node* create_unary_operand_node(std::stack<Node*>& operand_stack, char o);
	static Precedence operator_precedence(char o);
	static bool operator_left_associative(char o);
	static bool more_binary_operands(char n, 
		std::stack<Node*>& operand_stack, std::stack<char>& operator_stack);
	static bool parse_it(bool& possible_implicit_concatenation, int& index,
		std::string::const_iterator& it, std::string::const_iterator& it_end,
		std::stack<Node*>& operand_stack, std::stack<char>& operator_stack);
};



#endif // !__PARSER_H
