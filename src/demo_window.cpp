#include <demo_window.h>
#include <gtkmm/label.h>
#include <gtkmm-plplot/plot2d.h>
#include <localizer.h>
#include <plotter.h>
#include <plot_functions.h>

const double demo_window::estimation_plot_height_norm = 0.6;
const double demo_window::error_plot_offset_norm = demo_window::estimation_plot_height_norm;
const double demo_window::error_plot_height_norm = 0.4;

demo_window::demo_window()
    : localizer_(estimated_position::from_error_range(0.0, 0.3)),                                                                      // todo x_scale here!
      unit_step_in_metres_(1.0),
      estimation_plot_(std::make_shared<Gtk::PLplot::Plot2D>("x [m]", "", "Current estimation", 1.0, estimation_plot_height_norm)),         // todo extract to consts
      error_plot_(std::make_shared<Gtk::PLplot::Plot2D>("", "error [m]", "Estimation error", 1.0, error_plot_height_norm, 0.0, error_plot_offset_norm)),
      plotter_(estimation_plot_, plot_functions::create_uniform_scale(-50, 50, 1000), error_plot_, 100),                                  // todo to consts
      move_left_button_("Move left"),
      move_right_button_("Move right"),
      measure_position_button_("Measure position") {

    plotter_.add_estimation(localizer_.get_position(), robot_.get_position_in_world());

    canvas_.add_plot(*estimation_plot_);
    error_plot_->hide_legend();
    canvas_.add_plot(*error_plot_);
    canvas_.set_hexpand(true);
    canvas_.set_vexpand(true);
    layout_.attach(canvas_, 1, 1, 3, 1);

    move_left_button_.signal_clicked().connect(sigc::mem_fun(*this, &demo_window::on_move_left_clicked));
    layout_.attach(move_left_button_, 1, 3, 1, 1);
    move_right_button_.signal_clicked().connect(sigc::mem_fun(*this, &demo_window::on_move_right_clicked));
    layout_.attach(move_right_button_, 2, 3, 1, 1);
    measure_position_button_.signal_clicked().connect(sigc::mem_fun(this, &demo_window::on_measure_position_clicked));
    layout_.attach(measure_position_button_, 3, 3, 1, 1);

    add(layout_);
    override_background_color(Gdk::RGBA("white"));
    set_border_width(10);
    show_all_children();
}

void demo_window::on_move_left_clicked() {
    auto distance = -unit_step_in_metres_;
    robot_.move(distance);
    auto estimation = localizer_.movement_executed(distance, robot_.get_error_range_of_move_command(distance));
    plotter_.add_estimation(estimation, robot_.get_position_in_world());
}

void demo_window::on_move_right_clicked() {
    auto distance = unit_step_in_metres_;
    robot_.move(distance);
    auto estimation = localizer_.movement_executed(distance, robot_.get_error_range_of_move_command(distance));
    plotter_.add_estimation(estimation, robot_.get_position_in_world());
}

void demo_window::on_measure_position_clicked() {
    auto measurement = sensor_.get_noisy_measurement(robot_.get_position_in_world());
    auto estimation = localizer_.measurement_received(measurement.get_position(), measurement.get_error_range());
    plotter_.add_estimation_after_measurement(estimation, measurement, robot_.get_position_in_world());
}
