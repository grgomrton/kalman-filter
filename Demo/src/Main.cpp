#include <gtkmm.h>
#include <Main_window.h>

int main(int argc, char *argv[]) {

    auto app = Gtk::Application::create(argc, argv, "hu.marc.kalmanfilter.demo");
    Main_window window;
    window.set_default_size(480, 280);
    window.set_title("Kalman filter");

    return app->run(window);
}

