#pragma once

#include "gaussian_noise.h"

class robot {
public:
    robot();

    double move(double distance);

    double get_position_in_world();

    double get_error_range_of_move_command(double distance);

private:
    double position_in_world_;
    double movement_accuracy_in_percentage_;
    gaussian_noise noise_generator_;

};