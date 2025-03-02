#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "imgui.h"
#include "camera.h"

class Input {
    public:
        int showImGuiState = GLFW_RELEASE;
        bool firstClick = true;
        bool showImGui = false;
        void checkInput(GLFWwindow * window, Camera &cam);
};
