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
}
