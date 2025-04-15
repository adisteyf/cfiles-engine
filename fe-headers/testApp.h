#include "FBO.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "input.h"
#include "textRenderer.h"
#include "window.h"
#include "shader.h"
#include "model.h"

class FeTestApp
{
public:
    FeTestApp(void);
    void cycle(void);
    void free(void);
    void winresize_callback(GLFWwindow* window, int width, int height);

private:
    Input  * input;
    Shader * shader;
    Shader * outlineShader;
    Shader * txtShader;
    TextRenderer * txtRenderer;
    Window * window;
    Camera * camera;
    FBO    * fbo;
    Shader * fboShader;
};
