/*!
 * \file main.c
 * \author Copyright (C) 2007, 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Main program for the pcb footprintwizard (pcb-gfpw).
 *
 * pcb-gfpw (GtkFootPrintWizard) is a program for the creation of footprint
 * files to be used by with the pcb layout application
 * (see http://pcb.sourgeforge.net) for the placement of parts in a pcb
 * layout.\n
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
        GtkToggleButton *thermal = NULL;
        GtkToggleButton *thermal_nopaste_checkbutton = NULL;
        GtkWidget *thermal_length_entry = NULL;
        GtkWidget *thermal_width_entry = NULL;
        GtkWidget *thermal_clearance_entry = NULL;
        GtkWidget *thermal_solder_mask_clearance_entry = NULL;
        GtkToggleButton *silkscreen_package_outline = NULL;
        GtkWidget *silkscreen_line_width_entry = NULL;
        GtkToggleButton *courtyard = NULL;
        GtkWidget *courtyard_length_entry = NULL;
        GtkWidget *courtyard_width_entry = NULL;
        GtkWidget *courtyard_line_width_entry = NULL;
        GtkWidget *courtyard_clearance_with_package_entry = NULL;
        GtkWidget *C1_entry = NULL;
        GtkWidget *C2_entry = NULL;
        GtkWidget *G1_entry = NULL;
        GtkWidget *G2_entry = NULL;
        GtkWidget *Z1_entry = NULL;
        GtkWidget *Z2_entry = NULL;

#ifdef ENABLE_NLS
        bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
        bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
        textdomain (GETTEXT_PACKAGE);
#endif
        gtk_set_locale ();
        gtk_init (&argc, &argv);
        add_pixmap_directory (PACKAGE_DATA_DIR "/" PACKAGE "/pixmaps");
        /*
         * The following code was added by Glade to create one of each
         * component (except popup menus), just so that you see something
         * after building the project.
         * Delete any components that you don't want shown initially.
         */
        /* Create and show the about dialog as a splash screen. */
        about_dialog = create_about_dialog ();
        gtk_widget_show (about_dialog);
        /* Now create the main dialog. */
        pcb_gfpw = create_pcb_gfpw ();
        /* Set the initial state of the checkbutton for the thermal pad to false,
         * set the "length" entry for the thermal pad to insensitive,
         * set the "width" entry for the thermal pad to insensitive,
         * set the "clearance" entry for the thermal pad to insensitive,
         * and set the "solder mask clearance" entry for the thermal pad to insensitive.
         */
        thermal = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_checkbutton");
        thermal_nopaste_checkbutton = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_nopaste_checkbutton");
        thermal_length_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_length_entry");
        thermal_width_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_width_entry");
        thermal_clearance_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_clearance_entry");
        thermal_solder_mask_clearance_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_solder_mask_clearance_entry");
        gtk_toggle_button_set_active (thermal, FALSE);
        gtk_widget_set_sensitive (thermal_nopaste_checkbutton, FALSE);
        gtk_widget_set_sensitive (thermal_length_entry, FALSE);
        gtk_widget_set_sensitive (thermal_width_entry, FALSE);
        gtk_widget_set_sensitive (thermal_clearance_entry, FALSE);
        gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, FALSE);
        /* Set the initial state of the checkbutton for the silkscreen to true,
         * set the "linewidth" entry for the silkscreen to sensitive.
         */
        silkscreen_package_outline = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "silkscreen_package_outline_checkbutton");
        silkscreen_line_width_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "silkscreen_line_width_entry");
        gtk_toggle_button_set_active (silkscreen_package_outline, TRUE);
        gtk_widget_set_sensitive (silkscreen_line_width_entry, TRUE);
        /* Set the state of the check button for the courtyard to false,
         * set the "length" entry for the courtyard to insensitive,
         * set the "width" entry for the courtyard to insensitive,
         * set the "linewidth" entry for the courtyard to insensitive,
         * and set the "clearance to package" entry for the courtyard to
         * insensitive.
         */
        courtyard = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "courtyard_checkbutton");
        courtyard_length_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "courtyard_length_entry");
        courtyard_width_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "courtyard_width_entry");
        courtyard_line_width_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "courtyard_line_width_entry");
        courtyard_clearance_with_package_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "courtyard_clearance_with_package_entry");
        gtk_toggle_button_set_active (courtyard, FALSE);
        gtk_widget_set_sensitive (courtyard_length_entry, FALSE);
        gtk_widget_set_sensitive (courtyard_width_entry, FALSE);
        gtk_widget_set_sensitive (courtyard_line_width_entry, FALSE);
        gtk_widget_set_sensitive (courtyard_clearance_with_package_entry, FALSE);
        /* Set the initial state of the entries adjacent to the radiobuttons in
         * the notebook tab  "Heel & Toe goals".
         * These entries are for entering the C1, C2, G1, G2, Z1 and Z2
         * variables.
         */
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
        /* Now show the main dialog. */
        gtk_widget_show (pcb_gfpw);
        /* Now enter the main loop */
        gtk_main ();
        return 0;
}

/* EOF */
