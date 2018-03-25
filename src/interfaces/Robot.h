#ifndef KALMAN_FILTER_ROBOT_H
#define KALMAN_FILTER_ROBOT_H


#include "ILocalizer.hpp"
#include "IRobotPositionMaintainer.hpp"

class Robot {
public:
    Robot(ILocalizer& localizer, IRobotPositionMaintainer& world);
    void move(double distanceInMetres);

private:
    ILocalizer& localizer;
    IRobotPositionMaintainer& world;
};


#endif //KALMAN_FILTER_ROBOT_H
