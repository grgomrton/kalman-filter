#include <robot.h>

robot::robot()
        : position_in_world_(0.0),
          movement_accuracy_in_percentage_(30.0) { // TODO inject
}

double robot::move(double distance) {
    position_in_world_ += distance + noise_generator_.get_noise(get_error_range_of_move_command(distance) / 2.0);
    return position_in_world_;
}

double robot::get_position_in_world() {
    return position_in_world_;
}

double robot::get_error_range_of_move_command(double distance) {
    return fabs(distance) * (movement_accuracy_in_percentage_ / 100.0);
}
