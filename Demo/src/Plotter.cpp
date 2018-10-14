#include <Plotter.h>
#include <Estimated_position.h>
#include <gtkmm-plplot/plot2d.h>
#include <gtkmm-plplot/plotdata2d.h>
#include <Plot_functions.h>

const unsigned int Plotter::estimation_history_size = 5;

Plotter::Plotter(std::shared_ptr<Gtk::PLplot::Plot2D> plot_param, std::vector<double> x_scale_param,                // todo x_scale with begin and end
                 std::shared_ptr<Gtk::PLplot::Plot2D> error_plot_param, unsigned int error_history_size_param) {
estimation_x_scale = std::move(x_scale_param);                                                                      // todo check pointers
    error_plot = std::move(error_plot_param);
    estimation_plot = std::move(plot_param);
    estimations.reserve(estimation_history_size + 1);
    error_history_size = error_history_size_param;
}

void Plotter::add_estimation(Estimated_position estimation, double real_position) {
    auto y_values = Plot_functions::plot_gaussian(estimation.get_position(), estimation.get_variance(), estimation_x_scale);
    if (estimations.size() == estimation_history_size + 1) {
        estimation_plot->remove_data(*estimations.back());
        estimations.pop_back();
    }
    estimations.insert(estimations.begin(), std::make_unique<Gtk::PLplot::PlotData2D>(estimation_x_scale, y_values));
    estimation_plot->add_data(*estimations.front());

    if (last_measurement != nullptr) {
        estimation_plot->remove_data(*last_measurement);
        last_measurement.reset();
    }

    if (error_plot_data != nullptr) {
        error_plot->remove_data(*error_plot_data);
        error_plot_data.reset();
    }
    if (errors.size() == error_history_size) {
        errors.erase(errors.begin());
    }
    errors.push_back(error_between_estimation_and_real_position(estimation, real_position));
    if (errors.size() >= 2) {
        error_plot_data = std::make_unique<Gtk::PLplot::PlotData2D>(errors);
        error_plot->add_data(*error_plot_data);
    }

    update_curve_appearance();
}

void Plotter::add_estimation_after_measurement(Estimated_position estimation, Estimated_position measurement,
                                               double real_position) {
    add_estimation(estimation, real_position);

    auto y_values = Plot_functions::plot_gaussian(measurement.get_position(), measurement.get_variance(), estimation_x_scale);
    if (last_measurement != nullptr) {
        estimation_plot->remove_data(*last_measurement);
        last_measurement.reset();
    }
    last_measurement = std::make_unique<Gtk::PLplot::PlotData2D>(estimation_x_scale, y_values);
    estimation_plot->add_data(*last_measurement);

    update_curve_appearance();
}

double Plotter::error_between_estimation_and_real_position(Estimated_position estimation, double real_position) {
    return fabs(estimation.get_position() - real_position);
}

void Plotter::update_curve_appearance() {
    auto history_index = 0;
    auto shade_base = 0.0;
    auto increment = 0.15;
    auto color = Gdk::RGBA();
    for (auto it = estimations.begin(); it != estimations.end(); it++) {
        if (it == estimations.begin()) {
            (*it)->set_name("bel(t)");
            (*it)->set_color(Gdk::RGBA("red"));
            (*it)->set_line_width(1.0);
        } else {
            std::string label = "bel(t-" + std::to_string(history_index) + ")";
            (*it)->set_name(label);
            color.set_grey(std::min(shade_base + history_index * increment, 1.0));
            (*it)->set_color(color);
            (*it)->set_line_width(0.5);
        }
        history_index++;
    }
    if (last_measurement != nullptr) {
        last_measurement->set_name("meas(t)");
        last_measurement->set_color(Gdk::RGBA("blue"));
        last_measurement->set_line_width(1.0);
    }
    if (error_plot_data != nullptr) {
        error_plot_data->set_name("error [m]");
        error_plot_data->set_color(Gdk::RGBA("green"));
    }
}

Plotter::~Plotter() {
    for (auto& position : estimations) {
        estimation_plot->remove_data(*position);
    }
    if (last_measurement != nullptr) {
        estimation_plot->remove_data(*last_measurement);
        last_measurement.reset();
    }
    if (error_plot_data != nullptr) {
        error_plot->remove_data(*error_plot_data);
        error_plot_data.reset();
    }
}

