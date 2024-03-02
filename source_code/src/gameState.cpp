#include "gameState.h"
#include <Shader.hpp>
using namespace std;

GameState::GameState(sf::RenderWindow *window_ptr, StateManager *state_manager_ptr) : State(window_ptr, state_manager_ptr) {
    state = GAME_STATE;
    zoomAmount = 1.5f;
}

void GameState::zoomViewAt(sf::Vector2i pixel, sf::RenderWindow *window, float zoom) {
    const sf::Vector2f beforeCoord{ window->mapPixelToCoords(pixel) };
    auto view{ window->getView() };
    view.zoom(zoom);
    window->setView(view);
    const auto afterCoord{ window->mapPixelToCoords(pixel) };
    view.move(beforeCoord - afterCoord);
    window->setView(view);
}

void GameState::eventHandler(sf::Event &event) {
    while (window->pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window->close();
        }
        if (event.type == sf::Event::MouseWheelScrolled) {
            if (event.mouseWheelScroll.delta > 0) {
                zoomViewAt({ event.mouseWheelScroll.x, event.mouseWheelScroll.y }, window, (1.f / zoomAmount));
            }
            else if (event.mouseWheelScroll.delta < 0) {
                zoomViewAt({event.mouseWheelScroll.x, event.mouseWheelScroll.y}, window, zoomAmount);
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                auto view{ window->getView() };
                view.setSize((float)window->getSize().x, (float)window->getSize().y);
                view.setCenter((float)window->getSize().x / 2, (float)window->getSize().y / 2);
                window->setView(view);
            }
        }
    }
}

