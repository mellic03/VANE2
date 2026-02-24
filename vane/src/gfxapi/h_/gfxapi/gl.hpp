#pragma once

#include <glad/glad.h>
#include <GL/glu.h>

#include <cstdio>
#include <cassert>


#if defined(__GNUC__)
    #define VANE_INLINE [[gnu::always_inline]] inline
#elif defined(__clang__)
    #define VANE_INLINE [[gnu::always_inline]] [[gnu::gnu_inline]] extern inline
#elif defined(_MSC_VER)
    #pragma warning(error: 4714)
    #define VANE_INLINE __forceinline
#else
    #error Unsupported compiler
#endif


#define VANE_OPENGL_DEBUG
#ifdef VANE_OPENGL_DEBUG
    #define VN_GLCALL(Content_) \
    { \
        while (glGetError() != GL_NO_ERROR); \
        Content_ \
        GLenum err = glGetError(); \
        if (err != GL_NO_ERROR) \
        { \
            printf("OpenGL Error: %s\n", gluErrorString(err)); \
            fflush(stdout); \
            assert(err == GL_NO_ERROR); \
        } \
    }
#else
    #define VN_GLCALL(Content_) \
    { \
        Content_ \
    }
#endif


namespace gl
{
    VANE_INLINE void Enable(GLenum cap)  { VN_GLCALL( glEnable(cap); ) };
    VANE_INLINE void Disable(GLenum cap) { VN_GLCALL( glDisable(cap); ) };

    VANE_INLINE void Enable()  {  };
    VANE_INLINE void Disable() {  };

    template <typename... GLenums>
    VANE_INLINE void Enable(GLenum cap, GLenums... rest) { Enable(cap);  Enable(rest...); }

    template <typename... GLenums>
    VANE_INLINE void Disable(GLenum cap, GLenums... rest) { Disable(cap);  Disable(rest...); }

    VANE_INLINE void DispatchCompute( GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z )
    { VN_GLCALL( glDispatchCompute(num_groups_x, num_groups_y, num_groups_z); ) }

    VANE_INLINE void MemoryBarrier( GLbitfield barriers )
    { VN_GLCALL( glMemoryBarrier(barriers); ) }

    VANE_INLINE void GetBooleanv( GLenum pname, GLboolean *data )
    { VN_GLCALL( glGetBooleanv(pname, data); ) }

    VANE_INLINE void GetDoublev( GLenum pname, GLdouble *data )
    { VN_GLCALL( glGetDoublev(pname, data); ) }

    VANE_INLINE void GetFloatv( GLenum pname, GLfloat *data )
    { VN_GLCALL( glGetFloatv(pname, data); ) }

    VANE_INLINE void GetIntegerv( GLenum pname, GLint *data )
    { VN_GLCALL( glGetIntegerv(pname, data); ) }

    VANE_INLINE void GetInteger64v( GLenum pname, GLint64 *data )
    { VN_GLCALL( glGetInteger64v(pname, data); ) }

    VANE_INLINE void GetBooleani_v( GLenum target, GLuint index, GLboolean *data )
    { VN_GLCALL( glGetBooleani_v(target, index, data); ) }

    VANE_INLINE void GetIntegeri_v( GLenum target, GLuint index, GLint *data )
    { VN_GLCALL( glGetIntegeri_v(target, index, data); ) }

    VANE_INLINE void GetFloati_v( GLenum target, GLuint index, GLfloat *data )
    { VN_GLCALL( glGetFloati_v(target, index, data); ) }

    VANE_INLINE void GetDoublei_v( GLenum target, GLuint index, GLdouble *data )
    { VN_GLCALL( glGetDoublei_v(target, index, data); ) }

    VANE_INLINE void GetInteger64i_v( GLenum target, GLuint index, GLint64 *data )
    { VN_GLCALL( glGetInteger64i_v(target, index, data); ) }

    VANE_INLINE void GetProgramiv( GLuint program, GLenum pname, GLint *param )
    { VN_GLCALL( glGetProgramiv(program, pname, param); ) }


