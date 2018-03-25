#pragma once

#include "IMovingObjectPositionStore.hpp"
#include <random>

class World : public IMovingObjectPositionStore {
public:
    World(double robotPosition);
    double getRealRobotPosition();
    void moveCommandExecuted(IMovingObject& robot, double distance) override;
private:
    double robotPosition;
    double percentageToMultiplier(double percentage);
    std::default_random_engine generator;
};
