#ifndef FE_GENERAL_API
#define FE_GENERAL_API

#include "input.h"
#include "shader.h"
#include "window.h"

Input  * fe_getInput(void);
Shader * fe_getShader(int type);
Window * fe_getWindow(void);

void setupImGui(GLFWwindow * window);

#endif // FE_GENERAL_API
