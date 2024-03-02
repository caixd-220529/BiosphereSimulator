//
// Created by csyq on 2023/4/29.
// To display Chinese, use:
// system("chcp 65001");
// To output normally in debug mode, use:
// setbuf(stdout,NULL);
//

#include "logic.h"
using namespace std;

Logic::Logic(int map_size, int grid_size, float scale, int64_t cow_num, int64_t hare_num, int64_t tiger_num, int64_t fox_num, int poop_num, float grass_growth_per_frame,
	float waste_loss_per_frame, int rainy_possibility, int max_weather_time_1, int max_weather_time_2,
	int max_weather_time_3, int max_weather_time_4, int rainy_possibility_1, int rainy_possibility_2,
	int rainy_possibility_3, int rainy_possibility_4,
	//Cow parameter
	float energy_cow, float hungry_energy_cow, float reproduce_energy_cow, float baby_energy_cow, float calm_dis_cow, float active_dis_cow,
	float calm_loss_cow, float active_loss_cow, float still_loss_cow, float energy_gain_cow,
	int eyesight_cow, int age_cow, int max_age_cow,
	int reproduce_possibility_cow, int maximum_single_direction_frame_cow,
	float energy_efficiency_cow, float eat_speed_cow, int select_heap_event_cow,
	//Hare parameter
	float energy_hare, float hungry_energy_hare, float reproduce_energy_hare, float baby_energy_hare, float calm_dis_hare, float active_dis_hare,
	float calm_loss_hare, float active_loss_hare, float still_loss_hare, float energy_gain_hare,
	int eyesight_hare, int age_hare, int max_age_hare,
	int reproduce_possibility_hare, int maximum_single_direction_frame_hare,
	float energy_efficiency_hare, float eat_speed_hare, int select_heap_event_hare,
	//Tiger parameter
	float energy_tiger, float hungry_energy_tiger, float reproduce_energy_tiger, float baby_energy_tiger,
	float calm_dis_tiger, float active_dis_tiger,
	float calm_loss_tiger, float active_loss_tiger, float still_loss_tiger, float energy_gain_tiger,
	int eyesight_tiger, int age_tiger, int max_age_tiger,
	int reproduce_possibility_tiger, int maximum_single_direction_frame_tiger,
	float energy_efficiency_tiger,
	//Fox parameter
	float energy_fox, float hungry_energy_fox, float reproduce_energy_fox, float baby_energy_fox,
	float calm_dis_fox, float active_dis_fox,
	float calm_loss_fox, float active_loss_fox, float still_loss_fox, float energy_gain_fox,
	int eyesight_fox, int age_fox, int max_age_fox,
	int reproduce_possibility_fox, int maximum_single_direction_frame_fox,
	float energy_efficiency_fox
)
{
	this->poop_head = nullptr;
	this->poop_tail = NULL;
	this->scale = scale;
	this->map_size = map_size;
	this->grid_size = grid_size;
	this->id_allocate = 0;
	this->cow_num = cow_num;
	this->tiger_num= tiger_num;
	this->fox_num = fox_num;
	this->hare_num = hare_num;
	this->poop_num= poop_num;
	this->weather_timer= 0;
	this->season_timer= 0;

	this->grass_growth_per_frame= grass_growth_per_frame;
	this->waste_loss_per_frame= waste_loss_per_frame;
	this->rainy_possibility= rainy_possibility;

	//Cow parameter
	this->energy_cow= energy_cow;
	this->hungry_energy_cow= hungry_energy_cow;
	this->reproduce_energy_cow= reproduce_energy_cow;
	this->baby_energy_cow= baby_energy_cow;
	this->calm_dis_cow= calm_dis_cow ;
	this->active_dis_cow= active_dis_cow ;
	this->calm_loss_cow= calm_loss_cow;
	this->active_loss_cow= active_loss_cow;
	this->still_loss_cow= still_loss_cow;
	this->energy_gain_cow= energy_gain_cow;
	this->eyesight_cow= eyesight_cow ;
	this->age_cow= age_cow;
	this->max_age_cow= max_age_cow;
	this->reproduce_possibility_cow= reproduce_possibility_cow;
	this->maximum_single_direction_frame_cow= maximum_single_direction_frame_cow ;
	this->energy_efficiency_cow= energy_efficiency_cow;

	this->eat_speed_cow= eat_speed_cow;
	this->select_heap_event_cow= select_heap_event_cow;

	//Hare parameter
	this->energy_hare = energy_hare;
	this->hungry_energy_hare = hungry_energy_hare;
	this->reproduce_energy_hare = reproduce_energy_hare;
	this->baby_energy_hare = baby_energy_hare;
	this->calm_dis_hare = calm_dis_hare ;
	this->active_dis_hare = active_dis_hare ;
	this->calm_loss_hare = calm_loss_hare;
	this->active_loss_hare = active_loss_hare;
	this->still_loss_hare = still_loss_hare;
	this->energy_gain_hare = energy_gain_hare;
	this->eyesight_hare = eyesight_hare ;
	this->age_hare = age_hare;
	this->max_age_hare = max_age_hare;
	this->reproduce_possibility_hare = reproduce_possibility_hare;
	this->maximum_single_direction_frame_hare = maximum_single_direction_frame_hare;
	this->energy_efficiency_hare = energy_efficiency_hare;

	this->eat_speed_hare = eat_speed_hare;
	this->select_heap_event_hare = select_heap_event_hare;

	//Tiger parameter
	this->energy_tiger= energy_tiger;
	this->hungry_energy_tiger= hungry_energy_tiger;
	this->reproduce_energy_tiger= reproduce_energy_tiger;
	this->baby_energy_tiger= baby_energy_tiger;
	this->calm_dis_tiger= calm_dis_tiger ;
	this->active_dis_tiger= active_dis_tiger;
	this->calm_loss_tiger= calm_loss_tiger;
	this->active_loss_tiger= active_loss_tiger;
	this->still_loss_tiger= still_loss_tiger;
	this->energy_gain_tiger= energy_gain_tiger;
	this->eyesight_tiger= eyesight_tiger ;
	this->age_tiger= age_tiger;
	this->max_age_tiger= max_age_tiger;
	this->reproduce_possibility_tiger= reproduce_possibility_tiger;
	this->maximum_single_direction_frame_tiger= maximum_single_direction_frame_tiger ;
	this->energy_efficiency_tiger= energy_efficiency_tiger;

	//Fox parameter
	this->energy_fox = energy_fox;
	this->hungry_energy_fox = hungry_energy_fox;
	this->reproduce_energy_fox = reproduce_energy_fox;
	this->baby_energy_fox = baby_energy_fox;
	this->calm_dis_fox = calm_dis_fox ;
	this->active_dis_fox = active_dis_fox ;
	this->calm_loss_fox = calm_loss_fox;
	this->active_loss_fox = active_loss_fox;
	this->still_loss_fox = still_loss_fox;
	this->energy_gain_fox = energy_gain_fox;
	this->eyesight_fox = eyesight_fox;
	this->age_fox = age_fox;
	this->max_age_fox = max_age_fox;
	this->reproduce_possibility_fox = reproduce_possibility_fox;
	this->maximum_single_direction_frame_fox = maximum_single_direction_frame_fox ;
	this->energy_efficiency_fox = energy_efficiency_fox;

	this->now_season = SPRING;
	this->now_weather = SUNNY;

	this->max_weather_time_1 = max_weather_time_1;
	this->max_weather_time_2 = max_weather_time_2;
	this->max_weather_time_3 = max_weather_time_3;
	this->max_weather_time_4 = max_weather_time_4;
	this->weather_time_1 = rand() % max_weather_time_1;
	this->weather_time_2 = rand() % max_weather_time_2;
	this->weather_time_3 = rand() % max_weather_time_3;
	this->weather_time_4 = rand() % max_weather_time_4;
	this->rainy_possibility_1 = rainy_possibility_1;
	this->rainy_possibility_2 = rainy_possibility_2;
	this->rainy_possibility_3 = rainy_possibility_3;
	this->rainy_possibility_4 = rainy_possibility_4;
}

