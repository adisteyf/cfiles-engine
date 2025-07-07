#include "model.h"
#include "camera.h"
#include "fe-kernel.h"
#include "fe-settings.h"
#include "main.h"
#include <cstdio>
#include <glm/ext/quaternion_common.hpp>
#include <glm/fwd.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ostream>
#include <string>
#include <vector>
#include <algorithm>


std::vector<uint64_t> ids;


Model::Model(const char * file)
{
    std::string text = get_file_contents(file);
    JSON = json::parse(text);

    Model::file = file;
    data = getData();

    felog("Model generator:");
    felog(JSON["asset"]["generator"]);
    if (JSON["asset"]["generator"] != "Khronos glTF Blender I/O v4.4.56") {
        Model::reverseRot = false;
    }

    for (uint i=0; i<JSON["scenes"][0]["nodes"].size(); ++i) {
        traverseNode(JSON["scenes"][0]["nodes"][i]);
    }

    /* generate id */
    uint32_t i=0;
    if (!ids.empty()) {
        while (std::find(ids.begin(), ids.end(), i) != ids.end()) { ++i; }
    }

    ids.push_back(i);
    id = i;
}

Model::~Model() {
    /* if program is about to terminate */
    if (!ids.empty()) {
        for (int32_t i=0; i<ids.size(); ++i) {
            if (ids[i] == id) {
                ids.erase(ids.begin()+i);
                break;
            }
        }
    }
}

void Model::changePos(glm::vec3 newPos)
{
    for (unsigned int i=0; i<matricesMeshes.size(); ++i) {
        matricesMeshes[i] = glm::translate(matricesMeshes[i], position-newPos);
    }

    for (unsigned int i=0; i<meshes.size(); ++i) {
        meshes[i].updateVBO();
    }
    position = newPos;
} // TODO: доделать

void Model::draw(Shader &shader, Camera &camera, glm::vec4 globalColor)
{
    shader.setUniform("worldPos", pos);
    for (unsigned int i=0; i<meshes.size(); i++) {
        meshes[i].Mesh::draw(shader, camera, shType, globalColor, matricesMeshes[i]);
    }
}

void Model::drawMesh(Shader &shader, Camera &camera, uint index) /* TODO: add globalColor arg */
{
    meshes[index].Mesh::draw(shader, camera, shType, glm::vec4(0.f,0.f,0.f,0.f), matricesMeshes[index]);
}

void Model::draw(Shader &shader, float dcolor[4])
{
    Camera * camera = fe_getMainCamera();

		glm::vec4 dcolorvec4(dcolor[0], dcolor[1], dcolor[2], dcolor[3]);
    Model::draw(shader, *camera, (dcolor[3] == 0.f) ? glm::vec4(0.f,0.f,0.f,0.f) : dcolorvec4);
}

std::string Model::get_file_contents(const char* filename)
{
    std::cout << "reading file: \"" << filename << "\"" << std::endl;
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}

