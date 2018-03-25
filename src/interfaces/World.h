#ifndef KALMAN_FILTER_WORLD_H
#define KALMAN_FILTER_WORLD_H


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


#endif //KALMAN_FILTER_WORLD_H
