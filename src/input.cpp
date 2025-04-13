#include "input.h"
#include "window.h"
#include <GLFW/glfw3.h>



void Input::checkInput(Window * window, Camera &cam)
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

    int showImGuiCurr = window->windowGetKey(GLFW_KEY_RIGHT_SHIFT, GLFW_PRESS);
    if (showImGuiCurr && !showImGuiState) {
        cam.showImGui = !cam.showImGui;
    }

    showImGuiState = showImGuiCurr;
}
