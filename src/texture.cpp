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

    Texture::loadTexture(data, texType, slot);
    stbi_image_free(data);
}

void Texture::loadTexture(unsigned char *data, const char* texType, GLuint slot) {
    type = texType ? texType : "diffuse";
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &id);
    glActiveTexture(GL_TEXTURE0 + slot);
    unit = slot;
    glBindTexture(GL_TEXTURE_2D, id);

    FE_GL_TEXTURE_PARAMS

    switch (nrChannels) {
        case 4: {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            break;
        }

        case 3: {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            break;
        }

        case 1: {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
            break;
        }

        default: {
            std::cerr << "Invalid type of texture" << std::endl;
            fe_panic();
        }
    }

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::texUnit(Shader& shader, const char *uniform, GLuint unit) {
    shader.bind();
    shader.setUniform(uniform, (int)unit);
}

void Texture::bind() {
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, id);
}

