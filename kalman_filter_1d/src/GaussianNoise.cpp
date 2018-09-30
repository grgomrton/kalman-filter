#include "GaussianNoise.h"

GaussianNoise::GaussianNoise() : _generator(std::random_device()()) {};

double GaussianNoise::getNoise(double std_dev) {
    std::normal_distribution<double> distribution(0.0, std_dev);
    return distribution(_generator);
}