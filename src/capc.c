/*!
 * \file src/capc.c
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Functions for CAPC footprints
 * (Surface Mount Technology Chip Capacitor).
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
#include "capc.h"

/*!
 * \brief Create an Element for a CAPC package.
 *
 * \return the created \c element.
 */
ElementTypePtr
capc_create_element ()
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
                                (_("[%s] could not create a valid element pointer for an element.")),
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
                        "", /* pin name */
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
                        "", /* pin name */
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
                        "", /* pin name */
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
                        "", /* pin name */
                        "1", /* pin number */
                        pad_flag /* flags */
                );
        }
        /* Create a package body. */
        if (silkscreen_package_outline && package_body_width)
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
        /* Create a pin #1 marker. */
        if (silkscreen_indicate_1)
        {
                /* package has no pin/pad #1 indication */
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
                        (_("[%s] created an element for element: %s.")),
                        footprint_type,
                        footprint_filename);
        }
        return (element);
}


/*!
 * \brief Create a list of known CAPC packages.
 *
 * The data in this list can be used in a combobox to select a
 * pre-defined package.
 *
 * \return a list containing all package names of this footprint type
 * known by pcb-fpw.
 */
GList
capc_create_packages_list ()
{
        GList *capc_packages_list = NULL;
        capc_packages_list = g_list_append (capc_packages_list, "CAPC0603X33N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC0816X61N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1005X55N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1005X56N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1005X60N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1220X107N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1320X76N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1508X65N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1608X55N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1608X86N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1608X87N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1608X90N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1608X92N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1608X95N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1632X76N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC1632X168N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X100N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X100AN");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X120N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X127N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X130N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X135N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X140N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X145N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X145AN");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X70N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X71N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X88N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X90N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X94N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2012X95N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC2013X140N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC3215X168N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC3216X105N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC3216X125N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC3216X127N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC3216X130N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC3216X130AN");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC3216X140N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC3216X152N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC3216X175N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC3216X178N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC3216X180N");
        capc_packages_list = g_list_append (capc_packages_list, "CAPC3216X105L");
        return (*capc_packages_list);
}


/*!
 * \brief Do some Design Rule Checking for the CAPC package type.
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
capc_drc ()
{
        int result = EXIT_SUCCESS;
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        (_("[%s] DRC Check: checking package %s.")),
                        footprint_type, footprint_name);
        }
        /* Check for number of pads = 2. */
        if (number_of_pins != 2)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: check for number of pins/pads <> 2.")),
                                footprint_type);
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
                                        (_("[%s] DRC Error: NO_SHAPE specified for check for allowed pad shapes.")),
                                        footprint_type);
                        }
                        result = EXIT_FAILURE;
                        break;
                }
                case ROUND:
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        (_("[%s] DRC Error: circular pad shape specified for check for allowed pad shapes.")),
                                        footprint_type);
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
                                        (_("[%s] DRC Error: octagonal pad shape specified for check for allowed pad shapes.")),
                                        footprint_type);
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
        if (pitch_x - pad_length < pad_clearance)
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
        /* Check for fiducials */
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
        if (silkscreen_package_outline || (silkscreen_line_width == 0.0))
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
                if (silkscreen_line_width > 40.0)
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
                if (silkscreen_line_width > 4000.0)
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
                if (silkscreen_line_width > 1.0)
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
        if (verbose || (result == EXIT_SUCCESS))
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        (_("[%s] DRC Check: no errors while checking package %s.")),
                        footprint_type, footprint_name);
        }
        return result;
}


