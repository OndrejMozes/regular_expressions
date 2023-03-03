#include "Arguments.h"
#include "RegularExpression.h"

int main(int argc, char** argv) {
	ArgumentReader ar = ArgumentReader(argv + 1, argv + argc);
	std::string s;
	bool error;
	while (ar.get_next_string(s, error)) {
		RegularExpression re(s);
		if (!re.valid()) return 1;
		re.print();
	}
	if (error) return 1;
	return 0;
}