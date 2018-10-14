#pragma once

// includes

#include <vector>
#include <memory>

// forward declarations

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

    Plotter(std::shared_ptr<Gtk::PLplot::Plot2D> plot_param, std::vector<double> x_scale_param,
            std::shared_ptr<Gtk::PLplot::Plot2D> error_plot_param, unsigned int error_history_size);

    void add_estimation(Estimated_position estimation, double real_position);

    void add_estimation_after_measurement(Estimated_position estimation, Estimated_position measurement,
                                          double real_position);

    ~Plotter();

private:
    static const unsigned int estimation_history_size;

    std::vector<double> estimation_x_scale;
    std::shared_ptr<Gtk::PLplot::Plot2D> estimation_plot;
    std::vector<std::unique_ptr<Gtk::PLplot::PlotData2D>> estimations;

    std::unique_ptr<Gtk::PLplot::PlotData2D> last_measurement;

    unsigned int error_history_size;
    std::vector<double> errors;
    std::shared_ptr<Gtk::PLplot::Plot2D> error_plot;
    std::unique_ptr<Gtk::PLplot::PlotData2D> error_plot_data;

    void update_curve_appearance();

    static double error_between_estimation_and_real_position(Estimated_position estimation, double real_position);

};
