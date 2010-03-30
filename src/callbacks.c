/*!
 * \file callbacks.c
 * \author Copyright 2007, 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Callback functions for the pcb footprintwizard (pcb-gfpw).
 *
 * pcb-gfpw (GtkFootPrintWizard) is a program for the creation of
 * footprint files to be used by the pcb layout application
 * (see http://pcb.gpleda.org) for the placement of parts in a pcb
 * layout.\n
 * \n
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

#include "callbacks.h"
#include "interface.h"
#include "support.h"

/*! Define whether this is a GUI or not. */
#define GUI 1

#include "libfpw.c"
#include "packages.h"
#include "dimensions.c"
#include "preview.h"
#include "select_exceptions.c"


gboolean main_window_title_has_asterisk = FALSE;
        /*!< Keep track whether the main window title has an asterisk between
         * brackets or not. */
gboolean fpw_file_saved = FALSE;
        /*!< Keep track whether the FootPrintWizard file is saved, and thus
         * has a valid filename. */
gchar *temp_dir = NULL;
        /*!< Temporary directory from the GUI filechooser. */
gchar *work_dir = NULL;
        /*!< Working directory. */


/*!
 * \brief All entries need to be updated.
 *
 * For some reason (e.g. loading a fpw-file or looking a pre-defined package
 * for instance) the entry fields, combo boxes and check buttons need to be
 * updated to be in sync with the global variables (which are considered
 * leading over the actual values shown in the GUI in this case).
 * This function is to be called on one of the following events:
 * <ul>
 * <li>The "refresh" button is clicked.
 * <li>The "footprint name" entry has changed.
 * <li>The "open" button of the file chooser is clicked and new values are
 * loaded successfull.
 * </ul>
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Returns:</b> none.
 */
int
all_entries_need_updated (GtkWidget *widget)
{
	/* *Recalculate the number of pins and/or pads.*/
        number_of_pins_has_changed (widget);
        /* Widgets on tab "Footprint". */
        /* Only update the "footprint type" entry with a sensible value. */
        if (footprint_type)
        {
                GtkWidget *footprint_type_entry = lookup_widget
                        (GTK_WIDGET (widget), "footprint_type_entry");
                gtk_widget_set_sensitive (footprint_type_entry, TRUE);
                gtk_combo_box_set_active (GTK_COMBO_BOX
                        (footprint_type_entry), package_type);
        }
        /* Only update the "footprint name" entry with a sensible value. */
        if (footprint_name)
        {
                GtkWidget *footprint_name_entry = lookup_widget (GTK_WIDGET
                        (widget), "footprint_name_entry");
                gtk_widget_set_sensitive (footprint_name_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (footprint_name_entry),
                        footprint_name);
        }
        /* Only update the "footprint units" entry with a sensible value. */
        if (footprint_units)
        {
                GtkWidget *footprint_units_entry = lookup_widget (GTK_WIDGET
                        (widget), "footprint_units_entry");
                gtk_widget_set_sensitive (footprint_units_entry, TRUE);
                update_units_variables ();
                gtk_combo_box_set_active (GTK_COMBO_BOX (footprint_units_entry),
                        units_type);
        }
        /* Only update the "footprint refdes prefix" entry with a sensible
         * value. */
        if (footprint_refdes)
        {
                GtkWidget *footprint_refdes_entry = lookup_widget
                        (GTK_WIDGET (widget), "footprint_refdes_entry");
                gtk_widget_set_sensitive (footprint_refdes_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (footprint_refdes_entry),
                        footprint_refdes);
        }
        /* Only update the "footprint value" entry with a sensible value. */
        if (footprint_value)
        {
                GtkWidget *footprint_value_entry = lookup_widget
                        (GTK_WIDGET (widget), "footprint_value_entry");
                gtk_widget_set_sensitive (footprint_value_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (footprint_value_entry),
                        footprint_value);
        }
        /* Only update the "package body length" entry with a sensible value. */
        if (package_body_length != 0.0)
        {
                GtkWidget *package_body_length_entry = lookup_widget (GTK_WIDGET (widget),
                        "package_body_length_entry");
                gtk_widget_set_sensitive (package_body_length_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (package_body_length_entry),
                        g_strdup_printf ("%f", package_body_length));
        }
        /* Only update the "package body width" entry with a sensible value. */
        if (package_body_width != 0.0)
        {
                GtkWidget *package_body_width_entry = lookup_widget (GTK_WIDGET (widget),
                        "package_body_width_entry");
                gtk_widget_set_sensitive (package_body_width_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (package_body_width_entry),
                        g_strdup_printf ("%f", package_body_width));
        }
        /* Only update the "package body height" entry with a sensible value. */
        if (package_body_height != 0.0)
        {
                GtkWidget *package_body_height_entry = lookup_widget (GTK_WIDGET (widget),
                        "package_body_height_entry");
                gtk_widget_set_sensitive (package_body_height_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (package_body_height_entry),
                        g_strdup_printf ("%f", package_body_height));
        }
        /* Update the "package is radial" checkbutton. */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET
                (widget), "package_is_radial_checkbutton");
        gtk_widget_set_sensitive (package_is_radial_checkbutton, TRUE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
                (package_is_radial_checkbutton), package_is_radial);
        /* Update the "add license to footprint" checkbutton. */
        GtkWidget *add_license_checkbutton = lookup_widget (GTK_WIDGET
                (widget), "add_license_checkbutton");
        gtk_widget_set_sensitive (add_license_checkbutton, TRUE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
                (add_license_checkbutton), license_in_footprint);
	/* Update the "add attributes" checkbutton. */
        GtkWidget *add_attribs_checkbutton = lookup_widget (GTK_WIDGET
                (widget), "add_attribs_checkbutton");
        gtk_widget_set_sensitive (add_attribs_checkbutton, TRUE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
                (add_attribs_checkbutton), attributes_in_footprint);
        /* Only update the "footprint author" entry with a sensible value. */
        if (footprint_author)
        {
                GtkWidget *footprint_author_entry = lookup_widget (GTK_WIDGET (widget),
                        "footprint_author_entry");
                gtk_widget_set_sensitive (footprint_author_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (footprint_author_entry),
                        g_get_real_name ());
        }
        /* Only update the "footprint distribution license" entry with a
         * sensible value. */
        if (footprint_dist_license)
        {
                GtkWidget *footprint_dist_license_entry = lookup_widget
                        (GTK_WIDGET (widget),
                        "footprint_dist_license_entry");
                gtk_widget_set_sensitive (footprint_dist_license_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (footprint_dist_license_entry),
                        footprint_dist_license);
        }
        /* Only update the "footprint usage license" entry with a sensible
         * value. */
        if (footprint_use_license)
        {
                GtkWidget *footprint_use_license_entry = lookup_widget
                        (GTK_WIDGET (widget), "footprint_use_license_entry");
                gtk_widget_set_sensitive (footprint_use_license_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (footprint_use_license_entry),
                        footprint_use_license);
        }
        /* Only update the "footprint units" entry with a sensible value. */
        if (footprint_status)
        {
                GtkWidget *footprint_status_entry = lookup_widget (GTK_WIDGET
                        (widget), "footprint_status_entry");
                gtk_widget_set_sensitive (footprint_status_entry, TRUE);
                gtk_combo_box_set_active (GTK_COMBO_BOX (footprint_status_entry),
                        status_type);
        }
        /* Widgets on tab "Pins/Pads". */
        /* Only update the "number of pins" entry with a sensible value. */
        if (number_of_pins != 0)
        {
                GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (widget),
                        "number_total_pins_entry");
                gtk_widget_set_sensitive (number_total_pins_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (number_total_pins_entry),
                        g_strdup_printf ("%d", number_of_pins));
        }
        /* Only update the "number of rows" entry with a sensible value. */
        if (number_of_rows != 0)
        {
                GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                        "number_of_rows_entry");
                gtk_widget_set_sensitive (number_of_rows_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (number_of_rows_entry),
                        g_strdup_printf ("%d", number_of_rows));
        }
        /* Only update the "number of columns" entry with a sensible value. */
        if (number_of_columns != 0)
        {
                GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                        "number_of_columns_entry");
                gtk_widget_set_sensitive (number_of_columns_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (number_of_columns_entry),
                        g_strdup_printf ("%d", number_of_columns));
        }
        /* Only update the "pitch x" entry with a sensible value. */
        if (pitch_x != 0.0)
        {
                GtkWidget *pitch_x_entry = lookup_widget (GTK_WIDGET (widget),
                        "pitch_x_entry");
                gtk_widget_set_sensitive (pitch_x_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (pitch_x_entry),
                        g_strdup_printf ("%f", pitch_x));
        }
        /* Only update the "pitch y" entry with a sensible value. */
        if (pitch_y != 0.0)
        {
                GtkWidget *pitch_y_entry = lookup_widget (GTK_WIDGET (widget),
                        "pitch_y_entry");
                gtk_widget_set_sensitive (pitch_y_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (pitch_y_entry),
                        g_strdup_printf ("%f", pitch_y));
        }
        /* Only update the "count x" entry with a sensible value */
        if (count_x != 0)
        {
                GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                        "count_x_entry");
                gtk_widget_set_sensitive (count_x_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (count_x_entry),
                        g_strdup_printf ("%d", count_x));
        }
        /* Only update the "count y" entry with a sensible value */
        if (count_y != 0)
        {
                GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (widget),
                        "count_y_entry");
                gtk_widget_set_sensitive (count_y_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (count_y_entry),
                        g_strdup_printf ("%d", count_y));
        }
        /* Only update the "pin/pad exceptions" entry with a sensible value. */
        if (pin_pad_exceptions_string || (!strcmp (pin_pad_exceptions_string, "")))
        {
                GtkWidget *pin_pad_exceptions_entry = lookup_widget
                        (GTK_WIDGET (widget), "pin_pad_exceptions_entry");
                gtk_widget_set_sensitive (pin_pad_exceptions_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (pin_pad_exceptions_entry),
                        g_strdup_printf ("%s", pin_pad_exceptions_string));
        }
        /* Only update the "pin #1 position" entry with a sensible value */
        if (pin_1_position)
        {
                GtkWidget *pin_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                        "number_1_position_entry");
                gtk_widget_set_sensitive (pin_1_position_entry, TRUE);
                update_location_variables ();
                gtk_combo_box_set_active (GTK_COMBO_BOX (pin_1_position_entry),
                        pin1_location);
        }
        /* Only update the "pad diameter" entry with a sensible value */
        if (pad_diameter != 0.0)
        {
                GtkWidget *pad_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                        "pad_diameter_entry");
                gtk_widget_set_sensitive (pad_diameter_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (pad_diameter_entry),
                        g_strdup_printf ("%f", pad_diameter));
        }
        /* Only update the "pin drill diameter" entry with a sensible value */
        if (pin_drill_diameter != 0.0)
        {
                GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                        "pin_drill_diameter_entry");
                gtk_widget_set_sensitive (pin_drill_diameter_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (pin_drill_diameter_entry),
                        g_strdup_printf ("%f", pin_drill_diameter));
        }
        GtkWidget *pin1_square_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "pin_square_checkbutton");
        gtk_widget_set_sensitive (pin1_square_checkbutton, TRUE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (pin1_square_checkbutton),
                pin1_square);
        /* Only update the "pad shape" entry with a sensible value */
        if (pad_shape)
        {
                GtkWidget *pad_shape_entry = lookup_widget (GTK_WIDGET (widget),
                        "pad_shape_entry");
                gtk_widget_set_sensitive (pad_shape_entry, TRUE);
                update_pad_shapes_variables ();
                gtk_combo_box_set_active (GTK_COMBO_BOX (pad_shape_entry), pad_shapes_type);
        }
        /* Only update the "pad length" entry with a sensible value */
        if (pad_length != 0.0)
        {
                GtkWidget *pad_length_entry = lookup_widget (GTK_WIDGET (widget),
                        "pad_length_entry");
                gtk_widget_set_sensitive (pad_length_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (pad_length_entry),
                        g_strdup_printf ("%f", pad_length));
        }
        /* Only update the "pad width" entry with a sensible value */
        if (pad_width != 0.0)
        {
                GtkWidget *pad_width_entry = lookup_widget (GTK_WIDGET (widget),
                        "pad_width_entry");
                gtk_widget_set_sensitive (pad_width_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (pad_width_entry),
                        g_strdup_printf ("%f", pad_width));
        }
        /* Only update the "pad clearance" entry with a sensible value */
        if (pad_clearance != 0.0)
        {
                GtkWidget *pad_clearance_entry = lookup_widget (GTK_WIDGET (widget),
                        "pad_clearance_entry");
                gtk_widget_set_sensitive (pad_clearance_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (pad_clearance_entry),
                        g_strdup_printf ("%f", pad_clearance));
        }
        /* Only update the "pad solder mask clearance" entry with a sensible value */
        if (pad_solder_mask_clearance != 0.0)
        {
                GtkWidget *pad_solder_mask_clearance_entry = lookup_widget (GTK_WIDGET (widget),
                        "pad_solder_mask_clearance_entry");
                gtk_widget_set_sensitive (pad_solder_mask_clearance_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (pad_solder_mask_clearance_entry),
                        g_strdup_printf ("%f", pad_solder_mask_clearance));
        }
        /* Widgets on tab "Silkscreen" */
        GtkWidget *silkscreen_package_outline_checkbutton =
                lookup_widget (GTK_WIDGET (widget),
                "silkscreen_package_outline_checkbutton");
        gtk_widget_set_sensitive (silkscreen_package_outline_checkbutton, TRUE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
                (silkscreen_package_outline_checkbutton),
                silkscreen_package_outline);
        GtkWidget *silkscreen_indicate_1_checkbutton =
                lookup_widget (GTK_WIDGET (widget),
                "silkscreen_indicate_1_checkbutton");
        gtk_widget_set_sensitive (silkscreen_indicate_1_checkbutton, TRUE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
                (silkscreen_indicate_1_checkbutton),
                silkscreen_indicate_1);
        /* Only update the "courtyard length" entry with a sensible value. */
        if (courtyard_length != 0.0)
        {
                GtkWidget *courtyard_length_entry = lookup_widget (GTK_WIDGET
                        (widget), "courtyard_length_entry");
                gtk_widget_set_sensitive (courtyard_length_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY
                        (courtyard_length_entry),
                        g_strdup_printf ("%f",
                        courtyard_length));
        }
        /* Only update the "courtyard width" entry with a sensible value. */
        if (courtyard_width != 0.0)
        {
                GtkWidget *courtyard_width_entry = lookup_widget (GTK_WIDGET (widget),
                        "courtyard_width_entry");
                gtk_widget_set_sensitive (courtyard_width_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY
                        (courtyard_width_entry),
                        g_strdup_printf ("%f",
                        courtyard_width));
        }
        /* Only update the "courtyard line width" entry with a sensible value. */
        if (courtyard_line_width != 0.0)
        {
                GtkWidget *courtyard_line_width_entry = lookup_widget (GTK_WIDGET (widget),
                        "courtyard_line_width_entry");
                gtk_widget_set_sensitive (courtyard_line_width_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY
                        (courtyard_line_width_entry),
                        g_strdup_printf ("%f",
                        courtyard_line_width));
        }
        /* Only update the "courtyard clearance with package" entry with a sensible value. */
        if (courtyard_clearance_with_package != 0.0)
        {
                GtkWidget *courtyard_clearance_with_package_entry =
                        lookup_widget (GTK_WIDGET (widget),
                        "courtyard_clearance_with_package_entry");
                gtk_widget_set_sensitive (courtyard_clearance_with_package_entry,
                        TRUE);
                gtk_entry_set_text (GTK_ENTRY
                        (courtyard_clearance_with_package_entry),
                        g_strdup_printf ("%f",
                        courtyard_clearance_with_package));
        }
        /* Widgets on tab "Thermal Pads". */
        /* Update the "thermal" checkbutton. */
        GtkWidget *thermal_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "thermal_checkbutton");
        gtk_widget_set_sensitive (thermal_checkbutton, TRUE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (thermal_checkbutton),
                thermal);
        /* Update the "thermal nopaste" checkbutton. */
        GtkWidget *thermal_nopaste_checkbutton = lookup_widget
                (GTK_WIDGET (widget), "thermal_nopaste_checkbutton");
        gtk_widget_set_sensitive (thermal_nopaste_checkbutton, TRUE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON
                (thermal_nopaste_checkbutton), thermal_nopaste);
        /* Only update the "thermal length" entry with a sensible value. */
        if (thermal_length != 0.0)
        {
                GtkWidget *thermal_length_entry = lookup_widget
                        (GTK_WIDGET (widget), "thermal_length_entry");
                gtk_widget_set_sensitive (thermal_length_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (thermal_length_entry),
                        g_strdup_printf ("%f", thermal_length));
        }
        /* Only update the "thermal width" entry with a sensible value. */
        if (thermal_width != 0.0)
        {
                GtkWidget *thermal_width_entry = lookup_widget
                        (GTK_WIDGET (widget), "thermal_width_entry");
                gtk_widget_set_sensitive (thermal_width_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (thermal_width_entry),
                        g_strdup_printf ("%f", thermal_width));
        }
        /* Only update the "thermal pad clearance" entry with a sensible
         * value. */
        if (thermal_clearance != 0.0)
        {
                GtkWidget *thermal_clearance_entry = lookup_widget
                        (GTK_WIDGET (widget), "thermal_clearance_entry");
                gtk_widget_set_sensitive (thermal_clearance_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (thermal_clearance_entry),
                        g_strdup_printf ("%f", thermal_clearance));
        }
        /* Only update the "thermal pad clearance" entry with a sensible
         * value. */
        if (thermal_solder_mask_clearance != 0.0)
        {
                GtkWidget *thermal_solder_mask_clearance_entry =
                        lookup_widget (GTK_WIDGET (widget),
                        "thermal_solder_mask_clearance_entry");
                gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry,
                        TRUE);
                gtk_entry_set_text (GTK_ENTRY
                        (thermal_solder_mask_clearance_entry),
                        g_strdup_printf ("%f",
                        thermal_solder_mask_clearance));
        }
        GtkWidget *fiducial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "fiducial_checkbutton");
        gtk_widget_set_sensitive (fiducial_checkbutton, TRUE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (fiducial_checkbutton),
                fiducial);
        /* Only update the "fiducial pad diameter" entry with a sensible
         * value. */
        if (fiducial_pad_diameter != 0.0)
        {
                GtkWidget *fiducial_pad_diameter_entry = lookup_widget
                        (GTK_WIDGET (widget), "fiducial_pad_diameter_entry");
                gtk_widget_set_sensitive (fiducial_pad_diameter_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (fiducial_pad_diameter_entry),
                        g_strdup_printf ("%f", fiducial_pad_diameter));
        }
        /* Only update the "fiducial pad clearance" entry with a
         * sensible value. */
        if (fiducial_pad_clearance != 0.0)
        {
                GtkWidget *fiducial_pad_clearance_entry =
                        lookup_widget (GTK_WIDGET (widget),
                        "fiducial_pad_clearance_entry");
                gtk_widget_set_sensitive (fiducial_pad_clearance_entry,
                        TRUE);
                gtk_entry_set_text (GTK_ENTRY
                        (fiducial_pad_clearance_entry),
                        g_strdup_printf ("%f",
                        fiducial_pad_clearance));
        }
        /* Only update the "fiducial pad solder mask clearance" entry with a
         * sensible value. */
        if (fiducial_pad_solder_mask_clearance != 0.0)
        {
                GtkWidget *fiducial_pad_solder_mask_clearance_entry =
                        lookup_widget (GTK_WIDGET (widget),
                        "fiducial_pad_solder_mask_clearance_entry");
                gtk_widget_set_sensitive (fiducial_pad_solder_mask_clearance_entry,
                        TRUE);
                gtk_entry_set_text (GTK_ENTRY
                        (fiducial_pad_solder_mask_clearance_entry),
                        g_strdup_printf ("%f",
                        fiducial_pad_solder_mask_clearance));
        }
        /* Widgets on tab "Heel & Toe goals" */
        /* Only update the "C1" entry with a sensible value. */
        if (c1 != 0.0)
        {
                GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (widget),
                        "C1_entry");
                gtk_widget_set_sensitive (C1_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (C1_entry),
                        g_strdup_printf ("%f", c1));
        }
        /* Only update the "G1" entry with a sensible value. */
        if (g1 != 0.0)
        {
                GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (widget),
                        "G1_entry");
                gtk_widget_set_sensitive (G1_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (G1_entry),
                        g_strdup_printf ("%f", g1));
        }
        /* Only update the "Z1" entry with a sensible value. */
        if (z1 != 0.0)
        {
                GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (widget),
                        "Z1_entry");
                gtk_widget_set_sensitive (Z1_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (Z1_entry),
                        g_strdup_printf ("%f", z1));
        }
        /* Only update the "C2" entry with a sensible value. */
        if (c2 != 0.0)
        {
                GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (widget),
                        "C2_entry");
                gtk_widget_set_sensitive (C2_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (C2_entry),
                        g_strdup_printf ("%f", c2));
        }
        /* Only update the "G2" entry with a sensible value. */
        if (g2 != 0.0)
        {
                GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (widget),
                        "G2_entry");
                gtk_widget_set_sensitive (G2_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (G2_entry),
                        g_strdup_printf ("%f", g2));
        }
        /* Only update the "Z2" entry with a sensible value. */
        if (z2 != 0.0)
        {
                GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (widget),
                        "Z2_entry");
                gtk_widget_set_sensitive (Z2_entry, TRUE);
                gtk_entry_set_text (GTK_ENTRY (Z2_entry),
                        g_strdup_printf ("%f", z2));
        }
}



