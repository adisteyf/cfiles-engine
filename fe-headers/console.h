#ifndef __FE_CONSOLE
#define __FE_CONSOLE

#include <sstream>
#include <thread>


class Console
{
public:
  Console();
  ~Console();

  void input(std::string input);
	void process_input();
	void start_thread();

  std::ostringstream oss;
  std::istringstream iss;
	bool work = true;
	std::thread t;
};

#endif // __FE_CONSOLE
