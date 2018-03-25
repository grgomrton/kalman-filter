#pragma once

#include "ILocalizer.hpp"

///
/// A one-dimensional Kalman filter which can be used to maintain a gaussian estimation
/// of the current robot position incorporating move commands and measurements.
///
class GaussianLocalizer : public ILocalizer {
public:
    /// Initializes a new instance of a PositionEstimator which can be used to
    /// maintain a gaussian estimation of the current robot position incorporating
    /// move commands and measurements.
    /// \param initialPosition
    /// The position in the one-dimensional space where the robot currently is.
    /// The position and the accuracy settings should use the same metric.
    /// \param initialAccuracy
    /// The accuracy of the initial position estimation, where the accuracy is
    /// defined as the distance between the mean and the end of the interval
    /// where the robot is currently placed with a 95% confidence.
    /// The position and the accuracy settings should use the same metric.
    /// The accuracy must be a non-negative, non-zero value.
    /// \param movementAccuracyInPercentage
    /// The percentage of the movement distance where the robot arrives
    /// with a 95% confidence after a move command has executed.
    /// The percentage must be a non-negative, non-zero value.
    GaussianLocalizer(double initialPosition, double initialAccuracy, double movementAccuracyInPercentage);
    // TODO comments
    // TODO errorRange instead of accuracy?
    void moveCommandExecuted(double distance) override;
    void measurementReceived(double measuredPosition, double measurementAccuracy) override;
    double getEstimatedPosition();
    double getEstimationAccuracy();
private:
    double currentPosition;
    double currentCovariance;
    double distanceMultiplier;
    double accuracyToCovariance(double accuracy);
    double covarianceToAccuracy(double covariance);
    double percentageToMultiplier(double percentage);
    double accuracyOfMoveCommad(double distance);
};
