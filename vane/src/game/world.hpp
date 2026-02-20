#pragma once

#include "vane/game/gameobject.hpp"
#include <vector>

namespace vane
{
    class World;
}


class vane::World
{
public:
    World();
    void update();

private:
    std::vector<GameObject> mObjects;
    // vane::GameObject *mRoot;
};