/*!
 * \brief Look up default values for CAPC footprints.
 *
 * Footprint values can be looked up by placing a question mark "?" in
 * front of the footprint name.\n
 * If the footprint name is recognised known values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - CAPC0603X33N,
 * - CAPC0816X61N,
 * - CAPC1005X55N,
 * - CAPC1005X56N,
 * - CAPC1005X60N,
 * - CAPC1220X107N,
 * - CAPC1320X76N,
 * - CAPC1508X65N,
 * - CAPC1608X55N,
 * - CAPC1608X86N,
 * - CAPC1608X87N,
 * - CAPC1608X90N,
 * - CAPC1608X92N,
 * - CAPC1608X95N,
 * - CAPC1632X76N,
 * - CAPC1632X168N,
 * - CAPC2012X100N,
 * - CAPC2012X100AN,
 * - CAPC2012X120N,
 * - CAPC2012X127N,
 * - CAPC2012X130N,
 * - CAPC2012X135N,
 * - CAPC2012X140N,
 * - CAPC2012X145N,
 * - CAPC2012X145AN,
 * - CAPC2012X70N,
 * - CAPC2012X71N,
 * - CAPC2012X88N,
 * - CAPC2012X90N,
 * - CAPC2012X94N,
 * - CAPC2012X95N,
 * - CAPC2013X140N,
 * - CAPC3215X168N,
 * - CAPC3216X105N,
 * - CAPC3216X125N,
 * - CAPC3216X127N,
 * - CAPC3216X130N,
 * - CAPC3216X130AN,
 * - CAPC3216X140N,
 * - CAPC3216X152N,
 * - CAPC3216X175N,
 * - CAPC3216X178N,
 * - CAPC3216X180N,
 * - CAPC3216X105L.
 *
 * \return EXIT_SUCCESS when default values for a footprint were found,
 * \c EXIT_FAILURE when the footprint name was not found.
 */
