//
// Created by csyq on 2023/5/27.
// To display Chinese, use:
// system("chcp 65001");
// To output normally in debug mode, use:
// setbuf(stdout,NULL);
//

#ifndef BIOSPHERESIMULATOR_DISTANCENODE_H
#define BIOSPHERESIMULATOR_DISTANCENODE_H
#include <vector>

struct DistanceNode{
    double distance;
    double pseudo_radian;
    int x;
    int y;
    static std::vector<DistanceNode> search_sequence;
    explicit DistanceNode(int xp=0, int yp=0, double radian_shift_factor=0);
    bool operator<(DistanceNode n2) const;
    static void search_sequence_generation(int cow_eyesight, int hare_eyesight,
                                           int tiger_eyesight, int fox_eyesight,
                                           float prey_sunny_eyesight_factor,
                                           float predator_sunny_eyesight_factor,
                                           float fluctuating_range_of_animal_parameter);
};


#endif //BIOSPHERESIMULATOR_DISTANCENODE_H
