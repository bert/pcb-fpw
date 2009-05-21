/*!
 * \file indc.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Functions for INDC SMT footprints.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.\n
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n
 * See the GNU General Public License for more details.\n
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to:\n
 * the Free Software Foundation, Inc., \n
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "register_functions.c"

/*!
 * \brief Look up default values for INDC SMT footprint.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised known values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - .
 */
int
indc_get_default_footprint_values
(
        gchar *footprint_name
)
{
        if (!strcmp (footprint_name, "?INDC"))
        {
                number_of_pins = 2;
                package_body_length = 0.0;
                package_body_width = 0.0;
                package_body_height = 0.0;
                package_is_radial = FALSE;
                number_of_columns = 0;
                number_of_rows = 0;
                pitch_x = 0.0;
                pitch_y = 0.0;
                pad_length = 0.0;
                pad_width = 0.0;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.0;
                silkscreen_width = 0.0;
                courtyard_length = 0.0;
                courtyard_width = 0.0;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("INDC");
                return (EXIT_SUCCESS);
        }
        else
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("default values for footprint %s not found.\n"),
                        footprint_name);
                return (EXIT_FAILURE);
        }
}


#if GUI
/*!
 * \brief Set GUI constraints for the INDC SMT package type.
 */
int
indc_set_gui_constraints (GtkWidget *widget)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_columns_entry), "2");
        gtk_widget_set_sensitive (number_of_columns_entry, FALSE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_rows_entry), "1");
        gtk_widget_set_sensitive (number_of_rows_entry, FALSE);
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
        gtk_combo_box_set_active (GTK_COMBO_BOX (number_1_position_entry), UPPER_LEFT);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}
#endif /* GUI */


/*!
 * \brief Write a INDC SMT footprint with two pads for a chip package.
 */
