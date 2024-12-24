#include "EBO.h"

EBO::EBO(std::vector<GLuint> &indices)
{
    glGenBuffers(1, &EBObuff);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBObuff);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
}

EBO::~EBO()
{
    free();
}


void EBO::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBObuff);
}

void EBO::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void EBO::free()
{
    glDeleteBuffers(1, &EBObuff);
}