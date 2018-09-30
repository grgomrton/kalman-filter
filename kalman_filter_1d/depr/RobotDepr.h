#pragma once

#include <functional>
#include <vector>
#include <memory>
#include "ILocalizerDepr.h"
#include "WorldDepr.h"

class RobotDepr {
public:
    RobotDepr(double moveCommandAccuracyInPercentage, const std::shared_ptr<IWorldDepr>& world, const std::shared_ptr<ILocalizerDepr>& localizer);

    void move(double distanceInMetres);

    double getMoveCommandAccuracyInPercentage() const;

private:
    double moveCommandAccuracyInPercentage;
    std::shared_ptr<IWorldDepr> world;
    std::shared_ptr<ILocalizerDepr> localizer;

};
