#include <stdexcept>
#include <algorithm>
#include <exception>
#include "RobotDepr.h"

RobotDepr::RobotDepr(double moveCommandAccuracyInPercentage, const std::shared_ptr<IWorldDepr>& world, const std::shared_ptr<ILocalizerDepr>& localizer)
        :
        moveCommandAccuracyInPercentage(moveCommandAccuracyInPercentage),
        world(world),
        localizer(localizer) {
    if (moveCommandAccuracyInPercentage <= 0.0) {
        throw std::invalid_argument("moveCommandAccuracyInPercentage must be a non-zero positive value");
    }
}

void RobotDepr::move(double distanceInMetres) {
    world->onRobotMoveCommandReceived(distanceInMetres);
    localizer->onRobotMoveCommandReceived(distanceInMetres);
}

double RobotDepr::getMoveCommandAccuracyInPercentage() const {
    return moveCommandAccuracyInPercentage;
}