int
capc_get_default_footprint_values
(
        gchar *footprint_name
                /*!< : a \c NULL terminated footprint name.*/
)
{
        if (!strcmp (footprint_name, "?CAPC0603X33N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 0.63;
                package_body_width = 0.30;
                package_body_height = 0.33;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 0.66;
                pitch_y = 0.0;
                pad_length = 0.46;
                pad_width = 0.42;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 1.42;
                courtyard_width = 0.72;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC0603X33N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " EIA 0201, metric 0603.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: pads are being trimmed.")), footprint_name);
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC0816X61N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 0.96;
                package_body_width = 1.75;
                package_body_height = 0.61;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 0.80;
                pitch_y = 0.0;
                pad_length = 0.60;
                pad_width = 1.78;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 1.70;
                courtyard_width = 2.08;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC0816X61N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " EIA 0306, metric 0816.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: pads are being trimmed.")), footprint_name);
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1005X55N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.05;
                package_body_width = 0.55;
                package_body_height = 0.55;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 0.90;
                pitch_y = 0.0;
                pad_length = 0.62;
                pad_width = 0.62;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 1.82;
                courtyard_width = 0.92;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1005X55N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0402, metric 1005.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1005X56N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.10;
                package_body_width = 0.50;
                package_body_height = 0.56;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 0.96;
                pitch_y = 0.0;
                pad_length = 0.59;
                pad_width = 0.64;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 1.86;
                courtyard_width = 0.94;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1005X56N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0402, metric 1005.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1005X60N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.10;
                package_body_width = 0.60;
                package_body_height = 0.60;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 0.98;
                pitch_y = 0.0;
                pad_length = 0.58;
                pad_width = 0.66;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 1.86;
                courtyard_width = 0.96;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1005X60N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0402, metric 1005.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1220X107N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.45;
                package_body_width = 2.20;
                package_body_height = 1.07;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.10;
                pitch_y = 0.0;
                pad_length = 0.77;
                pad_width = 2.22;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 2.18;
                courtyard_width = 2.52;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1220X107N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0508, metric 1220.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1320X76N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.52;
                package_body_width = 2.25;
                package_body_height = 0.76;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.10;
                pitch_y = 0.0;
                pad_length = 0.84;
                pad_width = 2.27;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 2.24;
                courtyard_width = 2.58;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1320X76N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0508, metric 1220.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1508X65N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.72;
                package_body_width = 1.00;
                package_body_height = 0.65;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.18;
                pitch_y = 0.0;
                pad_length = 0.97;
                pad_width = 1.02;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 2.46;
                courtyard_width = 1.32;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1508X65N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0603, metric 1608.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: pads are being trimmed.")), footprint_name);
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1608X55N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.70;
                package_body_width = 0.90;
                package_body_height = 0.55;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.50;
                pitch_y = 0.0;
                pad_length = 0.90;
                pad_width = 0.95;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 2.90;
                courtyard_width = 1.50;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1608X55N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0603, metric 1608.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1608X86N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.75;
                package_body_width = 0.96;
                package_body_height = 0.86;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.60;
                pitch_y = 0.0;
                pad_length = 0.95;
                pad_width = 1.00;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.10;
                courtyard_width = 1.50;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1608X86N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0603, metric 1608.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1608X87N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.75;
                package_body_width = 0.95;
                package_body_height = 0.87;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.60;
                pitch_y = 0.0;
                pad_length = 0.95;
                pad_width = 1.00;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.10;
                courtyard_width = 1.50;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1608X87N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0603, metric 1608.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1608X90N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.75;
                package_body_width = 0.95;
                package_body_height = 0.90;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.60;
                pitch_y = 0.0;
                pad_length = 0.95;
                pad_width = 1.00;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.10;
                courtyard_width = 1.50;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1608X90N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0603, metric 1608.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1608X92N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.72;
                package_body_width = 0.92;
                package_body_height = 0.92;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.60;
                pitch_y = 0.0;
                pad_length = 0.90;
                pad_width = 0.92;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.00;
                courtyard_width = 1.50;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1608X92N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0603, metric 1608.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1608X95N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.75;
                package_body_width = 0.95;
                package_body_height = 0.95;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.60;
                pitch_y = 0.0;
                pad_length = 0.95;
                pad_width = 1.00;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.10;
                courtyard_width = 1.50;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1608X95N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0603, metric 1608.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1632X76N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.85;
                package_body_width = 3.45;
                package_body_height = 0.76;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.60;
                pitch_y = 0.0;
                pad_length = 0.95;
                pad_width = 3.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.10;
                courtyard_width = 4.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1632X76N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0612, metric 1632.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC1632X168N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.80;
                package_body_width = 3.40;
                package_body_height = 1.68;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.60;
                pitch_y = 0.0;
                pad_length = 0.95;
                pad_width = 3.40;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.10;
                courtyard_width = 3.90;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC1632X168N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0612, metric 1632.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X100N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.20;
                package_body_width = 1.45;
                package_body_height = 1.00;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X100N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X100AN"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.20;
                package_body_width = 1.40;
                package_body_height = 1.00;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.40;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 1.90;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X100AN");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X120N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.20;
                package_body_width = 1.45;
                package_body_height = 1.20;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X120N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X127N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.21;
                package_body_width = 1.45;
                package_body_height = 1.27;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X127N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X130N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.38;
                package_body_width = 1.63;
                package_body_height = 1.30;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.30;
                pad_width = 1.65;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.60;
                courtyard_width = 2.20;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X130N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X135N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.10;
                package_body_width = 1.35;
                package_body_height = 1.35;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.05;
                pad_width = 1.40;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.40;
                courtyard_width = 1.90;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X135N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X140N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.20;
                package_body_width = 1.45;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X140N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X145N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.20;
                package_body_width = 1.45;
                package_body_height = 1.45;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X145N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X145AN"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.20;
                package_body_width = 1.45;
                package_body_height = 1.45;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X145AN");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X70N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.20;
                package_body_width = 1.45;
                package_body_height = 0.70;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X70N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X71N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.20;
                package_body_width = 1.45;
                package_body_height = 0.71;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X71N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X88N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.20;
                package_body_width = 1.45;
                package_body_height = 0.88;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X88N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X90N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.20;
                package_body_width = 1.45;
                package_body_height = 0.90;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X90N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X94N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.21;
                package_body_width = 1.45;
                package_body_height = 0.94;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X94N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2012X95N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.20;
                package_body_width = 1.45;
                package_body_height = 0.95;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.45;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2012X95N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 0805, metric 2012.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC2013X140N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.38;
                package_body_width = 1.65;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 1.80;
                pitch_y = 0.0;
                pad_length = 1.30;
                pad_width = 1.65;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                silkscreen_line_width = 0.00;
                courtyard_length = 3.60;
                courtyard_width = 2.20;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC2013X140N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " 0805.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC3215X168N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.40;
                package_body_width = 1.60;
                package_body_height = 1.68;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.00;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.65;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.10;
                silkscreen_width = 1.50;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.70;
                courtyard_width = 2.20;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC3215X168N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 1206, metric 3216.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC3216X105N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.40;
                package_body_width = 1.80;
                package_body_height = 1.05;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.00;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.80;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.10;
                silkscreen_width = 1.60;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.70;
                courtyard_width = 2.30;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC3216X105N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 1206, metric 3216.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC3216X125N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.40;
                package_body_width = 1.80;
                package_body_height = 1.25;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.00;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.80;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.10;
                silkscreen_width = 1.60;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.70;
                courtyard_width = 2.30;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC3216X125N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 1206, metric 3216.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC3216X127N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.40;
                package_body_width = 1.80;
                package_body_height = 1.27;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.00;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.80;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.10;
                silkscreen_width = 1.60;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.70;
                courtyard_width = 2.30;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC3216X127N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 1206, metric 3216.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC3216X130N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.40;
                package_body_width = 1.80;
                package_body_height = 1.30;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.00;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.80;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.10;
                silkscreen_width = 1.60;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.70;
                courtyard_width = 2.30;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC3216X130N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 1206, metric 3216.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC3216X130AN"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.58;
                package_body_width = 1.98;
                package_body_height = 1.30;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.00;
                pitch_y = 0.0;
                pad_length = 1.30;
                pad_width = 2.00;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.00;
                silkscreen_width = 1.60;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.80;
                courtyard_width = 2.50;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC3216X130AN");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 1206, metric 3216.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC3216X140N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.40;
                package_body_width = 1.80;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.00;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.80;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.10;
                silkscreen_width = 1.60;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.70;
                courtyard_width = 2.30;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC3216X140N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 1206, metric 3216.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC3216X152N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.40;
                package_body_width = 1.80;
                package_body_height = 1.52;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.00;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.80;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.10;
                silkscreen_width = 1.60;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.70;
                courtyard_width = 2.30;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC3216X152N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 1206, metric 3216.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC3216X175N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.40;
                package_body_width = 1.80;
                package_body_height = 1.75;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.00;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.80;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.10;
                silkscreen_width = 1.60;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.70;
                courtyard_width = 2.30;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC3216X175N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 1206, metric 3216.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC3216X178N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.40;
                package_body_width = 1.80;
                package_body_height = 1.78;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.00;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.80;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.10;
                silkscreen_width = 1.60;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.70;
                courtyard_width = 2.30;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC3216X178N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 1206, metric 3216.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC3216X180N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.40;
                package_body_width = 1.80;
                package_body_height = 1.80;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.00;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 1.80;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.10;
                silkscreen_width = 1.60;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.70;
                courtyard_width = 2.30;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC3216X180N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 1206, metric 3216.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CAPC3216X105L"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.40;
                package_body_width = 1.80;
                package_body_height = 1.05;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 2.80;
                pitch_y = 0.0;
                pad_length = 0.95;
                pad_width = 1.70;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.10;
                silkscreen_width = 1.60;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.00;
                courtyard_width = 2.00;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CAPC3216X105L");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s: is also known as")), footprint_name,
                                " EIA 1206.");
                }
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


