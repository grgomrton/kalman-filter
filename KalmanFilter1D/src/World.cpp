#include "IGaussianNoiseGenerator.h"
#include "World.h"

World::World(const IObservableRobot& robot, double robotPosition, IGaussianNoiseGenerator& noiseGenerator) :
        robotPosition(robotPosition),
        noiseGenerator(noiseGenerator),
        robotMovementAccuracyInPercentage(robot.getMoveCommandAccuracyInPercentage())
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