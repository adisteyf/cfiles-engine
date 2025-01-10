#ifndef DEBUG_FE_H
#define DEBUG_FE_H

#include <iostream>
#include <glad/glad.h>

void            fe_debug();
void GLAPIENTRY debugCallback
(
    GLenum           source,
    GLenum           type,
    GLuint           id,
    GLenum           severity,
    GLsizei          length,
    const   GLchar * message,
    const   void   * userParam
);
#endif
