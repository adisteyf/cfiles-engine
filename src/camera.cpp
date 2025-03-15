#include "camera.h"

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
    shader.setUniform(uniform, cameraMatrix);
}

