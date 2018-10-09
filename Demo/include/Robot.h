#pragma once

#include "Gaussian_noise.h"

class Robot {
public:
    Robot();

    double move(double distance);

    double get_position_in_world();

    double get_error_range_of_move_command(double distance);

private:
    double position_in_world;
    double movement_accuracy_in_percentage;
    Gaussian_noise noise_generator;

};