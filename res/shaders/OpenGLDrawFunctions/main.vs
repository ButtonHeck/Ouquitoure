#version 450

layout (location = 0) in vec3 i_pos;
layout (location = 1) in vec3 i_color;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;

out vec3 v_color;

void main()
{
    v_color = i_color;
    gl_Position = u_projection * u_view * u_model * vec4(i_pos, 1.0);
}