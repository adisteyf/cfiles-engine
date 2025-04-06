// vertex shader
#version 330 core

layout (location=0) in vec3 aPos;
layout (location=1) in vec3 aNormal;
layout (location=2) in vec3 aColor;
layout (location=3) in vec2 aTexCoord;
out vec3 FragPos;
out vec3 Normal;
out vec3 ourColor;
out vec2 ourTexCoord;

uniform mat4 camMatrix;
uniform mat4 model;
uniform mat4 translation;
uniform mat4 rotation;
uniform mat4 scale;


void main()
{
   FragPos = vec3(model * translation * -rotation * scale * vec4(aPos, 1.0));
   Normal = aNormal;
   
   ourColor = aColor;
   ourTexCoord = mat2(0.0, -1.0, 1.0, 0.0) * aTexCoord;

   gl_Position = camMatrix * vec4(FragPos, 1.0);
}

// fragment shader
#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 ourColor;
in vec2 ourTexCoord;

out uvec4 FragColor;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;
uniform uint objectR;
uniform uint objectG;
uniform uint objectB;

void main()
{
    FragColor = uvec4(objectR, objectG, objectB, 1.0);
    //FragColor = vec4(1.0,1.0,1.0,1.0);
}
