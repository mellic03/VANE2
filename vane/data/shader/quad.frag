#version 450 core

layout (location=0) out vec4 fsout_frag_color;

in FS_in {
    layout (location=0) vec2 texcoord;
} fsin;

void main()
{
    vec2 uv = fsin.texcoord;
    fsout_frag_color = vec4(uv.x, uv.y, 0.0, 1.0);
}
