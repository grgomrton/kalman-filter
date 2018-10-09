#include <Main_window.h>
#include <gtkmm/label.h>
#include <gtkmm-plplot/plot2d.h>
#include <Localizer.h>
#include <Plotter.h>
#include <Plot_functions.h>

Main_window::Main_window() :                                                // todo x_scale here!
        localizer(Estimated_position::from_accuracy(0.0, 2.0)),
        unit_step_metres(1.0),
        plot(std::make_shared<Gtk::PLplot::Plot2D>("x", "")),               // todo extract to consts
        plotter(plot, Plot_functions::create_uniform_scale(-50, 50, 1000)),        // todo to consts
        move_left_button("Move left"),
        move_right_button("Move right"),
        measure_position_button("Measure position") {
    plotter.add_estimation(localizer.get_position());

    auto label = Gtk::manage(new Gtk::Label("Current estimation: "));
    label->set_margin_bottom(10);
    layout.attach(*label, 1, 1, 3, 1);

    canvas.add_plot(*plot);
    canvas.set_hexpand(true);
    canvas.set_vexpand(true);
    layout.attach(canvas, 1, 2, 3, 1);

    move_left_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_move_left_clicked));
    layout.attach(move_left_button, 1, 3, 1, 1);
    move_right_button.signal_clicked().connect(sigc::mem_fun(*this, &Main_window::on_move_right_clicked));
    layout.attach(move_right_button, 2, 3, 1, 1);
    measure_position_button.signal_clicked().connect(sigc::mem_fun(this, &Main_window::on_measure_position_clicked));
    layout.attach(measure_position_button, 3, 3, 1, 1);

    add(layout);
    set_border_width(10);
    show_all_children();
}

void Main_window::on_move_left_clicked() {
    auto step = -unit_step_metres;
    robot.move(step);
    auto estimation = localizer.movement_executed(step, robot.get_accuracy_of_move_command(step));
    plotter.add_estimation(estimation);
    debug_error_between_actual_and_estimated_position();
}

void Main_window::on_move_right_clicked() {
    auto step = unit_step_metres;
    robot.move(step);
    auto estimation = localizer.movement_executed(step, robot.get_accuracy_of_move_command(step));
    plotter.add_estimation(estimation);
    debug_error_between_actual_and_estimated_position();
}

void Main_window::on_measure_position_clicked() {
    auto measurement = sensor.get_noisy_measurement(robot.get_position_in_world());
    auto estimation = localizer.measurement_received(measurement, sensor.get_accuracy());
    plotter.add_estimation(estimation); // todo add estimation after measurement
    plotter.add_measurement(Estimated_position::from_accuracy(measurement, sensor.get_accuracy()));
    debug_error_between_actual_and_estimated_position();
}

void Main_window::debug_error_between_actual_and_estimated_position() {
    std::cout << "error between estimation and real position: "
              << std::to_string(localizer.get_position().get_position() - robot.get_position_in_world())
              << std::endl;
}
