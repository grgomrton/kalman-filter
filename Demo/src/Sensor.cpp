#include <Estimated_position.h>
#include <Sensor.h>

const double Sensor::error_range_in_metres = 4.9; // TODO inject

Sensor::Sensor()
    : noise_standard_deviation(error_range_in_metres / 2.0) {
}

Estimated_position Sensor::get_noisy_measurement(double position) {
    auto measured_position = position + noise_generator.get_noise(noise_standard_deviation);
    return Estimated_position::from_error_range(measured_position, error_range_in_metres);
}

double Sensor::get_error_range() {
    return error_range_in_metres;
}
