#include <stdexcept>
#include <cmath>
#include "Localizer.h"

Localizer::Localizer(double initialPosition, double initialAccuracy, double movementAccuracyInPercentage) :
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

double Localizer::getEstimatedPosition() {
    return currentPosition;
}

double Localizer::getEstimationAccuracy() {
    return covarianceToAccuracy(currentCovariance);
}

void Localizer::onRobotMoveCommandReceived(double distance) {
    double covarianceOfExecutionError = accuracyToCovariance(accuracyOfMoveCommad(distance));
    double meanAfterMove = currentPosition + distance;
    double covarianceAfterMove = currentCovariance + covarianceOfExecutionError;

    currentPosition = meanAfterMove;
    currentCovariance = covarianceAfterMove;
}

void Localizer::measurementReceived(double measuredPosition, double measurementAccuracy) {
    double covarianceOfMeasurementError = accuracyToCovariance(measurementAccuracy);
    double gain = currentCovariance / (currentCovariance + covarianceOfMeasurementError);
    double meanAfterMeasurement = currentPosition + gain * (measuredPosition - currentPosition);
    double covarianceAfterMeasurement = (1 - gain) * currentCovariance;

    currentPosition = meanAfterMeasurement;
    currentCovariance = covarianceAfterMeasurement;
}

double Localizer::accuracyToCovariance(double accuracy) {
    auto standardDeviation = accuracy / 2.0;
    return pow(standardDeviation, 2.0);
}

double Localizer::covarianceToAccuracy(double covariance) {
    return sqrt(covariance) * 2.0;
}

double Localizer::percentageToMultiplier(double percentage) {
    return percentage / 100.0;
}

double Localizer::accuracyOfMoveCommad(double distance) {
    return distance * distanceMultiplier;
}
