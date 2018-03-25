#include <stdexcept>
#include "Robot.h"

Robot::Robot(double moveCommandAccuracyInPercentage, ILocalizer& localizer, IMovingObjectPositionStore& world) :
        moveCommandAccuracyInPercentage(moveCommandAccuracyInPercentage),
        localizer(localizer),
        world(world)
{
    if (moveCommandAccuracyInPercentage <= 0.0) {
        throw std::invalid_argument("moveCommandAccuracyInPercentage cannot be smaller than or equal to zero");
    }
}

void Robot::move(double distanceInMetres)
{
    localizer.moveCommandExecuted(distanceInMetres);
    world.moveCommandExecuted(*this, distanceInMetres);
}

double Robot::getMoveCommandAccuracyInPercentage()
{
    return moveCommandAccuracyInPercentage;
}