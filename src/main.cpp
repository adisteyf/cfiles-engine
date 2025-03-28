/* Headers for Graphics API */
#include <glad/glad.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

/* fe-headers */
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
#include <optional>







Shader * shader        = nullptr;
Shader * outlineShader = nullptr;
Window * window        = nullptr;
Input  * input         = nullptr;

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



void fe_GLContext(void)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, FE_GLFW_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, FE_GLFW_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
}

void fe_preWorkFuncs(void)
{
    Window::initGLFW();
    fe_GLContext();
}


#ifdef FE_ASPECT_RATIO
float aspect_ratio = 0;

void windowResizeCallback(GLFWwindow* window, int width, int height) {
    float currentAspectRatio = (float)width / (float)height;

    if (currentAspectRatio > aspect_ratio) {
        int viewportWidth = (int)(height * aspect_ratio);
        int viewportX = (width - viewportWidth) / 2;
        glViewport(viewportX, 0, viewportWidth, height);
    } else {
        int viewportHeight = (int)(width / aspect_ratio);
        int viewportY = (height - viewportHeight) / 2;
        glViewport(0, viewportY, width, viewportHeight);
    }

    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera) {
        camera->w = width;
        camera->h = height;
        camera->updateMatrix();
    }
}
#endif



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

#ifdef FE_ASPECT_RATIO
    felog("next is glfwSetWindowSizeCallback");
    glfwSetWindowSizeCallback(window->getWindow(), windowResizeCallback);

    felog("calculating aspect_ratio...");
    GLFWmonitor * primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode * mmode = glfwGetVideoMode(primaryMonitor);
    aspect_ratio = (float)mmode->width / (float)mmode->height;
    printf("VIDM:\n%d\n%d\n%f\n", mmode->width, mmode->height, aspect_ratio);
#endif

    input = new Input();
    FE_SCRIPTS

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
    shader->killShader();
    window->killWindow();
    delete input;
    delete window;
    delete shader;
    delete outlineShader;
}

