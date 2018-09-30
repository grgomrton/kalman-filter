#pragma once

#include "IRobotObserver.h"
#include "IGaussianNoiseGenerator.h"

class World : public IRobotObserver {
public:
    World(const IObservableRobot& robot, double robotPosition, IGaussianNoiseGenerator& noiseGenerator);

    double getRealRobotPosition();

    void onRobotMoveCommandReceived(double distance) override;

private:
    IGaussianNoiseGenerator& noiseGenerator;
    double robotPosition;
    double robotMovementAccuracyInPercentage;

    double percentageToMultiplier(double percentage);
};
