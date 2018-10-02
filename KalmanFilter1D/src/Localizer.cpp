#include "Localizer.h"

Localizer::Localizer(GaussianDistributionDescriptor initialPosition) : _position(initialPosition) {

}

GaussianDistributionDescriptor Localizer::movementUpdate(double distance, double accuracyInPercentage) {
    double error_cov = GaussianDistributionDescriptor::accuracyToVariance(
            calculateAbsoluteAccuracy(distance, accuracyInPercentage));
    double prev_mean = _position.getPosition();
    double prev_cov = _position.getVariance();

    double new_mean = prev_mean + distance;
    double new_cov = prev_cov + error_cov;

    _position = GaussianDistributionDescriptor::makeFromVariance(new_mean, new_cov);
    return _position;
}

GaussianDistributionDescriptor Localizer::measurementUpdate(double measuredPosition, double absoluteAccuracy) {
    double error_cov = GaussianDistributionDescriptor::accuracyToVariance(absoluteAccuracy);
    double prev_mean = _position.getPosition();
    double prev_cov = _position.getVariance();

    double gain = prev_cov / (prev_cov + error_cov);
    double new_mean = prev_mean + gain * (measuredPosition - prev_mean);
    double new_cov = (1 - gain) * prev_cov;

    _position = GaussianDistributionDescriptor::makeFromVariance(new_mean, new_cov);
    return _position;
}

GaussianDistributionDescriptor Localizer::getPosition() {
    return _position;
}

double Localizer::calculateAbsoluteAccuracy(double distance, double accuracyInPercentage) {
    return distance * (accuracyInPercentage / 100.0);
}
