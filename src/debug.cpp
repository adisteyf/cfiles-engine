#include <iostream>
#include <glad/glad.h>

void fe_debug()
{
    GLenum err;
    while((err = glGetError()) != GL_NO_ERROR)
    {
        std::cout << "GL ERROR: ";
        std::cout << err << std::endl;
    }
}
