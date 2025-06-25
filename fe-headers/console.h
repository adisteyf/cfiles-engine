#ifndef __FE_CONSOLE
#define __FE_CONSOLE

#include <sstream>


class Console
{
public:
  Console();
  ~Console();

  void input(std::string input);

  std::ostringstream oss;
  std::istringstream iss;
};

#endif // __FE_CONSOLE
