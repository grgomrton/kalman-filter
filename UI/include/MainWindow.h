#pragma once

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm-plplot/plot2d.h>
#include <gtkmm-plplot/canvas.h>


class MainWindow : public Gtk::Window {
public:
    MainWindow(const std::string& greeting_text,
            const std::string& second_greeting_text,
            const std::valarray<double>& x_values,
            const std::valarray<double>& y_values,
            const std::string& x_axis_label,
            const std::string& y_axis_label);

private:
    Gtk::Grid layout;
    Gtk::Label greeting;
    Gtk::PLplot::PlotData2D data;
    Gtk::PLplot::Plot2D plot;
    Gtk::PLplot::Canvas canvas;
};
