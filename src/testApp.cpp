#include "testApp.h"
#include "camera.h"
#include "model.h"
#include "shader.h"
#include "window.h"
#include "fe-settings.h"
#include "main.h"

/* ImGui */
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"



FeTestApp::FeTestApp(void)
    : input(fe_getInput()), 
      shader(fe_getShader(0)), 
      outlineShader(fe_getShader(1)), 
      window(fe_getWindow())
{
    camera = new Camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(-2.f, 8.f, 4.f));
    model  = new Model("assets/models/sword/scene.gltf");

    glfwSetWindowUserPointer(window->getWindow(), camera);
    setupImGui(window->getWindow());
}

void FeTestApp::cycle(void)
{
    felog("fe_main(): checking input...");
    input->checkInput(window->getWindow(), *camera);
    felog("fe_main(): updating camera...");
    camera->updateMatrix(45.0f, 0.1f, 100.0f);

    glStencilFunc(GL_ALWAYS, 1, 0xff);
    glStencilMask(0xff);
    model->draw(*shader, *camera);

    glStencilFunc(GL_NOTEQUAL, 1, 0xff);
    glStencilMask(0x00);
    glDisable(GL_DEPTH_TEST);
    outlineShader->bind();
    outlineShader->setUniform("outlining", 0.08f);
    model->draw(*outlineShader, *camera);

    glStencilMask(0xff);
    glStencilFunc(GL_ALWAYS, 0, 0xff);
    glEnable(GL_DEPTH_TEST);

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
}
