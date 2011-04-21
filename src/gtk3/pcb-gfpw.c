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
#include "about_dialog.h"


int
main (int argc, char *argv[])
{
    GtkWidget *about_dialog;

    gtk_init (&argc, &argv);
    about_dialog = create_about_dialog ();
    gtk_main ();
    return 0;
}


/* EOF */

