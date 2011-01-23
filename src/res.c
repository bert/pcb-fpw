/*!
 * \file src/res.c
 *
 * \author Copyright 2007, 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Functions for RES footprints.
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
#include "res.h"


/*!
 * \brief Create an Element for a RES package.
 *
 * \return the created \c element.
 */
ElementTypePtr
res_create_element ()
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
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("could not create a valid element pointer for a %s package."),
                                footprint_type);
                }
                return (NULL);
        }
        /* Define the center of our universe and guess for a place where to
         * put the element mark */
        element->MarkX = 0;
        element->MarkY = 0;
        /* Determine (extreme) courtyard dimensions based on pin/pad
         * properties */
        if (pad_shapes_type == ROUND_ELONGATED)
        {
                xmin = multiplier *
                (
                        (-pitch_x / 2.0) -
                        (pad_length / 2.0) -
                        pad_solder_mask_clearance
                );
                xmax = multiplier *
                (
                        (pitch_x / 2.0) +
                        (pad_length / 2.0) +
                        pad_solder_mask_clearance
                );
                ymin = multiplier *
                (
                        (-pitch_y / 2.0) -
                        (pad_width / 2.0) -
                        pad_solder_mask_clearance
                );
                ymax = multiplier *
                (
                        (pitch_y / 2.0) +
                        (pad_width / 2.0) +
                        pad_solder_mask_clearance
                );
        }
        else
        {
                xmin = multiplier *
                (
                        (-pitch_x / 2.0) -
                        (pad_diameter / 2.0) -
                        pad_solder_mask_clearance
                );
                xmax = multiplier *
                (
                        (pitch_x / 2.0) +
                        (pad_diameter / 2.0) +
                        pad_solder_mask_clearance
                );
                ymin = multiplier *
                (
                        (-pitch_y / 2.0) -
                        (pad_diameter / 2.0) -
                        pad_solder_mask_clearance
                );
                ymax = multiplier *
                (
                        (pitch_y / 2.0) +
                        (pad_diameter / 2.0) +
                        pad_solder_mask_clearance
                );
        }
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
        else if (pad_shapes_type == OCTAGONAL)
        {
                pad_flag.f = OCTAGON;
        }
        else
        {
                pad_flag.f = CLEAR;
        }
        create_new_pin
        (
                element,
                (int) (multiplier * ((pitch_x + pad_diameter) / 2.0)), /* x0 coordinate */
                0, /* y0-coordinate */
                (int) (multiplier * pad_diameter), /* pad width */
                (int) (multiplier * pad_clearance), /* clearance */
                (int) (multiplier * (pad_diameter + pad_solder_mask_clearance)), /* solder mask clearance */
                (int) (multiplier * pin_drill_diameter), /* pin drill diameter */
                "", /* pin name */
                "2", /* pin number */
                pad_flag /* flags */
        );
        /* Overrule previous settings in favour of pin 1 square setting */
        if (pin1_square)
        {
                pad_flag.f = SQUARE;
        }
        create_new_pin
        (
                element,
                (int) (multiplier * ((-pitch_x - pad_diameter) / 2.0)), /* x0 coordinate */
                0, /* y0-coordinate */
                (int) (multiplier * pad_diameter), /* pad width */
                (int) (multiplier * pad_clearance), /* clearance */
                (int) (multiplier * (pad_diameter + pad_solder_mask_clearance)), /* solder mask clearance */
                (int) (multiplier * pin_drill_diameter), /* pin drill diameter */
                "", /* pin name */
                "1", /* pin number */
                pad_flag /* flags */
        );
        if (pad_shapes_type == ROUND_ELONGATED)
        {
                /* Add pads on component side */
                pad_flag.f = CLEAR;
                create_new_pad
                (
                        element,
                        (int) (multiplier * ((-pitch_x - pad_length + pad_width) / 2.0)), /* x0 coordinate */
                        0, /* y0-coordinate */
                        (int) (multiplier * ((-pitch_x + pad_length - pad_width) / 2.0)), /* x1 coordinate */
                        0, /* y1-coordinate */
                        (int) (multiplier * pad_width), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        "", /* pin name */
                        "1", /* pin number */
                        pad_flag /* flags */
                );
                create_new_pad
                (
                        element,
                        (int) (multiplier * ((pitch_x + pad_length - pad_width) / 2.0)), /* x0 coordinate */
                        0, /* y0-coordinate */
                        (int) (multiplier * ((pitch_x - pad_length + pad_width) / 2.0)), /* x1 coordinate */
                        0, /* y1-coordinate */
                        (int) (multiplier * pad_width), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        "", /* pin name */
                        "2", /* pin number */
                        pad_flag /* flags */
                );
                /* Add pads on solder side */
                pad_flag.f = ONSOLDER;
                create_new_pad
                (
                        element,
                        (int) (multiplier * ((-pitch_x - pad_length + pad_width) / 2.0)), /* x0 coordinate */
                        0, /* y0-coordinate */
                        (int) (multiplier * ((-pitch_x + pad_length - pad_width) / 2.0)), /* x1 coordinate */
                        0, /* y1-coordinate */
                        (int) (multiplier * pad_width), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        "", /* pin name */
                        "1", /* pin number */
                        pad_flag /* flags */
                );
                create_new_pad
                (
                        element,
                        (int) (multiplier * ((pitch_x + pad_length - pad_width) / 2.0)), /* x0 coordinate */
                        0, /* y0-coordinate */
                        (int) (multiplier * ((pitch_x - pad_length + pad_width) / 2.0)), /* x1 coordinate */
                        0, /* y1-coordinate */
                        (int) (multiplier * pad_width), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        "", /* pin name */
                        "2", /* pin number */
                        pad_flag /* flags */
                );
        }
        /* Create a package body on the silkscreen. */
        if (silkscreen_package_outline)
        {
                create_new_line
                (
                        element,
                        (int) (multiplier * (-package_body_length / 2.0)),
                        (int) (multiplier * (-package_body_width / 2.0)),
                        (int) (multiplier * (-package_body_length / 2.0)),
                        (int) (multiplier * (package_body_width / 2.0)),
                        (int) (multiplier * silkscreen_line_width)
                );
                create_new_line
                (
                        element,
                        (int) (multiplier * (package_body_length / 2.0)),
                        (int) (multiplier * (-package_body_width / 2.0)),
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
                create_new_line
                (
                        element,
                        (int) (multiplier * (package_body_length / 2.0)),
                        (int) (multiplier * (package_body_width / 2.0)),
                        (int) (multiplier * (-package_body_length / 2.0)),
                        (int) (multiplier * (package_body_width / 2.0)),
                        (int) (multiplier * silkscreen_line_width)
                );
                /* Now draw some leads if available real estate allows for it. */
                if (package_body_length < ((pitch_x - pad_diameter - pad_solder_mask_clearance) / 2.0) - silkscreen_line_width)
                {
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (package_body_length / 2.0)),
                                0,
                                (int) ((multiplier * (pitch_x - pad_diameter - pad_solder_mask_clearance) / 2.0) - silkscreen_line_width),
                                0,
                                (int) (multiplier * silkscreen_line_width)
                        );
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (-package_body_length / 2.0)),
                                0,
                                (int) ((multiplier * (-pitch_x + pad_diameter + pad_solder_mask_clearance) / 2.0) + silkscreen_line_width),
                                0,
                                (int) (multiplier * silkscreen_line_width)
                        );
                }
        }
        /* Create a pin #1 marker on the silkscreen. */
        if (silkscreen_indicate_1)
        {
                /* package has no pin/pad #1 indication */
        }
        /* Create a courtyard outline on the silkscreen. */
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
 * \brief Create a list of RES packages with pre-defined values.
 *
 * The data in this list can be used in a combo box to select a
 * pre-defined package.
 *
 * \return a list containing all package names of this footprint type
 * known by pcb-fpw.
 */
