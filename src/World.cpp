#include <IMovingObject.hpp>
#include "World.h"

World::World(double robotPosition) : robotPosition(robotPosition) {
}

double World::getRealRobotPosition() {
    return robotPosition;
}

void World::moveCommandExecuted(IMovingObject& robot, double distance) {
    robotPosition += distance;
}
