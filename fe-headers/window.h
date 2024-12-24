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
    ~Window();
    
    bool shouldClose();
    void swapBuffers();
    void pollEvents();
    GLFWwindow* getWindow() { return window; }
    
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    
    void clear();
    static void initGLFW();
    static void terminateGLFW();
};

#endif // WINDOW_CLASS_FE