    // glGen...
    // ---------------------------------------------------------------------------------------
    VANE_INLINE void GenVertexArrays( GLsizei n, GLuint *arrays )
    { VN_GLCALL( glGenVertexArrays(n, arrays); ) }

    VANE_INLINE void GenBuffers( GLsizei n, GLuint *buffers )
    { VN_GLCALL( glGenBuffers(n, buffers); ) }

    VANE_INLINE void GenTextures( GLsizei n, GLuint *textures )
    { VN_GLCALL( glGenTextures(n, textures); ) }

    VANE_INLINE void GenFramebuffers( GLsizei n, GLuint *framebuffers )
    { VN_GLCALL( glGenFramebuffers(n, framebuffers); ) }

    VANE_INLINE void GenRenderbuffers( GLsizei n, GLuint *renderbuffers )
    { VN_GLCALL( glGenRenderbuffers(n, renderbuffers); ) }
    // ---------------------------------------------------------------------------------------

    // glDeleteXXX ---------------------------------------------------------------------------
    /**/
    VANE_INLINE void DeleteVertexArrays( GLsizei n, GLuint *arrays )
    { VN_GLCALL( glDeleteVertexArrays(n, arrays); ) }

    VANE_INLINE void DeleteBuffers( GLsizei n, GLuint *buffers )
    { VN_GLCALL( glDeleteBuffers(n, buffers); ) }

    VANE_INLINE void DeleteTextures( GLsizei n, GLuint *textures )
    { VN_GLCALL( glDeleteTextures(n, textures); ) }

    VANE_INLINE void DeleteFramebuffers( GLsizei n, GLuint *framebuffers )
    { VN_GLCALL( glDeleteFramebuffers(n, framebuffers); ) }

    VANE_INLINE void DeleteRenderbuffers( GLsizei n, GLuint *renderbuffers )
    { VN_GLCALL( glDeleteRenderbuffers(n, renderbuffers); ) }
    // ---------------------------------------------------------------------------------------


    // glBindXXX -----------------------------------------------------------------------------
    /**/
    VANE_INLINE void BindVertexArray( GLuint VAO )
    { VN_GLCALL( glBindVertexArray(VAO); ) }

    VANE_INLINE void BindBuffer( GLenum type, GLuint buf )
    { VN_GLCALL( glBindBuffer(type, buf); ) }

    VANE_INLINE void BindBufferBase( GLenum target, GLuint index, GLuint buffer )
    { VN_GLCALL( glBindBufferBase(target, index, buffer); ) }

    VANE_INLINE void BindFramebuffer( GLenum target, GLuint framebuffer )
    { VN_GLCALL( glBindFramebuffer(target, framebuffer); ) }

    VANE_INLINE void BindRenderbuffer( GLenum target, GLuint renderbuffer )
    { VN_GLCALL( glBindRenderbuffer(target, renderbuffer); ) }

    VANE_INLINE void BindTexture( GLenum target, GLuint texture )
    { VN_GLCALL( glBindTexture(target, texture); ) }

    VANE_INLINE void BindTextureUnit( GLuint unit, GLuint texture )
    { VN_GLCALL( glBindTextureUnit(unit, texture); ) }

    VANE_INLINE void BindImageTexture( GLuint unit, GLuint texture, GLint level, GLboolean layered,
                            GLint layer, GLenum access, GLenum format )
    { VN_GLCALL( glBindImageTexture(unit, texture, level, layered, layer, access, format); ) }

    VANE_INLINE void BindImageTextures( GLuint first, GLsizei count, const GLuint *textures )
    { VN_GLCALL( glBindImageTextures(first, count, textures); ) }

    VANE_INLINE void ClearTexImage( GLuint texture, GLint level, GLenum format, GLenum type,
                            const void *data )
    { VN_GLCALL( glClearTexImage(texture, level, format, type, data); ) }
    // ---------------------------------------------------------------------------------------


    // glDrawXXX -----------------------------------------------------------------------------
    /**/
    VANE_INLINE void DrawArrays( GLenum mode, GLint first, GLsizei count )
    { VN_GLCALL( glDrawArrays(mode, first, count); ) }

