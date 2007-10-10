/*!
 * \file main.c
 * \author Copyright (C) 2007 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief gFootprintWizard is a program for the creation of footprint files
 * used by the pcb layout application (see http://pcb.sourgeforge.net) for
 * the placement of parts in a pcb layout.
 *
 */


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"

int
main (int argc, char *argv[])
{
        GtkWidget *pcb_gfpw;
        GtkWidget *about_dialog;

#ifdef ENABLE_NLS
        bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
        bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
        textdomain (GETTEXT_PACKAGE);
#endif

        gtk_set_locale ();
        gtk_init (&argc, &argv);

        add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");

        /*
         * The following code was added by Glade to create one of each component
         * (except popup menus), just so that you see something after building
         * the project. Delete any components that you don't want shown initially.
         */

        /* Create and show the about dialog as a splash screen. */
        about_dialog = create_about_dialog ();
        gtk_widget_show (about_dialog);

        /* Now create the main dialog. */
        pcb_gfpw = create_pcb_gfpw ();

        /* Set the initial state of the entrys adjacent to the radiobuttons in
         * the main dialog, these are for entering the C1, C2, G1, G2, Z1 and
         * Z2 variables.
         */
        GtkWidget *C1_entry = NULL;
        GtkWidget *C2_entry = NULL;
        GtkWidget *G1_entry = NULL;
        GtkWidget *G2_entry = NULL;
        GtkWidget *Z1_entry = NULL;
        GtkWidget *Z2_entry = NULL;

        C1_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "C1_entry");
        C2_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "C2_entry");
        G1_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "G1_entry");
        G2_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "G2_entry");
        Z1_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "Z1_entry");
        Z2_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "Z2_entry");
        gtk_widget_set_sensitive (C1_entry, TRUE);
        gtk_widget_set_sensitive (C2_entry, TRUE);
        gtk_widget_set_sensitive (G1_entry, FALSE);
        gtk_widget_set_sensitive (G2_entry, FALSE);
        gtk_widget_set_sensitive (Z1_entry, FALSE);
        gtk_widget_set_sensitive (Z2_entry, FALSE);

        /* Set the state of the check button for the thermal pad to false,
         * and set the length, width and solder mask entries for the thermal
         * pad to insensitive. */
        GtkToggleButton *thermal = NULL;
        GtkWidget *thermal_length_entry = NULL;
        GtkWidget *thermal_width_entry = NULL;
        GtkWidget *thermal_solder_mask_clearance_entry = NULL;

        thermal = lookup_widget (GTK_WIDGET (pcb_gfpw), "thermal_checkbutton");
        thermal_length_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "thermal_length_entry");
        thermal_width_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "thermal_width_entry");
        thermal_solder_mask_clearance_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "thermal_solder_mask_clearance_entry");
        gtk_toggle_button_set_active (thermal, FALSE);
        gtk_widget_set_sensitive (thermal_length_entry, FALSE);
        gtk_widget_set_sensitive (thermal_width_entry, FALSE);
        gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, FALSE);

        /* Now show the main dialog. */
        gtk_widget_show (pcb_gfpw);

        gtk_main ();
        return 0;
}

/* EOF */
