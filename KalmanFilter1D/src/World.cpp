#include "IGaussianNoiseProvider.h"
#include "World.h"

World::World(double robotPosition, IGaussianNoiseProvider& noiseGenerator) :
        robotPosition(robotPosition),
        noiseGenerator(noiseGenerator)
{
}

double World::getRealRobotPosition() {
    return robotPosition;
}

void World::moveCommandExecuted(IMovingObject& robot, double distance) {
    double standardDeviation = distance * percentageToMultiplier(robot.getMoveCommandAccuracyInPercentage()) / 2.0;
    double noise = noiseGenerator.getNoise(standardDeviation);
    robotPosition = robotPosition + distance + noise;
}

double World::percentageToMultiplier(double percentage) {
    return percentage / 100.0;
}