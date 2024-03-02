#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "state.h"

class StateManager {

public:
    explicit StateManager(sf::RenderWindow *window_ptr);
    ~StateManager() = default;

    void switch_state(std::unique_ptr<State> state);

    void update(float delta);

private:
    std::unique_ptr<State> current_state = nullptr;
    sf::RenderWindow *window;
};


#endif //STATEMANAGER_H
