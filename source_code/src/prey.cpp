#include "prey.h"

int Prey::per_grass_energy = PREY_DEFAULT_STATIC_VALUE;
float Prey::max_grass_state = PREY_DEFAULT_STATIC_VALUE;
float Prey::min_state_can_eat_grass = PREY_DEFAULT_STATIC_VALUE;

float Prey::sunny_eye_sight_factor = PREY_DEFAULT_STATIC_VALUE;
float Prey::rainy_eye_sight_factor = PREY_DEFAULT_STATIC_VALUE;

float Prey::spring_reproduce_factor = PREY_DEFAULT_STATIC_VALUE;
float Prey::summer_reproduce_factor = PREY_DEFAULT_STATIC_VALUE;
float Prey::autumn_reproduce_factor = PREY_DEFAULT_STATIC_VALUE;
float Prey::winter_reproduce_factor = PREY_DEFAULT_STATIC_VALUE;

float Prey::sunny_speed_factor = PREY_DEFAULT_STATIC_VALUE;
float Prey::rainy_speed_factor = PREY_DEFAULT_STATIC_VALUE;
int Prey::run_time_num = 3;
int Prey::living_together_dis = 6;
int Prey::effected_predator_distance = PREY_DEFAULT_STATIC_VALUE;
float Prey::water_speed_factor = PREY_DEFAULT_STATIC_VALUE;
int Prey::priority_cow_num = PREY_DEFAULT_STATIC_VALUE;

Prey::Prey(int64_t id, float energy, float hungry_energy, float reproduce_energy, float baby_energy, float calm_speed, float active_speed,
    float calm_loss, float active_loss, float still_loss, float energy_gain,
    float x, float y, int eyesight, int age, int max_age,
    int reproduce_possibility, float maximum_single_direction,
    float energy_efficiency, float eat_speed, int select_heap_event)
    :Animal(id, energy, hungry_energy, reproduce_energy, baby_energy, calm_speed, active_speed,
        calm_loss, active_loss, still_loss, energy_gain,
        x, y, eyesight, age, max_age,
        reproduce_possibility, maximum_single_direction,
        energy_efficiency)
    {
        
        this->run_time = 0;
        this->update_time = 0;
        this->current_event_size = 0;
        this->eat_speed = eat_speed;
        this->select_heap_event = select_heap_event;
        this->be_prey_number = 0;// herbivore is not caught by tigers when initialize
        this->can_eat_grass = false;
        this->is_reproduce = false;
        this->poop_flag = false;
        this->current_event.clear();
        this->next_x = 0;
        this->next_y = 0;
        this->previous_x = this->x;
        this->previous_y = this->y;
        this->init_x = this->x;
        this->init_y = this->y;
        priority_cow = rand() % priority_cow_num;

        for (int i = 0; i < this->select_heap_event; i++) {
            Event E1 = Event(0, "x", 0, 0);
            this->current_event.emplace_back(E1);
        }
    }

void Prey::initial_static_value(float sunny_eye_sight_factor_p, float rainy_eye_sight_factor_p,
    float spring_reproduce_factor_p, float summer_reproduce_factor_p,
    float autumn_reproduce_factor_p, float winter_reproduce_factor_p,
    float sunny_speed_factor_p, float rainy_speed_factor_p,
    int per_grass_energy_p, float min_state_can_eat_grass_p, float max_grass_state_p,
    int run_time_num_p,int living_together_dis_p, float water_speed_factor_p,
    int effected_predator_distance_p,int priority_cow_num_p) {

    sunny_eye_sight_factor = sunny_eye_sight_factor_p;
    rainy_eye_sight_factor = rainy_eye_sight_factor_p;

    spring_reproduce_factor = spring_reproduce_factor_p;
    summer_reproduce_factor = summer_reproduce_factor_p;
    autumn_reproduce_factor = autumn_reproduce_factor_p;
    winter_reproduce_factor = winter_reproduce_factor_p;

    sunny_speed_factor = sunny_speed_factor_p;
    rainy_speed_factor = rainy_speed_factor_p;

    per_grass_energy = per_grass_energy_p;
    min_state_can_eat_grass = min_state_can_eat_grass_p;
    max_grass_state = max_grass_state_p;

    run_time_num = run_time_num_p;
    living_together_dis = living_together_dis_p;
    water_speed_factor = water_speed_factor_p;

    effected_predator_distance = effected_predator_distance_p;
    priority_cow_num = priority_cow_num_p;
}

