#pragma once

#include "Estimated_position.h"

class Localizer {
public:
    explicit Localizer(Estimated_position initial_position);

    Estimated_position movement_executed(double distance, double error_range);

    Estimated_position measurement_received(double measured_position, double error_range);

    Estimated_position get_position();

private:
    Estimated_position current_estimation;

    static double calculate_absolute_accuracy(double distance, double accuracy_in_percentage);

};
