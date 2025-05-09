#include "fe-settings.h"
#include "testApp.h"
#include "FBO.h"
#include "camera.h"
#include "model.h"
#include "shader.h"
#include "window.h"
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
    Model * model  = new Model("assets/models/vec3arr/scene.gltf");
    Model * model1 = new Model("assets/models/sword/scene.gltf");
    model->shType = 0;

    glfwSetWindowUserPointer(window->getWindow(), camera);
    setupImGui(window->getWindow());

    addModel(model);
    addModel(model1);
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

    if (window->windowGetKey(GLFW_KEY_F, GLFW_PRESS)) {
        Model * model = getModel(0);
        model->changePos(glm::vec3(1.0f, 1.f, 1.f));
    }

    if (window->windowGetKey(GLFW_KEY_G, GLFW_PRESS)) {
        Model * model = getModel(0);
        model->changePos(glm::vec3(0.f,0.f,0.f));
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

void FeTestApp::input_callback(Window * window, Camera &cam)
{
    if (!cam.showImGui) {
        if (window->windowGetKey(GLFW_KEY_W, GLFW_PRESS)) {
            cam.pos += cam.speed * cam.orientation;
            printf("campos changed (%f)\n", cam.pos.x);
        }
        if (window->windowGetKey(GLFW_KEY_A, GLFW_PRESS)) {
            cam.pos -= cam.speed * glm::normalize(glm::cross(cam.orientation, cam.up));
        }
        if (window->windowGetKey(GLFW_KEY_S, GLFW_PRESS)) {
            cam.pos -= cam.speed * cam.orientation;
        }
        if (window->windowGetKey(GLFW_KEY_D, GLFW_PRESS)) {
            cam.pos += cam.speed * glm::normalize(glm::cross(cam.orientation, cam.up));
        }
        if (window->windowGetKey(GLFW_KEY_SPACE, GLFW_PRESS)) {
            cam.pos += cam.speed * cam.up;
        }
        if (window->windowGetKey(GLFW_KEY_LEFT_CONTROL, GLFW_PRESS)) {
            cam.pos -= cam.speed * cam.up;
        }

        if (window->windowGetKey(GLFW_KEY_P, GLFW_PRESS)) {
            cam.speed = 0.4f;
        }
        if (window->windowGetKey(GLFW_KEY_P, GLFW_RELEASE)) {
            //cam.speed = 0.1f;
        }

        #ifdef LOG_LEVEL_INFO
        std::cout << cam.pos.x << std::endl;
        std::cout << cam.pos.y << std::endl;
        std::cout << cam.pos.z << std::endl;
        #endif

        if (window->windowGetMouseButton(GLFW_MOUSE_BUTTON_LEFT, GLFW_PRESS) && !cam.showImGui) {
            window->hideCursor();

            glm::vec2 center = {
                cam.w/2,
                cam.h/2,
            };

            if (firstClick) {
                window->setCursorPos(center.x, center.y);
                firstClick = false;
            }

            double mouseX, mouseY;
            window->getCursorPos(&mouseX, &mouseY);

            float deltaX = (float)(mouseX - center.x);
            float deltaY = (float)(mouseY - center.y);

            float rotX = cam.sensitivity * deltaY / cam.h;
            float rotY = cam.sensitivity * deltaX / cam.w;
            glm::vec3 newOrientation = glm::rotate(cam.orientation, glm::radians(-rotX), glm::normalize(glm::cross(cam.orientation, cam.up)));

            if (abs((int)glm::angle(newOrientation, cam.up) - (int)glm::radians(90.0f)) <= glm::radians(85.0f)) {
                cam.orientation = newOrientation;
            }

            cam.orientation = glm::rotate(cam.orientation, glm::radians(-rotY), cam.up);

            std::cout << cam.orientation.x << std::endl;
            std::cout << cam.orientation.y << std::endl;
            std::cout << cam.orientation.z << std::endl;
            window->setCursorPos(center.x, center.y);
        }

        else if (window->windowGetMouseButton(GLFW_MOUSE_BUTTON_LEFT, GLFW_RELEASE)) {
            window->normalCursor();
            firstClick = true;
        }
    }
}

void FeTestApp::free(void)
{
    delete txtShader;
    delete txtRenderer;
    delete camera;
}