float Prey::get_effected_displacement_factor(float delta) const {
    float dis = 1;
    if(this->now_state==ACTIVE){dis = this->active_speed * delta;}
    else if(this->now_state==CALM){dis = this->calm_speed * delta;}
    if(current_map[int(this->x)][int(this->y)].terrain == WATER)
        dis *= water_speed_factor;
    switch (now_weather) {
    case SUNNY:
        return sunny_speed_factor * dis;
    case RAINY:
        return rainy_speed_factor * dis;
    default:
        return 0;
    }
}

int Prey::get_effected_reproduce_possibility() const {
    switch (now_season) {
    case SPRING:
        return int(this->unit_time_reproduce_possibility * spring_reproduce_factor);
    case SUMMER:
        return int(this->unit_time_reproduce_possibility * summer_reproduce_factor);
    case AUTUMN:
        return int(this->unit_time_reproduce_possibility * autumn_reproduce_factor);
    case WINTER:
        return int(this->unit_time_reproduce_possibility * winter_reproduce_factor);
    default:
        return 0;
    }
}

int Prey::get_effected_eye_sight() const {
    switch (now_weather) {
    case RAINY:
        return this->eyesight * rainy_eye_sight_factor;
    case SUNNY:
        return this->eyesight * sunny_eye_sight_factor;
    default:
        return 0;
    }
}

bool Prey::reproduce_decision(float delta) {
    this->is_reproduce = false;
    if (this->energy > this->reproduce_energy) {
        if((rand()%int(this->get_effected_reproduce_possibility()/delta))==0){
            this->is_reproduce = true;
            return true;
        }
        return false;

    }
    else{
        return false;
    }
}

float Prey::energy_of_map(int map_x, int map_y) {
    if (0 <= current_map[map_x][map_y].state && current_map[map_x][map_y].state <= max_grass_state)
        return current_map[map_x][map_y].state * per_grass_energy;
    else
        return 0;
}

void Prey::minheapsort() {
    for (int i = 0; i < this->select_heap_event; i++) {
        min_heap.push(current_event[i]);
    }
    for (int i = this->select_heap_event; i < current_event_size; i++) {
        if (min_heap.top().priority < current_event[i].priority)
        {
            min_heap.pop();
            min_heap.push(current_event[i]);
        }
    }
}

void Prey::heapsort(std::vector<Event>& arr, int len)
{
    for (int i = len / 2 - 1; i >= 0; i--)
        max_heapify(arr, i, len - 1);
    for (int i = len - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        max_heapify(arr, 0, i - 1);
    }
}

//according the priority of event to build max_heap
void Prey::max_heapify(std::vector<Event>& arr, int start, int end) {
    int dad = start;
    int son = dad * 2 + 1;
    while (son <= end) {
        if (son + 1 <= end && arr[son].priority > arr[son + 1].priority)
            son++;
        if (arr[dad].priority < arr[son].priority)
            return;
        else {
            std::swap(arr[dad], arr[son]);
            dad = son;
            son = dad * 2 + 1;
        }
    }
}

float Prey::grass_priority(int map_x, int map_y) {
    // use the reciprocal of distance times the energy in map(x,y) as grass priority
    return (1 / (this->calculate_distance(int(this->x), int(this->y), map_x, map_y))) * energy_of_map(map_x, map_y);
}

int Prey::get_prey_number()
{
    return this->be_prey_number;
}

void Prey::add_prey_number()
{
    this->be_prey_number++;
}

bool Prey::get_can_eat_grass() {
    return can_eat_grass;
}

float Prey::get_eat_speed() {
    return eat_speed;
}

