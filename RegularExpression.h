#ifndef __REGULAR_EXPRESSION_H
#define __REGULAR_EXPRESSION_H

#include <string>
#include <iostream>
#include "Node.h"


class RegularExpression {
public:
	RegularExpression(const std::string& s);
	~RegularExpression();
	void print(std::ostream& os = std::cout);
	const bool valid() const;
private:
	const Node* root_;
	const std::string input_string_;
	bool valid_;
};

inline const bool RegularExpression::valid() const{
	return valid_;
}

#endif
