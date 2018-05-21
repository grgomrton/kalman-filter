#include <gtkmm.h>
#include <GaussianNoiseProvider.h>
#include "MainWindow.h"

int main(int argc, char* argv[]) {
    auto app =
            Gtk::Application::create(argc, argv, "org.gtkmm.example");

    GaussianNoiseProvider noise;
    MainWindow window(std::to_string(noise.getNoise(0.1)));
    window.set_default_size(400, 200);

    return app->run(window);
    //delete window; should do if anything would happen after app.run
}