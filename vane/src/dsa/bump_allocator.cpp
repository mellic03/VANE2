#include "vane/bump_allocator.hpp"
#include "vane/align.hpp"
#include "vane/log.hpp"


vane::BumpAllocator::BumpAllocator(size_t cap)
:   mCap(cap), mBase(new uint8_t[mCap]), mEnd(mBase+mCap)
{
    this->reset();
}


void vane::BumpAllocator::reset()
{
    mTop = (uint8_t*)mBase;
}


void *vane::BumpAllocator::alloc(size_t size, size_t alignment)
{
    uint8_t *aligned = util::align_up(mTop, alignment);
    if (aligned + size > mEnd)
    {
        VLOG_FATAL("Out of memory!");
        return nullptr; 
    }
    mTop = aligned + size;
    return aligned;
}

