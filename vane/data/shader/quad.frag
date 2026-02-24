#version 450 core

layout (location=0) out vec4 fsout_frag_color;

in FS_in {
    layout (location=0) vec2 texcoord;
} fsin;

layout (std140, binding = 0)
uniform ubo_CameraData {
    vec4 color;
    mat4 T;
    mat4 V;
    mat4 P;
} uboCameraData;


void main()
{
    vec2 uv = fsin.texcoord;
    vec3 color = uboCameraData.color.xyz;
    fsout_frag_color = vec4(color, 1.0);
}