void Model::loadMesh(unsigned int indMesh)
{
    unsigned int posAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["POSITION"];
    unsigned int normalAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["NORMAL"];
    unsigned int texAccInd = JSON["meshes"][indMesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
    unsigned int indAccInd = JSON["meshes"][indMesh]["primitives"][0]["indices"];

    std::vector<float> posVec = getFloats(JSON["accessors"][posAccInd]);
    std::vector<glm::vec3> positions = groupFloatsVec3(posVec);
    std::vector<float> normalVec = getFloats(JSON["accessors"][normalAccInd]);
    std::vector<glm::vec3> normals = groupFloatsVec3(normalVec);
    std::vector<float> texVec = getFloats(JSON["accessors"][texAccInd]);
    std::vector<glm::vec2> texUVs = groupFloatsVec2(texVec);

    std::vector<Vertex> vertices = assembleVertices(positions, normals, texUVs);
    std::vector<GLuint> indices = getIndices(JSON["accessors"][indAccInd]);
    std::vector<Texture> textures = getTextures();

    int matInd = JSON["meshes"][indMesh]["primitives"][0]["material"];
    auto pbrMetR = JSON["materials"][matInd]["pbrMetallicRoughness"];
    if (pbrMetR.contains("baseColorFactor") && (textures.empty() || strcmp(textures[0].type, "diffuseerr")==0)) {
        float color[4] = {
            pbrMetR["baseColorFactor"][0],
            pbrMetR["baseColorFactor"][1],
            pbrMetR["baseColorFactor"][2],
            pbrMetR["baseColorFactor"][3],
        };

        textures[0].type = "diffuse";
        glm::vec4 colorVec = glm::make_vec4(color);
        printf("COLORS: %f %f %f %f\n", colorVec.r, colorVec.g, colorVec.b, colorVec.a);
        meshes.push_back(Mesh(vertices, indices, textures, colorVec));
        return;
    }

    meshes.push_back(Mesh(vertices, indices, textures, glm::vec4(0.f,0.f,0.f,0.f)));
}

void Model::traverseNode(unsigned int nextNode, glm::mat4 matrix)
{
    json node = JSON["nodes"][nextNode];

    glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
    if (node.find("translation") != node.end()) {
        float transValues[3];
        for (unsigned int i=0; i<node["translation"].size(); i++)
            transValues[i] = node["translation"][i];
        translation = glm::make_vec3(transValues);
    }

    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    if (node.find("rotation") != node.end()) {
      float rotValues[4];
        if (!reverseRot) {
            rotValues[0] = node["rotation"][3];
            rotValues[1] = node["rotation"][0];
            rotValues[2] = node["rotation"][1];
            rotValues[3] = node["rotation"][2];
        } else {
            rotValues[0] = node["rotation"][0];
            rotValues[1] = node["rotation"][1];
            rotValues[2] = node["rotation"][2];
            rotValues[3] = node["rotation"][3];
        }

        rotation = glm::make_quat(rotValues);
    }

    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    if (node.find("scale") != node.end())
    {
        float scaleValues[3];
        for (unsigned int i=0; i<node["scale"].size(); i++)
            scaleValues[i] = node["scale"][i];
        scale = glm::make_vec3(scaleValues);
    }

    glm::mat4 matNode = glm::mat4(1.0f);
    if (node.find("matrix") != node.end())
    {
        float matValues[16];
        for (unsigned int i=0; i<node["matrix"].size(); i++)
            matValues[i] = node["matrix"][i];
        matNode = glm::make_mat4(matValues);
    }

    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);

    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);

    glm::mat4 matNextNode;
    if (!reverseRot) {
        matNextNode = matrix * matNode * trans * -rot * sca;
    } else {
        matNextNode = matrix * matNode * trans * rot * sca;
    }

    if (node.find("mesh") != node.end()) {
        translationMeshes.push_back(translation);
        rotationsMeshes.push_back(rotation);
        scalesMeshes.push_back(scale);
        matricesMeshes.push_back(matNextNode);

        loadMesh(node["mesh"]);
    }

    if (node.find("children") != node.end()) {
        for (unsigned int i=0; i<node["children"].size(); i++) {
            traverseNode(node["children"][i], matNextNode);
        }
    }
}

std::vector<unsigned char> Model::getData()
{
    std::string bytesText;
    std::cout << "Next is URI get" << std::endl; 
    std::string uri = JSON["buffers"][0]["uri"];

    std::cout << "Next is file to string" << std::endl;
    std::string fileStr = std::string(file);
    std::string fileDir = fileStr.substr(0, fileStr.find_last_of('/')+1);
    bytesText = get_file_contents((fileDir+uri).c_str());

    std::vector<unsigned char> data(bytesText.begin(), bytesText.end());
    return data;
}

std::vector<float> Model::getFloats(json accessor)
{
    std::vector<float> floatVec;

    unsigned int buffViewInd = accessor.value("bufferView", 1);
    unsigned int count = accessor["count"];
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    std::string type = accessor["type"];

    json bufferView = JSON["bufferViews"][buffViewInd];
    unsigned int byteOffset = bufferView["byteOffset"];

    unsigned int numPerVert=0;
    if (type == "SCALAR") numPerVert = 1;
    else if (type == "VEC2") numPerVert = 2;
    else if (type == "VEC3") numPerVert = 3;
    else if (type == "VEC4") numPerVert = 4;
    else
    {
        std::cerr << "Invalid type (model.cpp)" << std::endl;
        fe_panic();
    }

    unsigned int beginningOfData = byteOffset+accByteOffset;
    unsigned int lengthOfData = count * 4 * numPerVert;
    for (unsigned int i = beginningOfData; i < beginningOfData+lengthOfData; i += 4)
    {
        unsigned char bytes[] = { data[i], data[i+1], data[i+2], data[i+3] };
        float value;
        std::memcpy(&value, bytes, sizeof(float));
        floatVec.push_back(value);
    }
    
    return floatVec;
}

std::vector<GLuint> Model::getIndices(json accessor)
{
    std::vector<GLuint> indices;

    unsigned int buffViewInd = accessor.value("bufferView", 0);
    unsigned int count = accessor["count"];
    unsigned int accByteOffset = accessor.value("byteOffset", 0);
    unsigned int componentType = accessor["componentType"];

    json bufferView = JSON["bufferViews"][buffViewInd];
    unsigned int byteOffset = bufferView["byteOffset"];

    unsigned int beginningOfData = byteOffset + accByteOffset;

    if (componentType == 5125)
    {
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 4; i += 4)
        {
            unsigned char bytes[] = { data[i], data[i+1], data[i+2], data[i+3] };
            unsigned int value;
            std::memcpy(&value, bytes, sizeof(unsigned int));
            indices.push_back((GLuint)value);
        }
    }

    else if (componentType == 5123)
    {
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i += 2)
        {
            unsigned char bytes[] = { data[i], data[i+1] };
            unsigned short value;
            std::memcpy(&value, bytes, sizeof(unsigned short));
            indices.push_back((GLuint)value);
        }
    }

    else if (componentType == 5122)
    {
        for (unsigned int i = beginningOfData; i < byteOffset + accByteOffset + count * 2; i += 2)
        {
            unsigned char bytes[] = { data[i], data[i+1] };
            short value;
            std::memcpy(&value, bytes, sizeof(short));
            indices.push_back((GLuint)value);
        }
    }

    return indices;
}

