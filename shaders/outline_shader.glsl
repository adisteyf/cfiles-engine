// vertex shader
#version 330 core

layout (location = 0) in vec3 aPos;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;
uniform float outlining;

void main()
{
    vec3 currPos = vec3(model*translation*rotation*scale*outlining * vec4(aPos, 1.0));
    gl_Position = camMatrix * vec4(currPos, 1.0);
}

// fragment shader
#version 330 core

out vec4 FragColor;

void main()
{
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
