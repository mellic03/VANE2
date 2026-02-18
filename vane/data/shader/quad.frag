#version 450 core

layout (location=0) out vec4 fsout_frag_color;

layout(set=0, binding=1) uniform sampler2D un_textures[];

in FS_in {
    layout (location=0) vec2 texcoord;
} fsin;


void main()
{
    fsout_frag_color = texture(un_textures[0], fsin.texcoord);
}
