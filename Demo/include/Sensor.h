#pragma once

#include <Gaussian_noise.h>

class Sensor {
public:
    explicit Sensor();
    double get_noisy_measurement(double position);
    double get_accuracy();

private:
    static const double sensor_accuracy_in_metres;
    double noise_standard_deviation;
    Gaussian_noise noise_generator;
};
