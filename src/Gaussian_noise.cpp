#include "Gaussian_noise.h"

const double Gaussian_noise::distribution_mean = 0.0;

Gaussian_noise::Gaussian_noise() : generator(std::random_device()()) {};

double Gaussian_noise::get_noise(double std_dev) {
    std::normal_distribution<double> distribution(distribution_mean, std_dev);
    return distribution(generator);
}