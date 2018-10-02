#include <GaussianDistributionDescriptor.h>

#include <cmath>

GaussianDistributionDescriptor
GaussianDistributionDescriptor::makeFromAccuracy(double position, double accuracy) { // todo test
    return {position, accuracyToVariance(accuracy)};
}

GaussianDistributionDescriptor
GaussianDistributionDescriptor::makeFromVariance(double position, double variance) { // test
    return {position, variance};
}

double GaussianDistributionDescriptor::accuracyToVariance(double accuracy) {
    auto standardDeviation = accuracy / 2.0;
    return pow(standardDeviation, 2.0);
}

double GaussianDistributionDescriptor::varianceToAccuracy(double variance) {
    return sqrt(variance) * 2.0;
}

double GaussianDistributionDescriptor::getPosition() {
    return _position;
}

double GaussianDistributionDescriptor::getVariance() {
    return _variance;
}

double GaussianDistributionDescriptor::getAccuracy() {
    return varianceToAccuracy(_variance);
}

GaussianDistributionDescriptor::GaussianDistributionDescriptor(double position, double variance)
        : _position(position), _variance(variance) {}
