#ifndef FE_TEST_APP_
#define FE_TEST_APP_

#include "FBO.h"
#include "camera.h"
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
    void input_callback(Window * window, Camera &cam);

private:
    Input  * input;
    Shader * shader;
    Shader * outlineShader;
    Shader * txtShader;
    TextRenderer * txtRenderer;
    Window * window;
    Camera * camera;
    bool     firstClick;
};

#endif // FE_TEST_APP_
