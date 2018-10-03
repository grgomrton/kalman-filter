#pragma once

#include <vector>

class Plotter {
public:
    static std::vector<double> CreateUniformScale(double start, double end, unsigned int reference_point_count);

    static std::vector<double> PlotGaussian(double mean, double variance, const std::vector<double>& scale);
};
