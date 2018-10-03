#include "MainWindow.h"
#include <gtkmm/label.h>
#include <gtkmm-plplot/plot2d.h>
#include <Localizer.h>
#include <Plotter.h>
#include <MainWindow.h>


MainWindow::MainWindow() : // todo x_scale here!
    currentPosition(GaussianDistributionDescriptor::makeFromAccuracy(0.0, 0.1)), // 0.0 +/-10 cm
    localizer(currentPosition),
    plotData(nullptr),
    plot("x", ""), // todo extract to consts
    moveLeftButton("Move left"),
    moveRightButton("Move right"),
    unitStepInMetres(1.0),
    movementAccuracyInPercentage(20.0) {

    auto label = Gtk::manage(new Gtk::Label("Current estimation: "));
    label->set_margin_bottom(10);
    layout.attach(*label, 1, 1, 2, 1);

    unsigned int reference_point_count = 1000;
    double start = -10;
    double end = 10;
    x_scale = Plotter::CreateUniformScale(start, end, reference_point_count);
    canvas.add_plot(plot);

    canvas.set_hexpand(true);
    canvas.set_vexpand(true);
    layout.attach(canvas, 1, 2, 2, 1);

    moveLeftButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::moveLeftClicked));
    layout.attach(moveLeftButton, 1, 3, 1, 1);

    moveRightButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::moveRightClicked));
    layout.attach(moveRightButton, 2, 3, 1, 1);

    add(layout);
    set_border_width(10);
    invalidate();
    show_all_children();
}

void MainWindow::moveLeftClicked() {
    currentPosition = localizer.movementUpdate(-unitStepInMetres, movementAccuracyInPercentage);
    invalidate();
    std::cout << "current position mean: " << currentPosition.getPosition() << " accuracy: " << currentPosition.getAccuracy() << std::endl;
}

void MainWindow::moveRightClicked() {
    currentPosition = localizer.movementUpdate(unitStepInMetres, movementAccuracyInPercentage);
    invalidate();
    std::cout << "current position mean: " << currentPosition.getPosition() << " accuracy: " << currentPosition.getAccuracy() << std::endl;
}


void MainWindow::invalidate() {
    if (plotData != nullptr) {
        plot.remove_data(*plotData);
    }
    delete plotData;
    plotData = nullptr;
    std::vector<double> y_values = Plotter::PlotGaussian(currentPosition.getPosition(), currentPosition.getVariance(),
                                                         x_scale);
    plotData = new Gtk::PLplot::PlotData2D(x_scale, y_values, Gdk::RGBA("red"));
    plot.add_data(*plotData);
}

MainWindow::~MainWindow() {
    delete plotData;
}


