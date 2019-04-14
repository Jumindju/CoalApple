#pragma once

#include <string>
#include <fstream>
#include <iostream>

namespace utils {
	std::string readFile(const char* fileName) {
		std::ifstream in(fileName);
		std::string contents((std::istreambuf_iterator<char>(in)),
			std::istreambuf_iterator<char>());

		return contents;
	}
}