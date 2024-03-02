#include <cstdlib>
#include <iostream>
#include <random>
#include <Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include "stateManager.h"
#include "initializationState.h"
using namespace std;

int main() {
    system("chcp 65001");
    setbuf(stdout,nullptr);

    sf::RenderWindow window(sf::VideoMode(1024+256, 1024), "Biosphere Simulator",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
//    window.setFramerateLimit(15);

    auto main_background = sf::RectangleShape({1024+256, 1024});
    auto main_background_texture = sf::Texture();
    main_background_texture.loadFromFile("./res/main_background.png");
    main_background.setTexture(&main_background_texture);
    main_background.setPosition(0, 0);

    StateManager manager(&window);
    tgui::GuiSFML tgui{window};
    bool start_flag = false;

    auto v_layout = tgui::VerticalLayout::create();

    auto tiger_h_layout = tgui::HorizontalLayout::create();
        auto tiger_textbox = tgui::EditBox::create();
        auto tiger_prompt = tgui::Label::create("Tiger Number");
            tiger_prompt->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
            tiger_prompt->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
            tiger_prompt->getRenderer()->setTextColor(tgui::Color(243, 156, 18));
            tiger_prompt->setTextSize(30);
        tiger_h_layout->add(tiger_prompt);
        tiger_h_layout->add(tiger_textbox);

    auto cow_h_layout = tgui::HorizontalLayout::create();
        auto cow_textbox = tgui::EditBox::create();
        auto cow_prompt = tgui::Label::create("Cow Number");
            cow_prompt->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
            cow_prompt->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
            cow_prompt->getRenderer()->setTextColor(tgui::Color(243, 156, 18));
            cow_prompt->setTextSize(30);
        cow_h_layout->add(cow_prompt);
        cow_h_layout->add(cow_textbox);

    auto fox_h_layout = tgui::HorizontalLayout::create();
        auto fox_textbox = tgui::EditBox::create();
        auto fox_prompt = tgui::Label::create("Fox Number");
            fox_prompt->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
            fox_prompt->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
            fox_prompt->getRenderer()->setTextColor(tgui::Color(243, 156, 18));
            fox_prompt->setTextSize(30);
        fox_h_layout->add(fox_prompt);
        fox_h_layout->add(fox_textbox);

    auto hare_h_layout = tgui::HorizontalLayout::create();
        auto hare_textbox = tgui::EditBox::create();
        auto hare_prompt = tgui::Label::create("Hare Number");
            hare_prompt->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
            hare_prompt->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
            hare_prompt->getRenderer()->setTextColor(tgui::Color(243, 156, 18));
            hare_prompt->setTextSize(30);
        hare_h_layout->add(hare_prompt);
        hare_h_layout->add(hare_textbox);

    auto start_button = tgui::Button::create("Start");
        start_button->onClick([&]() {
            try {
                auto tiger_n = tiger_textbox->getText().toInt(0);
                auto cow_n = cow_textbox->getText().toInt(0);
                auto fox_n = fox_textbox->getText().toInt(0);
                auto hare_n = hare_textbox->getText().toInt(0);
                auto init_state = std::make_unique<InitializationState>(&window, &manager);
                init_state->init(cow_n, tiger_n, fox_n, hare_n, window.getSize().x, window.getSize().y);
                manager.switch_state(std::move(init_state));
                start_flag = true;
            }
            catch (exception &e) {std::cout << e.what() << std::endl;}
        });
        start_button->setTextSize(30);
        start_button->getRenderer()->setBackgroundColorHover(tgui::Color(230, 126, 34));
        start_button->getRenderer()->setBorderColor(tgui::Color::Transparent);
        start_button->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
        start_button->getRenderer()->setBorderColorHover(tgui::Color::Transparent);
        start_button->getRenderer()->setBorderColorDown(tgui::Color::Transparent);

    v_layout->add(tiger_h_layout);
    v_layout->addSpace(0.2f);
    v_layout->add(cow_h_layout);
    v_layout->addSpace(0.2f);
    v_layout->add(fox_h_layout);
    v_layout->addSpace(0.2f);
    v_layout->add(hare_h_layout);
    v_layout->addSpace(0.2f);
    v_layout->add(start_button);

    v_layout->setSize("50%", "40%");
    v_layout->setOrigin(0.5f, 0.5f);
    v_layout->setPosition("50%", "55%");

    array<tgui::Texture, 11> main_screen_textures = {
        tgui::Texture("./res/tiger.png"),
        tgui::Texture("./res/cow.png"),
        tgui::Texture("./res/fox.png"),
        tgui::Texture("./res/hare.png"),
        tgui::Texture("./res/fearful-face.png"),
        tgui::Texture("./res/grinning-face-with-sweat.png"),
        tgui::Texture("./res/hot-face.png"),
        tgui::Texture("./res/loudly-crying-face.png"),
        tgui::Texture("./res/poop.png"),
        tgui::Texture("./res/pouting-face.png"),
        tgui::Texture("./res/smiling-face-with-halo.png")
    };

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, main_screen_textures.size()-1);

    auto top_left_button = tgui::Button::create();
        top_left_button->getRenderer()->setTexture(main_screen_textures[0]);
        top_left_button->setPosition("15%", "25%");

    auto top_right_button = tgui::Button::create();
        top_right_button->getRenderer()->setTexture(main_screen_textures[1]);
        top_right_button->setPosition("85%", "25%");

    auto bottom_left_button = tgui::Button::create();
        bottom_left_button->getRenderer()->setTexture(main_screen_textures[2]);
        bottom_left_button->setPosition("15%", "85%");

    auto bottom_right_button = tgui::Button::create();
        bottom_right_button->getRenderer()->setTexture(main_screen_textures[3]);
        bottom_right_button->setPosition("85%", "85%");

    array<shared_ptr<tgui::Button>, 4> decorate_buttons = {
        top_left_button,
        top_right_button,
        bottom_left_button,
        bottom_right_button
    };

    for (auto& button : decorate_buttons) {
        button->setOrigin(0.5f, 0.5f);
        button->setSize(120, 120);
        button->getRenderer()->setBorderColor(tgui::Color::Transparent);
        button->getRenderer()->setBorderColorFocused(tgui::Color::Transparent);
        button->getRenderer()->setBorderColorHover(tgui::Color::Transparent);
        button->getRenderer()->setBorderColorDown(tgui::Color::Transparent);
        button->onPress([&]() {
            button->getRenderer()->setTexture(main_screen_textures[dis(gen)]);
        });
    }

    tgui.add(top_left_button);
    tgui.add(top_right_button);
    tgui.add(bottom_left_button);
    tgui.add(bottom_right_button);

    tgui.add(v_layout);

    while (!start_flag) {
        sf::Event event{};
        while (window.pollEvent(event)) {
            tgui.handleEvent(event);
            if (event.type == sf::Event::Closed) {
                window.close();
                return EXIT_SUCCESS;
            }
        }
        window.clear();
        window.draw(main_background);
        tgui.draw();
        window.display();
    }

    sf::Clock clock;
    clock.restart();
    while (window.isOpen()) {
        auto delta = clock.restart().asSeconds();
        manager.update(delta);
    }

    return EXIT_SUCCESS;
}


