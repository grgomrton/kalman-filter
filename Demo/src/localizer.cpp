#include <localizer.h>

localizer::localizer(estimated_position initial_position)
        : current_estimation_(initial_position) {
}

estimated_position localizer::movement_executed(double distance, double error_range) {
    double error_cov = estimated_position::error_range_to_variance(error_range);
    double prev_mean = current_estimation_.get_position();
    double prev_cov = current_estimation_.get_variance();

    double new_mean = prev_mean + distance;
    double new_cov = prev_cov + error_cov;

    current_estimation_ = estimated_position::from_variance(new_mean, new_cov);
    return current_estimation_;
}

estimated_position localizer::measurement_received(double measured_position, double error_range) {
    double error_cov = estimated_position::error_range_to_variance(error_range);
    double prev_mean = current_estimation_.get_position();
    double prev_cov = current_estimation_.get_variance();

    double gain = prev_cov / (prev_cov + error_cov);
    double new_mean = prev_mean + gain * (measured_position - prev_mean);
    double new_cov = (1 - gain) * prev_cov;

    current_estimation_ = estimated_position::from_variance(new_mean, new_cov);
    return current_estimation_;
}

estimated_position localizer::get_position() {
    return current_estimation_;
}
