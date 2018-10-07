#pragma once

// includes

#include <vector>
#include <memory>

// forward declarations

class GaussianDistributionDescriptor;

namespace Gtk {
    namespace PLplot {
        class Plot2D;

        class PlotData2D;
    }
}

// class declaration

class Plotter {
public:

    Plotter(std::shared_ptr<Gtk::PLplot::Plot2D> plot, std::vector<double> scale);

    void AddBelief(GaussianDistributionDescriptor pose);

    void AddMeasurement(GaussianDistributionDescriptor measurement);

    ~Plotter();

private:
    std::vector<double> mScale;
    std::shared_ptr<Gtk::PLplot::Plot2D> mpPlot;
    std::unique_ptr<Gtk::PLplot::PlotData2D> mpLastPosition;
    std::unique_ptr<Gtk::PLplot::PlotData2D> mpLastMeasurement;

};
