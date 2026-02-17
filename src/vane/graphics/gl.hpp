#pragma once
#include <glad/glad.h>
#include <cassert>

#define GLClearError() \
{ \
    while (glGetError() != GL_NO_ERROR); \
}

#ifdef IDK_DEBUG
    #define IDK_GLCALL(glFunc) \
    { \
        GLClearError(); \
        glFunc \
        GLenum err = glGetError(); \
        if (err != GL_NO_ERROR) \
        { \
            printf("OpenGL Error: %s\n", gluErrorString(err)); \
            fflush(stdout); \
            assert(err == GL_NO_ERROR); \
        } \
    }
#else
    #define IDK_GLCALL(glFunc) \
    { \
        glFunc \
    }
#endif



namespace gl
{
    inline void Enable(GLenum cap)      { IDK_GLCALL( glEnable(cap);  ) };
    inline void Disable(GLenum cap)     { IDK_GLCALL( glDisable(cap); ) };
    inline void Enable()  {  };
    inline void Disable() {  };

    template <typename... GLenums>
    inline void Enable( GLenum, GLenums... );

    template <typename... GLenums>
    inline void Disable( GLenum, GLenums... );

    void DispatchCompute( GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z );
    void MemoryBarrier( GLbitfield barriers );

    void GetBooleanv( GLenum pname, GLboolean *data );
    void GetDoublev( GLenum pname, GLdouble *data );
    void GetFloatv( GLenum pname, GLfloat *data );
    void GetIntegerv( GLenum pname, GLint *data );
    void GetInteger64v( GLenum pname, GLint64 *data );
    void GetBooleani_v( GLenum target, GLuint index, GLboolean *data );
    void GetIntegeri_v( GLenum target, GLuint index, GLint *data );
    void GetFloati_v( GLenum target, GLuint index, GLfloat *data );
    void GetDoublei_v( GLenum target, GLuint index, GLdouble *data );
    void GetInteger64i_v( GLenum target, GLuint index, GLint64 *data );

    void GetProgramiv( GLuint program, GLenum pname, GLint *param );

    void GenVertexArrays  ( GLsizei n, GLuint *arrays );
    void GenBuffers       ( GLsizei n, GLuint *buffers );
    void GenTextures      ( GLsizei n, GLuint *textures );
    void GenFramebuffers  ( GLsizei n, GLuint *framebuffers );
    void GenRenderbuffers ( GLsizei n, GLuint *renderbuffers );

    void CreateVertexArrays  ( GLsizei n, GLuint *arrays );
    void CreateBuffers       ( GLsizei n, GLuint *buffers );
    void CreateTextures      ( GLenum target, GLsizei n, GLuint *textures );
    void CreateFramebuffers  ( GLsizei n, GLuint *framebuffers );
    void CreateRenderbuffers ( GLsizei n, GLuint *renderbuffers );

    GLuint CreateProgram    ();
    GLuint CreateShader     ( GLenum type );

    void ShaderSource( GLuint shader, GLsizei count, const GLchar *const *string,
                       const GLint *length );

    void ShaderBinary( GLsizei count, const GLuint *shaders, GLenum binaryformat,
                       const void *binary, GLsizei length );

    void CompileShader    ( GLuint shader );
    void GetShaderiv      ( GLuint shader, GLenum pname, GLint *param );
    void GetShaderInfoLog ( GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog );
    void AttachShader     ( GLuint program, GLuint shader );
    void DeleteShader     ( GLuint shader );
    void ValidateProgram  ( GLuint program );
    void LinkProgram      ( GLuint program );

