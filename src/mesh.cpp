#include "mesh.h"

Mesh::Mesh(std::vector<Vertex> &vertices, std::vector<GLuint> &indices, std::vector<Texture> &textures)
{
    Mesh::vertices = vertices;
    Mesh::indices = indices;
    Mesh::textures = textures;

    vao.bind();

    VBO vbo(vertices);
    EBO ebo(indices);

    vao.makeAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    vao.makeAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    vao.makeAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    vao.makeAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
    
    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}

void Mesh::draw
(
    Shader &shader,
    Camera &camera,
    glm::mat4 matrix,
    glm::vec3 translation,
    glm::quat rotation,
    glm::vec3 scale
)

{
    shader.bind();
    vao.bind();

    unsigned int numDiffuse = 0;
    unsigned int numSpecular = 0;

    for (unsigned int i = 0; i < textures.size(); i++)
    {
        std::string number;
        std::string type = textures[i].type;

        if (type == "diffuse")
        {
            number = std::to_string(numDiffuse++);
        }
        else if (type == "specular")
        {
            number = std::to_string(numSpecular++);
        }

		textures[i].texUnit(shader, (type + number).c_str(), i);
		textures[i].bind();
    }

    glUniform3f(glGetUniformLocation(shader.getProgram(), "camPos"), camera.pos.x, camera.pos.y, camera.pos.z);
    camera.matrix(shader, "camMatrix");

    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);

    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "translation"), 1, GL_FALSE, glm::value_ptr(trans));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "rotation"), 1, GL_FALSE, glm::value_ptr(rot));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "scale"), 1, GL_FALSE, glm::value_ptr(sca));
    glUniformMatrix4fv(glGetUniformLocation(shader.getProgram(), "model"), 1, GL_FALSE, glm::value_ptr(matrix));

    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}

Mesh::~Mesh()
{
    vao.free();
}
