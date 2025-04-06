#ifndef SHADER_CLASS_FE
#define SHADER_CLASS_FE

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>
#include <vector>
#include <fstream>
#include "fe-kernel.h"  // for panic
#include "fe-settings.h" // for log

#define VERTEX_MARKER "// vertex shader"
#define FRAGMENT_MARKER "// fragment shader"
#define VERTEX_MARKER_LEN 16
#define FRAGMENT_MARKER_LEN 18

class Shader
{
    private:
        GLuint program,vs,fs;
        void splitShader(const char* shaderSource, char** vertexShader, char** fragmentShader);

    public:
        char* readFile(const char* filename);
        void compileShader(GLuint shader, const char* code, const char* shaderType);
        Shader(const char* filename);
        ~Shader();
        void bind();
        void setUniform(const char *name, int val);
        void setUniform(const char *name, unsigned int val);
        void setUniform(const char *name, float val);
        void setUniform(const char *name, glm::mat4 val);
        void setUniform(const char *name, glm::vec4 val);
        void setUniform(const char *name, glm::vec3 val);
        void freeShader();
        GLuint getProgram();
};

#endif // SHADER_CLASS_FE