float Prey::lose_energy(float delta) {
    float result = 0;
    if (this->is_reproduce) {
        result += baby_energy;
    }
    switch (this->now_state) {
    case CALM:
        result += this->calm_energy_loss_speed * delta;
        break;
    case ACTIVE:
        result += this->active_energy_loss_speed * delta;
        break;
    case STILL:
        result += this->still_energy_loss_speed * delta;
        break;
    }
    return result;
}

float Prey::gain_energy(float& consume_grass_state,float delta) { // grass state should reduce consume_grass_state
    consume_grass_state = 0;
    if (!this->can_eat_grass)
        return 0;
    const std::vector<Animal*>& temp_cow_ptr_vec = current_map[int(this->x)][int(this->y)].cow_ptr_vec;
    const std::vector<Animal*>& temp_hare_ptr_vec = current_map[int(this->x)][int(this->y)].hare_ptr_vec;
    float total_loss_state = 0;
    // check how many cow and hare
    float grass_state = current_map[int(this->x)][int(this->y)].state;
    int prey_number = 0;
    for (int k = 0; k < temp_cow_ptr_vec.size(); k++) {
        Animal* animal_ptr = temp_cow_ptr_vec[k];
        Prey* prey_ptr = dynamic_cast<Prey*>(animal_ptr);
        if(prey_ptr->get_can_eat_grass() == true){
            total_loss_state += prey_ptr->get_eat_speed() * delta;
            prey_number += 1;
        }
    }
    for (int k = 0; k < temp_hare_ptr_vec.size(); k++) {
        Animal* animal_ptr = temp_hare_ptr_vec[k];
        Prey* prey_ptr = dynamic_cast<Prey*>(animal_ptr);
        if(prey_ptr->get_can_eat_grass() == true){
            total_loss_state += prey_ptr->get_eat_speed() * delta;
            prey_number += 1;
        }
    }
    if (prey_number > 0) {
        if (grass_state - total_loss_state >= 0) { // if grass energy can satisfy all cow and hare
            float result = energy_efficiency * eat_speed * per_grass_energy * delta;
            float grass_loss_energy = eat_speed * delta;
            consume_grass_state = grass_loss_energy;
            if(next_map[int(this->x)][int(this->y)].state - consume_grass_state < 0)
                consume_grass_state = next_map[int(this->x)][int(this->y)].state;
            return result;
        }
        else {
            float result = energy_efficiency * (grass_state / prey_number ) * delta;
            float grass_loss_energy = (grass_state / prey_number ) * delta;
            consume_grass_state = grass_loss_energy;
            if(next_map[int(this->x)][int(this->y)].state - consume_grass_state < 0)
                consume_grass_state = next_map[int(this->x)][int(this->y)].state;
            return result;
        }
    }
    else
        return 0;
}

std::pair<float, float> Prey::prey_get_new_position(std::pair<float, float> direction_vec, float displacement) {
    
    float unit_x = direction_vec.first;
    float unit_y = direction_vec.second;
    // get displacement
    float move_x = unit_x * displacement;
    float move_y = unit_y * displacement;
    // get new position
    float target_x = this->x + move_x;
    float target_y = this->y + move_y;


    if ((target_x < 0 || target_x >= map_size) && (target_y < 0 || target_y >= map_size)) {
        double angle = 0;
        if (unit_x <= 0) {
            angle = acos(unit_x) - acos(-1.0);
            angle -= 0.8 * acos(-1.0);
        }
        else {
            angle = acos(unit_x);
            angle -= 0.8 * acos(-1.0);
        }
        unit_x = cos(angle);
        unit_y = sin(angle);
        move_x = unit_x * displacement;
        move_y = unit_y * displacement;
        target_x = this->x + move_x;
        target_y = this->y + move_y;
    }
    else if (target_x >= map_size && target_y >= 0 && target_y < map_size) {
        if (unit_y > 0) {
            target_x = this->x - move_y;
        }
        else {
            target_x = this->x + move_y;
            if(unit_y == 0)
                target_y = this->y - move_x;
        }
    }
    else if (target_x < 0 && target_y >= 0 && target_y < map_size) {
        if (unit_y < 0) {
            target_x = this->x - move_y;
        }
        else {
            target_x = this->x + move_y;
            if (unit_y == 0)
                target_y = this->y - move_x;
        }
    }
    else if (target_y >= map_size && target_x >= 0 && target_x < map_size) {
        if (unit_x < 0) {
            target_y = this->y + move_x;
        }
        else {
            target_y = this->y - move_x;
            if (unit_x == 0)
                target_x = this->x + move_y;
        }
    }
    else if (target_y < 0 && target_x >= 0 && target_x < map_size) {
        if (unit_x < 0) {
            target_y = this->y - move_x;
        }
        else {
            target_y = this->y + move_x;
            if (unit_x == 0)
                target_x = this->x + move_y;
        }
    }

    if (target_x >= 0 && target_x < map_size && target_y >= 0 && target_y < map_size) {
        std::pair<float, float> result(target_x, target_y);
        return result;
    }
    else {
        if (target_x < 0) {
            target_x = 0;
        }
        else if (target_x >= map_size) {
            target_x = map_size - 1;
        }
        if (target_y < 0) {
            target_y = 0;
        }
        else if (target_y >= map_size) {
            target_y = map_size - 1;
        }

        std::pair<float, float> result(target_x, target_y);
        return result;
    }
}

