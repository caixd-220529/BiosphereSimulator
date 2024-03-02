#ifndef BIOSPHERESIMULATOR_PREY_H
#define BIOSPHERESIMULATOR_PREY_H
#include "animal.h"
#include <string>
#include <vector>
#include <math.h>
#include <string>
#include <iostream>
#include <Windows.h> 
#include <queue>
#include <stdio.h>
class Prey;

struct Event {
    float priority; // distinct event priority
    std::string name; // event name
    //position
    int event_x;
    int event_y;
    Event* next;
    //initial function
    explicit Event(float priority, std::string name, int event_x, int event_y)
        : priority(priority), name(name), event_x(event_x), event_y(event_y)
    {
    }
};

struct cmp
{
    bool operator()(Event a, Event b)
    {
        return a.priority > b.priority;
    }
};


const float PREY_DEFAULT_STATIC_VALUE = -1;

class Prey: public Animal{
protected:
    float next_x;
    float next_y;
    float previous_x;
    float previous_y;
    int current_event_size;
    int update_time;
    int run_time;
    float init_x, init_y;
    std::priority_queue<Event, std::vector<Event>, cmp> min_heap;
    std::vector<Event> current_event; //store event for prey
    float eat_speed; // eat how many per grass at a frame
    int select_heap_event; // select how many event in maxheap
    bool can_eat_grass; // decide whether cow can eat grass
    int be_prey_number;

    static float min_state_can_eat_grass; // the minimal map state that cow can eat grass
    static float max_grass_state; // the max grass state in map
    static int per_grass_energy; // the energy of per grass
    // environment
    static float sunny_eye_sight_factor;
    static float rainy_eye_sight_factor;

    static float spring_reproduce_factor;
    static float summer_reproduce_factor;
    static float autumn_reproduce_factor;
    static float winter_reproduce_factor;

    static float sunny_speed_factor;
    static float rainy_speed_factor;

    static int run_time_num;
    static int living_together_dis;
    static int effected_predator_distance;

    static float water_speed_factor;
    static int priority_cow_num;
    int priority_cow;

    [[nodiscard]] int get_effected_eye_sight() const; // get the effected eye sight in different whether
    [[nodiscard]] int get_effected_reproduce_possibility() const; // get the effected reproduce possibility in different season
    [[nodiscard]] float get_effected_displacement_factor(float delta) const; // get the effected displacement factor in different whether
    bool reproduce_decision(float delta) override; // get the reproduce decision
    float energy_of_map(int, int); // return the energy of grass on map[x][y]
    void heapsort(std::vector<Event>&, int); //heapsort for current_event
    void max_heapify(std::vector<Event>&, int, int); //build max_heap for heapsort
    float grass_priority(int, int); // get the priority of per map
    void minheapsort();
    virtual void all_event() = 0; // assign value to current_evevt
    std::pair<float, float> prey_get_new_position(std::pair<float, float> direction_vec, float displacement);
    
    bool is_reproduce;  // used for energy calculation

public:
    explicit Prey(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_speed, float active_speed,
        float calm_loss, float active_loss, float still_loss, float energy_gain,
        float x, float y, int eyesight, int age, int max_age,
        int reproduce_possibility, float maximum_single_direction,
        float energy_efficiency, float eat_speed, int select_heap_event);
    // update position and can_reproduce_flag per frame
    void update_information(std::pair<float, float>& next_position, bool& can_reproduce_flag, float delta);
    float lose_energy(float delta);
    float gain_energy(float& consume_grass_state, float delta);
    static void initial_static_value(float sunny_eye_sight_factor_p, float rainy_eye_sight_factor_p,
        float spring_reproduce_factor_p, float summer_reproduce_factor_p,
        float autumn_reproduce_factor_p, float winter_reproduce_factor_p,
        float sunny_speed_factor_p, float rainy_speed_factor_p,
        int per_grass_energy_p, float min_state_can_eat_grass_p, float max_grass_state_p,
        int run_time_num_p,int living_together_p, float water_speed_factor_p,
        int effected_predator_distance_p,int priority_cow_num_p);
    int get_prey_number();
    void add_prey_number();
    bool get_can_eat_grass();
    float get_eat_speed();
    
};


#endif //BIOSPHERESIMULATOR_PREY_H
