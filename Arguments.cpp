#include "Arguments.h"

ArgumentReader::ArgumentReader(char** args_start, char** args_end) :
	arguments_(args_t(args_start, args_end)), input_mode_(InputMode::ARGUMENT){
	args_it_ = arguments_.begin();
}

bool ArgumentReader::get_next_string(std::string& output, bool & error) {
	while (true) {
		if (!input_file_stream_.is_open() && args_it_ == arguments_.end()) {
			return false;
		} else if (!input_file_stream_.is_open() && args_it_ != arguments_.end() && *args_it_ == ARGUMENT_OPTION) {
			input_mode_ = InputMode::ARGUMENT;
			++args_it_;
		} else if (!input_file_stream_.is_open() && args_it_ != arguments_.end() && *args_it_ == FILE_OPTION) {
			input_mode_ = InputMode::FILE;
			++args_it_;
		} else if (!input_file_stream_.is_open() && args_it_ != arguments_.end() && input_mode_ == InputMode::ARGUMENT) {
			output = *args_it_;
			++args_it_;
			return true;
		} else if (input_mode_ == InputMode::FILE) {
			if (!get_next_string_from_file(output, error)) {
				if (error) {
					return false;
				} else {
					continue;
				}					
			}
			return true;
		}
	}
}

bool ArgumentReader::get_next_string_from_file(std::string& output, bool& error) {
	error = false;
	while (true) {
		if (!input_file_stream_.is_open()) {
			if (args_it_ == arguments_.end()) return false;
			input_file_stream_.open(*args_it_);
			if (!input_file_stream_.good()) {
				error = true;
				return false;
			}
			++args_it_;
		}
		if (!std::getline(input_file_stream_, output)) {
			input_file_stream_.close();
			return false;
		}
		if (output.empty()) continue; // skip empty lines
		return true;
	}
}