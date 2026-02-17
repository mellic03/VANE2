#include "gl.hpp"


void gl::DispatchCompute( GLuint num_groups_x, GLuint num_groups_y, GLuint num_groups_z )
{ IDK_GLCALL( glDispatchCompute(num_groups_x, num_groups_y, num_groups_z); ) }

void gl::MemoryBarrier( GLbitfield barriers )
{ IDK_GLCALL( glMemoryBarrier(barriers); ) }

void gl::GetBooleanv( GLenum pname, GLboolean *data )
{ IDK_GLCALL( glGetBooleanv(pname, data); ) }

void gl::GetDoublev( GLenum pname, GLdouble *data )
{ IDK_GLCALL( glGetDoublev(pname, data); ) }

void gl::GetFloatv( GLenum pname, GLfloat *data )
{ IDK_GLCALL( glGetFloatv(pname, data); ) }

void gl::GetIntegerv( GLenum pname, GLint *data )
{ IDK_GLCALL( glGetIntegerv(pname, data); ) }

void gl::GetInteger64v( GLenum pname, GLint64 *data )
{ IDK_GLCALL( glGetInteger64v(pname, data); ) }

void gl::GetBooleani_v( GLenum target, GLuint index, GLboolean *data )
{ IDK_GLCALL( glGetBooleani_v(target, index, data); ) }

void gl::GetIntegeri_v( GLenum target, GLuint index, GLint *data )
{ IDK_GLCALL( glGetIntegeri_v(target, index, data); ) }

void gl::GetFloati_v( GLenum target, GLuint index, GLfloat *data )
{ IDK_GLCALL( glGetFloati_v(target, index, data); ) }

void gl::GetDoublei_v( GLenum target, GLuint index, GLdouble *data )
{ IDK_GLCALL( glGetDoublei_v(target, index, data); ) }

void gl::GetInteger64i_v( GLenum target, GLuint index, GLint64 *data )
{ IDK_GLCALL( glGetInteger64i_v(target, index, data); ) }

void gl::GetProgramiv( GLuint program, GLenum pname, GLint *param )
{ IDK_GLCALL( glGetProgramiv(program, pname, param); )


}



// glGenXXX ------------------------------------------------------------------------------
/**/
void gl::GenVertexArrays( GLsizei n, GLuint *arrays )
{ IDK_GLCALL( glGenVertexArrays(n, arrays); ) }

void gl::GenBuffers( GLsizei n, GLuint *buffers )
{ IDK_GLCALL( glGenBuffers(n, buffers); ) }

void gl::GenTextures( GLsizei n, GLuint *textures )
{ IDK_GLCALL( glGenTextures(n, textures); ) }

void gl::GenFramebuffers( GLsizei n, GLuint *framebuffers )
{ IDK_GLCALL( glGenFramebuffers(n, framebuffers); ) }

void gl::GenRenderbuffers( GLsizei n, GLuint *renderbuffers )
{ IDK_GLCALL( glGenRenderbuffers(n, renderbuffers); ) }
// ---------------------------------------------------------------------------------------


void gl::CreateTextures( GLenum target, GLsizei n, GLuint *textures )
{ IDK_GLCALL( glCreateTextures(target, n, textures); ) }

void gl::CreateFramebuffers( GLsizei n, GLuint *framebuffers )
{ IDK_GLCALL( glCreateFramebuffers(n, framebuffers); ) }

void gl::CreateRenderbuffers( GLsizei n, GLuint *framebuffers )
{ IDK_GLCALL( glCreateRenderbuffers(n, framebuffers); ) }



// glDeleteXXX ---------------------------------------------------------------------------
/**/
void gl::DeleteVertexArrays( GLsizei n, GLuint *arrays )
{ IDK_GLCALL( glDeleteVertexArrays(n, arrays); ) }

void gl::DeleteBuffers( GLsizei n, GLuint *buffers )
{ IDK_GLCALL( glDeleteBuffers(n, buffers); ) }

void gl::DeleteTextures( GLsizei n, GLuint *textures )
{ IDK_GLCALL( glDeleteTextures(n, textures); ) }

void gl::DeleteFramebuffers( GLsizei n, GLuint *framebuffers )
{ IDK_GLCALL( glDeleteFramebuffers(n, framebuffers); ) }

void gl::DeleteRenderbuffers( GLsizei n, GLuint *renderbuffers )
{ IDK_GLCALL( glDeleteRenderbuffers(n, renderbuffers); ) }
// ---------------------------------------------------------------------------------------


