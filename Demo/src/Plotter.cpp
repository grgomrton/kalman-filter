#include <Plotter.h>
#include <Estimated_position.h>
#include <gtkmm-plplot/plot2d.h>
#include <gtkmm-plplot/plotdata2d.h>
#include <Plot_functions.h>

const unsigned long Plotter::history_size = 5;

Plotter::Plotter(std::shared_ptr<Gtk::PLplot::Plot2D> plot_param, std::vector<double> x_scale_param) {
    x_scale = std::move(x_scale_param);           // todo check pointers
    plot = std::move(plot_param);
    estimations.reserve(history_size + 1);
}

void Plotter::add_estimation(Estimated_position estimation) {
    auto y_values = Plot_functions::plot_gaussian(estimation.get_position(), estimation.get_variance(), x_scale);
    if (estimations.size() == history_size + 1) {
        plot->remove_data(*estimations.back());
        estimations.pop_back();
    }
    estimations.insert(estimations.begin(), std::make_unique<Gtk::PLplot::PlotData2D>(x_scale, y_values));
    plot->add_data(*estimations.front());
    if (last_measurement) {
        plot->remove_data(*last_measurement);
    }
    last_measurement.reset();

    update_curve_appearance();
}

void Plotter::add_estimation_after_measurement(Estimated_position estimation, Estimated_position measurement) {
    add_estimation(estimation);

    auto y_values = Plot_functions::plot_gaussian(measurement.get_position(), measurement.get_variance(), x_scale);
    if (last_measurement) {
        plot->remove_data(*last_measurement);
    }
    last_measurement = std::make_unique<Gtk::PLplot::PlotData2D>(x_scale, y_values);
    plot->add_data(*last_measurement);

    update_curve_appearance();
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
            std::string label;
            label += "bel(t-";
            label += std::to_string(history_index);
            label += ")";
            (*it)->set_name(label);
            color.set_grey(std::min(shade_base + history_index * increment, 1.0));
            (*it)->set_color(color);
            (*it)->set_line_width(0.5);
        }
        history_index++;
    }
    if (last_measurement) {
        last_measurement->set_name("meas(t)");
        last_measurement->set_color(Gdk::RGBA("blue"));
        last_measurement->set_line_width(1.0);
    }
}

Plotter::~Plotter() {
    for (auto& position : estimations) {
        plot->remove_data(*position);
    }
    if (last_measurement) {
        plot->remove_data(*last_measurement);
    }
}