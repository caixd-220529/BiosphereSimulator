//
// Created by csyq on 2023/5/3.
// To display Chinese, use:
// system("chcp 65001");
// To output normally in debug mode, use:
// setbuf(stdout,NULL);
//
#include"logic.h"
#include<iostream>
#include<string>
#include <ctime>
#include "distancenode.h"

using namespace std;
void initial_vvs(vector<vector<string>>& vvs, int map_size)
{
	vvs.clear();
	for (int i = 0; i < map_size; i++)
	{
		vector<string> vs;
		for (int j = 0; j < map_size; j++)
		{
			string s1 = " ";
			vs.push_back(s1);
		}
		vvs.push_back(vs);
	}
}
void update_vvs(vector<vector<string>>& vvs, int map_size, Logic test)
{
    for (int i = 0; i < map_size; i++)
	{
		for (int j = 0; j < map_size; j++)
		{
			switch ((int)Animal::current_map[i][j].state)
			{
			case 0:
				vvs[i][j] = "0";
				break;
			case 1:
				vvs[i][j] = "1";
				break;
			case 2:
				vvs[i][j] = "2";
				break;
			case 3:
				vvs[i][j] = "3";
				break;
			}
		}
	}
	vector<pair<float, float>> location = test.get_poop_location_vector();
	for (int i = 0; i < location.size(); i++)
	{
		int x_down = location[i].first;
		int y_down = location[i].second;
		vvs[x_down][y_down] = "S";
	}
	location = test.get_cow_location_vector();
	for (int i = 0; i < location.size(); i++)
	{
		int x_down = location[i].first;
		int y_down = location[i].second;
		vvs[x_down][y_down] = "C";
	}
	location = test.get_tiger_location_vector();
	for (int i = 0; i < location.size(); i++)
	{
		int x_down = location[i].first;
		int y_down = location[i].second;
		vvs[x_down][y_down] = "T";
	}
}


void print_vvs(vector<vector<string>>& vvs, int map_size)
{
    return;
    for (int i = 0; i < map_size; i++)
	{ 
		for (int j = 0; j < map_size; j++)
		{
			cout << vvs[i][j];
		}
		cout << endl;
	}
}