// glBindXXX -----------------------------------------------------------------------------
/**/
void gl::BindVertexArray( GLuint VAO )
{ IDK_GLCALL( glBindVertexArray(VAO); ) }

void gl::BindBuffer( GLenum type, GLuint buf )
{ IDK_GLCALL( glBindBuffer(type, buf); ) }

void gl::BindBufferBase( GLenum target, GLuint index, GLuint buffer )
{ IDK_GLCALL( glBindBufferBase(target, index, buffer); ) }

void gl::BindFramebuffer( GLenum target, GLuint framebuffer )
{ IDK_GLCALL( glBindFramebuffer(target, framebuffer); ) }

void gl::BindRenderbuffer( GLenum target, GLuint renderbuffer )
{ IDK_GLCALL( glBindRenderbuffer(target, renderbuffer); ) }

void gl::BindTexture( GLenum target, GLuint texture )
{ IDK_GLCALL( glBindTexture(target, texture); ) }

void gl::BindTextureUnit( GLuint unit, GLuint texture )
{ IDK_GLCALL( glBindTextureUnit(unit, texture); ) }


void gl::BindImageTexture( GLuint unit, GLuint texture, GLint level, GLboolean layered,
                           GLint layer, GLenum access, GLenum format )
{ IDK_GLCALL( glBindImageTexture(unit, texture, level, layered, layer, access, format); ) }

void gl::BindImageTextures( GLuint first, GLsizei count, const GLuint *textures )
{ IDK_GLCALL( glBindImageTextures(first, count, textures); ) }

void gl::ClearTexImage( GLuint texture, GLint level, GLenum format, GLenum type,
                        const void *data )
{ IDK_GLCALL( glClearTexImage(texture, level, format, type, data); ) }

// ---------------------------------------------------------------------------------------


// glDrawXXX -----------------------------------------------------------------------------
/**/
void gl::DrawArrays( GLenum mode, GLint first, GLsizei count )
{ IDK_GLCALL( glDrawArrays(mode, first, count); ) }

void gl::DrawElements( GLenum mode, GLsizei count, GLenum type, const void *indices )
{ IDK_GLCALL( glDrawElements(mode, count, type, indices); ) }

void gl::DrawElementsInstanced( GLenum mode, GLsizei count, GLenum type,
                                const void *indices, GLsizei instancecount )
{ IDK_GLCALL( glDrawElementsInstanced(mode, count, type, indices, instancecount); ) }

void gl::MultiDrawElements( GLenum mode, const GLsizei *count, GLenum type,
                            const void *const *indices, GLsizei drawcount )
{ IDK_GLCALL( glMultiDrawElements(mode, count, type, indices, drawcount); ) }

void gl::MultiDrawElementsIndirect( GLenum mode, GLenum type, const void *indirect,
                                    GLsizei primcount, GLsizei stride )
{ IDK_GLCALL( glMultiDrawElementsIndirect(mode, type, indirect, primcount, stride); ) }
// ---------------------------------------------------------------------------------------


// glBufferXXX ---------------------------------------------------------------------------
/**/
void gl::BufferData( GLenum target, GLsizeiptr size, const void *data, GLenum usage )
{ IDK_GLCALL( glBufferData(target, size, data, usage); ) }

void gl::BufferSubData( GLenum target, GLintptr offset, GLsizeiptr size, const void *data)
{ IDK_GLCALL( glBufferSubData(target, offset, size, data); ) }

void gl::CreateVertexArrays( GLsizei n, GLuint *arrays )
{ IDK_GLCALL( glCreateVertexArrays(n, arrays); ) }

void gl::CreateBuffers( GLsizei n, GLuint *buffers )
{ IDK_GLCALL( glCreateBuffers(n, buffers); ) }

GLuint gl::CreateProgram()
{ IDK_GLCALL( return glCreateProgram(); ) }

GLuint gl::CreateShader( GLenum type )
{ IDK_GLCALL( return glCreateShader(type); ) }

void gl::ShaderSource( GLuint shader, GLsizei count, const GLchar *const *string,
                       const GLint *length )
{ IDK_GLCALL( glShaderSource(shader, count, string, length); ) }

void gl::ShaderBinary( GLsizei count, const GLuint *shaders, GLenum binaryformat,
                       const void *binary, GLsizei length )
{ IDK_GLCALL( glShaderBinary(count, shaders, binaryformat, binary, length); ) }

void gl::CompileShader( GLuint shader )
{ IDK_GLCALL( glCompileShader(shader); ) }

void gl::GetShaderiv( GLuint shader, GLenum pname, GLint *param )
{ IDK_GLCALL( glGetShaderiv(shader, pname, param); ) }

