// #pragma once

// #include <glad/glad.h>
// #include <GL/glu.h>

// #include <cstdio>
// #include <cassert>

// #define GLClearError() \
// { \
//     while (glGetError() != GL_NO_ERROR); \
// }

// #define VANE_OPENGL_DEBUG
// #ifdef VANE_OPENGL_DEBUG
//     #define VN_GLCALL(Content_) \
//     { \
//         GLClearError(); \
//         Content_ \
//         GLenum err = glGetError(); \
//         if (err != GL_NO_ERROR) \
//         { \
//             printf("OpenGL Error: %s\n", gluErrorString(err)); \
//             fflush(stdout); \
//             assert(err == GL_NO_ERROR); \
//         } \
//     }
// #else
//     #define VN_GLCALL(Content_) \
//     { \
//         Content_ \
//     }
// #endif


// namespace gl
// {
//     inline void Enable(GLenum cap)      { VN_GLCALL( glEnable(cap); ) };
//     inline void Disable(GLenum cap)     { VN_GLCALL( glDisable(cap); ) };

//     inline void Enable()  {  };
//     inline void Disable() {  };

//     template <typename... GLenums>
//     inline void Enable( GLenum cap, GLenums... rest )
//     { Enable(cap);  Enable(rest...); }

//     template <typename... GLenums>
//     inline void Disable( GLenum cap, GLenums... rest )
//     { Disable(cap);  Disable(rest...); }

//     inline void DispatchCompute( GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z )
//     { VN_GLCALL( glDispatchCompute(num_groups_x, num_groups_y, num_groups_z); ) }

//     inline void MemoryBarrier( GLbitfield barriers )
//     { VN_GLCALL( glMemoryBarrier(barriers); ) }

//     inline void GetBooleanv( GLenum pname, GLboolean *data )
//     { VN_GLCALL( glGetBooleanv(pname, data); ) }

//     inline void GetDoublev( GLenum pname, GLdouble *data )
//     { VN_GLCALL( glGetDoublev(pname, data); ) }

//     inline void GetFloatv( GLenum pname, GLfloat *data )
//     { VN_GLCALL( glGetFloatv(pname, data); ) }

//     inline void GetIntegerv( GLenum pname, GLint *data )
//     { VN_GLCALL( glGetIntegerv(pname, data); ) }

//     inline void GetInteger64v( GLenum pname, GLint64 *data )
//     { VN_GLCALL( glGetInteger64v(pname, data); ) }

//     inline void GetBooleani_v( GLenum target, GLuint index, GLboolean *data )
//     { VN_GLCALL( glGetBooleani_v(target, index, data); ) }

//     inline void GetIntegeri_v( GLenum target, GLuint index, GLint *data )
//     { VN_GLCALL( glGetIntegeri_v(target, index, data); ) }

//     inline void GetFloati_v( GLenum target, GLuint index, GLfloat *data )
//     { VN_GLCALL( glGetFloati_v(target, index, data); ) }

//     inline void GetDoublei_v( GLenum target, GLuint index, GLdouble *data )
//     { VN_GLCALL( glGetDoublei_v(target, index, data); ) }

//     inline void GetInteger64i_v( GLenum target, GLuint index, GLint64 *data )
//     { VN_GLCALL( glGetInteger64i_v(target, index, data); ) }

//     inline void GetProgramiv( GLuint program, GLenum pname, GLint *param )
//     { VN_GLCALL( glGetProgramiv(program, pname, param); ) }


//     // glGenXXX ------------------------------------------------------------------------------
//     /**/
//     inline void GenVertexArrays( GLsizei n, GLuint *arrays )
//     { VN_GLCALL( glGenVertexArrays(n, arrays); ) }

//     inline void GenBuffers( GLsizei n, GLuint *buffers )
//     { VN_GLCALL( glGenBuffers(n, buffers); ) }

//     inline void GenTextures( GLsizei n, GLuint *textures )
//     { VN_GLCALL( glGenTextures(n, textures); ) }

//     inline void GenFramebuffers( GLsizei n, GLuint *framebuffers )
//     { VN_GLCALL( glGenFramebuffers(n, framebuffers); ) }

//     inline void GenRenderbuffers( GLsizei n, GLuint *renderbuffers )
//     { VN_GLCALL( glGenRenderbuffers(n, renderbuffers); ) }
//     // ---------------------------------------------------------------------------------------


//     inline void CreateTextures( GLenum target, GLsizei n, GLuint *textures )
//     { VN_GLCALL( glCreateTextures(target, n, textures); ) }

