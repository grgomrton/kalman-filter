#include "GaussianNoiseGeneratorDepr.h"

GaussianNoiseGeneratorDepr::GaussianNoiseGeneratorDepr() :
        generator(std::random_device()())
    {};

double GaussianNoiseGeneratorDepr::getNoise(double standardDeviation) {
    std::normal_distribution<double> distribution(0.0, standardDeviation);
    return distribution(generator);
}