void Logic::initial_grid()
{
	int grid_number = map_size / grid_size;
	for (int i = 0; i < grid_number; i++)
	{
		vector<int> vi;
		for (int j = 0; j < grid_number; j++)
		{
			int grass = rand() % 3;
			for (int x = 0; x < grid_size; x++)
			{
				for (int y = 0; y < grid_size; y++)
				{
					Animal::current_map[i*grid_size+x][j*grid_size+y].state = grass;
				}
			}
			vi.push_back(grass);
		}
		grid_map.push_back(vi);
	}
}

void Logic::initial_map()
{
	for (int i = 0; i < map_size; i++)
	{
		vector<Node> vN;
		for (int j = 0; j < map_size; j++)
		{
			//std::vector<Animal*> animals_ptr_vec ;
			struct Node n1;
			n1.state = rand() % 3;
			vN.push_back(n1);
		}
		Animal::current_map.push_back(vN);
	}
	initial_grid();
	Animal::next_map = Animal::current_map;
	Animal::current_map_ptr = &Animal::current_map;
	Animal::next_map_ptr = &Animal::next_map;
}

void Logic::initial_animal()
{
	for (int i = 0; i < cow_num; i++)//initial cow_vector 
	{

		int x = rand() % map_size;
		int y = rand() % map_size;
		while (Animal::current_map[x][y].terrain == WATER)
		{
			x = rand() % map_size;
			y = rand() % map_size;
		}
        int age_cow_l = rand() % max_age_cow;
		int energy = energy_cow/10 + (rand() % (int)energy_cow);
		Cow* cow_ptr = new Cow(id_allocate, energy, hungry_energy_cow, reproduce_energy_cow, baby_energy_cow, calm_dis_cow, active_dis_cow,
			calm_loss_cow, active_loss_cow, still_loss_cow, energy_gain_cow,
			x, y, eyesight_cow, age_cow_l, max_age_cow,
			reproduce_possibility_cow, maximum_single_direction_frame_cow,
			energy_efficiency_cow, eat_speed_cow, select_heap_event_cow);//haven't finished
		id_allocate++;
		prey_list.push_back(cow_ptr);
		//this->cow_vector.push_back(cow_ptr);	//useless
		int x_down = (int)(cow_ptr->get_x());
		int y_down = (int)(cow_ptr->get_y());
		Animal::current_map[x_down][y_down].animals_ptr_vec.push_back(cow_ptr);//initial map
        Animal::current_map[x_down][y_down].cow_ptr_vec.push_back(cow_ptr);//initial map

    }

	for (int i = 0; i < hare_num; i++)//initial cow_vector 
	{
		int x = rand() % map_size;
		int y = rand() % map_size;
		while (Animal::current_map[x][y].terrain == WATER)
		{
			x = rand() % map_size;
			y = rand() % map_size;
		}
        int age_hare_l = rand() % max_age_hare;
		int energy = energy_hare/10 + (rand() % (int)energy_hare);
		Hare* hare_ptr = new Hare(id_allocate, energy, hungry_energy_hare, reproduce_energy_hare, baby_energy_hare, calm_dis_hare, active_dis_hare,
			calm_loss_hare, active_loss_hare, still_loss_hare, energy_gain_hare,
			x, y, eyesight_hare, age_hare_l, max_age_hare,
			reproduce_possibility_hare, maximum_single_direction_frame_hare,
			energy_efficiency_hare, eat_speed_hare, select_heap_event_hare);//haven't finished
		id_allocate++;
		prey_list.push_back(hare_ptr);
		//this->cow_vector.push_back(cow_ptr);	//useless
		int x_down = (int)(hare_ptr->get_x());
		int y_down = (int)(hare_ptr->get_y());
		Animal::current_map[x_down][y_down].animals_ptr_vec.push_back(hare_ptr);//initial map
        Animal::current_map[x_down][y_down].hare_ptr_vec.push_back(hare_ptr);//initial map

    }

	for (int i = 0; i < tiger_num; i++)//initial tiger_vector
	{
		int x = rand() % map_size;
		int y = rand() % map_size;
		while (Animal::current_map[x][y].terrain == WATER)
		{
			x = rand() % map_size;
			y = rand() % map_size;
		}
        int age_tiger_l = rand() % max_age_tiger;
		int energy = energy_tiger/10 + (rand() % (int)energy_tiger);
		Tiger* tiger_ptr = new Tiger(id_allocate, energy, hungry_energy_tiger, reproduce_energy_tiger,
			baby_energy_tiger, calm_dis_tiger, active_dis_tiger,
			calm_loss_tiger, active_loss_tiger, still_loss_tiger, energy_gain_tiger,
			x, y, eyesight_tiger, age_tiger_l, max_age_tiger,
			reproduce_possibility_tiger, maximum_single_direction_frame_tiger,
			energy_efficiency_tiger);//haven't finished
		id_allocate++;
		//this->tiger_vector.push_back(tiger_ptr);//useless;
		predator_list.push_back(tiger_ptr);
		int x_down = (int)(tiger_ptr->get_x());
		int y_down = (int)(tiger_ptr->get_y());
		Animal::current_map[x_down][y_down].animals_ptr_vec.push_back(tiger_ptr);//initial map
        Animal::current_map[x_down][y_down].tiger_ptr_vec.push_back(tiger_ptr);//initial map

    }

	for (int i = 0; i < fox_num; i++)//initial fox_vector
	{
		int x = rand() % map_size;
		int y = rand() % map_size;
		while (Animal::current_map[x][y].terrain == WATER)
		{
			x = rand() % map_size;
			y = rand() % map_size;
		}
        int age_fox_l = rand() % max_age_fox;
		int energy = energy_fox/10 + (rand() % (int)energy_fox);
		Fox* fox_ptr = new Fox(id_allocate, energy, hungry_energy_fox, reproduce_energy_fox,
			baby_energy_fox, calm_dis_fox, active_dis_fox,
			calm_loss_fox, active_loss_fox, still_loss_fox, energy_gain_fox,
			x, y, eyesight_fox, age_fox_l, max_age_fox,
			reproduce_possibility_fox, maximum_single_direction_frame_fox,
			energy_efficiency_fox);//haven't finished
		id_allocate++;
		//this->fox_vector.push_back(fox_ptr);//useless;
		predator_list.push_back(fox_ptr);
		int x_down = (int)(fox_ptr->get_x());
		int y_down = (int)(fox_ptr->get_y());
		Animal::current_map[x_down][y_down].animals_ptr_vec.push_back(fox_ptr);//initial map
        Animal::current_map[x_down][y_down].fox_ptr_vec.push_back(fox_ptr);//initial map

    }
}
void Logic::initial_poop_queue()
{
	int prey_index = 0; int tiger_index = 0;
	list<Predator*>::iterator predator_ite = predator_list.begin();
	list<Prey*>::iterator prey_ite = prey_list.begin();
	while (predator_ite != predator_list.end() || prey_ite != prey_list.end())
	{
		if (rand() % 2 == 0&&predator_ite!=predator_list.end())
		{
			poop_node* pn = new poop_node();
			pn->animal_ptr = *predator_ite;
			pn->id = (*predator_ite)->get_id();
			pn->next_pp_node = NULL;
			if (poop_head == NULL)
			{
				poop_head = pn;
				poop_tail = pn;
			}
			else
			{
				poop_tail->next_pp_node = pn;
				poop_tail = pn;
			}
			predator_ite++;
		}
		else if (prey_ite != prey_list.end())
		{
			poop_node* pn = new poop_node();
			pn->animal_ptr = *prey_ite;
			pn->id = (*prey_ite)->get_id();
			pn->next_pp_node = NULL;
			if (poop_head == NULL)
			{
				poop_head = pn;
				poop_tail = pn;
			}
			else
			{
				poop_tail->next_pp_node = pn;
				poop_tail = pn;
			}
			prey_ite++;
		}
	}

}

