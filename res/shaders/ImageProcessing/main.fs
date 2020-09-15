#version 450

in vec2 v_texCoords;
out vec4 o_FragColor;

layout (location = 2) uniform sampler2D u_image;

void main()
{
    o_FragColor = texture(u_image, v_texCoords);
}
