#include "camera.h"

// TODO: add lastMouseX/Y and use it instead glfwSetCursorPos()
void Camera::updateMatrix(void)
{
    view = glm::lookAt(pos, pos + orientation, up);
    projection = glm::perspective(fov, (float)w / (float)h, near_plane, far_plane);
    cameraMatrix = projection * view;
}

void Camera::matrix(Shader &shader, const char *uniform) {
    shader.setUniform(uniform, cameraMatrix);
}

