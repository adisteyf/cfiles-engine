#ifndef MODEL_H
#define MODEL_H

#include "mesh.h"
#include <glm/fwd.hpp>
#include <json/json.h>
#include <string>
#include "VBO.h"
#include "texture.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"
#include "fe-kernel.h" /* for fe_panic() */
#include <fstream>
#include <iostream>

using json = nlohmann::json;

class Model {
public:
    Model(const char * name);
    ~Model();
    void draw(Shader &shader, Camera &camera, glm::vec4 globalColor = glm::vec4(0.f,0.f,0.f,0.f));
    void draw(Shader &shader, float dcolor[4] = 0);
    void drawMesh(Shader &shader, Camera &camera, uint index);
    std::string get_file_contents(const char* filename);
    void changePos(glm::vec3 newPos);
    std::vector<Mesh> meshes;
    std::vector<glm::vec3> translationMeshes;
    uint64_t getId(void) { return id; }
    int shType = 1;          /* shader type */
    uint enablePicking = 0;  /* picking id  */

    glm::vec3 pos = glm::vec3(0,0,0);
private:
    uint64_t id;
    const char * file;
    std::vector<unsigned char> data;
    json JSON;
    bool reverseRot = true;

    glm::vec3 position = glm::vec3(0.f,0.f,0.f);
    std::vector<glm::quat> rotationsMeshes;
    std::vector<glm::vec3> scalesMeshes;
    std::vector<glm::mat4> matricesMeshes;

    std::vector<std::string> loadedTexName;
    std::vector<Texture> loadedTex;

    void loadMesh(unsigned int indMesh);
    void traverseNode(unsigned int nextNode, glm::mat4 matrix = glm::mat4(1.0f));

    std::vector<unsigned char> getData();
    std::vector<float> getFloats(json accessor);
    std::vector<GLuint> getIndices(json accessor);
    std::vector<Texture> getTextures();

    std::vector<Vertex> assembleVertices
    (
        std::vector<glm::vec3> positions,
        std::vector<glm::vec3> normals,
        std::vector<glm::vec2> texUVs
    );

    std::vector<glm::vec2> groupFloatsVec2(std::vector<float> floatVec);
    std::vector<glm::vec3> groupFloatsVec3(std::vector<float> floatVec);
    std::vector<glm::vec4> groupFloatsVec4(std::vector<float> floatVec);
};

#endif
