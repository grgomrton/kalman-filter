#pragma once

#include <random>

class Gaussian_noise {
public:
    Gaussian_noise();

    double get_noise(double std_dev);

private:
    static const double distribution_mean;
    std::default_random_engine generator;
};
