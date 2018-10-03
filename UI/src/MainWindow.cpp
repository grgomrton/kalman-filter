#include "MainWindow.h"
#include <gtkmm/label.h>
#include <gtkmm-plplot/plot2d.h>
#include <Localizer.h>
#include <MainWindow.h>


MainWindow::MainWindow() : // todo x_scale here!
    currentPosition(GaussianDistributionDescriptor::makeFromAccuracy(0.0, 0.1)), // 0.0 +/-10 cm
    localizer(currentPosition),
    plotData(nullptr),
    plot("x", ""), // todo extract to consts
    moveLeftButton("Move left") {

    auto label = Gtk::manage(new Gtk::Label("Current estimation: "));
    label->set_margin_bottom(10);
    layout.attach_next_to(*label, Gtk::POS_BOTTOM, 1, 1);

    unsigned int reference_point_count = 1000;
    double start = -10;
    double end = 10;
    x_scale = uniformScale(start, end, reference_point_count);
    canvas.add_plot(plot);

    canvas.set_hexpand(true);
    canvas.set_vexpand(true);
    layout.attach_next_to(canvas, Gtk::POS_BOTTOM, 1, 1);

    moveLeftButton.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::moveLeftClicked));
    layout.attach_next_to(moveLeftButton, Gtk::POS_BOTTOM, 1, 1);

    add(layout);
    set_border_width(10);
    invalidate();
    show_all_children();
}

std::vector<double> MainWindow::uniformScale(double start, double end, unsigned int reference_point_count) {
    std::vector<double> scale(reference_point_count);
    double step = (end - start) / (double) (reference_point_count - 1);
    for (int i = 0; i < reference_point_count; i++) {
        scale[i] = start + i * step;
    }
    return scale;
}

void MainWindow::moveLeftClicked() {
    currentPosition = localizer.movementUpdate(-1.0, 20);
    invalidate();
    std::cout << "current position mean: " << currentPosition.getPosition() << " variance: " << currentPosition.getVariance() << std::endl;
    std::cout << "updated!" << std::endl;
}

std::vector<double> MainWindow::plotGaussian(double mean, double variance, const std::vector<double>& scale) {
    auto fx = [](double x, double mean, double variance) { return 1 / (sqrt(variance)*sqrt(2*M_PI))*pow(M_E, -0.5*pow((x-mean)/sqrt(variance), 2)); }; // ugh
    std::vector<double> y_values(scale.size());
    for (int i=0; i<y_values.size(); i++) {
        y_values[i] = fx(scale[i], mean, variance);
    }
    return y_values;
}

void MainWindow::invalidate() {
    if (plotData != nullptr) {
        plot.remove_data(*plotData);
    }
    delete plotData;
    plotData = nullptr;
    std::vector<double> y_values = plotGaussian(currentPosition.getPosition(), currentPosition.getVariance(), x_scale);
    plotData = new Gtk::PLplot::PlotData2D(x_scale, y_values, Gdk::RGBA("red"));
    plot.add_data(*plotData);
}

MainWindow::~MainWindow() {
    delete plotData;
}

