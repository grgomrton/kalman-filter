#pragma once

#include "estimated_position.h"

class localizer {
public:
    explicit localizer(estimated_position initial_position);

    estimated_position movement_executed(double distance, double error_range);

    estimated_position measurement_received(double measured_position, double error_range);

    estimated_position get_position();

private:
    estimated_position current_estimation_;
    
};
