#include "vane/memory.hpp"
#include "vane/align.hpp"
#include <cstdlib>

struct vane::ThreadMemoryRegion
{
    void  *base;
    size_t size;
};

static vane::ThreadMemoryRegion tmr_base_[32];
static vane::ThreadMemoryRegion *tmr_top_ = tmr_base_;

vane::ThreadMemoryRegion const *vane::createThreadMemory(size_t size)
{
    auto *desc = tmr_top_++;
    desc->base = util::align_up(std::malloc(size+16), 16);
    desc->size = size;
    return desc;
}




template <typename T>
class ThreadMemoryWriter
{
private:
    vane::ThreadMemoryRegion &tmr_;

public:
    ThreadMemoryWriter(vane::ThreadMemoryRegion const *tmr)
    :   tmr_(*tmr)
    {

    }

};


template <typename T>
class ThreadMemoryReader
{
private:
    vane::ThreadMemoryRegion &tmr_;

public:
    ThreadMemoryReader(vane::ThreadMemoryRegion const *tmr)
    :   tmr_(*tmr)
    {

    }

};

