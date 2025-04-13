/* Headers for Graphics API */
#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* fe-headers */
#include "FBO.h"
#include "fe-kernel.h"
#include "fe-settings.h"
#include "window.h"
#include "camera.h"
#include "model.h"
#include "debug.h"
#include "input.h"
#include "textRenderer.h"
#include "scriptManager.h"
#include "testApp.h"

/* ImGui */
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

/* std */
#include <glm/matrix.hpp>
#include <optional>





#ifdef FE_ENABLE_FBOPICKING
FBO    * fboPicking       = nullptr;
Shader * pickingShader    = nullptr;
#endif
Shader * shader        = nullptr;
Shader * outlineShader = nullptr;
Window * window        = nullptr;
Input  * input         = nullptr;
FE_SCRIPTS

Shader* fe_getShader(int type)
{
    switch (type) {
        case 0: return shader;
        case 1: return outlineShader;
        default: return 0;
    }
}

Window* fe_getWindow(void) {
    return window;
}

Input* fe_getInput(void) {
    return input;
}

void fe_preWorkFuncs(void)
{
    Window::initGLFW();
    fe_GLContext();
}


extern float aspect_ratio;




void setupImGui(GLFWwindow * window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void)io;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

void fe_main()
{
    felog("fe_main(): enabling pre-work functions...");
    fe_preWorkFuncs();
    felog("fe_main(): initializing window...");
    window = new Window(WINDOW_WIDTH, WINDOW_HEIGHT, "Files Engine");

    felog("fe_main(): initializing shader...");
    shader = new Shader("shaders/shader_def.glsl");
    outlineShader = new Shader("shaders/outline_shader.glsl");

    felog("fe_main(): initializing model...");
    felog("fe_main(): initializing light shader...");

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    felog("fe_main(): initializing light model...");
    glm::vec3 lightPos(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    felog("fe_main(): binding shader...");
    shader->bind();
    shader->setUniform("lightColor", lightColor);
    shader->setUniform("lightPos", lightPos);

    felog("fe_main(): enabling glEnables...");
    FE_GLENABLE
    felog("next is glDebugMessageCallback");
    glDebugMessageCallback(debugCallback, 0);

    felog("next is setWindowSizeCallback");
    WINDOW_SETRESIZECB
#ifdef FE_ASPECT_RATIO
    felog("calculating aspect_ratio...");
    windowGetAspectRatio();
#endif

    input = new Input();
#   ifdef FE_ENABLE_FBOPICKING
    fboPicking = new FBO(window->getWidth(), window->getHeight());
    fboShader = new Shader("shaders/pickingShader.glsl");
#   endif
    FE_SCRIPTS_START

    felog("fe_main(): entering main loop...");
    while (!window->shouldClose() && !fe_status) {
        felog("fe_main(): polling events...");
        window->pollEvents();
        felog("fe_main(): clearing window...");
        window->clear();

        FE_CYCLE_SCRIPTS

        felog("fe_main(): swapping buffers...");
        window->swapBuffers();

        felog("fe_main(): end of main loop");
    }

    felog("fe_main(): exiting main loop (end of fe_main)...");
    FE_FREE_SCRIPTS
    window->killWindow();
    delete input;
    delete window;
    delete shader;
    delete outlineShader;
#   ifdef FE_ENABLE_FBOPICKING
    delete fboPicking;
#   endif
}

