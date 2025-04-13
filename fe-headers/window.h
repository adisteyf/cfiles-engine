#ifndef WINDOW_CLASS_FE
#define WINDOW_CLASS_FE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "fe-kernel.h"

#define WINDOW_SETRESIZECB \
    glfwSetWindowSizeCallback(window->getWindow(), windowResizeCallback);

class Window {
private:
    GLFWwindow* window;
    int width;
    int height;
    const char* title;

public:
    Window(int w, int h, const char* t);

    bool shouldClose() const { return glfwWindowShouldClose(window); }
    void swapBuffers() { glfwSwapBuffers(window); }
    void pollEvents() { glfwPollEvents(); }
    GLFWwindow* getWindow() { return window; }
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void clear();
    static void initGLFW();
    static void terminateGLFW() { glfwTerminate(); }
    void killWindow();
};

void windowResizeCallback(GLFWwindow* window, int width, int height);
void fe_GLContext(void);
void windowGetAspectRatio();

#endif // WINDOW_CLASS_FE
