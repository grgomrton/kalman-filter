#include "catch2/catch.hpp"
#include "snowhouse/snowhouse.h"
#include "../src/PositionEstimator.h"
// TODO add include library (?)

using namespace snowhouse;

TEST_CASE("After initialization the estimated position should be identical with the passed one") {
    double initialPositionInMetres = 5.0;
    double initialAccuracyInMetres = 0.05;
    double accuracyOfMoveCommandInPercentage = 8.0;
    double precision = 0.001;

    PositionEstimator estimator(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);
    auto estimatedPosition = estimator.getEstimatedPosition();

    AssertThat(estimatedPosition, Is().EqualToWithDelta(initialPositionInMetres, precision));
}

TEST_CASE("After initialization the estimated accuracy should be identical with the passed one") {
    double initialPosition = 5.0;
    double initialAccuracy = 0.05;
    double accuracyOfMoveCommandInPercentage = 8.0;
    double precision = 0.001;

    PositionEstimator estimator(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage);
    auto estimatedAccuracy = estimator.getEstimationAccuracy();

    AssertThat(estimatedAccuracy, Is().EqualToWithDelta(initialAccuracy, precision));
}

TEST_CASE("Initial accuracy should not be negative") {
    double initialPosition = 5.0;
    double initialAccuracy = -0.05;
    double accuracyOfMoveCommandInPercentage = 8.0;

    AssertThrows(std::invalid_argument, PositionEstimator(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage));
    AssertThat(LastException<std::invalid_argument>().what(), Is().Containing("initialAccuracy"));
}

TEST_CASE("Initial accuracy should not be zero") {
    double initialPosition = 5.0;
    double initialAccuracy = 0.0;
    double accuracyOfMoveCommandInPercentage = 8.0;

    AssertThrows(std::invalid_argument, PositionEstimator(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage));
    AssertThat(LastException<std::invalid_argument>().what(), Is().Containing("initialAccuracy"));
}


TEST_CASE("Movement accuracy should not be negative") {
    double initialPosition = 5.0;
    double initialAccuracy = 0.05;
    double accuracyOfMoveCommandInPercentage = -8.0;

    AssertThrows(std::invalid_argument, PositionEstimator(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage));
    AssertThat(LastException<std::invalid_argument>().what(), Is().Containing("movementAccuracy"));
}

TEST_CASE("Movement accuracy should not be zero") {
    double initialPosition = 5.0;
    double initialAccuracy = 0.05;
    double accuracyOfMoveCommandInPercentage = 0.0;

    AssertThrows(std::invalid_argument, PositionEstimator(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage));
    AssertThat(LastException<std::invalid_argument>().what(), Is().Containing("movementAccuracy"));
}

TEST_CASE("After a movement the mean should move to the endpoint of the command") {
    double initialPositionInMetres = 5.0;
    double initialAccuracyInMetres = 0.05;
    double distanceInMetres = 1.0;
    double accuracyOfMoveCommandInPercentage = 8.0;
    double expectedPositionAfterMove = 6.0;
    double precision = 0.001;
    PositionEstimator estimator(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);

    estimator.moveCommandExecuted(distanceInMetres);
    auto estimatedPosition = estimator.getEstimatedPosition();

    AssertThat(estimatedPosition, Is().EqualToWithDelta(expectedPositionAfterMove, precision));
}


TEST_CASE("After a movement the accuracy should be in a higher range") {
    double initialPositionInMetres = 5.0;
    double initialAccuracyInMetres = 0.05;
    double distanceInMetres = 1.0;
    double accuracyOfMoveCommandInPercentage = 8.0;
    PositionEstimator estimator(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);

    estimator.moveCommandExecuted(distanceInMetres);
    auto estimationAccuracy = estimator.getEstimationAccuracy();

    AssertThat(estimationAccuracy, Is().GreaterThan(initialAccuracyInMetres));
}

TEST_CASE("After a measurement the mean should move in between the original and the measured one") {
    double initialPositionInMetres = 3.0;
    double initialAccuracyInMetres = 0.5;
    double measuredPositionInMetres = 3.3;
    double accuracyOfMeasurementInMetres = 0.5;
    double accuracyOfMoveCommandInPercentage = 8.0;
    PositionEstimator estimator(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);

    estimator.measurementReceived(measuredPositionInMetres, accuracyOfMeasurementInMetres);
    auto estimatedPosition = estimator.getEstimatedPosition();

    AssertThat(estimatedPosition, Is().GreaterThan(initialPositionInMetres).And().LessThan(measuredPositionInMetres));
}

