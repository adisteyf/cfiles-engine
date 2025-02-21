#include "camera.h"

bool firstClick = true;
Camera::~Camera() {}
// TODO: add lastMouseX/Y and use it instead glfwSetCursorPos()
int showImGuiState = GLFW_RELEASE;

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane) {
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 projection = glm::mat4(1.0f);

    view = glm::lookAt(pos, pos + orientation, up);
    projection = glm::perspective(glm::radians(FOVdeg), (float)w / (float)h, nearPlane, farPlane);
    cameraMatrix = projection * view;
}

void Camera::matrix(Shader &shader, const char *uniform) {
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), uniform), 1, GL_FALSE, glm::value_ptr(cameraMatrix));
}


void Camera::inputs(GLFWwindow *window) {
    int showImGuiCurr = glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT);
    if (showImGuiCurr == GLFW_PRESS && showImGuiState == GLFW_RELEASE) {
        showImGui = !showImGui;
    }

    showImGuiState = showImGuiCurr;

    std::cout << pos.x << std::endl;
    std::cout << pos.y << std::endl;
    std::cout << pos.z << std::endl;

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !showImGui) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

        int half_w = w/2;
        int half_h = h/2;

        if (firstClick) {
            glfwSetCursorPos(window, half_w, half_h);
            firstClick = false;
        }

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float deltaX = (float)(mouseX - half_w);
        float deltaY = (float)(mouseY - half_h);

        float rotX = sensitivity * deltaY / h;
        float rotY = sensitivity * deltaX / w;
        glm::vec3 newOrientation = glm::rotate(orientation, glm::radians(-rotX), glm::normalize(glm::cross(orientation, up)));

        if (abs((int)glm::angle(newOrientation, up) - (int)glm::radians(90.0f)) <= glm::radians(85.0f)) {
            orientation = newOrientation;
        }

        orientation = glm::rotate(orientation, glm::radians(-rotY), up);

        std::cout << orientation.x << std::endl;
        std::cout << orientation.y << std::endl;
        std::cout << orientation.z << std::endl;
        glfwSetCursorPos(window, half_w, half_h);
    }

    else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }
}
