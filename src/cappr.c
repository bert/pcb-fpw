/*!
 * \file src/cappr.c
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Functions for CAPPR footprints (Through Hole Polarized Radial Capacitors).
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
#include "cappr.h"


/*!
 * \brief Create an Element for a CAPPR package.
 *
 * \return \c EXIT_SUCCESS when an element was created,
 * \c EXIT_FAILURE when errors were encountered.
 */
int
cappr_create_element ()
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
                                (_("[%s] could not create a valid element pointer for an element.")),
                                footprint_type);
                }
                return (EXIT_FAILURE);
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
                "N", /* pin name */
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
                "P", /* pin name */
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
                        "P", /* pin name */
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
                        "N", /* pin name */
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
                        "P", /* pin name */
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
                        "N", /* pin name */
                        "2", /* pin number */
                        pad_flag /* flags */
                );
        }
        /* Create a package body on the silkscreen. */
        if (silkscreen_package_outline)
        {
                if (package_is_radial)
                {
                        create_new_arc
                        (
                                element,
                                0, /* x coordinate */
                                0, /* y coordinate */
                                (int) (multiplier * package_body_length), /* width */
                                (int) (multiplier * package_body_length), /* height */
                                0, /* start angle */
                                360, /* delta angle */
                                (int) (multiplier * silkscreen_line_width)
                        );
                }
                else
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
                }
        }
        /* Create a pin #1 marker on the silkscreen. */
        if (silkscreen_indicate_1)
        {
                /* Draw a polarity indicator. */
                if (package_body_length < ((pitch_x - pad_diameter - pad_solder_mask_clearance) / 2.0) - silkscreen_line_width)
                {
                        create_new_line /* Horizontal line. */
                        (
                                element,
                                (int) (multiplier * ((-pitch_x / 2.0) - (3 * silkscreen_line_width))),
                                (int) (multiplier * (((-pad_diameter - pad_solder_mask_clearance) / 2.0) - (3 * silkscreen_line_width))),
                                (int) (multiplier * ((-pitch_x / 2.0) + (3 * silkscreen_line_width))),
                                (int) (multiplier * (((-pad_diameter - pad_solder_mask_clearance) / 2.0) - (3 * silkscreen_line_width))),
                                (int) (multiplier * silkscreen_line_width)
                        );
                        create_new_line /* Vertical line. */
                        (
                                element,
                                (int) (multiplier * (-pitch_x / 2.0)),
                                (int) (multiplier * (((-pad_diameter - pad_solder_mask_clearance) / 2.0) - (silkscreen_line_width))),
                                (int) (multiplier * (-pitch_x / 2.0)),
                                (int) (multiplier * (((-pad_diameter - pad_solder_mask_clearance) / 2.0) - (6 * silkscreen_line_width))),
                                (int) (multiplier * silkscreen_line_width)
                        );
                }
        }
        /* Create a courtyard outline on the silkscreen. */
        if (courtyard)
        {
                if (package_is_radial)
                {
                        create_new_arc
                        (
                                element,
                                0, /* x coordinate */
                                0, /* y coordinate */
                                (int) (2 * xmax), /* width, already in mil/100 */
                                (int) (2 * ymax), /* height, already in mil/100 */
                                0, /* start angle */
                                360, /* delta angle */
                                (int) (multiplier * courtyard_line_width)
                        );
                }
                else
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
                        (_("[%s] created an element for element: %s.")),
                        footprint_type,
                        footprint_filename);
        }
        current_element = (ElementTypePtr) &element;
        return (EXIT_SUCCESS);
}


/*!
 * \brief Create a list of known CAPPR packages.
 *
 * The data in this list can be used in a combo box to select a
 * pre-defined package.
 *
 * \return \c EXIT_SUCCESS when a packages list was created,
 * \c EXIT_FAILURE when errors were encountered.
 */
int
cappr_create_packages_list ()
{
        g_list_free (packages_list);
        packages_list = g_list_append (packages_list, "CAPPR");
        return (EXIT_SUCCESS);
}


/*!
 * \brief Do some Design Rule Checking for the CAPPR package type.
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
cappr_drc ()
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
                                (_("[%s] DRC Error: specified package body length is too small.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        if (package_body_width <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: specified package body width is too small.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        if (package_body_height <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: specified package body height is too small.")),
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
                                (_("[%s] DRC Error: specified courtyard length is too small.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        if (courtyard_width <= 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: specified courtyard width is too small.")),
                                footprint_type);
                }
                return (EXIT_FAILURE);
        }
        /* Check for minimum clearance between copper (X-direction). */
        if ((pitch_x - pad_diameter < pad_clearance) 
                || (pitch_x - pad_length < pad_clearance))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: minimum clearance between copper (X-direction) is too small.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        /* Check for pitch in Y-direction to be 0.0 */
        if (pitch_y != 0.0)
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
                                (_("[%s] DRC Error: package should not have a fiducial pad.")),
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
        if (silkscreen_package_outline && (silkscreen_line_width == 0.0))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: silkscreen line width is too small.")),
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
                                        (_("[%s] DRC Error: no units specified.")),
                                        footprint_type);
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                case MIL:
                if (silkscreen_package_outline && (silkscreen_line_width > 40.0))
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        (_("[%s] DRC Error: silkscreen line width too wide.")),
                                        footprint_type);
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                case MIL_100:
                if (silkscreen_package_outline && (silkscreen_line_width > 4000.0))
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        (_("[%s] DRC Error: silkscreen line width too wide.")),
                                        footprint_type);
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                case MM:
                if (silkscreen_package_outline && (silkscreen_line_width > 1.0))
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        (_("[%s] DRC Error: silkscreen line width too wide.")),
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
                                        (_("[%s] DRC Error: no valid units type specified.")),
                                        footprint_type);
                        }
                        result = EXIT_FAILURE;
                        break;
                }
        }
        /* No failures on DRC found. */
        if (verbose && (result == EXIT_SUCCESS))
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        (_("[%s] DRC Check: no errors while checking package %s.")),
                        footprint_type, footprint_name);
        }
        return result;
}


