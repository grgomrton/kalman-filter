#include <stdexcept>
#include "Robot.h"

Robot::Robot(double moveCommandAccuracyInPercentage) :
        moveCommandAccuracyInPercentage(moveCommandAccuracyInPercentage),
        listeners()
{
    if (moveCommandAccuracyInPercentage <= 0.0) {
        throw std::invalid_argument("moveCommandAccuracyInPercentage cannot be smaller than or equal to zero");
    }
}

void Robot::move(double distanceInMetres)
{
    for (auto& listener : listeners) {
        listener(distanceInMetres);
    }
}

double Robot::getMoveCommandAccuracyInPercentage()
{
    return moveCommandAccuracyInPercentage;
}

void Robot::addRobotMoveCommandReceivedListener(std::function<void(double)> listener) {
    listeners.push_back(listener); // TODO no equality check for std::function > no double subscr check and no unsubscribe
}
