#include "gfxapi/gfxapi_gl.hpp"
#include "vane/log.hpp"
#include "vane/file.hpp"
#include "vane/log.hpp"
#include "vane_string.hpp"
#include <fstream>
#include <memory>

using namespace vane;


void shader_preprocess(const std::string &src, std::string &out)
{
    static char incpath[256];

    const char *beg = src.data();
    const char *end = beg + src.length();

    const char *str = beg;
    while (true)
    {
        str = string::seek_ch(str, '#');
        if (!(*str && str<end))
        {
            return;
        }

        str = string::skip_key(str, "#include");
        VANE_ASSERT(str != nullptr, "Shader preprocess error: expected \"#include\"");

        str = string::skip_ch(str, ' ');
        VANE_ASSERT(
            *str == '\"',
            "Shader preprocess error: expected \"{}\", recieved \"{}\"",
            "\"", *str
        );

        const char *A = str;
        const char *B = string::seek_ch(A+1, '\"');
        VANE_ASSERT(B != nullptr, "Shader preprocess error: expected \"\"\"");

        A += 1; // "filename.glsl" --> filename.glsl"
        B -= 1; //  filename.glsl" --> filename.glsl
        std::memset(incpath, '\0', sizeof(incpath));
        std::strncpy(incpath, A, B-A);
        std::printf("incpath: \"%s\"\n", incpath);
        exit(123);
    }
}


// void shader_preprocess(const std::string &src, std::string &out)
// {
//     // const char *src = ree.c_str();
//     // char ch = *src;
//     size_t idx = 0;
//     char   ch  = '\0';

// lex_start: {
//     ch = src[idx];
//     if (idx >= src.length())
//         goto lex_end;
//     if (ch == '#')
//         goto lex_include;
// }   goto lex_end;

// lex_include: {
    
// }   goto lex_end;

// lex_end: {
//     VANE_ASSERT(idx == src.length(), "Error lexing source string");
// }   return;

// }

