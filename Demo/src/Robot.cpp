#include <Robot.h>

Robot::Robot()
        : position_in_world(0.0),
          movement_accuracy_in_percentage(30.0) {
}

double Robot::move(double distance) {
    position_in_world += distance + noise_generator.get_noise(calculate_absolute_accuracy(distance, movement_accuracy_in_percentage) / 2.0);
    return position_in_world;
}

double Robot::calculate_absolute_accuracy(double distance, double accuracy_in_percentage) {
    return fabs(distance) * (accuracy_in_percentage / 100.0);
}

double Robot::get_position_in_world() {
    return position_in_world;
}

double Robot::get_accuracy_of_move_command(double distance) {
    return calculate_absolute_accuracy(distance, movement_accuracy_in_percentage);
}
