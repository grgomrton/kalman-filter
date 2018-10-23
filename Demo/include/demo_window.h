#pragma once

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm-plplot/canvas.h>
#include <gtkmm/button.h>
#include "localizer.h"
#include "estimated_position.h"
#include "plotter.h"
#include "gaussian_noise.h"
#include "sensor.h"
#include "robot.h"

class demo_window : public Gtk::Window {
public:
    demo_window();

private:
    static const double estimation_plot_height_norm;
    static const double error_plot_height_norm;
    static const double error_plot_offset_norm;

    robot robot_;
    sensor sensor_;
    localizer localizer_;
    double unit_step_in_metres_;

    Gtk::Grid layout_;
    Gtk::PLplot::Canvas canvas_;
    std::shared_ptr<Gtk::PLplot::Plot2D> estimation_plot_;
    std::shared_ptr<Gtk::PLplot::Plot2D> error_plot_;
    plotter plotter_;
    Gtk::Button move_left_button_;
    Gtk::Button move_right_button_;
    Gtk::Button measure_position_button_;

    void on_move_left_clicked();

    void on_move_right_clicked();

    void on_measure_position_clicked();

};
