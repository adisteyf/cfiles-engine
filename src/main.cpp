#include "window.h"
#include "mesh.h"

Vertex vertices[] = {
    // Position            // Color              // UV           // Normal
	Vertex{glm::vec3(-1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3( 1.0f, 0.0f,  1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)}
};

GLuint indices[] = {
    0, 1, 2,
    0, 2, 3
};

Vertex lightVertices[] = {
    Vertex{glm::vec3(-0.1f, -0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f, -0.1f,  0.1f)},

    Vertex{glm::vec3(-0.1f,  0.1f,  0.1f)},
    Vertex{glm::vec3(-0.1f,  0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f,  0.1f, -0.1f)},
    Vertex{glm::vec3(0.1f,  0.1f,  0.1f)}
};

GLuint lightIndices[] = {
    0, 1, 2,
    0, 2, 3,
    0, 4, 7,
    0, 7, 3,
    3, 7, 6,
    3, 6, 2,
    2, 6, 5,
    2, 5, 1,
    1, 5, 4,
    1, 4, 0,
    4, 5, 6,
    4, 6, 7
};



int fe_main() {
    felog("fe_main(): initializing GLFW...");
    Window::initGLFW();
    felog("fe_main(): initializing window...");
    Window window(WINDOW_WIDTH, WINDOW_HEIGHT, "Files Engine");

    Texture textures[] = {
        Texture("assets/textures/wood.jpg", "diffuse", 0, GL_RGB, GL_UNSIGNED_BYTE),
        Texture("assets/textures/wood_ac.jpg", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
    };

    felog("fe_main(): initializing shader...");
    Shader shader("shaders/shader_def.glsl");
    felog("fe_main(): initializing model...");
    std::vector<Vertex> verts(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
    std::vector<GLuint> inds(indices, indices + sizeof(indices) / sizeof(GLuint));
    std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
    Mesh floor(verts, inds, tex);

    felog("fe_main(): initializing light shader...");
    Shader lightShader("shaders/light_shader.glsl");

    felog("fe_main(): initializing light buffers...");
    std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
    std::vector<GLuint> lightInds(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
    Mesh light(lightVerts, lightInds, tex);

    glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);

    felog("fe_main(): initializing light model...");
    glm::vec3 lightPos(1.0f, 1.0f, 1.0f);
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPos);
    lightModel = glm::scale(lightModel, glm::vec3(0.2f));

    felog("fe_main(): initializing pyramid model...");
    glm::vec3 pyramidPos = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::mat4 pyramidModel = glm::mat4(1.0f);
    pyramidModel = glm::translate(pyramidModel, pyramidPos);

    felog("fe_main(): binding light shader...");
    lightShader.bind();
    felog("fe_main(): setting light model...");
    lightShader.setUniform("model", lightModel);

    felog("fe_main(): setting light color...");
    glUniform4f(glGetUniformLocation(lightShader.getProgram(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

    felog("fe_main(): binding shader...");
    shader.bind();
    felog("fe_main(): setting pyramid model...");
    shader.setUniform("model", pyramidModel);

    glUniform4f(glGetUniformLocation(shader.getProgram(), "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
    glUniform3f(glGetUniformLocation(shader.getProgram(), "lightPos"), lightPos.x, lightPos.y, lightPos.z);

    felog("fe_main(): enabling depth test...");
    glEnable(GL_DEPTH_TEST);

    felog("fe_main(): initializing camera...");
    Camera camera(WINDOW_WIDTH, WINDOW_HEIGHT, glm::vec3(0.0f, 0.0f, 2.0f));

    felog("fe_main(): entering main loop...");
    while (!window.shouldClose() && !fe_status) {
        felog("fe_main(): polling events...");
        window.pollEvents();
        felog("fe_main(): clearing window...");
        window.clear();

        felog("fe_main(): updating camera...");
        camera.inputs(window.getWindow());
        camera.updateMatrix(45.0f, 0.1f, 100.0f);

        felog("fe_main(): drawing floor & light...");
        floor.draw(shader, camera);
        light.draw(lightShader, camera);

        felog("fe_main(): swapping buffers...");
        window.swapBuffers();
        felog("fe_main(): end of main loop");
    }

    felog("fe_main(): exiting main loop (end of fe_main)...");
    return 0;
}