void Logic::update_poop_list( float delta)
{
    if(rand()%(int)(3000/delta)>(cow_num+tiger_num+fox_num+hare_num))
    {
        return;
    }
	//queue<Animal*> prior_poop;
	//queue<Animal*> temp_poop_queue;
	//poop_location_vector.clear();
	poop_node* indicate_list_head = poop_head;
	//while (indicate_list_head->next_pp_node != nullptr)
	//{
		//cout << indicate_list_head->id << endl;
		//indicate_list_head = indicate_list_head->next_pp_node;
	//}
	poop_node* prior_list_head = NULL;
	poop_node* prior_list_tail = NULL;
	poop_node* temp_list_head = NULL;
	poop_node* temp_list_tail = NULL;
	for (int i = 0; i < poop_num && (!(poop_head == NULL)); i++)
	{
		struct poop_node pn = *poop_head;
		if (pn.animal_ptr->get_id() != pn.id || pn.animal_ptr->is_dead())//animal has been die
		{
			i--;
		}
		else if (pn.animal_ptr->get_poop_flag())
		{
			//cout << "poop" << endl;
			//cout <<"poop id is: " << pn.animal_ptr->get_id() << "--------------------"<<endl;
			float x_down = pn.animal_ptr->get_x();
			float y_down = pn.animal_ptr->get_y();
			Animal::next_map[x_down][y_down].waste_amount += WASTE_PER_ANIMAL;
			Animal::current_map[x_down][y_down].waste_amount += WASTE_PER_ANIMAL;
			if (temp_list_head == NULL)
			{
				temp_list_head = poop_head;
				temp_list_tail = poop_head;
			}
			else
			{
				temp_list_tail->next_pp_node = poop_head;
				temp_list_tail = poop_head;
			}

		}
		else
		{
			if (prior_list_head == NULL)
			{
				prior_list_head = poop_head;
				prior_list_tail = poop_head;
			}
			else
			{
				prior_list_tail->next_pp_node = poop_head;
				prior_list_tail = poop_head;
			}
			i--;
		}
		if (poop_head->next_pp_node != NULL)
		{
			poop_head = poop_head->next_pp_node;
		}
		else
		{
			poop_head = NULL;
			poop_tail = NULL;
		}

		if (poop_tail != NULL)
		{
			poop_tail->next_pp_node = NULL;
		}

		if (prior_list_tail != NULL)
		{
			prior_list_tail->next_pp_node = NULL;
		}
		if (temp_list_tail != NULL)
		{
			temp_list_tail->next_pp_node = NULL;
		}
	}
	//merge the list
		if (prior_list_head == NULL)
		{
			prior_list_head = poop_head;
			prior_list_tail = poop_tail;
		}
		else if (poop_head != NULL)
		{
			prior_list_tail->next_pp_node = poop_head;
			prior_list_tail = poop_tail;
		}
		if (temp_list_head != NULL)
		{
			if (prior_list_head != NULL)
			{
				prior_list_tail->next_pp_node = temp_list_head;
				prior_list_tail = temp_list_tail;
			}
			else
			{
				prior_list_head = temp_list_head;
				prior_list_tail = temp_list_tail;
			}
		}
		poop_head = prior_list_head;
		poop_tail = prior_list_tail;

	
		/*
		Animal* animal_ptr = poop_queue.front();
		poop_queue.pop();
		if (animal_ptr == NULL)
		{
			cout << "null" << endl;
		}
		if (animal_ptr->is_dead())
		{
			i--;
		}
		else if (animal_ptr->get_poop_flag())
		{
			float x_down = animal_ptr->get_x();
			float y_down = animal_ptr->get_y();

			//			Animal::next_map[x_down][y_down].waste_exist = true;
			//			Animal::next_map[x_down][y_down].waste_timer = 0;
			//			Animal::current_map[x_down][y_down].waste_exist = true;
			//			Animal::current_map[x_down][y_down].waste_timer = 0;


						// if animal poop, add some waste to the node.-cxd
			Animal::next_map[x_down][y_down].waste_amount += WASTE_PER_ANIMAL;
			Animal::current_map[x_down][y_down].waste_amount += WASTE_PER_ANIMAL;


			//std::pair<float, float> location(x_down, y_down);
			//poop_location_vector.push_back(location);
			temp_poop_queue.push(animal_ptr);
		}
		else
		{
			i--;
			prior_poop.push(animal_ptr);
		}
	}
	while (!poop_queue.empty())
	{
		Animal* animal_ptr = poop_queue.front();
		poop_queue.pop();
		if (!animal_ptr->is_dead())
		{
			prior_poop.push(animal_ptr);
		}
	}
	while (!temp_poop_queue.empty())
	{
		Animal* animal_ptr = temp_poop_queue.front();
		temp_poop_queue.pop();
		prior_poop.push(animal_ptr);
	}
	while (!prior_poop.empty())
	{
		Animal* animal_ptr = prior_poop.front();
		prior_poop.pop();
		poop_queue.push(animal_ptr);
	}
	*/
}

