#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &VAObuff);
}

VAO::~VAO()
{
    free();
}

void VAO::makeAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
    VBO.bind();
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);
    VBO.unbind();
}

void VAO::bind()
{
    glBindVertexArray(VAObuff);
}

void VAO::unbind()
{
    glBindVertexArray(0);
}

void VAO::free()
{
    glDeleteVertexArrays(1, &VAObuff);
}