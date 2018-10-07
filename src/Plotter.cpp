#include <Plotter.h>
#include <GaussianDistributionDescriptor.h>
#include <gtkmm-plplot/plot2d.h>
#include <gtkmm-plplot/plotdata2d.h>
#include <PlotFunctions.h>

Plotter::Plotter(std::shared_ptr<Gtk::PLplot::Plot2D> plot, std::vector<double> scale) {    // todo check pointers
    mScale = std::move(scale);
    mpPlot = std::move(plot);
}

void Plotter::AddBelief(GaussianDistributionDescriptor pose) {
    std::vector<double> y_values = PlotFunctions::PlotGaussian(pose.getPosition(), pose.getVariance(), mScale);

    if (mpLastPosition != nullptr) { mpPlot->remove_data(*mpLastPosition); }
    mpLastPosition = std::make_unique<Gtk::PLplot::PlotData2D>(mScale, y_values, Gdk::RGBA("red"));
    mpPlot->add_data(*mpLastPosition);

    if (mpLastMeasurement != nullptr) { mpPlot->remove_data(*mpLastMeasurement); }
    mpLastMeasurement.reset();
}

void Plotter::AddMeasurement(GaussianDistributionDescriptor measurement) {
    std::vector<double> y_values = PlotFunctions::PlotGaussian(measurement.getPosition(),
                                                               measurement.getVariance(),
                                                               mScale);

    if (mpLastMeasurement != nullptr) { mpPlot->remove_data(*mpLastMeasurement); }
    mpLastMeasurement = std::make_unique<Gtk::PLplot::PlotData2D>(mScale, y_values, Gdk::RGBA("blue"));
    mpPlot->add_data(*mpLastMeasurement);
}

Plotter::~Plotter() {
    if (mpLastPosition != nullptr) { mpPlot->remove_data(*mpLastPosition); }
    if (mpLastMeasurement != nullptr) { mpPlot->remove_data(*mpLastMeasurement); }
}
