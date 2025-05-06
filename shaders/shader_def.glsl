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
   ourTexCoord = aTexCoord;

   gl_Position = camMatrix * vec4(FragPos, 1.0);
}

// fragment shader
#version 330 core

in vec3 FragPos;
in vec3 Normal;
in vec3 ourColor;
in vec2 ourTexCoord;

out vec4 FragColor;

uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform vec4 lightColor;
uniform vec3 lightPos;
uniform vec3 camPos;

vec4 pointLight() {
   vec3 lightVec = lightPos - FragPos;
   float lightDist = length(lightVec);
   float a = 1.0f;
   float b = 0.04f;
   float intensity = 1.0f / (a * lightDist * lightDist + b * lightDist + 1.0f);

   float ambient = 0.2f;

   vec3 normal = normalize(Normal);
   vec3 lightDir = normalize(lightVec);

   float diff = max(dot(normal, lightDir), 0.0);

   float specularStrength = 0.5f;
   vec3 viewDir = normalize(camPos - FragPos);
   vec3 reflectDir = reflect(-lightDir, normal);
   float spec = pow(max(dot(viewDir, reflectDir), 0.0f), 32);
   float specular = specularStrength * spec;

   vec4 texColor = texture(diffuse0, ourTexCoord);
   vec4 texColor2 = texture(specular0, ourTexCoord);
   vec4 result = (texColor * (diff * intensity + ambient) + texColor2.r * specular * intensity) * lightColor;

   return result;
}

vec4 directionalLight() {
    vec3 lightDirection = normalize(vec3(1.0f, 1.0f, 0.0f));
    
    float ambient = 0.2f;

    vec3 normal = normalize(Normal);
    float diff = max(dot(normal, lightDirection), 0.0f);

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(camPos - FragPos);
    vec3 reflectDir = reflect(-lightDirection, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    float specular = specularStrength * spec;

    vec4 texColor = texture(diffuse0, ourTexCoord);
    vec4 texColor2 = texture(specular0, ourTexCoord);
    
    vec4 result = (texColor * (diff + ambient) + texColor2.r * specular) * lightColor;

    return result;
}

vec4 spotLight()
{
	float outerCone = 0.90f;
	float innerCone = 0.95f;

	float ambient = 0.20f;

	vec3 normal = normalize(Normal);
	vec3 lightDirection = normalize(lightPos - FragPos);
	float diffuse = max(dot(normal, lightDirection), 0.0f);

	float specularLight = 0.50f;
	vec3 viewDirection = normalize(camPos - FragPos);
	vec3 reflectionDirection = reflect(-lightDirection, normal);
	float specAmount = pow(max(dot(viewDirection, reflectionDirection), 0.0f), 16);
	float specular = specAmount * specularLight;

	float angle = dot(vec3(0.0f, -1.0f, 0.0f), -lightDirection);
	float inten = clamp((angle - outerCone) / (innerCone - outerCone), 0.0f, 1.0f);

	return (texture(diffuse0, ourTexCoord) * (diffuse * inten + ambient) + texture(specular0, ourTexCoord).r * specular * inten) * lightColor;
}

float near = 0.1f;
float far  = 100.f;

float steepness = 0.5f;
float offset = 30.0f;

float linearizeDepth(float depth) {
    return (2.0 * near * far) / (far + near - (depth * 2.0 - 1.0) * (far - near));
}

float logisticDepth(float depth)
{
    float zVal = linearizeDepth(depth);
    return (1 / (1 + exp(-steepness * (zVal - offset))));
}

void main()
{
    //FragColor = spotLight();
    float depth = logisticDepth(gl_FragCoord.z);
    FragColor = directionalLight() * (1.0f - depth) + vec4(depth * vec3(0.85f, 0.85f, 0.90f), 1.0f);
}
