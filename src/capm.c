/*!
 * \file capm.c
 * \author Copyright 2007, 2008, 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Functions for CAPM SMT footprints.
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
 * \brief Create an Element for a CAPM package.
 *
 * \return the created \c element.
 */
ElementTypePtr
capm_create_element ()
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
        FlagType pad_flag;
        ElementTypePtr element;

        if (!element)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("could not create a valid element pointer for a %s package."),
                                footprint_type);
                return (NULL);
        }
        /* Define the center of our universe and guess for a place where to
         * put the element mark */
        element->MarkX = 0;
        element->MarkY = 0;
        /* Determine (extreme) courtyard dimensions based on pin/pad
         * properties */
        xmin = multiplier * ((-pitch_x / 2.0) - (pad_length / 2.0) - pad_solder_mask_clearance);
        xmax = multiplier * (pitch_x / 2.0 + pad_length / 2.0 + pad_solder_mask_clearance);
        ymin = multiplier * ((-pad_width / 2.0) - pad_solder_mask_clearance);
        ymax = multiplier * (pad_width / 2.0 + pad_solder_mask_clearance);
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
        /* Guess for a place where to put the element name */
        element->Name[1].Scale = 100; /* 100 percent */
        element->Name[1].X = 0.0 ; /* already in mil/100 */
        element->Name[1].Y = (ymin - 10000.0); /* already in mil/100 */
        element->Name[1].TextString = footprint_name;
        element->Name[1].Element = element;
        element->Name[1].Direction = EAST;
        element->Name[1].ID = ID++;
        /* Guess for a place where to put the element refdes */
        element->Name[2].Scale = 100; /* 100 percent */
        element->Name[2].X = 0.0 ; /* already in mil/100 */
        element->Name[2].Y = (ymin - 10000.0); /* already in mil/100 */
        element->Name[2].TextString = footprint_refdes;
        element->Name[2].Element = element;
        element->Name[2].Direction = EAST;
        element->Name[2].ID = ID++;
        /* Guess for a place where to put the element value */
        element->Name[3].Scale = 100; /* 100 percent */
        element->Name[3].X = 0.0 ; /* already in mil/100 */
        element->Name[3].Y = (ymin - 10000.0); /* already in mil/100 */
        element->Name[3].TextString = footprint_value;
        element->Name[3].Element = element;
        element->Name[3].Direction = EAST;
        element->Name[3].ID = ID++;
        /* Create pin and/or pad entities */
        if (pad_shapes_type == SQUARE)
        {
                pad_flag.f = SQUARE;
        }
        else
        {
                pad_flag.f = CLEAR;
        }
        if (pad_length > pad_width) /* Write pads parallel to x-axis */
        {
                /* Pad #2 */
                create_new_pad
                (
                        element,
                        (int) (multiplier * ((pitch_x - pad_length + pad_width) / 2.0)), /* x0 coordinate */
                        0, /* y0-coordinate */
                        (int) (multiplier * ((pitch_x + pad_length - pad_width) / 2.0)), /* x1 coordinate */
                        0, /* y1-coordinate */
                        (int) (multiplier * pad_width), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * (pad_width + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        "N", /* pad name */
                        "2", /* pin number */
                        pad_flag /* flags */
                );
                /* Write pad #1 with a square pad if checked */
                if (pin1_square)
                {
                        pad_flag.f = SQUARE;
                }
                /* Pad #1 */
                create_new_pad
                (
                        element,
                        (int) (multiplier * ((-pitch_x - pad_length + pad_width) / 2.0)), /* x0 coordinate */
                        0, /* y0-coordinate */
                        (int) (multiplier * ((-pitch_x + pad_length - pad_width) / 2.0)), /* x1 coordinate */
                        0, /* y1-coordinate */
                        (int) (multiplier * pad_width), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * (pad_width + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        "P", /* pad name */
                        "1", /* pin number */
                        pad_flag /* flags */
                );
        }
        else /* write pads perpendiclar to x-axis */
        {
                /* Pad #2 */
                create_new_pad
                (
                        element,
                        (int) (multiplier * (pitch_x / 2.0)), /* x0 coordinate */
                        (int) (multiplier * ((pad_width - pad_length) / 2.0)), /* y0-coordinate */
                        (int) (multiplier * (pitch_x / 2.0)), /* x1 coordinate */
                        (int) (multiplier * ((-pad_width + pad_length) / 2.0)), /* y1-coordinate */
                        (int) (multiplier * pad_length), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * (pad_length + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        "N", /* pad name */
                        "2", /* pin number */
                        pad_flag /* flags */
                );
                /* Write pad #1 with a square pad if checked */
                if (pin1_square)
                {
                        pad_flag.f = SQUARE;
                }
                /* Pad #1 */
                create_new_pad
                (
                        element,
                        (int) (multiplier * (-pitch_x / 2.0)), /* x0 coordinate */
                        (int) (multiplier * ((pad_width - pad_length) / 2.0)), /* y0-coordinate */
                        (int) (multiplier * (-pitch_x / 2)), /* x1 coordinate */
                        (int) (multiplier * ((-pad_width + pad_length) / 2.0)), /* y1-coordinate */
                        (int) (multiplier * pad_length), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * (pad_length + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        "P", /* pad name */
                        "1", /* pin number */
                        pad_flag /* flags */
                );
        }
        /* Create a package body. */
        if (silkscreen_package_outline && package_body_width)
        {
                if (pad_width >= package_body_width)
                {
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (((-pitch_x + pad_length) / 2.0) + pad_solder_mask_clearance + silkscreen_line_width)),
                                (int) (multiplier * (package_body_width / 2.0)),
                                (int) (multiplier * (((pitch_x - pad_length) / 2.0) - pad_solder_mask_clearance - silkscreen_line_width)),
                                (int) (multiplier * (package_body_width / 2.0)),
                                (int) (multiplier * silkscreen_line_width)
                        );
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (((-pitch_x + pad_length) / 2.0) + pad_solder_mask_clearance + silkscreen_line_width)),
                                (int) (multiplier * (-package_body_width / 2.0)),
                                (int) (multiplier * (((pitch_x - pad_length) / 2.0) - pad_solder_mask_clearance - silkscreen_line_width)),
                                (int) (multiplier * (-package_body_width / 2.0)),
                                (int) (multiplier * silkscreen_line_width)
                        );
                }
                else
                {
                        /* lines parallel to X-axis */
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (-package_body_length / 2.0)),
                                (int) (multiplier * (package_body_width / 2.0)),
                                (int) (multiplier * (package_body_length / 2.0)),
                                (int) (multiplier * (package_body_width / 2.0)),
                                (int) (multiplier * silkscreen_line_width)
                        );
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (-package_body_length / 2.0)),
                                (int) (multiplier * (-package_body_width / 2.0)),
                                (int) (multiplier * (package_body_length / 2.0)),
                                (int) (multiplier * (-package_body_width / 2.0)),
                                (int) (multiplier * silkscreen_line_width)
                        );
                        /* lines perpendicular to X-axis */
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (-package_body_length / 2.0)),
                                (int) (multiplier * (-package_body_width / 2.0)),
                                (int) (multiplier * (-package_body_length / 2.0)),
                                (int) (multiplier * (((-pad_width - silkscreen_line_width) / 2.0) - pad_solder_mask_clearance)),
                                (int) (multiplier * silkscreen_line_width)
                        );
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (-package_body_length / 2.0)),
                                (int) (multiplier * (package_body_width / 2.0)),
                                (int) (multiplier * (-package_body_length / 2.0)),
                                (int) (multiplier * (((pad_width + silkscreen_line_width) / 2.0) + pad_solder_mask_clearance)),
                                (int) (multiplier * silkscreen_line_width)
                        );
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (package_body_length / 2.0)),
                                (int) (multiplier * (-package_body_width / 2.0)),
                                (int) (multiplier * (package_body_length / 2.0)),
                                (int) (multiplier * (((-pad_width - silkscreen_line_width) / 2.0) - pad_solder_mask_clearance)),
                                (int) (multiplier * silkscreen_line_width)
                        );
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (package_body_length / 2.0)),
                                (int) (multiplier * (package_body_width / 2.0)),
                                (int) (multiplier * (package_body_length / 2.0)),
                                (int) (multiplier * (((pad_width + silkscreen_line_width) / 2.0) + pad_solder_mask_clearance)),
                                (int) (multiplier * silkscreen_line_width)
                        );
                }
        }
        /* Create a pin #1 marker. */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                if (pad_width >= package_body_width)
                {
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (((-pitch_x + pad_length) / 2.0) + pad_solder_mask_clearance + silkscreen_line_width)),
                                (int) (multiplier * (-package_body_width / 2.0)),
                                (int) (multiplier * (((-pitch_x + pad_length) / 2.0) + pad_solder_mask_clearance + silkscreen_line_width)),
                                (int) (multiplier * (package_body_width / 2.0)),
                                (int) (multiplier * silkscreen_line_width)
                        );
                }
                else
                {
                        create_new_arc
                        (
                                element,
                                (int) (multiplier * (((-package_body_length) / 2.0) - 2 * silkscreen_line_width)),
                                (int) (multiplier * (-package_body_width / 2.0)),
                                (int) (multiplier * 0.5 * silkscreen_line_width),
                                (int) (multiplier * 0.5 * silkscreen_line_width),
                                0,
                                360,
                                (int) (multiplier * silkscreen_line_width)
                        );
                }
        }
        /* Create a courtyard. */
        if (courtyard)
        {
                create_new_line
                (
                        element,
                        (int) (xmin), /* already in mil/100 */
                        (int) (ymin), /* already in mil/100 */
                        (int) (xmin), /* already in mil/100 */
                        (int) (ymax), /* already in mil/100 */
                        (int) (multiplier * courtyard_line_width)
                );
                create_new_line
                (
                        element,
                        (int) (xmax), /* already in mil/100 */
                        (int) (ymin), /* already in mil/100 */
                        (int) (xmax), /* already in mil/100 */
                        (int) (ymax), /* already in mil/100 */
                        (int) (multiplier * courtyard_line_width)
                );
                create_new_line
                (
                        element,
                        (int) (xmin), /* already in mil/100 */
                        (int) (ymin), /* already in mil/100 */
                        (int) (xmax), /* already in mil/100 */
                        (int) (ymin), /* already in mil/100 */
                        (int) (multiplier * courtyard_line_width)
                );
                create_new_line
                (
                        element,
                        (int) (xmax), /* already in mil/100 */
                        (int) (ymax), /* already in mil/100 */
                        (int) (xmin), /* already in mil/100 */
                        (int) (ymax), /* already in mil/100 */
                        (int) (multiplier * courtyard_line_width)
                );
        }
        /* Create attributes. */
        if (attributes_in_footprint)
        {
                element = create_attributes_in_element (element);
        }
        /* We are ready creating an element. */
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("created an element for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
        }
        return (element);
}


