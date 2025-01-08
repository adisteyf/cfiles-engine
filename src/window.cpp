#include "window.h"

Window::Window(int w, int h, const char* t) : width(w), height(h), title(t) {
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

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

Window::~Window() {
    terminateGLFW();
    if (window) glfwDestroyWindow(window);
}

bool Window::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Window::swapBuffers() {
    glfwSwapBuffers(window);
}

void Window::pollEvents() {
    glfwPollEvents();
}

void Window::clear() {
    glClearColor(0.07f, 0.13f, 0.17f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        fe_panic();
    }
}

void Window::terminateGLFW() {
    glfwTerminate();
}
