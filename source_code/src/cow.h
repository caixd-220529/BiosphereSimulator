#ifndef BIOSPHERESIMULATOR_COW_H
#define BIOSPHERESIMULATOR_COW_H
#include "prey.h"
#include "hare.h"
#include "tiger.h"
#include "distancenode.h"

class Cow: public Prey{
private:
    static float cow_priority; // the priority increase if there have cow around
    static float max_cow_priority_calculate; // the max cow number in priority calculation
    static int grass_eyesight; // within the distance if have cow then grass priority increase, should small

    void all_event(); // assign value to current_evevt
    static Cow* freelist;
    Cow* next;
public:
    explicit Cow(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_spedd, float active_speed,
        float calm_loss, float active_loss, float still_loss, float energy_gain,
        float x, float y, int eyesight, int age, int max_age,
        int reproduce_possibility, float maximum_single_direction,
        float energy_efficiency, float eat_speed, int select_heap_event);
    static void cow_initial_static_value(float cow_priority_p, float max_cow_priority_calculate_p, int grass_eyesight_p);
    void* operator new(size_t);
    void operator delete(void* ptr);
};


#endif //BIOSPHERESIMULATOR_COW_H
