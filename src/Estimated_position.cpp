#include <Estimated_position.h>
#include <cmath>

Estimated_position Estimated_position::from_accuracy(double position, double estimation_accuracy) { // todo test
    return {position, accuracy_to_variance(estimation_accuracy)};
}

Estimated_position Estimated_position::from_variance(double position, double estimation_variance) { // test
    return {position, estimation_variance};
}

double Estimated_position::accuracy_to_variance(double accuracy) {
    auto standard_deviation = accuracy / 2.0;
    return pow(standard_deviation, 2.0);
}

double Estimated_position::variance_to_accuracy(double variance) {
    return sqrt(variance) * 2.0;
}

double Estimated_position::get_position() {
    return position;
}

double Estimated_position::get_variance() {
    return variance;
}

double Estimated_position::get_accuracy() {
    return variance_to_accuracy(variance);
}

Estimated_position::Estimated_position(double position_param, double variance_param)
        : position(position_param),
          variance(variance_param) {
}
