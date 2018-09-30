#pragma once

#include <random>

class GaussianNoise {
public:
    GaussianNoise();

    double getNoise(double std_dev);

private:
    std::default_random_engine _generator;
};
