#include <Localizer.h>

Localizer::Localizer(Estimated_position initialPosition) : _position(initialPosition) {

}

Estimated_position Localizer::movementUpdate(double distance, double accuracyInPercentage) {
    double error_cov = Estimated_position::accuracy_to_variance(calculateAbsoluteAccuracy(distance, accuracyInPercentage));
    double prev_mean = _position.get_position();
    double prev_cov = _position.get_variance();

    double new_mean = prev_mean + distance;
    double new_cov = prev_cov + error_cov;

    _position = Estimated_position::from_variance(new_mean, new_cov);
    return _position;
}

Estimated_position Localizer::measurementUpdate(double measuredPosition, double absoluteAccuracy) {
    double error_cov = Estimated_position::accuracy_to_variance(absoluteAccuracy);
    double prev_mean = _position.get_position();
    double prev_cov = _position.get_variance();

    double gain = prev_cov / (prev_cov + error_cov);
    double new_mean = prev_mean + gain * (measuredPosition - prev_mean);
    double new_cov = (1 - gain) * prev_cov;

    _position = Estimated_position::from_variance(new_mean, new_cov);
    return _position;
}

Estimated_position Localizer::getPosition() {
    return _position;
}

double Localizer::calculateAbsoluteAccuracy(double distance, double accuracyInPercentage) {
    return distance * (accuracyInPercentage / 100.0);
}