    void DeleteVertexArrays  ( GLsizei n, GLuint *arrays );
    void DeleteBuffers       ( GLsizei n, GLuint *buffers );
    void DeleteTextures      ( GLsizei n, GLuint *textures );
    void DeleteFramebuffers  ( GLsizei n, GLuint *framebuffers );
    void DeleteRenderbuffers ( GLsizei n, GLuint *renderbuffers );
    void BindVertexArray( GLuint VAO );
    void BindBuffer( GLenum type, GLuint buf );
    void BindBufferBase( GLenum target, GLuint index, GLuint buffer );
    void BindFramebuffer( GLenum target, GLuint framebuffer );
    void BindRenderbuffer( GLenum target, GLuint renderbuffer );
    void BindTexture( GLenum target, GLuint texture );
    void BindTextureUnit( GLuint unit, GLuint texture );
    void BindImageTexture( GLuint unit, GLuint texture, GLint level, GLboolean layered,
                           GLint layer, GLenum access, GLenum format );

    void BindImageTextures( GLuint first, GLsizei count, const GLuint *textures );
    void ClearTexImage( GLuint texture, GLint level, GLenum format, GLenum type, const void *data );

    void DrawArrays( GLenum mode, GLint first, GLsizei count );
    void DrawElements( GLenum mode, GLsizei count, GLenum type, const void *indices );
    void DrawElementsInstanced( GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount );
    void MultiDrawElements( GLenum mode, const GLsizei *count, GLenum type, const void *const *indices, GLsizei drawcount );
    void MultiDrawElementsIndirect( GLenum mode, GLenum type, const void *indirect, GLsizei primcount, GLsizei stride );

    void BufferData( GLenum target, GLsizeiptr size, const void *data, GLenum usage );
    void BufferSubData( GLenum target, GLintptr offset, GLsizeiptr size, const void *data);

    void NamedBufferData( GLuint buffer, GLsizeiptr size, const void *data, GLenum usage );
    void NamedBufferSubData( GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data );
    void NamedBufferStorage( GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags );
    void NamedRenderbufferStorage( GLuint renderbuffer, GLenum internalformat, GLsizei width, GLsizei height );
    void NamedFramebufferRenderbuffer( GLuint framebuffer, GLenum attachment, GLenum renderbuffertarget, GLuint renderbuffer );


    void *MapBuffer( GLenum target, GLenum access );
    void  UnmapBuffer( GLenum target );

    void *MapNamedBuffer( GLuint buffer, GLenum access );
    void  UnmapNamedBuffer( GLuint buffer );

    void *MapNamedBufferRange( GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access );

    // glActiveXXX -----------------------------------------------------------------------------
    /**/
    void ActiveTexture( GLenum texture );
    // -----------------------------------------------------------------------------------------


    // glTexXXX --------------------------------------------------------------------------------
    /**/
    void TexImage2D( GLenum target, GLint level, GLint internalformat, GLsizei w, GLsizei h,
                     GLint border, GLenum format, GLenum type, const void *data );

