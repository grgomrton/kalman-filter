#ifndef KALMAN_FILTER_WORLD_H
#define KALMAN_FILTER_WORLD_H


// TODO why do i have to add this here?
#include "IMovingObjectPositionStore.hpp"

class World : public IMovingObjectPositionStore {
public:
    World(double robotPosition);
    double getRealRobotPosition();
    void moveCommandExecuted(IMovingObject& robot, double distance) override;
private:
    double robotPosition;
};


#endif //KALMAN_FILTER_WORLD_H
