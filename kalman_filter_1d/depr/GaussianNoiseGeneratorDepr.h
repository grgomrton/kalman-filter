#pragma once

#include <random>
#include "IGaussianNoiseGeneratorDepr.h"

class GaussianNoiseGeneratorDepr : public IGaussianNoiseGeneratorDepr {
public:
    GaussianNoiseGeneratorDepr();
    double getNoise(double standardDeviation) override;
private:
    std::default_random_engine generator;
};
