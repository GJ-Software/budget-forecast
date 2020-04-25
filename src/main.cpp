#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <gtkmm.h>
#include <iostream>

#ifdef SQLITECPP_ENABLE_ASSERT_HANDLER
namespace SQLite
{
    void assertion_failed(const char* apFile, const long apLine, const char* apFunc, const char* apExpr, const char* apMsg)
    {
        // Print a message to the standard error output stream, and abort the program.
        std::cerr << apFile << ":" << apLine << ":" << " error: assertion failed (" << apExpr << ") in " << apFunc << "() with message \"" << apMsg << "\"\n";
        std::abort();
    }
}
#endif


Gtk::Window* mainWindow = nullptr;

static void testClicked(Gtk::Label* heckLabel) {
    heckLabel->set_text("HECK YOU");
    std::cout << "test" << std::endl;
}

int main (int argc, char *argv[]) {

    try {
        SQLite::Database db("/data/Test_DB.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
        std::cout << "SQLite database file '" << db.getFilename().c_str() << "' opened successfully\n";

        int nb = db.exec("INSERT INTO test VALUES (NULL, \"test\")");
        std::cout << "INSERT INTO test VALUES (NULL, \"test\")\", returned " << nb << std::endl;

    }
    catch (std::exception& e)
    {
        std::cout << "SQLite exception: " << e.what() << std::endl;
        return EXIT_FAILURE; // unexpected error : exit the example program
    }
    remove("Test_DB.db3");



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
