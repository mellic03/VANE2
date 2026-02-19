#include "event.hpp"


void vane::EventEmitter::notify(const GameObject &obj, int32_t event)
{
    EventListener *curr = mHead;
    while (curr != NULL)
    {
        curr->onNotify(obj, event);
        curr = curr->mNext;
    }
}


void vane::EventEmitter::listen(EventListener *el)
{
    el->mNext = mHead;
    mHead = el;
}


void vane::EventEmitter::forget(EventListener *el)
{
    if (mHead == el)
    {
        mHead = el->mNext;
        el->mNext = nullptr;
        return;
    }

    EventListener *curr = mHead;
    while (curr != nullptr)
    {
        if (curr->mNext == el)
        {
            curr->mNext = el->mNext;
            el->mNext = nullptr;
            return;
        }

        curr = curr->mNext;
    }
}


// void vane::EventEmitter::notify(const vane::Object &obj, int32_t event)
// {
//     for (int i=0; i<mEventSinks.size(); i++)
//     {
//         mEventSinks[i]->onNotify(obj, event);
//     }
// }

// void vane::EventEmitter::addEventSink(EventListener *listener)
// {
//     mEventSinks.push(listener);
// }

// void vane::EventEmitter::removeEventSink(EventListener *listener)
// {
//     static inplace_stack<EventListener*, MAX_EventSinkS> temp;

//     for (int i=0; i<mEventSinks.size(); i++)
//     {
//         if (mEventSinks[i] == listener)
//         {
//             mEventSinks.remove(i);
//             return;
//         }
//     }
// }

