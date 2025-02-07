#include "VBO.h"

VBO::VBO(std::vector<Vertex> &vertices)
{
    glGenBuffers(1, &VBObuff);
    glBindBuffer(GL_ARRAY_BUFFER, VBObuff);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
}

VBO::VBO()
{
    glGenBuffers(1, &VBObuff);
    glBindBuffer(GL_ARRAY_BUFFER, VBObuff);
}

void VBO::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, VBObuff);
}

void VBO::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::free()
{
    glDeleteBuffers(1, &VBObuff);
}
