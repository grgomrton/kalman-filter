#include <Plotter.h>
#include <GaussianDistributionDescriptor.h>
#include <gtkmm-plplot.h>
#include <PlotFunctions.h>

Plotter::Plotter(std::shared_ptr<Gtk::PLplot::Plot2D> plot, double scaleBegin, double scaleEnd,
                 int referencePointCount) {
    scale_ = PlotFunctions::CreateUniformScale(scaleBegin, scaleEnd, referencePointCount);
    plot_ = plot;
    plotData_ = nullptr;
    measurementPlotData = nullptr;
}

void Plotter::AddBelief(GaussianDistributionDescriptor pose) {
    if (plotData_ != nullptr) {
        plot_->remove_data(*plotData_);
    }
    delete plotData_;
    plotData_ = nullptr;
    if (measurementPlotData != nullptr) {
        plot_->remove_data(*measurementPlotData);
    }
    delete measurementPlotData;
    measurementPlotData = nullptr;

    std::vector<double> y_values = PlotFunctions::PlotGaussian(pose.getPosition(), pose.getVariance(), scale_);
    plotData_ = new Gtk::PLplot::PlotData2D(scale_, y_values, Gdk::RGBA("red"));
    plot_->add_data(*plotData_);
}

void Plotter::AddMeasurement(GaussianDistributionDescriptor measurement) {
    if (measurementPlotData != nullptr) {
        plot_->remove_data(*measurementPlotData);
    }
    delete measurementPlotData;
    measurementPlotData = nullptr;

    std::vector<double> meas_y_values = PlotFunctions::PlotGaussian(measurement.getPosition(), measurement.getVariance(),
                                                     scale_);
    measurementPlotData = new Gtk::PLplot::PlotData2D(scale_, meas_y_values, Gdk::RGBA("blue"));
    plot_->add_data(*measurementPlotData);
}

Plotter::~Plotter() {
    if (plotData_ != nullptr) {
        plot_->remove_data(*plotData_);
    }
    delete plotData_;
    plotData_ = nullptr;

    if (measurementPlotData != nullptr) {
        plot_->remove_data(*measurementPlotData);
    }
    delete measurementPlotData;
    measurementPlotData = nullptr;
}
