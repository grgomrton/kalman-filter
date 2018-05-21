#pragma once

#include "IMovingObject.h"
#include "ILocalizer.h"
#include "IMovingObjectContainer.h"

class Robot : public IMovingObject {
public:
    Robot(double moveCommandAccuracyInPercentage, ILocalizer& localizer, IMovingObjectContainer& world);
    void move(double distanceInMetres);
    double getMoveCommandAccuracyInPercentage() override;
private:
    double moveCommandAccuracyInPercentage;
    ILocalizer& localizer;
    IMovingObjectContainer& world;
};
