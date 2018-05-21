#pragma once

#include <random>
#include "IGaussianNoiseProvider.h"

class GaussianNoiseProvider : public IGaussianNoiseProvider {
public:
    GaussianNoiseProvider();
    double getNoise(double standardDeviation) override;
private:
    std::default_random_engine generator;
};
