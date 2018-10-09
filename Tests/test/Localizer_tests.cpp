#include "Localizer.h"
#include "catch2/catch.hpp"

TEST_CASE("After initialization the estimated position should be identical with the passed one") {
    double initialPositionInMetres = 5.0;
    double initialAccuracyInMetres = 0.05;
    Estimated_position initial_position =
            Estimated_position::from_accuracy(initialPositionInMetres, initialAccuracyInMetres);

    Localizer localizer(initial_position);
    auto estimatedPosition = localizer.get_position();

    CHECK(estimatedPosition.get_position() == Approx(initialPositionInMetres));
    CHECK(estimatedPosition.get_accuracy() == Approx(initialAccuracyInMetres));
}

TEST_CASE("After a movement the mean should move to the endpoint of the command") {
    double initialPositionInMetres = 5.0;
    double initialAccuracyInMetres = 0.05;
    Estimated_position initial_position =
            Estimated_position::from_accuracy(initialPositionInMetres, initialAccuracyInMetres);
    double distanceInMetres = 1.0;
    double accuracyOfMoveCommandInPercentage = 8.0;
    double expectedPositionAfterMove = 6.0;
    Localizer localizer(initial_position);

    auto estimated_position = localizer.movement_executed(distanceInMetres, accuracyOfMoveCommandInPercentage);

    CHECK(estimated_position.get_position() == Approx(expectedPositionAfterMove));
}

TEST_CASE("After a movement the accuracy should be in a higher range") {
    double initialPositionInMetres = 5.0;
    double initialAccuracyInMetres = 0.05;
    Estimated_position initial_position =
            Estimated_position::from_accuracy(initialPositionInMetres, initialAccuracyInMetres);
    double distanceInMetres = 1.0;
    double accuracyOfMoveCommandInMetres = 0.08;
    Localizer localizer(initial_position);

    auto new_position = localizer.movement_executed(distanceInMetres, accuracyOfMoveCommandInMetres);

    CHECK(new_position.get_accuracy() > initialAccuracyInMetres);
}

TEST_CASE("After a measurement the mean should move in between the original and the measured one") {
    double initialPositionInMetres = 3.0;
    double initialAccuracyInMetres = 0.5;
    Estimated_position initial_position =
            Estimated_position::from_accuracy(initialPositionInMetres, initialAccuracyInMetres);
    double measuredPositionInMetres = 3.3;
    double accuracyOfMeasurementInMetres = 0.5;
    Localizer localizer(initial_position);

    auto new_position = localizer.measurement_received(measuredPositionInMetres, accuracyOfMeasurementInMetres);

    CHECK(new_position.get_position() > initialPositionInMetres);
    CHECK(new_position.get_position() < measuredPositionInMetres);
}

TEST_CASE("After a measurement the accuracy should be in a smaller range") {
    double initialPositionInMetres = 3.0;
    double initialAccuracyInMetres = 0.5;
    Estimated_position initial_position =
            Estimated_position::from_accuracy(initialPositionInMetres, initialAccuracyInMetres);
    double measuredPositionInMetres = 3.3;
    double accuracyOfMeasurementInMetres = 0.5;
    Localizer localizer(initial_position);

    auto new_position = localizer.measurement_received(measuredPositionInMetres, accuracyOfMeasurementInMetres);

    CHECK(new_position.get_accuracy() < initialAccuracyInMetres);
}

TEST_CASE("After a close measurement the accuracy should be in smaller range than both the initial and the measured one") {
    // Follows Figure 3.2 (a, b, c) from
    // Thrun, S., Burgard, W.,, Fox, D. (2006). Probabilistic Robotics (Intelligent Robotics and Autonomous Agents).
    double initialPositionInMetres = 8.0;
    double initialAccuracyInMetres = 8.0;
    Estimated_position initial_position =
            Estimated_position::from_accuracy(initialPositionInMetres, initialAccuracyInMetres);
    double measuredPositionInMetres = 6.0;
    double accuracyOfMeasurementInMetres = 4.0;
    double expectedMean = 6.5;
    double expectedAccuracy = 3.6;
    double precisionForPosition = 0.1;
    double precisionForAccuracy = 0.05;
    Localizer localizer(initial_position);

    auto new_position = localizer.measurement_received(measuredPositionInMetres, accuracyOfMeasurementInMetres);

    CHECK(new_position.get_position() == Approx(expectedMean).epsilon(precisionForPosition));
    CHECK(new_position.get_accuracy() == Approx(expectedAccuracy).epsilon(precisionForAccuracy));
}

TEST_CASE("After a measurement the move command should introduce uncertainty") {
    // Follows Figure 3.2 (c, d) from
    // Thrun, S., Burgard, W.,, Fox, D. (2006). Probabilistic Robotics (Intelligent Robotics and Autonomous Agents).
    double initialPositionInMetres = 8.0;
    double initialAccuracyInMetres = 8.0;
    Estimated_position initial_position =
            Estimated_position::from_accuracy(initialPositionInMetres, initialAccuracyInMetres);
    double measuredPositionInMetres = 6.0;
    double accuracyOfMeasurementInMetres = 4.0;
    double distanceInMetres = 15.0;
    double accuracyOfMoveCommandInMetres = 6;
    double expectedMean = 21.5;
    double expectedAccuracy = 7.0;
    double precisionForPosition = 0.1;
    double precisionForAccuracy = 0.05;
    Localizer localizer(initial_position);

    localizer.measurement_received(measuredPositionInMetres, accuracyOfMeasurementInMetres);
    auto last_position = localizer.movement_executed(distanceInMetres, accuracyOfMoveCommandInMetres);

    CHECK(last_position.get_position() == Approx(expectedMean).epsilon(precisionForPosition));
    CHECK(last_position.get_accuracy() == Approx(expectedAccuracy).epsilon(precisionForAccuracy));
}

TEST_CASE("The certainty after measurement update is independent of the distance") {
    double initialPosition = 3.0;
    double initialAccuracy = 0.5;
    Estimated_position initial_position =
            Estimated_position::from_accuracy(initialPosition, initialAccuracy);
    double measuredPositionOfCloseMeasurement = 3.3;
    double accuracyOfCloseMeasurement = 0.5;
    double measuredPositionOfDistantMeasurement = 5.3;
    double accuracyOfDistantMeasurement = 0.5;
    double precision = 0.001;
    double magnitudeOfComparisonPrecision = 0.01;
    Localizer localizerForCloseMeasurement(initial_position);
    Localizer localizerForDistantMeasurement(initial_position);

    auto close_measurement_position = localizerForCloseMeasurement.measurement_received(
            measuredPositionOfCloseMeasurement, accuracyOfCloseMeasurement);
    auto distant_measurement_position = localizerForDistantMeasurement.measurement_received(
            measuredPositionOfDistantMeasurement, accuracyOfDistantMeasurement);

    CHECK(close_measurement_position.get_accuracy() == Approx(distant_measurement_position.get_accuracy()).epsilon(precision));
    CHECK(close_measurement_position.get_accuracy() > magnitudeOfComparisonPrecision);
    CHECK(distant_measurement_position.get_accuracy() > magnitudeOfComparisonPrecision);
}