#include <Plotter.h>
#include <Estimated_position.h>
#include <gtkmm-plplot/plot2d.h>
#include <gtkmm-plplot/plotdata2d.h>
#include <Plot_functions.h>

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

    recolour_curves();
    update_curve_labels();
}

void Plotter::add_measurement(Estimated_position measurement) {
    auto y_values = Plot_functions::plot_gaussian(measurement.get_position(), measurement.get_variance(), x_scale);
    if (last_measurement) {
        plot->remove_data(*last_measurement);
    }
    last_measurement = std::make_unique<Gtk::PLplot::PlotData2D>(x_scale, y_values);
    plot->add_data(*last_measurement);

    recolour_curves();
    update_curve_labels();
}

void Plotter::recolour_curves() {
    auto history_index = 0;
    auto shade_base = 0.0;
    auto increment = 0.15;
    auto color = Gdk::RGBA();
    for (auto it = estimations.begin(); it != estimations.end(); it++) {
        if (it == estimations.begin()) {
            (*it)->set_color(Gdk::RGBA("red"));
            (*it)->set_line_width(1.0);
        } else {
            history_index++;
            color.set_grey(std::min(shade_base + history_index * increment, 1.0));
            (*it)->set_color(color);
            (*it)->set_line_width(0.5);
        }
    }
    if (last_measurement) {
        last_measurement->set_color(Gdk::RGBA("blue"));
        last_measurement->set_line_width(1.0);
    }
}

void Plotter::update_curve_labels() {
    for (int i = 0; i < estimations.size(); i++) {
        if (i == 0) {
            estimations[i]->set_name("bel(t)");
        } else {
            std::string label;
            label += "bel(t-";
            label += std::to_string(i);
            label += ")";
            estimations[i]->set_name(label);
        }
    }
    if (last_measurement) {
        last_measurement->set_name("meas(t)");
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