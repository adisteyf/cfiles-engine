#include "console.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <streambuf>
#include "fe-commands.h"

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

std::vector<std::string> Console::split_args(const std::string &input) { /* FIXME: Bad " and \ */
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

void Console::set_bool(std::vector<std::string> args, bool *var) {
		if (args.size() != 2) {
			std::string err = (args.size() > 2) ? "Too many args." : "Too few args.";
			std::cout << err << std::endl;
			return;
		}
		
		if (args[1] == "0" || args[1] == "false") { *var = false; return; }
		if (args[1] == "1" || args[1] == "true")  { *var = true;  return; }

		std::cout << "invalid value. (1/0/true/false)" << std::endl;
}

void Console::set_int(std::vector<std::string> args, int *var) {
	if (args.size() != 2) {
		std::string err = (args.size() > 2) ? "Too many args." : "Too few args.";
		std::cout << err << std::endl;
		return;
	}

	int res;

	try {
		res = std::stoi(args[1]);
	}

	catch (const std::invalid_argument &e) { return; }
	catch (const std::out_of_range &e)     { return; }

	*var = res;
}

extern fe_rd rd;
void Console::process_input() {
//	while (Console::work) {
		std::string cmd;
		getline(std::cin, cmd);
		std::vector<std::string> args = split_args(cmd);

		if (args[0] == "echo" && args.size() > 1) {
			std::cout << args[1] << std::endl;
			return;
		}

		if (args[0] == "fe-tch") {
			std::cout << "fe-tch command" << std::endl;
			return;
		}

		/* rd. tier */
		if (args[0] == "rd.wireframe") {
			return set_bool(args, &rd.wireframe);
		}

		if (args[0] == "rd.wireframe_len") {
			return set_int(args, &rd.wireframe_len);
		}

//	}
}

//void Console::start_thread() {
//	this->t = std::thread([this]() { this->process_input(); });
//}
