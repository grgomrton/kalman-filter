#include "IGaussianNoiseGenerator.h"
#include "World.h"

World::World(double initialRobotPosition, double movementAccuracyInPercentage, IGaussianNoiseGenerator& noiseGenerator)
        :
        robotPosition(initialRobotPosition),
        noiseGenerator(noiseGenerator),
        robotMovementAccuracyInPercentage(movementAccuracyInPercentage)
{
}

double World::getRealRobotPosition() {
    return robotPosition;
}

void World::onRobotMoveCommandReceived(double distance) {
    double standardDeviation = distance * percentageToMultiplier(robotMovementAccuracyInPercentage) / 2.0;
    double noise = noiseGenerator.getNoise(standardDeviation);
    robotPosition = robotPosition + distance + noise;
}

double World::percentageToMultiplier(double percentage) {
    return percentage / 100.0;
}