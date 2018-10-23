#include "localizer.h"
#include "catch2/catch.hpp"

TEST_CASE("After initialization the estimated position should be identical with the passed one") {
    double initial_position = 5.0;
    double initial_error_range = 0.05;
    estimated_position initial_estimation = estimated_position::from_error_range(initial_position, initial_error_range);

    localizer localizer(initial_estimation);
    auto estimatedPosition = localizer.get_position();

    CHECK(estimatedPosition.get_position() == Approx(initial_position));
    CHECK(estimatedPosition.get_error_range() == Approx(initial_error_range));
}

TEST_CASE("After a movement the mean should move to the endpoint of the command") {
    double initial_position = 5.0;
    double initial_accuracy = 0.05;
    estimated_position initial_estimation = estimated_position::from_error_range(initial_position, initial_accuracy);
    double distance = 1.0;
    double accuracy_of_move_command_in_percentage = 8.0;
    double expected_position_after_move = 6.0;
    localizer localizer(initial_estimation);

    auto estimated_position = localizer.movement_executed(distance, accuracy_of_move_command_in_percentage);

    CHECK(estimated_position.get_position() == Approx(expected_position_after_move));
}

TEST_CASE("After a movement the accuracy should be in a higher range") {
    double initial_position = 5.0;
    double initial_error_range = 0.05;
    estimated_position initial_estimation = estimated_position::from_error_range(initial_position, initial_error_range);
    double distance = 1.0;
    double accuracy_of_move_command_in_metres = 0.08;
    localizer localizer(initial_estimation);

    auto new_position = localizer.movement_executed(distance, accuracy_of_move_command_in_metres);

    CHECK(new_position.get_error_range() > initial_error_range);
}

TEST_CASE("After a measurement the mean should move in between the original and the measured one") {
    double initial_position = 3.0;
    double initial_error_range = 0.5;
    estimated_position initial_estimation = estimated_position::from_error_range(initial_position, initial_error_range);
    double measured_position = 3.3;
    double error_range_of_measurement = 0.5;
    localizer localizer(initial_estimation);

    auto new_position = localizer.measurement_received(measured_position, error_range_of_measurement);

    CHECK(new_position.get_position() > initial_position);
    CHECK(new_position.get_position() < measured_position);
}

TEST_CASE("After a measurement the accuracy should be in a smaller range") {
    double initial_position = 3.0;
    double initial_error_range = 0.5;
    estimated_position initial_estimation = estimated_position::from_error_range(initial_position, initial_error_range);
    double measured_position = 3.3;
    double error_range_of_measurement = 0.5;
    localizer localizer(initial_estimation);

    auto new_position = localizer.measurement_received(measured_position, error_range_of_measurement);

    CHECK(new_position.get_error_range() < initial_error_range);
}

TEST_CASE("After a close measurement the accuracy should be in smaller range than both the initial and the measured one") {
    // Follows Figure 3.2 (a, b, c) from
    // Thrun, S., Burgard, W.,, Fox, D. (2006). Probabilistic Robotics (Intelligent Robotics and Autonomous Agents).
    double initial_position = 8.0;
    double initial_error_range = 8.0;
    estimated_position initial_estimation = estimated_position::from_error_range(initial_position, initial_error_range);
    double measured_position = 6.0;
    double error_range_of_measurement = 4.0;
    double expected_mean = 6.5;
    double expected_error_range = 3.6;
    double precision_for_position = 0.1;
    double precision_for_error_range = 0.05;
    localizer localizer(initial_estimation);

    auto new_position = localizer.measurement_received(measured_position, error_range_of_measurement);

    CHECK(new_position.get_position() == Approx(expected_mean).epsilon(precision_for_position));
    CHECK(new_position.get_error_range() == Approx(expected_error_range).epsilon(precision_for_error_range));
}

TEST_CASE("After a measurement the move command should introduce uncertainty") {
    // Follows Figure 3.2 (c, d) from
    // Thrun, S., Burgard, W.,, Fox, D. (2006). Probabilistic Robotics (Intelligent Robotics and Autonomous Agents).
    double initial_position = 8.0;
    double initial_error_range = 8.0;
    estimated_position initial_estimation = estimated_position::from_error_range(initial_position, initial_error_range);
    double measured_position = 6.0;
    double error_range_of_measurement = 4.0;
    double move_distance = 15.0;
    double absolute_error_range_of_move_command = 6;
    double expected_mean = 21.5;
    double expected_error_range = 7.0;
    double precision_for_position = 0.1;
    double precision_for_error_range = 0.05;
    localizer localizer(initial_estimation);

    localizer.measurement_received(measured_position, error_range_of_measurement);
    auto last_position = localizer.movement_executed(move_distance, absolute_error_range_of_move_command);

    CHECK(last_position.get_position() == Approx(expected_mean).epsilon(precision_for_position));
    CHECK(last_position.get_error_range() == Approx(expected_error_range).epsilon(precision_for_error_range));
}

TEST_CASE("The certainty after measurement update is independent of the distance") {
    double initial_position = 3.0;
    double initial_error_range = 0.5;
    estimated_position initial_estimation = estimated_position::from_error_range(initial_position, initial_error_range);
    double measured_position_close_measurement = 3.3;
    double error_range_of_close_measurement = 0.5;
    double measured_position_distant_measurement = 5.3;
    double error_range_of_distant_measurement = 0.5;
    double precision = 0.001;
    double magnitude_of_comparison_precision = 0.01;
    localizer localizer_for_close_measurement(initial_estimation);
    localizer localizer_for_distant_measurement(initial_estimation);

    auto close_measurement_position = localizer_for_close_measurement.measurement_received(
            measured_position_close_measurement, error_range_of_close_measurement);
    auto distant_measurement_position = localizer_for_distant_measurement.measurement_received(
            measured_position_distant_measurement, error_range_of_distant_measurement);

    CHECK(close_measurement_position.get_error_range() == Approx(distant_measurement_position.get_error_range()).epsilon(precision));
    CHECK(close_measurement_position.get_error_range() > magnitude_of_comparison_precision);
    CHECK(distant_measurement_position.get_error_range() > magnitude_of_comparison_precision);
}
