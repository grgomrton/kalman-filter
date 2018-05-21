#pragma once

#include "../interfaces/IGaussianNoiseProvider.h"
#include <random>

class GaussianNoiseProvider : public IGaussianNoiseProvider {
public:
    GaussianNoiseProvider();
    double getNoise(double standardDeviation) override;
private:
    std::default_random_engine generator;
};
