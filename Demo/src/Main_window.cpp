#include <Main_window.h>
#include <gtkmm/label.h>
#include <gtkmm-plplot/plot2d.h>
#include <Localizer.h>
#include <Plotter.h>
#include <Plot_functions.h>

const double Main_window::sensor_accuracy_in_metres = 5.88;                 // todo obviously, this const should not be here

Main_window::Main_window() :                                                // todo x_scale here!
        robot_position_world(0.0),
        localizer(Estimated_position::from_accuracy(0.0, 2.0)),
        robot_position_localizer(localizer.get_position()),
        unit_step_metres(1.0),
        movement_accuracy_percentage(30.0),
        layout(),
        canvas(),
        plot(std::make_shared<Gtk::PLplot::Plot2D>("x", "")),               // todo extract to consts
        plotter(plot, Plot_functions::create_uniform_scale(-50, 50, 1000)),        // todo to consts
        move_left_button("Move left"),
        move_right_button("Move right"),
        measure_position_button("Measure position") {
    plotter.add_estimation(robot_position_localizer);

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
    robot_position_world -= unit_step_metres; // perfect movement
    robot_position_localizer = localizer.movement_executed(-unit_step_metres, movement_accuracy_percentage);
    plotter.add_estimation(robot_position_localizer);
    std::cout << "current position mean: " << robot_position_localizer.get_position() << " error range: "
              << robot_position_localizer.get_accuracy() << std::endl;
}

void Main_window::on_move_right_clicked() {
    robot_position_world += unit_step_metres; // perfect movement
    robot_position_localizer = localizer.movement_executed(unit_step_metres, movement_accuracy_percentage);
    plotter.add_estimation(robot_position_localizer);
    std::cout << "current position mean: " << robot_position_localizer.get_position() << " error range: "
              << robot_position_localizer.get_accuracy() << std::endl;
}

void Main_window::on_measure_position_clicked() {

    auto measured_position = robot_position_world + noise_generator.get_noise(sensor_accuracy_in_metres / 2.0);
    auto measurement = Estimated_position::from_accuracy(measured_position, sensor_accuracy_in_metres);
    robot_position_localizer = localizer.measurement_received(measured_position, sensor_accuracy_in_metres);
    plotter.add_estimation(robot_position_localizer);
    plotter.add_measurement(measurement);
    std::cout << "current position mean: " << robot_position_localizer.get_position() << " error range: "
              << robot_position_localizer.get_accuracy() << std::endl;
}