    void TexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
                        GLsizei height, GLenum format, GLenum type, const void *pixels );

    void TexImage3D( GLenum target, GLint level, GLint internalformat, GLsizei w, GLsizei h,
                     GLsizei d, GLint border, GLenum format, GLenum type, const void *data );

    void TexParameteri( GLenum target, GLenum pname, GLint param );

    // -----------------------------------------------------------------------------------------


    // glTextureXXX ----------------------------------------------------------------------------
    // -----------------------------------------------------------------------------------------
    void TextureStorage2D( GLuint texture, GLsizei levels, GLenum internalformat,
                           GLsizei width, GLsizei height );

    void TextureSubImage2D( GLenum texture, GLint level, GLint xoffset, GLint yoffset,
                            GLsizei width, GLsizei height, GLenum format, GLenum type,
                            const void *pixels );

    void TextureStorage3D( GLuint texture, GLsizei levels, GLenum internalformat,
                           GLsizei width, GLsizei height, GLsizei depth );

    void TextureSubImage3D( GLuint texture, GLint level, GLint xoffset, GLint yoffset,
                            GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
                            GLenum format, GLenum type, const void *pixels );

    void TextureParameteri( GLuint texture, GLenum pname, GLint param );
    void TextureParameterf( GLuint texture, GLenum pname, GLfloat param );
    // -----------------------------------------------------------------------------------------

    void GetTextureImage( GLuint texture, GLint level, GLenum format, GLenum type,
                          GLsizei bufSize, void *pixels );

    GLuint64 GetTextureHandleARB( GLuint texture );
    void     MakeTextureHandleResidentARB( GLuint64 handle );
    void     MakeTextureHandleNonResidentARB( GLuint64 handle );

    void GenerateTextureMipmap( GLuint texture );
    void GenerateMipmap( GLenum target );
    void PixelStorei( GLenum pname, GLint param );


    // Framebuffer stuff  --------------------------------------------------------------------
    /**/
    void FramebufferTexture( GLenum target, GLenum attachment, GLuint texture, GLint level );

    void FramebufferTexture2D( GLenum target, GLenum attachment, GLenum textarget,
                                GLuint texture, GLint level );

    void FramebufferTexture3D( GLenum target, GLenum attachment, GLenum textarget,
                               GLuint texture, GLint level, GLint layer );

    void FramebufferTextureLayer( GLenum target, GLenum attachment, GLuint texture,
                                  GLint level, GLint layer );

    void NamedFramebufferTexture ( GLuint framebuffer, GLenum attachment, GLuint texture,
                                   GLint level );

    void NamedFramebufferDrawBuffer( GLuint framebuffer, GLenum mode );

    void NamedFramebufferDrawBuffers( GLuint framebuffer, GLsizei n, const GLenum *bufs );

    void NamedFramebufferTextureLayer( GLuint framebuffer, GLenum attachment, GLuint texture,
                                       GLint level, GLint layer );
    // ---------------------------------------------------------------------------------------

    // Uniforms ------------------------------------------------------------------------------
    /**/
    GLint GetUniformLocation( GLuint program, const char *name );
    void  Uniform1i( GLint loc, int i );
    void  Uniform2iv( GLint loc, GLsizei count, const int * );
    void  Uniform3iv( GLint loc, GLsizei count, const int * );
    void  Uniform1f( GLint loc, float f );
    void  Uniform2fv( GLint loc, GLsizei count, float *value );
    void  Uniform3fv( GLint loc, GLsizei count, float *value );
    void  Uniform4fv( GLint loc, GLsizei count, float *value );
    void  UniformMatrix3fv( GLint loc, GLsizei count, GLboolean transpose, float *value );
    void  UniformMatrix4fv( GLint loc, GLsizei count, GLboolean transpose, float *value );

    void  UniformHandleui64ARB( GLint location, GLuint64 value );
    // ---------------------------------------------------------------------------------------

    void VertexAttribPointer( GLuint index, GLint size, GLenum type, GLboolean normalized,
                              GLsizei stride, GLuint offset );

    void EnableVertexAttribArray( GLuint index );


    void VertexArrayVertexBuffer( GLuint vaobj, GLuint bindingindex, GLuint buffer,
                                  GLintptr offset, GLsizei stride );

    void VertexArrayElementBuffer( GLuint vaobj, GLuint buffer );

    void EnableVertexArrayAttrib( GLuint vaobj, GLuint index );

    void VertexArrayAttribFormat( GLuint vaobj, GLuint attribindex, GLint size, GLenum type,
                                  GLboolean normalized, GLuint relativeoffset );

    void VertexArrayAttribBinding( GLuint vaobj, GLuint attribindex, GLuint bindingindex );



    void UseProgram( GLuint program );
    void DeleteProgram( GLuint program );
    void ClearColor( float r, float g, float b, float a );
    void Clear( GLbitfield mask );
    void Viewport( GLint x, GLint y, GLsizei w, GLsizei h );
    void CullFace( GLenum mode );
    void BlendFunc( GLenum sfactor, GLenum dfactor );
    void BlendFunci( GLuint buf, GLenum sfactor, GLenum dfactor );

};


template <typename... GLenums>
inline void gl::Enable( GLenum cap, GLenums... rest )
{
    Enable(cap);
    Enable(rest...);
}


template <typename... GLenums>
inline void gl::Disable( GLenum cap, GLenums... rest )
{
    Disable(cap);
    Disable(rest...);
}