/*!
 * \brief Set all entries widgets to default sensitivity.
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Returns:</b> none.
 */
int
all_entries_to_default_sensitivity (GtkWidget *widget)
{
        /* Widgets on tab "Footprint" */
        GtkWidget *footprint_type_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_type_entry");
        gtk_widget_set_sensitive (footprint_type_entry, TRUE);
        GtkWidget *footprint_name_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_name_entry");
        gtk_widget_set_sensitive (footprint_name_entry, TRUE);
        GtkWidget *footprint_units_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_units_entry");
        gtk_widget_set_sensitive (footprint_units_entry, TRUE);
        GtkWidget *footprint_refdes_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_refdes_entry");
        gtk_widget_set_sensitive (footprint_refdes_entry, TRUE);
        GtkWidget *footprint_value_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_value_entry");
        gtk_widget_set_sensitive (footprint_value_entry, TRUE);
        GtkWidget *package_body_length_entry = lookup_widget (GTK_WIDGET (widget),
                "package_body_length_entry");
        gtk_widget_set_sensitive (package_body_length_entry, TRUE);
        GtkWidget *package_body_width_entry = lookup_widget (GTK_WIDGET (widget),
                "package_body_width_entry");
        gtk_widget_set_sensitive (package_body_width_entry, TRUE);
        GtkWidget *package_body_height_entry = lookup_widget (GTK_WIDGET (widget),
                "package_body_height_entry");
        gtk_widget_set_sensitive (package_body_height_entry, TRUE);
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_widget_set_sensitive (package_is_radial_checkbutton, TRUE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), FALSE);
        GtkWidget *footprint_author_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_author_entry");
        gtk_widget_set_sensitive (footprint_author_entry, TRUE);
        GtkWidget *footprint_dist_license_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_dist_license_entry");
        gtk_widget_set_sensitive (footprint_dist_license_entry, TRUE);
        GtkWidget *footprint_use_license_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_use_license_entry");
        gtk_widget_set_sensitive (footprint_use_license_entry, TRUE);
        GtkWidget *footprint_status_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_status_entry");
        gtk_widget_set_sensitive (footprint_status_entry, TRUE);

        /* Widgets on tab Pins/Pads" */
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (widget),
                "number_total_pins_entry");
        gtk_widget_set_sensitive (number_total_pins_entry, TRUE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_widget_set_sensitive (number_of_rows_entry, TRUE);
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_widget_set_sensitive (number_of_columns_entry, TRUE);
        GtkWidget *pitch_x_entry = lookup_widget (GTK_WIDGET (widget),
                "pitch_x_entry");
        gtk_widget_set_sensitive (pitch_x_entry, TRUE);
        GtkWidget *pitch_y_entry = lookup_widget (GTK_WIDGET (widget),
                "pitch_y_entry");
        gtk_widget_set_sensitive (pitch_y_entry, TRUE);
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                "count_x_entry");
        gtk_widget_set_sensitive (count_x_entry, TRUE);
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (widget),
                "count_y_entry");
        gtk_widget_set_sensitive (count_y_entry, TRUE);
        GtkWidget *pad_shape_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_shape_entry");
        gtk_widget_set_sensitive (pad_shape_entry, TRUE);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_widget_set_sensitive (number_1_position_entry, TRUE);
        GtkWidget *pin_pad_exceptions_button = lookup_widget (GTK_WIDGET (widget),
                "pin_pad_exceptions_button");
        gtk_widget_set_sensitive (pin_pad_exceptions_button, FALSE);
        GtkWidget *pad_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_diameter_entry");
        gtk_widget_set_sensitive (pad_diameter_entry, TRUE);
        GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pin_drill_diameter_entry");
        gtk_widget_set_sensitive (pin_drill_diameter_entry, TRUE);
        GtkWidget *pin1_square_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "pin_square_checkbutton");
        gtk_widget_set_sensitive (pin1_square_checkbutton, TRUE);
        GtkWidget *pad_length_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_length_entry");
        gtk_widget_set_sensitive (pad_length_entry, TRUE);
        GtkWidget *pad_width_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_width_entry");
        gtk_widget_set_sensitive (pad_width_entry, TRUE);
        GtkWidget *pad_clearance_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_clearance_entry");
        gtk_widget_set_sensitive (pad_clearance_entry, TRUE);
        GtkWidget *pad_solder_mask_clearance_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_solder_mask_clearance_entry");
        gtk_widget_set_sensitive (pad_solder_mask_clearance_entry, TRUE);

        /* Widgets on tab "Silkscreen" */
        GtkWidget *silkscreen_package_outline_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "silkscreen_package_outline_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (silkscreen_package_outline_checkbutton), FALSE);
        GtkWidget *silkscreen_line_width_entry = lookup_widget (GTK_WIDGET (widget),
                "silkscreen_line_width_entry");
        gtk_widget_set_sensitive (silkscreen_line_width_entry, FALSE);
        GtkWidget *silkscreen_indicate_1_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "silkscreen_indicate_1_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (silkscreen_indicate_1_checkbutton), FALSE);
        GtkWidget *courtyard_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "courtyard_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (courtyard_checkbutton), FALSE);
        GtkWidget *courtyard_length_entry = lookup_widget (GTK_WIDGET (widget),
                "courtyard_length_entry");
        gtk_widget_set_sensitive (courtyard_length_entry, FALSE);
        GtkWidget *courtyard_width_entry = lookup_widget (GTK_WIDGET (widget),
                "courtyard_width_entry");
        gtk_widget_set_sensitive (courtyard_width_entry, FALSE);
        GtkWidget *courtyard_line_width_entry = lookup_widget (GTK_WIDGET (widget),
                "courtyard_line_width_entry");
        gtk_widget_set_sensitive (courtyard_line_width_entry, FALSE);
        GtkWidget *courtyard_clearance_with_package_entry = lookup_widget (GTK_WIDGET (widget),
                "courtyard_clearance_with_package_entry");
        gtk_widget_set_sensitive (courtyard_clearance_with_package_entry, FALSE);

        /* Widgets on tab "Thermal pad" */
        GtkWidget *thermal_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "thermal_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (thermal_checkbutton), FALSE);
        GtkWidget *thermal_nopaste_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "thermal_nopaste_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (thermal_nopaste_checkbutton), FALSE);
        GtkWidget *thermal_length_entry = lookup_widget (GTK_WIDGET (widget),
                "thermal_length_entry");
        gtk_widget_set_sensitive (thermal_length_entry, FALSE);
        GtkWidget *thermal_width_entry = lookup_widget (GTK_WIDGET (widget),
                "thermal_width_entry");
        gtk_widget_set_sensitive (thermal_width_entry, FALSE);
        GtkWidget *thermal_clearance_entry = lookup_widget (GTK_WIDGET (widget),
                "thermal_clearance_entry");
        gtk_widget_set_sensitive (thermal_clearance_entry, FALSE);
        GtkWidget *thermal_solder_mask_clearance_entry = lookup_widget
                (GTK_WIDGET (widget), "thermal_solder_mask_clearance_entry");
        gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, FALSE);
        GtkWidget *fiducial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "fiducial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (fiducial_checkbutton),
                FALSE);
        GtkWidget *fiducial_pad_diameter_entry = lookup_widget (GTK_WIDGET
                (widget), "fiducial_pad_diameter_entry");
        gtk_widget_set_sensitive (fiducial_pad_diameter_entry, FALSE);
        GtkWidget *fiducial_pad_clearance_entry = lookup_widget
                (GTK_WIDGET (widget), "fiducial_pad_clearance_entry");
        gtk_widget_set_sensitive (fiducial_pad_clearance_entry, FALSE);
        GtkWidget *fiducial_pad_solder_mask_clearance_entry = lookup_widget
                (GTK_WIDGET (widget), "fiducial_pad_solder_mask_clearance_entry");
        gtk_widget_set_sensitive (fiducial_pad_solder_mask_clearance_entry, FALSE);

        /* Widgets on tab "Heel & Toe goals" */
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (widget),
                "C1_entry");
        gtk_widget_set_sensitive (C1_entry, TRUE);
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (widget),
                "C2_entry");
        gtk_widget_set_sensitive (C2_entry, TRUE);
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (widget),
                "G1_entry");
        gtk_widget_set_sensitive (G1_entry, FALSE);
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (widget),
                "G2_entry");
        gtk_widget_set_sensitive (G2_entry, FALSE);
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (widget),
                "Z1_entry");
        gtk_widget_set_sensitive (Z1_entry, FALSE);
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (widget),
                "Z2_entry");
        gtk_widget_set_sensitive (Z2_entry, FALSE);
        GtkWidget *C1_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "C1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C1_radiobutton), TRUE);
        gtk_widget_set_sensitive (C1_radiobutton, TRUE);
        GtkWidget *C2_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "C2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C2_radiobutton), TRUE);
        gtk_widget_set_sensitive (C2_radiobutton, TRUE);
        GtkWidget *G1_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "G1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (G1_radiobutton), FALSE);
        gtk_widget_set_sensitive (G1_radiobutton, TRUE);
        GtkWidget *G2_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "G2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (G2_radiobutton), FALSE);
        gtk_widget_set_sensitive (G2_radiobutton, TRUE);
        GtkWidget *Z1_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "Z1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (Z1_radiobutton), FALSE);
        gtk_widget_set_sensitive (Z1_radiobutton, TRUE);
        GtkWidget *Z2_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "Z2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (Z2_radiobutton), FALSE);
        gtk_widget_set_sensitive (Z2_radiobutton, TRUE);
}