void gl::GetShaderInfoLog( GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog )
{ IDK_GLCALL( glGetShaderInfoLog(shader, bufSize, length, infoLog); ) }

void gl::AttachShader( GLuint program, GLuint shader )
{ IDK_GLCALL( glAttachShader(program, shader); ) }

void gl::DeleteShader( GLuint shader )
{ IDK_GLCALL( glDeleteShader(shader); ) }

void gl::ValidateProgram( GLuint program )
{ IDK_GLCALL( glValidateProgram(program); ) }

void gl::LinkProgram( GLuint program )
{ IDK_GLCALL( glLinkProgram(program); ) }

void gl::NamedBufferData( GLuint buffer, GLsizeiptr size, const void *data, GLenum usage )
{ IDK_GLCALL( glNamedBufferData(buffer, size, data, usage); ) }

void gl::NamedBufferSubData( GLuint buffer, GLintptr offset, GLsizeiptr size, const void *data )
{ IDK_GLCALL( glNamedBufferSubData(buffer, offset, size, data); ) }

void gl::NamedBufferStorage( GLuint buffer, GLsizeiptr size, const void *data, GLbitfield flags )
{ IDK_GLCALL( glNamedBufferStorage(buffer, size, data, flags); ) }

void gl::NamedRenderbufferStorage( GLuint renderbuffer, GLenum internalformat, GLsizei width,
                                   GLsizei height )
{ IDK_GLCALL( glNamedRenderbufferStorage(renderbuffer, internalformat, width, height); ) }

void gl::NamedFramebufferRenderbuffer( GLuint framebuffer, GLenum attachment,
                                       GLenum renderbuffertarget, GLuint renderbuffer )
{ glNamedFramebufferRenderbuffer(framebuffer, attachment, renderbuffertarget, renderbuffer); }



void *gl::MapBuffer( GLenum target, GLenum access )
{
    void *data;
    IDK_GLCALL( data = glMapBuffer(target, access); )
    return data;
}

void gl::UnmapBuffer( GLenum target )
{
    IDK_GLCALL( glUnmapBuffer(target); )
}

void *gl::MapNamedBuffer( GLuint buffer, GLenum access )
{
    void *data;
    IDK_GLCALL( data = glMapNamedBuffer(buffer, access); )
    return data;
}

void gl::UnmapNamedBuffer( GLuint buffer )
{
    IDK_GLCALL( glUnmapNamedBuffer(buffer); )
}

void *gl::MapNamedBufferRange( GLuint buffer, GLintptr offset, GLsizeiptr length, GLbitfield access )
{
    void *data;
    IDK_GLCALL( data = glMapNamedBufferRange(buffer, offset, length, access); )
    return data;
}
// ---------------------------------------------------------------------------------------


// glActiveXXX ---------------------------------------------------------------------------
/**/
/**/
void
gl::ActiveTexture( GLenum texture )
{
    IDK_GLCALL( glActiveTexture(texture); )
}
// ---------------------------------------------------------------------------------------


// glTexXXX ------------------------------------------------------------------------------
/**/
void
gl::TexImage2D( GLenum target, GLint level, GLint internalformat, GLsizei w, GLsizei h,
                     GLint border, GLenum format, GLenum type, const void *data )
{
    IDK_GLCALL( glTexImage2D(target, level, internalformat, w, h, border, format, type, data); )
}

void
gl::TexSubImage2D( GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width,
                        GLsizei height, GLenum format, GLenum type, const void *pixels )
{
    glTexSubImage2D(target, level, xoffset, yoffset, width, height, format, type, pixels);
}

void
gl::TexImage3D( GLenum target, GLint level, GLint internalformat, GLsizei w, GLsizei h,
                     GLsizei d, GLint border, GLenum format, GLenum type, const void *data )
{
    IDK_GLCALL( glTexImage3D(target, level, internalformat, w, h, d, border, format, type, data); )
}

void
gl::TexParameteri( GLenum target, GLenum pname, GLint param )
{
    IDK_GLCALL( glTexParameteri(target, pname, param); )
}


void
gl::GetTextureImage( GLuint texture, GLint level, GLenum format, GLenum type,
                          GLsizei bufSize, void *pixels )
{
    IDK_GLCALL( glGetTextureImage(texture, level, format, type, bufSize, pixels); )
}


GLuint64
gl::GetTextureHandleARB( GLuint texture )
{
    GLuint64 handle;
    IDK_GLCALL( handle = glGetTextureHandleARB(texture); )

    return handle;
}

