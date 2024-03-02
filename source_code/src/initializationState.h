#ifndef INITIALIZATIONSTATE_H
#define INITIALIZATIONSTATE_H

#include <thread>
#include "state.h"
#include "logic.h"
#include "gameState.h"


class InitializationState : public State {

public:
    InitializationState(sf::RenderWindow *window, StateManager *state_manager_ptr);
    void init(int32_t cow_n, int32_t tiger_n, int32_t fox_n, int32_t hare_n, uint32_t map_l, uint32_t map_w);
    void update(float delta) override;


private:
    std::unique_ptr<Logic> logic = nullptr;
    std::unique_ptr<GameState> game_state = nullptr;
    bool loading = true;
    sf::Text text;
    std::thread loading_thread;

};


#endif //INITIALIZATIONSTATE_H
