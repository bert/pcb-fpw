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
#include "con_dip.h"


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
 * \brief Do some Design Rule Checking for the CON-DIP package type.
 *
 * <ul>
 * <li> check for total number of pins is even.
 * <li> check for number of rows is 2.
 * <li> check for number of columns is more than 1.
 * <li> check for allowed pad shapes.
 * <li> check for zero sized packages.
 * <li> check for a zero sized courtyard.
 * <li> check for minimum clearance between copper (X-direction).
 * <li> check for minimum clearance between copper (Y-direction).
 * <li> If any fiducials exist:
 *   <ul>
 *   <li> check for zero fiducial pad diameter.
 *   <li> check for zero width solder mask clearance.
 *   <li> check for minimum clearance between copper (between pads and
 *   fiducials, if any fiducials exist).
 *   </ul>
 * <li> check for clearance of the package length with regard to the
 * courtyard dimensions.
 * <li> check for clearance of the package width with regard to the
 * courtyard dimensions.
 * <li> check for any silk lines or texts touching bare copper.
 * <li> check for soldermask clearance (solder mask overlapping copper
 * at the solder fillet area or worse).
 * <li> check for a reasonable silk line width.
 * </ul>
 *
 * \return \c EXIT_SUCCESS when no DRC violations were encountered,
 * \c EXIT_FAILURE when DRC violations were found.
 */
int
con_dip_drc ()
{
        int result = EXIT_SUCCESS;
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("DRC Check: checking %s package %s."),
                        footprint_type, footprint_name);
        }
        /* Check for total number of pins is even. */
        if (!(number_of_pins % 2))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for number of pins is even."));
                }
                result = EXIT_FAILURE;
        }
        /* Check for number of rows is 2. */
        if (number_of_rows < 1)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for number of rows < 1."));
                }
                result = EXIT_FAILURE;
        }
        /* Check for number of columns < 1. */
        if (number_of_columns != 2)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for number of columns = 2."));
                }
                number_of_columns = 2;
                result = EXIT_FAILURE;
        }
        /* Check for allowed pad shapes. */
        switch (pad_shapes_type)
        {
                case NO_SHAPE:
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: NO_SHAPE specified for check for allowed pad shapes."));
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                case ROUND:
                {
                        break;
                }
                case SQUARE:
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: square pad shape specified for check for allowed pad shapes."));
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                case OCTAGONAL:
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: octagonal pad shape specified for check for allowed pad shapes."));
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                case ROUND_ELONGATED:
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: round elongated pad shape specified for check for allowed pad shapes."));
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                default:
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: no valid pad shape type specified."));
                        }
                        result = EXIT_FAILURE;
                        break;
                }
        }
        /* Check for zero sized packages. */
        if (package_body_length <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for package body length is <= 0.0."));
                }
                result = EXIT_FAILURE;
        }
        if (package_body_width <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for package body width is <= 0.0."));
                }
                result = EXIT_FAILURE;
        }
        if (package_body_height <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for package body height is <= 0.0."));
                }
                result = EXIT_FAILURE;
        }
        /* Check for a zero sized courtyard. */
        if (courtyard_length <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for courtyard length is <= 0.0."));
                }
                result = EXIT_FAILURE;
        }
        if (courtyard_width <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for courtyard width is <= 0.0."));
                }
                result = EXIT_FAILURE;
        }
        /* Check for minimum clearance between copper (X-direction). */
        if (pitch_x - pad_diameter < pad_clearance)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for minimum clearance between copper (X-direction)."));
                }
                result = EXIT_FAILURE;
        }
        /* Check for minimum clearance between copper (Y-direction). */
        if (pitch_y - pad_diameter < pad_clearance)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for minimum clearance between copper (Y-direction)."));
                }
                result = EXIT_FAILURE;
        }
        /*! If any fiducials exist:
         * - check for zero fiducial pad diameter.
         * - check for zero width solder mask clearance.
         * \todo - check for minimum clearance between pad copper and fiducial pad
         *   copper (including solder mask clearances).
         */
        if (fiducial)
        {
                /* Check for a zero width fiducial pad. */
                if (fiducial_pad_diameter == 0.0)
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: check for zero width fiducial pad."));
                        }
                        result = EXIT_FAILURE;
                }
                /* Check for a clearance of zero. */
                if (fiducial_pad_solder_mask_clearance == 0.0)
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: check for zero width solder mask clearance."));
                        }
                        result = EXIT_FAILURE;
                }
                /* Check for minimum clearance between pad copper and fiducial pad
                 * copper (including solder mask clearances). */
#if 0
                if ()
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: check for distance between fiducial and nearest pad."));
                        }
                        result = EXIT_FAILURE;
                }