    VANE_INLINE void DrawElements( GLenum mode, GLsizei count, GLenum type, const void *indices )
    { VN_GLCALL( glDrawElements(mode, count, type, indices); ) }

    VANE_INLINE void DrawElementsInstanced( GLenum mode, GLsizei count, GLenum type,
                                    const void *indices, GLsizei instancecount )
    { VN_GLCALL( glDrawElementsInstanced(mode, count, type, indices, instancecount); ) }

    VANE_INLINE void MultiDrawElements( GLenum mode, const GLsizei *count, GLenum type,
                                const void *const *indices, GLsizei drawcount )
    { VN_GLCALL( glMultiDrawElements(mode, count, type, indices, drawcount); ) }

    VANE_INLINE void MultiDrawElementsIndirect( GLenum mode, GLenum type, const void *indirect,
                                        GLsizei primcount, GLsizei stride )
    { VN_GLCALL( glMultiDrawElementsIndirect(mode, type, indirect, primcount, stride); ) }
    // ---------------------------------------------------------------------------------------


    // glBufferXXX ---------------------------------------------------------------------------
    /**/
    VANE_INLINE void BufferData( GLenum target, GLsizeiptr size, const void *data, GLenum usage )
    { VN_GLCALL( glBufferData(target, size, data, usage); ) }

    VANE_INLINE void BufferSubData( GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
    { VN_GLCALL( glBufferSubData(target, offset, size, data); ) }

    VANE_INLINE void ShaderSource( GLuint shader, GLsizei count, const GLchar *const *string,
                                   const GLint *length )
    { VN_GLCALL( glShaderSource(shader, count, string, length); ) }

    VANE_INLINE void ShaderBinary( GLsizei count, const GLuint *shaders, GLenum binaryformat,
                        const void *binary, GLsizei length )
    { VN_GLCALL( glShaderBinary(count, shaders, binaryformat, binary, length); ) }

    VANE_INLINE void CompileShader( GLuint shader )
    { VN_GLCALL( glCompileShader(shader); ) }

    VANE_INLINE void GetShaderiv( GLuint shader, GLenum pname, GLint *param )
    { VN_GLCALL( glGetShaderiv(shader, pname, param); ) }

    VANE_INLINE void GetShaderInfoLog( GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog )
    { VN_GLCALL( glGetShaderInfoLog(shader, bufSize, length, infoLog); ) }

    VANE_INLINE void AttachShader( GLuint program, GLuint shader )
    { VN_GLCALL( glAttachShader(program, shader); ) }

    VANE_INLINE void DeleteShader( GLuint shader )
    { VN_GLCALL( glDeleteShader(shader); ) }

    VANE_INLINE void ValidateProgram( GLuint program )
    { VN_GLCALL( glValidateProgram(program); ) }

    VANE_INLINE void LinkProgram( GLuint program )
    { VN_GLCALL( glLinkProgram(program); ) }

    VANE_INLINE void ObjectLabel(GLenum identifier, GLuint name, GLsizei length, const char *label)
    { VN_GLCALL( glObjectLabel(identifier, name, length, label); ) }

    VANE_INLINE void ObjectPtrLabel(void *ptr, GLsizei length, const char *label)
    { VN_GLCALL( glObjectPtrLabel(ptr, length, label); ) }

    VANE_INLINE void GetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, char *label)
    { VN_GLCALL( glGetObjectLabel(identifier, name, bufSize, length, label); ) }

    VANE_INLINE void GetObjectPtrLabel(void *ptr, GLsizei bufSize, GLsizei *length, char *label)
    { VN_GLCALL( glGetObjectPtrLabel(ptr, bufSize, length, label); ) }

    VANE_INLINE void *MapBuffer( GLenum target, GLenum access )
    {
        void *data;
        VN_GLCALL( data = glMapBuffer(target, access); )
        return data;
    }

    VANE_INLINE void UnmapBuffer( GLenum target )
    { VN_GLCALL( glUnmapBuffer(target); ) }
    // ---------------------------------------------------------------------------------------


