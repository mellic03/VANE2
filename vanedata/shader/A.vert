#version 450 core

#include "B.glsl"

void main()
{
    const vec2 position  = vec2(gl_VertexIndex%2, gl_VertexIndex/2) * 4.0 - 1.0;
    const vec2 texcoord = (position + 1) * 0.5;

    vsout.texcoord = texcoord;
    gl_Position = vec4(position, 1.0, 1.0);
}

