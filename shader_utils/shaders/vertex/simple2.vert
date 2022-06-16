#version 330 core
layout (location = 0) in vec3 position;

uniform mat4 projection;
uniform mat4 model;
uniform mat4 translate;
uniform mat4 scale;
uniform mat4 view;


void main()
{
    gl_Position = projection * view * translate * scale * vec4(position, 1.0f);
}