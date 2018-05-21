#pragma once

#include "IMovingObject.h"
#include "ILocalizer.h"
#include "IMovingObjectPositionStore.h"

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
