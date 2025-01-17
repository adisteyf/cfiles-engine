#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shader.h"
#include <string>

class Texture {

public:
    GLuint id;
    const char* type;
    int width, height, nrChannels;
    GLuint unit;

    Texture(unsigned char *data, const char* texType, GLuint slot);
    Texture(const char *path, const char* texType, GLuint slot);

    unsigned char* getData(const char *path);
    void texUnit(Shader& shader, const char *uniform, GLuint unit);
    void bind();
    void unbind();
    void remove();

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif
