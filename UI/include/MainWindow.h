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
    GaussianDistributionDescriptor currentPosition;
    Localizer localizer;

    std::vector<double> x_scale;
    Gtk::Grid layout;
    Gtk::PLplot::Canvas canvas;
    Gtk::PLplot::PlotData2D* plotData;
    Gtk::PLplot::Plot2D plot;
    Gtk::Button moveLeftButton;

    void moveLeftClicked();
    void invalidate();

    static std::vector<double> uniformScale(double start, double end, unsigned int reference_point_count); // plotter?
    static std::vector<double> plotGaussian(double mean, double variance, const std::vector<double>& scale);
};