//     inline void CreateFramebuffers( GLsizei n, GLuint *framebuffers )
//     { VN_GLCALL( glCreateFramebuffers(n, framebuffers); ) }

//     inline void CreateRenderbuffers( GLsizei n, GLuint *framebuffers )
//     { VN_GLCALL( glCreateRenderbuffers(n, framebuffers); ) }



//     // glDeleteXXX ---------------------------------------------------------------------------
//     /**/
//     inline void DeleteVertexArrays( GLsizei n, GLuint *arrays )
//     { VN_GLCALL( glDeleteVertexArrays(n, arrays); ) }

//     inline void DeleteBuffers( GLsizei n, GLuint *buffers )
//     { VN_GLCALL( glDeleteBuffers(n, buffers); ) }

//     inline void DeleteTextures( GLsizei n, GLuint *textures )
//     { VN_GLCALL( glDeleteTextures(n, textures); ) }

//     inline void DeleteFramebuffers( GLsizei n, GLuint *framebuffers )
//     { VN_GLCALL( glDeleteFramebuffers(n, framebuffers); ) }

//     inline void DeleteRenderbuffers( GLsizei n, GLuint *renderbuffers )
//     { VN_GLCALL( glDeleteRenderbuffers(n, renderbuffers); ) }
//     // ---------------------------------------------------------------------------------------


//     // glBindXXX -----------------------------------------------------------------------------
//     /**/
//     inline void BindVertexArray( GLuint VAO )
//     { VN_GLCALL( glBindVertexArray(VAO); ) }

//     inline void BindBuffer( GLenum type, GLuint buf )
//     { VN_GLCALL( glBindBuffer(type, buf); ) }

//     inline void BindBufferBase( GLenum target, GLuint index, GLuint buffer )
//     { VN_GLCALL( glBindBufferBase(target, index, buffer); ) }

//     inline void BindFramebuffer( GLenum target, GLuint framebuffer )
//     { VN_GLCALL( glBindFramebuffer(target, framebuffer); ) }

//     inline void BindRenderbuffer( GLenum target, GLuint renderbuffer )
//     { VN_GLCALL( glBindRenderbuffer(target, renderbuffer); ) }

//     inline void BindTexture( GLenum target, GLuint texture )
//     { VN_GLCALL( glBindTexture(target, texture); ) }

//     inline void BindTextureUnit( GLuint unit, GLuint texture )
//     { VN_GLCALL( glBindTextureUnit(unit, texture); ) }


//     inline void BindImageTexture( GLuint unit, GLuint texture, GLint level, GLboolean layered,
//                             GLint layer, GLenum access, GLenum format )
//     { VN_GLCALL( glBindImageTexture(unit, texture, level, layered, layer, access, format); ) }

//     inline void BindImageTextures( GLuint first, GLsizei count, const GLuint *textures )
//     { VN_GLCALL( glBindImageTextures(first, count, textures); ) }

//     inline void ClearTexImage( GLuint texture, GLint level, GLenum format, GLenum type,
//                             const void *data )
//     { VN_GLCALL( glClearTexImage(texture, level, format, type, data); ) }

//     // ---------------------------------------------------------------------------------------


//     // glDrawXXX -----------------------------------------------------------------------------
//     /**/
//     inline void DrawArrays( GLenum mode, GLint first, GLsizei count )
//     { VN_GLCALL( glDrawArrays(mode, first, count); ) }

//     inline void DrawElements( GLenum mode, GLsizei count, GLenum type, const void *indices )
//     { VN_GLCALL( glDrawElements(mode, count, type, indices); ) }

//     inline void DrawElementsInstanced( GLenum mode, GLsizei count, GLenum type,
//                                     const void *indices, GLsizei instancecount )
//     { VN_GLCALL( glDrawElementsInstanced(mode, count, type, indices, instancecount); ) }

//     inline void MultiDrawElements( GLenum mode, const GLsizei *count, GLenum type,
//                                 const void *const *indices, GLsizei drawcount )
//     { VN_GLCALL( glMultiDrawElements(mode, count, type, indices, drawcount); ) }

//     inline void MultiDrawElementsIndirect( GLenum mode, GLenum type, const void *indirect,
//                                         GLsizei primcount, GLsizei stride )
//     { VN_GLCALL( glMultiDrawElementsIndirect(mode, type, indirect, primcount, stride); ) }
//     // ---------------------------------------------------------------------------------------


