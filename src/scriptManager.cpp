#include "scriptManager.h"

ScriptManager::ScriptManager(Window * window, Shader * shader, Shader * outlineShader, Input * input)
    : fe_window_ptr(window), fe_def_shader_ptr(shader), fe_outline_shader_ptr(outlineShader), fe_input_ptr(input)
{
}
