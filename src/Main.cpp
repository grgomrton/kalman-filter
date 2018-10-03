#include <gtkmm.h>
#include "MainWindow.h"

int main(int argc, char *argv[]) {

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    MainWindow window;
    window.set_default_size(480, 280);

    return app->run(window);
    //delete window; should do if anything would happen after app.run
}

