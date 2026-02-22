#include "vane/objmanager.hpp"

void vane::ObjectManager::update()
{
    for (int i=mObjects.size()-1; i>=0; i--)
    {
        if (mObjects[i]->mBrandOfSacrifice)
        {
            std::swap(mObjects[i], mObjects.back());
            mObjects.pop_back();
        }
    }

    for (auto &obj: mObjects)
    {
        obj->onUpdate();
    }
}

