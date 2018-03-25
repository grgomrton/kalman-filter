#pragma once

#include "ILocalizer.hpp"
#include "IMovingObjectPositionStore.hpp"
#include "IMovingObject.hpp"

class Robot : public IMovingObject {
public:
    Robot(double moveCommandAccuracyInPercentage, ILocalizer& localizer, IMovingObjectPositionStore& world);
    void move(double distanceInMetres);
    double getMoveCommandAccuracyInPercentage() override;
private:
    double moveCommandAccuracyInPercentage;
    ILocalizer& localizer;
    IMovingObjectPositionStore& world;
};
