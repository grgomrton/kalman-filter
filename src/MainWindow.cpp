#include <gtkmm/label.h>
#include "MainWindow.h"

MainWindow::MainWindow(const char* greetingText) {
    Gtk::Label* greeting = Gtk::manage(new Gtk::Label(greetingText));
    add(*greeting);
    greeting->show();
}

MainWindow::~MainWindow() {

}
