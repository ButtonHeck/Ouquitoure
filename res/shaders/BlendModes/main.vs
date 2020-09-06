#version 450

layout (location = 0) in vec2 i_pos;
layout (location = 1) in vec4 i_color;

out vec4 v_color;

void main()
{
    gl_Position = vec4( i_pos, 0.0, 1.0 );
    v_color = i_color;
}
