#include <gtkmm.h>
#include "MainWindow.h"

std::valarray<double> create_uniform_scale(double start, double end, int reference_point_count) {
    std::valarray<double> scale(reference_point_count);
    double step = (end - start) / (double) (reference_point_count - 1);
    for (int i = 0; i < reference_point_count; i++) {
        scale[i] = start + i * step;
    }
    return scale;
}

int main(int argc, char *argv[]) {
    std::string greeting_message = "Hi!";
    std::string second_greeting_message = "This is a sine function:";

    std::string x_caption = "x";
    std::string y_caption = "sin(x)";
    int reference_point_count = 100;
    double start = 0;
    double end = 6.28;
    std::valarray<double> x_values = create_uniform_scale(start, end, reference_point_count);
    std::valarray<double> y_values = sin(x_values);

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    MainWindow window(greeting_message, second_greeting_message, x_values, y_values, x_caption, y_caption);
    window.set_default_size(480, 280);

    return app->run(window);
    //delete window; should do if anything would happen after app.run
}

