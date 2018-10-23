#include <estimated_position.h>
#include <sensor.h>

const double sensor::error_range_in_metres_ = 4.9; // TODO inject

sensor::sensor()
    : noise_standard_deviation_(error_range_in_metres_ / 2.0) {
}

estimated_position sensor::get_noisy_measurement(double position) {
    auto measured_position = position + noise_generator_.get_noise(noise_standard_deviation_);
    return estimated_position::from_error_range(measured_position, error_range_in_metres_);
}

double sensor::get_error_range() {
    return error_range_in_metres_;
}
