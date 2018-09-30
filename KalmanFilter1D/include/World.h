#pragma once

#include "IGaussianNoiseGenerator.h"
#include "IWorld.h"

class World : public IWorld {
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
