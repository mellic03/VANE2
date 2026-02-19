#pragma once

#include <cstddef>

namespace vane
{
    class iComponent;
    class Container;
}


class vane::Container
{
public:
    Container() {  }
    virtual ~Container() {  };
    virtual void update();
    virtual void sendmsg(iComponent *origin, const void *msg, size_t msgsz);

    template <typename T>
    void sendmsg(iComponent *origin, const T &msg)
    {
        sendmsg(origin, (const void*)msg, sizeof(T));
    }

    template <typename T>
    inline void addComponent()
    {
        static_assert(
            std::is_base_of_v<iComponent, T>,
            "T must be derivative of iComponent"
        );

        auto *comp = static_cast<iComponent*>(new T(this));
        comp->mNext = mComponentList.head;
        mComponentList.head = comp;
    }

private:
    struct iComponentList
    {
        iComponent *head;

        struct iterator
        {
            iComponent *mC;

            iterator(iComponent *C);
            iterator(const iterator &I);

            iterator &operator++();
            iterator operator++(int);

            bool operator== (const iterator &rhs ) { return mC == rhs.mC; };
            bool operator!= (const iterator &rhs ) { return mC != rhs.mC; };
            iComponent *&operator*() { return mC; };
        };

        iterator begin() { return iterator(this->head); };
        iterator end()   { return iterator(nullptr); };
    };

    iComponentList mComponentList;
};
