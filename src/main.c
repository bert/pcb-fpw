/*!
 * \file main.c
 * \author Copyright (C) 2007, 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Main program for the pcb footprintwizard (pcb-gfpw).
 *
 * pcb-gfpw (GtkFootPrintWizard) is a program for the creation of footprint
 * files to be used by with the pcb layout application
 * (see http://pcb.sourgeforge.net) for the placement of parts in a pcb
 * layout.\n
 *
 * \todo When this wizard becomes really quit popular, we can write a function to
 * read from the footprintwizard files as to allow for editing or any other
 * (futuristic) purpose you can think of.\n
 * This needs debugging.
 *
 * \todo Add the preview widget.
 *
 * \todo Add a menubar (in the future ?).
 *
 * \todo GUI is now "static" and based on code generated with Glade.\n
 * In the distant future it can become neccessary to have a "dynamic" GUI to
 * be generated with libglade code.
 *
 * \todo Inserting of generated footprint into pcb by means of an Inter
 * Process Communication protocol such as DBUS for instance.
 *
 * This program is free software; you can redistribute it and/or modify\n
 * it under the terms of the GNU General Public License as published by\n
 * the Free Software Foundation; either version 2 of the License, or\n
 * (at your option) any later version.\n
 * \n
 * This program is distributed in the hope that it will be useful,\n
 * but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.\n
 * \n
 * You should have received a copy of the GNU General Public License\n
 * along with this program; if not, write to:\n
 * the Free Software Foundation, Inc.,\n
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\n
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
        /* Set the initial state of the total pins and pads entry to
         * insensitive. The entry is to be used as a label for most packages
         * as the total amount of pins and pads can be caluculated.
         * However for some packages it might be needed to set a value here.
         */
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "number_total_pins_entry");
        gtk_widget_set_sensitive (number_total_pins_entry, FALSE);
        /* Set the initial state of the checkbutton for the thermal pad to false,
         * set the "length" entry for the thermal pad to insensitive,
         * set the "width" entry for the thermal pad to insensitive,
         * set the "clearance" entry for the thermal pad to insensitive,
         * and set the "solder mask clearance" entry for the thermal pad to insensitive.
         */
        GtkToggleButton *thermal = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_checkbutton");
        gtk_toggle_button_set_active (thermal, FALSE);
        GtkToggleButton *thermal_nopaste_checkbutton = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_nopaste_checkbutton");
        gtk_widget_set_sensitive (thermal_nopaste_checkbutton, FALSE);
        GtkWidget *thermal_length_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_length_entry");
        gtk_widget_set_sensitive (thermal_length_entry, FALSE);
        GtkWidget *thermal_width_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_width_entry");
        gtk_widget_set_sensitive (thermal_width_entry, FALSE);
        GtkWidget *thermal_clearance_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_clearance_entry");
        gtk_widget_set_sensitive (thermal_clearance_entry, FALSE);
        GtkWidget *thermal_solder_mask_clearance_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_solder_mask_clearance_entry");
        gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, FALSE);
        /* Set the initial state of the checkbutton for the silkscreen to true,
         * set the "linewidth" entry for the silkscreen to sensitive.
         */
        GtkToggleButton *silkscreen_package_outline = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "silkscreen_package_outline_checkbutton");
        gtk_toggle_button_set_active (silkscreen_package_outline, TRUE);
        GtkWidget *silkscreen_line_width_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "silkscreen_line_width_entry");
        gtk_widget_set_sensitive (silkscreen_line_width_entry, TRUE);
        /* Set the state of the check button for the courtyard to false,
         * set the "length" entry for the courtyard to insensitive,
         * set the "width" entry for the courtyard to insensitive,
         * set the "linewidth" entry for the courtyard to insensitive,
         * and set the "clearance to package" entry for the courtyard to
         * insensitive.
         */
        GtkToggleButton *courtyard = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "courtyard_checkbutton");
        gtk_toggle_button_set_active (courtyard, FALSE);
        GtkWidget *courtyard_length_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "courtyard_length_entry");
        gtk_widget_set_sensitive (courtyard_length_entry, FALSE);
        GtkWidget *courtyard_width_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "courtyard_width_entry");
        gtk_widget_set_sensitive (courtyard_width_entry, FALSE);
        GtkWidget *courtyard_line_width_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "courtyard_line_width_entry");
        gtk_widget_set_sensitive (courtyard_line_width_entry, FALSE);
        GtkWidget *courtyard_clearance_with_package_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "courtyard_clearance_with_package_entry");
        gtk_widget_set_sensitive (courtyard_clearance_with_package_entry, FALSE);
        /* Set the initial state of the entries adjacent to the radiobuttons in
         * the notebook tab  "Heel & Toe goals".
         * These entries are for entering the C1, C2, G1, G2, Z1 and Z2
         * variables.
         */
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "C1_entry");
        gtk_widget_set_sensitive (C1_entry, TRUE);
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "C2_entry");
        gtk_widget_set_sensitive (C2_entry, TRUE);
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "G1_entry");
        gtk_widget_set_sensitive (G1_entry, FALSE);
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "G2_entry");
        gtk_widget_set_sensitive (G2_entry, FALSE);
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "Z1_entry");
        gtk_widget_set_sensitive (Z1_entry, FALSE);
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (pcb_gfpw), "Z2_entry");
        gtk_widget_set_sensitive (Z2_entry, FALSE);
        /* Now show the main dialog. */
        gtk_widget_show (pcb_gfpw);
        /* Now enter the main loop */
        gtk_main ();
        return 0;
}

/* EOF */
