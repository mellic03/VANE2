#include "event.hpp"


void vane::EventSource::notify(const vane::Object &obj, int32_t event)
{
    EventSink *curr = mHead;
    while (curr != NULL)
    {
        curr->onNotify(obj, event);
        curr = curr->mNext;
    }
}


void vane::EventSource::addObserver(EventSink *obsv)
{
    obsv->mNext = mHead;
    mHead = obsv;
}


void vane::EventSource::removeObserver(EventSink *obsv)
{
    if (mHead == obsv)
    {
        mHead = obsv->mNext;
        obsv->mNext = nullptr;
        return;
    }

    EventSink *curr = mHead;
    while (curr != nullptr)
    {
        if (curr->mNext == obsv)
        {
            curr->mNext = obsv->mNext;
            obsv->mNext = nullptr;
            return;
        }

        curr = curr->mNext;
    }
}


// void vane::EventSource::notify(const vane::Object &obj, int32_t event)
// {
//     for (int i=0; i<mEventSinks.size(); i++)
//     {
//         mEventSinks[i]->onNotify(obj, event);
//     }
// }

// void vane::EventSource::addEventSink(EventSink *obsv)
// {
//     mEventSinks.push(obsv);
// }

// void vane::EventSource::removeEventSink(EventSink *obsv)
// {
//     static inplace_stack<EventSink*, MAX_EventSinkS> temp;

//     for (int i=0; i<mEventSinks.size(); i++)
//     {
//         if (mEventSinks[i] == obsv)
//         {
//             mEventSinks.remove(i);
//             return;
//         }
//     }
// }

