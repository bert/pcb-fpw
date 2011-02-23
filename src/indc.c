/*!
 * \file src/indc.c
 *
 * \author Copyright (C) 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Functions for INDC SMT footprints.
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
#include "indc.h"


/*!
 * \brief Create an Element for an INDC SMT package.
 *
 * \return \c EXIT_SUCCESS when an element was created,
 * \c EXIT_FAILURE when errors were encountered.
 */
int
indc_create_element ()
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
                return (EXIT_FAILURE);
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
        if (silkscreen_package_outline && (package_body_width))
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
                        _("created an element for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
        }
        current_element = (ElementTypePtr) &element;
        return (EXIT_SUCCESS);
}


/*!
 * \brief Create a list of INDC packages with pre-defined values.
 *
 * The data in this list can be used in a combobox to select a
 * pre-defined package.
 *
 * \return a list containing all package names of this footprint type
 * known by pcb-fpw.
 */
GList
indc_create_packages_list ()
{
        GList *indc_packages_list = NULL;
        indc_packages_list = g_list_append (indc_packages_list, "INDC1005X60N");
        indc_packages_list = g_list_append (indc_packages_list, "INDC1608X95N");
        indc_packages_list = g_list_append (indc_packages_list, "INDC2520X220N");
        indc_packages_list = g_list_append (indc_packages_list, "INDC3225X135N");
        indc_packages_list = g_list_append (indc_packages_list, "INDC4509X190N");
        indc_packages_list = g_list_append (indc_packages_list, "INDC4532X175N");
        indc_packages_list = g_list_append (indc_packages_list, "INDC4648X310N");
        indc_packages_list = g_list_append (indc_packages_list, "INDC5750X180N");
        indc_packages_list = g_list_append (indc_packages_list, "INDC6350X200N");
        return (*indc_packages_list);
}


/*!
 * \brief Do some Design Rule Checking for the INDC package type.
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
indc_drc ()
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
        if (pitch_x - pad_length < pad_clearance)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: check for minimum clearance between copper (X-direction).")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        /* Check for minimum clearance between copper (Y-direction). */
        if (pitch_y - pad_width < pad_clearance)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: check for minimum clearance between copper (Y-direction).")),
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
        if (silkscreen_package_outline && (silkscreen_line_width == 0.0))
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
                if (silkscreen_package_outline && (silkscreen_line_width > 40.0))
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
                if (silkscreen_package_outline && (silkscreen_line_width > 4000.0))
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
                if (silkscreen_package_outline && (silkscreen_line_width > 1.0))
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
        if (verbose && (result == EXIT_SUCCESS))
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        (_("[%s] DRC Check: no errors while checking package %s.")),
                        footprint_type, footprint_name);
        }
        return result;
}


/*!
 * \brief Look up default values for INDC SMT footprint.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised known values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - INDC1005X60N,
 * - INDC1608X95N,
 * - INDC2520X220N,
 * - INDC3225X135N,
 * - INDC4509X190N,
 * - INDC4532X175N,
 * - INDC4648X310N,
 * - INDC5750X180N,
 * - INDC6350X200N.
 *
 * \return \c EXIT_SUCCESS when default values for a footprint were
 * found, \c EXIT_FAILURE when the footprint name was not found.
 */
