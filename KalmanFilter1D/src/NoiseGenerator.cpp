#include "NoiseGenerator.h"

NoiseGenerator::NoiseGenerator() :
        generator(std::random_device()())
    {};

double NoiseGenerator::getNoise(double standardDeviation) {
    std::normal_distribution<double> distribution(0.0, standardDeviation);
    return distribution(generator);
}