void GameState::init(std::unique_ptr<Logic> logic_ptr) {
    logic = std::move(logic_ptr);

    try {
        cow_texture.loadFromFile("../res/cow.png");
        tiger_texture.loadFromFile("../res/tiger.png");
        fox_texture.loadFromFile("../res/fox.png");
        hare_texture.loadFromFile("../res/hare.png");
        poop_texture.loadFromFile("../res/poop.png");

        grid_textures[0].loadFromFile("../res/grass_0.png");
        grid_textures[1].loadFromFile("../res/grass_1.png");
        grid_textures[2].loadFromFile("../res/grass_2.png");
        grid_textures[3].loadFromFile("../res/grass_3.png");
        grid_textures[4].loadFromFile("../res/water.png");

    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    /** text */
    font.loadFromFile("../res/timesbd.ttf");

    fps_text.setFont(font);
    fps_text.setString("FPS: ");
    fps_text.setCharacterSize(24);
    fps_text.setPosition({(int) 1024+24, (int) 48});
    fps_text.setFillColor(sf::Color(230, 126, 34));

    season_text.setFont(font);
    season_text.setString("Season: ");
    season_text.setCharacterSize(24);
    season_text.setPosition({(int) 1024+24, (int) 48+128});
    season_text.setFillColor(sf::Color(230, 126, 34));

    weather_text.setFont(font);
    weather_text.setString("Weather: ");
    weather_text.setCharacterSize(24);
    weather_text.setPosition({(int) 1024+24, (int) 48+128*2});
    weather_text.setFillColor(sf::Color(230, 126, 34));

    cow_num_text.setFont(font);
    cow_num_text.setString("Cow Number: ");
    cow_num_text.setCharacterSize(24);
    cow_num_text.setPosition({(int) 1024+24, (int) 48+128*3});
    cow_num_text.setFillColor(sf::Color(230, 126, 34));

    tiger_num_text.setFont(font);
    tiger_num_text.setString("Tiger Number: ");
    tiger_num_text.setCharacterSize(24);
    tiger_num_text.setPosition({(int) 1024+24, (int) 48+128*4});
    tiger_num_text.setFillColor(sf::Color(230, 126, 34));

    fox_num_text.setFont(font);
    fox_num_text.setString("Fox Number: ");
    fox_num_text.setCharacterSize(24);
    fox_num_text.setPosition({(int) 1024+24, (int) 48+128*5});
    fox_num_text.setFillColor(sf::Color(230, 126, 34));

    hare_num_text.setFont(font);
    hare_num_text.setString("Hare Number: ");
    hare_num_text.setCharacterSize(24);
    hare_num_text.setPosition({(int) 1024+24, (int) 48+128*6});
    hare_num_text.setFillColor(sf::Color(230, 126, 34));

    total_num_text.setFont(font);
    total_num_text.setString("Total Number: ");
    total_num_text.setCharacterSize(24);
    total_num_text.setPosition({(int) 1024+24, (int) 48+128*7});
    total_num_text.setFillColor(sf::Color(230, 126, 34));

    info_background_rectangle = sf::RectangleShape({256, 1024});
    info_background_rectangle.setFillColor(sf::Color(46, 204, 113, 128));
    info_background_rectangle.setPosition(1024, 0);

    /** map */
    for  (auto i = 0; i < 32; i++) {
        auto row = std::vector<sf::RectangleShape>();
        for (auto j = 0; j < 32 ; j++) {
            sf::RectangleShape cell;
            cell.setPosition((float)i * 32, (float)j * 32);
            cell.setSize(sf::Vector2f(32, 32));
            cell.setTexture(&grid_textures[0]);
            row.emplace_back(cell);
        }
        map.emplace_back(row);
    }

    /** animal sprites */
    tiger_sprites = {};
    for (auto i = 0; i < 10000; i++) {
        sf::Sprite tiger_sprite;
        tiger_sprite.setTexture(tiger_texture);
        tiger_sprite.setOrigin(60, 60);
        tiger_sprite.setScale(0.25f, 0.25f);
        tiger_sprites.push_back(tiger_sprite);
    }

    cow_sprites = {};
    for (auto i = 0; i < 10000; i++) {
        sf::Sprite cow_sprite;
        cow_sprite.setTexture(cow_texture);
        cow_sprite.setOrigin(60, 60);
        cow_sprite.setScale(0.25f, 0.25f);
        cow_sprites.push_back(cow_sprite);
    }

    fox_sprites = {};
    for (auto i = 0; i < 10000; i++) {
        sf::Sprite fox_sprite;
        fox_sprite.setTexture(fox_texture);
        fox_sprite.setOrigin(60, 60);
        fox_sprite.setScale(0.25f, 0.25f);
        fox_sprites.push_back(fox_sprite);
    }

    hare_sprites = {};
    for (auto i = 0; i < 10000; i++) {
        sf::Sprite hare_sprite;
        hare_sprite.setTexture(hare_texture);
        hare_sprite.setOrigin(60, 60);
        hare_sprite.setScale(0.25f, 0.25f);
        hare_sprites.push_back(hare_sprite);
    }

    poop_sprites = {};
    for (auto i = 0; i < 10000; i++) {
        sf::Sprite poop_sprite;
        poop_sprite.setTexture(poop_texture);
        poop_sprite.setOrigin(60, 60);
        poop_sprite.setScale(0.25f, 0.25f);
        poop_sprites.push_back(poop_sprite);
    }

}

void GameState::update(float delta) {
    sf::Event event{};
    eventHandler(event);

    window->clear(sf::Color::White);

    /** map */
    auto map_matrix = logic->get_grid_map();
    for (auto i = 0; i < map.size(); i++) {
        for (auto j = 0 ; j < map[0].size(); j++) {
            map[i][j].setTexture(&grid_textures[map_matrix[i][j] == -1 ? 4 : map_matrix[i][j]]);
            window->draw(map[i][j]);
        }
    }

    auto poop_positions = logic->get_poop_location_vector();
    for (auto i = 0; i < poop_positions.size(); i++) {
        auto sprite = poop_sprites[i];
        sprite.setPosition(get<0>(poop_positions[i]), get<1>(poop_positions[i]));
        window->draw(sprite);
    }

    auto cow_positions = logic->get_cow_location_vector();
    auto&& cow_num = cow_positions.size();
    for (auto i = 0; i < cow_num; i++) {
        auto sprite = cow_sprites[i];
        sprite.setPosition(get<0>(cow_positions[i]), get<1>(cow_positions[i]));
        window->draw(sprite);
    }

    auto fox_positions = logic->get_fox_location_vector();
    auto&& fox_num = fox_positions.size();
    for (auto i = 0; i < fox_num; i++) {
        auto sprite = fox_sprites[i];
        sprite.setPosition(get<0>(fox_positions[i]), get<1>(fox_positions[i]));
        window->draw(sprite);
    }

    auto hare_positions = logic->get_hare_location_vector();
    auto&& hare_num = hare_positions.size();
    for (auto i = 0; i < hare_num; i++) {
        auto sprite = hare_sprites[i];
        sprite.setPosition(get<0>(hare_positions[i]), get<1>(hare_positions[i]));
        window->draw(sprite);
    }

    auto tiger_positions = logic->get_tiger_location_vector();
    auto&& tiger_num = tiger_positions.size();
    for (auto i = 0; i < tiger_num; i++) {
        auto sprite = tiger_sprites[i];
        sprite.setPosition(get<0>(tiger_positions[i]), get<1>(tiger_positions[i]));
        window->draw(sprite);
    }

    /** text */
    season_text.setString([&]() {
        switch (logic->get_season()) {
            case 1:
                return "Season: Spring";
            case 2:
                return "Season: Summer";
            case 3:
                return "Season: Autumn";
            case 4:
                return "Season: Winter";
            default:
                return "Season: Unknown";
        }
    }());

    weather_text.setString([&]() {
        switch (logic->get_weather()) {
            case 1:
                return "Weather: Sunny";
            case 2:
                return "Weather: Rainy";
            default:
                return "Weather: Unknown";
        }
    }());

    fps_text.setString("FPS: " + std::to_string(static_cast<int>(1 / delta)));
    cow_num_text.setString("Cow Number: " + std::to_string(cow_num));
    tiger_num_text.setString("Tiger Number: " + std::to_string(tiger_num));
    fox_num_text.setString("Fox Number: " + std::to_string(fox_num));
    hare_num_text.setString("Hare Number: " + std::to_string(hare_num));
    total_num_text.setString("Total Number: " + std::to_string(cow_num + tiger_num + fox_num + hare_num));

    window->draw(info_background_rectangle);

    window->draw(fps_text);

    window->draw(season_text);
    window->draw(weather_text);

    window->draw(cow_num_text);
    window->draw(tiger_num_text);
    window->draw(fox_num_text);
    window->draw(hare_num_text);
    window->draw(total_num_text);

    logic->update(delta);

    window->display();
}


