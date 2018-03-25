#include "World.h"

World::World(double robotPosition) :
        robotPosition(robotPosition),
        generator(std::random_device()())
{
}

double World::getRealRobotPosition() {
    return robotPosition;
}

void World::moveCommandExecuted(IMovingObject& robot, double distance) {
    double meanAfterExecution = robotPosition + distance;
    double standardDeviation = distance * percentageToMultiplier(robot.getMoveCommandAccuracyInPercentage()) / 2.0;
    std::normal_distribution<double> distribution(meanAfterExecution, standardDeviation);

    double newPositionWithAddedNoise = distribution(generator);

    robotPosition = newPositionWithAddedNoise;
}

double World::percentageToMultiplier(double percentage) {
    return percentage / 100.0;
}