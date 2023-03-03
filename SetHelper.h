#ifndef __SETHELPER_H
#define __SETHELPER_H

#include "Symbol.h"
#include <set>


class SetHelper {
public:
	static void print_Symbol_set(const std::set<Symbol>& set,
		std::ostream& os = std::cout);
	static void print_SymbolPair_set(const std::set<SymbolPair>& set,
		std::ostream& os = std::cout);
	static std::set<Symbol> make_union_of_Symbol_sets(const std::set<Symbol>& first_set,
		const std::set<Symbol>& second_set);
	static std::set<SymbolPair> make_union_of_SymbolPair_sets(
		const std::set<SymbolPair>& first_set, const std::set<SymbolPair>& second_set);
};
std::ostream& operator<<(std::ostream& os, const std::set<Symbol>& ss);
std::ostream& operator<<(std::ostream& os, const std::set<SymbolPair>& sps);



#endif // !__SETHELPER_H
