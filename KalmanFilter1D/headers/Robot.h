#pragma once

#include "ILocalizer.h"
#include "../interfaces/IMovingObjectPositionStore.h"
#include "../interfaces/IMovingObject.h"

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
