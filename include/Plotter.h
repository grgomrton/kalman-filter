#pragma once

// includes

#include <vector>
#include <memory>

// predeclarations

class Estimated_position;

namespace Gtk {
    namespace PLplot {
        class Plot2D;

        class PlotData2D;
    }
}

// class declaration

class Plotter {
public:

    Plotter(std::shared_ptr<Gtk::PLplot::Plot2D> plot_param, std::vector<double> x_scale_param);

    void add_estimation(Estimated_position estimation);

    void add_measurement(Estimated_position measurement);

    ~Plotter();

private:
    static const int history_size = 5;
    std::vector<double> x_scale;
    std::shared_ptr<Gtk::PLplot::Plot2D> plot;
    std::unique_ptr<Gtk::PLplot::PlotData2D> last_measurement;
    std::vector<std::unique_ptr<Gtk::PLplot::PlotData2D>> estimations;

    void recolour_curves();

    void update_curve_labels();

};
