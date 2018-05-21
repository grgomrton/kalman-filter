#include <gtkmm/label.h>
#include "MainWindow.h"

MainWindow::MainWindow(const std::string& greetingText) :
        greeting(greetingText) {
    add(greeting);
    greeting.show();
}