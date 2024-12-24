#ifndef EBO_H
#define EBO_H

#include <glad/glad.h>
#include <vector>
class EBO
{
public:
    GLuint EBObuff;

    EBO(std::vector<GLuint> &indices);
    ~EBO();
    void bind();
    void unbind();
    void free();
};

#endif