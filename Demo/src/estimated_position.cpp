#include <estimated_position.h>
#include <cmath>

estimated_position estimated_position::from_error_range(double position, double estimation_error_range) { // todo test
    return {position, error_range_to_variance(estimation_error_range)};
}

estimated_position estimated_position::from_variance(double position, double estimation_variance) { // test
    return {position, estimation_variance};
}

double estimated_position::error_range_to_variance(double error_range) {
    auto standard_deviation = error_range / 2.0;
    return pow(standard_deviation, 2.0);
}

double estimated_position::variance_to_error_range(double variance) {
    return sqrt(variance) * 2.0;
}

double estimated_position::get_position() {
    return position_;
}

double estimated_position::get_variance() {
    return variance_;
}

double estimated_position::get_error_range() {
    return variance_to_error_range(variance_);
}

estimated_position::estimated_position(double position_param, double variance_param)
        : position_(position_param),
          variance_(variance_param) {
}
