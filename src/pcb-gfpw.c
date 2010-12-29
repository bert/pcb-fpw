/*!
 * \file src/pcb-gfpw.c
 *
 * \author Copyright (C) 2007, 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief GTK program for the pcb footprintwizard (pcb-gfpw).
 *
 * pcb-gfpw (GtkFootPrintWizard) is a program for the creation of footprint
 * files to be used by with the pcb layout application
 * (see http://pcb.sourgeforge.net) for the placement of parts in a pcb
 * layout.\n
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.\n
 * \n
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.\n
 * \n
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.\n
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "interface.h"
#include "support.h"


/*!
 * \brief The GTK GUI for the footprintwizard.
 *
 * \return 0 if successfull.
 */
int
main
(
        int argc, /*!< : number of arguments.*/
        char *argv[] /*!< : array of argument variables.*/
)
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
        /* Set the "Add license to footprint" checkbutton initially to
         * TRUE */
        GtkWidget *add_license_checkbutton = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "add_license_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (add_license_checkbutton),
                TRUE);
        /* Set the initial state of the total pins and pads entry to
         * sensitive. The entry is to be used as a label for most packages
         * as the total amount of pins and pads can be caluculated.
         * However for some packages it might be needed to set a value here.
         */
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "number_total_pins_entry");
        gtk_widget_set_sensitive (number_total_pins_entry, TRUE);
        GtkWidget *pin_pad_exceptions_button = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "pin_pad_exceptions_button");
        gtk_widget_set_sensitive (pin_pad_exceptions_button, FALSE);
        /* Set the initial state of the checkbutton for the thermal pad to false,
         * set the "length" entry for the thermal pad to insensitive,
         * set the "width" entry for the thermal pad to insensitive,
         * set the "clearance" entry for the thermal pad to insensitive,
         * and set the "solder mask clearance" entry for the thermal pad to insensitive.
         */
        GtkWidget *thermal_checkbutton = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (thermal_checkbutton), FALSE);
        GtkWidget *thermal_nopaste_checkbutton = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "thermal_nopaste_checkbutton");
        gtk_widget_set_sensitive (GTK_WIDGET (thermal_nopaste_checkbutton), FALSE);
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
        /* Set the initial state of the checkbutton for the fiducial pads to
         * false, set the "fiducial pad diameter" entry to insensitive,
         * and set the "fiducial pad clearance" entry to insensitive,
         * and set the "fiducial pad solder mask clearance" entry to insensitive.
         */
        GtkWidget *fiducial_checkbutton = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "fiducial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (fiducial_checkbutton), FALSE);
        GtkWidget *fiducial_pad_diameter_entry = lookup_widget
                (GTK_WIDGET (pcb_gfpw),
                "fiducial_pad_diameter_entry");
        gtk_widget_set_sensitive (fiducial_pad_diameter_entry, FALSE);
        GtkWidget *fiducial_pad_clearance_entry = lookup_widget
                (GTK_WIDGET (pcb_gfpw),
                "fiducial_pad_clearance_entry");
        gtk_widget_set_sensitive (fiducial_pad_clearance_entry, FALSE);
        GtkWidget *fiducial_pad_solder_mask_clearance_entry = lookup_widget
                (GTK_WIDGET (pcb_gfpw),
                "fiducial_pad_solder_mask_clearance_entry");
        gtk_widget_set_sensitive (fiducial_pad_solder_mask_clearance_entry,
                FALSE);
        /* Set the initial state of the checkbutton for the silkscreen to true,
         * set the "linewidth" entry for the silkscreen to sensitive.
         */
        GtkWidget *silkscreen_package_outline = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "silkscreen_package_outline_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (silkscreen_package_outline), TRUE);
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
        GtkWidget *courtyard_checkbutton = lookup_widget (GTK_WIDGET (pcb_gfpw),
                "courtyard_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (courtyard_checkbutton), FALSE);
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
