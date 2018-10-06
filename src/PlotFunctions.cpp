#include "PlotFunctions.h"
#include <cmath>

std::vector<double>
PlotFunctions::CreateUniformScale(double start, double end, unsigned int reference_point_count) { // todo exceptions
    std::vector<double> scale(reference_point_count);
    double step = (end - start) / (double) (reference_point_count - 1);
    for (int i = 0; i < reference_point_count; i++) {
        scale[i] = start + i * step;
    }
    return scale;
}

std::vector<double> PlotFunctions::PlotGaussian(double mean, double variance, const std::vector<double>& scale) {
    auto fx = [](double x, double mean, double variance) {
        return 1 / (sqrt(variance) * sqrt(2 * M_PI)) * pow(M_E, -0.5 * pow((x - mean) / sqrt(variance), 2)); // ugh
    };
    std::vector<double> y_values(scale.size());
    for (int i = 0; i < y_values.size(); i++) {
        y_values[i] = fx(scale[i], mean, variance);
    }
    return y_values;
}