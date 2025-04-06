#include "window.h"
#include "fe-settings.h"

Window::Window(int w, int h, const char* t) : width(w), height(h), title(t)
{
    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        fe_panic();
    }

    glfwMakeContextCurrent(window);
    
    if (!gladLoadGL()) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        fe_panic();
    }

    glViewport(0, 0, width, height);
}

void Window::killWindow() {
    if (window) glfwDestroyWindow(window);
    terminateGLFW();
}

void Window::clear() {
    glClearColor(
        FE_CLEARCOLOR
    );
    glClear
    (
        GL_COLOR_BUFFER_BIT
        | GL_DEPTH_BUFFER_BIT
#ifdef FE_ENABLE_STENCIL
        | GL_STENCIL_BUFFER_BIT
#endif
    );
}

void Window::initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        fe_panic();
    }
}

