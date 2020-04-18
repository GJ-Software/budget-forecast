
#include <gtkmm.h>


static GtkWidget*
create_window (void)
{

    GtkWidget *window;

    GtkBuilder *builder;

    GError* error = NULL;

    builder = gtk_builder_new ();
    if (!gtk_builder_add_from_file(builder, "aaa.glade", &error))
    {
        g_critical ("Can't load a file: %s", error->message);
        g_error_free (error);
    }
    gtk_builder_connect_signals (builder, NULL);

    window = GTK_WIDGET (gtk_builder_get_object (builder, "window"));
    if (!window)
    {
        g_critical ("Error getting window widget");
    }
    g_object_unref (builder);

    return window;
}


int main (int argc, char *argv[])
{
    GtkWidget *window;
    gtk_init (&argc, &argv);

    window = create_window ();
    gtk_widget_show (window);
    gtk_main ();
    return 0;
}