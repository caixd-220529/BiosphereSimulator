//
// Created by csyq on 2023/5/27.
// To display Chinese, use:
// system("chcp 65001");
// To output normally in debug mode, use:
// setbuf(stdout,NULL);
//

#include "distancenode.h"
#include<iostream>
#include<cmath>
#include<algorithm>
using namespace std;

vector<DistanceNode> DistanceNode::search_sequence = vector<DistanceNode>(0);

DistanceNode::DistanceNode(int xp, int yp, double radian_shift_factor){
    this->x = xp;
    this->y = yp;
    this->distance = sqrt(pow(x, 2) + pow(y, 2));
    if(this->distance!=0){
        this->pseudo_radian = acos(this->x / this->distance);
        if(this->y<0){
            this->pseudo_radian+=acos(-1.0);
        }
    }

    this->pseudo_radian -= acos(radian_shift_factor);
    // 2.0*rand()/RAND_MAX-1.0
    if(this->pseudo_radian<0){
        this->pseudo_radian += 2 * acos(-1.0);
    }
}

bool DistanceNode::operator<(DistanceNode n2) const{
    if(this->distance<n2.distance){
        return true;
    }
    else if(this->distance>n2.distance){
        return false;
    }
    else{
        return this->pseudo_radian < n2.pseudo_radian;
    }
}

void DistanceNode::search_sequence_generation(int cow_eyesight, int hare_eyesight, int tiger_eyesight, int fox_eyesight,
                                              float prey_sunny_eyesight_factor, float predator_sunny_eyesight_factor,
                                              float fluctuating_range_of_animal_parameter) {
    float maximum_eyesight = cow_eyesight*prey_sunny_eyesight_factor;
    if(hare_eyesight>cow_eyesight){
        maximum_eyesight = hare_eyesight*prey_sunny_eyesight_factor;
    }
    if(tiger_eyesight*predator_sunny_eyesight_factor>maximum_eyesight){
        maximum_eyesight = predator_sunny_eyesight_factor*tiger_eyesight;
    }
    if(fox_eyesight*predator_sunny_eyesight_factor>maximum_eyesight){
        maximum_eyesight = predator_sunny_eyesight_factor*fox_eyesight;
    }
    maximum_eyesight*=(fluctuating_range_of_animal_parameter+1);
    maximum_eyesight = int(maximum_eyesight+1);
    cout<<"maximum_eyesight_is: "<<maximum_eyesight<<endl;
    for(int i=-int(maximum_eyesight);i<=int(maximum_eyesight);i++){
        for(int j=-int(maximum_eyesight);j<=int(maximum_eyesight);j++){
            // assume no shift
            DistanceNode::search_sequence.emplace_back(i, j, 0);
        }
    }
    sort(search_sequence.begin(), search_sequence.end());
}

