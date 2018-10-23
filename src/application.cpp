#include <gtkmm.h>
#include <demo_window.h>

int main(int argc, char *argv[]) {

    auto app = Gtk::Application::create(argc, argv, "hu.marc.kalmanfilter.demo");
    demo_window demo_window;
    demo_window.set_default_size(480, 280);
    demo_window.set_title("Kalman filter demo");

    return app->run(demo_window);
}

