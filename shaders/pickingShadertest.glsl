// vertex shader
#version 330 core
layout (location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}

// fragment shader
#version 330 core

uniform uint objectID;
out vec4 fragColor;

void main() {
    uint r = (objectID >> 16) & 0xFFu;
    uint g = (objectID >> 8) & 0xFFu;
    uint b = objectID & 0xFFu;
    uint a = (objectID >> 24) & 0xFFu;

    fragColor = vec4(float(r) / 255.0, float(g) / 255.0, float(b) / 255.0, float(a) / 255.0);
}