void Logic::check_cow_dead(Cow*& cow,int index)
{
	if (cow == cow_vector[index])
	{
		cow_vector.erase(begin(cow_vector) + index);
		delete(cow);
		cow = NULL;
	}
	else
	{
	cout << "error happened in erase cow." << endl;
	system("pause");
	}
		
}

void Logic::check_tiger_dead(Tiger* tiger,int index)
{
	if (tiger == tiger_vector[index])
	{
		tiger_vector.erase(begin(tiger_vector) + index);
		delete(tiger);
	}
	else
	{
		cout << "error happened in erase cow." << endl;
		system("pause");
	}
}

void Logic::reproduce_prey(Prey* prey_ptr)
{
	float x = prey_ptr->get_x();
	float y = prey_ptr->get_y(); 
	int energy = prey_ptr->get_baby_energy();
	Cow* cow_ptr = dynamic_cast<Cow*>(prey_ptr);
	if (cow_ptr != nullptr)
	{
		Cow* new_cow = new Cow(id_allocate, energy, hungry_energy_cow, reproduce_energy_cow, baby_energy_cow, calm_dis_cow, active_dis_cow,
			calm_loss_cow, active_loss_cow, still_loss_cow, energy_gain_cow,
			x, y, eyesight_cow, 0, max_age_cow,//0 is age_cow
			reproduce_possibility_cow, maximum_single_direction_frame_cow,
			energy_efficiency_cow, eat_speed_cow, select_heap_event_cow);
		id_allocate++;
        cow_num++;
		new_born_prey.push(new_cow);

	}
	else if(dynamic_cast<Hare*>(prey_ptr)!=nullptr)
	{
		Hare* new_hare = new Hare(id_allocate, energy, hungry_energy_hare, reproduce_energy_hare, baby_energy_hare, calm_dis_hare, active_dis_hare,
			calm_loss_hare, active_loss_hare, still_loss_hare, energy_gain_hare,
			x, y, eyesight_hare, 0, max_age_hare,//0 is age_hare
			reproduce_possibility_hare, maximum_single_direction_frame_hare,
			energy_efficiency_hare, eat_speed_hare, select_heap_event_hare);
		id_allocate++;
		new_born_prey.push(new_hare);
        hare_num++;
	}
	else
	{
		cout << "reproduce error in prey" << endl;
		system("pause");
	}
}

void Logic::reproduce_predator(Predator* predator_ptr)
{
	float x = predator_ptr->get_x();
	float y = predator_ptr->get_y();
	int energy = predator_ptr->get_baby_energy();
	Tiger* tiger_ptr = dynamic_cast<Tiger*>(predator_ptr);
	if (tiger_ptr != nullptr)
	{
		Tiger* new_tiger = new Tiger(id_allocate, energy, hungry_energy_tiger, reproduce_energy_tiger, baby_energy_tiger, calm_dis_tiger, active_dis_tiger,
			calm_loss_tiger, active_loss_tiger, still_loss_tiger, energy_gain_tiger,
			x, y, eyesight_tiger, 0, max_age_tiger,//0 is age_tiger
			reproduce_possibility_tiger, maximum_single_direction_frame_tiger,
			energy_efficiency_tiger);
		id_allocate++;
		new_born_predator.push(new_tiger);
        tiger_num++;

	}
	else if (dynamic_cast<Fox*>(predator_ptr) != nullptr)
	{
		Fox* new_fox = new Fox(id_allocate, energy, hungry_energy_fox, reproduce_energy_fox, baby_energy_fox, calm_dis_fox, active_dis_fox,
			calm_loss_fox, active_loss_fox, still_loss_fox, energy_gain_fox,
			x, y, eyesight_fox, 0, max_age_fox,//0 is age_fox
			reproduce_possibility_fox, maximum_single_direction_frame_fox,
			energy_efficiency_fox);
		id_allocate++;
		new_born_predator.push(new_fox);
        fox_num++;
	}
	else
	{
		cout << "reproduce error in predator" << endl;
		system("pause");
	}
}

std::vector<std::pair<float, float>> Logic::get_cow_location_vector()
{
	return cow_location_vector;
}

std::vector<std::pair<float, float>> Logic::get_tiger_location_vector()
{
	return tiger_location_vector;
}

std::vector<std::pair<float, float>> Logic::get_hare_location_vector()
{
	return hare_location_vector;
}

std::vector<std::pair<float, float>> Logic::get_fox_location_vector()
{
	return fox_location_vector;
}

std::vector<std::pair<float, float>> Logic::get_poop_location_vector()
{
	return this->poop_location_vector;
}

std::vector<vector<int>> Logic::get_grid_map()
{
	return this->grid_map;
}

int Logic::get_season()
{
    return this->now_season;
}

int Logic::get_weather()
{
    return this->now_weather;
}

int64_t Logic::get_cow_num()
{
    return this->cow_num;
}

int64_t Logic::get_tiger_num()
{
    return this->tiger_num;
}

int64_t Logic::get_hare_num()
{
    return this->hare_num;
}

int64_t Logic::get_fox_num()
{
    return this->fox_num;
}


void Logic::clear_next_map()
{
	for (int i = 0; i < map_size; i++)
	{
		for (int j = 0; j < map_size; j++)
		{
			Animal::next_map[i][j].animals_ptr_vec.clear();
            Animal::next_map[i][j].cow_ptr_vec.clear();
            Animal::next_map[i][j].tiger_ptr_vec.clear();
            Animal::next_map[i][j].hare_ptr_vec.clear();
            Animal::next_map[i][j].fox_ptr_vec.clear();

        }
	}
}

