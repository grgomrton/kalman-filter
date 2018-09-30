#include "IGaussianNoiseGeneratorDepr.h"
#include "WorldDepr.h"

WorldDepr::WorldDepr(double initialRobotPosition, double movementAccuracyInPercentage, IGaussianNoiseGeneratorDepr& noiseGenerator)
        :
        robotPosition(initialRobotPosition),
        noiseGenerator(noiseGenerator),
        robotMovementAccuracyInPercentage(movementAccuracyInPercentage)
{
}

double WorldDepr::getRealRobotPosition() {
    return robotPosition;
}

void WorldDepr::onRobotMoveCommandReceived(double distance) {
    double standardDeviation = distance * percentageToMultiplier(robotMovementAccuracyInPercentage) / 2.0;
    double noise = noiseGenerator.getNoise(standardDeviation);
    robotPosition = robotPosition + distance + noise;
}

double WorldDepr::percentageToMultiplier(double percentage) {
    return percentage / 100.0;
}