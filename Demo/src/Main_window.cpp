#include <Main_window.h>
#include <gtkmm/label.h>
#include <gtkmm-plplot/plot2d.h>
#include <Localizer.h>
#include <Plotter.h>
#include <Plot_functions.h>

const double Main_window::estimation_plot_height_norm = 0.6;
const double Main_window::error_plot_offset_norm = Main_window::estimation_plot_height_norm;
const double Main_window::error_plot_height_norm = 0.4;

Main_window::Main_window()
    : localizer(Estimated_position::from_error_range(0.0, 0.3)),                                                                      // todo x_scale here!
      unit_step_metres(1.0),
      estimation_plot(std::make_shared<Gtk::PLplot::Plot2D>("x [m]", "", "Current estimation", 1.0, estimation_plot_height_norm)),         // todo extract to consts
      error_plot(std::make_shared<Gtk::PLplot::Plot2D>("", "error [m]", "Estimation error", 1.0, error_plot_height_norm, 0.0, error_plot_offset_norm)),
      plotter(estimation_plot, Plot_functions::create_uniform_scale(-50, 50, 1000), error_plot, 100),                                  // todo to consts
      move_left_button("Move left"),
      move_right_button("Move right"),
      measure_position_button("Measure position") {

    plotter.add_estimation(localizer.get_position(), robot.get_position_in_world());

    canvas.add_plot(*estimation_plot);
    error_plot->hide_legend();
    canvas.add_plot(*error_plot);
    canvas.set_hexpand(true);
    canvas.set_vexpand(true);
    layout.attach(canvas, 1, 1, 3, 1);

    move_left_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_move_left_clicked));
    layout.attach(move_left_button, 1, 3, 1, 1);
    move_right_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_move_right_clicked));
    layout.attach(move_right_button, 2, 3, 1, 1);
    measure_position_button.signal_clicked().connect(sigc::mem_fun(this, &Main_window::on_measure_position_clicked));
    layout.attach(measure_position_button, 3, 3, 1, 1);

    add(layout);
    override_background_color(Gdk::RGBA("white"));
    set_border_width(10);
    show_all_children();
}

void Main_window::on_move_left_clicked() {
    auto distance = -unit_step_metres;
    robot.move(distance);
    auto estimation = localizer.movement_executed(distance, robot.get_error_range_of_move_command(distance));
    plotter.add_estimation(estimation, robot.get_position_in_world());
}

void Main_window::on_move_right_clicked() {
    auto distance = unit_step_metres;
    robot.move(distance);
    auto estimation = localizer.movement_executed(distance, robot.get_error_range_of_move_command(distance));
    plotter.add_estimation(estimation, robot.get_position_in_world());
}

void Main_window::on_measure_position_clicked() {
    auto measurement = sensor.get_noisy_measurement(robot.get_position_in_world());
    auto estimation = localizer.measurement_received(measurement.get_position(), measurement.get_error_range());
    plotter.add_estimation_after_measurement(estimation, measurement, robot.get_position_in_world());
}