/*!
 * \brief Change the main window title.
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c *main_window_title is the string containing
 * the new title.\n
 * \n
 * <b>Returns:</b> none.
 */
int
change_main_window_title (GtkWidget *widget, gchar *main_window_title)
{
        /* lookup the window */
        GtkWidget *main_window;
        main_window = lookup_widget (GTK_WIDGET (widget), "pcb_gfpw");
        gtk_window_set_title (GTK_WINDOW (main_window), main_window_title);
}


/*!
 * \brief The value in one of the entries in the GUI has changed.
 *
 * Add an asterix between brackets [*] before the current window title.\n
 * \n
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Returns:</b> none.
 */
int
entry_has_changed (GtkWidget *widget)
{
        if (!main_window_title_has_asterisk)
        {
                /* lookup the window */
                GtkWidget *main_window;
                main_window = lookup_widget (GTK_WIDGET (widget), "pcb_gfpw");
                /* get the current title */
                const gchar* main_window_title = gtk_window_get_title (GTK_WINDOW (main_window));
                if (!fpw_file_saved)
                {
                        /* fpw file has not been saved before */
                        change_main_window_title (GTK_WIDGET (main_window),
                                g_strconcat (_("pcb-gfpw : Unsaved fpw file"),
                                NULL));
                }
                else
                {
                        /* fpw file has been saved before, assume the fpw
                         * filename is already listed in the main window
                         * title, add an asterix between brackets [*] before
                         * the current window title */
                        change_main_window_title (GTK_WIDGET (main_window),
                                g_strconcat ("[*] ",
                                main_window_title, NULL));
                        main_window_title_has_asterisk = TRUE;
                }
        }
}


/*!
 * \brief Set GUI constraints: disable the entries in the
 * "Heel and Toe goals" tab.
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Returns:</b> none.
 */
int
gui_constraints_disable_heel_and_toe_goals_tab_widgets (GtkWidget *widget)
{
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (widget),
                "C1_entry");
        gtk_entry_set_text (GTK_ENTRY (C1_entry), "");
        gtk_widget_set_sensitive (C1_entry, FALSE);
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (widget),
                "C2_entry");
        gtk_entry_set_text (GTK_ENTRY (C2_entry), "");
        gtk_widget_set_sensitive (C2_entry, FALSE);
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (widget),
                "G1_entry");
        gtk_entry_set_text (GTK_ENTRY (G1_entry), "");
        gtk_widget_set_sensitive (G1_entry, FALSE);
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (widget),
                "G2_entry");
        gtk_entry_set_text (GTK_ENTRY (G2_entry), "");
        gtk_widget_set_sensitive (G2_entry, FALSE);
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (widget),
                "Z1_entry");
        gtk_entry_set_text (GTK_ENTRY (Z1_entry), "");
        gtk_widget_set_sensitive (Z1_entry, FALSE);
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (widget),
                "Z2_entry");
        gtk_entry_set_text (GTK_ENTRY (Z2_entry), "");
        gtk_widget_set_sensitive (Z2_entry, FALSE);
        GtkWidget * C1_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "C1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C1_radiobutton), TRUE);
        gtk_widget_set_sensitive (C1_radiobutton, FALSE);
        GtkWidget * C2_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "C2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C2_radiobutton), TRUE);
        gtk_widget_set_sensitive (C2_radiobutton, FALSE);
        GtkWidget * G1_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "G1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (G1_radiobutton), FALSE);
        gtk_widget_set_sensitive (G1_radiobutton, FALSE);
        GtkWidget * G2_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "G2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (G2_radiobutton), FALSE);
        gtk_widget_set_sensitive (G2_radiobutton, FALSE);
        GtkWidget * Z1_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "Z1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (Z1_radiobutton), FALSE);
        gtk_widget_set_sensitive (Z1_radiobutton, FALSE);
        GtkWidget * Z2_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "Z2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (Z2_radiobutton), FALSE);
        gtk_widget_set_sensitive (Z2_radiobutton, FALSE);
}


/*!
 * \brief Set GUI constraints: disable the entries in the
 * "Thermal Pad" tab.
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Returns:</b> none.
 */
int
gui_constraints_disable_thermal_tab_widgets (GtkWidget *widget)
{
        GtkWidget *thermal_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "thermal_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (thermal_checkbutton),
                FALSE);
        gtk_widget_set_sensitive (thermal_checkbutton, FALSE);
        GtkWidget *thermal_nopaste_checkbutton = lookup_widget
                (GTK_WIDGET (widget), "thermal_nopaste_checkbutton");
        gtk_widget_set_sensitive (GTK_WIDGET (thermal_nopaste_checkbutton),
                FALSE);
        GtkWidget *thermal_length_entry = lookup_widget (GTK_WIDGET (widget),
                "thermal_length_entry");
        gtk_widget_set_sensitive (thermal_length_entry, FALSE);
        GtkWidget *thermal_width_entry = lookup_widget (GTK_WIDGET (widget),
                "thermal_width_entry");
        gtk_widget_set_sensitive (thermal_width_entry, FALSE);
        GtkWidget *thermal_clearance_entry = lookup_widget (GTK_WIDGET
                (widget), "thermal_clearance_entry");
        gtk_widget_set_sensitive (thermal_clearance_entry, FALSE);
        GtkWidget *thermal_solder_mask_clearance_entry = lookup_widget
                (GTK_WIDGET (widget), "thermal_solder_mask_clearance_entry");
        gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, FALSE);
        GtkWidget *fiducial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "fiducial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (fiducial_checkbutton),
                FALSE);
        gtk_widget_set_sensitive (fiducial_checkbutton, FALSE);
        GtkWidget *fiducial_pad_diameter_entry = lookup_widget
                (GTK_WIDGET (widget),
                "fiducial_pad_diameter_entry");
        gtk_widget_set_sensitive (fiducial_pad_diameter_entry, FALSE);
        GtkWidget *fiducial_pad_clearance_entry = lookup_widget
                (GTK_WIDGET (widget),
                "fiducial_pad_clearance_entry");
        gtk_widget_set_sensitive (fiducial_pad_clearance_entry,
                FALSE);
        GtkWidget *fiducial_pad_solder_mask_clearance_entry = lookup_widget
                (GTK_WIDGET (widget),
                "fiducial_pad_solder_mask_clearance_entry");
        gtk_widget_set_sensitive (fiducial_pad_solder_mask_clearance_entry,
                FALSE);
}


/*!
 * \brief Set GUI constraints for SMT package types.
 *
 * The following types are applicable: \n
 * CAPC, CAPM, CAPMP, DIOM, DIOMELF, INDC, INDM, INDP, RESC, RESM and RESMELF.
 * \n
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Returns:</b> none.
 */
int
gui_constraints_set_smt (GtkWidget *widget)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_columns_entry), "");
        gtk_widget_set_sensitive (number_of_columns_entry, FALSE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_rows_entry), "");
        gtk_widget_set_sensitive (number_of_rows_entry, FALSE);
        GtkWidget *pitch_y_entry = lookup_widget (GTK_WIDGET (widget),
                "pitch_y_entry");
        gtk_entry_set_text (GTK_ENTRY (pitch_y_entry), "");
        gtk_widget_set_sensitive (pitch_y_entry, FALSE);
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                "count_x_entry");
        gtk_entry_set_text (GTK_ENTRY (count_x_entry), "");
        gtk_widget_set_sensitive (count_x_entry, FALSE);
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (widget),
                "count_y_entry");
        gtk_entry_set_text (GTK_ENTRY (count_y_entry), "");
        gtk_widget_set_sensitive (count_y_entry, FALSE);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (number_1_position_entry), 1);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);
        GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pin_drill_diameter_entry");
        gtk_entry_set_text (GTK_ENTRY (pin_drill_diameter_entry), "");
        gtk_widget_set_sensitive (pin_drill_diameter_entry, FALSE);
        GtkWidget *pad_shape_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_shape_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (pad_shape_entry), 2);

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}


/*!
 * \brief Set GUI constraints for the TO92 package type.
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Returns:</b> none.
 */
int
gui_constraints_set_to92 (GtkWidget *widget)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), TRUE);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_columns_entry), "");
        gtk_widget_set_sensitive (number_of_columns_entry, FALSE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_rows_entry), "");
        gtk_widget_set_sensitive (number_of_rows_entry, FALSE);
        GtkWidget *pitch_x_entry = lookup_widget (GTK_WIDGET (widget),
                "pitch_x_entry");
        gtk_entry_set_text (GTK_ENTRY (pitch_x_entry), "");
        gtk_widget_set_sensitive (pitch_x_entry, FALSE);
        GtkWidget *pitch_y_entry = lookup_widget (GTK_WIDGET (widget),
                "pitch_y_entry");
        gtk_entry_set_text (GTK_ENTRY (pitch_y_entry), "");
        gtk_widget_set_sensitive (pitch_y_entry, FALSE);
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                "count_x_entry");
        gtk_entry_set_text (GTK_ENTRY (count_x_entry), "");
        gtk_widget_set_sensitive (count_x_entry, FALSE);
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (widget),
                "count_y_entry");
        gtk_entry_set_text (GTK_ENTRY (count_y_entry), "");
        gtk_widget_set_sensitive (count_y_entry, FALSE);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (number_1_position_entry), 1);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}


/*!
 * \brief Send a message to the statusbar.
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c *message is the string containing the new
 * message for  the statusbar.\n
 * \n
 * <b>Returns:</b> none.
 */
int
message_to_statusbar (GtkWidget *widget, gchar *message)
{
        /* lookup the statusbar */
        GtkStatusbar *statusbar = GTK_STATUSBAR (lookup_widget (GTK_WIDGET (widget),
                "statusbar"));
        guint context_id;
        guint message_id;
        context_id = gtk_statusbar_get_context_id (statusbar, message);
        message_id = gtk_statusbar_push (statusbar, context_id, message);
}


/*!
 * \brief Update the value in the "number_total_pins" entry.
 *
 * This function is to be called on one of the following events:
 * <ul>
 * <li>Number of columns entry is changed: \c number_of_columns changes.
 * <li>Number of rows entry is changed: \c number_of_rows changes.
 * <li>Count of pin/pads (on a row) in the X-direction entry is changed: \c count_x changes.
 * <li>Count of pin/pads (on a column) in the Y-direction entry is changed: \c count_y changes.
 * <li>The thermal pad button is toggled: \c thermal changes.
 * </ul>
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Returns:</b> none.
 */
