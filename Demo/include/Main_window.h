#pragma once

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm-plplot/canvas.h>
#include <gtkmm/button.h>
#include "Localizer.h"
#include "Estimated_position.h"
#include "Plotter.h"
#include "Gaussian_noise.h"
#include "Sensor.h"
#include "Robot.h"

class Main_window : public Gtk::Window {
public:
    Main_window();

private:
    Robot robot;
    Sensor sensor;
    Localizer localizer;
    double unit_step_metres;

    Gtk::Grid layout;
    Gtk::PLplot::Canvas canvas;
    std::shared_ptr<Gtk::PLplot::Plot2D> plot;
    Plotter plotter;
    Gtk::Button move_left_button;
    Gtk::Button move_right_button;
    Gtk::Button measure_position_button;

    void on_move_left_clicked();

    void on_move_right_clicked();

    void on_measure_position_clicked();

    void print_error_between_actual_and_estimated_position();

};
