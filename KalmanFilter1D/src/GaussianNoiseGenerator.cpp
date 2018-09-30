#include "GaussianNoiseGenerator.h"

GaussianNoiseGenerator::GaussianNoiseGenerator() :
        generator(std::random_device()())
    {};

double GaussianNoiseGenerator::getNoise(double standardDeviation) {
    std::normal_distribution<double> distribution(0.0, standardDeviation);
    return distribution(generator);
}