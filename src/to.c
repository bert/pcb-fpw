/*!
 * \file to.c
 * \author Copyright (C) 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Functions for TO (Transistor Outline) footprints.
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
 * \brief Create a list of TO packages with pre-defined values.
 *
 * The data in this list can be used in a combobox to select a
 * pre-defined package.
 *
 * \return a list containing all package names of this footprint type
 * known by pcb-fpw.
 */
GList
to_create_packages_list ()
{
        GList *to_packages_list = NULL;
        to_packages_list = g_list_append (to_packages_list, "TO92");
        return (*to_packages_list);
}


/*!
 * \brief Look up default values for TO footprint.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised known values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - .
 *
 * \return \c EXIT_SUCCESS when default values for a footprint were
 * found, \c EXIT_FAILURE when the footprint name was not found.
 */
int
to_get_default_footprint_values
(
        gchar *footprint_name
                /*!< : a \c NULL terminated footprint name.*/
)
{
        if (!strcmp (footprint_name, "?TO92"))
        {
                number_of_pins = 3;
                package_body_length = 0.0;
                package_body_width = 0.0;
                package_body_height = 0.0;
                package_is_radial = TRUE;
                number_of_columns = 0;
                number_of_rows = 0;
                pitch_x = 0.0;
                pitch_y = 0.0;
                pad_length = 0.0;
                pad_width = 0.0;
                pad_shape = g_strdup ("rounded pad");
                pad_shapes_type = ROUND;
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
                footprint_name = g_strdup ("TO92");
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


/*!
 * \brief Set GUI constraints for the TO package type.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
#if GUI
int
to_set_gui_constraints
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
        return (EXIT_SUCCESS);
}
#endif /* GUI */


/*!
 * \brief Write a TO92 footprint for a transistor package.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
to_write_footprint_to92 ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;

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
        xmin = -10500 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        xmax = 10500 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymin = -8600 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymax = 10500 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
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
        else
                pin_pad_flags = g_strdup ("");
        write_pin
        (
                1, /* pin number */
                "", /* pin name */
                -5000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                /* Write pin #1 with a square pad */
                (pin1_square) ? "square" : "" /* flags */
        );
        write_pin
        (
                2, /* pin number */
                "", /* pin name */
                0.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        write_pin
        (
                3, /* pin number */
                "", /* pin name */
                5000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        /* Write package body on the silkscreen */
        if (silkscreen_package_outline)
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
                fprintf (fp, "\tElementLine[-8600 -6000 8600 -6000 1000]\n");
                fprintf (fp, "\tElementArc[0 0 10500 10500 -35 250 1000]\n");
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                /*! \todo Write a pin #1 marker on the silkscreen ! */
        }
        /* Write a courtyard on the silkscreen */
        if (courtyard)
        {
                fprintf (fp, "# Write a courtyard on the silkscreen\n");
                if (package_is_radial)
                {
                        write_element_arc
                        (
                                0.0,
                                0.0,
                                xmax, /* already in mil/100 */
                                ymax, /* already in mil/100 */
                                0,
                                360,
                                multiplier * courtyard_line_width
                        );
                }
                else
                {
                        write_rectangle
                        (
                                xmin, /* already in mil/100 */
                                ymin, /* already in mil/100 */
                                xmax, /* already in mil/100 */
                                ymax, /* already in mil/100 */
                                multiplier * courtyard_line_width
                        );
                }
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
 * \brief A list containing all TO related functions.
 */
static fpw_function_t
to_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                to_set_gui_constraints,
                "Set GUI constraints for a TO package",
                NULL
        },
#endif /* GUI */
        {
                "Default Element Values",
                to_get_default_footprint_values,
                "Get default values for a INDC SMT package",
                NULL
        },
        {
                "Write footprint",
                to_write_footprint_to92,
                "Write a footprint for a TO92 package",
                NULL
        }
};


REGISTER_FUNCTIONS (to_function_list)


/*!
 * \brief Initialise by registering all TO related functions.
 */
void
to_init ()
{
        register_to_function_list ();
}


/* EOF */
