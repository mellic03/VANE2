#include "world.hpp"
#include "event.hpp"


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


