#pragma once

class IMovingObject {
public:
    virtual double getMoveCommandAccuracyInPercentage() = 0;
    virtual ~IMovingObject() = default;
};
