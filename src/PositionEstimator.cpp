#include <stdexcept>
#include <math.h>
#include "PositionEstimator.h"

PositionEstimator::PositionEstimator(double initialPosition, double initialAccuracy, double movementAccuracyInPercentage) :
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

double PositionEstimator::getEstimatedPosition() {
    return currentPosition;
}

double PositionEstimator::getEstimationAccuracy() {
    return covarianceToAccuracy(currentCovariance);
}

void PositionEstimator::moveCommandExecuted(double distance) {
    double covarianceOfExecutionError = accuracyToCovariance(accuracyOfMoveCommad(distance));
    double meanAfterMove = currentPosition + distance;
    double covarianceAfterMove = currentCovariance + covarianceOfExecutionError;

    currentPosition = meanAfterMove;
    currentCovariance = covarianceAfterMove;
}

void PositionEstimator::measurementReceived(double measuredPosition, double measurementAccuracy) {
    double covarianceOfMeasurementError = accuracyToCovariance(measurementAccuracy);
    double gain = currentCovariance / (currentCovariance + covarianceOfMeasurementError);
    double meanAfterMeasurement = currentPosition + gain * (measuredPosition - currentPosition);
    double covarianceAfterMeasurement = (1 - gain) * currentCovariance;

    currentPosition = meanAfterMeasurement;
    currentCovariance = covarianceAfterMeasurement;
}

double PositionEstimator::accuracyToCovariance(double accuracy) {
    auto standardDeviation = accuracy / 2.0;
    return pow(standardDeviation, 2.0);
}

double PositionEstimator::covarianceToAccuracy(double covariance) {
    return sqrt(covariance) * 2.0;
}

double PositionEstimator::percentageToMultiplier(double percentage) {
    return percentage / 100.0;
}

double PositionEstimator::accuracyOfMoveCommad(double distance) {
    return distance * distanceMultiplier;
}
