//
// Created by csyq on 2023/5/16.
// To display Chinese, use:
// system("chcp 65001");
// To output normally in debug mode, use:
// setbuf(stdout,NULL);
//

#include "predator.h"
#include <iostream>
using namespace std;

float Predator::sunny_eye_sight_factor = PREDATOR_DEFAULT_STATIC_VALUE;
float Predator::rainy_eye_sight_factor = PREDATOR_DEFAULT_STATIC_VALUE;

float Predator::spring_reproduce_factor = PREDATOR_DEFAULT_STATIC_VALUE;
float Predator::summer_reproduce_factor = PREDATOR_DEFAULT_STATIC_VALUE;
float Predator::autumn_reproduce_factor = PREDATOR_DEFAULT_STATIC_VALUE;
float Predator::winter_reproduce_factor = PREDATOR_DEFAULT_STATIC_VALUE;

float Predator::sunny_speed_factor = PREDATOR_DEFAULT_STATIC_VALUE;
float Predator::rainy_speed_factor = PREDATOR_DEFAULT_STATIC_VALUE;
float Predator::water_speed_factor = PREDATOR_DEFAULT_STATIC_VALUE;

int Predator::get_effected_eye_sight() const {
    switch (Predator::now_weather) {
        case RAINY:
            return this->eyesight*Predator::rainy_eye_sight_factor;
        case SUNNY:
            return this->eyesight*Predator::sunny_eye_sight_factor;
        default:
            cout<<"no implemented weather in Predator::get_effected_eye_sight()";
            system("pause");
            return -1;
    }
}

int Predator::get_effected_reproduce_possibility() const {
    // delta is applied when the function is called
    switch(Predator::now_season){
        case SPRING:
            return int(this->unit_time_reproduce_possibility*Predator::spring_reproduce_factor);
        case SUMMER:
            return int(this->unit_time_reproduce_possibility*Predator::summer_reproduce_factor);
        case AUTUMN:
            return int(this->unit_time_reproduce_possibility*Predator::autumn_reproduce_factor);
        case WINTER:
            return int(this->unit_time_reproduce_possibility*Predator::winter_reproduce_factor);
        default:
            cout<<"no implemented season in Predator::get_effected_reproduce_possibility()";
            system("pause");
            return -1;
    }
}

float Predator::get_effected_displacement(animal_state_types state, float delta) const {
    float displacement;
    if(state==ACTIVE){displacement = this->active_speed * delta;}
    else if(state==CALM){displacement = this->calm_speed * delta;}
    else{cout<<"no implemented animal_state in Tiger::get_effected_displacement()";
        system("pause");}

    if(Animal::current_map[int(this->x)][int(this->y)].terrain==terrain_types::WATER){
        displacement *= Predator::water_speed_factor;
    }

    switch(Predator::now_weather){
        case SUNNY:
            return Predator::sunny_speed_factor*displacement;
        case RAINY:
            return Predator::rainy_speed_factor*displacement;
        default:
            cout<<"no implemented weather in Predator::get_effected_displacement()";
            system("pause");
            return -1;
    }
}

bool Predator::reproduce_decision(float delta) {
//    cout << this->energy - this->reproduce_energy << endl;
    //cout <<"-------------------------"<< this->get_effected_reproduce_possibility()/delta<<endl;
    if(this->energy>this->reproduce_energy&&(rand()%int(this->get_effected_reproduce_possibility()/delta))==0){
        this->is_reproduce = true;
        return true;
    }else{
        return false;
    }
}

void Predator::get_prey_information(int x_down, int y_down, std::pair<float, float> &prey_location, Prey *&prey_ptr) {
    // try to trace the closest cow
    // get the location of the prey
    int effected_eyesight = this->get_effected_eye_sight();
    for(auto location: DistanceNode::search_sequence){
        if(location.distance>effected_eyesight){return;}
        int optional_x = x_down+location.x;
        int optional_y = y_down+location.y;
        if(optional_x<0||optional_x>=map_size||optional_y<0||optional_y>=map_size){
            continue; // invalid position
        }
        get_prey_ptr_location(optional_x, optional_y, prey_location, prey_ptr);
        if(prey_ptr!= nullptr){
            return;
        }
    }
}

std::pair<float, float> Predator::calculate_tracing_end_position(Prey *prey_ptr, std::pair<float, float> now_prey_location,
                                                                 const map<int64_t, std::pair<float, float>> &prey_id_2_next_map_location,
                                                                 const float delta) {
    float distance = calculate_distance(this->get_x(), this->get_y(),
                                        now_prey_location.first, now_prey_location.second);
    float chase_range = this->active_speed * delta - prey_ptr->get_active_speed() * delta;
    if(chase_range<0){
//        cout<<"A kind of predator will not catch a kind of prey in a default situation;"<<endl;
//        system("pause");
    }

    if(distance>chase_range){
        // can not catch a cow
        float prey_x = now_prey_location.first;
        float prey_y = now_prey_location.second;
        // get unit direction vector
        float unit_x = (prey_x - this->get_x())/distance;
        float unit_y = (prey_y - this->get_y())/distance;
        pair<float, float> direction_vec = pair<float, float>(unit_x, unit_y);

        return get_new_position(direction_vec, get_effected_displacement(this->now_state, delta));
    }else{
        // can catch a cow! tiger will just go there
        this->died_prey_ptr = prey_ptr;
        this->left_prey_energy = prey_ptr->get_energy(); // first assume that the tiger can get the whole energy, then do detail calculation in set_extra_information()
        this->need_extra_information = true;
        this->get_extra_information = false;
        try{
            return prey_id_2_next_map_location.at(prey_ptr->get_id());
        }catch(const std::out_of_range& oor){
            cout<<"try to access id: "<< prey_ptr->get_id()<<endl;
            return std::pair<float, float>(this->x, this->y);
        }
    }
}

