#pragma once

#include <unordered_set>


namespace vane
{
    class World;
    class Object;
    // class GameObject;
}


class vane::World
{
public:
    World();
    void update();

private:
    std::unordered_set<vane::Object*> mObjects;
    // vane::GameObject *mRoot;
};

