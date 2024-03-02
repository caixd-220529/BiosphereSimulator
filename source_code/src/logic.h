//
// Created by csyq on 2023/4/29.
// To display Chinese, use:
// system("chcp 65001");
// To output normally in debug mode, use:
// setbuf(stdout,NULL);
//

#ifndef BIOSPHERESIMULATOR_LOGIC_H
#define BIOSPHERESIMULATOR_LOGIC_H

#include "animal.h"
#include "cow.h"
#include "tiger.h"
#include "predator.h"
#include "prey.h"
#include "hare.h"
#include "fox.h"
#include <stack>
#include <queue>
#include <list>
#include <time.h>

struct poop_node
{
    Animal* animal_ptr;
    int64_t id;
    poop_node* next_pp_node;
};

class Logic {
private:
    int map_size;
    int grid_size;
    float scale;
    int64_t id_allocate;
    int64_t cow_num;
    int64_t tiger_num;
    int64_t hare_num;
    int64_t fox_num;
    int poop_num;
    std::queue<Animal*> poop_queue; //:<
    std::list<Prey*> prey_list;
    std::list<Predator*> predator_list;

    std::vector<Cow*> cow_vector;//store cows' pointer
    std::vector<Tiger*> tiger_vector;//store tigers' pointer
    std::vector<std::pair<float, float>> poop_location_vector;
    std::vector<std::pair<float, float>> cow_location_vector;
    std::vector<std::pair<float, float>> tiger_location_vector;
    std::vector<std::pair<float, float>> hare_location_vector;
    std::vector<std::pair<float, float>> fox_location_vector;
    std::stack<Predator*> need_extra_predator;
    std::map<int64_t, std::pair<float, float>> prey_id_2_next_map_location;
    std::queue<Prey*> new_born_prey;
    std::queue<Predator*> new_born_predator;
    poop_node* poop_head;
    poop_node* poop_tail;
    std::vector<std::vector<int>> grid_map;

    float weather_timer;
    float season_timer;
    season_types now_season;
    weather_types now_weather;

    float grass_growth_per_frame;
    float waste_loss_per_frame;
    int rainy_possibility;

    // 1 is spring,2 is summer,3 is fall,4 is winter
    int rainy_possibility_1; // the possibility of rainy in spring. if the value is 3,then the possibility is 1/3.
    float weather_time_1; 
    int rainy_possibility_2;
    float weather_time_2;
    int rainy_possibility_3;
    float weather_time_3; 
    int rainy_possibility_4;
    float weather_time_4;
    int max_weather_time_1; // the max rainy time in spring
    int max_weather_time_2;
    int max_weather_time_3;
    int max_weather_time_4;


    const int MIN_STATE = 0;
    const int MAX_STATE = 3;
    const float GROW_PER_FRAME = 0.075;
    const float WASTE_PER_ANIMAL = 0.5;
    const float WASTE_LOST_PER_FRAME = 0.075;
    const float GROW_WITH_WASTE = 0.075;
    const float GROW_WITH_RAIN = 0.0375;
    const float MAX_WEATHER_TIMER = 5;
    const float MAX_SEASON_TIMER = 25;

    //Cow parameter
    float energy_cow;
    float hungry_energy_cow; float reproduce_energy_cow; float baby_energy_cow; 
    float calm_dis_cow; float active_dis_cow;
    float calm_loss_cow; float active_loss_cow; float still_loss_cow; float energy_gain_cow;
    int eyesight_cow; int age_cow; int max_age_cow;
    int reproduce_possibility_cow;
    int maximum_single_direction_frame_cow;
    float energy_efficiency_cow;

    float eat_speed_cow;
    int select_heap_event_cow;

    //Hare parameter
    float energy_hare;
    float hungry_energy_hare; float reproduce_energy_hare; float baby_energy_hare;
    float calm_dis_hare; float active_dis_hare;
    float calm_loss_hare; float active_loss_hare; float still_loss_hare; float energy_gain_hare;
    int eyesight_hare; int age_hare; int max_age_hare;
    int reproduce_possibility_hare;
    int maximum_single_direction_frame_hare;
    float energy_efficiency_hare;

    float eat_speed_hare;
    int select_heap_event_hare;

    //Tiger parameter
    float energy_tiger;
    float hungry_energy_tiger; float reproduce_energy_tiger; float baby_energy_tiger;
    float calm_dis_tiger; float active_dis_tiger;
    float calm_loss_tiger; float active_loss_tiger; float still_loss_tiger; float energy_gain_tiger;
    int eyesight_tiger; int age_tiger; int max_age_tiger;
    int reproduce_possibility_tiger;
    int maximum_single_direction_frame_tiger;
    float energy_efficiency_tiger;

