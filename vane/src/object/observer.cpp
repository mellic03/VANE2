#pragma once

#include "observer.hpp"


vane::Subscriber::Subscriber()
{

}

void vane::Subscriber::notify(const vane::Object &entity, int32_t event)
{
    for (int i=0; i<mObservers.size(); i++)
    {
        mObservers[i]->onNotify(entity, event);
    }
}

void vane::Subscriber::addObserver(Observer *obsv)
{
    mObservers.push(obsv);
}

void vane::Subscriber::removeObserver(Observer *observer)
{
    static inplace_stack<Observer*, MAX_OBSERVERS> temp;

    while (!mObservers.empty())
    {
        auto *ob = mObservers.top(); mObservers.pop();
        if (ob != observer)
            temp.push(ob);
    }

    while (!temp.empty())
    {
        auto *ob = temp.top(); temp.pop();
        mObservers.push(ob);
    }

}

