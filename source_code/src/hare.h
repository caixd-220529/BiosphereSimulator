#ifndef BIOSPHERESIMULATOR_HARE_H
#define BIOSPHERESIMULATOR_HARE_H
#include "prey.h"
#include "predator.h"
#include "cow.h"
#include "distancenode.h"

class Hare: public Prey{
private:
    void all_event(); // assign value to current_evevt
    static Hare* freelist;
    Hare* next;
public:
    explicit Hare(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_speed, float active_speed,
        float calm_loss, float active_loss, float still_loss, float energy_gain,
        float x, float y, int eyesight, int age, int max_age,
        int reproduce_possibility, float maximum_single_direction,
        float energy_efficiency, float eat_speed, int select_heap_event);
    void* operator new(size_t);
    void operator delete(void* ptr);
};


#endif //BIOSPHERESIMULATOR_HARE_H
