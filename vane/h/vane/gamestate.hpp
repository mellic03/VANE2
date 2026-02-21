#pragma once

#include "vane/type.hpp"
#include <vector>


namespace vane
{
    class GameStateManager;
    class GameState;
}


// class GameState
// {
// public:
//     //State transitions
//     virtual bool enter() = 0;
//     virtual bool exit() = 0;

//     //Main loop functions
//     virtual void handleEvent( SDL_Event& e ) = 0;
//     virtual void update() = 0;
//     virtual void render() = 0;

//     //Make sure to call child destructors
//     virtual ~GameState() = default;
// };

class vane::GameState
{
private:
    friend class vane::GameStateManager;
    vane::GameStateManager *m_gsm;
    size_t m_typeid;

public:
    virtual void onUpdate() {  }
    virtual void onEntry() {  }
    virtual void onExit() {  }

    template <typename GameStateType>
    void transition();

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
    :   m_state(nullptr) {  }

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
              obj->m_gsm    = this;
              obj->m_typeid = vane_typeid<T>();
        m_states.push_back(obj);
    }

    template <typename T>
    void transition()
    {
        for (GameState *obj: m_states)
            if (obj->m_typeid == vane_typeid<T>())
                _transition(obj);
        _transition(nullptr);
    }
};



template <typename GameStateType>
inline void vane::GameState::transition()
{
    m_gsm->transition<GameStateType>();
}