void Logic::update_map_state(float delta)
{
	poop_location_vector.clear();
	for (int i = 0; i < map_size; i++)
	{
		for (int j = 0; j < map_size; j++)
		{
			if (Animal::current_map[i][j].terrain == GRASS)
			{
				Animal::next_map[i][j].state += GROW_PER_FRAME*delta;
				Animal::current_map[i][j].state = Animal::next_map[i][j].state;
				if (Animal::next_map[i][j].waste_amount > 0) {
					std::pair<float, float> location(i*scale, j*scale);
					//cout << "waste: "<< Animal::next_map[i][j].waste_amount << endl;
					poop_location_vector.push_back(location);
					//1. decrease waste
					Animal::next_map[i][j].waste_amount -= WASTE_LOST_PER_FRAME*delta;
					Animal::current_map[i][j].waste_amount = Animal::next_map[i][j].waste_amount;
					if (Animal::next_map[i][j].waste_amount < 0)
					{
						Animal::next_map[i][j].waste_amount = 0;
						Animal::current_map[i][j].waste_amount = 0;
					}
					//2. let grass grow
					Animal::next_map[i][j].state += GROW_WITH_WASTE*delta;
					Animal::current_map[i][j].state = Animal::next_map[i][j].state;

				}
				if (now_weather == RAINY) {
					Animal::next_map[i][j].state += GROW_WITH_RAIN*delta;
					Animal::current_map[i][j].state = Animal::next_map[i][j].state;
				}
				//3. normalization of the state of node
				if (Animal::next_map[i][j].state > MAX_STATE) {
					Animal::next_map[i][j].state = MAX_STATE; Animal::current_map[i][j].state = MAX_STATE;
				}
			}
			
		}
	}
}

void Logic::update_grid_map()
{
	int grid_number = map_size / grid_size;
	for (int i = 0; i < grid_number;i++)
	{
		for (int j = 0; j < grid_number; j++)
		{
			float grass_total = 0;
			int water_count = 0;
			int grass_count = 0;
			for (int x = 0; x < grid_size; x++)
			{
				for (int y = 0; y < grid_size; y++)
				{
					if (Animal::next_map[i * grid_size + x][j * grid_size + y].terrain == GRASS)
					{
						grass_total += Animal::next_map[i * grid_size + x][j * grid_size + y].state;
						grass_count++;
					}
					else
					{
						water_count++;
					}
				}
			}
			
			if (grass_count != 0)
			{
				grid_map[i][j] = grass_total / grass_count;
			}
			else
			{
				grid_map[i][j] = -1;
			}
			if (grid_map[i][j] < -1 || grid_map[i][j]>3)
			{
				cout << "grass total = " << grass_total << endl;
				cout <<"grid value = " << grid_map[i][j] << endl;
				cout << "error in update grid_map " << endl;
				system("pause");
			}
		}
	}
}

void Logic::weather_change(float delta)
{

	if (now_season == 1) { // spring
		if (weather_timer >= weather_time_1)
		{
			if (now_weather == RAINY)
			{
				now_weather = SUNNY;
			}
			else if (now_weather == SUNNY && (rand() + 1) % rainy_possibility_1 == 0)
			{
				now_weather = RAINY;
			}
			weather_timer -= weather_time_1;
			this->weather_time_1 = rand() % max_weather_time_1;
		}
		else
		{
			weather_timer+= delta;
		}
	}
	else if (now_season == 2) { // summer
		if (weather_timer >= weather_time_2)
		{
			if (now_weather == RAINY)
			{
				now_weather = SUNNY;
			}
			else if (now_weather == SUNNY && (rand() + 1) % rainy_possibility_2 == 0)
			{
				now_weather = RAINY;
			}
			weather_timer -= weather_time_2;
			this->weather_time_2 = rand() % max_weather_time_2;
		}
		else
		{
			weather_timer+= delta;
		}
	}
	else if (now_season == 3) { // fall
		if (weather_timer >= weather_time_3)
		{
			if (now_weather == RAINY)
			{
				now_weather = SUNNY;
			}
			else if (now_weather == SUNNY && (rand() + 1) % rainy_possibility_3 == 0)
			{
				now_weather = RAINY;
			}
			weather_timer -= weather_time_3;
			this->weather_time_3 = rand() % max_weather_time_3;
		}
		else
		{
			weather_timer+= delta;
		}
	}
	else // winter
	{
		if (weather_timer >= weather_time_4)
		{
			if (now_weather == RAINY)
			{
				now_weather = SUNNY;
			}
			else if (now_weather == SUNNY && (rand() + 1) % rainy_possibility_4 == 0)
			{
				now_weather = RAINY;
			}
			weather_timer -= weather_time_4;
			this->weather_time_4 = rand() % max_weather_time_4;
		}
		else
		{
			weather_timer+= delta;
		}
	}

	/*if (weather_timer >= MAX_WEATHER_TIMER)
	{
		if (now_weather == RAINY)
		{
			now_weather = SUNNY;
		}
		else if (now_weather == RAINY&&rand()%rainy_possibility==0)
		{
			now_weather = RAINY;
		}
		weather_timer -= MAX_WEATHER_TIMER;
	}
	else
	{
		weather_timer++;
	}*/
}

void Logic::season_change(float delta)
{
	if (season_timer >= MAX_SEASON_TIMER)
	{
		switch (now_season)
		{
		case 1:
			now_season = SUMMER;
			break;
		case 2:
			now_season = AUTUMN;
			break;
		case 3:
			now_season = WINTER;
			break;
		case 4:
			now_season = SPRING;
			break;
		default:
		{
		cout << "error in season change" << endl;
		system("pause");break;
		}
			
			
		}
		season_timer -= MAX_SEASON_TIMER;
	}
	else
	{
		season_timer+=delta;
	}
}

