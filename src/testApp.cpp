#include "testApp.h"
#include "FBO.h"
#include "camera.h"
#include "model.h"
#include "shader.h"
#include "window.h"
#include "fe-settings.h"
#include "main.h"
#include "textRenderer.h"
#include "fe-logic.h"

/* ImGui */
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <cmath>
#include <ostream>

extern Camera * mainCamera;
extern Shader * modelDrawShader;

FeTestApp::FeTestApp(void)
    : input(fe_getInput()), 
      shader(fe_getShader(0)), 
      outlineShader(fe_getShader(1)), 
      txtShader(new Shader("shaders/shader_txt.glsl")),
      txtRenderer(new TextRenderer(*txtShader, "assets/fonts/ProggyCleanRu.ttf", 40)),
      window(fe_getWindow())
{
    camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(-2.f, 8.f, 4.f), 45.0f, 0.1f, 100.0f);
    mainCamera = camera;
    Model * model = new Model("assets/models/bunny/scene.gltf");

    glfwSetWindowUserPointer(window->getWindow(), camera);
    setupImGui(window->getWindow());

    addModel(model);
}

void FeTestApp::cycle(void)
{
    if (window->windowGetMouseButton(GLFW_MOUSE_BUTTON_RIGHT, GLFW_PRESS)) {
        FBO * fbo = fe_getFBO();
        double mouseX, mouseY;
        glfwGetCursorPos(window->getWindow(), &mouseX, &mouseY);
        uint modelID = fbo->getModelID((int)mouseX, (int)mouseY);

        std::cout << "ID in big-endian: " << modelID << std::endl;
    }

    // TODO: add drawOutline func
    /*glStencilFunc(GL_ALWAYS, 1, 0xff);
    glStencilMask(0xff);*/
/*

    glStencilFunc(GL_NOTEQUAL, 1, 0xff);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    outlineShader->bind();
    outlineShader->setUniform("outlining", 0.08f);
    model->draw(*outlineShader, *camera);

    glStencilMask(0xff);
    glStencilFunc(GL_ALWAYS, 0, 0xff);
    glEnable(GL_DEPTH_TEST);*/

    if (camera->showImGui) {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        ImGui::Begin("Settings");
            ImGui::SliderFloat("Speed", &camera->speed, 0.001, 0.5);
        ImGui::End();


        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    txtRenderer->RenderText(*txtShader, "Sample text", 25.0f, 25.0f, .5f, glm::vec3(0.5, 0.8f, 0.2f));
}

void FeTestApp::free(void)
{
    delete txtShader;
    delete txtRenderer;
    delete camera;
}
