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

    Plotter(const Plotter& other) = delete; // TODO these are now automatically deleted, aren't they?

    Plotter& operator=(const Plotter& other) = delete;

private:
    std::vector<double> scale_;
    std::shared_ptr<Gtk::PLplot::Plot2D> plot_;
    std::unique_ptr<Gtk::PLplot::PlotData2D> lastPosition_;
    std::unique_ptr<Gtk::PLplot::PlotData2D> lastMeasurement_;

};
