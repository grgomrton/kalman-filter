#pragma once

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm-plplot/canvas.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow();

private:
    Gtk::Grid layout;
    Gtk::PLplot::Canvas canvas;
    static std::vector<double> uniformScale(double start, double end, unsigned int reference_point_count);
};
