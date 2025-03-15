#ifndef WINDOW_CLASS_FE
#define WINDOW_CLASS_FE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "fe-kernel.h"

class Window {
private:
    GLFWwindow* window;
    int width;
    int height;
    const char* title;

public:
    Window(int w, int h, const char* t);
    //~Window();

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

#endif // WINDOW_CLASS_FE