int
indc_get_default_footprint_values
(
        gchar *footprint_name
                /*!< : a \c NULL terminated footprint name.*/
)
{
        if (!strcmp (footprint_name, "?INDC1005X60N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 1.10;
                package_body_width = 0.70;
                package_body_height = 0.60;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 0.95;
                pitch_y = 0.0;
                pad_length = 0.59;
                pad_width = 0.72;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.0;
                silkscreen_width = 0.0;
                silkscreen_line_width = 0.20;
                courtyard_length = 1.85;
                courtyard_width = 1.05;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("INDC1005X60N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " EIA 0402, metric 1005.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?INDC1608X95N"))
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
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.0;
                silkscreen_width = 0.0;
                silkscreen_line_width = 0.20;
                courtyard_length = 3.10;
                courtyard_width = 1.50;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("INDC1608X95N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " EIA 0603, metric 1608.");
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("%s: footprint is too small for a package outline on the silkscreen.")),
                                footprint_name);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?INDC2520X220N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.70;
                package_body_width = 2.30;
                package_body_height = 2.20;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 2.50;
                pitch_y = 0.0;
                pad_length = 0.95;
                pad_width = 2.30;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 0.80;
                silkscreen_width = 2.00;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.00;
                courtyard_width = 2.80;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("INDC2520X220N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " EIA 1008, metric 2520.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?INDC3225X135N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 3.40;
                package_body_width = 2.70;
                package_body_height = 1.35;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.00;
                pitch_y = 0.0;
                pad_length = 1.15;
                pad_width = 2.70;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 1.10;
                silkscreen_width = 2.50;
                silkscreen_line_width = 0.20;
                courtyard_length = 4.70;
                courtyard_width = 3.20;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("INDC3225X135N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " EIA 1210, metric 3225.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?INDC4509X190N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 4.80;
                package_body_width = 1.20;
                package_body_height = 1.90;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 4.20;
                pitch_y = 0.0;
                pad_length = 1.30;
                pad_width = 1.20;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 2.20;
                silkscreen_width = 0.90;
                silkscreen_line_width = 0.20;
                courtyard_length = 6.00;
                courtyard_width = 1.70;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("INDC4509X190N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " EIA 1806, metric 4509.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?INDC4532X175N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 4.80;
                package_body_width = 3.40;
                package_body_height = 1.75;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 4.10;
                pitch_y = 0.0;
                pad_length = 1.40;
                pad_width = 3.40;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 2.00;
                silkscreen_width = 3.20;
                silkscreen_line_width = 0.20;
                courtyard_length = 6.00;
                courtyard_width = 3.90;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("INDC4532X175N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " EIA 1812, metric 4532.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?INDC4648X310N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 4.60;
                package_body_width = 5.00;
                package_body_height = 3.10;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 3.50;
                pitch_y = 0.0;
                pad_length = 2.00;
                pad_width = 5.00;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 0.20;
                silkscreen_width = 4.80;
                silkscreen_line_width = 0.20;
                courtyard_length = 6.00;
                courtyard_width = 5.50;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("INDC4648X310N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?INDC5750X180N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 5.90;
                package_body_width = 5.30;
                package_body_height = 1.80;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 5.40;
                pitch_y = 0.0;
                pad_length = 1.20;
                pad_width = 5.30;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 3.50;
                silkscreen_width = 5.00;
                silkscreen_line_width = 0.20;
                courtyard_length = 7.10;
                courtyard_width = 5.80;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("INDC5750X180N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " EIA 2220, metric 5650.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?INDC6350X200N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 6.50;
                package_body_width = 5.30;
                package_body_height = 2.00;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 0;
                number_of_rows = 0;
                count_x = 0;
                count_y = 0;
                pitch_x = 6.00;
                pitch_y = 0.0;
                pad_length = 1.20;
                pad_width = 5.30;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_package_outline = TRUE;
                silkscreen_length = 4.10;
                silkscreen_width = 5.00;
                silkscreen_line_width = 0.20;
                courtyard_length = 7.70;
                courtyard_width = 5.80;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("INDC6350X200N");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " EIA 2520, metric 6350.");
                }
                return (EXIT_SUCCESS);
        }
        else
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("default values for footprint %s not found.\n"),
                        footprint_name);
                return (EXIT_FAILURE);
        }
        return (EXIT_FAILURE);
}


/*!
 * \brief Set GUI constraints for the INDC SMT package type.
 *
 * This function is only to be compiled for GUI targets.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
#if GUI
int
indc_set_gui_constraints
(
        GtkWidget *widget
                /*!< : the caller widget.*/
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
 * \brief Write a INDC SMT footprint with two pads for a chip package.
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
indc_write_footprint ()
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
                        multiplier * (-pitch_x / 2), /* x0-coordinate */
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
                        multiplier * (pitch_x / 2.0), /* x1-coordinate */
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
        if (silkscreen_package_outline && (package_body_width))
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
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
 * \brief A list containing all INDC related functions.
 */
static fpw_function_t
indc_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                indc_set_gui_constraints,
                "Set GUI constraints for a INDC SMT package",
                NULL
        },
#endif /* GUI */
        {
                "Create Element",
                indc_create_element,
                "Create a pcb element for an INDC SMT package",
                NULL
        },
        {
                "DRC INDC Element",
                indc_drc,
                "Design Rule Check for an INDC SMT package",
                NULL
        },
        {
                "Default Element Values",
                indc_get_default_footprint_values,
                "Get default values for a INDC SMT package",
                NULL
        },
        {
                "Write footprint",
                indc_write_footprint,
                "Write a footprint for a INDC SMT package",
                NULL
        }
};


REGISTER_FUNCTIONS (indc_function_list)


/*!
 * \brief Initialise by registering all INDC related functions.
 */
void
indc_init ()
{
        register_indc_function_list ();
}


/* EOF */