/*!
 * \brief Set GUI constraints for the CAPC package type.
 *
 * This function is only to be compiled for GUI targets.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
#if GUI
int
capc_set_gui_constraints
(
        GtkWidget *widget
                /*!< : is the caller widget.*/

)
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
        gtk_widget_set_sensitive (number_of_rows_entry, FALSE);
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
 * \brief Write a footprint for a CAPC package.
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
capc_write_footprint ()
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
                        "", /* pad name */
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
                fprintf (fp, (_("# Write a package body on the silkscreen\n")));
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
                fprintf (fp, (_("# Write a courtyard on the silkscreen\n")));
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
                        (_("wrote a footprint for a %s package: %s.")),
                        footprint_type,
                        footprint_filename);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief A list containing all CAPC related functions.
 */
static fpw_function_t
capc_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                capc_set_gui_constraints,
                "Set GUI constraints for a CAPC package",
                NULL
        },
#endif /* GUI */
        {
                "Create Element",
                capc_create_element,
                "Create a pcb element for a CAPC package",
                NULL
        },
        {
                "Create Packages List",
                capc_create_packages_list,
                "Create a list of known CAPC packages",
                NULL
        },
        {
                "DRC CAPC Element",
                capc_drc,
                "Design Rule Check for a CAPC package",
                NULL
        },
        {
                "Default Element Values",
                capc_get_default_footprint_values,
                "Get default values for a selected CAPC package",
                NULL
        },
        {
                "Write footprint",
                capc_write_footprint,
                "Write a footprint for a CAPC package",
                NULL
        }
};


REGISTER_FUNCTIONS (capc_function_list)


/*!
 * \brief Initialise by registering all CAPC related functions.
 */
void
capc_init ()
{
        register_capc_function_list ();
}


/* EOF */