/*!
 * \brief Look up default values for CAPPR footprint.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised known values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - CAPPR,
 * - .
 *
 * \return \c EXIT_SUCCESS when default values for a footprint were
 * found, \c EXIT_FAILURE when the footprint name was not found.
 */
int
cappr_get_default_footprint_values ()
{
        if (!strcmp (footprint_name, "?CAPPR"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 0.0;
                package_body_width = 0.0;
                package_body_height = 0.0;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 2;
                number_of_rows = 1;
                pitch_x = 0.0;
                pitch_y = 0.0;
                count_x = 0;
                count_y = 0;
                pad_diameter = 0.0;
                pin_drill_diameter = 0.0;
                pad_length = 0.0;
                pad_width = 0.0;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 0.0;
                silkscreen_width = 0.0;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = 0.00;
                courtyard_width = 0.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPPR");
                return (EXIT_SUCCESS);
        }
        else
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                         (_("default values for footprint %s not found.\n")),
                         footprint_name);
                return (EXIT_FAILURE);
        }
}


#if GUI
/*!
 * \brief Set GUI constraints for the CAPPR package type.
 *
 * This function is only to be compiled for GUI targets.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
cappr_set_gui_constraints ()
{
        /* Widgets on tab "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), TRUE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, TRUE);

        /* Widgets on tab "Pins/Pads" */
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_columns_entry), "2");
        gtk_widget_set_sensitive (number_of_columns_entry, FALSE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_rows_entry), "");
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
 * \brief Write a TH footprint for a CAPPR package.
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
cappr_write_footprint ()
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
                g_log ("", G_LOG_LEVEL_WARNING,
                        (_("could not open file for %s footprint: %s.")),
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
                "N", /* pin name */
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
                "P", /* pin name */
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
                        "P", /* pad name */
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
                        "N", /* pad name */
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
                        "P", /* pad name */
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
                        "N", /* pad name */
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
                fprintf (fp, (_("# Write a package body on the silkscreen\n")));
                if (package_is_radial)
                {
                        
                        write_element_arc
                        (
                                0, /* x coordinate */
                                0, /* y coordinate */
                                multiplier * package_body_length, /* width */
                                multiplier * package_body_length, /* height */
                                0, /* start angle */
                                360, /* delta angle */
                                multiplier * silkscreen_line_width
                        );
                }
                else
                {
                        write_rectangle
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * silkscreen_line_width
                        );
                }
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                /* Draw a polarity indicator. */
                if (package_body_length < ((pitch_x - pad_diameter - pad_solder_mask_clearance) / 2.0) - silkscreen_line_width)
                {
                        write_element_line /* Horizontal line. */
                        (
                                multiplier * ((-pitch_x / 2.0) - (3 * silkscreen_line_width)),
                                multiplier * (((-pad_diameter - pad_solder_mask_clearance) / 2.0) - (3 * silkscreen_line_width)),
                                multiplier * ((-pitch_x / 2.0) + (3 * silkscreen_line_width)),
                                multiplier * (((-pad_diameter - pad_solder_mask_clearance) / 2.0) - (3 * silkscreen_line_width)),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line /* Vertical line. */
                        (
                                multiplier * (-pitch_x / 2.0),
                                multiplier * (((-pad_diameter - pad_solder_mask_clearance) / 2.0) - (silkscreen_line_width)),
                                multiplier * (-pitch_x / 2.0),
                                multiplier * (((-pad_diameter - pad_solder_mask_clearance) / 2.0) - (6 * silkscreen_line_width)),
                                multiplier * silkscreen_line_width
                        );
                }
        }
        /* Write a courtyard on the silkscreen */
        if (courtyard)
        {
                fprintf (fp, (_("# Write a courtyard on the silkscreen\n")));
                if (package_is_radial)
                {
                        write_element_arc
                        (
                                0, /* x coordinate */
                                0, /* y coordinate */
                                2 * xmax, /* width, already in mil/100 */
                                2 * ymax, /* height, already in mil/100 */
                                0, /* start angle */
                                360, /* delta angle */
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
                        (_("wrote a footprint for a %s package: %s.")),
                        footprint_type,
                        footprint_filename);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief A list containing all CAPPR related functions.
 */
static fpw_function_t
cappr_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                cappr_set_gui_constraints,
                "Set GUI constraints for a CAPPR package",
                NULL
        },
#endif /* GUI */
        {
                "Create element",
                cappr_create_element,
                "Create an element for a CAPPR package",
                NULL
        },
        {
                "Packages list",
                cappr_create_packages_list,
                "Create a list of known CAPPR packages",
                NULL
        },
        {
                "DRC CAPPR Element",
                cappr_drc,
                "Design Rule Check for a CAPPR package",
                NULL
        },
        {
                "Default Element Values",
                cappr_get_default_footprint_values,
                "Get default values for a selected CAPPR package",
                NULL
        },
        {
                "Write footprint",
                cappr_write_footprint,
                "Write a footprint for a CAPPR package",
                NULL
        }
};


/*!
 * \brief A list containing all CAPPR related functions.
 */
REGISTER_FUNCTIONS (cappr_function_list)


/*!
 * \brief Initialise by registering all CAPPR related functions.
 */
void
cappr_init ()
{
        register_cappr_function_list ();
}


/* EOF */
