#version 450

layout (location = 0) in vec2 i_pos;
layout (location = 1) in vec2 i_texCoords;

out vec2 v_texCoords;

void main()
{
    v_texCoords = i_texCoords;
    gl_Position = vec4(i_pos, 0.0, 1.0);
}
