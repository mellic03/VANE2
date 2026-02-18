#include "world.hpp"
#include "object.hpp"
#include "event.hpp"


class PhysicsSystem: public vane::EventSource
{
public:
    void updateObject(vane::Object &obj)
    {
        bool wasOnSurface = false;
        obj.mAcc.y += 9.81f;
        obj.update();
    
        if (wasOnSurface && !false)
        {
            this->notify(obj, 0);
        }
    }
};



vane::World::World()
{

}

void vane::World::update()
{
    for (auto *obj: mObjects)
    {
        obj->update();
    }
}

