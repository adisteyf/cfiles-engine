#ifndef __FE_CONSOLE
#define __FE_CONSOLE

#include <sstream>
#include <vector>
#include <thread>

class Console
{
public:
  Console();
  ~Console();


	std::vector<std::string> split_args(const std::string &input);

  void input(std::string input);
	void process_input();
	void start_thread();
	void set_int(std::vector<std::string> args, int *var);
	void set_bool(std::vector<std::string> args, bool *var);

  std::ostringstream oss;
  std::istringstream iss;
};

#endif // __FE_CONSOLE
