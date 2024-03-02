#include "hare.h"

Hare* Hare::freelist = nullptr;

Hare::Hare(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_speed, float active_speed,
    float calm_loss, float active_loss, float still_loss, float energy_gain,
    float x, float y, int eyesight, int age, int max_age,
    int reproduce_possibility, float maximum_single_direction,
    float energy_efficiency, float eat_speed, int select_heap_event)
    :Prey(id, energy, hungry_energy, reproduce_energy, baby_energy, calm_speed, active_speed,
        calm_loss, active_loss, still_loss, energy_gain,
        x, y, eyesight, age, max_age,
        reproduce_possibility, maximum_single_direction,
        energy_efficiency, eat_speed, select_heap_event){
}

void Hare::all_event() {
	bool need_update = true;
	if (int(this->previous_x) == int(this->next_x) && int(this->previous_y) == int(this->next_y)) {
		if (this->current_event[0].name == "predator") {
			need_update = false;
			this->update_time += 1;
		}
	}
	if (this->update_time >= 3) {
		this->update_time = 0;
		need_update = true;
	}
	if (this->run_time > 0) {
		need_update = false;
		this->run_time -= 1;
	}
	if (!need_update)
		return;
	int heap_size_num = 0;
	float max_grass_energy = max_grass_state * per_grass_energy;
	int x_current = int(this->x);
	int y_current = int(this->y);
	int effected_eyesight = this->get_effected_eye_sight();
	int predator_num = 0;
	int max_grass = 0;
	for (auto location : DistanceNode::search_sequence) {
		if (location.distance > effected_eyesight) {
			if (heap_size_num == 0) {
				Event E = Event(0, "x", 0, 0);
				this->min_heap.emplace(E);
			}
			return;
		}
		if (predator_num == this->select_heap_event) {
			return;
		}
		int optional_x = x_current + location.x;
		int optional_y = y_current + location.y;
		if (optional_x < 0 || optional_x >= map_size || optional_y < 0 || optional_y >= map_size)
			continue; // invalid position
		if (location.x == 0 && location.y == 0) {
			if (predator_num >= 1)
				continue;
			if (current_map[optional_x][optional_y].state >= min_state_can_eat_grass) {
				max_grass += 1;
				if (predator_num >= 1)
					continue;
				if (heap_size_num < this->select_heap_event) {
					Event Ex = Event(max_grass_energy + 1, "current_position_grass", optional_x, optional_y);
					this->min_heap.emplace(Ex);
					heap_size_num += 1;
				}
				else {
					if (int(min_heap.top().priority) < max_grass_energy + 1)
					{
						this->min_heap.pop();
						Event Ex = Event(max_grass_energy + 1, "current_position_grass", optional_x, optional_y);
						this->min_heap.pop();
						this->min_heap.emplace(Ex);
					}
				}
			}
			continue;
		}
        if(current_map[optional_x][optional_y].tiger_ptr_vec.size() > 0 || current_map[optional_x][optional_y].fox_ptr_vec.size() > 0){
            predator_num += 1;
            if (heap_size_num < this->select_heap_event) {
                Event Ex = Event((max_grass_energy + 2) * (1 + 1 / this->calculate_distance(optional_x, optional_y, this->x, this->y)),
                                 "predator", optional_x, optional_y);
                this->min_heap.emplace(Ex);
                heap_size_num += 1;

            }
            else {
                if (int(min_heap.top().priority) < (max_grass_energy + 2) * (1 + 1 / this->calculate_distance(optional_x, optional_y, this->x, this->y)))
                {
                    this->min_heap.pop();
                    Event Ex = Event((max_grass_energy + 2) * (1 + 1 / this->calculate_distance(optional_x, optional_y, this->x, this->y)),
                                     "predator", optional_x, optional_y);
                    this->min_heap.emplace(Ex);

                }
            }
        }
		if (predator_num >= 1 || max_grass >= 1 || current_map[optional_x][optional_y].state <= min_state_can_eat_grass)
			continue;
		else {
			if (heap_size_num < this->select_heap_event) {
				Event Ex = Event(this->grass_priority(optional_x, optional_y), "grass", optional_x, optional_y);
				this->min_heap.emplace(Ex);
				heap_size_num += 1;
			}
			else {
				if (int(min_heap.top().priority) < this->grass_priority(optional_x, optional_y))
				{
					this->min_heap.pop();
					Event Ex = Event(this->grass_priority(optional_x, optional_y), "grass", optional_x, optional_y);
					this->min_heap.emplace(Ex);
				}
			}
		}
	}
}

void* Hare::operator new(size_t size) {
    if (freelist == nullptr) { return ::operator new(size); }
    Hare* temp = freelist;
    freelist = freelist->next;
    return temp;
}

void Hare::operator delete(void* ptr) {
    ((Hare*)ptr)->next = freelist;
    freelist = (Hare*)ptr;
}