void
gl::MakeTextureHandleResidentARB( GLuint64 handle )
{
    IDK_GLCALL( glMakeTextureHandleResidentARB(handle); )
}

void
gl::MakeTextureHandleNonResidentARB( GLuint64 handle )
{
    IDK_GLCALL( glMakeTextureHandleNonResidentARB(handle); )
}


void
gl::GenerateTextureMipmap( GLuint texture )
{
    IDK_GLCALL( glGenerateTextureMipmap(texture); )
}


void
gl::GenerateMipmap( GLenum target )
{
    IDK_GLCALL( glGenerateMipmap(target); )
}

void
gl::PixelStorei( GLenum pname, GLint param )
{
    IDK_GLCALL( glPixelStorei(pname, param); )
}
// ---------------------------------------------------------------------------------------------



// glTextureXXX
// ---------------------------------------------------------------------------------------------
void
gl::TextureStorage2D( GLuint texture, GLsizei levels, GLenum internalformat,
                                GLsizei width, GLsizei height )
{
    IDK_GLCALL( glTextureStorage2D(texture, levels, internalformat, width, height); )
}

void
gl::TextureSubImage2D( GLenum texture, GLint level, GLint xoffset, GLint yoffset,
                                 GLsizei width, GLsizei height, GLenum format, GLenum type,
                                 const void *pixels )
{
    IDK_GLCALL(
        glTextureSubImage2D(texture, level, xoffset, yoffset, width, height, format, type, pixels);
    )
}


void
gl::TextureStorage3D( GLuint texture, GLsizei levels, GLenum internalformat,
                           GLsizei width, GLsizei height, GLsizei depth )
{
    IDK_GLCALL( glTextureStorage3D(texture, levels, internalformat, width, height, depth); )
}