void Logic::update_map(Animal* animal)
{
	if (!animal->is_dead())
	{
		int x_down = (int)animal->get_x();
		int y_down = (int)animal->get_y();
//		cout <<animal->get_id()<<endl;
//        cout << x_down << " " << y_down <<" --";
//        cout << animal->get_x()<<" "<<animal->get_y()<<"  "<<endl;
//        if(dynamic_cast<Tiger*>(animal)){cout<<"tiger"<<" "<<((Tiger*)animal)->get_died_prey_ptr() <<endl;}
//        if(dynamic_cast<Cow*>(animal)){cout<<"cow"<<endl;}
//        cout<<endl;
        Animal::next_map[x_down][y_down].animals_ptr_vec.push_back(animal);
		Tiger* tiger_ptr = dynamic_cast<Tiger*>(animal);
		if (tiger_ptr != nullptr)
		{
			std::pair<float, float> location(tiger_ptr->get_x()*scale, tiger_ptr->get_y() * scale);
			tiger_location_vector.push_back(location);
            Animal::next_map[x_down][y_down].tiger_ptr_vec.push_back(tiger_ptr);
		}
		else
		{
			Cow* cow_ptr = dynamic_cast<Cow*>(animal);
			if (cow_ptr != nullptr)
			{
				std::pair<float, float> location(cow_ptr->get_x() * scale, cow_ptr->get_y() * scale);
				cow_location_vector.push_back(location);
                Animal::next_map[x_down][y_down].cow_ptr_vec.push_back(cow_ptr);

            }
			else
			{
				Hare* hare_ptr = dynamic_cast<Hare*>(animal);
				if (hare_ptr != nullptr)
				{
					std::pair<float, float> location(hare_ptr->get_x() * scale,hare_ptr->get_y() * scale);
					hare_location_vector.push_back(location);
                    Animal::next_map[x_down][y_down].hare_ptr_vec.push_back(hare_ptr);
				}
				else
				{
					Fox* fox_ptr = dynamic_cast<Fox*>(animal);
					if (fox_ptr != nullptr)
					{
						std::pair<float, float> location(fox_ptr->get_x() * scale, fox_ptr->get_y() * scale);
						fox_location_vector.push_back(location);
                        Animal::next_map[x_down][y_down].fox_ptr_vec.push_back(animal);

                    }
					else
					{
						cout << "error in update_map" << endl;
						system("pause");
					}
				}
			}
		}
	}

}

void Logic::update_animal_vector()
{
	while (!new_born_prey.empty())
	{
		//cout << " new born prey!" << endl;
		//system("pause");
		Prey* prey_ptr = new_born_prey.front();
		//cow_vector.push_back(cow_ptr);
		int x_down = prey_ptr->get_x();
		int y_down = prey_ptr->get_y();
		Animal::next_map[x_down][y_down].animals_ptr_vec.push_back(prey_ptr);
        Hare* hare_ptr = dynamic_cast<Hare*>(prey_ptr);
        if (hare_ptr != nullptr)
        {
            Animal::next_map[x_down][y_down].hare_ptr_vec.push_back(hare_ptr);
        }
        else {
            Cow *cow_ptr = dynamic_cast<Cow *>(prey_ptr);
            if (cow_ptr != nullptr) {
                Animal::next_map[x_down][y_down].cow_ptr_vec.push_back(cow_ptr);
            }
            else {
                cout << "error in update_animal_vector prey" << endl;
                system("pause");
            }
        }

        prey_list.push_back(prey_ptr);
		poop_node* pn = new poop_node();
		pn->animal_ptr = prey_ptr;
		pn->id = prey_ptr->get_id();
		if (poop_head == nullptr)
		{
			poop_head = pn;
			poop_tail = pn;
		}
		else
		{
			poop_tail->next_pp_node = pn;
			poop_tail = pn;
		}
		new_born_prey.pop();
	}
	while (!new_born_predator.empty())
	{
		//cout << " new born predator!" << endl;
		//system("pause");
		Predator* predator_ptr = new_born_predator.front();
		//tiger_vector.push_back(tiger_ptr);
		int x_down = predator_ptr->get_x();
		int y_down = predator_ptr->get_y();
		Animal::next_map[x_down][y_down].animals_ptr_vec.push_back(predator_ptr);
        Tiger* tiger_ptr = dynamic_cast<Tiger*>(predator_ptr);
        if (tiger_ptr != nullptr)
        {
            Animal::next_map[x_down][y_down].tiger_ptr_vec.push_back(tiger_ptr);
        }
        else {
            Fox *fox_ptr = dynamic_cast<Fox *>(predator_ptr);
            if (fox_ptr != nullptr) {
                Animal::next_map[x_down][y_down].fox_ptr_vec.push_back(fox_ptr);
            }
            else {
                cout << "error in update_animal_vector predator" << endl;
                system("pause");
            }
        }
        predator_list.push_back(predator_ptr);
		poop_node* pn = new poop_node();
		pn->animal_ptr = predator_ptr;
		pn->id = predator_ptr->get_id();
		if (poop_head == nullptr)
		{
			poop_head = pn;
			poop_tail = pn;
		}
		else
		{
			poop_tail->next_pp_node = pn;
			poop_tail = pn;
		}
		new_born_predator.pop();
	}
}

int check_bound(float x, int map_size)
{
	if (x < 0)
		return 0;
	else if (x >= map_size)
		return map_size - 1;
	else
		return (int)x;
}

void Logic::set_water(std::pair<float, float> center, float radius)
{
	int x_lb = check_bound(center.first - radius, map_size);
	int x_ub = check_bound(center.first + radius, map_size);
	int y_lb = check_bound(center.second - radius, map_size);
	int y_ub = check_bound(center.second + radius, map_size);
	for (int i = x_lb; i <= x_ub; i++)
	{
		for (int j = y_lb; j <= y_ub; j++)
		{
			float temp1 = pow(i - center.first, 2);
			float temp2 = pow(j - center.second, 2);
			if (sqrt(temp1 + temp2) <= radius)
			{
                Animal::current_map[i][j].state = -1;
				Animal::current_map[i][j].terrain = WATER;
				Animal::current_map[i][j].center = center;
				Animal::current_map[i][j].radius = radius;
                Animal::next_map[i][j].state = -1;
				Animal::next_map[i][j].terrain = WATER;
				Animal::next_map[i][j].center = center;
				Animal::next_map[i][j].radius = radius;
			}
		}
	}
}

void Logic::predator_delete_help(list<Predator*>::iterator& predator_ite)
{
	Tiger* tiger_ptr = dynamic_cast<Tiger*>(*predator_ite);
	if (tiger_ptr != nullptr)
	{
		delete(tiger_ptr);
        tiger_num--;
	}
	else
	{
		Fox* fox_ptr = dynamic_cast<Fox*>(*predator_ite);
		if (fox_ptr!=nullptr)
		{
			delete(fox_ptr);
            fox_num--;
		}
		else
		{
			cout << "error in delete predator" << endl;
			system("pause");
		}
	}
	predator_ite = predator_list.erase(predator_ite);
}

void Logic::prey_delete_help(list<Prey*>::iterator& prey_ite)
{
	Cow* cow_ptr = dynamic_cast<Cow*>(*prey_ite);
	if (cow_ptr != nullptr)
	{
		delete(cow_ptr);
        cow_num--;
	}
	else
	{
		Hare* hare_ptr = dynamic_cast<Hare*>(*prey_ite);
		if (hare_ptr != nullptr)
		{
			delete(hare_ptr);
            hare_num--;
		}
		else
		{
			cout << "error in delete prey" << endl;
			system("pause");
		}
	}
//	cout << "before erase prey's id is " << (*prey_ite)->get_id() << endl;
	prey_ite = prey_list.erase(prey_ite);

}

