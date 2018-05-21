#pragma once

#include "IMovingObjectContainer.h"

class World : public IMovingObjectContainer {
public:
    World(double robotPosition, IGaussianNoiseGenerator& noiseGenerator);
    double getRealRobotPosition();
    void moveCommandExecuted(IMovingObject& robot, double distance) override;
private:
    IGaussianNoiseGenerator& noiseGenerator;
    double robotPosition;
    double percentageToMultiplier(double percentage);
};
