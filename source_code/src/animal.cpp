//
// Created by csyq on 2023/4/29.
// To display Chinese, use:
// system("chcp 65001");
// To output normally in debug mode, use:
// setbuf(stdout,NULL);
//

#include "animal.h"
#include <iostream>
using namespace std;

int Animal::map_size = -1;
float Animal::fluctuating_range_of_parameter = -1;
season_types Animal::now_season = SPRING;
weather_types Animal::now_weather = SUNNY;

std::vector<std::vector<Node>>* Animal::current_map_ptr = nullptr;
std::vector<std::vector<Node>>* Animal::next_map_ptr = nullptr;
std::vector<std::vector<Node>> Animal::current_map = std::vector<std::vector<Node>>(0);
std::vector<std::vector<Node>> Animal::next_map = std::vector<std::vector<Node>>(0);

float Animal::calculate_distance(const float x1, const float y1, const float x2, const float y2) {
    float temp_1 = pow(x1-x2, 2);
    float temp_2 = pow(y1-y2, 2);
    return sqrt(temp_1+temp_2);
}

std::pair<float, float> Animal::get_random_direction(const float delta) {
    if(current_direction_accumulated_time>=maximum_single_direction_time){
        int rand_x = rand();
        int rand_y = rand();
        if(rand_x%2==0){
            rand_x = -rand_x;
        }
        if(rand_y%2==0){
            rand_y = -rand_y;
        }
        float denominator = calculate_distance(rand_x, rand_y,0,0);
        float direction_x = rand_x/denominator;
        float direction_y = rand_y/denominator;
        this->last_direction = std::pair<float, float> (direction_x, direction_y);
        current_direction_accumulated_time = 0;
    }else{
        current_direction_accumulated_time+=delta;
    }
//    cout << "11111111111111111111" << endl;
    return this->last_direction;
}

std::pair<float, float> Animal::get_new_position(const std::pair<float, float> direction_vec, const float displacement) const {
    float unit_x = direction_vec.first;
    float unit_y = direction_vec.second;
    // get displacement
    float move_x = unit_x * displacement;
    float move_y = unit_y * displacement;
    // get new position
    float target_x = this->x + move_x;
    float target_y = this->y + move_y;
//    cout << "unit_x = " << unit_x << " unit_y = " << unit_y << endl;
//    cout << "move_x = " << move_x << " move_y = " << move_y << endl;
//    cout << "this -> x = " << this->x << " this -> y = " << this->y << endl;
//    cout << "target_x = " << target_x << " target_y = " << target_y << endl;
    // bound checking
    if(target_x<0){
        target_x=0;
    }else if(target_x>=map_size){
        target_x = map_size - 1;
    }
    if(target_y<0){
        target_y=0;
    }else if(target_y>=map_size){
        target_y = map_size - 1;
    }

    std::pair<float, float> result(target_x, target_y);
    return result;
}

void Animal::visible_refresh() {
    if(this->age>this->max_age||this->energy<0){
        this->visible = false;
    }
}

bool Animal::is_dead() const {
    return !visible;
}

void Animal::kill_animal() {
    this->visible=false;
}

float Animal::get_energy() const {
    return this->energy;
}

void Animal::set_energy(const float new_energy) {
    this->energy = new_energy;
}

void Animal::age_refresh(const float delta) {
    this->age+=delta;
}

bool Animal::get_poop_flag() const {
    return this->poop_flag;
}

void Animal::environment_refresh(season_types now_season_p, weather_types now_weather_p) {
    Animal::now_season = now_season_p;
    Animal::now_weather = now_weather_p;
}

float Animal::get_x() const {
    return this->x;
}


float Animal::get_baby_energy() const {
    return this->baby_energy;
}

float Animal::get_y() const {
    return this->y;
}


void Animal::set_x(const float x_pos) {
    this->x = x_pos;
}


void Animal::set_y(const float y_pos){
    this->y = y_pos;
}

float Animal::get_active_speed() const {
    return this->active_speed;
}

int64_t Animal::get_id() const{
    return this->id;
}

void Animal::set_animal_static(const int map_size_p, const season_types now_season_p,
                               const weather_types now_weather_p, const float fluctuating_range_of_parameter_p) {
    Animal::map_size = map_size_p;
    Animal::now_season = now_season_p;
    Animal::now_weather = now_weather_p;
    Animal::fluctuating_range_of_parameter = fluctuating_range_of_parameter_p;

}


Animal::Animal(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_dis,
               float active_dis, float calm_loss, float active_loss, float still_loss, float energy_gain, float x,
               float y,int eyesight, int age, int max_age, int reproduce_possibility, float maximum_single_direction_frame,
               float energy_efficiency) {
    this->id = id;
    this->maximum_single_direction_time = fluctuating_single_parameter(maximum_single_direction_frame);
    this->current_direction_accumulated_time = this->maximum_single_direction_time;
    this->visible=true;
    this->now_state = CALM;
    this->energy = energy;
    this->hungry_energy = fluctuating_single_parameter(hungry_energy);
    this->reproduce_energy = fluctuating_single_parameter(reproduce_energy);
    this->baby_energy = baby_energy;

    this->calm_speed= calm_dis;
    this->active_speed = active_dis;
    this->calm_energy_loss_speed = calm_loss;
    this->active_energy_loss_speed = active_loss;
    fluctuating_a_pair_of_parameters(this->calm_speed, this->calm_energy_loss_speed);
    fluctuating_a_pair_of_parameters(this->active_speed, this->active_energy_loss_speed);

    this->still_energy_loss_speed = fluctuating_single_parameter(still_loss);
    this->energy_gain_speed = fluctuating_single_parameter(energy_gain);
    this->x=x;this->y=y;this->eyesight=fluctuating_single_parameter(eyesight);

    this->visible = true;
    this->poop_flag = false;

    this->max_age=fluctuating_single_parameter(max_age);
    this->age = age;this->age = fluctuating_single_parameter_with_upperbound(age, this->max_age);//how to set age = 0 when a animal is reproduced?
    this->unit_time_reproduce_possibility = fluctuating_single_parameter(reproduce_possibility);
    this->energy_efficiency = fluctuating_single_parameter(energy_efficiency);
}

