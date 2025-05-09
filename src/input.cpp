#include "input.h"
#include "fe-settings.h"
#include "testApp.h"
#include "window.h"
#include <GLFW/glfw3.h>


FE_SCRIPTS_EXTERN
void Input::checkInput(Window * window, Camera &cam)
{
    FE_INPUT_SCRIPTS

    int showImGuiCurr = window->windowGetKey(GLFW_KEY_RIGHT_SHIFT, GLFW_PRESS);
    if (showImGuiCurr && !showImGuiState) {
        cam.showImGui = !cam.showImGui;
    }

    showImGuiState = showImGuiCurr;
}
