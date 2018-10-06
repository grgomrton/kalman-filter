#pragma once

#include <vector>
#include <memory>

class GaussianDistributionDescriptor;

namespace Gtk {
    namespace PLplot {
        class Plot2D;

        class PlotData2D;
    }
}

class Plotter {
public:

    explicit Plotter(std::shared_ptr<Gtk::PLplot::Plot2D> plot, double scaleBegin, double scaleEnd,
                     int referencePointCount);

    Plotter(const Plotter& other) = delete;

    Plotter& operator=(const Plotter& other) = delete;

    void AddBelief(GaussianDistributionDescriptor pose);

    void AddMeasurement(GaussianDistributionDescriptor measurement);

    ~Plotter();

private:
    std::shared_ptr<Gtk::PLplot::Plot2D> plot_;
    Gtk::PLplot::PlotData2D* plotData_;
    Gtk::PLplot::PlotData2D* measurementPlotData;
    std::vector<double> scale_;

};