/*!
 * \brief Create a list of known CAPM packages.
 *
 * The data in this list can be used in a combobox to select a
 * pre-defined package.
 *
 * \return a list containing all package names of this footprint type
 * known by pcb-fpw.
 */
GList
capm_create_packages_list ()
{
        GList *capm_packages_list = NULL;
        capm_packages_list = g_list_append (capm_packages_list, "CAPM");
        return (*capm_packages_list);
}


/*!
 * \brief Do some Design Rule Checking for the CAPM package type.
 *
 * <ul>
 * <li>check for allowed pad shapes.
 * <li>check for zero sized packages.
 * <li>check for a zero sized courtyard.
 * <li>check for minimum clearance between copper (X-direction).
 * <li>check for minimum clearance between copper (Y-direction).
 * <li>If any fiducials exist:
 * <ul>
 * <li>check for zero fiducial pad diameter.
 * <li>check for zero width solder mask clearance.
 * <li>check for minimum clearance between copper (between pads and fiducials,
 * if any fiducials exist).
 * </ul>
 * <li>check for clearance of the package length with regard to the courtyard
 * dimensions.
 * <li>check for clearance of the package width with regard to the courtyard
 * dimensions.
 * <li>check for any silk lines or texts touching bare copper.
 * <li>check for soldermask clearance (solder mask overlapping copper at the
 * solder fillet area or worse).
 * <li>check for a reasonable silk line width.
 * </ul>
 *
 * \return \c EXIT_SUCCESS when no DRC violations were encountered,
 * \c EXIT_FAILURE when DRC violations were found.
 */