GList
res_create_packages_list (GList *res_packages_list)
{
        res_packages_list = g_list_append (res_packages_list, "RES600-320X170");
        res_packages_list = g_list_append (res_packages_list, "RES770-420X200");
        res_packages_list = g_list_append (res_packages_list, "RES1030-640X250");
        res_packages_list = g_list_append (res_packages_list, "RES1130-700X280");
        res_packages_list = g_list_append (res_packages_list, "RES1190-800X300");
        res_packages_list = g_list_append (res_packages_list, "RES1390-1000X350");
        res_packages_list = g_list_append (res_packages_list, "RES1440-1050X200");
        res_packages_list = g_list_append (res_packages_list, "RES1670-1200X400");
        res_packages_list = g_list_append (res_packages_list, "RES1680-1200X500");
        return (*res_packages_list);
}


/*!
 * \brief Do some Design Rule Checking for the RES package type.
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
res_drc ()
{
        int result = EXIT_SUCCESS;
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        (_("[%s] DRC Check: checking package %s.")),
                        footprint_type, footprint_name);
        }
        /* Check for allowed pad shapes. */
        switch (pad_shapes_type)
        {
                case NO_SHAPE:
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        (_("[%s] DRC Error: NO_SHAPE specified for check for allowed pad shapes.")),
                                        footprint_type);
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
                        break;
                }
                case OCTAGONAL:
                {
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
                                        (_("[%s] DRC Error: no valid pad shape type specified.")),
                                        footprint_type);
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
                                (_("[%s] DRC Error: check for package body length is <= 0.0.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        if (package_body_width <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: check for package body width is <= 0.0.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        if (package_body_height <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: check for package body height is <= 0.0.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        /* Check for a zero sized courtyard. */
        if (courtyard_length <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: check for courtyard length is <= 0.0.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        if (courtyard_width <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: check for courtyard width is <= 0.0.")),
                                footprint_type);
                }
                return (EXIT_FAILURE);
        }
        /* Check for minimum clearance between copper (X-direction). */
        if ((pitch_x - pad_length < pad_clearance) || (pitch_x - pad_diameter < pad_clearance))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: check for minimum clearance between copper (X-direction).")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        /* Check for pitch in Y-direction is smaller or equal 0.0 */
        if (pitch_y <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: pitch in Y-direction should be 0.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        /* Check for fiducials. */
        if (fiducial)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: check for fiducial set to TRUE, package has no fiducials.")),
                                footprint_type);
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
                                (_("[%s] DRC Error: check for clearance of the package length with regard to the courtyard dimensions.")),
                                footprint_type);
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
                                (_("[%s] DRC Error: check for clearance of the package width with regard to the courtyard dimensions.")),
                                footprint_type);
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
                                (_("[%s] DRC Error: line width 0.0 specified for check for a reasonable silk line width.")),
                                footprint_type);
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
                                        (_("[%s] DRC Error: no units specified for check for a reasonable silk line width.")),
                                        footprint_type);
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
                                        (_("[%s] DRC Error: line width > 40.0 mil specified check for a reasonable silk line width.")),
                                        footprint_type);
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
                                        (_("[%s] DRC Error: line width > 40.0 mil specified check for a reasonable silk line width.")),
                                        footprint_type);
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
                                        (_("[%s] DRC Error: line width > 1.0 mm specified check for a reasonable silk line width.")),
                                        footprint_type);
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                default:
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        (_("[%s] DRC Error: no valid units type specified for check for a reasonable silk line width.")),
                                        footprint_type);
                        }
                        result = EXIT_FAILURE;
                        break;
                }
        }
        /* No failures on DRC found. */
        if (verbose || (result == EXIT_SUCCESS))
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        (_("[%s] DRC Check: no errors while checking package %s.")),
                        footprint_type, footprint_name);
        }
        return result;
}


