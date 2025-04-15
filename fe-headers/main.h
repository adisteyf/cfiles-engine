#ifndef FE_GENERAL_API
#define FE_GENERAL_API

#include "FBO.h"
#include "input.h"
#include "shader.h"
#include "window.h"
#include "fe-settings.h"

Input  * fe_getInput(void);
Shader * fe_getShader(int type);
Window * fe_getWindow(void);
#ifdef FE_ENABLE_FBOPICKING
FBO    * fe_getFBO(void);
#endif

void setupImGui(GLFWwindow * window);

#endif // FE_GENERAL_API
