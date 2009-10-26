/*!
 * \file plcc.c
 * \author Copyright (C) 2007, 2008, 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Functions for PLCC footprints.
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
 * \brief Look up default values for PLCC footprints.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised the values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * -.
 *
 * \return \c EXIT_SUCCESS when default values for a footprint were
 * found, \c EXIT_FAILURE when the footprint name was not found.
 */
int
plcc_get_default_footprint_values
(
        gchar *footprint_name
                /*!< : a \c NULL terminated footprint name.*/
)
{
        if (!strcmp (footprint_name, "?PLCC84"))
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
                footprint_name = g_strdup ("PLCC84");
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
 * \brief Set GUI constraints for the PLCC package type.
 *
 * This function is only to be compiled for GUI targets.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
plcc_set_gui_constraints
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
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (number_1_position_entry), 4);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);
        GtkWidget *pad_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_diameter_entry");
        gtk_entry_set_text (GTK_ENTRY (pad_diameter_entry), "");
        gtk_widget_set_sensitive (pad_diameter_entry, FALSE);
        GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pin_drill_diameter_entry");
        gtk_entry_set_text (GTK_ENTRY (pin_drill_diameter_entry), "");
        gtk_widget_set_sensitive (pin_drill_diameter_entry, FALSE);
        GtkWidget *pad_shape_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_shape_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (pad_shape_entry), 2);

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);
        return (EXIT_SUCCESS);
}
#endif /* GUI */


