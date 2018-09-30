#pragma once

#include <functional>
#include <vector>
#include <memory>
#include "ILocalizer.h"
#include "World.h"

class Robot {
public:
    Robot(double moveCommandAccuracyInPercentage, const std::shared_ptr<IWorld>& world, const std::shared_ptr<ILocalizer>& localizer);

    void move(double distanceInMetres);

    double getMoveCommandAccuracyInPercentage() const;

private:
    double moveCommandAccuracyInPercentage;
    std::shared_ptr<IWorld> world;
    std::shared_ptr<ILocalizer> localizer;

};