//     // glBufferXXX ---------------------------------------------------------------------------
//     /**/
//     inline void BufferData( GLenum target, GLsizeiptr size, const void *data, GLenum usage )
//     { VN_GLCALL( glBufferData(target, size, data, usage); ) }

//     inline void BufferSubData( GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
//     { VN_GLCALL( glBufferSubData(target, offset, size, data); ) }

//     inline void CreateVertexArrays( GLsizei n, GLuint *arrays )
//     { VN_GLCALL( glCreateVertexArrays(n, arrays); ) }

//     inline void CreateBuffers( GLsizei n, GLuint *buffers )
//     { VN_GLCALL( glCreateBuffers(n, buffers); ) }

//     inline GLuint CreateProgram()
//     { VN_GLCALL( return glCreateProgram(); ) }

//     inline GLuint CreateShader( GLenum type )
//     { VN_GLCALL( return glCreateShader(type); ) }

//     inline void ShaderSource( GLuint shader, GLsizei count, const GLchar *const *string,
//                         const GLint *length )
//     { VN_GLCALL( glShaderSource(shader, count, string, length); ) }

//     inline void ShaderBinary( GLsizei count, const GLuint *shaders, GLenum binaryformat,
//                         const void *binary, GLsizei length )
//     { VN_GLCALL( glShaderBinary(count, shaders, binaryformat, binary, length); ) }

//     inline void CompileShader( GLuint shader )
//     { VN_GLCALL( glCompileShader(shader); ) }

//     inline void GetShaderiv( GLuint shader, GLenum pname, GLint *param )
//     { VN_GLCALL( glGetShaderiv(shader, pname, param); ) }

//     inline void GetShaderInfoLog( GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog )
//     { VN_GLCALL( glGetShaderInfoLog(shader, bufSize, length, infoLog); ) }

//     inline void AttachShader( GLuint program, GLuint shader )
//     { VN_GLCALL( glAttachShader(program, shader); ) }

//     inline void DeleteShader( GLuint shader )
//     { VN_GLCALL( glDeleteShader(shader); ) }

//     inline void ValidateProgram( GLuint program )
//     { VN_GLCALL( glValidateProgram(program); ) }

//     inline void LinkProgram( GLuint program )
//     { VN_GLCALL( glLinkProgram(program); ) }

//     inline void NamedBufferData( GLuint buffer, GLsizeiptr size, const void *data, GLenum usage )
//     { VN_GLCALL( glNamedBufferData(buffer, size, data, usage); ) }

//     inline void NamedBufferSubData( GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data )
//     { VN_GLCALL( glNamedBufferSubData(buffer, offset, size, data); ) }

//     inline void NamedBufferStorage( GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags )
//     { VN_GLCALL( glNamedBufferStorage(buffer, size, data, flags); ) }

//     inline void NamedRenderbufferStorage( GLuint renderbuffer, GLenum internalformat, GLsizei width,
//                                     GLsizei height )
//     { VN_GLCALL( glNamedRenderbufferStorage(renderbuffer, internalformat, width, height); ) }

//     inline void NamedFramebufferRenderbuffer( GLuint framebuffer, GLenum attachment,
//                                         GLenum renderbuffertarget, GLuint renderbuffer )
//     { VN_GLCALL( glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer); ) }



//     inline void ObjectLabel(GLenum identifier, GLuint name, GLsizei length, const char *label)
//     { VN_GLCALL( glObjectLabel(identifier, name, length, label); ) }

//     inline void ObjectPtrLabel(void *ptr, GLsizei length, const char *label)
//     { VN_GLCALL( glObjectPtrLabel(ptr, length, label); ) }

//     inline void GetObjectLabel(GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, char *label)
//     { VN_GLCALL( glGetObjectLabel(identifier, name, bufSize, length, label); ) }

//     inline void GetObjectPtrLabel(void *ptr, GLsizei bufSize, GLsizei *length, char *label)
//     { VN_GLCALL( glGetObjectPtrLabel(ptr, bufSize, length, label); ) }



//     inline void *MapBuffer( GLenum target, GLenum access )
//     {
//         void *data;
//         VN_GLCALL( data = glMapBuffer(target, access); )
//         return data;
//     }

//     inline void UnmapBuffer( GLenum target )
//     { VN_GLCALL( glUnmapBuffer(target); ) }

//     inline void *MapNamedBuffer( GLuint buffer, GLenum access )
//     {
//         void *data;
//         VN_GLCALL( data = glMapNamedBuffer(buffer, access); )
//         return data;
//     }

