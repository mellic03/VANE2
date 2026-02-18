#pragma once

#include "object.hpp"
#include "vane/dsa/inplace_stack.hpp"


namespace vane
{
    class Observer;
    class Subscriber;
}


class vane::Observer
{
public:
    virtual ~Observer() {  }
    virtual void onNotify(const Object&, int32_t event) = 0;
};


class vane::Subscriber
{
public:
    Subscriber();
    void addObserver(Observer*);
    void removeObserver(Observer*);

protected:
    void notify(const Object&, int32_t event);

private:
    static constexpr size_t MAX_OBSERVERS = 32;
    inplace_stack<Observer*, MAX_OBSERVERS> mObservers;
};


// class Achievements: public Observer
// {
// public:
//     virtual void onNotify(const Object &entity, int32_t event)
//     {
//         switch (event)
//         {
//             case EVENT_ENTITY_FELL:
//                 // unlock(ACHIEVEMENT_FELL_OFF_BRIDGE);
//                 break;
//         // Handle other events, and update heroIsOnBridge_...
//         }
//     }

// private:

//   bool heroIsOnBridge_;
// };