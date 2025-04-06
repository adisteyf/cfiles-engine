#ifndef FBO_H
#define FBO_H

#include "shader.h"
#include <glad/glad.h>
#include <glm/glm.hpp>

class FBO {
public:
    GLuint FBObuff, pickingTextureID;
    int width, height;
    
    FBO(int width, int height);
    void free();
    void bind();
    void unbind();
    uint getModelID(int x, int y);
    void setModelID(Shader& fboShader, uint objectID);
};
#endif // FBO_H
