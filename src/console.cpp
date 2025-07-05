#include "console.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <streambuf>

std::streambuf * origCoutBuff;
std::streambuf * origCinBuff;

Console::Console(void) {
    origCoutBuff = std::cout.rdbuf();
    origCinBuff  = std::cin.rdbuf();

    std::cout.rdbuf(oss.rdbuf());
    // std::cin.rdbuf(iss.rdbuf()); /* useless */
    std::cout << "stdout redirected" << std::endl;
}

Console::~Console() {
  std::cout.rdbuf(origCoutBuff);
  std::cin.rdbuf(origCinBuff);
}

void Console::input(std::string input) {
  iss.str(input);
  iss.clear();
  iss.seekg(0);
  std::cin.rdbuf(iss.rdbuf()); /* new buff */

	this->process_input();
}

std::vector<std::string> Console::split_args(const std::string &input) {
	std::vector<std::string> res;
	std::string crt;
	bool inQuotes = false;

	for (int i=0; i<input.size(); ++i) {
		char c = input[i];

		switch (c) {
			case '\"':
				inQuotes = !inQuotes;
				break;
			case ' ':
				if (!inQuotes && !crt.empty()) {
					res.push_back(crt);
					crt.clear();
				}
				break;
			case '\\':
				if (i + 1 < input.size() && (input[i + 1] == '\"' || input[i + 1] == '\\')) {
						crt += input[i+1]; i++;
				}
				break;

			default:
				crt += c;
		}
	}

	if (!crt.empty()) { res.push_back(crt); }
	return res;
}

void Console::process_input() {
//	while (Console::work) {
		std::string cmd;
		getline(std::cin, cmd);
		std::vector<std::string> args = split_args(cmd);

		if (args[0] == "echo" && args.size() > 1) {
			std::cout << args[1] << std::endl;
		}

		if (args[0] == "fe-tch") {
			std::cout << "fe-tch command" << std::endl;
		}
//	}
}

//void Console::start_thread() {
//	this->t = std::thread([this]() { this->process_input(); });
//}
