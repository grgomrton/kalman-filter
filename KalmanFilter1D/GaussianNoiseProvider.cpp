#include "headers/GaussianNoiseProvider.h"

GaussianNoiseProvider::GaussianNoiseProvider() :
        generator(std::random_device()())
    {};

double GaussianNoiseProvider::getNoise(double standardDeviation) {
    std::normal_distribution<double> distribution(0.0, standardDeviation);
    return distribution(generator);
}