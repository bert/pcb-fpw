/*!
 * \file con_hdr.c
 * \author Copyright 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Functions for CON-HDR (connector) footprints.
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


#include "register_functions.c"


/*!
 * \brief Look up default values for CON-HDR footprints.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised the values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - ,
 *
 * <b>Parameters:</b> \c *footprint_name a \c NULL terminated footprint
 * name.\n
 * \n
 * <b>Returns:</b> \c EXIT_SUCCESS when default values for a footprint
 * were found, \c EXIT_FAILURE when the footprint name was not found.
 */
int
con_hdr_get_default_footprint_values
(
        gchar *footprint_name)
{
        if (!strcmp (footprint_name, "?CON-HDR"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 4;
                package_body_width = 300;
                package_body_length = 100;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 100;
                pitch_y = 100;
                count_x = 0;
                count_y = 2;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON-HDR");
                return (EXIT_SUCCESS);
        }
        else
        {
                fprintf (stderr,
                         _("WARNING: default values for footprint %s not found.\n"),
                         footprint_name);
                return (EXIT_FAILURE);
        }
}


/*!
 * \brief Create a list of CON-HDR packages with pre-defined values.
 *
 * The data in this list can be used in a combo box to select a
 * pre-defined package.
 * \n
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> a list containing all package names of this footprint
 * type known by pcb-fpw.
 */
GList
con_hdr_create_packages_list ()
{
        GList *con_hdr_packages_list = NULL;
        con_hdr_packages_list = g_list_append (con_hdr_packages_list, "CON-DIP");
        return (*con_hdr_packages_list);
}


/*!
 * \brief Set GUI constraints for the CON-HDR package type.
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Returns:</b> none.
 */
#if GUI
int
con_hdr_set_gui_constraints (GtkWidget *widget)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (widget),
                "number_total_pins_entry");
        gtk_widget_set_sensitive (number_total_pins_entry, FALSE);
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_columns_entry), "");
        gtk_widget_set_sensitive (number_of_columns_entry, FALSE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_rows_entry), "");
        gtk_widget_set_sensitive (number_of_rows_entry, TRUE);
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                "count_x_entry");
        gtk_entry_set_text (GTK_ENTRY (count_x_entry), "");
        gtk_widget_set_sensitive (count_x_entry, TRUE);
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
#endif /* GUI */


