// project: GTKPeriodicTable
// file: main.cpp

#include <gtkmm/application.h>
#include "periodictablewindow.h"

#ifndef NLS
#define NLS 1
#define PROGRAMNAME_LOCALEDIR "."
#define GETTEXT_PACKAGE "GTKPeriodicTable"
#endif

int main(int argc, char *argv[])
{
#ifdef NLS
	setlocale(LC_ALL, "");
	bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);
#endif

    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    PeriodicTableWindow window(app);

    //Shows the window and returns when it is closed.
    return app->run(window);
}

