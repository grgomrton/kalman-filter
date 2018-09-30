#pragma once

#include "IGaussianNoiseGeneratorDepr.h"
#include "IWorldDepr.h"

class WorldDepr : public IWorldDepr {
public:
    WorldDepr(double initialRobotPosition, double movementAccuracyInPercentage, IGaussianNoiseGeneratorDepr& noiseGenerator);

    double getRealRobotPosition();

    void onRobotMoveCommandReceived(double distance) override;

private:
    IGaussianNoiseGeneratorDepr& noiseGenerator;
    double robotPosition;
    double robotMovementAccuracyInPercentage;

    double percentageToMultiplier(double percentage);
};
