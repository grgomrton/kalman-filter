#include <Robot.h>

Robot::Robot()
        : position_in_world(0.0),
          movement_accuracy_in_percentage(30.0) { // TODO inject
}

double Robot::move(double distance) {
    auto increment = distance + noise_generator.get_noise(get_error_range_of_move_command(distance) / 2.0);
    position_in_world += increment;
    return position_in_world;
}

double Robot::get_position_in_world() {
    return position_in_world;
}

double Robot::get_error_range_of_move_command(double distance) {
    return fabs(distance) * (movement_accuracy_in_percentage / 100.0);
}
