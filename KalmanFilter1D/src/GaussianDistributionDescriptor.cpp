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

double GaussianDistributionDescriptor::varianceToAccuracy(double covariance) {
    return sqrt(covariance) * 2.0;
}

double GaussianDistributionDescriptor::getPosition() {
    return _position;
}

double GaussianDistributionDescriptor::getVariance() {
    return _covariance;
}

double GaussianDistributionDescriptor::getAccuracy() {
    return varianceToAccuracy(_covariance);
}

GaussianDistributionDescriptor::GaussianDistributionDescriptor(double position, double covariance)
        : _position(position), _covariance(covariance) {}
