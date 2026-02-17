#include "vane/world.hpp"
#include "vane/object.hpp"
#include <vector>

class RootObject: public vane::VaneObject
{
public:
    virtual void update() final;
private:
    std::vector<VaneObject*> mChildren;
};



vane::World::World()
:   mRoot(new RootObject())
{

}

void vane::World::update()
{
    mRoot->update();
}


void RootObject::update()
{
    for (VaneObject *obj: mChildren)
    {
        obj->update();
    }
}