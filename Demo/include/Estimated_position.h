#pragma once

struct Estimated_position {
public:
    double get_position();

    double get_variance();

    double get_error_range();

    static Estimated_position from_error_range(double position, double estimation_error_range);

    static Estimated_position from_variance(double position, double estimation_variance);

    static double error_range_to_variance(double error_range);

    static double variance_to_error_range(double variance);

private:
    Estimated_position(double position_param, double variance_param);

    double position;
    double variance;

};