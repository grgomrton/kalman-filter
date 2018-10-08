#pragma once

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm-plplot/canvas.h>
#include <gtkmm/button.h>
#include "Localizer.h"
#include "Estimated_position.h"
#include "Plotter.h"
#include "Gaussian_noise.h"

class Main_window : public Gtk::Window {
public:
    Main_window();

private:
    static const double sensor_accuracy_in_metres;

    double robot_position_world;
    Localizer localizer;
    Estimated_position robot_position_localizer;
    Gaussian_noise noise_generator;
    double unit_step_metres;
    double movement_accuracy_percentage;

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

};
