#ifndef MESH_H
#define MESH_H

#include <string>
#include "VAO.h"
#include "EBO.h"
#include "camera.h"
#include "texture.h"
#include "debug.h"

class Mesh {
public:
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    VAO vao;

    Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures);
    ~Mesh();

    void draw
    (
        Shader &shader,
        Camera &camera,
        glm::mat4 matrix = glm::mat4(1.0f),
        glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f),
        glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f)
    );
};

#endif
