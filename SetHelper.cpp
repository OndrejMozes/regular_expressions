#include "SetHelper.h"

/*
I think the way to avoid this duplicate code is to use templates,
but we haven't gotten to templates in c++ yet.
*/
void SetHelper::print_Symbol_set(const std::set<Symbol>& set, std::ostream& os) {
	os << "{";
	for (auto it = set.begin(); it != set.end(); ++it) {
		os << *it;
		auto it_plus_one = it;
		++it_plus_one;
		if (it_plus_one != set.end()) os << ", ";
	}
	os << "}";
}

void SetHelper::print_SymbolPair_set(const std::set<SymbolPair>& set, std::ostream& os) {
	os << "{";
	for (auto it = set.begin(); it != set.end(); ++it) {
		os << *it;
		auto it_plus_one = it;
		++it_plus_one;
		if (it_plus_one != set.end()) os << ", ";
	}
	os << "}";
}

std::set<Symbol> SetHelper::make_union_of_Symbol_sets(const std::set<Symbol>& first_set,
	const std::set<Symbol>& second_set) {
	std::set<Symbol> union_set = std::set<Symbol>(first_set);
	for (auto s : second_set) {
		union_set.insert(s);
	}
	return union_set;
}

std::set<SymbolPair> SetHelper::make_union_of_SymbolPair_sets(const std::set<SymbolPair>& first_set,
	const std::set<SymbolPair>& second_set) {
	std::set<SymbolPair> union_set = std::set<SymbolPair>(first_set);
	for (auto sp : second_set) {
		union_set.insert(sp);
	}
	return union_set;
}

std::ostream& operator<<(std::ostream& os, const std::set<Symbol>& ss) {
	SetHelper::print_Symbol_set(ss);
	return os;
}

std::ostream& operator<<(std::ostream& os, const std::set<SymbolPair>& sps) {
	SetHelper::print_SymbolPair_set(sps);
	return os;
}
