#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include "fe-kernel.h"
#include "fe-settings.h"
#include "mesh.h"
#include "texture.h"
#include "window.h"
#include "camera.h"
#include "model.h"
#include "debug.h"
#include "input.h"
#include "textRenderer.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

float aspect_ratio = 0;

void windowResizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);

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
}



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
    felog("fe_main(): initializing GLFW...");
    Window::initGLFW();
    felog("fe_main(): initializing window...");
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Files Engine");

    felog("fe_main(): initializing shader...");
    Shader shader("shaders/shader_def.glsl");
    felog("fe_main(): initializing model...");

    felog("fe_main(): initializing light shader...");

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    felog("fe_main(): initializing light model...");
    glm::vec3 lightPos(0.5f, 0.5f, 0.5f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);

    felog("fe_main(): binding shader...");
    shader.bind();
    felog("fe_main(): setting pyramid model...");

    glUniform4f(glGetUniformLocation(shader.getProgram(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    felog("fe_main(): enabling depth test...");
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    felog("next is glDebugMessageCallback");
    glDebugMessageCallback(debugCallback, 0);

    felog("next is glfwSetWindowSizeCallback");
    glfwSetWindowSizeCallback(window.getWindow(), windowResizeCallback);

    felog("calculating aspect_ratio...");
    GLFWmonitor * primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode * mmode = glfwGetVideoMode(primaryMonitor);
    aspect_ratio = mmode->width / mmode->height;

    felog("fe_main(): initializing camera...");
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(-2.f, 8.f, 4.f));

    felog("fe_main(): initializing imgui...");
    setupImGui(window.getWindow());


    Model model("assets/models/sword/scene.gltf");
    Input input;
    TextRenderer txtRenderer;
    Shader txtShader("shaders/shader_txt.glsl");
    txtRenderer.init(txtShader, "assets/fonts/ProggyCleanRu.ttf");
    // TODO: сделать адекватный конструктор для txtRenderer


    felog("fe_main(): entering main loop...");
    while (!window.shouldClose() && !fe_status) {
        felog("fe_main(): polling events...");
        window.pollEvents();
        felog("fe_main(): clearing window...");
        window.clear();

        felog("fe_main(): updating camera...");
        input.checkInput(window.getWindow(), camera);
        //camera.inputs(window.getWindow());
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        model.draw(shader, camera);
        if (camera.showImGui) {
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplGlfw_NewFrame();
            ImGui::NewFrame();

            ImGui::ShowDemoWindow();
            ImGui::Render();

            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        }

        txtRenderer.RenderText(txtShader, "Sample text", 25.0f, 25.0f, 1.f, glm::vec3(0.5, 0.8f, 0.2f));
        felog("fe_main(): swapping buffers...");
        window.swapBuffers();

        felog("fe_main(): end of main loop");
    }

    felog("fe_main(): exiting main loop (end of fe_main)...");
    shader.killShader();
    window.killWindow();
}

