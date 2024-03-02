//
// Created by csyq on 2023/4/29.
// To display Chinese, use:
// system("chcp 65001");
// To output normally in debug mode, use:
// setbuf(stdout,NULL);
//

#ifndef BIOSPHERESIMULATOR_ANIMAL_H
#define BIOSPHERESIMULATOR_ANIMAL_H

#include <cstdint>
#include<vector>
#include<utility>
#include <algorithm>
#include <cmath>
class Animal;

enum terrain_types {
    GRASS = 1,
    WATER = 2,
};

enum season_types{
    SPRING=1,
    SUMMER=2,
    AUTUMN=3,
    WINTER=4,
};

enum weather_types{
    SUNNY=1,
    RAINY=2,
};

enum animal_state_types{
    CALM=1,
    ACTIVE=2,
    STILL=3, // when the animal is eating, use this state
};

struct Node {
    std::vector<Animal*> animals_ptr_vec;
    std::vector<Animal*> cow_ptr_vec;
    std::vector<Animal*> tiger_ptr_vec;
    std::vector<Animal*> hare_ptr_vec;
    std::vector<Animal*> fox_ptr_vec;
    float state;
    float waste_amount; // the amount of waste on the current node, can not overflow the upper bound defined in logic.h
    int eat_grass_number;
    terrain_types terrain;
    std::pair<float, float> center;
    float radius;
    explicit Node(): state(0), waste_amount(0), eat_grass_number(0),terrain(GRASS),radius(0){}
};


class Animal {
private:
    float maximum_single_direction_time;
    float current_direction_accumulated_time;
    static float fluctuating_range_of_parameter;
    std::pair<float, float> last_direction;
    template<class T>
            T fluctuating_single_parameter(T para);
    template<class T>
            T fluctuating_single_parameter_with_upperbound(T para, T upperbound);
    template<class T>
            void fluctuating_a_pair_of_parameters(T& para_1, T& para_2);
protected:
    int64_t id;


    float energy;
    float hungry_energy;  // Animal will try to search food only when its energy is lower than this threshold.
    float reproduce_energy; // Animal will try to reproduce only when its energy is higher than this threshold.
    float baby_energy; // The energy of the descendant of the animal
    float calm_speed;
    float active_speed;
    float calm_energy_loss_speed;
    float active_energy_loss_speed;
    float still_energy_loss_speed;
    float energy_gain_speed;
    float energy_efficiency;

    float x;float y;
    int eyesight;
    bool visible;
    int age;
    int max_age;
    int unit_time_reproduce_possibility; // The possibility that the animal will reproduce is 1/reproduce_possibility
    bool poop_flag;

    static int map_size;
    static season_types now_season;
    static weather_types now_weather;
    animal_state_types now_state;


    Animal(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_speed, float active_speed,
           float calm_loss, float active_loss, float still_loss, float energy_gain,
           float x, float y, int eyesight,int age, int max_age,
           int reproduce_possibility, float maximum_single_direction_frame,
           float energy_efficiency);
    static float calculate_distance(float x1, float y1, float x2, float y2);
    std::pair<float, float> get_random_direction(float delta);
    [[nodiscard]] std::pair<float, float> get_new_position(std::pair<float, float> direction_vec, float displacement) const;

    virtual bool reproduce_decision(float delta) = 0;  // a virtual function to enable dynamic_cast
public:
    void visible_refresh(); // call for all animal at the end of update()
    void age_refresh(float delta); // call for all animal at the end of update()
    static void environment_refresh(season_types now_season_p,
                                    weather_types now_weather_p);// call at the beginning of update()
    [[nodiscard]] bool is_dead() const;
    void kill_animal(); // set visible flag
    [[nodiscard]] float get_energy() const;
    [[nodiscard]] float get_x() const;
    [[nodiscard]] float get_y() const;
    [[nodiscard]] float get_baby_energy() const;
    void set_x(float);
    void set_y(float);
    [[nodiscard]] int64_t get_id() const;
    void set_energy(float new_energy);
    [[nodiscard]] bool get_poop_flag() const;
    [[nodiscard]] float get_active_speed() const; // used for tiger, should not be called by other classes

    static void set_animal_static(int map_size_p, season_types now_season_p,
                                  weather_types now_weather_p, float fluctuating_range_of_parameter_p);
    static std::vector<std::vector<Node>> current_map;
    static std::vector<std::vector<Node>> next_map;
    static std::vector<std::vector<Node>>* current_map_ptr;
    static std::vector<std::vector<Node>>* next_map_ptr;
};

template<class T>
T Animal::fluctuating_single_parameter(T para) {
    // should be called in constructor
    float upper_bound = para * (1+fluctuating_range_of_parameter);
    float lower_bound = para * (1-fluctuating_range_of_parameter);
    return lower_bound + (upper_bound-lower_bound)*(float(rand())/RAND_MAX);
}

template<class T>
T Animal::fluctuating_single_parameter_with_upperbound(T para, T upperbound) {
    float lower_bound = para * (1-fluctuating_range_of_parameter);
    return lower_bound + (upperbound-lower_bound)*(float(rand())/RAND_MAX);
}

template<class T>
void Animal::fluctuating_a_pair_of_parameters(T &para_1, T &para_2) {
    float upper_bound_1 = para_1 * (1+fluctuating_range_of_parameter);
    float upper_bound_2 = para_2 * (1+fluctuating_range_of_parameter);
    float lower_bound_1 = para_1 * (1-fluctuating_range_of_parameter);
    float lower_bound_2 = para_2 * (1-fluctuating_range_of_parameter);
    int random_int = rand();
    para_1 = lower_bound_1 + (upper_bound_1-lower_bound_1)*(random_int/RAND_MAX);
    para_2 = lower_bound_2 + (upper_bound_2-lower_bound_2)*(random_int/RAND_MAX);
}


#endif //BIOSPHERESIMULATOR_ANIMAL_H
