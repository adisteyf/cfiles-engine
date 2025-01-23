#ifndef FE_SETTINGS_H
#define FE_SETTINGS_H

#include <iostream>

// settings for fe-kernel
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define LOG_LEVEL_INFO

#define FE_GLFW_MAJOR 4
#define FE_GLFW_MINOR 3

#define RED "\033[31m"
#define RESET "\033[0m"
#define BLUE "\033[34m"
#define felogftl(msg) std::cerr << RED "FE_FATAL: " << msg << RESET << std::endl
#define felogerr(msg) std::cerr << RED "FE_ERROR: " << RESET << msg << std::endl

// define log function, if LOG_LEVEL_INFO is defined, it will be a normal log, otherwise it will be a no-op
#ifdef LOG_LEVEL_INFO
#define felog(msg) std::cout << BLUE "INFO: " << msg << RESET << std::endl
#else
#define felog(msg)
#endif

#endif // FE_SETTINGS_H
