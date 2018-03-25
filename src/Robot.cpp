#include "Robot.h"

Robot::Robot(ILocalizer& localizer, IRobotPositionMaintainer& world) : localizer(localizer), world(world) {
}

void Robot::move(double distanceInMetres) {
    localizer.moveCommandExecuted(distanceInMetres);
    world.moveCommandExecuted(distanceInMetres);
}