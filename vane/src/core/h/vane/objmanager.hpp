#pragma once

#include "vane/type.hpp"
#include <memory>
#include <vector>


namespace vane
{
    class ObjectManager
    {
    public:
        class Object
        {
        private:
            friend class vane::ObjectManager;
            bool mBrandOfSacrifice;
            size_t mVaneTypeId;

        public:
            Object(): mBrandOfSacrifice(false), mVaneTypeId(0) {  };
            ~Object() {  };

            virtual void onUpdate() = 0;
        };

        ObjectManager() {  }
        void update();

        template <typename T, typename... Args>
        T   *createObject(Args...);

        void destroyObject(Object*);

    protected:
        std::vector<std::unique_ptr<Object>> mObjects;

    };
}



template <typename T, typename... Args>
inline T *vane::ObjectManager::createObject(Args... args)
{
    static_assert(
        std::is_base_of_v<Object, T>,
        "T must be derivative of vane::ObjectManager::Object"
    );

    T *obj = new T(args...);
       obj->mVaneTypeId = vane_typeid<T>();
    mObjects.push_back(std::unique_ptr<T>(obj));

    return obj;
}


inline void vane::ObjectManager::destroyObject(Object *obj)
{
    obj->mBrandOfSacrifice = true;
}