int
capm_drc ()
{
        int result = EXIT_SUCCESS;
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("DRC Check: checking %s package %s."), footprint_name, footprint_type);
        }
        /* Check for number of pads = 2. */
        if (number_of_pins != 2)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for number of pins/pads <> 2."));
                }
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
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: circular pad shape specified for check for allowed pad shapes."));
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                case SQUARE:
                {
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
                return (EXIT_FAILURE);
        }
        /* Check for minimum clearance between copper (X-direction). */
        if (pitch_x - pad_length < pad_clearance)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for minimum clearance between copper (X-direction)."));
                }
                result = EXIT_FAILURE;
        }
        /* Check for minimum clearance between copper (Y-direction). */
        if (pitch_y - pad_width < pad_clearance)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for minimum clearance between copper (Y-direction)."));
                }
                result = EXIT_FAILURE;
        }
        /* Check for fiducials */
        if (fiducial)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for fiducials, package should not have fiducials."));
                }
                result = EXIT_FAILURE;
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
                        _("DRC Check: no errors while checking %s package %s."), footprint_name, footprint_type);
        }
        return result;
}


/*!
 * \brief Look up default values for a CAPM footprint.
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
capm_get_default_footprint_values
(
        gchar *footprint_name
                /*!< : a \c NULL terminated footprint name.*/
)
{
        if (!strcmp (footprint_name, "?CAPM"))
        {
                pitch_y = 0.0;
                number_of_pins = 2;
                package_body_length = 0.0;
                package_body_width = 0.0;
                package_body_height = 0.0;
                package_is_radial = FALSE;
                number_of_columns = 0;
                number_of_rows = 0;
                pitch_x = 0.0;
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
                footprint_name = g_strdup ("CAPM");
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
 * \brief Set GUI constraints for a CAPM package type.
 *
 * This function is only to be compiled for GUI targets.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
#if GUI
int
capm_set_gui_constraints
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
 * \brief Write a footprint with two pads for a CAPM package.
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
capm_write_footprint ()
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
                        "P", /* pad name */
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
                        "N", /* pad name */
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
                        "P", /* pad name */
                        multiplier * (-pitch_x / 2.0), /* x0-coordinate */
                        multiplier * ((pad_width - pad_length) / 2.0), /* y0-coordinate */
                        multiplier * (-pitch_x / 2), /* x1-coordinate */
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
                        "N", /* pad name */
                        multiplier * (pitch_x / 2.0), /* x0-coordinate */
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
        if (silkscreen_package_outline && package_body_width)
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
                if (pad_width >= package_body_width)
                {
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
                else
                {
                        /* lines parallel to X-axis */
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * silkscreen_line_width
                        );
                        /* lines perpendicular to X-axis */
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (((-pad_width - silkscreen_line_width) / 2.0) - pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (((pad_width + silkscreen_line_width) / 2.0) + pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (((-pad_width - silkscreen_line_width) / 2.0) - pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (((pad_width + silkscreen_line_width) / 2.0) + pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                }
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                if (pad_width >= package_body_width)
                {
                        write_element_line
                        (
                                multiplier * (((-pitch_x + pad_length) / 2.0) + pad_solder_mask_clearance + silkscreen_line_width),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (((-pitch_x + pad_length) / 2.0) + pad_solder_mask_clearance + silkscreen_line_width),
                                multiplier * (package_body_width / 2.0),
                                multiplier * silkscreen_line_width
                        );
                }
                else
                {
                        write_element_arc
                        (
                                multiplier * (((-package_body_length) / 2.0) - 2 * silkscreen_line_width),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * 0.5 * silkscreen_line_width,
                                multiplier * 0.5 * silkscreen_line_width,
                                0,
                                360,
                                multiplier * silkscreen_line_width
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
        return (EXIT_SUCCESS);
}


/*!
 * \brief A list containing all CAPM related functions.
 */
static fpw_function_t
capm_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                capm_set_gui_constraints,
                "Set GUI constraints for a CAPM package",
                NULL
        },
#endif /* GUI */
        {
                "Create Element",
                capm_create_element,
                "Create a pcb element for a CAPM package",
                NULL
        },
        {
                "Create Packages List",
                capm_create_packages_list,
                "Create a list of known CAPM packages",
                NULL
        },
        {
                "DRC CAPM Element",
                capm_drc,
                "Design Rule Check for a CAPM package",
                NULL
        },
        {
                "Default Element Values",
                capm_get_default_footprint_values,
                "Get default values for a CAPM package",
                NULL
        },
        {
                "Write footprint",
                capm_write_footprint,
                "Write a footprint for a CAPM package",
                NULL
        }
};


/*!
 * \brief A list containing all CAPM related functions.
 */
REGISTER_FUNCTIONS (capm_function_list)


/*!
 * \brief Initialise by registering all CAPM related functions.
 */
void
capm_init ()
{
        register_capm_function_list ();
}


/* EOF */
