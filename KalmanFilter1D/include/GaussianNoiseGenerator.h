#pragma once

#include <random>
#include "IGaussianNoiseGenerator.h"

class GaussianNoiseGenerator : public IGaussianNoiseGenerator {
public:
    GaussianNoiseGenerator();
    double getNoise(double standardDeviation) override;
private:
    std::default_random_engine generator;
};
