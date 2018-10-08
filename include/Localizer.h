#pragma once

#include "Estimated_position.h"

class Localizer {
public:
    explicit Localizer(Estimated_position initialPosition);

    Estimated_position movementUpdate(double distance, double accuracyInPercentage);

    Estimated_position measurementUpdate(double measuredPosition, double absoluteAccuracy);

    Estimated_position getPosition();

private:
    Estimated_position _position;

    static double calculateAbsoluteAccuracy(double distance, double accuracyInPercentage);

};
