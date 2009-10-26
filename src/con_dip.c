/*!
 * \file con_dip.c
 * \author Copyright 2007, 2008, 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Functions for CON-DIP (connector) footprints.
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
 * \brief Look up default values for CON-DIP footprints.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised the values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - ,
 *
 * \return \c EXIT_SUCCESS when default values for a footprint were
 * found, \c EXIT_FAILURE when the footprint name was not found.
 */
int
con_dip_get_default_footprint_values
(
        gchar *footprint_name
                /*!< : a \c NULL terminated footprint name.*/
)
{
        if (!strcmp (footprint_name, "?CON-DIP"))
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
                footprint_name = g_strdup ("CON-DIP04300");
                return (EXIT_SUCCESS);
        }
        else
        {
                fprintf (stderr,
                         _("WARNING: default values for footprint %s not found.\n"),
                         footprint_name);
                return (EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Create a list of CON-DIP packages with pre-defined values.
 *
 * The data in this list can be used in a combo box to select a
 * pre-defined package.
 *
 * \return a list containing all package names of this footprint type
 * known by pcb-fpw.
 */
GList
con_dip_create_packages_list ()
{
        GList *con_dip_packages_list = NULL;
        con_dip_packages_list = g_list_append (con_dip_packages_list, "CON-DIP");
        return (*con_dip_packages_list);
}


/*!
 * \brief Set GUI constraints for the CON-DIP package type.
 *
 * This function is only to be compiled for GUI targets.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
#if GUI
int
con_dip_set_gui_constraints
(
        GtkWidget *widget
                /*!< : the caller widget.*/
)
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
        gtk_widget_set_sensitive (number_of_columns_entry, TRUE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_rows_entry), "2");
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
        gtk_combo_box_set_active (GTK_COMBO_BOX (number_1_position_entry), 3);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
        return (EXIT_SUCCESS);
}
#endif /* GUI */


/*!
 * \brief Write a CON-DIP pin through hole footprint.
 *
 * The pin/pad numbering scheme of the CON-DIP package is: \n
 * 8 7 6 5 \n
 * 1 2 3 4 \n
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
con_dip_write_footprint ()
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
        for (i = 0; (i < number_of_columns); i++)
        {
                pin_number = 1 + i;
                if (pin1_square && (pin_number == 1))
                        pin_pad_flags = g_strdup ("square");
                else
                        pin_pad_flags = g_strdup ("");
                write_pin
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        multiplier * ((((-number_of_columns - 1) / 2.0) +1 + i) * pitch_x), /* x0-coordinate */
                        multiplier * (pitch_y / 2.0), /* y0 coordinate */
                        multiplier * pad_diameter, /* width of the annulus ring (pad) */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
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
                                multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x0-coordinate */
                                multiplier * (pitch_y + pad_length - pad_width) / 2.0, /* y0 coordinate */
                                multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x1-coordinate */
                                multiplier * (pitch_y - pad_length + pad_width) / 2.0, /* y1 coordinate */
                                multiplier * pad_length, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                }
                pin_number = (number_of_rows * number_of_columns) - i;
                if (pin1_square && (pin_number == 1))
                        pin_pad_flags = g_strdup ("square");
                else
                        pin_pad_flags = g_strdup ("");
                write_pin
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x0-coordinate */
                        multiplier * (-pitch_y / 2.0), /* y0 coordinate */
                        multiplier * pad_diameter, /* width of the annulus ring (pad) */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
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
                                pin_number, /* pad number = pin_number*/
                                pin_pad_name, /* pad name */
                                multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x0-coordinate */
                                multiplier * (pitch_y - pad_length + pad_width) / 2.0, /* y0 coordinate */
                                multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x1-coordinate */
                                multiplier * (pitch_y + pad_length - pad_width) / 2.0, /* y1 coordinate */
                                multiplier * pad_length, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
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
        return (EXIT_SUCCESS);
}


/*!
 * \brief A list containing all CON-DIP related functions.
 */
static fpw_function_t
con_dip_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                con_dip_set_gui_constraints,
                "Set GUI constraints for a CON-DIP package",
                NULL
        },
#endif /* GUI */
        {
                "Create Package List",
                con_dip_create_packages_list,
                "Create a list of packages with known values",
                NULL
        },
        {
                "Default Element Values",
                con_dip_get_default_footprint_values,
                "Get default values for a selected CON package",
                NULL
        },
        {
                "Write footprint",
                con_dip_write_footprint,
                "Write footprint for a selected CON-DIP package",
                NULL
        }
};


/*!
 * \brief A list containing all CON-DIP related functions.
 */
REGISTER_FUNCTIONS (con_dip_function_list)


/*!
 * \brief Initialise by registering all CON-DIP related functions.
 */
void
con_dip_init ()
{
        register_con_dip_function_list ();
}


/* EOF */
