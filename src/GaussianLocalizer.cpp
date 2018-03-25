#include <stdexcept>
#include <cmath>
#include "GaussianLocalizer.h"

GaussianLocalizer::GaussianLocalizer(double initialPosition, double initialAccuracy, double movementAccuracyInPercentage) :
    // TODO field initialization here and assert in the body?
    currentPosition(initialPosition),
    currentCovariance(accuracyToCovariance(initialAccuracy)),
    distanceMultiplier(percentageToMultiplier(movementAccuracyInPercentage))
{
    if (initialAccuracy <= 0.0) {
        throw std::invalid_argument("initialAccuracy cannot be smaller than or equal to zero");
    }
    if (movementAccuracyInPercentage <= 0.0) {
        throw std::invalid_argument("movementAccuracyInPercentage cannot be smaller than or equal to zero");
    }
}

double GaussianLocalizer::getEstimatedPosition() {
    return currentPosition;
}

double GaussianLocalizer::getEstimationAccuracy() {
    return covarianceToAccuracy(currentCovariance);
}

void GaussianLocalizer::moveCommandExecuted(double distance) {
    double covarianceOfExecutionError = accuracyToCovariance(accuracyOfMoveCommad(distance));
    double meanAfterMove = currentPosition + distance;
    double covarianceAfterMove = currentCovariance + covarianceOfExecutionError;

    currentPosition = meanAfterMove;
    currentCovariance = covarianceAfterMove;
}

void GaussianLocalizer::measurementReceived(double measuredPosition, double measurementAccuracy) {
    double covarianceOfMeasurementError = accuracyToCovariance(measurementAccuracy);
    double gain = currentCovariance / (currentCovariance + covarianceOfMeasurementError);
    double meanAfterMeasurement = currentPosition + gain * (measuredPosition - currentPosition);
    double covarianceAfterMeasurement = (1 - gain) * currentCovariance;

    currentPosition = meanAfterMeasurement;
    currentCovariance = covarianceAfterMeasurement;
}

double GaussianLocalizer::accuracyToCovariance(double accuracy) {
    auto standardDeviation = accuracy / 2.0;
    return pow(standardDeviation, 2.0);
}

double GaussianLocalizer::covarianceToAccuracy(double covariance) {
    return sqrt(covariance) * 2.0;
}

double GaussianLocalizer::percentageToMultiplier(double percentage) {
    return percentage / 100.0;
}

double GaussianLocalizer::accuracyOfMoveCommad(double distance) {
    return distance * distanceMultiplier;
}
