#include "Localizer.h"

Localizer::Localizer(pos_est initial_position) : _position(initial_position) {

}

pos_est Localizer::movementUpdate(double distance, double accuracy_percentage) {
    double error_cov = pos_est::accuracy_to_covariance(calcAccuracy(distance, accuracy_percentage));
    double prev_mean = _position.position();
    double prev_cov = _position.covariance();

    double new_mean = prev_mean + distance;
    double new_cov = prev_cov + error_cov;

    _position = pos_est::make_from_covariance(new_mean, new_cov);
    return _position;
}

pos_est Localizer::measurementUpdate(double measured_position, double absolute_accuracy) {
    double error_cov = pos_est::accuracy_to_covariance(absolute_accuracy);
    double prev_mean = _position.position();
    double prev_cov = _position.covariance();

    double gain = prev_cov / (prev_cov + error_cov);
    double new_mean = prev_mean + gain * (measured_position - prev_mean);
    double new_cov = (1 - gain) * prev_cov;

    _position = pos_est::make_from_covariance(new_mean, new_cov);
    return _position;
}

pos_est Localizer::getPosition() {
    return _position;
}

double Localizer::calcAccuracy(double distance, double accuracy_percentage) {
    return distance * calcMultiplier(accuracy_percentage);
}

double Localizer::calcMultiplier(double percentage) {
    return percentage / 100.0;
}
