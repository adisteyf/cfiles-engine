#include "texture.h"

Texture::Texture(const char *path, const char* texType, GLuint slot) {
    type = texType ? texType : "diffuse";

    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);
    if (!data) {
        std::cerr << "Failed to load texture: " << path << std::endl;
        std::cerr << "STB Error: " << stbi_failure_reason() << std::endl;
        return;
    }
    std::cout << "Texture loaded successfully: " << path << std::endl;
    std::cout << "Width: " << width << ", Height: " << height << ", Channels: " << nrChannels << std::endl;

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (nrChannels == 4)
    {
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                width,
                height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                data
        );
    }

    else if (nrChannels == 3)
    {
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
        );
    }

    else if (nrChannels == 1)
    {
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                width,
                height,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                data
        );
    }
    else
    {
        std::cerr << "Invalid type of texture" << std::endl;
        fe_panic();
    }

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}


Texture::Texture(unsigned char *data, const char* texType, GLuint slot) {
    type = texType ? texType : "diffuse";

    stbi_set_flip_vertically_on_load(true);
    //unsigned char* data = stbi_load(path, &width, &height, &nrChannels, 0);

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    glBindTexture(GL_TEXTURE_2D, id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if (nrChannels == 4)
    {
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                width,
                height,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                data
        );
    }

    else if (nrChannels == 3)
    {
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                width,
                height,
                0,
                GL_RGB,
                GL_UNSIGNED_BYTE,
                data
        );
    }

    else if (nrChannels == 1)
    {
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                width,
                height,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                data
        );
    }
    else
    {
        std::cerr << "Invalid type of texture" << std::endl;
        fe_panic();
    }
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char *uniform, GLuint unit) {
    GLuint tex0Uni = glGetUniformLocation(shader.getProgram(), uniform);
    shader.bind();
    glUniform1i(tex0Uni, unit);
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::remove() {
    glDeleteTextures(1, &id);
}

Texture::~Texture() {
    remove();
}
