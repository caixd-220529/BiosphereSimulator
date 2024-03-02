#include "cow.h"

Cow* Cow::freelist = nullptr;
float Cow::cow_priority = PREY_DEFAULT_STATIC_VALUE;
float Cow::max_cow_priority_calculate = PREY_DEFAULT_STATIC_VALUE;
int Cow::grass_eyesight = PREY_DEFAULT_STATIC_VALUE;

Cow::Cow(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_speed, float active_speed,
	float calm_loss, float active_loss, float still_loss, float energy_gain,
	float x, float y, int eyesight, int age, int max_age,
	int reproduce_possibility, float maximum_single_direction,
	float energy_efficiency, float eat_speed, int select_heap_event)
	:Prey(id, energy, hungry_energy, reproduce_energy, baby_energy, calm_speed, active_speed,
		calm_loss, active_loss, still_loss, energy_gain,
		x, y, eyesight, age, max_age,
		reproduce_possibility, maximum_single_direction,
		energy_efficiency, eat_speed, select_heap_event) // Calling the constructor of the parent class
{
	
}

void Cow::all_event() {
	bool need_update = true;
	if (int(this->previous_x) == int(this->next_x) && int(this->previous_y) == int(this->next_y)) {
		if (this->current_event[0].name == "predator") {
			need_update = false;
			this->update_time += 1;
		}
	}
	if (this->update_time >= 3) {
		need_update = false;
		this->update_time = 0;
	}
	if (this->run_time > 0) {
		need_update = false;
		this->run_time -= 1;
	}
	if (!need_update)
		return;
	float max_grass_energy = max_grass_state * per_grass_energy;
	int x_current = int(this->x);
	int y_current = int(this->y);
	int effected_eyesight = this->get_effected_eye_sight();
	int predator_num = 0;
	int heap_size_num = 0;
    int max_grass_with_cow = 0;
	for (auto location : DistanceNode::search_sequence) {
		if (location.distance > effected_eyesight) { 
			if (heap_size_num == 0) {
				Event E = Event(0,"x", 0, 0);
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
			else if (current_map[optional_x][optional_y].state >= min_state_can_eat_grass) {
				if (predator_num >= 1)
					continue;
				if (heap_size_num < this->select_heap_event) {
					Event E = Event(max_grass_energy + 1 + cow_priority * max_cow_priority_calculate,
						"current_position_grass", optional_x, optional_y);
					this->min_heap.emplace(E);
					heap_size_num += 1;
				}
				else {
					if (int(min_heap.top().priority) < (max_grass_energy + 1 + cow_priority * max_cow_priority_calculate))
					{
						this->min_heap.pop();
						Event E = Event(max_grass_energy + 1 + cow_priority * max_cow_priority_calculate,
							"current_position_grass", optional_x, optional_y);
						this->min_heap.emplace(E);
					}
					else
						continue;
				}
			}
			continue;
		}
		bool have_cow = false;
		int have_cow_number = 0;
        if(current_map[optional_x][optional_y].tiger_ptr_vec.size() > 0){
            predator_num += 1;
            // according to the distance between cow and tiger give priority to tiger
            if (heap_size_num < this->select_heap_event) {
                Event E = Event((max_grass_energy + 3 + cow_priority * max_cow_priority_calculate) *
                                (2 + 1 / this->calculate_distance(optional_x, optional_y, this->x, this->y)), "predator", optional_x, optional_y);
                this->min_heap.emplace(E);
                heap_size_num += 1;
            }
            else {
                if (int(min_heap.top().priority) < (max_grass_energy + 3 + cow_priority * max_cow_priority_calculate) *
                                                   (2 + 1 / this->calculate_distance(optional_x, optional_y, this->x, this->y)))
                {
                    this->min_heap.pop();
                    Event E = Event((max_grass_energy + 3 + cow_priority * max_cow_priority_calculate) *
                                    (2 + 1 / this->calculate_distance(optional_x, optional_y, this->x, this->y)), "predator", optional_x, optional_y);
                    min_heap.emplace(E);
                }
            }
        }
        if (predator_num >= 1 || current_map[optional_x][optional_y].state <= min_state_can_eat_grass || max_grass_with_cow >= 1 || have_cow)
            continue;
		const std::vector<Animal*>& temp_ptr_vec = current_map[optional_x][optional_y].cow_ptr_vec;
		for (int k = 0; k < temp_ptr_vec.size(); k++) {
			Animal* animal_ptr = temp_ptr_vec[k];
			Cow* cow_ptr = dynamic_cast<Cow*>(animal_ptr);
			if (cow_ptr != nullptr && !(cow_ptr->is_dead())) {
                if(cow_ptr->priority_cow == 0){
                    have_cow_number++;
                    have_cow = true;
                }
			}
		}
        if (have_cow) {
            if (have_cow_number >= max_cow_priority_calculate)
                have_cow_number = max_cow_priority_calculate;
            for(int k = -grass_eyesight; k <= grass_eyesight;k++){
                for(int l = -grass_eyesight; l <= grass_eyesight;l++){
                    int x_help = optional_x + k;
                    int y_help = optional_y + l;
                    if (x_help < 0 || x_help >= map_size || y_help < 0 || y_help >= map_size)
                        continue; // invalid position
                    if(x_help == int(this->x) && y_help == int(this->y))
                        continue;
                    if (heap_size_num < this->select_heap_event) {
                        Event E = Event((max_grass_energy + 2 + cow_priority * have_cow_number) *
                                        (1 + 1 / this->calculate_distance(x_help, y_help, this->x, this->y)),
                                        "grass_with_cow", x_help, y_help);
                        this->min_heap.emplace(E);
                        heap_size_num += 1;
                        max_grass_with_cow += 1;
                    }
                    else {
                        if (int(min_heap.top().priority) < (max_grass_energy + 2 + cow_priority * have_cow_number) *
                                                           (1 + 1 / this->calculate_distance(x_help, y_help, this->x, this->y)))
                        {
                            this->min_heap.pop();
                            Event E = Event( (max_grass_energy + 2 + cow_priority * have_cow_number) *
                                             (1 + 1 / this->calculate_distance(x_help, y_help, this->x, this->y)),
                                             "grass_with_cow", x_help, y_help);
                            this->min_heap.emplace(E);
                            max_grass_with_cow += 1;
                        }
                    }
                }
            }

        }
        else {
            if (heap_size_num < this->select_heap_event) {
                Event E = Event(this->grass_priority(optional_x, optional_y), "grass", optional_x, optional_y);
                this->min_heap.emplace(E);
                heap_size_num += 1;
            }
            else {
                if (int(min_heap.top().priority) < this->grass_priority(optional_x, optional_y))
                {
                    this->min_heap.pop();
                    Event E = Event(this->grass_priority(optional_x, optional_y), "grass", optional_x, optional_y);
                    this->min_heap.emplace(E);
                }
            }
        }
    }
}



void Cow::cow_initial_static_value(float cow_priority_p, float max_cow_priority_calculate_p, int grass_eyesight_p) {
    cow_priority = cow_priority_p;
    max_cow_priority_calculate = max_cow_priority_calculate_p;
    grass_eyesight = grass_eyesight_p;
}

void* Cow::operator new(size_t size) {
    if (freelist == nullptr) { return ::operator new(size); }
    Cow* temp = freelist;
    freelist = freelist->next;
    return temp;
}

void Cow::operator delete(void* ptr) {
    ((Cow*)ptr)->next = freelist;
    freelist = (Cow*)ptr;
}
