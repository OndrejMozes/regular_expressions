#include "Symbol.h"


Symbol::Symbol(char s, int i) : symbol(s), index(i) {}

void Symbol::print(std::ostream& os) const {
	os << symbol << ":" << index;
}

bool operator<(const Symbol& left, const Symbol& right) {
	return left.index < right.index;
}

bool operator==(const Symbol& left, const Symbol& right) {
	return left.index == right.index;
}

std::ostream& operator<<(std::ostream& os, const Symbol& s) {
	s.print();
	return os;
}

bool operator<(const SymbolPair& left, const SymbolPair& right) {
	return (left.first_symbol < right.first_symbol) ||
		(left.second_symbol < right.second_symbol&& left.first_symbol == right.first_symbol);
}

SymbolPair::SymbolPair(Symbol first_symbol, Symbol second_symbol) :
	first_symbol(first_symbol), second_symbol(second_symbol) {}

void SymbolPair::print(std::ostream& os) const {
	os << "(" << first_symbol << ", " << second_symbol << ")";
}

std::ostream& operator<<(std::ostream& os, const SymbolPair& sp) {
	sp.print();
	return os;
}