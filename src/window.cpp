#include "window.h"
#include "fe-settings.h"
#include "fe-includes.h"
#include "main.h"

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
    glClear(FE_CLEARFLAGS);
}

void Window::clearBlack() {
    glClearColor(0.f,0.f,0.f,1.f);
    glClear(FE_CLEARFLAGS);
}

void Window::initGLFW() {
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        fe_panic();
    }
}

FE_SCRIPTS_EXTERN
#ifdef FE_ASPECT_RATIO
float aspect_ratio = 0;
#endif
void windowResizeCallback(GLFWwindow* window, int width, int height) {
#   ifdef FE_ENABLE_FBOPICKING
    extern FBO * fboPicking;
    delete fboPicking;
    fboPicking = new FBO(width,height);
#   endif
    FE_WINRESIZE_SCRIPTS
#ifdef FE_ASPECT_RATIO
    float currentAspectRatio = (float)width / (float)height;

    if (currentAspectRatio > aspect_ratio) {
        int viewportWidth = (int)(height * aspect_ratio);
        int viewportX = (width - viewportWidth) / 2;
        glViewport(viewportX, 0, viewportWidth, height);
    } else {
        int viewportHeight = (int)(width / aspect_ratio);
        int viewportY = (height - viewportHeight) / 2;
        glViewport(0, viewportY, width, viewportHeight);
    }

    Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
    if (camera) {
        camera->w = width;
        camera->h = height;
        camera->updateMatrix();
    }
#endif
}

void fe_GLContext(void)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, FE_GLFW_MAJOR);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, FE_GLFW_MINOR);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, 1);
    glfwWindowHint(GLFW_STENCIL_BITS, 8);
}

#ifdef FE_ASPECT_RATIO
void windowGetAspectRatio() {
    GLFWmonitor * primaryMonitor = glfwGetPrimaryMonitor();
    const GLFWvidmode * mmode = glfwGetVideoMode(primaryMonitor);
    aspect_ratio = (float)mmode->width / (float)mmode->height;
    printf("VIDM:\n%d\n%d\n%f\n", mmode->width, mmode->height, aspect_ratio);
}
#endif

bool Window::windowGetKey(int key, int state) {
    return glfwGetKey(window, key) == state;
}

bool Window::windowGetMouseButton(int key, int state) {
    return glfwGetMouseButton(window, key) == state;
}

void Window::hideCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}

void Window::normalCursor() {
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void Window::setCursorPos(double x, double y) {
    glfwSetCursorPos(window, x, y);
}

void Window::getCursorPos(double *x, double *y) {
    glfwGetCursorPos(window, x, y);
}
