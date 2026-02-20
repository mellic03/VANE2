#pragma once

#include "vane/type.hpp"
#include <vector>


namespace vane
{
    class GameStateManager;
    class GameState;
}


class vane::GameState
{
private:
    friend class vane::GameStateManager;
    vaneid_t m_typeid;

public:
    virtual void onUpdate() {  }
    virtual void onEntry() {  }
    virtual void onExit() {  }

};



class vane::GameStateManager
{
private:
    std::vector<GameState*> m_states;
    GameState *m_state;

    void _transition(GameState *tostate)
    {
        if (m_state) m_state->onExit();
        if (tostate) tostate->onEntry();
        m_state = tostate;
    }

public:
    GameStateManager()
    :   m_state(nullptr)
    {

    }

    void update()
    {
        if (m_state)
        {
            m_state->onUpdate();
        }
    }

    template <typename T>
    void addState()
    {
        auto *obj = static_cast<GameState*>(new T());
              obj->m_typeid = vane_typeid<T>();
        m_states.push_back(obj);
    }

    template <typename T>
    void transition()
    {
        for (GameState *obj: m_states)
        {
            if (obj->m_typeid == vane_typeid<T>())
            {
                _transition(obj);
            }
        }
    
        _transition(nullptr);
    }
};

