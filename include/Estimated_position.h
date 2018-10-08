#pragma once

struct Estimated_position {
public:
    double get_position();

    double get_variance();

    double get_accuracy();

    static Estimated_position from_accuracy(double position, double estimation_accuracy);

    static Estimated_position from_variance(double position, double estimation_variance);

    static double accuracy_to_variance(double accuracy);

    static double variance_to_accuracy(double variance);

private:
    Estimated_position(double position_param, double variance_param);

    double position;
    double variance;

};