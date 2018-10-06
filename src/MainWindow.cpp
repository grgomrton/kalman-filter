#include "MainWindow.h"
#include <gtkmm/label.h>
#include <gtkmm-plplot/plot2d.h>
#include <Localizer.h>
#include <Plotter.h>
#include <MainWindow.h>
#include <PlotFunctions.h>

MainWindow::MainWindow() :                                              // todo x_scale here!
        robotPositionInWorld(0.0),
        localizer(GaussianDistributionDescriptor::makeFromAccuracy(0.0, 2.0)),
        robotPositionInLocalizer(localizer.getPosition()),
        unitStepInMetres(1.0),
        movementAccuracyInPercentage(30.0),
        layout(),
        canvas(),
        plot(std::make_shared<Gtk::PLplot::Plot2D>("x", "")),           // todo extract to consts
        plotter(plot, PlotFunctions::CreateUniformScale(-100, 100, 1000)),        // todo to consts
        moveLeftButton("Move left"),
        moveRightButton("Move right"),
        getGpsSignalButton("Measure position") {
    plotter.AddBelief(robotPositionInLocalizer);

    auto label = Gtk::manage(new Gtk::Label("Current estimation: "));
    label->set_margin_bottom(10);
    layout.attach(*label, 1, 1, 3, 1);

    canvas.add_plot(*plot);
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
    show_all_children();
}

void MainWindow::moveLeftClicked() {
    robotPositionInWorld -= unitStepInMetres;
    robotPositionInLocalizer = localizer.movementUpdate(-unitStepInMetres, movementAccuracyInPercentage);
    plotter.AddBelief(robotPositionInLocalizer);
    std::cout << "current position mean: " << robotPositionInLocalizer.getPosition() << " error range: "
              << robotPositionInLocalizer.getAccuracy() << std::endl;
}

void MainWindow::moveRightClicked() {
    robotPositionInWorld += unitStepInMetres;
    robotPositionInLocalizer = localizer.movementUpdate(unitStepInMetres, movementAccuracyInPercentage);
    plotter.AddBelief(robotPositionInLocalizer);
    std::cout << "current position mean: " << robotPositionInLocalizer.getPosition() << " error range: "
              << robotPositionInLocalizer.getAccuracy() << std::endl;
}

void MainWindow::getGpsSignalClicked() {
    auto gpsAccuracyInMetres = 5.88;
    auto measuredPosition = robotPositionInWorld;                       // measurement without error
    auto measurement = GaussianDistributionDescriptor(
            GaussianDistributionDescriptor::makeFromAccuracy(measuredPosition, gpsAccuracyInMetres));
    robotPositionInLocalizer = localizer.measurementUpdate(measuredPosition, gpsAccuracyInMetres);
    plotter.AddBelief(robotPositionInLocalizer);
    plotter.AddMeasurement(measurement);
    std::cout << "current position mean: " << robotPositionInLocalizer.getPosition() << " error range: "
              << robotPositionInLocalizer.getAccuracy() << std::endl;
}



