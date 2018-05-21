#pragma once

#include <random>
#include "IGaussianNoiseGenerator.h"

class NoiseGenerator : public IGaussianNoiseGenerator {
public:
    NoiseGenerator();
    double getNoise(double standardDeviation) override;
private:
    std::default_random_engine generator;
};