int
number_of_pins_has_changed (GtkWidget *widget)
{
        /* Recalculate the total number of pins/pads depending on the package
         * type */
        switch (package_type)
        {
                case BGA :
                        number_of_pins = (number_of_columns * number_of_rows) - number_of_exceptions;
                        break;
                case CAPC :
                        number_of_pins = 2;
                        break;
                case CAPM :
                        number_of_pins = 2;
                        break;
                case CAPMP :
                        number_of_pins = 2;
                        break;
                case CON_DIL :
                        number_of_pins = number_of_rows * count_x;
                        break;
                case CON_DIP :
                        number_of_pins = number_of_columns * number_of_rows;
                        break;
                case CON_HDR :
                        number_of_pins = number_of_rows * count_x;
                        break;
                case CON_SIL :
                        number_of_pins = number_of_rows;
                        break;
                case DIL :
                        number_of_pins = number_of_columns * number_of_rows;
                        break;
                case DIOM :
                        number_of_pins = 2;
                        break;
                case DIOMELF :
                        number_of_pins = 2;
                        break;
                case DIP :
                        number_of_pins = number_of_columns * count_y;
                        break;
                case INDC :
                        number_of_pins = 2;
                        break;
                case INDM :
                        number_of_pins = 2;
                        break;
                case INDP :
                        number_of_pins = 2;
                        break;
                case PGA :
                        number_of_pins = (number_of_columns * number_of_rows) - number_of_exceptions;
                        break;
                case PLCC :
                        number_of_pins = (number_of_columns * count_x +
                                number_of_rows * count_y) + thermal;
                        break;
                case QFN :
                        number_of_pins = (number_of_columns * count_x +
                                number_of_rows * count_y) + thermal;
                        break;
                case QFP :
                        number_of_pins = (number_of_columns * count_x +
                                number_of_rows * count_y) + thermal;
                        break;
                case RESC :
                        number_of_pins = 2;
                        break;
                case RESM :
                        number_of_pins = 2;
                        break;
                case RESMELF :
                        number_of_pins = 2;
                        break;
                case SIL :
                        number_of_pins = number_of_rows;
                        break;
                case SIP :
                        number_of_pins = number_of_rows;
                        break;
                case SO :
                        break;
                case SOT :
                        break;
                case TO92 :
                        number_of_pins = 3;
                        break;
                default :
                        break;
        }
        /* Update the "total number of pins/pads" entry */
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (widget),
                "number_total_pins_entry");
        gtk_entry_set_text (GTK_ENTRY (number_total_pins_entry),
                g_strdup_printf ("%d", number_of_pins));
}