void
gl::TextureSubImage3D( GLuint texture, GLint level, GLint xoffset, GLint yoffset,
                            GLint zoffset, GLsizei width, GLsizei height, GLsizei depth,
                            GLenum format, GLenum type, const void *pixels )
{
    IDK_GLCALL(
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



void
gl::TextureParameteri( GLuint texture, GLenum pname, GLint param )
{
    IDK_GLCALL( glTextureParameteri(texture, pname, param); )
}

void
gl::TextureParameterf( GLuint texture, GLenum pname, GLfloat param )
{
    IDK_GLCALL( glTextureParameterf(texture, pname, param); )
}
// ---------------------------------------------------------------------------------------------



// glFramebufferXXX ---------------------------------------------------------------------
void
gl::FramebufferTexture( GLenum target, GLenum attachment, GLuint texture, GLint level )
{
    IDK_GLCALL( glFramebufferTexture(target, attachment, texture, level); )
}


void
gl::FramebufferTexture2D( GLenum target, GLenum attachment, GLenum textarget,
                               GLuint texture, GLint level )
{
    IDK_GLCALL( glFramebufferTexture2D(target, attachment, textarget, texture, level); )
}


void
gl::FramebufferTexture3D( GLenum target, GLenum attachment, GLenum textarget,
                               GLuint texture, GLint level, GLint layer )

{
    IDK_GLCALL( glFramebufferTexture3D(target, attachment, textarget, texture, level, layer); )
}


void
gl::FramebufferTextureLayer( GLenum target, GLenum attachment, GLuint texture,
                                  GLint level, GLint layer )
{
    IDK_GLCALL( glFramebufferTextureLayer(target, attachment, texture, level, layer); )
}


void
gl::NamedFramebufferTexture( GLuint framebuffer, GLenum attachment, GLuint texture,
                                  GLint level )
{
    IDK_GLCALL( glNamedFramebufferTexture(framebuffer, attachment, texture, level); )
}


void
gl::NamedFramebufferDrawBuffer( GLuint framebuffer, GLenum mode )
{
    IDK_GLCALL( glNamedFramebufferDrawBuffer(framebuffer, mode); )
}


void
gl::NamedFramebufferDrawBuffers( GLuint framebuffer, GLsizei n, const GLenum *bufs )
{
    IDK_GLCALL( glNamedFramebufferDrawBuffers(framebuffer, n, bufs); )
}


void
gl::NamedFramebufferTextureLayer( GLuint framebuffer, GLenum attachment, GLuint texture,
                                       GLint level, GLint layer )
{
    IDK_GLCALL( glNamedFramebufferTextureLayer(framebuffer, attachment, texture, level, layer); )
}
// ---------------------------------------------------------------------------------------



// Uniforms ------------------------------------------------------------------------------
/**/
GLint
gl::GetUniformLocation( GLuint program, const char *name )
{
    return glGetUniformLocation(program, name);
}

void
gl::Uniform1i( GLint loc, int i )
{
    IDK_GLCALL( glUniform1i(loc, i); )
}

void gl::Uniform1f( GLint loc, float f )
{
    IDK_GLCALL( glUniform1f(loc, f); )
}

void
gl::Uniform2iv( GLint loc, GLsizei count, const int *value )
{
    IDK_GLCALL( glUniform2iv(loc, count, value); )
}

void
gl::Uniform3iv( GLint loc, GLsizei count, const int *value )
{
    IDK_GLCALL( glUniform3iv(loc, count, value); )
}

void
gl::Uniform2fv( GLint loc, GLsizei count, float *value )
{
    IDK_GLCALL( glUniform2fv(loc, count, value); )
}

void
gl::Uniform3fv( GLint loc, GLsizei count, float *value )
{
    IDK_GLCALL( glUniform3fv(loc, count, value); )
}

void
gl::Uniform4fv( GLint loc, GLsizei count, float *value )
{
    IDK_GLCALL( glUniform4fv(loc, count, value); )
}

void
gl::UniformMatrix3fv( GLint loc, GLsizei count, GLboolean transpose, float *value )
{
    IDK_GLCALL( glUniformMatrix3fv(loc, count, transpose, value); )
}

void
gl::UniformMatrix4fv( GLint loc, GLsizei count, GLboolean transpose, float *value )
{
    IDK_GLCALL( glUniformMatrix4fv(loc, count, transpose, value); )
}


void
gl::UniformHandleui64ARB( GLint location, GLuint64 value )
{
    IDK_GLCALL( glUniformHandleui64ARB(location, value); )
}
// ---------------------------------------------------------------------------------------


void
gl::VertexAttribPointer( GLuint index, GLint size,
                              GLenum type, GLboolean normalized,
                              GLsizei stride, GLuint offset )
{
    IDK_GLCALL(
        glVertexAttribPointer(
            index, size, type, normalized,
            stride, reinterpret_cast<void *>(offset)
        );
    )
}


void
gl::EnableVertexAttribArray( GLuint index )
{
    IDK_GLCALL( glEnableVertexAttribArray(index); )
}


void
gl::VertexArrayVertexBuffer( GLuint vaobj, GLuint bindingindex, GLuint buffer,
                                  GLintptr offset, GLsizei stride )
{
    IDK_GLCALL( glVertexArrayVertexBuffer(vaobj, bindingindex, buffer, offset, stride); )
}

void
gl::VertexArrayElementBuffer( GLuint vaobj, GLuint buffer )
{
    IDK_GLCALL( glVertexArrayElementBuffer(vaobj, buffer); )
}


void
gl::EnableVertexArrayAttrib( GLuint vaobj, GLuint index )
{
    IDK_GLCALL( glEnableVertexArrayAttrib(vaobj, index); )
}

void
gl::VertexArrayAttribFormat( GLuint vaobj, GLuint attribindex, GLint size, GLenum type,
                                  GLboolean normalized, GLuint relativeoffset )
{
    IDK_GLCALL(
        glVertexArrayAttribFormat(
            vaobj, attribindex, size, type, normalized, relativeoffset
        );
    )
}

void
gl::VertexArrayAttribBinding( GLuint vaobj, GLuint attribindex, GLuint bindingindex )
{
    IDK_GLCALL( glVertexArrayAttribBinding(vaobj, attribindex, bindingindex); )
}


void
gl::UseProgram( GLuint program )
{
    IDK_GLCALL( glUseProgram(program); )
}

void
gl::DeleteProgram( GLuint program )
{
    IDK_GLCALL( glDeleteProgram(program); )
}


void
gl::ClearColor( float r, float g, float b, float a )
{
    IDK_GLCALL( glClearColor(r, g, b, a); )
}


void
gl::Clear( GLbitfield mask )
{
    IDK_GLCALL( glClear(mask); )
}


void
gl::Viewport( GLint x, GLint y, GLsizei w, GLsizei h )
{
    IDK_GLCALL( glViewport(x, y, w, h); )
}


void
gl::CullFace( GLenum mode )
{
    IDK_GLCALL( glCullFace(mode); )
}


void
gl::BlendFunc( GLenum sfactor, GLenum dfactor )
{
    IDK_GLCALL( glBlendFunc(sfactor, dfactor); )
}


void
gl::BlendFunci( GLuint buf, GLenum sfactor, GLenum dfactor )
{
    IDK_GLCALL( glBlendFunci(buf, sfactor, dfactor); )
}
