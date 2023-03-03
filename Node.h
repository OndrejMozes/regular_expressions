#ifndef __NODE_H
#define __NODE_H

#include <set>
#include <iostream>
#include "Symbol.h"


// Making the make_x_ methods virtual and just calling them
// in the parent constructor would not work since the overriding
// of parent virtual methods has not yet taken place inside a
// parent constructor.


class Node {
public:
	virtual ~Node();
	void print(std::ostream& os = std::cout) const;
	const std::set<Symbol>& starting() const;
	const std::set<SymbolPair>& neighbors() const;
	const std::set<Symbol>& ending() const;
	const bool epsilon() const;
protected:
	Node(std::set<Symbol> starting, std::set<SymbolPair> neighbors,
		std::set<Symbol> ending, bool epsilon);
private:
	std::set<Symbol> starting_;
	std::set<SymbolPair> neighbors_;
	std::set<Symbol> ending_;
	bool epsilon_;
};

inline const std::set<Symbol>& Node::starting() const {
	return this->starting_;
}
inline const std::set<SymbolPair>& Node::neighbors() const {
	return this->neighbors_;
}
inline const std::set<Symbol>& Node::ending() const {
	return this->ending_;
}
inline const bool Node::epsilon() const {
	return this->epsilon_;
}

class SymbolNode final : public Node {
public:
	SymbolNode(Symbol symbol);
private:
	std::set<Symbol> make_starting_(Symbol symbol);
	std::set<SymbolPair> make_neighbors_();
	std::set<Symbol> make_ending_(Symbol symbol);
	bool make_epsilon_();
	Symbol symbol_;
};

class EmptyStringNode final : public Node {
public:
	EmptyStringNode();
private:
	std::set<Symbol> make_starting_();
	std::set<SymbolPair> make_neighbors_();
	std::set<Symbol> make_ending_();
	bool make_epsilon_();
};

class EmptyLanguageNode final : public Node {
public:
	EmptyLanguageNode();
private:
	std::set<Symbol> make_starting_();
	std::set<SymbolPair> make_neighbors_();
	std::set<Symbol> make_ending_();
	bool make_epsilon_();
};

class IterationNode final : public Node {
public:
	IterationNode(Node* child);
	~IterationNode();
private:
	std::set<Symbol> make_starting_(Node* child);
	std::set<SymbolPair> make_neighbors_(Node* child);
	std::set<Symbol> make_ending_(Node* child);
	bool make_epsilon_();
	Node* child_;
};

class BinaryOperationNode : public Node {
public:
	virtual ~BinaryOperationNode();
protected:
	BinaryOperationNode(std::set<Symbol> starting, std::set<SymbolPair> neighbors,
		std::set<Symbol> ending, bool epsilon, Node* left_child, Node* right_child);
	Node* left_child_, * right_child_;
};

class ConcatenationNode final : public BinaryOperationNode {
public:
	ConcatenationNode(Node* left_child, Node* right_child);
private:
	std::set<Symbol> make_starting_(Node* left_child, Node* right_child);
	std::set<SymbolPair> make_neighbors_(Node* left_child, Node* right_child);
	std::set<Symbol> make_ending_(Node* left_child, Node* right_child);
	bool make_epsilon_(Node* left_child, Node* right_child);
};

class AlternativeNode final : public BinaryOperationNode {
public:
	AlternativeNode(Node* left_child, Node* right_child);
private:
	std::set<Symbol> make_starting_(Node* left_child, Node* right_child);
	std::set<SymbolPair> make_neighbors_(Node* left_child, Node* right_child);
	std::set<Symbol> make_ending_(Node* left_child, Node* right_child);
	bool make_epsilon_(Node* left_child, Node* right_child);
};




#endif // !__NODE_H
