#pragma once

#include "IMovingObject.hpp"

class IMovingObjectPositionStore {
public:
    virtual void moveCommandExecuted(IMovingObject& robot, double distance) = 0;
    virtual ~IMovingObjectPositionStore() = default;
};