#endif
        }
        /* Check for clearance of the package length with regard to the
         * courtyard dimensions. */
        if (package_body_length - courtyard_length < courtyard_clearance_with_package)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for clearance of the package length with regard to the courtyard dimensions."));
                }
                result = EXIT_FAILURE;
        }
        /* Check for clearance of the package width with regard to the
         * courtyard dimensions. */
        if (package_body_width - courtyard_width < courtyard_clearance_with_package)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for clearance of the package width with regard to the courtyard dimensions."));
                }
                result = EXIT_FAILURE;
        }
        /*! \todo Check for any silk lines or texts touching bare copper. */

        /*! \todo Check for soldermask clearance (solder mask overlapping copper at
         * the solder fillet area or worse). */

        /* Check for a reasonable silk line width. */
        if (silkscreen_package_outline || (silkscreen_line_width == 0.0))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: line width 0.0 specified for check for a reasonable silk line width."));
                }
                result = EXIT_FAILURE;
        }
        switch (units_type)
        {
                case NO_UNITS:
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: no units specified for check for a reasonable silk line width."));
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                case MIL:
                if (silkscreen_line_width > 40.0)
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: line width > 40.0 mil specified check for a reasonable silk line width."));
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                case MIL_100:
                if (silkscreen_line_width > 4000.0)
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: line width > 40.0 mil specified check for a reasonable silk line width."));
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                case MM:
                if (silkscreen_line_width > 1.0)
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: line width > 1.0 mm specified check for a reasonable silk line width."));
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                default:
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: no valid units type specified for check for a reasonable silk line width."));
                        }
                        result = EXIT_FAILURE;
                        break;
                }
        }
        /*! \todo Create attributes here. */
        /* No failures on DRC found. */
        if (verbose || (result == EXIT_SUCCESS))
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("DRC Check: no errors while checking PGA package %s."),
                        footprint_name);
        }
        return (result);
}


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
        if (!strcmp (footprint_name, "?CON-DIP04300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 4;
                package_body_width = 200;
                package_body_length = 200;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 2;
                pitch_x = 100;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
        gtk_entry_set_text (GTK_ENTRY (number_of_columns_entry), "2");
        gtk_widget_set_sensitive (number_of_columns_entry, FALSE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_rows_entry), "");
        gtk_widget_set_sensitive (number_of_rows_entry, TRUE);
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
 * 1  8 \n
 * 2  7 \n
 * 3  6 \n
 * 4  5 \n
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
        gchar *pin_pad_flags = g_strdup ("");
        gint i;

        number_of_columns = 2;
        /* Attempt to open a file with write permission. */
        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not open file for %s footprint: %s."),
                        footprint_type, footprint_filename);
                fclose (fp);
                return (EXIT_FAILURE);
        }
        /* Print a license if requested. */
        if (license_in_footprint)
        {
                write_license ();
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
                (((-number_of_rows + 1) / 2.0) * pitch_y) -
                (((pad_diameter > pad_width) ? pad_diameter : pad_width) / 2.0) -
                pad_solder_mask_clearance
        );
        ymax = multiplier *
        (
                (((number_of_rows - 1 ) / 2.0) * pitch_y) +
                (((pad_diameter > pad_width) ? pad_diameter : pad_width) / 2.0) +
                pad_solder_mask_clearance
        );
        /* Determine (extreme) courtyard dimensions based on package
         * properties */
        if ((multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package)) < xmin)
        {
                xmin = (multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package));
        }
        if ((multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package)) > xmax)
        {
                xmax = (multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package));
        }
        if ((multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package)) < ymin)
        {
                ymin = (multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package));
        }
        if ((multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package)) > ymax)
        {
                ymax = (multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package));
        }
        /* If the user input is using even more real-estate then use it */
        if (multiplier * (-courtyard_length / 2.0) < xmin)
        {
                xmin = multiplier * (-courtyard_length / 2.0);
        }
        if (multiplier * (courtyard_length / 2.0) > xmax)
        {
                xmax = multiplier * (courtyard_length / 2.0);
        }
        if (multiplier * (-courtyard_width / 2.0) < ymin)
        {
                ymin = multiplier * (-courtyard_width / 2.0);
        }
        if (multiplier * (courtyard_width / 2.0) > ymax)
        {
                ymax = multiplier * (courtyard_width / 2.0);
        }
        /* Write element header
         * Guess for a place where to put the refdes text */
        x_text = 0.0 ; /* already in mil/100 */
        y_text = (ymin - 10000.0); /* already in mil/100 */
        write_element_header (x_text, y_text);
        /* Write pin and/or pad entities */
        for (i = 0; (i < number_of_rows); i++)
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
                        multiplier * (-pitch_x / 2.0), /* x0 coordinate */
                        multiplier * ((((-number_of_rows - 1) / 2.0) +1 + i) * pitch_y), /* y0-coordinate */
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
                                multiplier * (-pitch_x - pad_width + pad_length) / 2.0, /* x0 coordinate */
                                multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y), /* y0-coordinate */
                                multiplier * (-pitch_x + pad_width - pad_length) / 2.0, /* x1 coordinate */
                                multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y), /* y1-coordinate */
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
                        multiplier * (pitch_x / 2.0), /* x0 coordinate */
                        multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y), /* y0-coordinate */
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
                                multiplier * (pitch_x - pad_width + pad_length) / 2.0, /* x0 coordinate */
                                multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y), /* y0-coordinate */
                                multiplier * (pitch_x + pad_width - pad_length) / 2.0, /* x1 coordinate */
                                multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y), /* y1-coordinate */
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
        /* Write attributes to the footprint file. */
        if (attributes_in_footprint)
        {
                write_attributes ();
        }
        /* Finishing touch. */
        fprintf (fp, "\n");
        fprintf (fp, ")\n");
        fclose (fp);
        /* We are ready creating a footprint. */
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("wrote a footprint for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
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
                "DRC CON-DIP Element",
                con_dip_drc,
                "Design Rule Check for a CON-DIP package",
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