int
indc_write_footprint ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;

        /* Determine (extreme) courtyard dimensions based on pin/pad
         * properties */
        xmin = multiplier * ((-pitch_x / 2.0) - (pad_length / 2.0) - pad_solder_mask_clearance);
        xmax = multiplier * (pitch_x / 2.0 + pad_length / 2.0 + pad_solder_mask_clearance);
        ymin = multiplier * ((-pad_width / 2.0) - pad_solder_mask_clearance);
        ymax = multiplier * (pad_width / 2.0 + pad_solder_mask_clearance);
        /* Determine (extreme) courtyard dimensions based on package
         * properties */
        if ((multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package)) < xmin)
                xmin = (multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package)) > xmax)
                xmax = (multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package));
        if ((multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package)) < ymin)
                ymin = (multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package)) > ymax)
                ymax = (multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package));
        /* If the user input is using even more real-estate then use it */
        if (multiplier * (-courtyard_length / 2.0) < xmin)
                xmin = multiplier * (-courtyard_length / 2.0);
        if (multiplier * (courtyard_length / 2.0) > xmax)
                xmax = multiplier * (courtyard_length / 2.0);
        if (multiplier * (-courtyard_width / 2.0) < ymin)
                ymin = multiplier * (-courtyard_width / 2.0);
        if (multiplier * (courtyard_width / 2.0) > ymax)
                ymax = multiplier * (courtyard_width / 2.0);
        /* Write element header
         * Guess for a place where to put the refdes text */
        x_text = 0.0 ; /* already in mil/100 */
        y_text = (ymin - 10000.0); /* already in mil/100 */
        write_element_header (x_text, y_text);
        /* Write pin and/or pad entities */
        if (!strcmp (pad_shape, "rectangular pad"))
                pin_pad_flags = g_strdup ("square");
        if (pad_length > pad_width) /* Write pads parallel to x-axis */
        {
                /* Pad #1 */
                write_pad
                (
                        1, /* pad number */
                        "", /* pad name */
                        multiplier * ((-pitch_x - pad_length + pad_width) / 2.0), /* x0 coordinate */
                        0, /* y0-coordinate */
                        multiplier * ((-pitch_x + pad_length - pad_width) / 2.0), /* x1 coordinate */
                        0, /* y1-coordinate */
                        multiplier * pad_width, /* width of the pad */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                        /* Write pin #1 with a square pad if checked */
                        (pin1_square) ? "square" : pin_pad_flags /* flags */
                );
                /* Pad #2 */
                write_pad
                (
                        2, /* pad number */
                        "", /* pad name */
                        multiplier * ((pitch_x - pad_length + pad_width) / 2.0), /* x0 coordinate */
                        0, /* y0-coordinate */
                        multiplier * ((pitch_x + pad_length - pad_width) / 2.0), /* x1 coordinate */
                        0, /* y1-coordinate */
                        multiplier * pad_width, /* width of the pad */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
        }
        else /* write pads perpendiclar to x-axis */
        {
                /* Pad #1 */
                write_pad
                (
                        1, /* pad number */
                        "", /* pad name */
                        multiplier * (-pitch_x / 2.0), /* x0-coordinate */
                        multiplier * ((pad_width - pad_length) / 2.0), /* y0-coordinate */
                        multiplier * (-pitch_x / 2), /* x0-coordinate */
                        multiplier * ((-pad_width + pad_length) / 2.0), /* y1-coordinate */
                        multiplier * pad_length, /* width of the pad */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * (pad_length + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                        /* Write pin #1 with a square pad if checked */
                        (pin1_square) ? "square" : pin_pad_flags /* flags */
                );
                /* Pad #2 */
                write_pad
                (
                        2, /* pad number */
                        "", /* pad name */
                        multiplier * (pitch_x / 2.0), /* x1-coordinate */
                        multiplier * ((pad_width - pad_length) / 2.0), /* y0-coordinate */
                        multiplier * (pitch_x / 2.0), /* x1-coordinate */
                        multiplier * ((-pad_width + pad_length) / 2.0), /* y1-coordinate */
                        multiplier * pad_length, /* width of the pad */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * (pad_length + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
        }
        /* Write a package body on the silkscreen */
        if (silkscreen_package_outline && (package_body_width))
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
                write_element_line
                (
                        multiplier * (((-pitch_x + pad_length) / 2.0) + pad_solder_mask_clearance + silkscreen_line_width),
                        multiplier * (package_body_width / 2.0),
                        multiplier * (((pitch_x - pad_length) / 2.0) - pad_solder_mask_clearance - silkscreen_line_width),
                        multiplier * (package_body_width / 2.0),
                        multiplier * silkscreen_line_width
                );
                write_element_line
                (
                        multiplier * (((-pitch_x + pad_length) / 2.0) + pad_solder_mask_clearance + silkscreen_line_width),
                        multiplier * (-package_body_width / 2.0),
                        multiplier * (((pitch_x - pad_length) / 2.0) - pad_solder_mask_clearance - silkscreen_line_width),
                        multiplier * (-package_body_width / 2.0),
                        multiplier * silkscreen_line_width
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                /* package has no pin/pad #1 indication */
        }
        /* Write a courtyard on the silkscreen */
        if (courtyard)
        {
                fprintf (fp, "# Write a courtyard on the silkscreen\n");
                write_rectangle
                (
                        xmin, /* already in mil/100 */
                        ymin, /* already in mil/100 */
                        xmax, /* already in mil/100 */
                        ymax, /* already in mil/100 */
                        multiplier * courtyard_line_width
                );
        }
        return (EXIT_SUCCESS);
}


static fpw_function_t
indc_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                indc_set_gui_constraints,
                "Set GUI constraints for a INDC SMT package",
                NULL
        },
#endif /* GUI */
        {
                "Default Element Values",
                indc_get_default_footprint_values,
                "Get default values for a INDC SMT package",
                NULL
        },
        {
                "Write footprint",
                indc_write_footprint,
                "Write a footprint for a INDC SMT package",
                NULL
        }
};


REGISTER_FUNCTIONS (indc_function_list)

void
indc_init ()
{
        register_indc_function_list ();
}


/* EOF */
