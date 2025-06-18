#ifndef FE_SETTINGS_H
#define FE_SETTINGS_H

#include "VAO.h"
#include <iostream>

/* settings for fe-kernel */
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define FE_CLEARCOLOR 0.34f, 0.6f, 1.0f, 1.f

//#define LOG_LEVEL_INFO

#define FE_GLFW_MAJOR 4
#define FE_GLFW_MINOR 3

#define FE_ENABLE_FBOPICKING
#define FE_GLFW_NO_SETCURSOR /* if glfwSetCursorPos() didn't work */
#define FE_ASPECT_RATIO
#define FE_ENABLE_CULLFACE



#ifdef FE_ENABLE_CULLFACE

/* you can redact face culling flags here */
#define FE_CULLFACE_FLAGS \
    glEnable(GL_CULL_FACE); \
    glCullFace(GL_FRONT); \
    glFrontFace(GL_CCW);
#else
#define FE_CULLFACE_FLAGS
#endif

#define FE_GLENABLE \
    glEnable(GL_DEPTH_TEST); \
    FE_CULLFACE_FLAGS \
    glEnable(GL_DEBUG_OUTPUT); \
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS); \
    glEnable(GL_BLEND); \
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); \
    /*glEnable(GL_STENCIL_TEST); */\
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

#define FE_SCRIPTS \
    FeTestApp * fe_test;

#define FE_SCRIPTS_EXTERN \
    extern FeTestApp * fe_test;

#define FE_SCRIPTS_START \
    fe_test = new FeTestApp();

#define FE_CYCLE_SCRIPTS \
    fe_test->cycle();

#define FE_FREE_SCRIPTS \
    fe_test->free();

#define FE_INPUT_SCRIPTS \
    fe_test->input_callback(window,cam);

#define FE_WINRESIZE_SCRIPTS
//    fe_test->winresize_callback(window, width, height);

//#define FE_ENABLE_STENCIL

const int FE_CLEARFLAGS =
GL_COLOR_BUFFER_BIT
| GL_DEPTH_BUFFER_BIT
#ifdef FE_ENABLE_STENCIL
| GL_STEGL_STENCIL_BUFFER_BIT
#endif
;


#define RED "\033[31m"
#define RESET "\033[0m"
#define BLUE "\033[34m"
#define felogftl(msg) std::cerr << RED "FE_FATAL: " << msg << RESET << std::endl
#define felogerr(msg) std::cerr << RED "FE_ERROR: " << RESET << msg << std::endl

/* define log function, if LOG_LEVEL_INFO is defined, it will be a normal log, otherwise it will be a no-op */
#ifdef LOG_LEVEL_INFO
#define felog(msg) std::cout << BLUE "INFO: " << msg << RESET << std::endl
#else
#define felog(msg)
#endif

#endif /* FE_SETTINGS_H */
