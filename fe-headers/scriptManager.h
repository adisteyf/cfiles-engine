#ifndef FE_SCRIPT_MANAGER
#define FE_SCRIPT_MANAGER

#include "window.h"
#include "input.h"
#include "shader.h"

class ScriptManager
{
public:
    ScriptManager(Window * window, Shader * shader, Shader * outlineShader, Input * input);
    void cycle(void);

    Window * fe_window_ptr;
    Input  * fe_input_ptr;
    Shader * fe_def_shader_ptr;
    Shader * fe_outline_shader_ptr;
};
#endif // FE_SCRIPT_MANAGER
