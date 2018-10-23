#pragma once

#include <random>

class gaussian_noise {
public:
    gaussian_noise();

    double get_noise(double standard_deviation);

private:
    static const double mean_;

    std::default_random_engine generator_;
};
