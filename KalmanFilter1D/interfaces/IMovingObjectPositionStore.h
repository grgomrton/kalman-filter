#pragma once

#include "IMovingObject.h"

class IMovingObjectPositionStore {
public:
    virtual void moveCommandExecuted(IMovingObject& robot, double distance) = 0;
    virtual ~IMovingObjectPositionStore() = default;
};
