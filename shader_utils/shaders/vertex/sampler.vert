#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 texCoords;

out vec3 Normal;
out vec4 FragPos;
out vec3 lp;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat3 normal_trans;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);

    Normal = normal_trans * normal;
    FragPos = view * model * vec4(position, 1.0f);
    TexCoords = texCoords;
}