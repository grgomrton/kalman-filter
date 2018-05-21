#pragma once

#include <gtkmm/window.h>

class MainWindow : public Gtk::Window {
public:
    MainWindow(const std::string& greetingText);

private:
    Gtk::Label greeting;
};
