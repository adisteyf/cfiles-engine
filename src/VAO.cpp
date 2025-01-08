#include "VAO.h"
#include <iostream>

VAO::VAO()
{
    glGenVertexArrays(1, &VAObuff);
}

void VAO::makeAttrib(VBO& VBO, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset)
{
    VBO.bind();
    glEnableVertexAttribArray(layout);
    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
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
    std::cout << "VAO was freed" << std::endl;
}
