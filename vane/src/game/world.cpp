#include "vane/world.hpp"


vane::World::World()
{

}


void vane::World::update()
{
    for (GameObject &obj: mObjects)
    {
        obj.update();
    }
}


