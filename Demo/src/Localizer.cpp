#include <Localizer.h>

Localizer::Localizer(Estimated_position initial_position)
        : current_estimation(initial_position) {
}

Estimated_position Localizer::movement_executed(double distance, double error_range) {
    double error_cov = Estimated_position::error_range_to_variance(error_range);
    double prev_mean = current_estimation.get_position();
    double prev_cov = current_estimation.get_variance();

    double new_mean = prev_mean + distance;
    double new_cov = prev_cov + error_cov;

    current_estimation = Estimated_position::from_variance(new_mean, new_cov);
    return current_estimation;
}

Estimated_position Localizer::measurement_received(double measured_position, double error_range) {
    double error_cov = Estimated_position::error_range_to_variance(error_range);
    double prev_mean = current_estimation.get_position();
    double prev_cov = current_estimation.get_variance();

    double gain = prev_cov / (prev_cov + error_cov);
    double new_mean = prev_mean + gain * (measured_position - prev_mean);
    double new_cov = (1 - gain) * prev_cov;

    current_estimation = Estimated_position::from_variance(new_mean, new_cov);
    return current_estimation;
}

Estimated_position Localizer::get_position() {
    return current_estimation;
}