    // glActiveXXX ---------------------------------------------------------------------------
    /**/
    /**/
    VANE_INLINE void ActiveTexture( GLenum texture )
    { VN_GLCALL( glActiveTexture(texture); ) }
    // ---------------------------------------------------------------------------------------


    // glTexXXX ------------------------------------------------------------------------------
    /**/
    VANE_INLINE void TexImage2D( GLenum target, GLint level, GLint internalformat, GLsizei w, GLsizei h,
                        GLint border, GLenum format, GLenum type, const void *data )
    { VN_GLCALL( glTexImage2D(target, level, internalformat, w, h, border, format, type, data); ) }

    VANE_INLINE void TexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
                            GLsizei height, GLenum format, GLenum type, const void *pixels )
    { VN_GLCALL( glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels); ) }

    VANE_INLINE void TexImage3D( GLenum target, GLint level, GLint internalformat, GLsizei w, GLsizei h,
                        GLsizei d, GLint border, GLenum format, GLenum type, const void *data )
    { VN_GLCALL( glTexImage3D(target, level, internalformat, w, h, d, border, format, type, data); ) }

    VANE_INLINE void TexParameteri( GLenum target, GLenum pname, GLint param )
    { VN_GLCALL( glTexParameteri(target, pname, param); ) }

    VANE_INLINE void GetTextureImage( GLuint texture, GLint level, GLenum format, GLenum type,
                            GLsizei bufSize, void *pixels )
    { VN_GLCALL( glGetTextureImage(texture, level, format, type, bufSize, pixels); ) }


    VANE_INLINE GLuint64 GetTextureHandleARB( GLuint texture )
    {
        GLuint64 handle;
        VN_GLCALL( handle = glGetTextureHandleARB(texture); )
        return handle;
    }

    VANE_INLINE void MakeTextureHandleResidentARB( GLuint64 handle )
    { VN_GLCALL( glMakeTextureHandleResidentARB(handle); ) }

    VANE_INLINE void MakeTextureHandleNonResidentARB( GLuint64 handle )
    { VN_GLCALL( glMakeTextureHandleNonResidentARB(handle); ) }

    VANE_INLINE void GenerateTextureMipmap( GLuint texture )
    { VN_GLCALL( glGenerateTextureMipmap(texture); ) }

    VANE_INLINE void GenerateMipmap( GLenum target )
    { VN_GLCALL( glGenerateMipmap(target); ) }

    VANE_INLINE void PixelStorei( GLenum pname, GLint param )
    { VN_GLCALL( glPixelStorei(pname, param); ) }
    // ---------------------------------------------------------------------------------------------



    // glTextureXXX
    // ---------------------------------------------------------------------------------------------
    VANE_INLINE void TextureStorage2D( GLuint texture, GLsizei levels, GLenum internalformat,
                                      GLsizei width, GLsizei height )
    { VN_GLCALL( glTextureStorage2D(texture, levels, internalformat, width, height); ) }

    VANE_INLINE void TextureSubImage2D( GLenum texture, GLint level, GLint xoffset, GLint yoffset,
                                       GLsizei width, GLsizei height, GLenum format, GLenum type,
                                       const void *pixels )
    {
        VN_GLCALL(
            glTextureSubImage2D(
                texture, level, xoffset, yoffset, width, height, format, type, pixels
            );
        )
    }

    VANE_INLINE void TextureStorage3D( GLuint texture, GLsizei levels, GLenum internalformat,
                                      GLsizei width, GLsizei height, GLsizei depth )
    { VN_GLCALL( glTextureStorage3D(texture, levels, internalformat, width, height, depth); ) }


    VANE_INLINE void TextureSubImage3D( GLuint texture, GLint level, GLint xoffset, GLint yoffset,
                                       GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
                                       GLenum format, GLenum type, const void *pixels )
    {
        VN_GLCALL(
            glTextureSubImage3D(
                texture,
                level,
                xoffset, yoffset, zoffset,
                width, height, depth,
                format,
                type,
                pixels
            );
        )
    }


    VANE_INLINE void TextureParameteri( GLuint texture, GLenum pname, GLint param )
    { VN_GLCALL( glTextureParameteri(texture, pname, param); ) }

    VANE_INLINE void TextureParameterf( GLuint texture, GLenum pname, GLfloat param )
    { VN_GLCALL( glTextureParameterf(texture, pname, param); ) }
    // ---------------------------------------------------------------------------------------------


    // glFramebufferXXX ---------------------------------------------------------------------
    VANE_INLINE void FramebufferTexture( GLenum target, GLenum attachment, GLuint texture, GLint level )
    { VN_GLCALL( glFramebufferTexture(target, attachment, texture, level); ) }

    VANE_INLINE void FramebufferTexture2D( GLenum target, GLenum attachment, GLenum textarget,
                                          GLuint texture, GLint level )
    { VN_GLCALL( glFramebufferTexture2D(target, attachment, textarget, texture, level); ) }

    VANE_INLINE void FramebufferTexture3D( GLenum target, GLenum attachment, GLenum textarget,
                                          GLuint texture, GLint level, GLint layer )

    { VN_GLCALL( glFramebufferTexture3D(target, attachment, textarget, texture, level, layer); ) }

    VANE_INLINE void FramebufferTextureLayer( GLenum target, GLenum attachment, GLuint texture,
                                             GLint level, GLint layer )
    { VN_GLCALL( glFramebufferTextureLayer(target, attachment, texture, level, layer); ) }

    // ---------------------------------------------------------------------------------------


    // Uniforms ------------------------------------------------------------------------------
    /**/
    VANE_INLINE GLint GetUniformLocation( GLuint program, const char *name )
    {
        int32_t data;
        VN_GLCALL( data = glGetUniformLocation(program, name); )
        return data;
    }

    VANE_INLINE GLuint GetUniformBlockIndex(GLuint program, const GLchar *uniformBlockName)
    {
        GLuint data;
        VN_GLCALL( data = glGetUniformBlockIndex(program, uniformBlockName); )
        return data;
    }

    VANE_INLINE void UniformBlockBinding(GLuint program, GLuint uniformBlockIndex, GLuint uniformBlockBinding)
    { VN_GLCALL( glUniformBlockBinding(program, uniformBlockIndex, uniformBlockBinding); ) }

    VANE_INLINE void Uniform1i( GLint loc, int i )
    { VN_GLCALL( glUniform1i(loc, i); ) }

    VANE_INLINE void Uniform1f( GLint loc, float f )
    { VN_GLCALL( glUniform1f(loc, f); ) }

    VANE_INLINE void Uniform2iv( GLint loc, GLsizei count, const int *value )
    { VN_GLCALL( glUniform2iv(loc, count, value); ) }

    VANE_INLINE void Uniform3iv( GLint loc, GLsizei count, const int *value )
    { VN_GLCALL( glUniform3iv(loc, count, value); ) }

    VANE_INLINE void Uniform2fv( GLint loc, GLsizei count, float *value )
    { VN_GLCALL( glUniform2fv(loc, count, value); ) }

    VANE_INLINE void Uniform3fv( GLint loc, GLsizei count, float *value )
    { VN_GLCALL( glUniform3fv(loc, count, value); ) }

    VANE_INLINE void Uniform4fv( GLint loc, GLsizei count, float *value )
    { VN_GLCALL( glUniform4fv(loc, count, value); ) }

    VANE_INLINE void UniformMatrix3fv( GLint loc, GLsizei count, GLboolean transpose, float *value )
    { VN_GLCALL( glUniformMatrix3fv(loc, count, transpose, value); ) }

    VANE_INLINE void UniformMatrix4fv( GLint loc, GLsizei count, GLboolean transpose, float *value )
    { VN_GLCALL( glUniformMatrix4fv(loc, count, transpose, value); ) }

    VANE_INLINE void UniformHandleui64ARB( GLint location, GLuint64 value )
    { VN_GLCALL( glUniformHandleui64ARB(location, value); ) }
    // ---------------------------------------------------------------------------------------


    VANE_INLINE void VertexAttribPointer( GLuint index, GLint size,
                                GLenum type, GLboolean normalized,
                                GLsizei stride, GLuint offset )
    {
        VN_GLCALL(
            glVertexAttribPointer(
                index, size, type, normalized,
                stride, reinterpret_cast<void *>(offset)
            );
        )
    }

    VANE_INLINE void EnableVertexAttribArray( GLuint index )
    { VN_GLCALL( glEnableVertexAttribArray(index); ) }

    VANE_INLINE void VertexArrayVertexBuffer( GLuint vaobj, GLuint bindingindex, GLuint buffer,
                                    GLintptr offset, GLsizei stride )
    { VN_GLCALL( glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride); ) }

    VANE_INLINE void VertexArrayElementBuffer( GLuint vaobj, GLuint buffer )
    { VN_GLCALL( glVertexArrayElementBuffer(vaobj, buffer); ) }

    VANE_INLINE void EnableVertexArrayAttrib( GLuint vaobj, GLuint index )
    { VN_GLCALL( glEnableVertexArrayAttrib(vaobj, index); ) }

    VANE_INLINE void VertexArrayAttribFormat( GLuint vaobj, GLuint attribindex, GLint size, GLenum type,
                                    GLboolean normalized, GLuint relativeoffset )
    {
        VN_GLCALL(
            glVertexArrayAttribFormat(
                vaobj, attribindex, size, type, normalized, relativeoffset
            );
        )
    }

    VANE_INLINE void VertexArrayAttribBinding( GLuint vaobj, GLuint attribindex, GLuint bindingindex )
    { VN_GLCALL( glVertexArrayAttribBinding(vaobj, attribindex, bindingindex); ) }

    VANE_INLINE void UseProgram( GLuint program )
    { VN_GLCALL( glUseProgram(program); ) }

    VANE_INLINE void DeleteProgram( GLuint program )
    { VN_GLCALL( glDeleteProgram(program); ) }

    VANE_INLINE void ClearColor( float r, float g, float b, float a )
    { VN_GLCALL( glClearColor(r, g, b, a); ) }

    VANE_INLINE void Clear( GLbitfield mask )
    { VN_GLCALL( glClear(mask); ) }

    VANE_INLINE void Viewport( GLint x, GLint y, GLsizei w, GLsizei h )
    { VN_GLCALL( glViewport(x, y, w, h); ) }

    VANE_INLINE void CullFace( GLenum mode )
    { VN_GLCALL( glCullFace(mode); ) }

    VANE_INLINE void BlendFunc( GLenum sfactor, GLenum dfactor )
    { VN_GLCALL( glBlendFunc(sfactor, dfactor); ) }

    VANE_INLINE void BlendFunci( GLuint buf, GLenum sfactor, GLenum dfactor )
    { VN_GLCALL( glBlendFunci(buf, sfactor, dfactor); ) }


    VANE_INLINE void DebugMessageControl(GLenum source, GLenum type, GLenum severity,
                                    GLsizei count, const GLuint *ids, GLboolean enabled)
    { VN_GLCALL( glDebugMessageControl(source, type, severity, count, ids, enabled); ) }

    VANE_INLINE void DebugMessageCallback(GLDEBUGPROC callback, const void *userParam)
    { VN_GLCALL( glDebugMessageCallback(callback, userParam); ) }




    // OpenGL 4.6 AZDO functions
    // ---------------------------------------------------------------------------------------
    VANE_INLINE void CreateTextures( GLenum target, GLsizei n, GLuint *textures )
    { VN_GLCALL( glCreateTextures(target, n, textures); ) }

    VANE_INLINE void CreateFramebuffers( GLsizei n, GLuint *framebuffers )
    { VN_GLCALL( glCreateFramebuffers(n, framebuffers); ) }

    VANE_INLINE void CreateRenderbuffers( GLsizei n, GLuint *framebuffers )
    { VN_GLCALL( glCreateRenderbuffers(n, framebuffers); ) }

    VANE_INLINE void CreateVertexArrays(GLsizei n, GLuint *arrays)
    { VN_GLCALL( glCreateVertexArrays(n, arrays); ) }

    VANE_INLINE void CreateBuffers(GLsizei n, GLuint *buffers)
    { VN_GLCALL( glCreateBuffers(n, buffers); ) }

    VANE_INLINE GLuint CreateProgram()
    { VN_GLCALL( return glCreateProgram(); ) }

    VANE_INLINE GLuint CreateShader(GLenum type)
    { VN_GLCALL( return glCreateShader(type); ) }

    VANE_INLINE void NamedBufferData( GLuint buffer, GLsizeiptr size, const void *data, GLenum usage )
    { VN_GLCALL( glNamedBufferData(buffer, size, data, usage); ) }

    VANE_INLINE void NamedBufferSubData( GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data )
    { VN_GLCALL( glNamedBufferSubData(buffer, offset, size, data); ) }

    VANE_INLINE void NamedBufferStorage( GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags )
    { VN_GLCALL( glNamedBufferStorage(buffer, size, data, flags); ) }

    VANE_INLINE void NamedRenderbufferStorage( GLuint renderbuffer, GLenum internalformat, GLsizei width,
                                    GLsizei height )
    { VN_GLCALL( glNamedRenderbufferStorage(renderbuffer, internalformat, width, height); ) }

    VANE_INLINE void NamedFramebufferRenderbuffer( GLuint framebuffer, GLenum attachment,
                                        GLenum renderbuffertarget, GLuint renderbuffer )
    { VN_GLCALL( glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer); ) }

    VANE_INLINE void *MapNamedBuffer( GLuint buffer, GLenum access )
    {
        void *data;
        VN_GLCALL( data = glMapNamedBuffer(buffer, access); )
        return data;
    }
    VANE_INLINE void UnmapNamedBuffer( GLuint buffer )
    { VN_GLCALL( glUnmapNamedBuffer(buffer); ) }

    VANE_INLINE void *MapNamedBufferRange( GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access )
    {
        void *data;
        VN_GLCALL( data = glMapNamedBufferRange(buffer, offset, length, access); )
        return data;
    }

    VANE_INLINE void NamedFramebufferTexture( GLuint framebuffer, GLenum attachment, GLuint texture,
                                             GLint level )
    { VN_GLCALL( glNamedFramebufferTexture(framebuffer, attachment, texture, level); ) }

    VANE_INLINE void NamedFramebufferDrawBuffer( GLuint framebuffer, GLenum mode )
    { VN_GLCALL( glNamedFramebufferDrawBuffer(framebuffer, mode); ) }

    VANE_INLINE void NamedFramebufferDrawBuffers( GLuint framebuffer, GLsizei n, const GLenum *bufs )
    { VN_GLCALL( glNamedFramebufferDrawBuffers(framebuffer, n, bufs); ) }

    VANE_INLINE void NamedFramebufferTextureLayer( GLuint framebuffer, GLenum attachment, GLuint texture,
                                                  GLint level, GLint layer )
    { VN_GLCALL( glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer); ) }

    VANE_INLINE void ClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer,
                                        GLint drawbuffer, const GLint *value)
    { VN_GLCALL( glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value); ) }

    VANE_INLINE void ClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer,
                                         GLint drawbuffer, const GLuint *value)
    { VN_GLCALL( glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value); ) }

    VANE_INLINE void ClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer,
                                        GLint drawbuffer, const GLfloat *value)
    { VN_GLCALL( glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value); ) }

    VANE_INLINE void ClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer,
                                        GLint drawbuffer, GLfloat depth, GLint stencil)
    { VN_GLCALL( glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil); ) }

    VANE_INLINE GLenum CheckNamedFramebufferStatus(GLuint framebuffer, GLenum target)
    {
        GLenum status;
        VN_GLCALL( status = glCheckNamedFramebufferStatus(framebuffer, target); )
        return status;
    }
    // ---------------------------------------------------------------------------------------

};