void Predator::update_information(pair<float, float> &next_position, bool &can_reproduce_flag, bool &need_information,
                                  const map<int64_t, std::pair<float, float>> &prey_id_2_next_map_location, const float delta) {
    this->is_reproduce = false; this->need_extra_information = false;
    // tell the main function whether I need extra information or not at the end of function
    if(this->died_prey_ptr!= nullptr){
        // if the tiger still have something to eat
        this->now_state = STILL;
        can_reproduce_flag = reproduce_decision(delta);
        this->poop_flag = true;
        next_position = pair<float, float>(this->x, this->y);
    }else if(this->energy<hungry_energy){
        // if the tiger is hungry
        this->now_state = ACTIVE;
        Prey* prey_ptr = nullptr;
        pair<float, float> prey_location;
        int x_down = int(this->x);
        int y_down = int(this->y);
        get_prey_information(x_down, y_down, prey_location, prey_ptr);
        if(prey_ptr != nullptr){
            // find a prey and trace it, set died_prey_ptr if necessary
            // can not reproduce or poop
            can_reproduce_flag = false;
            this->poop_flag = false;
            next_position = calculate_tracing_end_position(prey_ptr, prey_location, prey_id_2_next_map_location, delta);
        }else{
            // do not find prey
            // have possibility to reproduce, can poop
            can_reproduce_flag = reproduce_decision(delta);
            this->poop_flag = true;
            next_position = get_new_position(get_random_direction(delta),
                                             get_effected_displacement(this->now_state, delta));
        }
    }else{
        // walk randomly
        this->now_state = CALM;
        can_reproduce_flag = reproduce_decision(delta);
        this->poop_flag = true;
        next_position = calculate_location_without_prey(delta);
    }

    need_information = this->need_extra_information;
}

void Predator::set_extra_information(float percentage) {
    if(!this->need_extra_information){
        cout<<"Why call Predator::set_extra_information()?"<<endl;
        system("pause");
    }
    this->left_prey_energy = this->left_prey_energy * percentage * this->energy_efficiency;
    this->get_extra_information = true;
}

Prey *Predator::get_died_prey_ptr() const {
    return this->died_prey_ptr;
}

float Predator::gain_energy(float delta) {
    if(need_extra_information&&!get_extra_information){
        cout<<"Tiger does not get enough information"<<endl;
        system("pause");
        return -1;
    }else if(need_extra_information&&get_extra_information){
        // tiger get a prey in this frame, but it cannot eat it
        return 0;
    }else if(!need_extra_information&&died_prey_ptr== nullptr) {
        // tiger does not catch a prey, so it cannot get energy
        return 0;
    }else{
        // tiger has something to eat, so it eats it
        if(this->left_prey_energy>energy_gain_speed * delta){
            this->left_prey_energy-=energy_gain_speed * delta;
            return energy_gain_speed * delta;
        }else{
            this->died_prey_ptr = nullptr;
            float result = left_prey_energy;
            this->left_prey_energy = 0;
            return result;
        }
    }
}

float Predator::lose_energy(float delta) {
    float result = 0;
    switch(this->now_state){
        case CALM:
            result = this->calm_energy_loss_speed * delta;
            break;
        case ACTIVE:
            result = this->active_energy_loss_speed * delta;
            break;
        case STILL:
            result = this->still_energy_loss_speed * delta;
            break;
    }
    if(this->is_reproduce){
        result+=this->baby_energy;
        this->is_reproduce = false;
    }
    return result;
}

void Predator::initial_static_value(float sunny_eye_sight_factor_p, float rainy_eye_sight_factor_p,
                                    float spring_reproduce_factor_p, float summer_reproduce_factor_p,
                                    float autumn_reproduce_factor_p, float winter_reproduce_factor_p,
                                    float sunny_speed_factor_p, float rainy_speed_factor_p,
                                    float water_speed_factor_p) {
    /* suggestion:
     * sunny_eye_sight_factor_p = 1;
     * rainy_eye_sight_factor_p < 1;
     * spring_reproduce_factor_p = 1;
     * summer_reproduce_factor_p > 1;
     * autumn_reproduce_factor_p > 1;
     * winter_reproduce_factor_p > 1;
     * sunny_speed_factor_p = 1;
     * rainy_speed_factor_p < 1;
     * water_speed_factor_p < 1;
     */
    sunny_eye_sight_factor = sunny_eye_sight_factor_p;
    rainy_eye_sight_factor = rainy_eye_sight_factor_p;

    spring_reproduce_factor = spring_reproduce_factor_p;
    summer_reproduce_factor = summer_reproduce_factor_p;
    autumn_reproduce_factor = autumn_reproduce_factor_p;
    winter_reproduce_factor = winter_reproduce_factor_p;

    sunny_speed_factor = sunny_speed_factor_p;
    rainy_speed_factor = rainy_speed_factor_p;

    water_speed_factor = water_speed_factor_p;
}

Predator::Predator(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_dis,
             float active_dis, float calm_loss, float active_loss, float still_loss, float energy_gain, float x,
             float y, int eyesight, int age, int max_age, int reproduce_possibility, float maximum_single_direction_frame,
             float energy_efficiency)
        : Animal(id, energy, hungry_energy, reproduce_energy, baby_energy, calm_dis, active_dis, calm_loss, active_loss,
                 still_loss, energy_gain, x, y, eyesight, age, max_age, reproduce_possibility,
                 maximum_single_direction_frame, energy_efficiency) {
    died_prey_ptr = nullptr;
    is_reproduce = false;
    get_extra_information = false;
    need_extra_information = false;
    left_prey_energy = 0;
}


