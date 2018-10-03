#pragma once

#include <gtkmm/window.h>
#include <gtkmm/grid.h>
#include <gtkmm-plplot/canvas.h>
#include <gtkmm/button.h>
#include <Localizer.h>
#include <gtkmm-plplot/plotdata2d.h>
#include <gtkmm-plplot.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow();
    MainWindow(const MainWindow& other) = delete;
    MainWindow& operator=(const MainWindow& other) = delete;
    ~MainWindow() override;

private:
    double robotPositionInWorld;
    GaussianDistributionDescriptor robotPositionInLocalizer;
    Localizer localizer;
    double unitStepInMetres;
    double movementAccuracyInPercentage;

    std::vector<double> x_scale;
    Gtk::Grid layout;
    Gtk::PLplot::Canvas canvas;
    Gtk::PLplot::PlotData2D* plotData;
    GaussianDistributionDescriptor* lastReceivedMeasurement;
    Gtk::PLplot::PlotData2D* measurementPlotData;
    Gtk::PLplot::Plot2D plot;
    Gtk::Button moveLeftButton;
    Gtk::Button moveRightButton;
    Gtk::Button getGpsSignalButton;
    bool shouldPlotMeasurement;

    void moveLeftClicked();
    void moveRightClicked();
    void getGpsSignalClicked();
    void invalidate();

};
