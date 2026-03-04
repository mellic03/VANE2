#pragma once

#include <cstddef>
#include <glm/glm.hpp>


namespace vane::gfxapi::gl_storage
{
    struct ubo_camera_t
    {
        glm::vec4 mouse;
        glm::vec4 rgba;
        glm::mat4 T;
        glm::mat4 V;
        glm::mat4 P;
    };


    static constexpr size_t SSBO_PARTICLE_COUNT = 128*128;
    struct ssbo_particles_t
    {
        glm::vec4 pos[SSBO_PARTICLE_COUNT];
        glm::vec4 vel[SSBO_PARTICLE_COUNT];
    };

    // layout (binding = 2, std430) readonly
    // buffer SSBO_2
    // {
    //     ssbo_particles_t ssIn;
    // };

    // layout (binding = 3, std430) writeonly
    // buffer SSBO_3
    // {
    //     ssbo_particles_t ssOut;
    // };

    // struct SsboParticleWriter: public SsboWrapperT<gl_storage::ssbo_particles_t>
    // {
    //     static constexpr size_t BINDING_INDEX = 2;
    // };


};