/*!
 * \brief Look up default values for RES footprint.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised known values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - RES600-320X170,
 * - RES770-420X200,
 * - RES1030-640X250.
 *
 * \return \c EXIT_SUCCESS when default values for a footprint were
 * found, \c EXIT_FAILURE when the footprint name was not found.
 */
int
res_get_default_footprint_values
(
        gchar *footprint_name)
{
        if (!strcmp (footprint_name, "?RES600-320X170"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.20;
                package_body_width = 1.70;
                package_body_height = 1.70;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 2;
                number_of_rows = 1;
                pitch_x = 6.00;
                pitch_y = 0.00;
                count_x = 0;
                count_y = 0;
                pad_diameter = 1.52;
                pad_length = 0.00;
                pad_width = 0.00;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 1.00;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 3.20;
                silkscreen_width = 1.70;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = pitch_x + pad_diameter + pad_solder_mask_clearance;
                courtyard_width = 1.70;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("RES600-320X170");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?RES770-420X200"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 4.20;
                package_body_width = 2.00;
                package_body_height = 2.00;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 2;
                number_of_rows = 1;
                pitch_x = 7.70;
                pitch_y = 0.00;
                count_x = 0;
                count_y = 0;
                pad_diameter = 1.52;
                pad_length = 0.00;
                pad_width = 0.00;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 1.00;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 4.20;
                silkscreen_width = 2.00;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = pitch_x + pad_diameter + pad_solder_mask_clearance;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("RES770-420X200");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?RES1030-640X250"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 6.40;
                package_body_width = 2.50;
                package_body_height = 2.50;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 2;
                number_of_rows = 1;
                pitch_x = 10.30;
                pitch_y = 0.00;
                count_x = 0;
                count_y = 0;
                pad_diameter = 1.52;
                pad_length = 0.00;
                pad_width = 0.00;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 1.00;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 6.40;
                silkscreen_width = 2.50;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = pitch_x + pad_diameter + pad_solder_mask_clearance;
                courtyard_width = 2.50;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("RES1030-640X250");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?RES1130-700X280"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 7.00;
                package_body_width = 2.80;
                package_body_height = 2.80;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 2;
                number_of_rows = 1;
                pitch_x = 11.30;
                pitch_y = 0.00;
                count_x = 0;
                count_y = 0;
                pad_diameter = 1.52;
                pad_length = 0.00;
                pad_width = 0.00;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 1.00;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 7.00;
                silkscreen_width = 2.80;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = pitch_x + pad_diameter + pad_solder_mask_clearance;
                courtyard_width = 2.80;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("RES1130-700X280");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?RES1190-800X300"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 8.00;
                package_body_width = 3.00;
                package_body_height = 3.00;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 2;
                number_of_rows = 1;
                pitch_x = 11.90;
                pitch_y = 0.00;
                count_x = 0;
                count_y = 0;
                pad_diameter = 1.52;
                pad_length = 0.00;
                pad_width = 0.00;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 1.00;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 8.00;
                silkscreen_width = 3.00;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = pitch_x + pad_diameter + pad_solder_mask_clearance;
                courtyard_width = 3.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("RES1190-800X300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?RES1390-1000X350"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 10.00;
                package_body_width = 3.50;
                package_body_height = 3.50;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 2;
                number_of_rows = 1;
                pitch_x = 13.90;
                pitch_y = 0.00;
                count_x = 0;
                count_y = 0;
                pad_diameter = 1.52;
                pad_length = 0.00;
                pad_width = 0.00;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 1.00;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 10.00;
                silkscreen_width = 3.50;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = pitch_x + pad_diameter + pad_solder_mask_clearance;
                courtyard_width = 3.50;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("RES1390-1000X350");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?RES1440-1050X200"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 10.50;
                package_body_width = 2.00;
                package_body_height = 2.00;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 2;
                number_of_rows = 1;
                pitch_x = 14.40;
                pitch_y = 0.00;
                count_x = 0;
                count_y = 0;
                pad_diameter = 1.52;
                pad_length = 0.00;
                pad_width = 0.00;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 1.00;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 10.50;
                silkscreen_width = 2.00;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = pitch_x + pad_diameter + pad_solder_mask_clearance;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("RES1440-1050X200");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?RES1670-1200X400"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 12.00;
                package_body_width = 4.00;
                package_body_height = 4.00;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 2;
                number_of_rows = 1;
                pitch_x = 16.70;
                pitch_y = 0.00;
                count_x = 0;
                count_y = 0;
                pad_diameter = 1.52;
                pad_length = 0.00;
                pad_width = 0.00;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 1.00;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 12.00;
                silkscreen_width = 4.00;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = pitch_x + pad_diameter + pad_solder_mask_clearance;
                courtyard_width = 4.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("RES1670-1200X400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?RES1680-1200X500"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 12.00;
                package_body_width = 5.00;
                package_body_height = 5.00;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 2;
                number_of_rows = 1;
                pitch_x = 16.80;
                pitch_y = 0.00;
                count_x = 0;
                count_y = 0;
                pad_diameter = 1.52;
                pad_length = 0.00;
                pad_width = 0.00;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 1.00;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 12.00;
                silkscreen_width = 5.00;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = pitch_x + pad_diameter + pad_solder_mask_clearance;
                courtyard_width = 5.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("RES1680-1200X500");
                return (EXIT_SUCCESS);
        }
        else
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("default values for footprint %s not found.\n"),
                                footprint_name);
                }
                return (EXIT_FAILURE);
        }
}


