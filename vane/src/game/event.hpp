#pragma once

#include "gameobject.hpp"

namespace vane
{
    class EventSource;
    class EventSink;
}


class vane::EventSource
{
private:
    vane::EventSink *mHead;
    
protected:
    void notify(const GameObject&, int32_t event);

public:
    EventSource(): mHead(nullptr) {  };
    void addObserver(EventSink*);
    void removeObserver(EventSink*);

};


class vane::EventSink
{
private:
    friend class vane::EventSource;
    vane::EventSink *mNext;

public:
    EventSink(): mNext(nullptr) {  }
    virtual ~EventSink() {  }
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