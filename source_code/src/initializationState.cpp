#include "initializationState.h"
#include "gameState.h"
using namespace std;

Logic logic_init(int32_t cow_n=10, int32_t tiger_n=10, int32_t fox_n=10, int32_t hare_n=10);

InitializationState::InitializationState(sf::RenderWindow *window, StateManager *state_manager_ptr) : State(window, state_manager_ptr) {
}

void InitializationState::init(int32_t cow_n, int32_t tiger_n, int32_t fox_n, int32_t hare_n, uint32_t map_l, uint32_t map_w) {

    text.setString("Loading...");
    text.setCharacterSize(50);
    text.setPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2);

    this->game_state = std::make_unique<GameState>(window, state_manager);

    loading_thread = std::thread([this](int32_t cow_n, int32_t tiger_n, int32_t fox_n, int32_t hare_n) {
        this->logic = std::make_unique<Logic>(logic_init(cow_n, tiger_n, fox_n, hare_n));
        this->loading = false;
        this->game_state->init(std::move(this->logic));
    }, cow_n, tiger_n, fox_n, hare_n);
    loading_thread.join();
}

void InitializationState::update(float delta) {
    while (loading) {
        window->clear();
        window->draw(text);
        window->display();
    }

    state_manager->switch_state(std::move(game_state));

}