/*!
 * \brief Write a CON-HDR pin through hole footprint.
 *
 * The pin/pad numbering scheme of the CON-HDR package is: \n
 * for 2 rows \n
 * 2 4 6 8 \n
 * 1 3 5 7 \n
 * or for 3 rows \n
 * 3  6  9  12 \n
 * 2  5  8  11 \n
 * 1  4  7  10 \n
 * You get the idea for 4 or more rows. \n
 * \n
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
con_hdr_write_footprint ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gint pin_number;
        gchar *pin_pad_name = g_strdup ("");
        gint i;
        gint j;

        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                fprintf
                (
                        stderr,
                        "ERROR: could not open file for %s footprint: %s.\n",
                        footprint_type,
                        footprint_filename
                );
                return (EXIT_FAILURE);
        }
        /* Determine (extreme) courtyard dimensions based on pin/pad
         * properties */
        xmin = multiplier *
        (
                (((-number_of_columns + 1) / 2.0) * pitch_x) -
                (((pad_diameter > pad_length) ? pad_diameter : pad_length) / 2.0) -
                pad_solder_mask_clearance
        );
        xmax = multiplier *
        (
                (((number_of_columns - 1) / 2.0) * pitch_x) +
                (((pad_diameter > pad_length) ? pad_diameter : pad_length) / 2.0) +
                pad_solder_mask_clearance
        );
        ymin = multiplier *
        (
                (-pitch_y / 2.0) -
                (((pad_diameter > pad_width) ? pad_diameter : pad_width) / 2.0) -
                pad_solder_mask_clearance
        );
        ymax = multiplier *
        (
                (pitch_y / 2.0) +
                (((pad_diameter > pad_width) ? pad_diameter : pad_width) / 2.0) +
                pad_solder_mask_clearance
        );
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
        pin_number = 1;
        for (i = 0; (i < count_x); i++)
        {
                for (j = 0; (j < number_of_rows); j++)
                {
                        if (pin1_square && (pin_number == 1))
                                pin_pad_flags = g_strdup ("square");
                        else
                                pin_pad_flags = g_strdup ("");
                        write_pin
                        (
                                pin_number, /* pin number */
                                pin_pad_name, /* pin name */
                                multiplier * ((((-count_x - 1) / 2.0) + 1 + i) * pitch_x), /* x0-coordinate */
                                multiplier * ((((number_of_rows - 1) / 2.0) + 1 - j) * (pitch_y / 2.0)), /* y0 coordinate */
                                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_diameter + 2 * pad_solder_mask_clearance), /* solder mask clearance */
                                multiplier * pin_drill_diameter, /* pin drill diameter */
                                pin_pad_flags /* flags */
                        );
                        if (!strcmp (pad_shape, "rounded pad, elongated"))
                        {
                                if (!strcmp (pin_pad_flags, ""))
                                        pin_pad_flags = g_strconcat (pin_pad_flags, "onsolder", NULL);
                                else
                                        pin_pad_flags = g_strconcat (pin_pad_flags, ",onsolder", NULL);
                                write_pad
                                (
                                        pin_number, /* pad number = pin_number */
                                        pin_pad_name, /* pad name */
                                        multiplier * ((((-count_x - 1) / 2.0) + 1 + i) * pitch_x), /* x0-coordinate */
                                        multiplier * (((((number_of_rows - 1) / 2.0) + 1 - j) * (pitch_y / 2.0)) + pad_length - pad_width) / 2.0, /* y0 coordinate */
                                        multiplier * ((((-count_x - 1) / 2.0) + 1 + i) * pitch_x), /* x1-coordinate */
                                        multiplier * (((((number_of_rows - 1) / 2.0) + 1 - j) * (pitch_y / 2.0)) - pad_length + pad_width) / 2.0, /* y1 coordinate */
                                        multiplier * pad_length, /* width of the pad */
                                        multiplier * 2 * pad_clearance, /* clearance */
                                        multiplier * (pad_length + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                        pin_pad_flags /* flags */
                                );
                        }
                        pin_number++;
                }
        }
        /* Write a package body on the silkscreen */
        if (silkscreen_package_outline)
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
                write_rectangle
                (
                        multiplier * ((-package_body_length - silkscreen_line_width) / 2.0) ,
                        multiplier * ((-package_body_width - silkscreen_line_width) / 2.0) ,
                        multiplier * ((package_body_length + silkscreen_line_width) / 2.0) ,
                        multiplier * ((package_body_width + silkscreen_line_width) / 2.0) ,
                        multiplier * silkscreen_line_width
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                write_element_arc
                (
                        xmin - (multiplier * (pad_solder_mask_clearance + pad_clearance)), /* xmin already in mil/100 */
                        ymax + (multiplier * (pad_solder_mask_clearance + pad_clearance)), /* ymax already in mil/100 */
                        multiplier * 0.5 * silkscreen_line_width,
                        multiplier * 0.5 * silkscreen_line_width,
                        0,
                        360,
                        multiplier * silkscreen_line_width
                );
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
        /* Write attributes */
        if (attributes_in_footprint)
                write_attributes ();
        fprintf (fp, "\n");
        fprintf (fp, ")\n");
        fclose (fp);
        fprintf
        (
                stderr,
                "SUCCESS: wrote a footprint file for a %s package: %s.\n",
                footprint_type,
                footprint_filename
        );
	return (EXIT_SUCCESS);
}


/*!
 * \brief A list containing all CON-HDR related functions.
 */
static fpw_function_t
con_hdr_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                con_hdr_set_gui_constraints,
                "Set GUI constraints for a CON-HDR package",
                NULL
        },
#endif /* GUI */
        {
                "Default Element Values",
                con_hdr_get_default_footprint_values,
                "Get default values for a selected CON-HDR package",
                NULL
        },
        {
                "Write footprint",
                con_hdr_write_footprint,
                "Write footprint for a selected CON-HDR package",
                NULL
        }
};


/*!
 * \brief A list containing all CON-HDR related functions.
 */
REGISTER_FUNCTIONS (con_hdr_function_list)


/*!
 * \brief Initialise by registering all CON-HDR related functions.
 *
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> none.
 */
void
con_hdr_init ()
{
        register_con_hdr_function_list ();
}


/* EOF */
