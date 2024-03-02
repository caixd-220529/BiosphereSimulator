//
// Created by csyq on 2023/4/29.
// To display Chinese, use:
// system("chcp 65001");
// To output normally in debug mode, use:
// setbuf(stdout,NULL);
//
#include "tiger.h"
#include <iostream>
using namespace std;

Tiger* Tiger::freelist = nullptr;
float Tiger::aggregation_factor = PREDATOR_DEFAULT_STATIC_VALUE;

void Tiger::get_prey_ptr_location(int x, int y, std::pair<float, float> &prey_location, Prey *&prey_ptr){
    const vector<Animal*>& temp_cow_ptr_vec = Tiger::current_map[x][y].cow_ptr_vec;
    const vector<Animal*>& temp_hare_ptr_vec = Tiger::current_map[x][y].hare_ptr_vec;
    if(!temp_cow_ptr_vec.empty()){
        prey_ptr = dynamic_cast<Prey*>(temp_cow_ptr_vec[rand()%temp_cow_ptr_vec.size()]);
        prey_location = pair<float, float>(prey_ptr->get_x(), prey_ptr->get_y());
        return;
    }
    if(!temp_hare_ptr_vec.empty()){
        prey_ptr = dynamic_cast<Prey*>(temp_hare_ptr_vec[rand()%temp_hare_ptr_vec.size()]);
        prey_location = pair<float, float>(prey_ptr->get_x(), prey_ptr->get_y());
        return;
    }

}

std::pair<float, float> Tiger::calculate_location_without_prey(const float delta) {
    // move the nearest tiger when nothing to do
    float minimum_distance = -1;
    int effected_eyesight = this->get_effected_eye_sight();
    float aggregation_range = float(effected_eyesight) * Tiger::aggregation_factor;
    pair<float, float> friend_location;
    int x_down = int(this->get_x());int y_down = int(this->get_y());
    for(auto location: DistanceNode::search_sequence){
        //if((i==0&&j==0)||!(i<-aggregation_range||i>aggregation_range||j<-aggregation_range||j>aggregation_range)){continue;}
        if(location.distance<aggregation_range){continue;}
        int optional_x = x_down + location.x;
        int optional_y = y_down + location.y;
        if(optional_x<0||optional_x>=map_size||optional_y<0||optional_y>=map_size){
            continue; // invalid position
        }

        const vector<Animal*>& temp_ptr_vec = current_map[optional_x][optional_y].animals_ptr_vec;
        for(auto animal_ptr : temp_ptr_vec){
            auto* friend_ptr = dynamic_cast<Tiger*>(animal_ptr);
            // check whether the prey exist on the cell
            if(friend_ptr!= nullptr&&!(friend_ptr->is_dead())){
                friend_location = pair<float, float>(friend_ptr->get_x(), friend_ptr->get_y());
                minimum_distance = float(location.distance);
                break; // find a cow then leave the grid immediately to save time
            }
        }
        if(minimum_distance != -1){break;}
    }

    float effected_displacement = get_effected_displacement(this->now_state, delta);
    if(minimum_distance==-1){
        return get_new_position(get_random_direction(delta),
                                effected_displacement);}
    else{
        float unit_x = (friend_location.first - this->get_x())/minimum_distance;
        float unit_y = (friend_location.second- this->get_y())/minimum_distance;
        pair<float, float> direction_vec = pair<float, float>(unit_x, unit_y);
        return get_new_position(direction_vec, effected_displacement);
    }
}

void* Tiger::operator new(size_t size){
    if(freelist== nullptr){return ::operator new(size);}
    Tiger* temp = freelist;
    freelist = freelist->next;
    return temp;
}

void Tiger::operator delete(void *ptr) {
    ((Tiger*)ptr)->next = freelist;
    freelist = (Tiger*)ptr;
}

void Tiger::set_tiger_static(float aggregation_factor_p) {
    Tiger::aggregation_factor = aggregation_factor_p;
}

Tiger::Tiger(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_dis,
             float active_dis, float calm_loss, float active_loss, float still_loss, float energy_gain, float x,
             float y, int eyesight, int age, int max_age, int reproduce_possibility, float maximum_single_direction_frame,
             float energy_efficiency) : Predator(id, energy, hungry_energy, reproduce_energy, baby_energy, calm_dis,
                                                 active_dis, calm_loss, active_loss, still_loss, energy_gain, x, y,
                                                 eyesight, age, max_age, reproduce_possibility,
                                                 maximum_single_direction_frame, energy_efficiency) {
    next = nullptr;
}
