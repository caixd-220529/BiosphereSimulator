//
// Created by csyq on 2023/4/29.
// To display Chinese, use:
// system("chcp 65001");
// To output normally in debug mode, use:
// setbuf(stdout,NULL);
//

#ifndef BIOSPHERESIMULATOR_TIGER_H
#define BIOSPHERESIMULATOR_TIGER_H
#include <map>
#include "predator.h"


class Tiger: public Predator{
protected:
    void get_prey_ptr_location(int x, int y, std::pair<float, float> &prey_location, Prey *&prey_ptr) override;
    std::pair<float, float>calculate_location_without_prey(float delta) override;
private:
    Tiger* next;
    static Tiger* freelist;
    static float aggregation_factor;
public:
    void* operator new(size_t);
    void operator delete(void* ptr);
    static void set_tiger_static(float aggregation_factor_p);

    Tiger(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_dis, float active_dis,
          float calm_loss, float active_loss, float still_loss, float energy_gain,
          float x, float y, int eyesight,int age, int max_age,
          int reproduce_possibility, float maximum_single_direction_frame,
          float energy_efficiency);
};


#endif //BIOSPHERESIMULATOR_TIGER_H
