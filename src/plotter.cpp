#include <plotter.h>
#include <estimated_position.h>
#include <gtkmm-plplot/plot2d.h>
#include <gtkmm-plplot/plotdata2d.h>
#include <plot_functions.h>

const unsigned int plotter::estimation_history_size_ = 5;

plotter::plotter(std::shared_ptr<Gtk::PLplot::Plot2D> plot, std::vector<double> x_scale,                // todo x_scale with begin and end
                 std::shared_ptr<Gtk::PLplot::Plot2D> error_plot, unsigned int error_history_size_param) {
    estimation_x_scale_ = std::move(x_scale);                                                                      // todo check pointers
    error_plot_ = std::move(error_plot);
    estimation_plot_ = std::move(plot);
    estimations_.reserve(estimation_history_size_ + 1);
    error_history_size_ = error_history_size_param;
}

void plotter::add_estimation(estimated_position estimation, double real_position) {
    auto y_values = plot_functions::plot_gaussian(estimation.get_position(), estimation.get_variance(), estimation_x_scale_);
    if (estimations_.size() == estimation_history_size_ + 1) {
        estimation_plot_->remove_data(*estimations_.back());
        estimations_.pop_back();
    }
    estimations_.insert(estimations_.begin(), std::make_unique<Gtk::PLplot::PlotData2D>(estimation_x_scale_, y_values));
    estimation_plot_->add_data(*estimations_.front());

    if (last_measurement_ != nullptr) {
        estimation_plot_->remove_data(*last_measurement_);
        last_measurement_.reset();
    }

    if (error_plot_data_ != nullptr) {
        error_plot_->remove_data(*error_plot_data_);
        error_plot_data_.reset();
    }
    if (errors_.size() == error_history_size_) {
        errors_.erase(errors_.begin());
    }
    errors_.push_back(error_between_estimation_and_real_position(estimation, real_position));
    if (errors_.size() >= 2) {
        error_plot_data_ = std::make_unique<Gtk::PLplot::PlotData2D>(errors_);
        error_plot_->add_data(*error_plot_data_);
    }

    update_curve_appearance();
}

void plotter::add_estimation_after_measurement(estimated_position estimation, estimated_position measurement,
                                               double real_position) {
    add_estimation(estimation, real_position);

    auto y_values = plot_functions::plot_gaussian(measurement.get_position(), measurement.get_variance(), estimation_x_scale_);
    if (last_measurement_ != nullptr) {
        estimation_plot_->remove_data(*last_measurement_);
        last_measurement_.reset();
    }
    last_measurement_ = std::make_unique<Gtk::PLplot::PlotData2D>(estimation_x_scale_, y_values);
    estimation_plot_->add_data(*last_measurement_);

    update_curve_appearance();
}

double plotter::error_between_estimation_and_real_position(estimated_position estimation, double real_position) {
    return fabs(estimation.get_position() - real_position);
}

void plotter::update_curve_appearance() {
    auto history_index = 0;
    auto shade_base = 0.0;
    auto increment = 0.15;
    auto color = Gdk::RGBA();
    for (auto it = estimations_.begin(); it != estimations_.end(); it++) {
        if (it == estimations_.begin()) {
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
    if (last_measurement_ != nullptr) {
        last_measurement_->set_name("meas(t)");
        last_measurement_->set_color(Gdk::RGBA("blue"));
        last_measurement_->set_line_width(1.0);
    }
    if (error_plot_data_ != nullptr) {
        error_plot_data_->set_name("error [m]");
        error_plot_data_->set_color(Gdk::RGBA("green"));
    }
}

plotter::~plotter() {
    for (auto& position : estimations_) {
        estimation_plot_->remove_data(*position);
    }
    if (last_measurement_ != nullptr) {
        estimation_plot_->remove_data(*last_measurement_);
        last_measurement_.reset();
    }
    if (error_plot_data_ != nullptr) {
        error_plot_->remove_data(*error_plot_data_);
        error_plot_data_.reset();
    }
}