/*!
 * \brief The "top to bottom pads/pins center-center distance (C1)" entry is
 * changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c c1 variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_C1_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (editable),
                "C1_entry");
        const gchar* C1_string = gtk_entry_get_text (GTK_ENTRY (C1_entry));
        c1 = g_ascii_strtod (C1_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "top to bottom pads/pins center-center distance (C1)"
 * radiobutton is clicked.
 *
 * <ul>
 * <li>set the "center-center distance (C1)" entry to sensitive.
 * <li>set the "inner-inner distance (G1)" entry to insensitive.
 * <li>set the "outer-outer distance (Z1)" entry to insensitive.
 * </ul>
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_C1_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        c1_state = gtk_toggle_button_get_active (togglebutton);
        g1_state = !c1_state;
        z1_state = !c1_state;
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (togglebutton), "C1_entry");
        gtk_widget_set_sensitive (C1_entry, TRUE);
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (togglebutton), "G1_entry");
        gtk_widget_set_sensitive (G1_entry, FALSE);
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z1_entry");
        gtk_widget_set_sensitive (Z1_entry, FALSE);
}


/*!
 * \brief The "left to right pads/pins center-center distance (C2)" entry is
 * changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c c2 variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_C2_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (editable),
                "C2_entry");
        const gchar* C2_string = gtk_entry_get_text (GTK_ENTRY (C2_entry));
        c2 = g_ascii_strtod (C2_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "left to right pads/pins center-center distance (C2)"
 * radiobutton is clicked.
 *
 * <ul>
 * <li>set the "center-center distance (C2)" entry to sensitive.
 * <li>set the "inner-inner distance (G2)" entry to insensitive.
 * <li>set the "outer-outer distance (Z2)" entry to insensitive.
 * </ul>
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_C2_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        c2_state = gtk_toggle_button_get_active (togglebutton);
        g2_state = !c2_state;
        z2_state = !c2_state;
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (togglebutton), "C2_entry");
        gtk_widget_set_sensitive (C2_entry, TRUE);
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (togglebutton), "G2_entry");
        gtk_widget_set_sensitive (G2_entry, FALSE);
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z2_entry");
        gtk_widget_set_sensitive (Z2_entry, FALSE);
}


/*!
 * \brief The top to bottom pads/pins inner-inner distance (G1) entry is
 * changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c g1 variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_G1_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (editable),
                "G1_entry");
        const gchar* G1_string = gtk_entry_get_text (GTK_ENTRY (G1_entry));
        g1 = g_ascii_strtod (G1_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The top to bottom pads/pins inner-inner distance (G1) radiobutton
 * is clicked.
 *
 * <ul>
 * <li>set the inner-inner (G1) entry to sensitive.
 * <li>set the center-center (C1) entry to insensitive.
 * <li>set the outer-outer (Z1) entry to insensitive.
 * </ul>
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_G1_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        g1_state = gtk_toggle_button_get_active (togglebutton);
        c1_state = !g1_state;
        z1_state = !g1_state;
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (togglebutton), "C1_entry");
        gtk_widget_set_sensitive (C1_entry, FALSE);
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (togglebutton), "G1_entry");
        gtk_widget_set_sensitive (G1_entry, TRUE);
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z1_entry");
        gtk_widget_set_sensitive (Z1_entry, FALSE);
}


/*!
 * \brief The left to right pads/pins inner-inner distance (G2) entry is
 * changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c g2 variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_G2_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (editable),
                "G2_entry");
        const gchar* G2_string = gtk_entry_get_text (GTK_ENTRY (G2_entry));
        g2 = g_ascii_strtod (G2_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The left to right pads/pins inner-inner distance (G2) radiobutton
 * is clicked.
 *
 * <ul>
 * <li>set the inner-inner (G2) entry to sensitive.
 * <li>set the center-centr (C2) entry to insensitive.
 * <li>set the outer-outer (Z2) entry to insensitive.
 * </ul>
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_G2_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        g2_state = gtk_toggle_button_get_active (togglebutton);
        c2_state = !g2_state;
        z2_state = !g2_state;
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (togglebutton), "C2_entry");
        gtk_widget_set_sensitive (C2_entry, FALSE);
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (togglebutton), "G2_entry");
        gtk_widget_set_sensitive (G2_entry, TRUE);
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z2_entry");
        gtk_widget_set_sensitive (Z2_entry, FALSE);
}


/*!
 * \brief The top to bottom pads/pins outer-outer distance (Z1) entry is
 * changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c z1 variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_Z1_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (editable),
                "Z1_entry");
        const gchar* Z1_string = gtk_entry_get_text (GTK_ENTRY (Z1_entry));
        z1 = g_ascii_strtod (Z1_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The top to bottom pads/pins outer-outer (Z1) radiobutton
 * is clicked.
 *
 * <ul>
 * <li>set the outer-outer (Z1) entry to sensitive.
 * <li>set the center-center (C1) entry to insensitive.
 * <li>set the inner-inner (G1) entry to insensitive.
 * </ul>
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_Z1_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        z1_state = gtk_toggle_button_get_active (togglebutton);
        c1_state = !z1_state;
        g1_state = !z1_state;
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (togglebutton), "C1_entry");
        gtk_widget_set_sensitive (C1_entry, FALSE);
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (togglebutton), "G1_entry");
        gtk_widget_set_sensitive (G1_entry, FALSE);
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z1_entry");
        gtk_widget_set_sensitive (Z1_entry, TRUE);
}


/*!
 * \brief The left to right pads/pins outer-outer distance (Z2) entry is
 * changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c z2 variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_Z2_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (editable),
                "Z2_entry");
        const gchar* Z2_string = gtk_entry_get_text (GTK_ENTRY (Z2_entry));
        z2 = g_ascii_strtod (Z2_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The left to right pads/pins outer-outer (Z2) radiobutton
 * is clicked.
 *
 * <ul>
 * <li>set the "outer-outer distance (Z2)" entry to sensitive.
 * <li>set the "center-center distance (C2)" entry to insensitive.
 * <li>set the "inner-inner distance (G2)" entry to insensitive.
 * </ul>
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_Z2_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        z2_state = gtk_toggle_button_get_active (togglebutton);
        c2_state = !z2_state;
        g2_state = !z2_state;
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (togglebutton), "C2_entry");
        gtk_widget_set_sensitive (C2_entry, FALSE);
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (togglebutton), "G2_entry");
        gtk_widget_set_sensitive (G2_entry, FALSE);
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z2_entry");
        gtk_widget_set_sensitive (Z2_entry, TRUE);
}


/*!
 * \brief The close button of the about dialog is clicked.
 *
 * <b>Parameters:</b> \c *dialog is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_about_dialog_close                  (GtkDialog       *dialog,
                                        gpointer         user_data)
{
        GtkWidget *about_dialog = lookup_widget (GTK_WIDGET (dialog),
                "about_dialog");
        gtk_widget_destroy (about_dialog);
}


/*!
 * \brief The destroy button of the about dialog is clicked.
 *
 * <b>Parameters:</b> \c *object is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_about_dialog_destroy                (GtkObject       *object,
                                        gpointer         user_data)
{
        GtkWidget *about_dialog = lookup_widget (GTK_WIDGET (object),
                "about_dialog");
        gtk_widget_destroy (about_dialog);
}


/*!
 * \brief The "add attributes to footprint" checkbutton is toggled.
 *
 * <ul>
 * <li>get active state.
 * <li>store in the \c attributes_in_footprint variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_add_attribs_checkbutton_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        attributes_in_footprint = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
}


/*!
 * \brief The "add a license text to footprint" checkbutton is toggled.
 *
 * <ul>
 * <li>get active state.
 * <li>store in the \c license_in_footprint variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_add_license_checkbutton_toggled     (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        license_in_footprint = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
}


/*!
 * \brief The "Clear" button is clicked.
 *
 * <ul>
 * <li>clear all entries or set entries which have a default values to that
 *   value,
 * <li>set all togglebuttons to the initial state.
 * </ul>
 *
 * \todo Combobox entries to be stripped of characters with something like
 * gtk_combo_box_remove_text ().
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_clear_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
        entry_has_changed (GTK_WIDGET (button));
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *footprint_type_entry = lookup_widget (GTK_WIDGET (button),
                "footprint_type_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (footprint_type_entry), 0);
        GtkWidget *footprint_name_entry = lookup_widget (GTK_WIDGET (button),
                "footprint_name_entry");
        gtk_entry_set_text (GTK_ENTRY (footprint_name_entry), "");
        GtkWidget *footprint_units_entry = lookup_widget (GTK_WIDGET (button),
                "footprint_units_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (footprint_units_entry), 0);
        GtkWidget *footprint_refdes_entry = lookup_widget (GTK_WIDGET (button),
                "footprint_refdes_entry");
        gtk_entry_set_text (GTK_ENTRY (footprint_refdes_entry), "");
        GtkWidget *footprint_value_entry = lookup_widget (GTK_WIDGET (button),
                "footprint_value_entry");
        gtk_entry_set_text (GTK_ENTRY (footprint_value_entry), "");
        GtkWidget *package_body_length_entry = lookup_widget (GTK_WIDGET (button),
                "package_body_length_entry");
        gtk_entry_set_text (GTK_ENTRY (package_body_length_entry), "");
        GtkWidget *package_body_width_entry = lookup_widget (GTK_WIDGET (button),
                "package_body_width_entry");
        gtk_entry_set_text (GTK_ENTRY (package_body_width_entry), "");
        GtkWidget *package_body_height_entry = lookup_widget (GTK_WIDGET (button),
                "package_body_height_entry");
        gtk_entry_set_text (GTK_ENTRY (package_body_height_entry), "");
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (button),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), FALSE);
        GtkWidget *footprint_author_entry = lookup_widget (GTK_WIDGET (button),
                "footprint_author_entry");
        gtk_entry_set_text (GTK_ENTRY (footprint_author_entry), "");
        GtkWidget *footprint_dist_license_entry = lookup_widget (GTK_WIDGET (button),
                "footprint_dist_license_entry");
        gtk_entry_set_text (GTK_ENTRY (footprint_dist_license_entry), "");
        GtkWidget *footprint_use_license_entry = lookup_widget (GTK_WIDGET (button),
                "footprint_use_license_entry");
        gtk_entry_set_text (GTK_ENTRY (footprint_use_license_entry), "");
        GtkWidget *footprint_status_entry = lookup_widget (GTK_WIDGET (button),
                "footprint_status_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (footprint_status_entry), 0);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (button),
                "number_total_pins_entry");
        gtk_entry_set_text (GTK_ENTRY (number_total_pins_entry), "");
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (button),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_rows_entry), "");
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (button),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_columns_entry), "");
        GtkWidget *pitch_x_entry = lookup_widget (GTK_WIDGET (button),
                "pitch_x_entry");
        gtk_entry_set_text (GTK_ENTRY (pitch_x_entry), "");
        GtkWidget *pitch_y_entry = lookup_widget (GTK_WIDGET (button),
                "pitch_y_entry");
        gtk_entry_set_text (GTK_ENTRY (pitch_y_entry), "");
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (button),
                "count_x_entry");
        gtk_entry_set_text (GTK_ENTRY (count_x_entry), "");
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (button),
                "count_y_entry");
        gtk_entry_set_text (GTK_ENTRY (count_y_entry), "");
        GtkWidget *pad_shape_entry = lookup_widget (GTK_WIDGET (button),
                "pad_shape_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (pad_shape_entry), 0);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (button),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (number_1_position_entry), 0);
        GtkWidget *pad_diameter_entry = lookup_widget (GTK_WIDGET (button),
                "pad_diameter_entry");
        gtk_entry_set_text (GTK_ENTRY (pad_diameter_entry), "");
        GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_WIDGET (button),
                "pin_drill_diameter_entry");
        gtk_entry_set_text (GTK_ENTRY (pin_drill_diameter_entry), "");
        GtkWidget *pin1_square_checkbutton = lookup_widget (GTK_WIDGET (button),
                "pin_square_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (pin1_square_checkbutton), FALSE);
        GtkWidget *pad_length_entry = lookup_widget (GTK_WIDGET (button),
                "pad_length_entry");
        gtk_entry_set_text (GTK_ENTRY (pad_length_entry), "");
        GtkWidget *pad_width_entry = lookup_widget (GTK_WIDGET (button),
                "pad_width_entry");
        gtk_entry_set_text (GTK_ENTRY (pad_width_entry), "");
        GtkWidget *pad_clearance_entry = lookup_widget (GTK_WIDGET (button),
                "pad_clearance_entry");
        gtk_entry_set_text (GTK_ENTRY (pad_clearance_entry), "");
        GtkWidget *pad_solder_mask_clearance_entry = lookup_widget (GTK_WIDGET (button),
                "pad_solder_mask_clearance_entry");
        gtk_entry_set_text (GTK_ENTRY (pad_solder_mask_clearance_entry), "");

        /* Widgets on tab 3 "Thermal Pad" */
        GtkWidget *thermal_checkbutton = lookup_widget (GTK_WIDGET (button),
                "thermal_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (thermal_checkbutton), FALSE);
        GtkWidget *thermal_nopaste_checkbutton = lookup_widget (GTK_WIDGET (button),
                "thermal_nopaste_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (thermal_nopaste_checkbutton), FALSE);
        GtkWidget *thermal_length_entry = lookup_widget (GTK_WIDGET (button),
                "thermal_length_entry");
        gtk_entry_set_text (GTK_ENTRY (thermal_length_entry), "");
        gtk_widget_set_sensitive (thermal_length_entry, FALSE);
        GtkWidget *thermal_width_entry = lookup_widget (GTK_WIDGET (button),
                "thermal_width_entry");
        gtk_entry_set_text (GTK_ENTRY (thermal_width_entry), "");
        gtk_widget_set_sensitive (thermal_width_entry, FALSE);
        GtkWidget *thermal_clearance_entry = lookup_widget (GTK_WIDGET (button),
                "thermal_clearance_entry");
        gtk_entry_set_text (GTK_ENTRY (thermal_clearance_entry), "");
        gtk_widget_set_sensitive (thermal_clearance_entry, FALSE);
        GtkWidget *thermal_solder_mask_clearance_entry = lookup_widget (GTK_WIDGET (button),
                "thermal_solder_mask_clearance_entry");
        gtk_entry_set_text (GTK_ENTRY (thermal_solder_mask_clearance_entry), "");
        gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, FALSE);

        /* Widgets on tab 4 "Silkscreen" */
        GtkWidget *silkscreen_package_outline_checkbutton = lookup_widget (GTK_WIDGET (button),
                "silkscreen_package_outline_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (silkscreen_package_outline_checkbutton), FALSE);
        GtkWidget *silkscreen_line_width_entry = lookup_widget (GTK_WIDGET (button),
                "silkscreen_line_width_entry");
        gtk_entry_set_text (GTK_ENTRY (silkscreen_line_width_entry), "");
        GtkWidget *silkscreen_indicate_1_checkbutton = lookup_widget (GTK_WIDGET (button),
                "silkscreen_indicate_1_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (silkscreen_indicate_1_checkbutton), FALSE);
        GtkWidget *courtyard_checkbutton = lookup_widget (GTK_WIDGET (button),
                "courtyard_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (courtyard_checkbutton), FALSE);
        GtkWidget *courtyard_length_entry = lookup_widget (GTK_WIDGET (button),
                "courtyard_length_entry");
        gtk_entry_set_text (GTK_ENTRY (courtyard_length_entry), "");
        GtkWidget *courtyard_width_entry = lookup_widget (GTK_WIDGET (button),
                "courtyard_width_entry");
        gtk_entry_set_text (GTK_ENTRY (courtyard_width_entry), "");
        GtkWidget *courtyard_line_width_entry = lookup_widget (GTK_WIDGET (button),
                "courtyard_line_width_entry");
        gtk_entry_set_text (GTK_ENTRY (courtyard_line_width_entry), "");
        GtkWidget *courtyard_clearance_with_package_entry = lookup_widget (GTK_WIDGET (button),
                "courtyard_clearance_with_package_entry");
        gtk_entry_set_text (GTK_ENTRY (courtyard_clearance_with_package_entry), "");

        /* Widgets on tab 5 "Heel & Toe goals" */
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (button),
                "C1_entry");
        gtk_entry_set_text (GTK_ENTRY (C1_entry), "");
        gtk_widget_set_sensitive (C1_entry, TRUE);
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (button),
                "C2_entry");
        gtk_entry_set_text (GTK_ENTRY (C2_entry), "");
        gtk_widget_set_sensitive (C2_entry, TRUE);
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (button),
                "G1_entry");
        gtk_entry_set_text (GTK_ENTRY (G1_entry), "");
        gtk_widget_set_sensitive (G1_entry, FALSE);
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (button),
                "G2_entry");
        gtk_entry_set_text (GTK_ENTRY (G2_entry), "");
        gtk_widget_set_sensitive (G2_entry, FALSE);
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (button),
                "Z1_entry");
        gtk_entry_set_text (GTK_ENTRY (Z1_entry), "");
        gtk_widget_set_sensitive (Z1_entry, FALSE);
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (button),
                "Z2_entry");
        gtk_entry_set_text (GTK_ENTRY (Z2_entry), "");
        gtk_widget_set_sensitive (Z2_entry, FALSE);
        GtkWidget *C1_radiobutton = lookup_widget (GTK_WIDGET (button),
                "C1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C1_radiobutton), TRUE);
        GtkWidget *C2_radiobutton = lookup_widget (GTK_WIDGET (button),
                "C2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C2_radiobutton), TRUE);
        GtkWidget *G1_radiobutton = lookup_widget (GTK_WIDGET (button),
                "G1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (G1_radiobutton), FALSE);
        GtkWidget *G2_radiobutton = lookup_widget (GTK_WIDGET (button),
                "G2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (G2_radiobutton), FALSE);
        GtkWidget *Z1_radiobutton = lookup_widget (GTK_WIDGET (button),
                "Z1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (Z1_radiobutton), FALSE);
        GtkWidget *Z2_radiobutton = lookup_widget (GTK_WIDGET (button),
                "Z2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (Z2_radiobutton), FALSE);
}


/*!
 * \brief The "Close" button is clicked.
 *
 * Close the application.
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_close_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
        gtk_main_quit();
}


/*!
 * \brief The "Count X-direction" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to an integer and store in the \c count_x variable
 *   (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_count_x_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (editable),
                "count_x_entry");
        const gchar* count_x_string = gtk_entry_get_text (GTK_ENTRY (count_x_entry));
        count_x = (int) g_ascii_strtod (count_x_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
        number_of_pins_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "Count Y-direction" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to an integer and store in the \c count_y variable
 *   (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_count_y_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (editable),
                "count_y_entry");
        const gchar* count_y_string = gtk_entry_get_text (GTK_ENTRY (count_y_entry));
        count_y = (int) g_ascii_strtod (count_y_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
        number_of_pins_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "courtyard" checkbutton is toggled.
 *
 * <ul>
 * <li>get active state.
 * <li>store in the \c courtyard variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_courtyard_checkbutton_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        courtyard = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        GtkWidget *courtyard_line_width_entry = lookup_widget (GTK_WIDGET (togglebutton),
                "courtyard_line_width_entry");
        gtk_widget_set_sensitive (courtyard_line_width_entry, courtyard);
        GtkWidget *courtyard_length_entry = lookup_widget (GTK_WIDGET (togglebutton),
                "courtyard_length_entry");
        gtk_widget_set_sensitive (courtyard_length_entry, courtyard);
        GtkWidget *courtyard_width_entry = lookup_widget (GTK_WIDGET (togglebutton),
                "courtyard_width_entry");
        gtk_widget_set_sensitive (courtyard_width_entry, courtyard);
        GtkWidget *courtyard_clearance_with_package_entry = lookup_widget (GTK_WIDGET (togglebutton),
                "courtyard_clearance_with_package_entry");
        gtk_widget_set_sensitive (courtyard_clearance_with_package_entry, courtyard);
        entry_has_changed (GTK_WIDGET (togglebutton));
}


/*!
 * \brief The "courtyard clearance with package" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c courtyard_clearance_with_package
 *   variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_courtyard_clearance_with_package_entry_changed
                                        (GtkEditable     *editable,
                                         gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *courtyard_clearance_with_package_entry = lookup_widget (GTK_WIDGET (editable),
                "courtyard_clearance_with_package_entry");
        const gchar* courtyard_clearance_with_package_string = gtk_entry_get_text (GTK_ENTRY (courtyard_clearance_with_package_entry));
        courtyard_clearance_with_package = g_ascii_strtod (courtyard_clearance_with_package_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "length of the courtyard (X)" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c courtyard_length variable
 *   (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_courtyard_length_entry_changed      (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *courtyard_length_entry = lookup_widget (GTK_WIDGET (editable),
                "courtyard_length_entry");
        const gchar* courtyard_length_string = gtk_entry_get_text (GTK_ENTRY (courtyard_length_entry));
        courtyard_length = g_ascii_strtod (courtyard_length_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "courtyard line width" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c courtyard_line_width
 *   variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_courtyard_line_width_entry_changed  (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *courtyard_line_width_entry = lookup_widget (GTK_WIDGET (editable),
                "courtyard_line_width_entry");
        const gchar* courtyard_line_width_string = gtk_entry_get_text (GTK_ENTRY (courtyard_line_width_entry));
        courtyard_line_width = g_ascii_strtod (courtyard_line_width_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "width of the courtyard (Y)" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c courtyard_width variable
 *   (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_courtyard_width_entry_changed       (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *courtyard_width_entry = lookup_widget (GTK_WIDGET (editable),
                "courtyard_width_entry");
        const gchar* courtyard_width_string = gtk_entry_get_text (GTK_ENTRY (courtyard_width_entry));
        courtyard_width = g_ascii_strtod (courtyard_width_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "Dimensions" button is clicked.
 *
 * Create a window with a pixmap of the dimensions of the current
 * footprint type (based on the value in the entry widget).
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_dimensions_button_clicked           (GtkButton       *button,
                                        gpointer         user_data)
{
        gchar *image_filename = g_strconcat
        (
                "pixmaps/", footprint_type, ".xpm", NULL
        );
        if (g_file_test (image_filename, G_FILE_TEST_EXISTS))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_INFO,
                                g_strdup_printf (_("loading image file: %s"),
                                image_filename));
                dimensions_create_window (image_filename, footprint_type);
        }
        else
        {
                if (verbose)
                g_log ("", G_LOG_LEVEL_WARNING,
                        g_strdup_printf (_("image file: %s does not exist."), image_filename));
        }
        g_free (image_filename);
}


/*!
 * \brief The "fiducial" checkbutton is toggled.
 *
 * <ul>
 * <li>get active state.
 * <li>store in the \c fiducial variable (global).
 * <li>set pad diameter and pad solder mask clearance entries to the
 *   corresponding sensitive state.
 * <li>set fpw entries have changed marker.
 * </ul>
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_fiducial_checkbutton_toggled        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        fiducial = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        GtkWidget *fiducial_pad_diameter_entry = lookup_widget (GTK_WIDGET (togglebutton),
                "fiducial_pad_diameter_entry");
        gtk_widget_set_sensitive (fiducial_pad_diameter_entry, fiducial);
        GtkWidget *fiducial_pad_soldermask_clearance_entry = lookup_widget
                (GTK_WIDGET (togglebutton),
                "fiducial_pad_solder_mask_clearance_entry");
        gtk_widget_set_sensitive (fiducial_pad_soldermask_clearance_entry, fiducial);
        entry_has_changed (GTK_WIDGET (togglebutton));
}


/*!
 * \brief The "fiducial pad clearance" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the
 *   \c fiducial_pad_clearance variable (global).
 * <li>set the fpw entries have changed marker "[*]" in the title bar.
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_fiducial_pad_clearance_entry_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *fiducial_pad_clearance_entry = lookup_widget (GTK_WIDGET (editable),
                "fiducial_pad_clearance_entry");
        const gchar* fiducial_pad_clearance_string =
                gtk_entry_get_text (GTK_ENTRY (fiducial_pad_clearance_entry));
        fiducial_pad_clearance = g_ascii_strtod (fiducial_pad_clearance_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));

}


/*!
 * \brief The "fiducial pad diameter (D)" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c fiducial_pad_diameter
 *   variable (global).
 * <li>set fpw entries have changed marker.
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_fiducial_pad_diameter_entry_changed (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *fiducial_pad_diameter_entry = lookup_widget (GTK_WIDGET (editable),
                "fiducial_pad_diameter_entry");
        const gchar* fiducial_pad_diameter_string =
                gtk_entry_get_text (GTK_ENTRY (fiducial_pad_diameter_entry));
        fiducial_pad_diameter = g_ascii_strtod (fiducial_pad_diameter_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "fiducial pad solder mask clearance" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the
 *   \c fiducial_pad_solder_mask_clearance variable (global).
 * <li>set fpw entries have changed marker.
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_fiducial_pad_solder_mask_clearance_entry_changed
                                        (GtkEditable     *editable,
                                         gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *fiducial_pad_solder_mask_clearance_entry =
                lookup_widget (GTK_WIDGET (editable),
                "fiducial_pad_solder_mask_clearance_entry");
        const gchar* fiducial_pad_solder_mask_clearance_string =
                gtk_entry_get_text (GTK_ENTRY
                (fiducial_pad_solder_mask_clearance_entry));
        fiducial_pad_solder_mask_clearance = g_ascii_strtod
                (fiducial_pad_solder_mask_clearance_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The file chooser dialog "Cancel" button is clicked.
 *
 * <ul>
 * <li>lookup the dialog widget.
 * <li>destroy the file chooser widget.
 * </ul>
 *
 * \todo - maybe restore the preview widget ?
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_filechooser_dialog_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
        GtkWidget *filechooser_dialog = lookup_widget (GTK_WIDGET (button),
                "filechooser_dialog");
        gtk_widget_destroy (filechooser_dialog);
}


/*!
 * \brief The file chooser dialog "close" signal is emitted.
 *
 * <ul>
 * <li>lookup the dialog widget.
 * <li>destroy the file chooser widget.
 * </ul>
 *
 * <b>Parameters:</b> \c *dialog is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_filechooser_dialog_close            (GtkDialog       *dialog,
                                        gpointer         user_data)
{
        GtkWidget *filechooser_dialog = lookup_widget (GTK_WIDGET (dialog),
                "filechooser_dialog");
        gtk_widget_destroy (filechooser_dialog);
}



/*!
 * \brief The file chooser dialog "current folder changed" signal is emitted.
 *
 * <ul>
 * <li>lookup the dialog widget.
 * <li>get the current folder.
 * <li>test the current folder for null pointer or empty string and if
 *   true, please log a message and return.
 * <li>store the (new) current folder name in \c temp_dir.
 * </ul>
 *
 * <b>Parameters:</b> \c *filechooser is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_filechooser_dialog_current_folder_changed
(
        GtkFileChooser *filechooser,
        gpointer user_data
)
{
        GtkWidget *filechooser_dialog = lookup_widget (GTK_WIDGET (filechooser),
                "filechooser_dialog");
        gchar *current_folder = g_strdup (gtk_file_chooser_get_current_folder
                (GTK_FILE_CHOOSER (filechooser_dialog)));
        /* Test if current folder is a null pointer.
         * If so, please log a message. */
        if (!current_folder)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("current folder is not initialised  (null pointer)."));
        }
        /* Test if current folder is an empty string pointer.
         * If so, please log a message. */
        else if (!strcmp (current_folder, ""))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("current folder contains an empty string."));
        }
        /* Test if current folder is a directory.
         * If so, store in temp_dir. */
        else if (g_file_test (current_folder, G_FILE_TEST_IS_DIR))
        {
                temp_dir = g_strdup (current_folder);
                if (verbose)
                        g_log ("", G_LOG_LEVEL_INFO, _("Changed cwd to: %s"),
                                current_folder);
        }
        /* Clean up used variable(s). */
        g_free (current_folder);
}