int main()
{
	system("chcp 65001");
    setbuf(stdout,NULL);
	int64_t cow_num = 20;
	int64_t tiger_num = 20;
	int64_t fox_num = 20;
	int64_t hare_num = 20;
	int poop_num = 3;
	int map_size = 1024;
	int grid_size = 32;

	int grass_growth_per_frame = 0.04;
	int waste_loss_per_frame = 0.04;
	int rainy_possibility = 5;
	int max_weather_time_1 = 75;
	int max_weather_time_2 = 50;
	int max_weather_time_3 = 30;
	int max_weather_time_4 = 20;

	int rainy_possibility_1 = 30;
	int rainy_possibility_2 = 50;
	int rainy_possibility_3 = 70;
	int rainy_possibility_4 = 100;


	//Cow parameter
	float energy_cow=1500;
	float hungry_energy_cow = 4000; float reproduce_energy_cow = 4000; float baby_energy_cow = 1500;
	float calm_dis_cow= 8; float active_dis_cow= 10;
	float calm_loss_cow=0; float active_loss_cow = 0; float still_loss_cow = 10; float energy_gain_cow = 12;
	int eyesight_cow=40; int age_cow=rand()%1000; int max_age_cow=1200;
	int reproduce_possibility_cow = 30;
	int maximum_single_direction_frame_cow=37;
	float energy_efficiency_cow= 0.2;

	float eat_speed_cow = 0.04;
	int select_heap_event_cow = 3;

	//Hare parameter
	float energy_hare = 1000;
	float hungry_energy_hare = 1500; float reproduce_energy_hare = 1500; float baby_energy_hare = 1000;
	float calm_dis_hare = 6; float active_dis_hare = 11;
	float calm_loss_hare = 0; float active_loss_hare = 0; float still_loss_hare = 4; float energy_gain_hare = 12;
	int eyesight_hare = 35; int age_hare = rand() % 500; int max_age_hare = 600;
	int reproduce_possibility_hare = 30;
	int maximum_single_direction_frame_hare = 37;
	float energy_efficiency_hare = 0.2;

	float eat_speed_hare = 0.04;
	int select_heap_event_hare = 3;

	//Tiger parameter
	float energy_tiger = 2000;
	float hungry_energy_tiger = 3000; float reproduce_energy_tiger = 3000; float baby_energy_tiger = 2000;
	float calm_dis_tiger = 8; float active_dis_tiger = 15;
	float calm_loss_tiger = 0; float active_loss_tiger = 0; float still_loss_tiger = 15; float energy_gain_tiger = 20;
	int eyesight_tiger = 50; int age_tiger = rand()%1000; int max_age_tiger= 1200;
	int reproduce_possibility_tiger = 20;
	int maximum_single_direction_frame_tiger = 37;
	float energy_efficiency_tiger = 0.25;

	//Fox parameter
	float energy_fox = 1500;
	float hungry_energy_fox = 1800; float reproduce_energy_fox = 2000; float baby_energy_fox = 1200;
	float calm_dis_fox = 7; float active_dis_fox = 14;
	float calm_loss_fox = 0; float active_loss_fox = 0; float still_loss_fox = 10; float energy_gain_fox = 20;
	int eyesight_fox = 50; int age_fox = rand() % 700; int max_age_fox = 800;
	int reproduce_possibility_fox = 20;
	int maximum_single_direction_frame_fox = 37;
	float energy_efficiency_fox = 0.25;

	float scale = 4;//this value should be 1,2,4,8,16...
	map_size /= scale;
	grid_size /= scale;
	
	calm_dis_cow /= scale;
	calm_dis_fox /= scale;
	calm_dis_hare /= scale;
	calm_dis_tiger /= scale;

	active_dis_cow /= scale;
	active_dis_fox /= scale;
	active_dis_hare /= scale;
	active_dis_tiger /= scale;

	eyesight_cow /= scale;
	eyesight_fox /= scale;
	eyesight_hare /= scale;
	eyesight_tiger /= scale;

	maximum_single_direction_frame_cow /= scale;
	maximum_single_direction_frame_fox /= scale;
	maximum_single_direction_frame_hare /= scale;
	maximum_single_direction_frame_tiger /= scale;

	Logic test(map_size, grid_size , scale, cow_num, hare_num, tiger_num, fox_num, poop_num, grass_growth_per_frame,
		waste_loss_per_frame, rainy_possibility, max_weather_time_1, max_weather_time_2,
		max_weather_time_3, max_weather_time_4, rainy_possibility_1, rainy_possibility_2,
		rainy_possibility_3, rainy_possibility_4,
		//Cow parameter
		energy_cow, hungry_energy_cow, reproduce_energy_cow, baby_energy_cow, calm_dis_cow, active_dis_cow,
		calm_loss_cow, active_loss_cow, still_loss_cow, energy_gain_cow,
		eyesight_cow, age_cow, max_age_cow,
		reproduce_possibility_cow, maximum_single_direction_frame_cow,
		energy_efficiency_cow, eat_speed_cow, select_heap_event_cow,
		//Hare parameter
		energy_hare, hungry_energy_hare, reproduce_energy_hare, baby_energy_hare, calm_dis_hare, active_dis_hare,
		calm_loss_hare, active_loss_hare, still_loss_hare, energy_gain_hare,
		eyesight_hare, age_hare, max_age_hare,
		reproduce_possibility_hare, maximum_single_direction_frame_hare,
		energy_efficiency_hare, eat_speed_hare, select_heap_event_hare,
		//Tiger parameter
		energy_tiger, hungry_energy_tiger, reproduce_energy_tiger, baby_energy_tiger,
		calm_dis_tiger, active_dis_tiger,
		calm_loss_tiger, active_loss_tiger, still_loss_tiger, energy_gain_tiger,
		eyesight_tiger, age_tiger, max_age_tiger,
		reproduce_possibility_tiger, maximum_single_direction_frame_tiger,
		energy_efficiency_tiger,
		//Fox parameter
		energy_fox, hungry_energy_fox, reproduce_energy_fox, baby_energy_fox,
		calm_dis_fox, active_dis_fox,
		calm_loss_fox, active_loss_fox, still_loss_fox, energy_gain_fox,
		eyesight_fox, age_fox, max_age_fox,
		reproduce_possibility_fox, maximum_single_direction_frame_fox,
		energy_efficiency_fox);

	float sunny_eye_sight_factor_predator = 1;
	float rainy_eye_sight_factor_predator = 0.75;

	float spring_reproduce_factor_predator = 1;
	float summer_reproduce_factor_predator = 0.8;
	float autumn_reproduce_factor_predator = 0.6;
	float winter_reproduce_factor_predator = 0;

	float sunny_speed_factor_predator = 1;
	float rainy_speed_factor_predator = 0.75;

	float sunny_eye_sight_factor_prey = 1;
	float rainy_eye_sight_factor_prey = 0.8;

	float spring_reproduce_factor_prey = 1;
	float summer_reproduce_factor_prey = 0.8;
	float autumn_reproduce_factor_prey = 0.6;
	float winter_reproduce_factor_prey = 0;

	float sunny_speed_factor_prey = 1;
	float rainy_speed_factor_prey = 0.7;
	float min_state_prey_eat_grass = 1;
	float max_grass_state = 3;
	int per_grass_energy = 3000;

	per_grass_energy *= scale;

	float aggregation_factor_tiger = 0.6;

	float cow_priority=1;
	float max_cow_priority_calculate=15;
	int grass_eyesight=0;

	float fluctuating_range_of_parameter_p = 0.1;

	Predator::initial_static_value(sunny_eye_sight_factor_predator, rainy_eye_sight_factor_predator,
		spring_reproduce_factor_predator, summer_reproduce_factor_predator,
		autumn_reproduce_factor_predator, winter_reproduce_factor_predator,
		sunny_speed_factor_predator, rainy_speed_factor_predator);

	Prey::initial_static_value(sunny_eye_sight_factor_prey, rainy_eye_sight_factor_prey,
		spring_reproduce_factor_prey, summer_reproduce_factor_prey,
		autumn_reproduce_factor_prey, winter_reproduce_factor_prey,
		sunny_speed_factor_prey, rainy_speed_factor_prey, per_grass_energy,min_state_prey_eat_grass, max_grass_state);

	Tiger::set_tiger_static(aggregation_factor_tiger);

	Cow::cow_initial_static_value(cow_priority, max_cow_priority_calculate, grass_eyesight);
    DistanceNode::search_sequence_generation(eyesight_cow, eyesight_hare, eyesight_tiger, eyesight_hare,
                                             sunny_eye_sight_factor_prey, sunny_eye_sight_factor_predator,
                                             fluctuating_range_of_parameter_p);
	season_types now_sea = SPRING;
	weather_types now_wea = SUNNY;
	Animal::set_animal_static(map_size, now_sea, now_wea, fluctuating_range_of_parameter_p);
	test.initial_map();
	float water_x = 500;
	float water_y = 500;
	float water_radius = 100;
	water_x /= scale;
	water_y /= scale;
	water_radius /= scale;
	pair<float, float> water_center(water_x, water_y);
	test.set_water(water_center, water_radius);
	test.initial_animal();
	test.initial_poop_queue();

	int frames;
	cin >> frames;
	vector<vector<string>> vvs;
	
	initial_vvs(vvs, map_size);
	while (frames != -1)
	{
        for (int i = 0; i < frames; i++)
		{
            cout<<i<<" \n";
            if(i%10==0){cout<<endl;}
			int start = clock();
            test.update();
			//update_vvs(vvs, map_size, test);
			//print_vvs(vvs, map_size);
			int end = clock();
			cout << end - start << endl;
		}
        
		cin >> frames;
	}
	system("pause");
}
