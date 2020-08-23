#version 450

layout (location = 0) in vec2 i_pos;
layout (location = 1) in vec3 i_color;

out vec3 v_color;

void main()
{
    v_color = i_color;
    gl_Position = vec4(i_pos, 0.0, 1.0);
}
