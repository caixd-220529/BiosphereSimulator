#ifndef STATE_H
#define STATE_H

#include <Graphics.hpp>

#define MAIN_STATE 0
#define INITIALIZATION_STATE 1
#define GAME_STATE 2

class StateManager;

class State {

public:
    State(sf::RenderWindow *window_ptr, StateManager *state_manager_ptr);
    virtual ~State() = default;
    virtual void update(float delta) = 0;


protected:
    int state = -1;
    sf::RenderWindow *window;
    StateManager *state_manager;
    virtual void eventHandler(sf::Event &event);
};

#include "stateManager.h"


#endif //STATE_H