//     inline void UnmapNamedBuffer( GLuint buffer )
//     { VN_GLCALL( glUnmapNamedBuffer(buffer); ) }

//     inline void *MapNamedBufferRange( GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access )
//     {
//         void *data;
//         VN_GLCALL( data = glMapNamedBufferRange(buffer, offset, length, access); )
//         return data;
//     }
//     // ---------------------------------------------------------------------------------------


//     // glActiveXXX ---------------------------------------------------------------------------
//     /**/
//     /**/
//     inline void ActiveTexture( GLenum texture )
//     { VN_GLCALL( glActiveTexture(texture); ) }
//     // ---------------------------------------------------------------------------------------


//     // glTexXXX ------------------------------------------------------------------------------
//     /**/
//     inline void TexImage2D( GLenum target, GLint level, GLint internalformat, GLsizei w, GLsizei h,
//                         GLint border, GLenum format, GLenum type, const void *data )
//     { VN_GLCALL( glTexImage2D(target, level, internalformat, w, h, border, format, type, data); ) }

//     inline void TexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
//                             GLsizei height, GLenum format, GLenum type, const void *pixels )
//     { VN_GLCALL( glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels); ) }

//     inline void TexImage3D( GLenum target, GLint level, GLint internalformat, GLsizei w, GLsizei h,
//                         GLsizei d, GLint border, GLenum format, GLenum type, const void *data )
//     { VN_GLCALL( glTexImage3D(target, level, internalformat, w, h, d, border, format, type, data); ) }

//     inline void TexParameteri( GLenum target, GLenum pname, GLint param )
//     { VN_GLCALL( glTexParameteri(target, pname, param); ) }

//     inline void GetTextureImage( GLuint texture, GLint level, GLenum format, GLenum type,
//                             GLsizei bufSize, void *pixels )
//     { VN_GLCALL( glGetTextureImage(texture, level, format, type, bufSize, pixels); ) }


//     inline GLuint64 GetTextureHandleARB( GLuint texture )
//     {
//         GLuint64 handle;
//         VN_GLCALL( handle = glGetTextureHandleARB(texture); )
//         return handle;
//     }

//     inline void MakeTextureHandleResidentARB( GLuint64 handle )
//     { VN_GLCALL( glMakeTextureHandleResidentARB(handle); ) }

//     inline void MakeTextureHandleNonResidentARB( GLuint64 handle )
//     { VN_GLCALL( glMakeTextureHandleNonResidentARB(handle); ) }

//     inline void GenerateTextureMipmap( GLuint texture )
//     { VN_GLCALL( glGenerateTextureMipmap(texture); ) }

//     inline void GenerateMipmap( GLenum target )
//     { VN_GLCALL( glGenerateMipmap(target); ) }

//     inline void PixelStorei( GLenum pname, GLint param )
//     { VN_GLCALL( glPixelStorei(pname, param); ) }
//     // ---------------------------------------------------------------------------------------------



//     // glTextureXXX
//     // ---------------------------------------------------------------------------------------------
//     inline void TextureStorage2D( GLuint texture, GLsizei levels, GLenum internalformat,
//                                       GLsizei width, GLsizei height )
//     { VN_GLCALL( glTextureStorage2D(texture, levels, internalformat, width, height); ) }

//     inline void TextureSubImage2D( GLenum texture, GLint level, GLint xoffset, GLint yoffset,
//                                        GLsizei width, GLsizei height, GLenum format, GLenum type,
//                                        const void *pixels )
//     {
//         VN_GLCALL(
//             glTextureSubImage2D(
//                 texture, level, xoffset, yoffset, width, height, format, type, pixels
//             );
//         )
//     }

//     inline void TextureStorage3D( GLuint texture, GLsizei levels, GLenum internalformat,
//                                       GLsizei width, GLsizei height, GLsizei depth )
//     { VN_GLCALL( glTextureStorage3D(texture, levels, internalformat, width, height, depth); ) }


//     inline void TextureSubImage3D( GLuint texture, GLint level, GLint xoffset, GLint yoffset,
//                                        GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
//                                        GLenum format, GLenum type, const void *pixels )
//     {
//         VN_GLCALL(
//             glTextureSubImage3D(
//                 texture,
//                 level,
//                 xoffset, yoffset, zoffset,
//                 width, height, depth,
//                 format,
//                 type,
//                 pixels
//             );
//         )
//     }


