// vertex shader
#version 330 core

layout(location = 0) in vec3 aPos;

uniform mat4 model;
uniform mat4 camMatrix;

void main() {
    gl_Position = camMatrix * model * vec4(aPos, 1.0);
}

// fragment shader
#version 330 core

out vec4 FragColor;
uniform vec4 lightColor;

void main() {
    FragColor = lightColor;
}
