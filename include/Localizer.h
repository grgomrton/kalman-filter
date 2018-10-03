#pragma once

#include "GaussianDistributionDescriptor.h"

class Localizer {
public:
    explicit Localizer(GaussianDistributionDescriptor initialPosition);

    GaussianDistributionDescriptor movementUpdate(double distance, double accuracyInPercentage);

    GaussianDistributionDescriptor measurementUpdate(double measuredPosition, double absoluteAccuracy);

    GaussianDistributionDescriptor getPosition();

private:
    GaussianDistributionDescriptor _position;

    static double calculateAbsoluteAccuracy(double distance, double accuracyInPercentage);

};
