#include <gtkmm/label.h>
#include "MainWindow.h"

MainWindow::MainWindow(const char* greetingText) {
    Gtk::Label* greeting = Gtk::manage(new Gtk::Label(greetingText));
    add(*greeting);
    set_border_width(10);
    greeting->show();
}

MainWindow::~MainWindow() {}
