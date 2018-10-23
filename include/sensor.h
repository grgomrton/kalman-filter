#pragma once

#include "gaussian_noise.h"

class estimated_position;

class sensor {
public:
    explicit sensor();
    estimated_position get_noisy_measurement(double position);
    double get_error_range();

private:
    static const double error_range_in_metres_;
    double noise_standard_deviation_;
    gaussian_noise noise_generator_;

};