    //Fox parameter
    float energy_fox;
    float hungry_energy_fox; float reproduce_energy_fox; float baby_energy_fox;
    float calm_dis_fox; float active_dis_fox;
    float calm_loss_fox; float active_loss_fox; float still_loss_fox; float energy_gain_fox;
    int eyesight_fox; int age_fox; int max_age_fox;
    int reproduce_possibility_fox;
    int maximum_single_direction_frame_fox;
    float energy_efficiency_fox;

public:
    Logic(int map_size,int grid_size, float scale, int64_t cow_num,int64_t hare_num, int64_t tiger_num, int64_t fox_num, int poop_numm, float grass_growth_per_frame,
    float waste_loss_per_frame, int rainy_possibility, int max_weather_time_1, int max_weather_time_2,
    int max_weather_time_3,int max_weather_time_4,int rainy_possibility_1,int rainy_possibility_2,
    int rainy_possibility_3,int rainy_possibility_4,
        //Cow parameter
        float energy_cow, float hungry_energy_cow, float reproduce_energy_cow, float baby_energy_cow, float calm_dis_cow, float active_dis_cow,
        float calm_loss_cow, float active_loss_cow, float still_loss_cow, float energy_gain_cow,
        int eyesight_cow, int age_cow, int max_age_cow,
        int reproduce_possibility_cow, int maximum_single_direction_frame_cow,
        float energy_efficiency_cow, float eat_speed_cow, int select_heap_event_cow,
        //Hare parameter
        float energy_hare, float hungry_energy_hare, float reproduce_energy_hare, float baby_energy_hare, float calm_dis_hare, float active_dis_hare,
        float calm_loss_hare, float active_loss_hare, float still_loss_hare, float energy_gain_hare,
        int eyesight_hare, int age_hare, int max_age_hare,
        int reproduce_possibility_hare, int maximum_single_direction_frame_hare,
        float energy_efficiency_hare, float eat_speed_hare, int select_heap_event_hare,
        //Tiger parameter
        float energy_tiger, float hungry_energy_tiger, float reproduce_energy_tiger, float baby_energy_tiger,
        float calm_dis_tiger, float active_dis_tiger,
        float calm_loss_tiger, float active_loss_tiger, float still_loss_tiger, float energy_gain_tiger,
        int eyesight_tiger, int age_tiger, int max_age_tiger,
        int reproduce_possibility_tiger, int maximum_single_direction_frame_tiger,
        float energy_efficiency_tiger,
        //Fox parameter
        float energy_fox, float hungry_energy_fox, float reproduce_energy_fox, float baby_energy_fox,
        float calm_dis_fox, float active_dis_fox,
        float calm_loss_fox, float active_loss_fox, float still_loss_fox, float energy_gain_fox,
        int eyesight_fox, int age_fox, int max_age_fox,
        int reproduce_possibility_fox, int maximum_single_direction_frame_fox,
        float energy_efficiency_fox);
    void initial_map();
    void initial_animal();
    void initial_grid();
    void initial_poop_queue();
    void update(float delta);  //:<
    void update_map(Animal* animal); //:)
    void update_poop_list(float delta);
    //void update_cow_location_vector();
    //void update_tiger_location_vector();

    //std::vector<std::pair<float, float>> get_state_location_vector(int state);
    void prey_delete_help(std::list<Prey*>::iterator& prey_ite);
    void predator_delete_help(std::list<Predator*>::iterator& predator_ite);

    void check_cow_dead(Cow*& cow, int index);
    void check_tiger_dead(Tiger* tiger, int index);
    void reproduce_prey(Prey* prey_ptr);
    void reproduce_predator(Predator* predator_ptr);
    void update_animal_vector();
    std::vector<std::pair<float, float>> get_poop_location_vector();
    std::vector<std::pair<float, float>> get_cow_location_vector();
    std::vector<std::pair<float, float>> get_tiger_location_vector();
    std::vector<std::pair<float, float>> get_hare_location_vector();
    std::vector<std::pair<float, float>> get_fox_location_vector();
    int get_season();
    int get_weather();
    int64_t get_cow_num();
    int64_t get_hare_num();
    int64_t get_tiger_num();
    int64_t get_fox_num();
    std::vector<std::vector<int>> get_grid_map();
    void update_map_state(float delta);
    void update_grid_map();
    void clear_next_map();
    void weather_change(float delta);
    void season_change(float delta);
    void set_water(std::pair<float,float> center,float radius);

};


#endif //BIOSPHERESIMULATOR_LOGIC_H
