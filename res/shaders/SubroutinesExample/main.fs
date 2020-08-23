#version 450

in vec3  v_color;
out vec4 o_fragColor;

//step 1. define a typedef-like function
subroutine vec4 changeColor(vec4);

//step 2. define some "implementations" of the subroutine
subroutine (changeColor) vec4 bypass(vec4 color)
{
    return color;
}
subroutine (changeColor) vec4 grayscale(vec4 color)
{
    float intensity = (color.r + color.g + color.b) / 3;
    return vec4(intensity, intensity, intensity, color.a);
}
subroutine (changeColor) vec4 shiftRight(vec4 color)
{
    return vec4(color.b, color.r, color.g, color.a);
}
subroutine (changeColor) vec4 shiftLeft(vec4 color)
{
    return vec4(color.g, color.b, color.r, color.a);
}
subroutine (changeColor) vec4 onlyRed(vec4 color)
{
    return vec4(color.r, 0.0, 0.0, color.a);
}
subroutine (changeColor) vec4 onlyGreen(vec4 color)
{
    return vec4(0.0, color.g, 0.0, color.a);
}
subroutine (changeColor) vec4 onlyBlue(vec4 color)
{
    return vec4(0.0, 0.0, color.b, color.a);
}

//step 3. define uniforms (they are like function pointers)
layout(location = 0) subroutine uniform changeColor colorFunc;

void main()
{
    o_fragColor = colorFunc( vec4(v_color, 1.0) );
}
