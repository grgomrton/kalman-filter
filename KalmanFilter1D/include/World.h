#pragma once

#include "IRobotObserver.h"
#include "IGaussianNoiseGenerator.h"

class World : public IRobotObserver {
public:
    World(double initialRobotPosition, double movementAccuracyInPercentage, IGaussianNoiseGenerator& noiseGenerator);

    double getRealRobotPosition();

    void onRobotMoveCommandReceived(double distance) override;

private:
    IGaussianNoiseGenerator& noiseGenerator;
    double robotPosition;
    double robotMovementAccuracyInPercentage;

    double percentageToMultiplier(double percentage);
};
