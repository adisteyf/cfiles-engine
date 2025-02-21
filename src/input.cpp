#include "input.h"



void Input::checkInput(GLFWwindow * window, Camera &cam)
{
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cam.pos += cam.speed * cam.orientation;
        printf("campos changed (%f)\n", cam.pos.x);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cam.pos -= cam.speed * glm::normalize(glm::cross(cam.orientation, cam.up));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cam.pos -= cam.speed * cam.orientation;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cam.pos += cam.speed * glm::normalize(glm::cross(cam.orientation, cam.up));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        cam.pos += cam.speed * cam.up;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        cam.pos -= cam.speed * cam.up;
    }

    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) {
        cam.speed = 0.4f;
    }
    if (glfwGetKey(window, GLFW_KEY_P) == GLFW_RELEASE) {
        cam.speed = 0.1f;
    }

    int showImGuiCurr = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
    if (showImGuiCurr == GLFW_PRESS && showImGuiState == GLFW_RELEASE) {
        showImGui = !showImGui;
    }

    showImGuiState = showImGuiCurr;

    std::cout << cam.pos.x << std::endl;
    std::cout << cam.pos.y << std::endl;
    std::cout << cam.pos.z << std::endl;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !showImGui) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        int half_w = cam.w/2;
        int half_h = cam.h/2;

        if (firstClick) {
            glfwSetCursorPos(window, half_w, half_h);
            firstClick = false;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float deltaX = (float)(mouseX - half_w);
        float deltaY = (float)(mouseY - half_h);

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
        glfwSetCursorPos(window, half_w, half_h);
    }

    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}