void Logic::update(float delta)
{
//	Animal::current_map = *Animal::current_map_ptr;
//	Animal::next_map = *Animal::next_map_ptr;
	long start, end;
	start = clock();
	clear_next_map();
	end = clock();
//	cout << "clear_next_map :" << end-start << endl;
	start = clock();
	cow_location_vector.clear();
	hare_location_vector.clear();
	tiger_location_vector.clear();
	fox_location_vector.clear();
	Animal::environment_refresh(now_season, now_weather);
	std::queue<Predator*> need_extra_info_predator;
	std::map<int64_t, std::pair<float, float>> prey_id_2_next_map_location;
	end = clock();
//	cout << "other :" << end - start << endl;

    start=clock();
	list<Prey*>::iterator prey_ite = prey_list.begin();
	for (; prey_ite != prey_list.end(); prey_ite++)
	{
		Prey* prey_ptr = *prey_ite;
		std::pair<float, float> prey_position(-1, -1);//default 
		bool can_reproduce_flag = false;
		prey_ptr->update_information(prey_position, can_reproduce_flag,delta);
		if (prey_position.first == -1)
		{
			cout << "error in cow_update position" << endl;
			system("pause");
		}
		//cout << "cow_position:\n" << "first = " << cow_position.first << " second = " << cow_position.second << endl;
		//cow_ptr->set_x(cow_position.first);
		//cow_ptr->set_y(cow_position.second);
		if (can_reproduce_flag)
		{
            //cout<<"reproduce prey!!--------------------"<<endl;
            //system("pause");
			reproduce_prey(prey_ptr);
		}
		if (prey_ptr->get_can_eat_grass())
		{
			int x_down = prey_ptr->get_x();
			int y_down = prey_ptr->get_y();
			Animal::current_map[x_down][y_down].eat_grass_number++;
		}
        //cout<<"prey id:"<<prey_ptr->get_id()<<endl;
		prey_id_2_next_map_location.insert(std::pair<int64_t, std::pair<float, float>>(prey_ptr->get_id(), prey_position));

	}
    end = clock();
//    cout<<"loop 1:"<<end-start<<endl;
    start=clock();
    /*
    for (int i = 0; i < cow_vector.size(); i++)
    {
        Cow* cow_ptr = cow_vector[i];
        std::pair<float, float> cow_position(-1, -1);//default
        bool can_reproduce_flag = false;
        cow_ptr->update_information(cow_position, can_reproduce_flag);
        if (cow_position.first == -1)
        {
            cout << "error in cow_update position" << endl;
            system("pause");
        }
        if (!(cow_position.first >= 0 && cow_position.first <= 99))
        {
            cow_position.first = 1;
        }
        if (!(cow_position.second >= 0 && cow_position.second <= 99))
        {
            cow_position.second = 1;
        }
        //cout << "cow_position:\n" << "first = " << cow_position.first << " second = " << cow_position.second << endl;
        //cow_ptr->set_x(cow_position.first);
        //cow_ptr->set_y(cow_position.second);
        if (can_reproduce_flag)
        {
            reproduce_cow(cow_ptr);
        }
        if (cow_ptr->get_can_eat_grass())
        {
            int x_down = cow_ptr->get_x();
            int y_down = cow_ptr->get_y();
            Animal::current_map[x_down][y_down].eat_grass_number++;
        }
        prey_id_2_next_map_location.insert(std::pair<int64_t, std::pair<float, float>>(cow_ptr->get_id(), cow_position));
    }*/
	list<Predator*>::iterator predator_ite = predator_list.begin();
	for (; predator_ite != predator_list.end(); predator_ite++)
	{
		Predator* predator_ptr = *predator_ite;

		std::pair<float, float> predator_position(-1, -1);//default 
		bool can_reproduce_flag = false;
		bool need_information = false;
		predator_ptr->update_information(predator_position, can_reproduce_flag, need_information, prey_id_2_next_map_location,delta);
		if (predator_position.first == -1)
		{
			cout << "error in tiger_update position" << endl;
			system("pause");
		}
		predator_ptr->set_x(predator_position.first);
		predator_ptr->set_y(predator_position.second);
		if (can_reproduce_flag)
		{
			reproduce_predator(predator_ptr);
		}
		if (need_information)
		{
			need_extra_info_predator.push(predator_ptr);
			Prey* prey_ptr = dynamic_cast<Prey*>(predator_ptr->get_died_prey_ptr());
			if (prey_ptr->get_can_eat_grass())
			{
				int x_down = prey_ptr->get_x();
				int y_down = prey_ptr->get_y();
				Animal::current_map[x_down][y_down].eat_grass_number--;
			}
			prey_ptr->add_prey_number();
			prey_ptr->kill_animal();
		}
		else
		{
			predator_ptr->set_energy(predator_ptr->get_energy() + predator_ptr->gain_energy(delta) - predator_ptr->lose_energy(delta));
			predator_ptr->age_refresh(delta);
			predator_ptr->visible_refresh();
			if (predator_ptr->is_dead())
			{
				//check_tiger_dead(tiger_ptr, i);
				//i--;
				predator_delete_help(predator_ite);
			}
			update_map(predator_ptr);
		}
		if (predator_ite == predator_list.end())
		{
			break;
		}
	}
    end = clock();
//    cout<<"loop 2:"<<end-start<<endl;
    start=clock();
	/*
	for (int i = 0; i < tiger_vector.size(); i++)
	{
		Tiger* tiger_ptr = tiger_vector[i];
		std::pair<float, float> tiger_position(-1, -1);//default 
		bool can_reproduce_flag = false;
		bool need_information = false;
		tiger_ptr->update_information(tiger_position, can_reproduce_flag, need_information, prey_id_2_next_map_location);
		if (tiger_position.first == -1)
		{
			cout << "error in tiger_update position" << endl;
			system("pause");
		}
		tiger_ptr->set_x(tiger_position.first);
		tiger_ptr->set_y(tiger_position.second);
		if (can_reproduce_flag)
		{
			reproduce_tiger(tiger_ptr);
		}
		if (need_information)
		{
			need_extra_info_tiger.push(tiger_ptr);
			Cow* cow_ptr = dynamic_cast<Cow*>(tiger_ptr->get_died_prey_ptr());
			if (cow_ptr->get_can_eat_grass())
			{
				int x_down = cow_ptr->get_x();
				int y_down = cow_ptr->get_y();
				Animal::current_map[x_down][y_down].eat_grass_number--;
			}
			cow_ptr->add_prey_number();
			cow_ptr->kill_animal();
		}
		else
		{
			tiger_ptr->set_energy(tiger_ptr->get_energy() + tiger_ptr->gain_energy() - tiger_ptr->lose_energy());
		}

		tiger_ptr->age_refresh();
		tiger_ptr->visible_refresh();
		if (tiger_ptr->is_dead())
		{
			check_tiger_dead(tiger_ptr, i);
			i--;
		}
		update_map(tiger_ptr);
	}
	*/
	while (!need_extra_info_predator.empty())
	{
		Predator* predator_ptr = need_extra_info_predator.front();
		need_extra_info_predator.pop();
		Prey* prey_ptr = dynamic_cast<Prey*>(predator_ptr->get_died_prey_ptr());
		float percentage = (float)(1) / (float)prey_ptr->get_prey_number();
		predator_ptr->set_extra_information(percentage);
		predator_ptr->set_energy(predator_ptr->get_energy() + predator_ptr->gain_energy(delta) - predator_ptr->lose_energy(delta));
		predator_ptr->age_refresh(delta);
		predator_ptr->visible_refresh();
		if (predator_ptr->is_dead())
		{
			//cout << "predator id = " << predator_ptr->get_id() << endl;
			//vector<Tiger*>::iterator ite = find(tiger_vector.begin(), tiger_vector.end(), tiger_ptr);
			//tiger_vector.erase(ite);
			list<Predator*>::iterator predator_ite_delete = find(predator_list.begin(), predator_list.end(), predator_ptr);
			if (predator_ite_delete == predator_list.end())
			{
				cout << "error in need extra info predator delete, cannot find the predator." << endl;
				system("pause");
			}
			predator_delete_help(predator_ite_delete);
		}
		update_map(predator_ptr);
	}
    end = clock();
//    cout<<"loop 3:"<<end-start<<endl;
    start=clock();
	prey_ite = prey_list.begin();
	for (; prey_ite != prey_list.end(); prey_ite++)
	{
		Prey* prey_ptr = *prey_ite;
		if (!prey_ptr->is_dead())
		{
			map<int64_t, std::pair<float, float>>::iterator ite;
			ite = prey_id_2_next_map_location.find(prey_ptr->get_id());
			if (ite != prey_id_2_next_map_location.end())
			{
				float x = ite->second.first;
                float y = ite->second.second;
				prey_ptr->set_x(x);
				prey_ptr->set_y(y);
			}
			else
			{
				cout << "prey didn't find it's position in map" << endl;
				system("pause");
			}
			float grass_consume = 0;
			int x_down = prey_ptr->get_x();
			int y_down = prey_ptr->get_y();
			//int eat_grass_number = Animal::current_map[x_down][y_down].eat_grass_number;//useless? 
			prey_ptr->set_energy(prey_ptr->get_energy() + prey_ptr->gain_energy(grass_consume,delta) - prey_ptr->lose_energy(delta));
			Animal::next_map[x_down][y_down].state -= grass_consume;
			if (Animal::next_map[x_down][y_down].state < -0.2&&Animal::next_map[x_down][y_down].terrain==GRASS)
			{
				cout << "in x = " << x_down << " y = " << y_down << endl;
				cout << "grass state = " << Animal::next_map[x_down][y_down].state << endl;
				cout << "grass consume = " << grass_consume << endl;
				cout << "error in eat grass" << endl;
				system("pause");
			}
			prey_ptr->age_refresh(delta);
			prey_ptr->visible_refresh();
			if (prey_ptr->is_dead())
			{
				//check_cow_dead(cow_ptr, i);
				//i--;
                //cout<<"prey id = "<<prey_ptr->get_id()<<endl;
				prey_delete_help(prey_ite);
			}
			else
			{
                //cout<<"prey id in update_map = "<<prey_ptr->get_id()<<endl;
				update_map(prey_ptr);
			}
		}
		else
		{
			//check_cow_dead(cow_ptr, i);
			//i--;
			prey_delete_help(prey_ite);
		}
		if (prey_ite == prey_list.end())
		{
			break;
		}
	}
    end = clock();
//    cout<<"loop 4:"<<end-start<<endl;
	/*
	for (int i = 0; i < cow_vector.size(); i++)
	{
		Cow* cow_ptr = cow_vector[i];
		if (!cow_ptr->is_dead())
		{
			map<int64_t, std::pair<float, float>>::iterator ite;
			ite = prey_id_2_next_map_location.find(cow_ptr->get_id());
			if (ite != prey_id_2_next_map_location.end())
			{
				int x = ite->second.first;
				int y = ite->second.second;
				cow_ptr->set_x(x);
				cow_ptr->set_y(y);
			}
			else
			{
				cout << "cow didn't find it's position in map" << endl;
				system("pause");
			}
			float grass_consume=0;
			int x_down = cow_ptr->get_x();
			int y_down = cow_ptr->get_y();
			int eat_grass_number = Animal::current_map[x_down][y_down].eat_grass_number;
			cow_ptr->set_energy(cow_ptr->get_energy() + cow_ptr->gain_energy(eat_grass_number,grass_consume) - cow_ptr->lose_energy());
			Animal::next_map[x_down][y_down].state -= grass_consume;
			if (Animal::next_map[x_down][y_down].state < 0)
			{
				cout << "error in eat grass" << endl;
				system("pause");
			}
			cow_ptr->age_refresh();
			cow_ptr->visible_refresh();
			if (cow_ptr->is_dead())
			{
				check_cow_dead(cow_ptr, i);
				i--;
			}
			else
			{
				update_map(cow_ptr);
			}
		}
		else
		{
			check_cow_dead(cow_ptr, i);
			i--;
		}
	}
	*/
	start = clock();
	update_poop_list(delta);
	end = clock();
//	cout << "update_poop_list :" << end - start << endl;
	start = clock();
	update_map_state(delta);
	end = clock();
//	cout << "update_map_state :" << end - start << endl;
	start = clock();
	update_grid_map();
	end = clock();
//	cout << "update_grid_map :" << end - start << endl;
	start = clock();
	update_animal_vector();
	end = clock();
//	cout << "update_animal_vector :" << end - start << endl;
	start = clock();
	season_change(delta);
	end = clock();
//	cout << "season_change :" << end - start << endl;
	start = clock();
	weather_change(delta);
	end = clock();
//	cout << "weather_change :" << end - start << endl;
	start = clock();
	//std::vector<std::vector<Node>>* temp_map_ptr;
//	temp_map_ptr = Animal::current_map_ptr;
//	Animal::current_map_ptr = Animal::next_map_ptr;
//	Animal::next_map_ptr = temp_map_ptr;
    Animal::current_map = Animal::next_map;
	end = clock();
//	cout << "Animal::current_map = Animal::next_map :" << end - start << endl;
}
	