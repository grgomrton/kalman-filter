#ifndef KALMAN_FILTER_IROBOTPOSITIONMAINTAINER_H
#define KALMAN_FILTER_IROBOTPOSITIONMAINTAINER_H


#include "IMovingObject.hpp"

class IMovingObjectPositionStore {
public:
    virtual void moveCommandExecuted(IMovingObject& robot, double distance) = 0;
    virtual ~IMovingObjectPositionStore() = default;
};


#endif //KALMAN_FILTER_IROBOTPOSITIONMAINTAINER_H
