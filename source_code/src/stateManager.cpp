#include "stateManager.h"

StateManager::StateManager(sf::RenderWindow *window_ptr) {
    window = window_ptr;
}


void StateManager::update(float delta) {
    if (current_state != nullptr)
        current_state->update(delta);
}


void StateManager::switch_state(std::unique_ptr<State> state) {
    current_state = std::move(state);
}






