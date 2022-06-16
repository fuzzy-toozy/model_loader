#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

out vec4 gouruad_color;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;
uniform vec3 lightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal_trans;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);

    vec3 Normal = normalize(normal_trans * normal);
    vec3 FragPos = vec3(view * model * vec4(position, 1.0f));

    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength * lightColor;

    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(Normal, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    float specularStrength = 0.5f;
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * lightColor;

    vec3 result = (diffuse + ambient + specular) * objectColor;

    gouruad_color = vec4(result, 1.0f);
}