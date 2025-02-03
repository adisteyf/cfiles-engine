#include "shader.h"

char* Shader::readFile(const char* filename) {
    std::ifstream file(filename, std::ios::binary | std::ios::ate);
    if (!file) {
        felogerr("Unable to open file: " << filename);
        fe_panic();
    }

    std::streamsize size = file.tellg();
    std::vector<char> buffer(size + 1);
    
    file.seekg(0);
    file.read(buffer.data(), size);
    buffer[size] = 0;
    
    return strdup(buffer.data());
}

void Shader::splitShader(const char* shaderSource, char** vertexShader, char** fragmentShader)
{
    const char* vertexPos = strstr(shaderSource, VERTEX_MARKER);
    const char* fragmentPos = strstr(shaderSource, FRAGMENT_MARKER);

    if (vertexPos == nullptr || fragmentPos == nullptr) {
        felogerr("Unable to find marker(s)");
        fe_panic();
    }

    size_t vertexLength = fragmentPos - vertexPos - VERTEX_MARKER_LEN;
    *vertexShader = new char[vertexLength + 1];
    strncpy(*vertexShader, vertexPos + VERTEX_MARKER_LEN, vertexLength);
    (*vertexShader)[vertexLength] = 0;

    size_t fragmentLength = strlen(fragmentPos + FRAGMENT_MARKER_LEN);
    *fragmentShader = new char[fragmentLength + 1];
    strncpy(*fragmentShader, fragmentPos + FRAGMENT_MARKER_LEN, fragmentLength);
    (*fragmentShader)[fragmentLength] = 0;

    // deleting space after marker comment
    std::string vertexNew(*vertexShader);
    vertexNew.erase(0,1);
    delete[] *vertexShader;
    *vertexShader = strdup(vertexNew.c_str());
}

void Shader::compileShader(GLuint shader, const char* code, const char* shaderType) {
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if (status != GL_TRUE) {
        GLint logSize;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logSize);
        std::vector<GLchar> infolog(logSize);
        glGetShaderInfoLog(shader, logSize, nullptr, infolog.data());
        
        std::string errorMsg = "Failed to compile ";
        errorMsg += shaderType;
        errorMsg += " shader:\n";
        errorMsg += infolog.data();
        felogftl(errorMsg);
        felogftl("Shader code:\n" << code);
        fe_panic();
    }
}

Shader::Shader(const char *filename) {
    const char *shader_str = readFile(filename);
    char *vertexCode = nullptr;
    char *fragmentCode = nullptr;

    splitShader(shader_str, &vertexCode, &fragmentCode);

    program = glCreateProgram();
    vs = glCreateShader(GL_VERTEX_SHADER);
    fs = glCreateShader(GL_FRAGMENT_SHADER);

    compileShader(vs, vertexCode, "vertex");
    compileShader(fs, fragmentCode, "fragment");

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glBindAttribLocation(program, 0, "vertices");
    glBindAttribLocation(program, 1, "textures");

    glLinkProgram(program);
    glValidateProgram(program);

    delete[] vertexCode;
    delete[] fragmentCode;
    delete[] shader_str;
}

/*Shader::~Shader() {
    killShader();
    freeShader();
}*/

void Shader::bind() {
    glUseProgram(program);
}

void Shader::setUniform(const char *name, int val)
{
    int location = glGetUniformLocation(program, name);
    if (location != -1) glUniform1i(location, val);
}

void Shader::setUniform(const char *name, glm::mat4 val)
{
    int location = glGetUniformLocation(program, name);
    if (location != -1) glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(val));
}

void Shader::killShader()
{
    glDeleteProgram(program);
    freeShader();
}

void Shader::freeShader()
{
    glDeleteShader(vs);
    glDeleteShader(fs);
}

GLuint Shader::getProgram()
{
    return program;
}

