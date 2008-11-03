/*!
 * \file pga.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Predefined values for PGA footprints.
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
 * \brief Look up default values for PGA footprints.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised the values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 */
int
pga_get_default_footprint_values
(
        gchar *footprint_name)
{
        if (!strcmp (footprint_name, "?PGA100"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                package_body_width = 11.00;
                package_body_length = 11.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 10;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.40;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                courtyard_length = 13.00;
                courtyard_width = 13.00;
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("PGA100");
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


#if GUI
/*!
 * \brief Set GUI constraints for the PGA package type.
 */
int
pga_set_gui_constraints (GtkWidget *widget)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab 2 "Pins/Pads" */
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
        GtkWidget *pin_pad_exceptions_button = lookup_widget (GTK_WIDGET (widget),
                "pin_pad_exceptions_button");
        gtk_widget_set_sensitive (pin_pad_exceptions_button, TRUE);
        GtkWidget *pad_shape_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_shape_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (pad_shape_entry), 1);
        gtk_widget_set_sensitive (pad_shape_entry, FALSE);
        GtkWidget *pad_length_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_length_entry");
        gtk_entry_set_text (GTK_ENTRY (pad_length_entry), "");
        gtk_widget_set_sensitive (pad_length_entry, FALSE);
        GtkWidget *pad_width_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_width_entry");
        gtk_entry_set_text (GTK_ENTRY (pad_width_entry), "");
        gtk_widget_set_sensitive (pad_width_entry, FALSE);

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}
#endif /* GUI */


/*!
 * \brief Write a footprint for a PGA package.
 */
int
pga_write_footprint ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gdouble dx;
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
                ((-pitch_x * number_of_columns) / 2.0) -
                (pad_diameter / 2.0) -
                pad_solder_mask_clearance
        );
        xmax = multiplier *
        (
                ((pitch_x * number_of_columns) / 2.0) +
                (pad_diameter / 2.0) +
                pad_solder_mask_clearance
        );
        ymin = multiplier *
        (
                ((-pitch_y * number_of_rows) / 2.0) -
                (pad_diameter / 2.0) -
                pad_solder_mask_clearance
        );
        ymax = multiplier *
        (
                ((pitch_y * number_of_rows) / 2.0) +
                (pad_diameter / 2.0) +
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
        for (i = 0; (i < number_of_rows); i++)
        /* one row at a time [A .. ZZ ..] etc.
         * where i is one or more letters of the alphabet,
         * excluding "I", "O", "Q", "S" and "Z" */
        {
                for (j = 0; (j < number_of_columns); j++)
                /* all columns of a row [1 .. n]
                 * where j is a member of the positive Natural numbers (N) */
                {
                        if (pin1_square && (pin_number == 1))
                                pin_pad_flags = g_strdup ("square");
                        else
                                pin_pad_flags = g_strdup ("");
                        pin_pad_name = g_strdup_printf ("%s%d", (row_letters[i]), (j + 1));
                        if (get_pin_pad_exception (pin_pad_name))
                        {
                                write_pin
                                (
                                        pin_number, /* pin number */
                                        pin_pad_name, /* pin name */
                                        multiplier * ((((- number_of_columns -1) / 2.0) + 1 + j) * pitch_x), /* x0 coordinate */
                                        multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y), /* y0-coordinate */
                                        multiplier * pad_diameter, /* width of the annulus ring (pad) */
                                        multiplier * pad_clearance, /* clearance */
                                        multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                                        multiplier * pin_drill_diameter, /* pin drill diameter */
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
                        multiplier * (-package_body_length / 2.0),
                        multiplier * (-package_body_width / 2.0),
                        multiplier * (package_body_length / 2.0),
                        multiplier * (package_body_width / 2.0),
                        multiplier * silkscreen_line_width
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                for (dx = 0.0; dx < (pitch_x / 2.0); dx = dx + silkscreen_line_width)
                {
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * ((-package_body_width / 2.0) + dx),
                                multiplier * ((-package_body_length / 2.0) + dx),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (silkscreen_line_width)
                        );
                }
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
}


static fpw_function_t
pga_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                pga_set_gui_constraints,
                "Set GUI constraints for a PGA package",
                NULL
        },
#endif /* GUI */
        {
                "Default Element Values",
                pga_get_default_footprint_values,
                "Get default values for a selected PGA package",
                NULL
        },
        {
                "Write footprint",
                pga_write_footprint,
                "Write a footprint for a selected PGA package",
                NULL
        }
};


REGISTER_FUNCTIONS (pga_function_list)

void
pga_init ()
{
        register_pga_function_list ();
}


/* EOF */
