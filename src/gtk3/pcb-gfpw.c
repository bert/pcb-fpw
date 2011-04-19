/*!
 * \file src/gtk3/pcb-gfpw.c
 *
 * First run the glade files through gtk-builder-convert with this command:
 *   gtk-builder-convert pcb-gfpw.glade pcb-gfpw.xml
 *   gtk-builder-convert about_dialog.glade about_dialog.xml
 * 
 * Compile it using this command (those are backticks,
 * not single quotes):
 *   gcc -Wall -g -o pcb-gfpw pcb-gfpw.c `pkg-config --cflags --libs gtk+-2.0` -export-dynamic
 *
 * Then execute the program using:
 *   ./pcb-gfpw
 */


#include <gtk/gtk.h>

void 
on_window_destroy (GtkObject *object, gpointer user_data)
{
    gtk_main_quit ();
}


int
main (int argc, char *argv[])
{
    GtkBuilder *builder; 
    GtkWidget *about_dialog;

    gtk_init (&argc, &argv);
    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "about_dialog.glade", NULL);
    about_dialog = GTK_WIDGET (gtk_builder_get_object (builder, "about_dialog"));
    gtk_builder_connect_signals (builder, NULL);
    g_object_unref (G_OBJECT (builder));
    gtk_widget_show (about_dialog);                
    gtk_main ();
    return 0;
}


/* EOF */

