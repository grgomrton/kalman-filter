#include <stdexcept>
#include <algorithm>
#include <exception>
#include "Robot.h"

Robot::Robot(double moveCommandAccuracyInPercentage, const std::shared_ptr<IWorld>& world, const std::shared_ptr<ILocalizer>& localizer)
        :
        moveCommandAccuracyInPercentage(moveCommandAccuracyInPercentage),
        world(world),
        localizer(localizer) {
    if (moveCommandAccuracyInPercentage <= 0.0) {
        throw std::invalid_argument("moveCommandAccuracyInPercentage must be a non-zero positive value");
    }
}

void Robot::move(double distanceInMetres) {
    world->onRobotMoveCommandReceived(distanceInMetres);
    localizer->onRobotMoveCommandReceived(distanceInMetres);
}

double Robot::getMoveCommandAccuracyInPercentage() const {
    return moveCommandAccuracyInPercentage;
}
