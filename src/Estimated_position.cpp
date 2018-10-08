#include "Estimated_position.h"

#include <cmath>

Estimated_position Estimated_position::from_accuracy(double position, double accuracy) { // todo test
    return {position, accuracy_to_variance(accuracy)};
}

Estimated_position Estimated_position::from_variance(double position, double variance) { // test
    return {position, variance};
}

double Estimated_position::accuracy_to_variance(double accuracy) {
    auto standardDeviation = accuracy / 2.0;
    return pow(standardDeviation, 2.0);
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
