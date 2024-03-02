#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "state.h"
#include "logic.h"

class State;

class GameState : public State {

public:
    explicit GameState(sf::RenderWindow *window_ptr, StateManager *state_manager_ptr);
    void init(std::unique_ptr<Logic> logic_ptr);
    void update(float delta) override;

private:

    static void zoomViewAt(sf::Vector2i pixel, sf::RenderWindow *window, float zoom);
    void eventHandler(sf::Event &event) override;

    float zoomAmount;
    std::unique_ptr<Logic> logic;

    // sfml parameters
    sf::Texture tiger_texture;
    sf::Texture cow_texture;
    sf::Texture fox_texture;
    sf::Texture hare_texture;
    sf::Texture poop_texture;

    sf::Font font;
    sf::Text fps_text;
    sf::Text season_text;
    sf::Text weather_text;
    sf::Text cow_num_text;
    sf::Text tiger_num_text;
    sf::Text fox_num_text;
    sf::Text hare_num_text;
    sf::Text total_num_text;
    sf::RectangleShape info_background_rectangle;

    std::vector<sf::Sprite> tiger_sprites;
    std::vector<sf::Sprite> cow_sprites;
    std::vector<sf::Sprite> fox_sprites;
    std::vector<sf::Sprite> hare_sprites;
    std::vector<sf::Sprite> poop_sprites;

    std::vector<std::vector<sf::RectangleShape>> map;
    std::array<sf::Texture, 5> grid_textures;

};


#endif //GAMESTATE_H
