#ifndef __SYMBOL_H
#define __SYMBOL_H

#include <iostream>

class Symbol {
public:
	Symbol(char symbol, int index);
	void print(std::ostream& os = std::cout) const;
	char symbol;
	int index;
};
bool operator<(const Symbol& left, const Symbol& right);
bool operator==(const Symbol& left, const Symbol& right);
std::ostream& operator<<(std::ostream& os, const Symbol& s);

class SymbolPair {
public:
	SymbolPair(Symbol first_symbol, Symbol second_symbol);
	void print(std::ostream& os = std::cout) const;
	Symbol first_symbol, second_symbol;
};
bool operator<(const SymbolPair& left, const SymbolPair& right);
std::ostream& operator<<(std::ostream& os, const SymbolPair& sp);



#endif // !__SYMBOL_H
