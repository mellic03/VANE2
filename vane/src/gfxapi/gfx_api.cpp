#include "gfxapi/gfxapi_gl.hpp"
#include "vane/log.hpp"

using namespace vane::gfxapi;

extern void vaneEnableOpenGlDebugOutput();


RenderEngine::RenderEngine(const char *name, int width, int height)
{
    if (false == SDL_Init(SDL_INIT_VIDEO))
        VLOG_FATAL("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,  24))
        VLOG_ERROR("{}", SDL_GetError());

    if (!SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8))
        VLOG_ERROR("{}", SDL_GetError());

    m_win = createWindow(name, width, height);
    // m_win->init(name, width, height);
}


void RenderEngine::onUpdate()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_EVENT_QUIT)
        {
            // this->shutdown();
            return;
        }

        m_win->onEvent(e);
    }

    m_win->_makeCurrent();

    // gl::BindVertexArray(mVAO);
    // // gl::UseProgram(mQuadProgram->mId);
    // gl::DrawArrays(GL_TRIANGLES, 0, 3);
}




RenderProgramPtr RenderEngine::createRenderProgram(const char *vertpath, const char *fragpath)
{
    m_render_programs.push_back(
        std::make_unique<RenderProgram>(vertpath, fragpath)
    );
}


ComputeProgramPtr RenderEngine::createComputeProgram(const char *filepath)
{

}






void RenderEngine::drawWindow(Window *win, Framebuffer &fb)
{

}


void RenderEngine::drawFramebuffer(Framebuffer &fb, RenderGraph &rg)
{
    _drawFramebuffer(fb, rg.rootNode());
}

void RenderEngine::_drawFramebuffer(Framebuffer &fb, RenderNode *node)
{
    if (0) // culling condition
    {
        return;
    }

    for (auto *child: node->children)
    {
        _drawFramebuffer(fb, child);
    }
}







RenderEngine::Window *RenderEngine::createWindow(const char *name, int w, int h)
{
    m_windows.push_back(std::make_unique<Window>(name, w, h));
    return m_windows.back().get();
}

