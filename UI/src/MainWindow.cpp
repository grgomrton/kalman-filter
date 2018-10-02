#include "MainWindow.h"
#include <gtkmm/label.h>
#include <gtkmm-plplot/plot2d.h>
#include <Localizer.h>

MainWindow::MainWindow() {
    GaussianDistributionDescriptor initial_position_localizer = GaussianDistributionDescriptor::GaussianDistributionDescriptor(0.0, 0.1); // 0.0 +/-10 cm
    Localizer localizer(initial_position_localizer);

    auto label = Gtk::manage(new Gtk::Label("Current estimation: "));
    label->set_margin_bottom(10);
    layout.attach_next_to(*label, Gtk::POS_BOTTOM, 1, 1);

    GaussianDistributionDescriptor current_estimation = localizer.getPosition();
    auto y_stdddev = [](double x, double mean, double variance) { return 1 / (sqrt(variance)*sqrt(2*M_PI))*pow(M_E, -0.5*pow((x-mean)/sqrt(variance), 2)); }; // ugh
    std::string x_caption = "x";
    std::string y_caption = "";
    unsigned int reference_point_count = 1000;
    double start = -10;
    double end = 10;
    std::vector<double> x_values = uniformScale(start, end, reference_point_count);
    std::vector<double> y_values;
    for (double x : x_values) {
        y_values.push_back(y_stdddev(x, current_estimation.getPosition(), current_estimation.getVariance()));
    }

    auto plot_data = Gtk::manage(new Gtk::PLplot::PlotData2D(x_values, y_values, Gdk::RGBA("red")));
    auto plot = Gtk::manage(new Gtk::PLplot::Plot2D(*plot_data, x_caption, y_caption));
    canvas.add_plot(*plot);

    canvas.set_hexpand(true);
    canvas.set_vexpand(true);
    layout.attach_next_to(canvas, Gtk::POS_BOTTOM, 1, 1);

    add(layout);
    set_border_width(10);
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

