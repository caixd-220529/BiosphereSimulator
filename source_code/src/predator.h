//
// Created by csyq on 2023/5/16.
// To display Chinese, use:
// system("chcp 65001");
// To output normally in debug mode, use:
// setbuf(stdout,NULL);
//

#ifndef BIOSPHERESIMULATOR_PREDATOR_H
#define BIOSPHERESIMULATOR_PREDATOR_H
#include <map>
#include "animal.h"
#include "prey.h"
#include "distancenode.h"

const float PREDATOR_DEFAULT_STATIC_VALUE = -1;


class Predator: public Animal{
protected:

    Prey* died_prey_ptr;
    float left_prey_energy;
    bool is_reproduce;  // used for energy calculation
    bool get_extra_information;
    bool need_extra_information;  // initial as false in constructor

    // environment
    static float sunny_eye_sight_factor;
    static float rainy_eye_sight_factor;

    static float spring_reproduce_factor;
    static float summer_reproduce_factor;
    static float autumn_reproduce_factor;
    static float winter_reproduce_factor;

    static float sunny_speed_factor;
    static float rainy_speed_factor;

    static float water_speed_factor;

    [[nodiscard]] int get_effected_eye_sight() const;
    [[nodiscard]] int get_effected_reproduce_possibility() const;
    [[nodiscard]] float get_effected_displacement(animal_state_types state, float delta) const;
    virtual std::pair<float, float>calculate_location_without_prey(float delta)=0;
    virtual void get_prey_ptr_location(int x, int y, std::pair<float, float> &prey_location, Prey *&prey_ptr)=0;
    bool reproduce_decision(float delta) override;
    void get_prey_information(int x_down, int y_down, std::pair<float, float>& prey_location, Prey*& prey_ptr);
    std::pair<float, float> calculate_tracing_end_position(Prey* prey_ptr, std::pair<float, float> now_prey_location,
                                                           const std::map<int64_t, std::pair<float, float>>& prey_id_2_next_map_location, float delta);
public:
    void update_information(std::pair<float, float> &next_position, bool &can_reproduce_flag, bool &need_information,
                            const std::map<int64_t, std::pair<float, float>>& prey_id_2_next_map_location, float delta);
    void set_extra_information(float percentage);
    [[nodiscard]] Prey* get_died_prey_ptr() const;
    float gain_energy(float delta);
    float lose_energy(float delta);

    static void initial_static_value(float sunny_eye_sight_factor_p, float rainy_eye_sight_factor_p,
                                     float spring_reproduce_factor_p,float summer_reproduce_factor_p,
                                     float autumn_reproduce_factor_p,float winter_reproduce_factor_p,
                                     float sunny_speed_factor_p, float rainy_speed_factor_p,
                                     float water_speed_factor_p); // call for one time

    Predator(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_speed, float active_speed,
    float calm_loss, float active_loss, float still_loss, float energy_gain,
    float x, float y, int eyesight,int age, int max_age,
    int reproduce_possibility, float maximum_single_direction,
    float energy_efficiency);
};


#endif //BIOSPHERESIMULATOR_PREDATOR_H