TEST_CASE("After a measurement the accuracy should be in a smaller range") {
    double initialPositionInMetres = 3.0;
    double initialAccuracyInMetres = 0.5;
    double measuredPositionInMetres = 3.3;
    double accuracyOfMeasurementInMetres = 0.5;
    double accuracyOfMoveCommandInPercentage = 8.0;
    PositionEstimator estimator(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);

    estimator.measurementReceived(measuredPositionInMetres, accuracyOfMeasurementInMetres);
    auto estimationAccuracyAfterMeasurement = estimator.getEstimationAccuracy();

    AssertThat(estimationAccuracyAfterMeasurement, Is().LessThan(initialAccuracyInMetres));
}

TEST_CASE("Interesting that the certainty after measurement is independent of the distance") {
    double initialPosition = 3.0;
    double initialAccuracy = 0.5;
    double measuredPositionOfCloseMeasurement = 3.3;
    double accuracyOfCloseMeasurement = 0.5;
    double measuredPositionOfDistantMeasurement = 5.3;
    double accuracyOfDistantMeasurement = 0.5;
    double accuracyOfMoveCommandInPercentage = 8.0;
    double precision = 0.001;
    double magnitudeOfComparisonPrecision = 0.01;
    PositionEstimator estimatorForCloseMeasurement(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage);
    PositionEstimator estimatorForDistantMeasurement(initialPosition, initialAccuracy, accuracyOfMoveCommandInPercentage);

    estimatorForCloseMeasurement.measurementReceived(measuredPositionOfCloseMeasurement, accuracyOfCloseMeasurement);
    auto estimationAccuracyAfterCloseMeasurement = estimatorForCloseMeasurement.getEstimationAccuracy();
    estimatorForDistantMeasurement.measurementReceived(measuredPositionOfDistantMeasurement, accuracyOfDistantMeasurement);
    auto estimationAccuracyAfterDistantMeasurement = estimatorForDistantMeasurement.getEstimationAccuracy();

    AssertThat(estimationAccuracyAfterCloseMeasurement, Is().GreaterThan(magnitudeOfComparisonPrecision));
    AssertThat(estimationAccuracyAfterDistantMeasurement, Is().GreaterThan(magnitudeOfComparisonPrecision));
    AssertThat(estimationAccuracyAfterCloseMeasurement, Is().EqualToWithDelta(estimationAccuracyAfterDistantMeasurement, precision));
}

// Follows Figure 3.2 (a, b, c) from
// Thrun, S., Burgard, W.,, Fox, D. (2006). Probabilistic Robotics (Intelligent Robotics and Autonomous Agents).
TEST_CASE("After a close measurement the accuracy should be in smaller range than both the initial and the measured one") {
    double initialPositionInMetres = 8.0;
    double initialAccuracyInMetres = 8.0;
    double measuredPositionInMetres = 6.0;
    double accuracyOfMeasurementInMetres = 4.0;
    double accuracyOfMoveCommandInPercentage = 8.0;
    double expectedMean = 6.5;
    double expectedAccuracy = 3.6;
    double precisionForPosition = 0.1;
    double precisionForAccuracy = 0.05;
    PositionEstimator estimator(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);

    estimator.measurementReceived(measuredPositionInMetres, accuracyOfMeasurementInMetres);
    auto estimatedPosition = estimator.getEstimatedPosition();
    auto estimationAccuracy = estimator.getEstimationAccuracy();

    AssertThat(estimatedPosition, Is().EqualToWithDelta(expectedMean, precisionForPosition));
    AssertThat(estimationAccuracy, Is().EqualToWithDelta(expectedAccuracy, precisionForAccuracy));
}

// Follows Figure 3.2 (c, d) from
// Thrun, S., Burgard, W.,, Fox, D. (2006). Probabilistic Robotics (Intelligent Robotics and Autonomous Agents).
TEST_CASE("After a measurement the move should introduce uncertainty") {
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
    PositionEstimator estimator(initialPositionInMetres, initialAccuracyInMetres, accuracyOfMoveCommandInPercentage);

    estimator.measurementReceived(measuredPositionInMetres, accuracyOfMeasurementInMetres);
    estimator.moveCommandExecuted(distanceInMetres);
    auto estimatedPosition = estimator.getEstimatedPosition();
    auto estimationAccuracy = estimator.getEstimationAccuracy();

    AssertThat(estimatedPosition, Is().EqualToWithDelta(expectedMean, precisionForPosition));
    AssertThat(estimationAccuracy, Is().EqualToWithDelta(expectedAccuracy, precisionForAccuracy));
}