void Prey::update_information(std::pair<float, float>& next_position, bool& can_reproduce_flag, float delta) {
    // initial

    can_eat_grass = false;
    this->is_reproduce = false;
    can_reproduce_flag = false;
    this->poop_flag = false;
    this->is_reproduce = false;
    this->all_event(); //store all event for cow

    int min_heap_size = min_heap.size();
    for(int i = min_heap_size;i < this->select_heap_event;i++) {
        current_event[i] = Event(0, "x", 0, 0);
    }
    for (int i = min_heap_size - 1; i >= 0; i--) {
        if(min_heap.top().name != "predator" && current_event[i].name == "predator")
            run_time = run_time_num;
        current_event[i] = min_heap.top();
        min_heap.pop();
    }

    this->current_event_size = current_event.size();

    std::pair<float, float> possible_direction;
    this->now_state = CALM;
    if (this->current_event[0].priority == 0) {
        next_position = this->prey_get_new_position(this->get_random_direction(delta), this->get_effected_displacement_factor(delta));
        if (this->get_energy() > this->hungry_energy)
        {
            can_reproduce_flag = this->reproduce_decision(delta);
            this->is_reproduce = can_reproduce_flag;
        }
    }
    else
    {
        if (this->current_event[0].name == "predator") { //  if cow see at least one tiger
            this->now_state = ACTIVE;
            double total_angle = 0;
            double angle;
            int angle_num = 0;
            float distance;

            for (int i = 0; i < this->select_heap_event; i++) {
                if (i >= current_event_size)
                    break;
                if (this->current_event[i].name == "predator") {
                    if (this->x - current_event[i].event_x == 0 && this->y - current_event[i].event_y == 0) {
                        possible_direction.first = 0;
                        possible_direction.second = 0;
                        next_position = this->prey_get_new_position(possible_direction, this->get_effected_displacement_factor(delta));
                        return;
                    }
                    distance = this->calculate_distance(this->x, this->y, current_event[i].event_x, current_event[i].event_y);
                    if(distance > effected_predator_distance && angle_num >= 1)
                        continue;
                    double angle_x;
                    if (current_event[i].event_y <= this->y) {
                        //acos()--(0,pi)  asin()--(-pi/2,pi/2)
                        angle_x = acos((double(this->x - current_event[i].event_x) / distance));

                    }
                    else {
                        angle_x = acos((double(current_event[i].event_x - this->x) / distance)) - acos(-1.0);
                    }
                    if(angle_x < 0)
                        angle_x += 3.1415 * 2;
                    total_angle += angle_x;
                    angle_num += 1;
                }
                else
                    break;
            }

            angle = total_angle / angle_num;
            std::pair<float, float> result(cos(angle), sin(angle));
            possible_direction = result;
            next_position = this->prey_get_new_position(possible_direction, this->get_effected_displacement_factor(delta));
        }
        else {
            this->now_state = CALM;
            this->poop_flag = true;
            if (this->get_energy() > this->hungry_energy) // if no hungry and no tiger, random walk.
            {
                if(current_event[0].name == "grass_with_cow"){
                    double dis = this->calculate_distance(x,y,current_event[0].event_x,current_event[0].event_y);
                    if(dis >= living_together_dis){
                        double angle_cow = 0;
                        if (y <= current_event[0].event_y) {
                            angle_cow = acos((current_event[0].event_x - x) / dis);
                        }
                        else {
                            angle_cow = acos((x - current_event[0].event_x) / dis) - acos(-1.0);
                        }
                        std::pair<float, float> result1(cos(angle_cow), sin(angle_cow));
                        possible_direction = result1;
                    }
                    else{
                        possible_direction = get_random_direction(delta);
                        next_position = this->prey_get_new_position(possible_direction, this->get_effected_displacement_factor(delta));
                        dis = this->calculate_distance(current_event[0].event_x,current_event[0].event_y,next_position.first,next_position.second);
                        if(dis > living_together_dis){
                            possible_direction.first = 0;
                            possible_direction.second = 0;
                        }
                    }
                }
                else{
                    possible_direction = get_random_direction(delta);
                }
                next_position = this->prey_get_new_position(possible_direction, this->get_effected_displacement_factor(delta));
                can_reproduce_flag = this->reproduce_decision(delta);
                this->is_reproduce = can_reproduce_flag;
            }
            else {// if hungry and no tiger
                if (current_map[int(this->x)][int(this->y)].state >= min_state_can_eat_grass) { // if cow current position have grass, the position will no change
                    can_eat_grass = true; // cow can eat grass
                    this->now_state = STILL;
                    
                    next_position.first = this->x;
                    next_position.second = this->y;
                }
                else {
                    int max_grass_priority_x = this->current_event[0].event_x;
                    int max_grass_priority_y = this->current_event[0].event_y;
                    float angle_grass = 0;
                    if (int(this->x) != max_grass_priority_x || int(this -> y) != max_grass_priority_y) {
                        float optional_x = this->x;
                        float optional_y = this->y;
                        float distance = this->calculate_distance(this->x, this->y, max_grass_priority_x, max_grass_priority_y);
                        if(distance <= living_together_dis){
                            if(current_map[int(optional_x)][int(optional_y)].state >= min_state_can_eat_grass){
                                possible_direction.first = 0;
                                possible_direction.second = 0;
                                next_position = this->prey_get_new_position(possible_direction, this->get_effected_displacement_factor(delta));
                                return;
                            }
                        }
                        if (optional_y <= max_grass_priority_y) {
                            angle_grass = acos((max_grass_priority_x - optional_x) / distance);
                        }
                        else {
                            angle_grass = acos((optional_x - max_grass_priority_x) / distance) - acos(-1.0);
                        }
                        std::pair<float, float> result1(cos(angle_grass), sin(angle_grass));
                        possible_direction = result1;
                        optional_x += possible_direction.first * this->get_effected_displacement_factor(delta);
                        optional_y += possible_direction.second * this->get_effected_displacement_factor(delta);
                        if (pow(distance, 2) <= pow(optional_x - max_grass_priority_x, 2) + pow(optional_y - max_grass_priority_y, 2)) {
                            next_position.first = int(max_grass_priority_x) + (rand()%100)/100;
                            next_position.second = int(max_grass_priority_y) + (rand()%100)/100;
                        }
                        else {
                            next_position = this->prey_get_new_position(possible_direction, this->get_effected_displacement_factor(delta));
                        }
                    }
                    else {
                        possible_direction.first = 0;
                        possible_direction.second = 0;
                        next_position = this->prey_get_new_position(possible_direction, this->get_effected_displacement_factor(delta));
                    }
                }
            }
        }
    }
    this->previous_x = this->x;
    this->previous_y = this->y;
    this->next_x = next_position.first;
    this->next_y = next_position.second;
}

