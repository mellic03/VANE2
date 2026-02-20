#include "vane/game/gamestate.hpp"

using namespace vane;


struct MainMenuState: public GameState
{
    virtual void onUpdate() final
    {
        bool btn_newgame  = false;
        bool btn_continue = false;
        bool btn_settings = false;
        bool btn_exit     = false;

        if (btn_settings)
        {
            // makeTransition<MainMenuSettingsState>();
        }
    }
    virtual void onEntry() final {  }
    virtual void onExit() final {  }
};


struct MainMenuSettingsState: public GameState
{
    virtual void onUpdate() final
    {
        bool btn_return = true;

        if (btn_return)
        {
            // makeTransition<MainMenuState>();
        }
    }
    virtual void onEntry_impl() final {  }
    virtual void onExit_impl() final {  }
};



static void testfn()
{
    GameStateManager gsm;

    gsm.addState<MainMenuState>();
    gsm.addState<MainMenuSettingsState>();

    gsm.transition<MainMenuState>();
    for (int i=0; i<1000; i++)
    {
        gsm.update();
    }

}