#if GUI
/*!
 * \brief Set GUI constraints for the RES package type.
 *
 * This function is only to be compiled for GUI targets.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
res_set_gui_constraints (GtkWidget *widget)
{
        /* Widgets on tab "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab "Pins/Pads" */
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_columns_entry), "2");
        gtk_widget_set_sensitive (number_of_columns_entry, FALSE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_rows_entry), "1");
        gtk_widget_set_sensitive (number_of_rows_entry, TRUE);
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
        gtk_combo_box_set_active (GTK_COMBO_BOX (number_1_position_entry), UPPER_LEFT);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);

        /* Widgets on tab "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
        return (EXIT_SUCCESS);
}
#endif /* GUI */


/*!
 * \brief Write a TH footprint for a RES package.
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
res_write_footprint ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gchar *pin_pad_flags = g_strdup ("");

        /* Attempt to open a file with write permission. */
        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("could not open file for %s footprint: %s."),
                                footprint_type, footprint_filename);
                }
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
        if (pad_shapes_type == ROUND_ELONGATED)
        {
                xmin = multiplier *
                (
                        (-pitch_x / 2.0) -
                        (pad_length / 2.0) -
                        pad_solder_mask_clearance
                );
                xmax = multiplier *
                (
                        (pitch_x / 2.0) +
                        (pad_length / 2.0) +
                        pad_solder_mask_clearance
                );
                ymin = multiplier *
                (
                        (-pitch_y / 2.0) -
                        (pad_width / 2.0) -
                        pad_solder_mask_clearance
                );
                ymax = multiplier *
                (
                        (pitch_y / 2.0) +
                        (pad_width / 2.0) +
                        pad_solder_mask_clearance
                );
        }
        else
        {
                xmin = multiplier *
                (
                        (-pitch_x / 2.0) -
                        (pad_diameter / 2.0) -
                        pad_solder_mask_clearance
                );
                xmax = multiplier *
                (
                        (pitch_x / 2.0) +
                        (pad_diameter / 2.0) +
                        pad_solder_mask_clearance
                );
                ymin = multiplier *
                (
                        (-pitch_y / 2.0) -
                        (pad_diameter / 2.0) -
                        pad_solder_mask_clearance
                );
                ymax = multiplier *
                (
                        (pitch_y / 2.0) +
                        (pad_diameter / 2.0) +
                        pad_solder_mask_clearance
                );
        }
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
        if (pad_shapes_type == SQUARE)
        {
                pin_pad_flags = g_strdup ("square");
        }
        else if (pad_shapes_type == OCTAGONAL)
        {
                pin_pad_flags = g_strdup ("octagon");
        }
        else
        {
                pin_pad_flags = g_strdup ("");
        }
        write_pin
        (
                2, /* pin number */
                "", /* pin name */
                multiplier * ((pitch_x + pad_diameter) / 2.0), /* x0 coordinate */
                0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        /* Overrule previous settings in favour of pin 1 square setting */
        if (pin1_square)
        {
                pin_pad_flags = g_strdup ("square");
        }
        write_pin
        (
                1, /* pin number */
                "", /* pin name */
                multiplier * ((-pitch_x - pad_diameter) / 2.0), /* x0 coordinate */
                0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        if (pad_shapes_type == ROUND_ELONGATED)
        {
                /* Add pads on component side */
                pin_pad_flags = g_strdup ("");
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
                        pin_pad_flags /* flags */
                );
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
                        multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
                /* Add pads on solder side */
                pin_pad_flags = g_strdup ("onsolder");
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
                        pin_pad_flags /* flags */
                );
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
                        multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
        }
        /* Write package body on silkscreen */
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
                /* Now draw some leads if available real estate allows for it. */
                if (package_body_length < ((pitch_x - pad_diameter - pad_solder_mask_clearance) / 2.0) - silkscreen_line_width)
                {
                        write_element_line
                        (
                                multiplier * (package_body_length / 2.0),
                                0,
                                multiplier * (((pitch_x - pad_diameter - pad_solder_mask_clearance) / 2.0) - silkscreen_line_width),
                                0,
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                0,
                                multiplier * (((-pitch_x + pad_diameter + pad_solder_mask_clearance) / 2.0) + silkscreen_line_width),
                                0,
                                multiplier * silkscreen_line_width
                        );
                }
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
 * \brief A list containing all RES related functions.
 */
static fpw_function_t
res_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                res_set_gui_constraints,
                "Set GUI constraints for a RES package",
                NULL
        },
#endif /* GUI */
        {
                "Create element",
                res_create_element,
                "Create an element for a RES package",
                NULL
        },
        {
                "Packages list",
                res_create_packages_list,
                "Create a list of known RES packages",
                NULL
        },
        {
                "DRC ? Element",
                res_drc,
                "Design Rule Check for a RES package",
                NULL
        },
        {
                "Default Element Values",
                res_get_default_footprint_values,
                "Get default values for a selected RES package",
                NULL
        },
        {
                "Write footprint",
                res_write_footprint,
                "Write a footprint for a RES package",
                NULL
        }
};


/*!
 * \brief A list containing all ? related functions.
 */
REGISTER_FUNCTIONS (res_function_list)


/*!
 * \brief Initialise by registering all ? related functions.
 */
void
res_init ()
{
        register_res_function_list ();
}


/* EOF */
