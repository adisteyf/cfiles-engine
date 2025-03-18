#include "input.h"
#include "window.h"
#include "shader.h"
#include "model.h"

class FeTestApp
{
public:
    FeTestApp(void);
    void cycle(void);

private:
    Input  * input;
    Shader * shader;
    Shader * outlineShader;
    Window * window;
    Camera * camera;
    Model  * model;
};
