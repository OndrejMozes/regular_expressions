#include "Node.h"
#include "SetHelper.h"


Node::~Node() {}

Node::Node(std::set<Symbol> starting, std::set<SymbolPair> neighbors,
	std::set<Symbol> ending, bool epsilon) :
	starting_(starting), neighbors_(neighbors),
	ending_(ending), epsilon_(epsilon) {}

void Node::print(std::ostream& os) const {
	os << "- Starting: " << starting_ << std::endl;
	os << "- Neighbors: " << neighbors_ << std::endl;
	os << "- Ending: " << ending_ << std::endl;
	os << "- Epsilon: " << std::boolalpha << epsilon_ << std::endl;
	os << std::endl;
}



SymbolNode::SymbolNode(Symbol symbol) : Node(make_starting_(symbol), make_neighbors_(),
	make_ending_(symbol), make_epsilon_()), symbol_(symbol) {}

std::set<Symbol> SymbolNode::make_starting_(Symbol symbol) {
	auto starting = std::set<Symbol>();
	starting.insert(symbol);
	return starting;
}
std::set<SymbolPair> SymbolNode::make_neighbors_() {
	return std::set<SymbolPair>();
}
std::set<Symbol> SymbolNode::make_ending_(Symbol symbol) {
	auto ending = std::set<Symbol>();
	ending.insert(symbol);
	return ending;
}
bool SymbolNode::make_epsilon_() {
	return false;
}



EmptyStringNode::EmptyStringNode() : Node(make_starting_(), make_neighbors_(),
	make_ending_(), make_epsilon_()) {}

std::set<Symbol> EmptyStringNode::make_starting_() {
	return std::set<Symbol>();
}
std::set<SymbolPair> EmptyStringNode::make_neighbors_() {
	return std::set<SymbolPair>();
}
std::set<Symbol> EmptyStringNode::make_ending_() {
	return std::set<Symbol>();
}
bool EmptyStringNode::make_epsilon_() {
	return true;
}



EmptyLanguageNode::EmptyLanguageNode() : Node(make_starting_(), make_neighbors_(),
	make_ending_(), make_epsilon_()) {}

std::set<Symbol> EmptyLanguageNode::make_starting_() {
	return std::set<Symbol>();
}
std::set<SymbolPair> EmptyLanguageNode::make_neighbors_() {
	return std::set<SymbolPair>();
}
std::set<Symbol> EmptyLanguageNode::make_ending_() {
	return std::set<Symbol>();
}
bool EmptyLanguageNode::make_epsilon_() {
	return false;
}



IterationNode::IterationNode(Node* child) : Node(make_starting_(child), make_neighbors_(child),
	make_ending_(child), make_epsilon_()), child_(child) {}

IterationNode::~IterationNode() {
	if (child_ != nullptr) {
		delete child_;
		child_ = nullptr;
	}
}

std::set<Symbol> IterationNode::make_starting_(Node* child) {
	return std::set<Symbol>(child->starting());
}
std::set<SymbolPair> IterationNode::make_neighbors_(Node* child) {
	auto neighbors = std::set<SymbolPair>(child->neighbors());
	for (auto x : child->ending()) {
		for (auto y : child->starting()) {
			neighbors.emplace(x, y);
		}
	}
	return neighbors;
}
std::set<Symbol> IterationNode::make_ending_(Node* child) {
	return child->ending();
}
bool IterationNode::make_epsilon_() {
	return true;
}



BinaryOperationNode::BinaryOperationNode(std::set<Symbol> starting, std::set<SymbolPair> neighbors,
	std::set<Symbol> ending, bool epsilon, Node* left_child, Node* right_child) :
	Node(starting, neighbors, ending, epsilon),
	left_child_(left_child), right_child_(right_child) {}

BinaryOperationNode::~BinaryOperationNode() {
	if (left_child_ != nullptr) {
		delete left_child_;
		left_child_ = nullptr;
	}
	if (right_child_!= nullptr) {
		delete right_child_;
		right_child_ = nullptr;
	}
}



ConcatenationNode::ConcatenationNode(Node* left_child, Node* right_child) :
	BinaryOperationNode(make_starting_(left_child, right_child),
		make_neighbors_(left_child, right_child),
		make_ending_(left_child, right_child),
		make_epsilon_(left_child, right_child),
		left_child, right_child) {}

std::set<Symbol> ConcatenationNode::make_starting_(Node* left_child, Node* right_child) {
	if (left_child->epsilon() == false) {
		return std::set<Symbol>(left_child->starting());
	}
	else {
		auto starting = SetHelper::make_union_of_Symbol_sets(
			left_child->starting(), right_child->starting());
		return starting;
	}
}
std::set<SymbolPair> ConcatenationNode::make_neighbors_(Node* left_child, Node* right_child) {
	auto neighbors = SetHelper::make_union_of_SymbolPair_sets(
		left_child->neighbors(), right_child->neighbors());
	for (auto x : left_child->ending()) {
		for (auto y : right_child->starting()) {
			neighbors.emplace(x, y);
		}
	}
	return neighbors;
}
std::set<Symbol> ConcatenationNode::make_ending_(Node* left_child, Node* right_child) {
	if (right_child->epsilon() == false) {
		return std::set<Symbol>(right_child->ending());
	}
	else {
		auto ending = SetHelper::make_union_of_Symbol_sets(
			left_child->ending(), right_child->ending());
		return ending;
	}
}
bool ConcatenationNode::make_epsilon_(Node* left_child, Node* right_child) {
	return left_child->epsilon() && right_child->epsilon();
}



AlternativeNode::AlternativeNode(Node* left_child, Node* right_child) :
	BinaryOperationNode(make_starting_(left_child, right_child),
		make_neighbors_(left_child, right_child),
		make_ending_(left_child, right_child),
		make_epsilon_(left_child, right_child),
		left_child, right_child) {}

std::set<Symbol> AlternativeNode::make_starting_(Node* left_child, Node* right_child) {
	auto starting = SetHelper::make_union_of_Symbol_sets(
		left_child->starting(), right_child->starting());
	return starting;
}
std::set<SymbolPair> AlternativeNode::make_neighbors_(Node* left_child, Node* right_child) {
	auto neighbors = SetHelper::make_union_of_SymbolPair_sets(
		left_child->neighbors(), right_child->neighbors());
	return neighbors;
}
std::set<Symbol> AlternativeNode::make_ending_(Node* left_child, Node* right_child) {
	auto ending = SetHelper::make_union_of_Symbol_sets(
		left_child->ending(), right_child->ending());
	return ending;
}
bool AlternativeNode::make_epsilon_(Node* left_child, Node* right_child) {
	return left_child->epsilon() || right_child->epsilon();
}