//     inline void TextureParameteri( GLuint texture, GLenum pname, GLint param )
//     { VN_GLCALL( glTextureParameteri(texture, pname, param); ) }

//     inline void TextureParameterf( GLuint texture, GLenum pname, GLfloat param )
//     { VN_GLCALL( glTextureParameterf(texture, pname, param); ) }
//     // ---------------------------------------------------------------------------------------------


//     // glFramebufferXXX ---------------------------------------------------------------------
//     inline void FramebufferTexture( GLenum target, GLenum attachment, GLuint texture, GLint level )
//     { VN_GLCALL( glFramebufferTexture(target, attachment, texture, level); ) }

//     inline void FramebufferTexture2D( GLenum target, GLenum attachment, GLenum textarget,
//                                           GLuint texture, GLint level )
//     { VN_GLCALL( glFramebufferTexture2D(target, attachment, textarget, texture, level); ) }

//     inline void FramebufferTexture3D( GLenum target, GLenum attachment, GLenum textarget,
//                                           GLuint texture, GLint level, GLint layer )

//     { VN_GLCALL( glFramebufferTexture3D(target, attachment, textarget, texture, level, layer); ) }

//     inline void FramebufferTextureLayer( GLenum target, GLenum attachment, GLuint texture,
//                                              GLint level, GLint layer )
//     { VN_GLCALL( glFramebufferTextureLayer(target, attachment, texture, level, layer); ) }

//     inline void NamedFramebufferTexture( GLuint framebuffer, GLenum attachment, GLuint texture,
//                                              GLint level )
//     { VN_GLCALL( glNamedFramebufferTexture(framebuffer, attachment, texture, level); ) }

//     inline void NamedFramebufferDrawBuffer( GLuint framebuffer, GLenum mode )
//     { VN_GLCALL( glNamedFramebufferDrawBuffer(framebuffer, mode); ) }

//     inline void NamedFramebufferDrawBuffers( GLuint framebuffer, GLsizei n, const GLenum *bufs )
//     { VN_GLCALL( glNamedFramebufferDrawBuffers(framebuffer, n, bufs); ) }

//     inline void NamedFramebufferTextureLayer( GLuint framebuffer, GLenum attachment, GLuint texture,
//                                                   GLint level, GLint layer )
//     { VN_GLCALL( glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer); ) }

//     inline void ClearNamedFramebufferiv(GLuint framebuffer, GLenum buffer,
//                                         GLint drawbuffer, const GLint *value)
//     { VN_GLCALL( glClearNamedFramebufferiv(framebuffer, buffer, drawbuffer, value); ) }

//     inline void ClearNamedFramebufferuiv(GLuint framebuffer, GLenum buffer,
//                                          GLint drawbuffer, const GLuint *value)
//     { VN_GLCALL( glClearNamedFramebufferuiv(framebuffer, buffer, drawbuffer, value); ) }

//     inline void ClearNamedFramebufferfv(GLuint framebuffer, GLenum buffer,
//                                         GLint drawbuffer, const GLfloat *value)
//     { VN_GLCALL( glClearNamedFramebufferfv(framebuffer, buffer, drawbuffer, value); ) }

//     inline void ClearNamedFramebufferfi(GLuint framebuffer, GLenum buffer,
//                                         GLint drawbuffer, GLfloat depth, GLint stencil)
//     { VN_GLCALL( glClearNamedFramebufferfi(framebuffer, buffer, drawbuffer, depth, stencil); ) }

 
//     inline GLenum CheckNamedFramebufferStatus(GLuint framebuffer, GLenum target)
//     {
//         GLenum status;
//         VN_GLCALL( status = glCheckNamedFramebufferStatus(framebuffer, target); )
//         return status;
//     }
//     // ---------------------------------------------------------------------------------------


//     // Uniforms ------------------------------------------------------------------------------
//     /**/
//     inline GLint GetUniformLocation( GLuint program, const char *name )
//     {
//         int32_t data;
//         VN_GLCALL( data = glGetUniformLocation(program, name); )
//         return data;
//     }

//     inline void Uniform1i( GLint loc, int i )
//     { VN_GLCALL( glUniform1i(loc, i); ) }

//     inline void Uniform1f( GLint loc, float f )
//     { VN_GLCALL( glUniform1f(loc, f); ) }

//     inline void Uniform2iv( GLint loc, GLsizei count, const int *value )
//     { VN_GLCALL( glUniform2iv(loc, count, value); ) }

