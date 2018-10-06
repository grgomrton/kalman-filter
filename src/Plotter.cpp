#include <Plotter.h>
#include <GaussianDistributionDescriptor.h>
#include <gtkmm-plplot/plot2d.h>
#include <gtkmm-plplot/plotdata2d.h>
#include <PlotFunctions.h>

Plotter::Plotter(std::shared_ptr<Gtk::PLplot::Plot2D> plot, std::vector<double> scale) {    // todo check pointers
    scale_ = std::move(scale);
    plot_ = std::move(plot);
}

void Plotter::AddBelief(GaussianDistributionDescriptor pose) {
    std::vector<double> y_values = PlotFunctions::PlotGaussian(pose.getPosition(), pose.getVariance(), scale_);

    if (lastPosition_ != nullptr) { plot_->remove_data(*lastPosition_); }
    lastPosition_ = std::make_unique<Gtk::PLplot::PlotData2D>(scale_, y_values, Gdk::RGBA("red"));
    plot_->add_data(*lastPosition_);

    if (lastMeasurement_ != nullptr) { plot_->remove_data(*lastMeasurement_); }
    lastMeasurement_.reset();
}

void Plotter::AddMeasurement(GaussianDistributionDescriptor measurement) {
    std::vector<double> y_values = PlotFunctions::PlotGaussian(measurement.getPosition(),
                                                               measurement.getVariance(),
                                                               scale_);

    if (lastMeasurement_ != nullptr) { plot_->remove_data(*lastMeasurement_); }
    lastMeasurement_ = std::make_unique<Gtk::PLplot::PlotData2D>(scale_, y_values, Gdk::RGBA("blue"));
    plot_->add_data(*lastMeasurement_);
}

Plotter::~Plotter() {
    if (lastPosition_ != nullptr) { plot_->remove_data(*lastPosition_); }
    if (lastMeasurement_ != nullptr) { plot_->remove_data(*lastMeasurement_); }
}