/*!
 * \brief The file chooser dialog "Open" button is clicked.
 *
 * <ul>
 * <li>lookup the dialog widget.
 * <li>get the selected filename.
 * <li>test the selected filename for null pointer or empty string and if true,
 *   please log a message.
 * <li>test if the selected filename is not a directory and if true,
 *   please log a message.
 * <li>store the selected filename in \c fpw_filename.
 * <li>duplicate the (new) current directory name from \c temp_dir into
 *   \c work_dir.
 * <li>read new global values from the selected footprintwizard file.
 * <li>update the entry widgets to reflect the changes.
 * </ul>
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_filechooser_dialog_open_button_clicked
(
        GtkButton *button,
        gpointer user_data
)
{
        GtkWidget *filechooser_dialog = lookup_widget (GTK_WIDGET (button),
                "filechooser_dialog");
        gchar *selected_filename = NULL;
        selected_filename = g_strdup (gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (filechooser_dialog)));
        /* Test if selected filename is a null pointer.
         * If so, please log a message and return. */
        if (!selected_filename)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("selected filename is not initialised (NULL pointer)."));
        }
        /* Test if selected filename is an empty string.
         * If so, please log a message and return. */
        else if (!strcmp (selected_filename, ""))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("selected filename contains an empty string."));
        }
        /* Test if selected filename is a directory.
         * If so, please notify the user (in the statusbar), to select a file
         * instead. */
        else if (g_file_test (selected_filename, G_FILE_TEST_IS_DIR))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING, _("selected filename is a directory."));
        }
        else
        {
                /* Store the (now validated) selected filename. */
                gchar *fpw_filename = g_strdup (selected_filename);
                if (temp_dir)
                        work_dir = g_strdup (temp_dir);
                /* Read new global values from the selected footprintwizard file. */
                if (read_footprintwizard_file (fpw_filename) == EXIT_SUCCESS)
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_INFO, _("Read footprintwizard file %s."), fpw_filename);
                        /* Update the entry widgets to reflect the changes. */
                        GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET (button));
                        if (GTK_WIDGET_TOPLEVEL (toplevel))
                        {
                                all_entries_need_updated (GTK_WIDGET (toplevel));
                        }
                        /* Clean up used variable(s). */
                        g_free (toplevel);
                }
                else
                {
                        GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET (button));
                        if (GTK_WIDGET_TOPLEVEL (toplevel))
                        {
                                GtkWidget *dialog = gtk_message_dialog_new
                                (
                                        GTK_WINDOW (toplevel),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_CLOSE,
                                        g_strdup_printf (_("ERROR: Unable to read footprint wizard file %s."), fpw_filename)
                                );
                                gtk_dialog_run (GTK_DIALOG (dialog));
                                gtk_widget_destroy (dialog);
                                g_free (dialog);
                                return;
                        }
                        g_free (toplevel);
                }
                /* Clean up used variable(s). */
                g_free (fpw_filename);
        }
        /* Clean up used variable(s). */
        g_free (selected_filename);
}


/*!
 * \brief The file chooser dialog "selection changed" signal is emitted.
 *
 * \todo - store the selected filename in \c temp_fpw_filename.
 * \todo - read the values from the selected footprintwizard file in a
 * temporary set of variables \c temp_*.
 * \todo - generate a new preview image.
 * \todo - update the preview widget.
 *
 * <b>Parameters:</b> \c *filechooser is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_filechooser_dialog_selection_changed
                                        (GtkFileChooser  *filechooser,
                                        gpointer         user_data)
{

}


/*!
 * \brief The file chooser dialog "update preview" signal is emitted.
 *
 * \todo - generate a new preview image.
 * \todo - update the preview widget.
 *
 * <b>Parameters:</b> \c *filechooser is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_filechooser_dialog_update_preview   (GtkFileChooser  *filechooser,
                                        gpointer         user_data)
{

}


/*!
 * \brief The "footprint author name" entry is changed.
 *
 * Store in the \c footprint_author variable (global).
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_footprint_author_entry_changed      (GtkEditable     *editable,
                                        gpointer         user_data)
{
        GtkWidget *footprint_author_entry = lookup_widget (GTK_WIDGET (editable),
                "footprint_author_entry");
        footprint_author = g_strdup (gtk_entry_get_text (GTK_ENTRY (footprint_author_entry)));
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "Footprint" button is clicked.
 *
 * <ul>
 * <li>check for null pointer and empty string in \c footprint_name.
 * <li>determine the name of the footprintwizard filename.
 * <li>determine the name of the footprint filename.
 * <li>invoke the write_footprint() function to write the footprint
 *   file.
 * <li>if the footprint file is written successfull reflect this in the
 *   statusbar.
 * </ul>
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_footprint_button_clicked            (GtkButton       *button,
                                        gpointer         user_data)
{
        /* Check for a null pointer in footprint_name for this might cause a
         * segmentation fault or undefined behaviour.
         */
        if (!footprint_name)
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint name not initialised (null pointer)."));
                message_to_statusbar (GTK_WIDGET (button), message);
                return;
        }
        /* Check for an empty footprint_name string for this might cause a
         * segmentation fault or undefined behaviour.
         */
        else if (!strcmp (footprint_name, ""))
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint name contains an empty string."));
                message_to_statusbar (GTK_WIDGET (button), message);
                return;
        }
        else
        {
                gchar *message = g_strdup_printf ("");
                message_to_statusbar (GTK_WIDGET (button), message);
        }
        /* Determine a filename for the footprint file */
        footprint_filename = g_strdup (footprint_name);
        if (g_str_has_suffix (footprint_filename, fp_suffix))
        {
                /* footprint_filename has the .fp suffix already,
                 * so do nothing here */
        }
        else
        {
                /* footprint_filename has no .fp suffix,
                 * so add a .fp suffix */
                footprint_filename = g_strconcat (footprint_filename, ".fp", NULL);
        }
        /* If the footprint file is written successfull reflect this in the
         * statusbar */
        if (write_footprint () == EXIT_SUCCESS)
        {
                gchar *message = g_strdup_printf (_("Wrote footprint %s to file."), footprint_filename);
                message_to_statusbar (GTK_WIDGET (button), message);
        }
        else
        {
                gchar *message = g_strdup_printf (_("ERROR: Unable to write footprint %s to file."), footprint_filename);
                message_to_statusbar (GTK_WIDGET (button), message);
        }
}


