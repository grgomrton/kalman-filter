#pragma once

// includes

#include <vector>
#include <memory>

// forward declarations

class estimated_position;

namespace Gtk {
    namespace PLplot {
        class Plot2D;

        class PlotData2D;
    }
}

// class declaration

class plotter {
public:

    plotter(std::shared_ptr<Gtk::PLplot::Plot2D> plot, std::vector<double> x_scale,
            std::shared_ptr<Gtk::PLplot::Plot2D> error_plot, unsigned int error_history_size);

    void add_estimation(estimated_position estimation, double real_position);

    void add_estimation_after_measurement(estimated_position estimation, estimated_position measurement,
                                          double real_position);

    ~plotter();

private:
    static const unsigned int estimation_history_size_;

    std::vector<double> estimation_x_scale_;
    std::shared_ptr<Gtk::PLplot::Plot2D> estimation_plot_;
    std::vector<std::unique_ptr<Gtk::PLplot::PlotData2D>> estimations_;

    std::unique_ptr<Gtk::PLplot::PlotData2D> last_measurement_;

    unsigned int error_history_size_;
    std::vector<double> errors_;
    std::shared_ptr<Gtk::PLplot::Plot2D> error_plot_;
    std::unique_ptr<Gtk::PLplot::PlotData2D> error_plot_data_;

    void update_curve_appearance();

    static double error_between_estimation_and_real_position(estimated_position estimation, double real_position);

};
