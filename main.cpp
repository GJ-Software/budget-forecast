#include <gtkmm.h>
#include "loadFile.h"




int main (int argc, char *argv[])
{
    GtkWidget *window;
    gtk_init (&argc, &argv);
    window = create_window();
    gtk_widget_show (window);
    gtk_main ();
    return 0;
}


extern "C" G_MODULE_EXPORT void testClicked (GtkButton *button, gpointer label)
{
    gtk_label_set_text(GTK_LABEL (label), "FUCK OFF");
}