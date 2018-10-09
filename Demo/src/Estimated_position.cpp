#include <Estimated_position.h>
#include <cmath>

Estimated_position Estimated_position::from_error_range(double position, double estimation_error_range) { // todo test
    return {position, error_range_to_variance(estimation_error_range)};
}

Estimated_position Estimated_position::from_variance(double position, double estimation_variance) { // test
    return {position, estimation_variance};
}

double Estimated_position::error_range_to_variance(double error_range) {
    auto standard_deviation = error_range / 2.0;
    return pow(standard_deviation, 2.0);
}

double Estimated_position::variance_to_error_range(double variance) {
    return sqrt(variance) * 2.0;
}

double Estimated_position::get_position() {
    return position;
}

double Estimated_position::get_variance() {
    return variance;
}

double Estimated_position::get_error_range() {
    return variance_to_error_range(variance);
}

Estimated_position::Estimated_position(double position_param, double variance_param)
        : position(position_param),
          variance(variance_param) {
}
