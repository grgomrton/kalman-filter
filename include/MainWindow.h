#pragma once

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm-plplot/canvas.h>
#include <gtkmm/button.h>
#include "Localizer.h"
#include "Plotter.h"

class MainWindow : public Gtk::Window {
public:
    MainWindow();

private:
    double robotPositionInWorld;
    Localizer localizer;
    Estimated_position robotPositionInLocalizer;
    double unitStepInMetres;
    double movementAccuracyInPercentage;

    Gtk::Grid layout;
    Gtk::PLplot::Canvas canvas;
    std::shared_ptr<Gtk::PLplot::Plot2D> plot;
    Plotter plotter;
    Gtk::Button moveLeftButton;
    Gtk::Button moveRightButton;
    Gtk::Button getGpsSignalButton;

    void moveLeftClicked();

    void moveRightClicked();

    void getGpsSignalClicked();

};
