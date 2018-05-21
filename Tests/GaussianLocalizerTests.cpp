#include <GaussianLocalizer.h>
#include "catch2/catch.hpp"
#include "snowhouse/snowhouse.h"

using namespace snowhouse;

TEST_CASE("After initialization the estimated position should be identical with the passed one") {
    double initialPositionInMetres = 5.0;
    double initialAccuracyInMetres = 0.05;
    double accuracyOfMoveCommandInPercentage = 8.0;
    double precision = 0.001;

    GaussianLocalizer localizer(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);
    auto estimatedPosition = localizer.getEstimatedPosition();

    AssertThat(estimatedPosition, Is().EqualToWithDelta(initialPositionInMetres, precision));
}

TEST_CASE("After initialization the estimated accuracy should be identical with the passed one") {
    double initialPosition = 5.0;
    double initialAccuracy = 0.05;
    double accuracyOfMoveCommandInPercentage = 8.0;
    double precision = 0.001;

    GaussianLocalizer localizer(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage);
    auto estimatedAccuracy = localizer.getEstimationAccuracy();

    AssertThat(estimatedAccuracy, Is().EqualToWithDelta(initialAccuracy, precision));
}

TEST_CASE("Initial accuracy should not be negative") {
    double initialPosition = 5.0;
    double initialAccuracy = -0.05;
    double accuracyOfMoveCommandInPercentage = 8.0;

    AssertThrows(std::invalid_argument, GaussianLocalizer(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage));
    AssertThat(LastException<std::invalid_argument>().what(), Is().Containing("initialAccuracy"));
}

TEST_CASE("Initial accuracy should not be zero") {
    double initialPosition = 5.0;
    double initialAccuracy = 0.0;
    double accuracyOfMoveCommandInPercentage = 8.0;

    AssertThrows(std::invalid_argument, GaussianLocalizer(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage));
    AssertThat(LastException<std::invalid_argument>().what(), Is().Containing("initialAccuracy"));
}


TEST_CASE("Estimator movement accuracy should not be negative") {
    double initialPosition = 5.0;
    double initialAccuracy = 0.05;
    double accuracyOfMoveCommandInPercentage = -8.0;

    AssertThrows(std::invalid_argument, GaussianLocalizer(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage));
    AssertThat(LastException<std::invalid_argument>().what(), Is().Containing("movementAccuracy"));
}

TEST_CASE("Estimator movement accuracy should not be zero") {
    double initialPosition = 5.0;
    double initialAccuracy = 0.05;
    double accuracyOfMoveCommandInPercentage = 0.0;

    AssertThrows(std::invalid_argument, GaussianLocalizer(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage));
    AssertThat(LastException<std::invalid_argument>().what(), Is().Containing("movementAccuracy"));
}

TEST_CASE("After a movement the mean should move to the endpoint of the command") {
    double initialPositionInMetres = 5.0;
    double initialAccuracyInMetres = 0.05;
    double distanceInMetres = 1.0;
    double accuracyOfMoveCommandInPercentage = 8.0;
    double expectedPositionAfterMove = 6.0;
    double precision = 0.001;
    GaussianLocalizer localizer(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);

    localizer.moveCommandExecuted(distanceInMetres);
    auto estimatedPosition = localizer.getEstimatedPosition();

    AssertThat(estimatedPosition, Is().EqualToWithDelta(expectedPositionAfterMove, precision));
}


TEST_CASE("After a movement the accuracy should be in a higher range") {
    double initialPositionInMetres = 5.0;
    double initialAccuracyInMetres = 0.05;
    double distanceInMetres = 1.0;
    double accuracyOfMoveCommandInPercentage = 8.0;
    GaussianLocalizer localizer(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);

    localizer.moveCommandExecuted(distanceInMetres);
    auto estimationAccuracy = localizer.getEstimationAccuracy();

    AssertThat(estimationAccuracy, Is().GreaterThan(initialAccuracyInMetres));
}

TEST_CASE("After a measurement the mean should move in between the original and the measured one") {
    double initialPositionInMetres = 3.0;
    double initialAccuracyInMetres = 0.5;
    double measuredPositionInMetres = 3.3;
    double accuracyOfMeasurementInMetres = 0.5;
    double accuracyOfMoveCommandInPercentage = 8.0;
    GaussianLocalizer localizer(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);

    localizer.measurementReceived(measuredPositionInMetres, accuracyOfMeasurementInMetres);
    auto estimatedPosition = localizer.getEstimatedPosition();

    AssertThat(estimatedPosition, Is().GreaterThan(initialPositionInMetres).And().LessThan(measuredPositionInMetres));
}

