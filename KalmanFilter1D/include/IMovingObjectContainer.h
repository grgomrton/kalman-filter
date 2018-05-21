#pragma once

#include "IMovingObject.h"

class IMovingObjectContainer {
public:
    virtual void moveCommandExecuted(IMovingObject& robot, double distance) = 0;
    virtual ~IMovingObjectContainer() = default;
};
