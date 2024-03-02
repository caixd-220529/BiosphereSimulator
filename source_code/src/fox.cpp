//
// Created by csyq on 2023/5/16.
// To display Chinese, use:
// system("chcp 65001");
// To output normally in debug mode, use:
// setbuf(stdout,NULL);
//

#include "fox.h"

#include <iostream>
using namespace std;

Fox* Fox::freelist = nullptr;

void Fox::get_prey_ptr_location(int x, int y, std::pair<float, float> &prey_location, Prey *&prey_ptr){
    const vector<Animal*>& temp_ptr_vec = Fox::current_map[x][y].hare_ptr_vec;
    if(!temp_ptr_vec.empty()){
        prey_ptr = dynamic_cast<Prey*>(temp_ptr_vec[rand()%temp_ptr_vec.size()]);
        prey_location = pair<float, float>(prey_ptr->get_x(), prey_ptr->get_y());
    }
}

std::pair<float, float> Fox::calculate_location_without_prey(const float delta) {
    return get_new_position(get_random_direction(delta),
                            get_effected_displacement(this->now_state, delta));
}

void* Fox::operator new(size_t size){
    if(freelist== nullptr){return ::operator new(size);}
    Fox* temp = freelist;
    freelist = freelist->next;
    return temp;
}

void Fox::operator delete(void *ptr) {
    ((Fox*)ptr)->next = freelist;
    freelist = (Fox*)ptr;
}

Fox::Fox(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_dis,
             float active_dis, float calm_loss, float active_loss, float still_loss, float energy_gain, float x,
             float y, int eyesight, int age, int max_age, int reproduce_possibility, float maximum_single_direction_frame,
             float energy_efficiency) : Predator(id, energy, hungry_energy, reproduce_energy, baby_energy, calm_dis,
                                                 active_dis, calm_loss, active_loss, still_loss, energy_gain, x, y,
                                                 eyesight, age, max_age, reproduce_possibility,
                                                 maximum_single_direction_frame, energy_efficiency) {
    next = nullptr;
}
