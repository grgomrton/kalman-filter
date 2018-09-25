#include "MainWindow.h"

MainWindow::MainWindow(const std::string& greeting_text,
        const std::string& second_greeting_text,
        const std::valarray<double>& x_values,
        const std::valarray<double>& y_values,
        const std::string& x_axis_label,
        const std::string& y_axis_label)
        : greeting(greeting_text),
          data(x_values, y_values, Gdk::RGBA("red")),
          plot(data, x_axis_label, y_axis_label),
          canvas(plot) {
    layout.add(greeting);

    Gtk::Label *extended_greeting = Gtk::manage(new Gtk::Label("This is a sine function:"));
    layout.attach_next_to(*extended_greeting, Gtk::POS_BOTTOM, 1, 1);

    canvas.set_hexpand(true);
    canvas.set_vexpand(true);
    layout.attach_next_to(canvas, Gtk::POS_BOTTOM, 1, 1);

    add(layout);
    show_all_children();
}

