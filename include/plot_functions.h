#pragma once

#include <vector>

class plot_functions {
public:
    static std::vector<double> create_uniform_scale(double start, double end, unsigned int reference_point_count);

    static std::vector<double> plot_gaussian(double mean, double variance, const std::vector<double>& scale);
};
