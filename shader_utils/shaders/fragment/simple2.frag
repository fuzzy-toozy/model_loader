#version 330 core

out vec4 color;
uniform vec3 cube_color;

void main()
{
    color = vec4(cube_color, 0.0f); // Set alle 4 vector values to 1.0f
}