//     inline void Uniform3iv( GLint loc, GLsizei count, const int *value )
//     { VN_GLCALL( glUniform3iv(loc, count, value); ) }

//     inline void Uniform2fv( GLint loc, GLsizei count, float *value )
//     { VN_GLCALL( glUniform2fv(loc, count, value); ) }

//     inline void Uniform3fv( GLint loc, GLsizei count, float *value )
//     { VN_GLCALL( glUniform3fv(loc, count, value); ) }

//     inline void Uniform4fv( GLint loc, GLsizei count, float *value )
//     { VN_GLCALL( glUniform4fv(loc, count, value); ) }

//     inline void UniformMatrix3fv( GLint loc, GLsizei count, GLboolean transpose, float *value )
//     { VN_GLCALL( glUniformMatrix3fv(loc, count, transpose, value); ) }

//     inline void UniformMatrix4fv( GLint loc, GLsizei count, GLboolean transpose, float *value )
//     { VN_GLCALL( glUniformMatrix4fv(loc, count, transpose, value); ) }

//     inline void UniformHandleui64ARB( GLint location, GLuint64 value )
//     { VN_GLCALL( glUniformHandleui64ARB(location, value); ) }
//     // ---------------------------------------------------------------------------------------


//     inline void VertexAttribPointer( GLuint index, GLint size,
//                                 GLenum type, GLboolean normalized,
//                                 GLsizei stride, GLuint offset )
//     {
//         VN_GLCALL(
//             glVertexAttribPointer(
//                 index, size, type, normalized,
//                 stride, reinterpret_cast<void *>(offset)
//             );
//         )
//     }

//     inline void EnableVertexAttribArray( GLuint index )
//     { VN_GLCALL( glEnableVertexAttribArray(index); ) }

//     inline void VertexArrayVertexBuffer( GLuint vaobj, GLuint bindingindex, GLuint buffer,
//                                     GLintptr offset, GLsizei stride )
//     { VN_GLCALL( glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride); ) }

//     inline void VertexArrayElementBuffer( GLuint vaobj, GLuint buffer )
//     { VN_GLCALL( glVertexArrayElementBuffer(vaobj, buffer); ) }

//     inline void EnableVertexArrayAttrib( GLuint vaobj, GLuint index )
//     { VN_GLCALL( glEnableVertexArrayAttrib(vaobj, index); ) }

//     inline void VertexArrayAttribFormat( GLuint vaobj, GLuint attribindex, GLint size, GLenum type,
//                                     GLboolean normalized, GLuint relativeoffset )
//     {
//         VN_GLCALL(
//             glVertexArrayAttribFormat(
//                 vaobj, attribindex, size, type, normalized, relativeoffset
//             );
//         )
//     }

//     inline void VertexArrayAttribBinding( GLuint vaobj, GLuint attribindex, GLuint bindingindex )
//     { VN_GLCALL( glVertexArrayAttribBinding(vaobj, attribindex, bindingindex); ) }

//     inline void UseProgram( GLuint program )
//     { VN_GLCALL( glUseProgram(program); ) }

//     inline void DeleteProgram( GLuint program )
//     { VN_GLCALL( glDeleteProgram(program); ) }

//     inline void ClearColor( float r, float g, float b, float a )
//     { VN_GLCALL( glClearColor(r, g, b, a); ) }

//     inline void Clear( GLbitfield mask )
//     { VN_GLCALL( glClear(mask); ) }

//     inline void Viewport( GLint x, GLint y, GLsizei w, GLsizei h )
//     { VN_GLCALL( glViewport(x, y, w, h); ) }

//     inline void CullFace( GLenum mode )
//     { VN_GLCALL( glCullFace(mode); ) }

//     inline void BlendFunc( GLenum sfactor, GLenum dfactor )
//     { VN_GLCALL( glBlendFunc(sfactor, dfactor); ) }

//     inline void BlendFunci( GLuint buf, GLenum sfactor, GLenum dfactor )
//     { VN_GLCALL( glBlendFunci(buf, sfactor, dfactor); ) }


//     inline void DebugMessageControl(GLenum source, GLenum type, GLenum severity,
//                                     GLsizei count, const GLuint *ids, GLboolean enabled)
//     { VN_GLCALL( glDebugMessageControl(source, type, severity, count, ids, enabled); ) }

//     inline void DebugMessageCallback(GLDEBUGPROC callback, const void *userParam)
//     { VN_GLCALL( glDebugMessageCallback(callback, userParam); ) }

// };




