#include "MainWindow.h"
#include <gtkmm/label.h>
#include <gtkmm-plplot/plot2d.h>
#include <Localizer.h>
#include <Plotter.h>
#include <MainWindow.h>
#include <Plot_functions.h>

MainWindow::MainWindow() :                                              // todo x_scale here!
        robotPositionInWorld(0.0),
        localizer(Estimated_position::from_accuracy(0.0, 2.0)),
        robotPositionInLocalizer(localizer.getPosition()),
        unitStepInMetres(1.0),
        movementAccuracyInPercentage(30.0),
        layout(),
        canvas(),
        plot(std::make_shared<Gtk::PLplot::Plot2D>("x", "")),           // todo extract to consts
        plotter(plot, Plot_functions::create_uniform_scale(-50, 50, 1000)),        // todo to consts
        moveLeftButton("Move left"),
        moveRightButton("Move right"),
        getGpsSignalButton("Measure position") {
    plotter.add_estimation(robotPositionInLocalizer);

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
    plotter.add_estimation(robotPositionInLocalizer);
    std::cout << "current position mean: " << robotPositionInLocalizer.get_position() << " error range: "
              << robotPositionInLocalizer.get_accuracy() << std::endl;
}

void MainWindow::moveRightClicked() {
    robotPositionInWorld += unitStepInMetres;
    robotPositionInLocalizer = localizer.movementUpdate(unitStepInMetres, movementAccuracyInPercentage);
    plotter.add_estimation(robotPositionInLocalizer);
    std::cout << "current position mean: " << robotPositionInLocalizer.get_position() << " error range: "
              << robotPositionInLocalizer.get_accuracy() << std::endl;
}

void MainWindow::getGpsSignalClicked() {
    auto gpsAccuracyInMetres = 5.88;
    auto measuredPosition = robotPositionInWorld;                       // measurement without error
    auto measurement = Estimated_position(
            Estimated_position::from_accuracy(measuredPosition, gpsAccuracyInMetres));
    robotPositionInLocalizer = localizer.measurementUpdate(measuredPosition, gpsAccuracyInMetres);
    plotter.add_estimation(robotPositionInLocalizer);
    plotter.add_measurement(measurement);
    std::cout << "current position mean: " << robotPositionInLocalizer.get_position() << " error range: "
              << robotPositionInLocalizer.get_accuracy() << std::endl;
}