/*!
 * \brief Write a SMT footprint for a PLCC package.
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
plcc_write_footprint ()
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
        gdouble x0;
        gdouble x1;
        gdouble y0;
        gdouble y1;
        gdouble y_dot;

        /* Determine (extreme) courtyard dimensions based on pin/pad
         * properties */
        if (c1_state) /* center-center distance */
        {
                ymin = multiplier * (((-c1 - pad_length) / 2.0) - pad_solder_mask_clearance);
                ymax = multiplier * (((c1 + pad_length) / 2.0) + pad_solder_mask_clearance);
        }
        if (g1_state) /* inner-inner distance */
        {
                ymin = multiplier * ((-g1 / 2.0) - pad_length - pad_solder_mask_clearance);
                ymax = multiplier * ((g1 / 2.0) + pad_length + pad_solder_mask_clearance);
        }
        if (z1_state) /* outer-outer distance */
        {
                ymin = multiplier * ((-z1 / 2.0) - pad_solder_mask_clearance);
                ymax = multiplier * ((z1 / 2.0) + pad_solder_mask_clearance);
        }
        if (c2_state) /* center-center distance */
        {
                xmin = multiplier * (((-c2 - pad_length) / 2.0) - pad_solder_mask_clearance);
                xmax = multiplier * (((c2 + pad_length) / 2.0) + pad_solder_mask_clearance);
        }
        if (g2_state) /* inner-inner distance */
        {
                xmin = multiplier * ((-g2 / 2.0) - pad_length - pad_solder_mask_clearance);
                xmax = multiplier * ((g2 / 2.0) + pad_length + pad_solder_mask_clearance);
        }
        if (z2_state) /* outer-outer distance */
        {
                xmin = multiplier * ((-z2 / 2.0) - pad_solder_mask_clearance);
                xmax = multiplier * ((z2 / 2.0) + pad_solder_mask_clearance);
        }
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
        /* Start with left top half side pads,
         * pads number from right to left,
         * pads itself are drawn from top (x0,y0) to bottom (x1,y1) */
        if (c1_state) /* center-center distance */
        {
                y0 = ((-c1 - pad_length + pad_width) / 2.0);
                y1 = ((-c1 + pad_length - pad_width) / 2.0);
        }
        if (g1_state) /* inner-inner distance */
        {
                y0 = ((-g1 + pad_width) / 2.0) - pad_length;
                y1 = ((-g1 - pad_width) / 2.0);
        }
        if (z1_state) /* outer-outer distance */
        {
                y0 = ((-z1 + pad_width) / 2.0);
                y1 = ((-z1 - pad_width) / 2.0) + pad_length;
        }
        for (pin_number = 1;
                pin_number < ((count_x / 2) + 1.5);
                pin_number++)
        {
                if (pin1_square && (pin_number == 1))
                        pin_pad_flags = g_strdup ("square");
                else if (!strcmp (pad_shape, "rectangular pad"))
                        pin_pad_flags = g_strdup ("square");
                else
                        pin_pad_flags = g_strdup ("");
                write_pad
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        multiplier * ((-pin_number + 1) * pitch_x), /* x0 coordinate */
                        multiplier * y0, /* y0-coordinate */
                        multiplier * ((-pin_number + 1) * pitch_x), /* x1 coordinate */
                        multiplier * y1, /* y1-coordinate */
                        multiplier * pad_width, /* pad width */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
        }
        /* Left side pads,
         * pads number from top to bottom,
         * pads itself are drawn from left (x0,y0) to right (x1,y1) */
        if (c2_state) /* center-center distance */
        {
                x0 = ((-c2 - pad_length + pad_width) / 2.0);
                x1 = ((-c2 + pad_length - pad_width) / 2.0);
        }
        if (g2_state) /* inner-inner distance */
        {
                x0 = ((-g2 + pad_width) / 2.0) - pad_length;
                x1 = ((-g2 - pad_width) / 2.0);
        }
        if (z2_state) /* outer-outer distance */
        {
                x0 = ((-z2 + pad_width) / 2.0);
                x1 = ((-z2 - pad_width) / 2.0) + pad_length;
        }
        i = 1;
        for (pin_number = ((count_x / 2) + 2.5);
                pin_number < ((count_x / 2) + 1.5 + count_y);
                pin_number++)
        {
                write_pad
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        multiplier * x0, /* x0 coordinate */
                        multiplier * ((-count_y / 2) - 1 + i) * pitch_y, /* y0-coordinate */
                        multiplier * x1, /* x1 coordinate */
                        multiplier * ((-count_y / 2) - 1 + i) * pitch_y, /* y1-coordinate */
                        multiplier * pad_width, /* pad width */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
                i++;
        }
        /* Bottom side pads,
         * pads number from left to right,
         * pads itself are drawn from top (x0,y0) to bottom (x1,y1) */
        if (c1_state) /* center-center distance */
        {
                y0 = ((c1 - pad_length + pad_width) / 2.0);
                y1 = ((c1 + pad_length - pad_width) / 2.0);
        }
        if (g1_state) /* inner-inner distance */
        {
                y0 = ((g1 + pad_width) / 2.0);
                y1 = ((g1 - pad_width) / 2.0) + pad_length;
        }
        if (z1_state) /* outer-outer distance */
        {
                y0 = ((z1 + pad_width) / 2.0) - pad_length;
                y1 = ((z1 - pad_width) / 2.0);
        }
        i = 1;
        for (pin_number = ((count_x / 2) + 2.5 + count_y);
                pin_number < ((count_x / 2) + 1.5 + count_y + count_x);
                pin_number++)
        {
                write_pad
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        multiplier * ((-count_x / 2) - 1 + i) * pitch_x, /* x0 coordinate */
                        multiplier * y0, /* y0-coordinate */
                        multiplier * ((-count_x / 2) - 1 + i) * pitch_x, /* x1 coordinate */
                        multiplier * y1, /* y1-coordinate */
                        multiplier * pad_width, /* pad width */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
                i++;
        }
        /* right side of the pads,
         * pads number from bottom to top,
         * pads itself are drawn from left (x0,y0) to right (x1,y1) */
        if (c2_state) /* center-center distance */
        {
                x0 = ((c2 - pad_length + pad_width) / 2.0);
                x1 = ((c2 + pad_length - pad_width) / 2.0);
        }
        if (g2_state) /* inner-inner distance */
        {
                x0 = ((g2 + pad_width) / 2.0);
                x1 = ((g2 - pad_width) / 2.0) + pad_length;
        }
        if (z2_state) /* outer-outer distance */
        {
                x0 = ((z2 + pad_width) / 2.0) - pad_length;
                x1 = ((z2 - pad_width) / 2.0);
        }
        i = 1;
        for (pin_number = ((count_x / 2) + 2.5 + count_y + count_x);
                pin_number < ((count_x / 2) + 1.5 + (2 * count_y) + count_x);
                pin_number++)
        {
                write_pad
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        multiplier * x0, /* x0 coordinate */
                        multiplier * ((count_y / 2) + 1 - i) * pitch_y, /* y0-coordinate */
                        multiplier * x1, /* x1 coordinate */
                        multiplier * ((count_y / 2) + 1 - i) * pitch_y, /* y1-coordinate */
                        multiplier * pad_width, /* pad width */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
                i++;
        }
        /* right top half of the pads,
         * pads number from right to left,
         * pads itself are drawn from top (x0,y0) to bottom (x1,y1) */
        if (c1_state) /* center-center distance */
        {
                y0 = ((-c1 - pad_length + pad_width) / 2.0);
                y1 = ((-c1 + pad_length - pad_width) / 2.0);
        }
        if (g1_state) /* inner-inner distance */
        {
                y0 = ((-g1 + pad_width) / 2.0) - pad_length;
                y1 = ((-g1 - pad_width) / 2.0);
        }
        if (z1_state) /* outer-outer distance */
        {
                y0 = ((-z1 + pad_width) / 2.0);
                y1 = ((-z1 - pad_width) / 2.0) + pad_length;
        }
        i = 1;
        for (pin_number = ((count_x / 2) + 2.5 + (2 * count_y) + count_x);
                pin_number < (2 * (count_y + count_x) + 1);
                pin_number++)
        {
                write_pad
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        multiplier * ((count_x / 2) + 1 - i) * pitch_x, /* x0 coordinate */
                        multiplier * y0, /* y0-coordinate */
                        multiplier * ((count_x / 2) + 1 - i) * pitch_x, /* x1 coordinate */
                        multiplier * y1, /* y1-coordinate */
                        multiplier * pad_width, /* pad width */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
                i++;
        }
        /* Write package body on silkscreen */
        if (silkscreen_package_outline)
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
                /* Upper right corner */
                write_element_line
                (
                        multiplier * (package_body_length / 2.0),
                        multiplier * (-package_body_width / 2.0),
                        multiplier * (package_body_length / 2.0),
                        multiplier * (-1 * ((((count_y - 1) * pitch_y) + pad_length) / 2.0) - pad_solder_mask_clearance),
                        multiplier * silkscreen_line_width
                );
                write_element_line
                (
                        multiplier * (package_body_length / 2.0),
                        multiplier * (-package_body_width / 2.0),
                        multiplier * (((((count_x - 1) * pitch_x) + pad_length) / 2.0) + pad_solder_mask_clearance),
                        multiplier * (-package_body_width / 2.0),
                        multiplier * silkscreen_line_width
                );
                /* Lower right corner */
                write_element_line
                (
                        multiplier * (package_body_length / 2.0),
                        multiplier * (package_body_width / 2.0),
                        multiplier * (package_body_length / 2.0),
                        multiplier * (((((count_y - 1) * pitch_y) + pad_length) / 2.0) + pad_solder_mask_clearance),
                        multiplier * silkscreen_line_width
                );
                write_element_line
                (
                        multiplier * (package_body_length / 2.0),
                        multiplier * (package_body_width / 2.0),
                        multiplier * (((((count_x - 1) * pitch_x) + pad_length) / 2.0) + pad_solder_mask_clearance),
                        multiplier * (package_body_width / 2.0),
                        multiplier * silkscreen_line_width
                );
                /* Lower left corner */
                write_element_line
                (
                        multiplier * (-package_body_length / 2.0),
                        multiplier * (package_body_width / 2.0),
                        multiplier * (-package_body_length / 2.0),
                        multiplier * (((((count_y - 1) * pitch_y) + pad_length) / 2.0) + pad_solder_mask_clearance),
                        multiplier * silkscreen_line_width
                );
                write_element_line
                (
                        multiplier * (-package_body_length / 2.0),
                        multiplier * (package_body_width / 2.0),
                        multiplier * (-1 * ((((count_x - 1) * pitch_x) + pad_length) / 2.0) - pad_solder_mask_clearance),
                        multiplier * (package_body_width / 2.0),
                        multiplier * silkscreen_line_width
                );
                /* Upper left corner */
                write_element_line
                (
                        multiplier * (-1 * ((((count_x - 1) * pitch_x) + pad_length) / 2.0) - pad_solder_mask_clearance),
                        multiplier * (-package_body_width / 2.0),
                        multiplier * (-package_body_length / 2.0),
                        multiplier * (-1 * ((((count_y - 1) * pitch_y) + pad_length) / 2.0) - pad_solder_mask_clearance),
                        multiplier * silkscreen_line_width
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                if (c1_state) /* center-center distance */
                {
                        y_dot = ((-c1 + pad_length - pad_width) / 2.0) +
                                pad_width + pad_solder_mask_clearance +
                                (2 * silkscreen_line_width);
                }
                if (g1_state) /* inner-inner distance */
                {
                        y_dot = ((-g1 - pad_width) / 2.0) +
                                pad_width + pad_solder_mask_clearance +
                                (2 * silkscreen_line_width);
                }
                if (z1_state) /* outer-outer distance */
                {
                        y_dot = ((-z1 - pad_width) / 2.0) + pad_length +
                                pad_width + pad_solder_mask_clearance +
                                (2 * silkscreen_line_width);
                }
                write_element_arc
                (
                        0,
                        multiplier * y_dot,
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
 * \brief A list containing all PLCC related functions.
 */
static fpw_function_t
plcc_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                plcc_set_gui_constraints,
                "Set GUI constraints for a PLCC package",
                NULL
        },
#endif /* GUI */
        {
                "Default Element Values",
                plcc_get_default_footprint_values,
                "Get default values for a selected PLCC package",
                NULL
        },
        {
                "Write footprint",
                plcc_write_footprint,
                "Write a footprint for a selected PLCC package",
                NULL
        }
};


/*!
 * \brief A list containing all PLCC related functions.
 */
REGISTER_FUNCTIONS (plcc_function_list)


/*!
 * \brief Initialise by registering all PLCC related functions.
 */
void
plcc_init ()
{
        register_plcc_function_list ();
}


/* EOF */
