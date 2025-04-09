#include "FBO.h"
#include "fe-settings.h"
#include "glm/glm.hpp"
#include <glm/fwd.hpp>

FBO::FBO(int w, int h) : width(w), height(h) {
    glGenFramebuffers(1, &FBObuff);
    glBindFramebuffer(GL_FRAMEBUFFER, FBObuff);

    glGenTextures(1, &pickingTextureID);
    glBindTexture(GL_TEXTURE_2D, pickingTextureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32UI, width, height, 0, GL_RGB_INTEGER, GL_UNSIGNED_INT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pickingTextureID, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
        felogerr("Can't build FBO");
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
};

uint FBO::getModelID(int x, int y)
{
    y = height - y - 1;
    glm::uvec3 pixelData;
    glBindFramebuffer(GL_FRAMEBUFFER, FBObuff);
    glReadPixels(x,y,1,1,GL_RGB_INTEGER,GL_UNSIGNED_INT,&pixelData);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    uint res = ((uint)pixelData.r << 16) | ((uint)pixelData.g << 8) | ((uint)pixelData.b);
    return res;
}

void FBO::setModelID(Shader& fboShader, uint objectID)
{
    uint r = (objectID >> 16) & 0xFFu;
    uint g = (objectID >> 8) & 0xFFu;
    uint b = objectID & 0xFFu;

    fboShader.setUniform("objectR", r);
    fboShader.setUniform("objectG", g);
    fboShader.setUniform("objectB", b);
}

void FBO::free()
{
    glDeleteTextures(1, &pickingTextureID);
    glDeleteFramebuffers(1, &FBObuff);
}

void FBO::bind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBObuff);
}

void FBO::unbind()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