Logic logic_init(int32_t cow_n, int32_t tiger_n, int32_t fox_n, int32_t hare_n) {

    int64_t cow_num = cow_n;
    int64_t tiger_num = tiger_n;
    int64_t fox_num = fox_n;
    int64_t hare_num = hare_n;
    int poop_num = 1;
    int map_size = 1024;
    int grid_size = 32;

    float grass_growth_per_frame = 0.04;
    float waste_loss_per_frame = 0.04;
    int rainy_possibility = 3;
    int max_weather_time_1 = 5;
    int max_weather_time_2 = 4;
    int max_weather_time_3 = 3;
    int max_weather_time_4 = 2;

    int rainy_possibility_1 = 2;
    int rainy_possibility_2 = 3;
    int rainy_possibility_3 = 4;
    int rainy_possibility_4 = 5;


    //Cow parameter
    float energy_cow=1500;
    float hungry_energy_cow = 6000; float reproduce_energy_cow = 4000; float baby_energy_cow = 1500;
    float calm_dis_cow= 30; float active_dis_cow= 30;
    float calm_loss_cow=30; float active_loss_cow = 30; float still_loss_cow = 22.5; float energy_gain_cow = 200;
    int eyesight_cow=100; int age_cow=1000; int max_age_cow=300;
    int reproduce_possibility_cow = 10;
    float maximum_single_direction_frame_cow=5;
    float energy_efficiency_cow= 0.2;

    float eat_speed_cow = 30;
    int select_heap_event_cow = 1;

    //Hare parameter
    float energy_hare = 1000;
    float hungry_energy_hare = 5000; float reproduce_energy_hare = 3500; float baby_energy_hare = 1000;
    float calm_dis_hare = 30; float active_dis_hare = 30;
    float calm_loss_hare = 22.5; float active_loss_hare = 22.5; float still_loss_hare = 15; float energy_gain_hare = 200;
    int eyesight_hare = 70; int age_hare = 500; int max_age_hare = 240;
    int reproduce_possibility_hare = 10;
    float maximum_single_direction_frame_hare = 5;
    float energy_efficiency_hare = 0.2;

    float eat_speed_hare = 30;
    int select_heap_event_hare = 3;

    //Tiger parameter
    float energy_tiger = 2000;
    float hungry_energy_tiger = 6000; float reproduce_energy_tiger = 3500; float baby_energy_tiger = 2000;
    float calm_dis_tiger = 37.5; float active_dis_tiger = 45;
    float calm_loss_tiger = 18; float active_loss_tiger = 69/2; float still_loss_tiger = 12.5; float energy_gain_tiger = 750;
    int eyesight_tiger = 100; int age_tiger = 1000; int max_age_tiger= 350;
    int reproduce_possibility_tiger = 12;
    float maximum_single_direction_frame_tiger = 5;
    float energy_efficiency_tiger = 0.75;

    //Fox parameter
    float energy_fox = 1200;
    float hungry_energy_fox = 4000; float reproduce_energy_fox = 2500; float baby_energy_fox = 1200;
    float calm_dis_fox = 37.5; float active_dis_fox = 90/2;
    float calm_loss_fox = 11.25; float active_loss_fox = 32.5/2; float still_loss_fox = 8.5; float energy_gain_fox = 500;
    int eyesight_fox = 90; int age_fox =  700; int max_age_fox = 300;
    int reproduce_possibility_fox = 12;
    float maximum_single_direction_frame_fox = 5;
    float energy_efficiency_fox = 0.75;

    float scale = 4;//this value should be 1,2,4,8,16...
    map_size /= scale;
    grid_size /= scale;

    calm_dis_cow /= scale;
    calm_dis_fox /= scale;
    calm_dis_hare /= scale;
    calm_dis_tiger /= scale;

    active_dis_cow /= scale;
    active_dis_fox /= scale;
    active_dis_hare /= scale;
    active_dis_tiger /= scale;

    eyesight_cow /= scale;
    eyesight_fox /= scale;
    eyesight_hare /= scale;
    eyesight_tiger /= scale;

    maximum_single_direction_frame_cow /= scale;
    maximum_single_direction_frame_fox /= scale;
    maximum_single_direction_frame_hare /= scale;
    maximum_single_direction_frame_tiger /= scale;

    Logic logic(map_size, grid_size, scale, cow_num, hare_num, tiger_num, fox_num, poop_num, grass_growth_per_frame,
               waste_loss_per_frame, rainy_possibility, max_weather_time_1, max_weather_time_2,
               max_weather_time_3, max_weather_time_4, rainy_possibility_1, rainy_possibility_2,
               rainy_possibility_3, rainy_possibility_4,
            //Cow parameter
               energy_cow, hungry_energy_cow, reproduce_energy_cow, baby_energy_cow, calm_dis_cow, active_dis_cow,
               calm_loss_cow, active_loss_cow, still_loss_cow, energy_gain_cow,
               eyesight_cow, age_cow, max_age_cow,
               reproduce_possibility_cow, maximum_single_direction_frame_cow,
               energy_efficiency_cow, eat_speed_cow, select_heap_event_cow,
            //Hare parameter
               energy_hare, hungry_energy_hare, reproduce_energy_hare, baby_energy_hare, calm_dis_hare, active_dis_hare,
               calm_loss_hare, active_loss_hare, still_loss_hare, energy_gain_hare,
               eyesight_hare, age_hare, max_age_hare,
               reproduce_possibility_hare, maximum_single_direction_frame_hare,
               energy_efficiency_hare, eat_speed_hare, select_heap_event_hare,
            //Tiger parameter
               energy_tiger, hungry_energy_tiger, reproduce_energy_tiger, baby_energy_tiger,
               calm_dis_tiger, active_dis_tiger,
               calm_loss_tiger, active_loss_tiger, still_loss_tiger, energy_gain_tiger,
               eyesight_tiger, age_tiger, max_age_tiger,
               reproduce_possibility_tiger, maximum_single_direction_frame_tiger,
               energy_efficiency_tiger,
            //Fox parameter
               energy_fox, hungry_energy_fox, reproduce_energy_fox, baby_energy_fox,
               calm_dis_fox, active_dis_fox,
               calm_loss_fox, active_loss_fox, still_loss_fox, energy_gain_fox,
               eyesight_fox, age_fox, max_age_fox,
               reproduce_possibility_fox, maximum_single_direction_frame_fox,
               energy_efficiency_fox);

    float sunny_eye_sight_factor_predator = 1;
    float rainy_eye_sight_factor_predator = 0.75;

    float spring_reproduce_factor_predator = 1;
    float summer_reproduce_factor_predator = 2;
    float autumn_reproduce_factor_predator = 5;
    float winter_reproduce_factor_predator = 10;

    float sunny_speed_factor_predator = 1;
    float rainy_speed_factor_predator = 0.75;

    float water_speed_factor_predator = 0.5;

    float sunny_eye_sight_factor_prey = 1;
    float rainy_eye_sight_factor_prey = 0.8;

    float spring_reproduce_factor_prey = 1;
    float summer_reproduce_factor_prey = 2;
    float autumn_reproduce_factor_prey = 5;
    float winter_reproduce_factor_prey = 10;

    float sunny_speed_factor_prey = 1;
    float rainy_speed_factor_prey = 0.7;
    float min_state_prey_eat_grass = 1;
    float max_grass_state = 3;
    int per_grass_energy = 10;
    int run_time_num_prey = 20;
    int living_together_dis_prey = 12;
    float water_speed_factor_prey = 0.7;
    int effected_predator_distance = 30;
    int priority_cow_num = 6;

    per_grass_energy *= scale;
    living_together_dis_prey/=scale;
    effected_predator_distance/=scale;

    float aggregation_factor_tiger = 0.6;

    float cow_priority=1;
    float max_cow_priority_calculate=5;
    int grass_eyesight=5;


    float fluctuating_range_of_parameter_p = 0.1;

    Predator::initial_static_value(sunny_eye_sight_factor_predator, rainy_eye_sight_factor_predator,
                                   spring_reproduce_factor_predator, summer_reproduce_factor_predator,
                                   autumn_reproduce_factor_predator, winter_reproduce_factor_predator,
                                   sunny_speed_factor_predator, rainy_speed_factor_predator,
                                   water_speed_factor_predator);

    Prey::initial_static_value(sunny_eye_sight_factor_prey, rainy_eye_sight_factor_prey,
                               spring_reproduce_factor_prey, summer_reproduce_factor_prey,
                               autumn_reproduce_factor_prey, winter_reproduce_factor_prey,
                               sunny_speed_factor_prey, rainy_speed_factor_prey, per_grass_energy,min_state_prey_eat_grass, max_grass_state,
                               run_time_num_prey,living_together_dis_prey,water_speed_factor_prey,effected_predator_distance,priority_cow_num);

    Tiger::set_tiger_static(aggregation_factor_tiger);

    Cow::cow_initial_static_value(cow_priority, max_cow_priority_calculate, grass_eyesight);
    DistanceNode::search_sequence_generation(eyesight_cow, eyesight_hare, eyesight_tiger, eyesight_fox,
                                             sunny_eye_sight_factor_prey, sunny_eye_sight_factor_predator,
                                             fluctuating_range_of_parameter_p);

    season_types now_sea = SPRING;
    weather_types now_wea = SUNNY;
    Animal::set_animal_static(map_size, now_sea, now_wea, fluctuating_range_of_parameter_p);
    logic.initial_map();
    float water_x = 272;
    float water_y = 240;
    float water_radius = 112;
    water_x /= scale;
    water_y /= scale;
    water_radius /= scale;
    pair<float, float> water_center(water_x,water_y);
    logic.set_water(water_center, water_radius);
    water_center.first = 208/scale;
    water_center.second = 336/scale;
    logic.set_water(water_center, 112/scale);
    water_center.first = 976/scale;
    water_center.second = 720/scale;
    logic.set_water(water_center, 112/scale);
    water_center.first = 976/scale;
    water_center.second = 816/scale;
    logic.set_water(water_center, 112/scale);
    water_center.first = 0;
    water_center.second = 1020/scale;
    logic.set_water(water_center, 144/scale);
    water_center.first = 0;
    water_center.second = 924/scale;
    logic.set_water(water_center, 144/scale);
    logic.initial_animal();
    logic.initial_poop_queue();

    return logic;
}
