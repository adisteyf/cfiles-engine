#include <iostream>
#include <glad/glad.h>
#include <GL/gl.h>
#include <GL/glu.h>

void fe_debug()
{
    GLenum code;
    const GLubyte* string;
    code = glGetError();
    if (code != GL_NO_ERROR) {
        string = gluErrorString(code);
        fprintf(stderr, "OpenGL error: %s (%d)\n", string, code);
    }
}
