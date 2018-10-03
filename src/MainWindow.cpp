#include "MainWindow.h"
#include <gtkmm/label.h>
#include <gtkmm-plplot/plot2d.h>
#include <Localizer.h>
#include <Plotter.h>
#include <MainWindow.h>


MainWindow::MainWindow() : // todo x_scale here!
    // currently robot executes and gps measures without error
    robotPositionInWorld(0.0),
    robotPositionInLocalizer(GaussianDistributionDescriptor::makeFromAccuracy(0.0, 0.1)), // 0.0 +/-10 cm
    localizer(robotPositionInLocalizer),
    unitStepInMetres(1.0),
    movementAccuracyInPercentage(30.0),
    plotData(nullptr),
    lastReceivedMeasurement(nullptr),
    measurementPlotData(nullptr),
    plot("x", ""), // todo extract to consts
    moveLeftButton("Move left"),
    moveRightButton("Move right"),
    getGpsSignalButton("Measure position"),
    shouldPlotMeasurement(false) {

    auto label = Gtk::manage(new Gtk::Label("Current estimation: "));
    label->set_margin_bottom(10);
    layout.attach(*label, 1, 1, 3, 1);

    unsigned int reference_point_count = 1000;
    double start = -100;
    double end = 100;
    x_scale = Plotter::CreateUniformScale(start, end, reference_point_count);
    canvas.add_plot(plot);

    canvas.set_hexpand(true);
    canvas.set_vexpand(true);
    layout.attach(canvas, 1, 2, 3, 1);

    moveLeftButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::moveLeftClicked));
    layout.attach(moveLeftButton, 1, 3, 1, 1);
    moveRightButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::moveRightClicked));
    layout.attach(moveRightButton, 2, 3, 1, 1);
    getGpsSignalButton.signal_clicked().connect(sigc::mem_fun(this, &MainWindow::getGpsSignalClicked));
    layout.attach(getGpsSignalButton, 3, 3, 1, 1);

    add(layout);
    set_border_width(10);
    invalidate();
    show_all_children();
}

void MainWindow::moveLeftClicked() {
    robotPositionInWorld -= unitStepInMetres;
    robotPositionInLocalizer = localizer.movementUpdate(-unitStepInMetres, movementAccuracyInPercentage);
    shouldPlotMeasurement = false;
    invalidate();
    std::cout << "current position mean: " << robotPositionInLocalizer.getPosition() << " accuracy: " << robotPositionInLocalizer.getAccuracy() << std::endl;
}

void MainWindow::moveRightClicked() {
    robotPositionInWorld += unitStepInMetres;
    robotPositionInLocalizer = localizer.movementUpdate(unitStepInMetres, movementAccuracyInPercentage);
    shouldPlotMeasurement = false;
    invalidate();
    std::cout << "current position mean: " << robotPositionInLocalizer.getPosition() << " accuracy: " << robotPositionInLocalizer.getAccuracy() << std::endl;
}

void MainWindow::getGpsSignalClicked() {
    auto gpsAccuracyInMetres = 5.88;
    auto measuredPosition = robotPositionInWorld;
    delete lastReceivedMeasurement;
    lastReceivedMeasurement = nullptr;
    lastReceivedMeasurement = new GaussianDistributionDescriptor(GaussianDistributionDescriptor::makeFromAccuracy(measuredPosition, gpsAccuracyInMetres));
    shouldPlotMeasurement = true;
    robotPositionInLocalizer = localizer.measurementUpdate(measuredPosition, gpsAccuracyInMetres);
    invalidate();
    std::cout << "current position mean: " << robotPositionInLocalizer.getPosition() << " accuracy: " << robotPositionInLocalizer.getAccuracy() << std::endl;
}


void MainWindow::invalidate() {
    if (plotData != nullptr) {
        plot.remove_data(*plotData);
    }
    delete plotData;
    plotData = nullptr;
    if (measurementPlotData != nullptr) {
        plot.remove_data(*measurementPlotData);
    }
    delete measurementPlotData;
    measurementPlotData = nullptr;

    std::vector<double> y_values = Plotter::PlotGaussian(robotPositionInLocalizer.getPosition(), robotPositionInLocalizer.getVariance(), x_scale);
    plotData = new Gtk::PLplot::PlotData2D(x_scale, y_values, Gdk::RGBA("red"));
    plot.add_data(*plotData);

    if (shouldPlotMeasurement) {
        if (lastReceivedMeasurement != nullptr) {
            std::vector<double> meas_y_values = Plotter::PlotGaussian(lastReceivedMeasurement->getPosition(), lastReceivedMeasurement->getVariance(), x_scale);
            measurementPlotData = new Gtk::PLplot::PlotData2D(x_scale, meas_y_values, Gdk::RGBA("blue"));
            plot.add_data(*measurementPlotData);
        } else {
            throw std::logic_error("No data available to plot");
        }
    }
}

MainWindow::~MainWindow() {
    delete plotData;
    delete measurementPlotData;
    delete lastReceivedMeasurement;
}



