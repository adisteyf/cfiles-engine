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
    glClearColor(0.07f, 0.13f, 0.17f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void Window::initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        fe_panic();
    }
}

