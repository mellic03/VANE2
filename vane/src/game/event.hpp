#pragma once

#include "gameobject.hpp"

namespace vane
{
    class EventEmitter;
    class EventListener;
}


class vane::EventEmitter
{
private:
    vane::EventListener *mHead;
    
protected:
    void notify(const GameObject&, int32_t event);

public:
    EventEmitter(): mHead(nullptr) {  };
    void listen(EventListener*);
    void forget(EventListener*);

};


class vane::EventListener
{
private:
    friend class vane::EventEmitter;
    vane::EventListener *mNext;

public:
    EventListener(): mNext(nullptr) {  }
    virtual ~EventListener() {  }
    virtual void onNotify(const GameObject&, int32_t event) = 0;

};

// class Achievements: public Observer
// {
// public:
//     virtual void onNotify(const GameObject &entity, int32_t event)
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