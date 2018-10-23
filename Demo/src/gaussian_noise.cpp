#include <gaussian_noise.h>

const double gaussian_noise::mean_ = 0.0;

gaussian_noise::gaussian_noise() : generator_(std::random_device()()) {};

double gaussian_noise::get_noise(double standard_deviation) {
    std::normal_distribution<double> distribution(mean_, standard_deviation);
    return distribution(generator_);
}