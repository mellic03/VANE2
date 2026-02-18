#pragma once

namespace vane
{
    class World;
    class GameObject;
}


class vane::World
{
public:
    World();
    void update();

private:
    vane::GameObject *mRoot;
};

