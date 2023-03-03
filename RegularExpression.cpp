#include "RegularExpression.h"
#include "Parser.h"

RegularExpression::RegularExpression(const std::string& s): input_string_(s){
	root_ = Parser::parse(s);
	valid_ = (root_ != nullptr);
}

RegularExpression::~RegularExpression() {
	if (root_ != nullptr) {
		delete root_;
		root_ = nullptr;
	}
}
void RegularExpression::print(std::ostream& os) {
	os << input_string_ << std::endl;
	root_->print();
}
