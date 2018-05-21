#pragma once

#include "IMovingObjectPositionStore.hpp"

class World : public IMovingObjectPositionStore {
public:
    World(double robotPosition, IGaussianNoiseProvider& noiseGenerator);
    double getRealRobotPosition();
    void moveCommandExecuted(IMovingObject& robot, double distance) override;
private:
    IGaussianNoiseProvider& noiseGenerator;
    double robotPosition;
    double percentageToMultiplier(double percentage);
};