TEST_CASE("After a measurement the accuracy should be in a smaller range") {
    double initialPositionInMetres = 3.0;
    double initialAccuracyInMetres = 0.5;
    double measuredPositionInMetres = 3.3;
    double accuracyOfMeasurementInMetres = 0.5;
    double accuracyOfMoveCommandInPercentage = 8.0;
    GaussianLocalizer localizer(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);

    localizer.measurementReceived(measuredPositionInMetres, accuracyOfMeasurementInMetres);
    auto estimationAccuracyAfterMeasurement = localizer.getEstimationAccuracy();

    AssertThat(estimationAccuracyAfterMeasurement, Is().LessThan(initialAccuracyInMetres));
}

TEST_CASE("After a close measurement the accuracy should be in smaller range than both the initial and the measured one") {
    // Follows Figure 3.2 (a, b, c) from
    // Thrun, S., Burgard, W.,, Fox, D. (2006). Probabilistic Robotics (Intelligent Robotics and Autonomous Agents).
    double initialPositionInMetres = 8.0;
    double initialAccuracyInMetres = 8.0;
    double measuredPositionInMetres = 6.0;
    double accuracyOfMeasurementInMetres = 4.0;
    double accuracyOfMoveCommandInPercentage = 8.0;
    double expectedMean = 6.5;
    double expectedAccuracy = 3.6;
    double precisionForPosition = 0.1;
    double precisionForAccuracy = 0.05;
    GaussianLocalizer localizer(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);

    localizer.measurementReceived(measuredPositionInMetres, accuracyOfMeasurementInMetres);
    auto estimatedPosition = localizer.getEstimatedPosition();
    auto estimationAccuracy = localizer.getEstimationAccuracy();

    AssertThat(estimatedPosition, Is().EqualToWithDelta(expectedMean, precisionForPosition));
    AssertThat(estimationAccuracy, Is().EqualToWithDelta(expectedAccuracy, precisionForAccuracy));
}

TEST_CASE("After a measurement the move command should introduce uncertainty") {
    // Follows Figure 3.2 (c, d) from
    // Thrun, S., Burgard, W.,, Fox, D. (2006). Probabilistic Robotics (Intelligent Robotics and Autonomous Agents).
    double initialPositionInMetres = 8.0;
    double initialAccuracyInMetres = 8.0;
    double measuredPositionInMetres = 6.0;
    double accuracyOfMeasurementInMetres = 4.0;
    double distanceInMetres = 15.0;
    double accuracyOfMoveCommandInPercentage = 40.0;
    double expectedMean = 21.5;
    double expectedAccuracy = 7.0;
    double precisionForPosition = 0.1;
    double precisionForAccuracy = 0.05;
    GaussianLocalizer localizer(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);

    localizer.measurementReceived(measuredPositionInMetres, accuracyOfMeasurementInMetres);
    localizer.moveCommandExecuted(distanceInMetres);
    auto estimatedPosition = localizer.getEstimatedPosition();
    auto estimationAccuracy = localizer.getEstimationAccuracy();

    AssertThat(estimatedPosition, Is().EqualToWithDelta(expectedMean, precisionForPosition));
    AssertThat(estimationAccuracy, Is().EqualToWithDelta(expectedAccuracy, precisionForAccuracy));
}

TEST_CASE("The certainty after measurement update is independent of the distance") {
    double initialPosition = 3.0;
    double initialAccuracy = 0.5;
    double measuredPositionOfCloseMeasurement = 3.3;
    double accuracyOfCloseMeasurement = 0.5;
    double measuredPositionOfDistantMeasurement = 5.3;
    double accuracyOfDistantMeasurement = 0.5;
    double accuracyOfMoveCommandInPercentage = 8.0;
    double precision = 0.001;
    double magnitudeOfComparisonPrecision = 0.01;
    GaussianLocalizer localizerForCloseMeasurement(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage);
    GaussianLocalizer localizerForDistantMeasurement(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage);

    localizerForCloseMeasurement.measurementReceived(measuredPositionOfCloseMeasurement, accuracyOfCloseMeasurement);
    auto estimationAccuracyAfterCloseMeasurement = localizerForCloseMeasurement.getEstimationAccuracy();
    localizerForDistantMeasurement.measurementReceived(measuredPositionOfDistantMeasurement, accuracyOfDistantMeasurement);
    auto estimationAccuracyAfterDistantMeasurement = localizerForDistantMeasurement.getEstimationAccuracy();

    AssertThat(estimationAccuracyAfterCloseMeasurement, Is().GreaterThan(magnitudeOfComparisonPrecision));
    AssertThat(estimationAccuracyAfterDistantMeasurement, Is().GreaterThan(magnitudeOfComparisonPrecision));
    AssertThat(estimationAccuracyAfterCloseMeasurement, Is().EqualToWithDelta(estimationAccuracyAfterDistantMeasurement, precision));
}