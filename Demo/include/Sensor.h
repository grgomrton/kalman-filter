#pragma once

#include <Gaussian_noise.h>

class Estimated_position;

class Sensor {
public:
    explicit Sensor();
    Estimated_position get_noisy_measurement(double position);
    double get_error_range();

private:
    static const double error_range_in_metres;
    double noise_standard_deviation;
    Gaussian_noise noise_generator;
};
