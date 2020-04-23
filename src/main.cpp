#include <iostream>
#include  <gtkmm.h>

Gtk::Window* mainWindow = nullptr;

static void testClicked(Gtk::Label* heckLabel) {
    heckLabel->set_text("HECK YOU");
    std::cout << "test" << std::endl;
}

int main (int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.budget-forecast");
    auto refBuilder = Gtk::Builder::create();
    try {
        // TODO: copy or bundle glade file with exe file
        refBuilder->add_from_file("src/glade/basic.glade");
    } catch(const Glib::FileError& ex) {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    } catch(const Glib::MarkupError& ex) {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    } catch(const Gtk::BuilderError& ex) {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

    refBuilder->get_widget("window", mainWindow);

    if(mainWindow) {
        Gtk::Button* heckButton = nullptr;
        refBuilder->get_widget("button1", heckButton);

        if(heckButton) {
            Gtk::Label* heckLabel = nullptr;
            refBuilder->get_widget("label1", heckLabel);
            heckButton->signal_clicked().connect(sigc::bind(sigc::ptr_fun(&testClicked), heckLabel));
        }

        app->run(*mainWindow);
    }
    return 0;
}
