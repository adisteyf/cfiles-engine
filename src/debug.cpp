#include <iostream>
#include <glad/glad.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "debug.h"

int countCall = 0;
void fe_debug()
{
    GLenum code;
    const GLubyte* string;
    code = glGetError();
    if (code != GL_NO_ERROR) {
        string = gluErrorString(code);
        fprintf(stderr, "OpenGL error: %s (%d)\n", string, code);
    }
}


const char* getSourceString(GLenum source)
{
    switch (source) {
        case GL_DEBUG_SOURCE_API: return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM: return "Window System";
        case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader Compiler";
        case GL_DEBUG_SOURCE_THIRD_PARTY: return "Third Party";
        case GL_DEBUG_SOURCE_APPLICATION: return "Application";
        case GL_DEBUG_SOURCE_OTHER: return "Other";
        default: return "Unknown";
    }
}

const char* getTypeString(GLenum type)
{
    switch (type) {
        case GL_DEBUG_TYPE_ERROR: return "Error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "Deprecated Behavior";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: return "Undefined Behavior";
        case GL_DEBUG_TYPE_PORTABILITY: return "Portability";
        case GL_DEBUG_TYPE_PERFORMANCE: return "Performance";
        case GL_DEBUG_TYPE_MARKER: return "Marker";
        case GL_DEBUG_TYPE_PUSH_GROUP: return "Push Group";
        case GL_DEBUG_TYPE_POP_GROUP: return "Pop Group";
        case GL_DEBUG_TYPE_OTHER: return "Other";
        default: return "Unknown";
    }
}

const char* getSeverityString(GLenum severity)
{
    switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH: return "High";
        case GL_DEBUG_SEVERITY_MEDIUM: return "Medium";
        case GL_DEBUG_SEVERITY_LOW: return "Low";
        case GL_DEBUG_SEVERITY_NOTIFICATION: return "Notification";
        default: return "Unknown";
    }
}

void gl1282debugBlock() {
    printf("DEBUG: gl1282debugBlock was called\n");
}

void GLAPIENTRY debugCallback
(
    GLenum           source,
    GLenum           type,
    GLuint           id,
    GLenum           severity,
    GLsizei          length,
    const   GLchar * message,
    const   void   * userParam
)

{
    //__debug_break(); for VS Code
    puts("DEBUG:");
    printf("\tsrc: %u\n", source);
    printf("\ttype: %u\n", type);
    printf("\tID: %d\n", id);
    printf("\tseverity: %u\n", severity);
    printf("\tlen: %d\n", length);
    printf("\tmsg: %s\n", message);

    
    printf("\tsrc: %s\n", getSourceString(source));
    printf("\ttype: %s\n", getTypeString(type));
    printf("\tID: %s\n", gluErrorString(id));
    printf("\tseverity: %s\n", getSeverityString(severity));
    printf("\tlen: %d\n", length);
    printf("\tmsg: %s\n", message);

    if (1282 == id) {
        gl1282debugBlock();
    }

    putchar('\n');
    if (countCall==2) {
        not1stCall();
    }
    countCall++;
}

void not1stCall() {
    puts("not 1st call");
}
