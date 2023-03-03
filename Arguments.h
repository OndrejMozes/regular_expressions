#ifndef __ARGUMENTS_H
#define __ARGUMENTS_H

#include <vector>
#include <string>
#include <fstream>

enum class InputMode {ARGUMENT, FILE};

const std::string ARGUMENT_OPTION = "-a",
				  FILE_OPTION = "-f";

using args_t = std::vector<std::string>;

class ArgumentReader {
public:
	ArgumentReader(char** args_start, char** args_end);
	/// <summary> Gets the next string from the input defined by the arguments </summary>
	/// <param name="output"> Where to set the next string </param>
	/// <param name="error"> If an error was encountered </param>
	/// <returns> 
	/// If the output was succesfully set
	/// false if the end of the input was reached or an error was encountered
	/// </returns>
	bool get_next_string(std::string& output, bool& error);
private:
	bool get_next_string_from_file(std::string& output, bool& error);
	args_t arguments_;
	args_t::iterator args_it_;
	InputMode input_mode_;
	std::ifstream input_file_stream_;
};

#endif