/*!
 * \brief The "footprint distribution license" entry is changed.
 *
 * Store in the \c footprint_dist_license variable (global).
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_footprint_dist_license_entry_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        GtkWidget *footprint_dist_license_entry = lookup_widget (GTK_WIDGET (editable),
                "footprint_dist_license_entry");
        footprint_dist_license = g_strdup (gtk_entry_get_text (GTK_ENTRY (footprint_dist_license_entry)));
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "footprint name" entry is changed.
 *
 * Store in the \c footprint_name variable (global).
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_footprint_name_entry_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        GtkWidget *footprint_name_entry = lookup_widget (GTK_WIDGET (editable),
                "footprint_name_entry");
        footprint_name = g_strdup (gtk_entry_get_text (GTK_ENTRY (footprint_name_entry)));
        entry_has_changed (GTK_WIDGET (editable));
        /* Check for a null pointer in footprint_name for this might cause a
         * segmentation fault or undefined behaviour.
         */
        if (!footprint_name)
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint name not initialised (null pointer)."));
                message_to_statusbar (GTK_WIDGET (editable), message);
                return;
        }
        /* Check for an empty footprint_name string for this might cause a
         * segmentation fault or undefined behaviour.
         */
        else if (!strcmp (footprint_name, ""))
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint name contains an empty string."));
                message_to_statusbar (GTK_WIDGET (editable), message);
                return;
        }
        else if (g_str_has_prefix (footprint_name, "?"))
        {
                switch (package_type)
                {
                        case BGA:
                        {
                                if (bga_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case CAPA:
                        {
                                if (capa_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case CAPC:
                        {
                                if (capc_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case CAPM:
                        {
                                if (capm_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case CAPMP:
                        {
                                if (capmp_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case CON_DIL:
                        {
                                if (con_dil_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case CON_DIP:
                        {
                                if (con_dip_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case CON_HDR:
                        {
                                if (con_hdr_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case CON_SIL:
                        {
                                if (con_sil_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case DIOM:
                        {
                                if (diom_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case DIOMELF:
                        {
                                if (diomelf_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case DIP:
                        {
                                if (dip_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case INDC:
                        {
                                if (indc_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case INDM:
                        {
                                if (indm_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case INDP:
                        {
                                if (indp_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case PGA:
                        {
                                if (pga_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case PLCC:
                        {
                                if (plcc_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case RES:
                        {
                                if (res_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case RESC:
                        {
                                if (resc_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case RESM:
                        {
                                if (resm_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case SIL:
                        {
                                if (sil_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case SIP:
                        {
                                if (sip_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        case SOT:
                        {
                                if (sot_get_default_footprint_values (footprint_name) == EXIT_SUCCESS)
                                        all_entries_need_updated (GTK_WIDGET (editable));
                                return;
                        }
                        default:
                        {
                                gchar *message = g_strdup_printf (_("ERROR: unknown or not yet implemented footprint type entered."));
                                message_to_statusbar (GTK_WIDGET (editable), message);
                                return;
                        }
                }
        }
        else
        {
                gchar *message = g_strdup_printf ("");
                message_to_statusbar (GTK_WIDGET (editable), message);
                return;
        }
}


/*!
 * \brief The "footprint refdes prefix" entry is changed.
 *
 * Store in the \c footprint_refdes variable (global).
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_footprint_refdes_entry_changed      (GtkEditable     *editable,
                                        gpointer         user_data)
{
        GtkWidget *footprint_refdes_entry = lookup_widget (GTK_WIDGET (editable),
                "footprint_refdes_entry");
        footprint_refdes = g_strdup (gtk_entry_get_text (GTK_ENTRY (footprint_refdes_entry)));
        entry_has_changed (GTK_WIDGET (editable));
}

/*!
 * \brief The "footprint status" entry is changed.
 *
 * Store in the \c footprint_status variable (global).
 *
 * <b>Parameters:</b> \c *combobox is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_footprint_status_entry_changed      (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        footprint_status = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
        entry_has_changed (GTK_WIDGET (combobox));
        /* Determine the status type. */
        if (get_status_type () == EXIT_FAILURE)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("footprint status contains an unknown status type."));
//                footprint_status = g_strdup ("");
                return;
        }
        else
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_INFO,
                                _("determined the status type successfull."));
        }
}


/*!
 * \brief The "footprint type" entry is changed.
 *
 * <ul>
 * <li>test if the footprint name is equal with the footprint type or has a
 *   null pointer or is an empty string, if so copy the footprint type into
 *   the footprint name entry.
 * <li>store the new value in the \c footprint_type variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *combobox is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_footprint_type_entry_changed        (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        /* Test if the existing footprint name is equal to the footprint
         * type or is empty or has a null pointer, if this is true the user
         * did not add any characters to the footprint name yet (he/she
         * probably made up his/her mind on the footprint type), so we can
         * safely copy the new footprint type into the footprint name entry.
         */
        if (!footprint_name ||
                (!strcmp (footprint_name, "")) ||
                (!strcmp (footprint_type, footprint_name)))
        {
                footprint_type = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
                footprint_name = g_strdup (footprint_type);
                GtkWidget *footprint_name_entry = lookup_widget (GTK_WIDGET (combobox),
                        "footprint_name_entry");
                gtk_entry_set_text (GTK_ENTRY (footprint_name_entry), footprint_name);
        }
        else
        {
                footprint_type = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
        }
//        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
        entry_has_changed (GTK_WIDGET (combobox));
        /* Determine the package type */
        if (get_package_type () == EXIT_FAILURE)
        {
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type contains an unknown package type."));
                footprint_type = g_strdup ("");
                return;
        }
        else
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_INFO,
                                _("determined the package type (%d) for footprint type %s successfull."),
                                package_type, footprint_type);
        }
        switch (package_type)
        {
                case BGA:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        bga_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case CAPA:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        capa_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case CAPC:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        capc_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case CAPM:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        capm_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case CAPMP:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        capmp_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case CON_DIL:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        con_dil_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case CON_DIP:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        con_dip_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case CON_HDR:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        con_hdr_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case CON_SIL:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        con_sil_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case DIL:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        dip_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case DIOM:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        diom_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case DIOMELF:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        diomelf_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case DIP:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        dip_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case INDC:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        indc_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case INDM:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        indm_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case INDP:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        indp_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case PGA:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        pga_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case PLCC:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        plcc_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case QFN:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        gchar *message = g_strdup_printf (_("ERROR: footprint type QFN is not yet implemented."));
                        message_to_statusbar (GTK_WIDGET (combobox), message);
                        break;
                }
                case QFP:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        gchar *message = g_strdup_printf (_("ERROR: footprint type QFP is not yet implemented."));
                        message_to_statusbar (GTK_WIDGET (combobox), message);
                        break;
                }
                case RES:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        res_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case RESC:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        resc_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case RESM:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        resm_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case RESMELF:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        resmelf_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case SIL:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        sil_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case SIP:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        sip_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case SO:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        gchar *message = g_strdup_printf (_("ERROR: footprint type SO is not yet implemented."));
                        message_to_statusbar (GTK_WIDGET (combobox), message);
                        break;
                }
                case SOT:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        sot_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case TO92:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        to_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case TO220:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        to_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case TO220S:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        to_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case TO220SW:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        to_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                case TO220W:
                {
                        all_entries_to_default_sensitivity (GTK_WIDGET (combobox));
                        to_set_gui_constraints (GTK_WIDGET (combobox));
                        break;
                }
                default:
                {
                        gchar *message = g_strdup_printf (_("ERROR: unknown or not yet implemented footprint type entered."));
                        message_to_statusbar (GTK_WIDGET (combobox), message);
                        break;
                }
        }
}


/*!
 * \brief The "footprint units" entry is changed.
 *
 * <ul>
 * <li>store in the \c footprint_units variable (global).
 * <li>check for null pointer and empty string.
 * </ul>
 *
 * <b>Parameters:</b> \c *combobox is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_footprint_units_entry_changed       (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        entry_has_changed (GTK_WIDGET (combobox));
        footprint_units = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
        /* Check for a null pointer in footprint units for this might cause a
         * segmentation fault or undefined behaviour.
         */
        if (!footprint_units)
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint units not initialised (null pointer)."));
                message_to_statusbar (GTK_WIDGET (combobox), message);
                return;
        }
        /* Check for an empty footprint units string for this might cause a
         * segmentation fault or undefined behaviour.
         */
        else if (!strcmp (footprint_units, ""))
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint units contains an empty string."));
                message_to_statusbar (GTK_WIDGET (combobox), message);
                return;
        }
        /* Determine the units multiplier and units type */
        else if (update_units_variables () == EXIT_FAILURE)
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint units contains an unknown units type."));
                message_to_statusbar (GTK_WIDGET (combobox), message);
        }
        else
        {
                gchar *message = g_strdup_printf ("");
                message_to_statusbar (GTK_WIDGET (combobox), message);
        }
}


/*!
 * \brief The "footprint usage license" entry is changed.
 *
 * Store in the \c footprint_use_license variable (global).
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_footprint_use_license_entry_changed (GtkEditable     *editable,
                                        gpointer         user_data)
{
        GtkWidget *footprint_use_license_entry = lookup_widget (GTK_WIDGET (editable),
                "footprint_use_license_entry");
        footprint_use_license = g_strdup (gtk_entry_get_text (GTK_ENTRY (footprint_use_license_entry)));
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "footprint value" entry is changed.
 *
 * Store in the \c footprint_value variable (global).
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_footprint_value_entry_changed       (GtkEditable     *editable,
                                        gpointer         user_data)
{
        GtkWidget *footprint_value_entry = lookup_widget (GTK_WIDGET (editable),
                "footprint_value_entry");
        footprint_value = g_strdup (gtk_entry_get_text (GTK_ENTRY (footprint_value_entry)));
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "position of number 1 pad/pin" entry is changed.
 *
 * Store in the \c n1_pos variable (global).
 *
 * <b>Parameters:</b> \c *combobox is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_number_1_position_entry_changed
                                        (GtkComboBox     *combobox,
                                         gpointer         user_data)
{
        pin_1_position = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
        entry_has_changed (GTK_WIDGET (combobox));
}


/*!
 * \brief The "number of columns" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c n_col variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_number_of_columns_entry_changed     (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (editable),
                "number_of_columns_entry");
        const gchar* number_of_columns_string = gtk_entry_get_text (GTK_ENTRY (number_of_columns_entry));
        number_of_columns = (int) g_ascii_strtod (number_of_columns_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
        number_of_pins_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "number of rows" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c n_row variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_number_of_rows_entry_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (editable),
                "number_of_rows_entry");
        const gchar* number_of_rows_string = gtk_entry_get_text (GTK_ENTRY (number_of_rows_entry));
        number_of_rows = (int) g_ascii_strtod (number_of_rows_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
        number_of_pins_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "number of pads/pins" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c n variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_number_total_pins_entry_changed     (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (editable),
                "number_total_pins_entry");
        const gchar* number_of_pins_string = gtk_entry_get_text (GTK_ENTRY (number_total_pins_entry));
        number_of_pins = (int) g_ascii_strtod (number_of_pins_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "Open" button is clicked.
 *
 * <ul>
 * <li>create a file chooser dialog.
 * <li>create and set a file filter "*.fpw" and add to the file chooser.
 * <li>show the file chooser widget to let the user select a .fpw file.
 * </ul>
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_open_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
        GtkWidget *filechooser_dialog = create_filechooser_dialog ();
        GtkFileFilter *file_filter = gtk_file_filter_new ();
        gtk_file_filter_set_name (file_filter, "fpw filter");
        gtk_file_filter_add_pattern (GTK_FILE_FILTER (file_filter), "*.fpw");
        gtk_file_chooser_add_filter (GTK_FILE_CHOOSER (filechooser_dialog),
                GTK_FILE_FILTER (file_filter));
        gtk_widget_show (filechooser_dialog);
}


/*!
 * \brief The "package body height" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c package_body_height variable
 *   (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_package_body_height_entry_changed   (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *package_body_height_entry = lookup_widget (GTK_WIDGET (editable),
                "package_body_height_entry");
        const gchar* package_body_height_string = gtk_entry_get_text (GTK_ENTRY (package_body_height_entry));
        package_body_height = g_ascii_strtod (package_body_height_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "package body length" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c package_body_length variable
 *   (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_package_body_length_entry_changed   (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *package_body_length_entry = lookup_widget (GTK_WIDGET (editable),
                "package_body_length_entry");
        const gchar* package_body_length_string = gtk_entry_get_text (GTK_ENTRY (package_body_length_entry));
        package_body_length = g_ascii_strtod (package_body_length_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "package body width" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c package_body_width variable
 *   (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_package_body_width_entry_changed    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *package_body_width_entry = lookup_widget (GTK_WIDGET (editable),
                "package_body_width_entry");
        const gchar* package_body_width_string = gtk_entry_get_text (GTK_ENTRY (package_body_width_entry));
        package_body_width = g_ascii_strtod (package_body_width_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "package is radial" checkbutton is toggled.
 *
 * Store the state of the checkbutton in the \c package_is_radial
 * variable (global).
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_package_is_radial_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        package_is_radial = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        entry_has_changed (GTK_WIDGET (togglebutton));
}


/*!
 * \brief The "pad clearance" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c pad_clearance variable
 *   (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pad_clearance_entry_changed         (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *pad_clearance_entry = lookup_widget (GTK_WIDGET (editable),
                "pad_clearance_entry");
        const gchar* pad_clearance_string = gtk_entry_get_text (GTK_ENTRY (pad_clearance_entry));
        pad_clearance = g_ascii_strtod (pad_clearance_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "diameter of the pad (D)" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c d_pad variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pad_diameter_entry_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *pad_diameter_entry = lookup_widget (GTK_WIDGET (editable),
                "pad_diameter_entry");
        const gchar* pad_diameter_string = gtk_entry_get_text (GTK_ENTRY (pad_diameter_entry));
        pad_diameter = g_ascii_strtod (pad_diameter_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "length of the pads (X)" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c pad_length variable
 *   (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pad_length_entry_changed            (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *pad_length_entry = lookup_widget (GTK_WIDGET (editable),
                "pad_length_entry");
        const gchar* pad_length_string = gtk_entry_get_text (GTK_ENTRY (pad_length_entry));
        pad_length = g_ascii_strtod (pad_length_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "shape of pads" entry is changed.
 *
 * <ul>
 * <li>store in the \c pad_shape variable (global).
 * <li>check for null pointer and empty string.
 * </ul>
 *
 * <b>Parameters:</b> \c *combobox is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pad_shape_entry_changed    (GtkComboBox     *combobox,
                               gpointer         user_data)
{
        pad_shape = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
        entry_has_changed (GTK_WIDGET (combobox));
        /* Check for a null pointer in pad shape for this might cause a
         * segmentation fault or undefined behaviour.
         */
        if (!pad_shape)
        {
                gchar *message = g_strdup_printf (_("ERROR: pad shape not initialised (null pointer)."));
                message_to_statusbar (GTK_WIDGET (combobox), message);
                return;
        }
        /* Check for an empty pad shape string for this might cause a
         * segmentation fault or undefined behaviour.
         */
        else if (!strcmp (pad_shape, ""))
        {
                gchar *message = g_strdup_printf (_("ERROR: pad shape contains an empty string."));
                message_to_statusbar (GTK_WIDGET (combobox), message);
                return;
        }
        /* Determine the pad shape type */
        else if (update_pad_shapes_variables () == EXIT_FAILURE)
        {
                gchar *message = g_strdup_printf (_("ERROR: pad shape contains an unknown pad shape type."));
                message_to_statusbar (GTK_WIDGET (combobox), message);
        }
        else
        {
                gchar *message = g_strdup_printf ("");
                message_to_statusbar (GTK_WIDGET (combobox), message);
        }
}


/*!
 * \brief The "pad solder mask clearance" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c solder_mask_clearance
 *   variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pad_solder_mask_clearance_entry_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *pad_solder_mask_clearance_entry = lookup_widget (GTK_WIDGET (editable),
                "pad_solder_mask_clearance_entry");
        const gchar* pad_SMC_string = gtk_entry_get_text (GTK_ENTRY (pad_solder_mask_clearance_entry));
        pad_solder_mask_clearance = g_ascii_strtod (pad_SMC_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "width of the pads (Y)" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c pad_with variable
 *   (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pad_width_entry_changed             (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *pad_width_entry = lookup_widget (GTK_WIDGET (editable),
                "pad_width_entry");
        const gchar* pad_width_string = gtk_entry_get_text (GTK_ENTRY (pad_width_entry));
        pad_width = g_ascii_strtod (pad_width_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The top-right "X" is clicked.
 *
 * Close the application.
 *
 * <b>Parameters:</b> \c *object is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pcb_gfpw_destroy                    (GtkObject       *object,
                                        gpointer         user_data)
{
        gtk_main_quit();
}


/*!
 * \brief The "diameter of the drill holes (d)" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c pin_drill_diameter
 *   variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pin_drill_diameter_entry_changed    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_WIDGET (editable),
                "pin_drill_diameter_entry");
        const gchar* pin_drill_diameter_string = gtk_entry_get_text (GTK_ENTRY (pin_drill_diameter_entry));
        pin_drill_diameter = g_ascii_strtod (pin_drill_diameter_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "Pin/Pad exceptions" button is clicked.
 *
 * <ul>
 * <li>check if a (valid) footprint type has been selected and if a
 *   valid number of rows and a valid number of columns is selected:
 *   <ul>
 *   <li>if non valid values have been selected (or not selected yet)
 *     log a warning and let this occurance pass.
 *   <li>if valid values have been selected create a seperate window
 *     with radio buttons depicting the package leads.
 *   </ul>
 * </ul>
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pin_pad_exceptions_button_clicked   (GtkButton       *button,
                                        gpointer         user_data)
{
        if ((number_of_rows < 1) ||
                (number_of_columns < 1))
        {
                gchar *message = g_strdup_printf (_("Number of rows or columns is 0."));
                message_to_statusbar (GTK_WIDGET (button), message);
                return;
        }
        else
        {
                /* initialise the entire selection button array with
                 * FALSE values */
                gint i;
                gint j;
                SelectionButtonSet *selection_button;
                gint selection_button_index = 0;
                for (i = 0; (i < MAX_ROWS); i++)
                {
                        for (j = 0; (j < MAX_COLUMNS); j++)
                        {
                                selection_button = &selection_buttons[selection_button_index];
                                selection_button->active = FALSE;
                                selection_button_index++;
                        }
                }
                /* fill the selection button array with values based on
	         * the current string obtained from the "pin/pad exceptions"
                 * entry */
                selection_button_index = 0;
                for (i = 0; (i < number_of_rows); i++)
                {
                        for (j = 0; (j < number_of_columns); j++)
                        {
                                selection_button = &selection_buttons[selection_button_index];
                                selection_button->id = selection_button_index;
                                gchar *selection_button_name = g_strdup_printf ("%s%d",
                                        (row_letters[i]), (j + 1));
                                selection_button->name = g_strdup (selection_button_name);
                                selection_button->active = !get_pin_pad_exception
                                        (selection_button_name);
                                selection_button_index++;
                                g_free (selection_button_name);
                        }
                }
                gchar *message = g_strdup ("");
                message_to_statusbar (GTK_WIDGET (button), message);
                select_exceptions_create_window (number_of_rows,
                        number_of_columns);
        }

}


/*!
 * \brief The "pin/pad exceptions" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>store the contents in the \c pin_pad_exception_string variable
 *   (global) for processing while generating a footprint or preview.
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pin_pad_exceptions_entry_changed     (GtkEditable     *editable,
                                        gpointer         user_data)
{
        GtkWidget *pin_pad_exceptions_entry = lookup_widget (GTK_WIDGET (editable),
                "pin_pad_exceptions_entry");
        pin_pad_exceptions_string = g_strdup_printf (gtk_entry_get_text (GTK_ENTRY (pin_pad_exceptions_entry)));
        entry_has_changed (GTK_WIDGET (editable));

}

/*!
 * \brief The "pin #1 square" checkbutton is toggled.
 *
 * Save the state of the checkbutton in the \c pin1_square variable
 * (global).
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pin_square_checkbutton_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        /* Save the state of checkbutton in global variable */
        pin1_square = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        entry_has_changed (GTK_WIDGET (togglebutton));
}

/*!
 * \brief The "Pitch X-direction" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c pitch_x variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pitch_x_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *pitch_x_entry = lookup_widget (GTK_WIDGET (editable),
                "pitch_x_entry");
        const gchar* pitch_x_string = gtk_entry_get_text (GTK_ENTRY (pitch_x_entry));
        pitch_x = g_ascii_strtod (pitch_x_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "Pitch Y-direction" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c pitch_y variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_pitch_y_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *pitch_y_entry = lookup_widget (GTK_WIDGET (editable),
                "pitch_y_entry");
        const gchar* pitch_y_string = gtk_entry_get_text (GTK_ENTRY (pitch_y_entry));
        pitch_y = g_ascii_strtod (pitch_y_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "Preview" button is clicked.
 *
 * Create a pixmap of the footprint based on the values in the entry
 * widgets.
 *
 * \todo - create and (re)load the preview image.
 *
 * There are several ways to create a preview image of the footprint based on
 * the values entered in the entries:\n
 * <ol>
 * <li>Copy the method as in the pcb pinout preview.\n
 * Advantage: proven functionality in pcb.\n
 * Disadvantage: this means including a lot of code from pcb.\n
 * <li>Invoke pcb to create a picture, and subsequent load that picture into
 * the preview drawing area.\n
 * Advantage: proven functionality in pcb.\n
 * Disadvantage: this will make the user wait, and this will eventually
 * become a showstopper.\n
 * <li>Change pcb-fpw into a plug-in.\n
 * Advantage: all pcb functionality is at hand.\n
 * Disadvantage: the gtk approach will not work on the lesstif GUI.\n
 * <li>Make an inbuilt renderer for drawing footprints inside pcb-fpw.\n
 * Advantage: a renderer would keep pcb-fpw independant of whatever GUI is
 * used in pcb itself, actually pcb-fpw itself would have to draw on a
 * canvas, regardless if pcb is installed/available or not.\n
 * Disadvantage: a lot of code to duplicate, modify and maintain.\n
 * </ol>
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
*/
void
on_preview_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
/*! \bug  Invoking preview_create_window (footprint_name, 300, 200);
 * gives an error by ld.
 */
}


/*!
 * \brief The "Refresh" button is clicked.
 *
 * Refresh all the entries in the GUI.
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_refresh_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
        all_entries_need_updated (GTK_WIDGET (button));
}

/*!
 * \brief The "Save" button is clicked.
 *
 * <ul>
 * <li>check for null pointer and empty string in \c footprint_name.
 * <li>determine the name of the footprintwizard filename.
 * <li>determine the name of the footprint filename.
 * <li>invoke the write_footprintwizard_file() to write the global variables to
 *   the footprintwizard file, with a .fpw suffix, for debugging and other
 *   (future) purposes.
 * <li>if the footprint wizard file is written successfull change the title of
 *   the main window with the latest filename.
 * <li>invoke the write_footprint() function to write the actual footprint
 *   file.
 * <li>if the footprint file is written successfull reflect this in the
 *   statusbar.
 * </ul>
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_save_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
        /* Check for a null pointer in footprint_name for this might cause a
         * segmentation fault or undefined behaviour.
         */
        if (!footprint_name)
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint name not initialised (null pointer)."));
                message_to_statusbar (GTK_WIDGET (button), message);
                return;
        }
        /* Check for an empty footprint_name string for this might cause a
         * segmentation fault or undefined behaviour.
         */
        else if (!strcmp (footprint_name, ""))
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint name contains an empty string."));
                message_to_statusbar (GTK_WIDGET (button), message);
                return;
        }
        else
        {
                gchar *message = g_strdup_printf ("");
                message_to_statusbar (GTK_WIDGET (button), message);
        }
        /* Determine a filename for the footprint file. */
        footprint_filename = g_strdup (footprint_name);
        if (g_str_has_suffix (footprint_filename, fp_suffix))
        {
                /* footprint_filename has the .fp suffix already,
                 * so do nothing here. */
        }
        else
        {
                /* footprint_filename has no .fp suffix,
                 * so add a .fp suffix. */
                footprint_filename = g_strconcat (footprint_filename, ".fp", NULL);
        }
        /* Determine a filename for the footprintwizard file. */
        gchar *fpw_filename = g_strdup (footprint_name);
        if (g_str_has_suffix (fpw_filename, fp_suffix))
        {
                /* footprint_name had the .fp suffix already,
                 * only add a "w" here, else we would end up with a filename
                 * like "footprint_name.fp.fpw". */
                fpw_filename = g_strconcat (fpw_filename, "w", NULL);
        }
        else
        {
                if (g_str_has_suffix (fpw_filename, fpw_suffix))
                {
                        /* footprint_name had the .fpw suffix already,
                         * we probably read from an existing footprintwizard
                         * file or screwed up, so do nothing here. */
                }
                else
                {
                        /* fpw_filename has no (.fpw) suffix yet,
                         * so add a .fpw suffix. */
                        fpw_filename = g_strconcat (fpw_filename, ".fpw", NULL);
                }
        }
        /* If the footprint wizard file is written successfull change the title of
         * the main window with the latest filename. */
        if (write_footprintwizard_file (fpw_filename) == EXIT_SUCCESS)
        {
                change_main_window_title (GTK_WIDGET (button),
                        g_strconcat ("pcb-gfpw : ",
                        fpw_filename, NULL));
                main_window_title_has_asterisk = FALSE;
                fpw_file_saved = TRUE;
        }
        else
        {
                gchar *message = g_strdup_printf (_("ERROR: Unable to write footprintwizard file %s."), footprint_filename);
                message_to_statusbar (GTK_WIDGET (button), message);
        }
}


/*!
 * \brief The "indicate pin/pad number 1" checkbutton is toggled.
 *
 * Store the state of the checkbutton in the \c silkscreen_indicate_1
 *   variable (global).
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_silkscreen_indicate_1_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        silkscreen_indicate_1 = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        entry_has_changed (GTK_WIDGET (togglebutton));
}


/*!
 * \brief The "silkscreen line width" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c silkscreen_line_thickness
 *   variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *ediatble is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_silkscreen_line_width_entry_changed (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *silkscreen_line_width_entry = lookup_widget (GTK_WIDGET (editable),
                "silkscreen_line_width_entry");
        const gchar* silkscreen_line_width_string = gtk_entry_get_text (GTK_ENTRY (silkscreen_line_width_entry));
        silkscreen_line_width = g_ascii_strtod (silkscreen_line_width_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "package outline" checkbutton is toggled.
 *
 * <ul>
 * <li>save the state of the checkbutton in the \c silkscreen_package_outline
 *   variable (global).
 * <li>if the "package outline" checkbutton is not "checked", set the linewidth
 *   entry to insensitive.
 * <li>if the "package outline" checkbutton is "checked", set the line width
 *   entry to sensitive.
 * </ul>
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_silkscreen_package_outline_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                         gpointer         user_data)
{
        /* Save the state of checkbutton in global variable */
        silkscreen_package_outline = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        /* Look up widgets */
        GtkWidget *silkscreen_line_width_entry = lookup_widget (GTK_WIDGET (togglebutton), "silkscreen_line_width_entry");
        /* Set entities to (in)sensitive according to the state of the
         * checkbutton variable */
        gtk_widget_set_sensitive (silkscreen_line_width_entry, silkscreen_package_outline);
        entry_has_changed (GTK_WIDGET (togglebutton));
}


/*!
 * \brief The "thermal pad" checkbutton is toggled.
 *
 * <ul>
 * <li>save the state of the checkbutton in the \c thermal variable
 *   (global).
 * <li>if the "thermal pad" checkbutton is not "checked", set the length
 *   and width entries to insensitive.
 * <li>if the "thermal pad" checkbutton is "checked", set the length and
 *   width entries to sensitive.
 * <li>if the "thermal pad" checkbutton is "checked", set the no paste
 *   checkbutton to sensitive and active (on).
 * </ul>
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_thermal_checkbutton_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        /* Save the state of checkbutton in a global variable */
        thermal = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        entry_has_changed (GTK_WIDGET (togglebutton));
        number_of_pins_has_changed (GTK_WIDGET (togglebutton));
        /* Look up widgets */
        GtkWidget *thermal_nopaste_checkbutton = lookup_widget (GTK_WIDGET (togglebutton),
                "thermal_nopaste_checkbutton");
        GtkWidget *thermal_length_entry = lookup_widget (GTK_WIDGET (togglebutton),
                "thermal_length_entry");
        GtkWidget *thermal_width_entry = lookup_widget (GTK_WIDGET (togglebutton),
                "thermal_width_entry");
        GtkWidget *thermal_clearance_entry = lookup_widget (GTK_WIDGET (togglebutton),
                "thermal_clearance_entry");
        GtkWidget *thermal_solder_mask_clearance_entry = lookup_widget (GTK_WIDGET (togglebutton),
                "thermal_solder_mask_clearance_entry");
        /* Set entities to (in)sensitive according to the state of the
         * checkbutton variable */
        gtk_widget_set_sensitive (thermal_nopaste_checkbutton, thermal);
        gtk_widget_set_sensitive (thermal_length_entry, thermal);
        gtk_widget_set_sensitive (thermal_width_entry, thermal);
        gtk_widget_set_sensitive (thermal_clearance_entry, thermal);
        gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, thermal);
        /* We want no paste on a thermal pad as a default, so when the user
         * checks the thermal checkbutton (on), the user has to turn off
         * paste if desired while leaving the thermal checkbutton checked
         * (on) */
        gtk_toggle_button_set_active ((void *) thermal_nopaste_checkbutton, thermal);
}


/*!
 * \brief The "thermal pad clearance" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c thermal_clearance
 *   variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_thermal_clearance_entry_changed     (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *thermal_clearance_entry = lookup_widget (GTK_WIDGET (editable),
                "thermal_clearance_entry");
        const gchar* thermal_clearance_string = gtk_entry_get_text (GTK_ENTRY (thermal_clearance_entry));
        thermal_clearance = g_ascii_strtod (thermal_clearance_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "thermal pad length" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c thermal_length variable
 *   (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_thermal_length_entry_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *thermal_length_entry = lookup_widget (GTK_WIDGET (editable),
                "thermal_length_entry");
        const gchar* thermal_length_string = gtk_entry_get_text (GTK_ENTRY (thermal_length_entry));
        thermal_length = g_ascii_strtod (thermal_length_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "thermal pad no paste" checkbutton is clicked.
 *
 * Store the state of the checkbutton in the \c thermal_nopaste variable
 *   (global).
 *
 * <b>Parameters:</b> \c *togglebutton is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_thermal_nopaste_checkbutton_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        thermal_nopaste = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        entry_has_changed (GTK_WIDGET (togglebutton));
}


/*!
 * \brief The "thermal pad solder mask clearance" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c thermal_solder_clearance
 *   variable (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_thermal_solder_mask_clearance_entry_changed
                                        (GtkEditable     *editable,
                                         gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *thermal_solder_mask_clearance_entry = lookup_widget (GTK_WIDGET (editable),
                "thermal_solder_mask_clearance_entry");
        const gchar* SMC_string = gtk_entry_get_text (GTK_ENTRY (thermal_solder_mask_clearance_entry));
        thermal_solder_mask_clearance = g_ascii_strtod (SMC_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}


/*!
 * \brief The "thermal pad width" entry is changed.
 *
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert to a double and store in the \c thermal_width variable
 *   (global).
 * </ul>
 *
 * <b>Parameters:</b> \c *editable is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_thermal_width_entry_changed         (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        GtkWidget *thermal_width_entry = lookup_widget (GTK_WIDGET (editable),
                "thermal_width_entry");
        const gchar* thermal_width_string = gtk_entry_get_text (GTK_ENTRY (thermal_width_entry));
        thermal_width = g_ascii_strtod (thermal_width_string, &leftovers);
        entry_has_changed (GTK_WIDGET (editable));
}

/* EOF */