std::vector<Texture> Model::getTextures()
{
    std::vector<Texture> textures;
    if (!JSON.contains("images")) {
        Texture diffuse = Texture("assets/textures/deadtex.png", "diffuseerr", loadedTex.size());
        textures.push_back(diffuse);
        loadedTex.push_back(diffuse);
        loadedTexName.push_back("assets/textures/deadtex.png");
        return textures;
    }

    std::string fileStr = std::string(file);
    std::string fileDir = fileStr.substr(0, fileStr.find_last_of('/')+1);

    for (unsigned int i=0; i<JSON["images"].size(); i++)
    {
        std::string texPath = JSON["images"][i]["uri"];

        bool skip = false;
        for (unsigned int j = 0; j < loadedTexName.size(); j++)
        {
            if (loadedTexName[j] == texPath)
            {
                textures.push_back(loadedTex[j]);
                skip=true;
                break;
            }
        }

        if (!skip)
        {
            if (texPath.find("baseColor") != std::string::npos) {
                Texture diffuse = Texture((fileDir+texPath).c_str(), "diffuse", loadedTex.size());
                textures.push_back(diffuse);
                loadedTex.push_back(diffuse);
                loadedTexName.push_back(texPath);
            } else if (texPath.find("metallicRoughness") != std::string::npos) {
                Texture specular = Texture((fileDir+texPath).c_str(), "specular", loadedTex.size());
                textures.push_back(specular);
                loadedTex.push_back(specular);
                loadedTexName.push_back(texPath);
            }
        }
    }

    return textures;
}

std::vector<Vertex> Model::assembleVertices
(
    std::vector<glm::vec3> positions,
    std::vector<glm::vec3> normals,
    std::vector<glm::vec2> texUVs
)
{
    std::vector<Vertex> vertices;
    for (size_t i=0; i<positions.size(); i++)
    {
        vertices.push_back
        (
            Vertex
            {
                positions[i],
                normals[i],
                glm::vec3(1.0f, 1.0f, 1.0f),
                texUVs[i]
            }
        );
    }

    return vertices;
}



std::vector<glm::vec2> Model::groupFloatsVec2(std::vector<float> floatVec)
{
	const unsigned int floatsPerVector = 2;
	
	std::vector<glm::vec2> vectors;
	for (unsigned int i=0; i<floatVec.size(); i += floatsPerVector)
	{
		vectors.push_back(glm::vec2(0, 0));

		for (unsigned int j=0; j<floatsPerVector; j++)
		{
			vectors.back()[j] = floatVec[i+j];
		}
	}
	return vectors;
}

std::vector<glm::vec3> Model::groupFloatsVec3(std::vector<float> floatVec)
{
	const unsigned int floatsPerVector = 3;

	std::vector<glm::vec3> vectors;
	for (unsigned int i = 0; i < floatVec.size(); i += floatsPerVector)
	{
		vectors.push_back(glm::vec3(0, 0, 0));

		for (unsigned int j = 0; j < floatsPerVector; j++)
		{
			vectors.back()[j] = floatVec[i + j];
		}
	}
	return vectors;
}

std::vector<glm::vec4> Model::groupFloatsVec4(std::vector<float> floatVec)
{
	const unsigned int floatsPerVector = 4;

	std::vector<glm::vec4> vectors;
	for (unsigned int i = 0; i < floatVec.size(); i += floatsPerVector)
	{
		vectors.push_back(glm::vec4(0, 0, 0, 0));

		for (unsigned int j = 0; j < floatsPerVector; j++)
		{
			vectors.back()[j] = floatVec[i + j];
		}
	}
	return vectors;
}

extern "C" {
  void deleteModelC(void * ptr) {
    Model * tmp = (Model *) ptr;
    printf("deleting model: %p\n", tmp);
    delete tmp;
  }

  void drawModelC(void * ptr, void * shptr) {
    Model  * mdl = (Model *)ptr;
    Shader * sdr = (Shader *)shptr;
    mdl->draw(*sdr, (float[]){0.f,0.f,0.f,0.f});
  }

  void drawModelOneColorC(void * ptr, void * shptr, float dcolor[4]) {
    Model  * mdl = (Model *)ptr;
    Shader * sdr = (Shader *)shptr;
    mdl->draw(*sdr, dcolor);
  }
}
