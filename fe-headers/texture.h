#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stb/stb_image.h>
#include "shader.h"
#include <string>

#define FE_GL_TEXTURE_PARAMS glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR); \
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); \
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); \
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


class Texture {

public:
    GLuint id;
    const char* type;
    int width, height, nrChannels;
    GLuint unit;

    void loadTexture(unsigned char *data, const char* texType, GLuint slot);
    Texture(const char *path, const char* texType, GLuint slot);

    unsigned char* getData(const char *path);
    void texUnit(Shader& shader, const char *uniform, GLuint unit);
    void bind();
    void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }
    void remove() { glDeleteTextures(1, &id); }

    int getWidth() const { return width; }
    int getHeight() const { return height; }
};

#endif
