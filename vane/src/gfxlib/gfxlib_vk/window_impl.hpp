
namespace vane
{
    namespace gpu_vk
    {
        struct WindowImpl
        {
            WindowImpl(const char *name, int x, int y, int w, int h) {  }
        };
    }
}


namespace vane
{
    using WindowImplType = gpu_vk::WindowImpl;
}

