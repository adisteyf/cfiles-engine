#include "console.h"
#include <iostream>
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

void Console::process_input() {
//	while (Console::work) {
		std::string cmd;
		getline(std::cin, cmd);
		std::cout << cmd << std::endl;
//	}
}

//void Console::start_thread() {
//	this->t = std::thread([this]() { this->process_input(); });
//}
