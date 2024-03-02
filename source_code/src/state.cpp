#include "state.h"

State::State(sf::RenderWindow *window_ptr, StateManager *state_manager_ptr) {
    window = window_ptr;
    state_manager = state_manager_ptr;
}

void State::eventHandler(sf::Event &event) {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                window->close();
            }
        }
    }
}

