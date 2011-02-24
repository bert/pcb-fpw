/*!
 * \file src/dips.c
 *
 * \author Copyright (C) 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Functions for DIPS footprints (DIP Socket).
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
#include "dips.h"


/*!
 * \brief Create an Element for a DIPS package.
 *
 * \return \c EXIT_SUCCESS when an element was created,
 * \c EXIT_FAILURE when errors were encountered.
 */
int
dips_create_element ()
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
         * put the element mark. */
        element->MarkX = 0;
        element->MarkY = 0;
        /* Determine (extreme) courtyard dimensions based on pin/pad
         * properties. */
        xmin = multiplier *
        (
                (-pitch_x / 2.0) -
                (((pad_diameter > pad_length) ? pad_diameter : pad_length) / 2.0) -
                pad_solder_mask_clearance
        );
        xmax = multiplier *
        (
                (pitch_x / 2.0) +
                (((pad_diameter > pad_length) ? pad_diameter : pad_length) / 2.0) +
                pad_solder_mask_clearance
        );
        ymin = multiplier *
        (
                ((((-count_y - 1) / 2.0) + 1) * pitch_y) -
                (((pad_diameter > pad_width) ? pad_diameter : pad_width) / 2.0) -
                pad_solder_mask_clearance
        );
        ymax = multiplier *
        (
                (((count_y - 1) / 2.0) * pitch_y) +
                (((pad_diameter > pad_width) ? pad_diameter : pad_width) / 2.0) +
                pad_solder_mask_clearance
        );
        /* Determine (extreme) courtyard dimensions based on package
         * properties. */
        if ((multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package)) < xmin)
                xmin = (multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package)) > xmax)
                xmax = (multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package));
        if ((multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package)) < ymin)
                ymin = (multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package)) > ymax)
                ymax = (multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package));
        /* If the user input is using even more real-estate then use it. */
        if (multiplier * (-courtyard_length / 2.0) < xmin)
                xmin = multiplier * (-courtyard_length / 2.0);
        if (multiplier * (courtyard_length / 2.0) > xmax)
                xmax = multiplier * (courtyard_length / 2.0);
        if (multiplier * (-courtyard_width / 2.0) < ymin)
                ymin = multiplier * (-courtyard_width / 2.0);
        if (multiplier * (courtyard_width / 2.0) > ymax)
                ymax = multiplier * (courtyard_width / 2.0);
        /* Guess for a place where to put the element name. */
        element->Name[1].Scale = 100; /* 100 percent */
        element->Name[1].X = 0.0 ; /* already in mil/100 */
        element->Name[1].Y = (ymin - 10000.0); /* already in mil/100 */
        element->Name[1].TextString = footprint_name;
        element->Name[1].Element = element;
        element->Name[1].Direction = EAST;
        element->Name[1].ID = ID++;
        /* Guess for a place where to put the element refdes. */
        element->Name[2].Scale = 100; /* 100 percent */
        element->Name[2].X = 0.0 ; /* already in mil/100 */
        element->Name[2].Y = (ymin - 10000.0); /* already in mil/100 */
        element->Name[2].TextString = footprint_refdes;
        element->Name[2].Element = element;
        element->Name[2].Direction = EAST;
        element->Name[2].ID = ID++;
        /* Guess for a place where to put the element value. */
        element->Name[3].Scale = 100; /* 100 percent */
        element->Name[3].X = 0.0 ; /* already in mil/100 */
        element->Name[3].Y = (ymin - 10000.0); /* already in mil/100 */
        element->Name[3].TextString = footprint_value;
        element->Name[3].Element = element;
        element->Name[3].Direction = EAST;
        element->Name[3].ID = ID++;
        /* Create pin and/or pad entities. */
        for (i = 0; (i < count_y); i++)
        {
                pin_number = 1 + i;
                if (pin1_square && (pin_number == 1))
                                pad_flag.f = SQUARE;
                        else
                                pad_flag.f = CLEAR;
                create_new_pin
                (
                        element,
                        (int) (multiplier * (-pitch_x / 2.0)), /* x0 coordinate */
                        (int) (multiplier * ((((-count_y - 1) / 2.0) +1 + i) * pitch_y)), /* y0-coordinate */
                        (int) (multiplier * pad_diameter), /* width of the annulus ring (pad) */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * (pad_diameter + pad_solder_mask_clearance)), /* solder mask clearance */
                        (int) (multiplier * pin_drill_diameter), /* pin drill diameter */
                        pin_pad_name, /* pin name */
                        g_strdup_printf ("%d", pin_number), /* pin number */
                        pad_flag /* flags */
                );
                if (!strcmp (pad_shape, "rounded pad, elongated"))
                {
                        pad_flag.f = ONSOLDER;
                        create_new_pad
                        (
                                element,
                                (int) (multiplier * (-pitch_x + pad_length - pad_width) / 2.0), /* x0 coordinate */
                                (int) (multiplier * ((((-count_y - 1) / 2.0) + 1 + i) * pitch_y)), /* y0-coordinate */
                                (int) (multiplier * (-pitch_x - pad_length + pad_width) / 2.0), /* x1 coordinate */
                                (int) (multiplier * ((((-count_y - 1) / 2.0) + 1 + i) * pitch_y)), /* y1-coordinate */
                                (int) (multiplier * pad_width), /* width of the pad */
                                (int) (multiplier * pad_clearance), /* clearance */
                                (int) (multiplier * (pad_width + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                                pin_pad_name, /* pin name */
                                g_strdup_printf ("%d", pin_number), /* pin number */
                                pad_flag /* flags */
                        );
                }
                pin_number = (number_of_columns * count_y) - i;
                if (pin1_square && (pin_number == 1))
                                pad_flag.f = SQUARE;
                        else
                                pad_flag.f = CLEAR;
                create_new_pin
                (
                        element,
                        (int) (multiplier * pitch_x / 2.0), /* x0 coordinate */
                        (int) (multiplier * ((((-count_y - 1) / 2.0) + 1 + i) * pitch_y)), /* y0-coordinate */
                        (int) (multiplier * pad_diameter), /* width of the annulus ring (pad) */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * (pad_diameter + pad_solder_mask_clearance)), /* solder mask clearance */
                        (int) (multiplier * pin_drill_diameter), /* pin drill diameter */
                        pin_pad_name, /* pin name */
                        g_strdup_printf ("%d", pin_number), /* pin number */
                        pad_flag /* flags */
                );
                if (!strcmp (pad_shape, "rounded pad, elongated"))
                {
                        pad_flag.f = ONSOLDER;
                        create_new_pad
                        (
                                element,
                                (int) (multiplier * (pitch_x - pad_length + pad_width) / 2.0), /* x0 coordinate */
                                (int) (multiplier * ((((-count_y - 1) / 2.0) + 1 + i) * pitch_y)), /* y0-coordinate */
                                (int) (multiplier * (pitch_x + pad_length - pad_width) / 2.0), /* x1 coordinate */
                                (int) (multiplier * ((((-count_y - 1) / 2.0) + 1 + i) * pitch_y)), /* y0-coordinate */
                                (int) (multiplier * pad_width), /* width of the pad */
                                (int) (multiplier * pad_clearance), /* clearance */
                                (int) (multiplier * (pad_width + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                                pin_pad_name, /* pin name */
                                g_strdup_printf ("%d", pin_number), /* pin number */
                                pad_flag /* flags */
                        );
                }
        }
        /* Create a package body. */
        if (silkscreen_package_outline)
        {
                create_new_line
                (
                        element,
                        (int) (multiplier * (-package_body_length / 2)),
                        (int) (multiplier * (-package_body_width / 2)),
                        (int) (multiplier * (package_body_length / 2)),
                        (int) (multiplier * (-package_body_width / 2)),
                        (int) (multiplier * silkscreen_line_width)
                );
                create_new_line
                (
                        element,
                        (int) (multiplier * (package_body_length / 2)),
                        (int) (multiplier * (-package_body_width / 2)),
                        (int) (multiplier * (package_body_length / 2)),
                        (int) (multiplier * (package_body_width / 2)),
                        (int) (multiplier * silkscreen_line_width)
                );
                create_new_line
                (
                        element,
                        (int) (multiplier * (package_body_length / 2)),
                        (int) (multiplier * (package_body_width / 2)),
                        (int) (multiplier * (-package_body_length / 2)),
                        (int) (multiplier * (package_body_width / 2)),
                        (int) (multiplier * silkscreen_line_width)
                );
                create_new_line
                (
                        element,
                        (int) (multiplier * (-package_body_length / 2)),
                        (int) (multiplier * (package_body_width / 2)),
                        (int) (multiplier * (-package_body_length / 2)),
                        (int) (multiplier * (-package_body_width / 2)),
                        (int) (multiplier * silkscreen_line_width)
                );
        }
        /* Create a pin #1 marker. */
        if (silkscreen_indicate_1)
        {
                create_new_arc
                (
                        element,
                        (int) (0.0), /* already in mil/100 */
                        (int) ymin, /* already in mil/100 */
                        (int) (multiplier * (pitch_x / 8)),
                        (int) (multiplier * (pitch_x / 8)),
                        0,
                        180,
                        (int) (multiplier * silkscreen_line_width)
                );
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
        /* Create attributes here. */
        if (attributes_in_footprint)
                element = create_attributes_in_element (element);
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
 * \brief Create a list of DIPS packages with pre-defined values.
 *
 * The data in this list can be used in a combo box to select a
 * pre-defined package.
 *
 * \return \c EXIT_SUCCESS when a packages list was created,
 * \c EXIT_FAILURE when errors were encountered.
 */
int
dips_create_packages_list ()
{
        g_list_free (packages_list);
        packages_list = g_list_append (packages_list, "DIPS762W52P254L508H254Q4B");
        packages_list = g_list_append (packages_list, "DIPS762W52P254L762H254Q6B");
        packages_list = g_list_append (packages_list, "DIPS762W52P254L1016H254Q8B");
        packages_list = g_list_append (packages_list, "DIPS1016W52P254L1016H254Q8B");
        packages_list = g_list_append (packages_list, "DIPS762W52P254L1270H254Q10B");
        packages_list = g_list_append (packages_list, "DIPS762W52P254L1778H254Q14B");
        packages_list = g_list_append (packages_list, "DIPS1016W52P254L1778H254Q14B");
        packages_list = g_list_append (packages_list, "DIPS762W52P254L2032H254Q16B");
        packages_list = g_list_append (packages_list, "DIPS1016W52P254L2032H254Q16B");
        packages_list = g_list_append (packages_list, "DIPS762W52P254L2286H254Q18B");
        packages_list = g_list_append (packages_list, "DIPS1016W52P254L2286H254Q18B");
        packages_list = g_list_append (packages_list, "DIPS762W52P254L2540H254Q20B");
        packages_list = g_list_append (packages_list, "DIPS1016W52P254L2540H254Q20B");
        packages_list = g_list_append (packages_list, "DIPS04300");
        packages_list = g_list_append (packages_list, "DIPS06300");
        packages_list = g_list_append (packages_list, "DIPS08300");
        packages_list = g_list_append (packages_list, "DIPS08400");
        packages_list = g_list_append (packages_list, "DIPS10300");
        packages_list = g_list_append (packages_list, "DIPS14300");
        packages_list = g_list_append (packages_list, "DIPS14400");
        packages_list = g_list_append (packages_list, "DIPS16300");
        packages_list = g_list_append (packages_list, "DIPS16400");
        packages_list = g_list_append (packages_list, "DIPS18300");
        packages_list = g_list_append (packages_list, "DIPS18400");
        packages_list = g_list_append (packages_list, "DIPS20300");
        packages_list = g_list_append (packages_list, "DIPS20400");
        packages_list = g_list_append (packages_list, "DIPS22300");
        packages_list = g_list_append (packages_list, "DIPS22400");
        packages_list = g_list_append (packages_list, "DIPS24300");
        packages_list = g_list_append (packages_list, "DIPS24400");
        packages_list = g_list_append (packages_list, "DIPS24600");
        packages_list = g_list_append (packages_list, "DIPS28300");
        packages_list = g_list_append (packages_list, "DIPS28400");
        packages_list = g_list_append (packages_list, "DIPS28600");
        packages_list = g_list_append (packages_list, "DIPS32300");
        packages_list = g_list_append (packages_list, "DIPS32600");
        packages_list = g_list_append (packages_list, "DIPS36600");
        packages_list = g_list_append (packages_list, "DIPS38600");
        packages_list = g_list_append (packages_list, "DIPS40600");
        packages_list = g_list_append (packages_list, "DIPS42600");
        packages_list = g_list_append (packages_list, "DIPS48600");
        packages_list = g_list_append (packages_list, "DIPS50900");
        packages_list = g_list_append (packages_list, "DIPS52600");
        packages_list = g_list_append (packages_list, "DIPS64900");
        return (EXIT_SUCCESS);
}


/*!
 * \brief Do some Design Rule Checking for the DIPS package type.
 *
 * <ul>
 * <li>check for allowed pad shapes.
 * <li>check for zero sized packages.
 * <li>check for a zero sized courtyard.
 * <li>check for minimum clearance between copper (X-direction).
 * <li>check for minimum clearance between copper (Y-direction).
 * <li>If any fiducials exist:
 *   <ul>
 *   <li>check for zero fiducial pad diameter.
 *   <li>check for zero width solder mask clearance.
 *   <li>check for minimum clearance between copper (between pads and
 *     fiducials, if any fiducials exist).
 *   </ul>
 * <li>check for clearance of the package length with regard to the
 *   courtyard dimensions.
 * <li>check for clearance of the package width with regard to the
 *   courtyard dimensions.
 * <li>check for any silk lines or texts touching bare copper.
 * <li>check for soldermask clearance (solder mask overlapping copper
 *   at the solder fillet area or worse).
 * <li>check for a reasonable silk line width.
 * </ul>
 * \n
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> \c EXIT_SUCCESS when no DRC violations were encountered,
 * \c EXIT_FAILURE when DRC violations were found.
 */
int
dips_drc ()
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
                result = EXIT_FAILURE;
        }
        /* Check for minimum clearance between copper (X-direction). */
        if ((pitch_x - pad_diameter < pad_clearance) || (pitch_x - pad_length < pad_clearance))
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
        if ((pitch_y - pad_diameter < pad_clearance) || (pitch_y - pad_width < pad_clearance))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: check for minimum clearance between copper (Y-direction).")),
                                footprint_type);
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
                                        (_("[%s] DRC Error: check for zero width fiducial pad.")),
                                        footprint_type);
                        }
                        result = EXIT_FAILURE;
                }
                /* Check for a clearance of zero. */
                if (fiducial_pad_solder_mask_clearance == 0.0)
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        (_("[%s] DRC Error: check for zero width solder mask clearance.")),
                                        footprint_type);
                        }
                        result = EXIT_FAILURE;
                }
                /* Check for minimum clearance between pad copper and fiducial pad
                 * copper (including solder mask clearances). */
#if 0
                if ()
                {
                        if (verbose)
                        (
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        (_("[%s] DRC Error: check for distance between fiducial and nearest pad.")),
                                        footprint_type);
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
        return (result);
}


/*!
 * \brief Look up default values for DIPS footprint.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised the values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - DIPS762W52P254L508H254Q4B,
 * - DIPS762W52P254L762H254Q6B,
 * - DIPS762W52P254L1016H254Q8B,
 * - DIPS1016W52P254L1016H254Q8B,
 * - DIPS762W52P254L1270H254Q10B,
 * - DIPS762W52P254L1778H254Q14B,
 * - DIPS1016W52P254L1778H254Q14B,
 * - DIPS762W52P254L2032H254Q16B,
 * - DIPS1016W52P254L2032H254Q16B,
 * - DIPS762W52P254L2286H254Q18B,
 * - DIPS1016W52P254L2286H254Q18B,
 * - DIPS762W52P254L2540H254Q20B,
 * - DIPS1016W52P254L2540H254Q20B,
 * - DIPS762W52P254L2794H254Q22B,
 * - DIPS1016W52P254L2794H254Q22B,
 * - DIPS04300,
 * - DIPS06300,
 * - DIPS08300,
 * - DIPS08400,
 * - DIPS10300,
 * - DIPS14300,
 * - DIPS14400,
 * - DIPS16300,
 * - DIPS16400,
 * - DIPS18300,
 * - DIPS18400,
 * - DIPS20300,
 * - DIPS20400,
 * - DIPS22300,
 * - DIPS22400,
 * - DIPS24300,
 * - DIPS24400,
 * - DIPS24600,
 * - DIPS28300,
 * - DIPS28400,
 * - DIPS28600,
 * - DIPS32300,
 * - DIPS32600,
 * - DIPS36600,
 * - DIPS38600,
 * - DIPS40600,
 * - DIPS42600,
 * - DIPS48600,
 * - DIPS50900,
 * - DIPS52600,
 * - DIPS64900.
 *
 * <b>Parameters:</b> \c *footprint_name a \c NULL terminated footprint name.\n
 * \n
 * <b>Returns:</b> \c EXIT_SUCCESS when default values for a footprint were
 * found, \c EXIT_FAILURE when the footprint name was not found.
 */
int
dips_get_default_footprint_values ()
{
        if (!strcmp (footprint_name, "?DIPS762W52P254L508H254Q4B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 4;
                package_body_width = 300;
                package_body_length = 200;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 2;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS762W52P254L508H254Q4B");
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_name, "?DIPS762W52P254L762H254Q6B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 6;
                package_body_width = 300;
                package_body_length = 200;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 3;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS762W52P254L762H254Q6B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS762W52P254L1016H254Q8B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 8;
                package_body_width = 300;
                package_body_length = 400;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 4;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS762W52P254L1016H254Q8B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS1016W52P254L1016H254Q8B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 8;
                package_body_width = 400;
                package_body_length = 400;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 4;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS1016W52P254L1016H254Q8B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS762W52P254L1270H254Q10B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 10;
                package_body_width = 300;
                package_body_length = 500;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 5;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS762W52P254L1270H254Q10B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS762W52P254L1778H254Q14B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 14;
                package_body_width = 300;
                package_body_length = 700;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 7;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS762W52P254L1778H254Q14B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS1016W52P254L1778H254Q14B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 8;
                package_body_width = 400;
                package_body_length = 700;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 7;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS1016W52P254L1778H254Q14B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS762W52P254L2032H254Q16B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 16;
                package_body_width = 300;
                package_body_length = 800;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 8;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS762W52P254L2032H254Q16B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS1016W52P254L2032H254Q16B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 16;
                package_body_width = 400;
                package_body_length = 400;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 8;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS1016W52P254L2032H254Q16B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS762W52P254L2286H254Q18B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 18;
                package_body_width = 300;
                package_body_length = 900;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 9;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS762W52P254L2286H254Q18B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS1016W52P254L2286H254Q18B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 18;
                package_body_width = 400;
                package_body_length = 900;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 9;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS1016W52P254L2286H254Q18B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS762W52P254L2540H254Q20B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 20;
                package_body_width = 300;
                package_body_length = 1000;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 10;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS762W52P254L2540H254Q20B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS1016W52P254L2540H254Q20B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 20;
                package_body_width = 400;
                package_body_length = 1000;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 10;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS1016W52P254L2540H254Q20B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS762W52P254L2794H254Q22B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 22;
                package_body_width = 300;
                package_body_length = 1100;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 11;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS762W52P254L2794H254Q22B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS1016W52P254L2794H254Q22B"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 22;
                package_body_width = 400;
                package_body_length = 1100;
                package_body_height = 100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 11;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS1016W52P254L2794H254Q22B");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS04300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 4;
                package_body_width = 300;
                package_body_length = 300;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 2;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS04300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS06300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 6;
                package_body_width = 300;
                package_body_length = 300;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 3;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS06300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS08300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 8;
                package_body_width = 300;
                package_body_length = 400;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 4;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS08300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS08400"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 8;
                package_body_width = 400;
                package_body_length = 400;
                package_body_height = 220;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 4;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS08400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS10300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 10;
                package_body_width = 300;
                package_body_length = 500;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 5;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS10300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS14300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 14;
                package_body_width = 300;
                package_body_length = 700;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 7;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS14300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS14400"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 8;
                package_body_width = 400;
                package_body_length = 700;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 7;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS14400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS16300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 16;
                package_body_width = 300;
                package_body_length = 800;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 8;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS16300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS16400"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 16;
                package_body_width = 400;
                package_body_length = 400;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 8;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS16400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS18300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 18;
                package_body_width = 300;
                package_body_length = 900;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 9;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS18300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS18400"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 18;
                package_body_width = 400;
                package_body_length = 900;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 9;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS18400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS20300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 20;
                package_body_width = 300;
                package_body_length = 1000;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 10;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS20300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS20400"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 20;
                package_body_width = 400;
                package_body_length = 1000;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 10;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS20400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS22300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 22;
                package_body_width = 300;
                package_body_length = 1100;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 11;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS22300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS22400"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 22;
                package_body_width = 400;
                package_body_length = 1100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 11;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS22400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS24300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 24;
                package_body_width = 300;
                package_body_length = 1200;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 12;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS24300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS24400"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 24;
                package_body_width = 400;
                package_body_length = 1200;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 12;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS24400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS24600"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 24;
                package_body_width = 600;
                package_body_length = 1200;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 12;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS24600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS28300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 28;
                package_body_width = 300;
                package_body_length = 1400;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 14;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS28300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS28400"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 28;
                package_body_width = 400;
                package_body_length = 1400;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 14;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS28400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS28600"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 28;
                package_body_width = 600;
                package_body_length = 1400;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 14;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS28600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS32300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 32;
                package_body_width = 300;
                package_body_length = 1600;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 16;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS32300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS32600"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 32;
                package_body_width = 600;
                package_body_length = 1600;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 16;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS32600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS36600"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 36;
                package_body_width = 600;
                package_body_length = 1800;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 18;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS36600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS38600"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 38;
                package_body_width = 600;
                package_body_length = 1900;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 19;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS38600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS40600"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 40;
                package_body_width = 600;
                package_body_length = 2000;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 20;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS40600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS42600"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 42;
                package_body_width = 600;
                package_body_length = 2100;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 21;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS42600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS48600"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 48;
                package_body_width = 600;
                package_body_length = 2400;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 24;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS48600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS50900"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 50;
                package_body_width = 900;
                package_body_length = 2500;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 900;
                pitch_y = 100;
                count_x = 0;
                count_y = 25;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS50900");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS52600"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 52;
                package_body_width = 600;
                package_body_length = 2600;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 26;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS52600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIPS64900"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 64;
                package_body_width = 900;
                package_body_length = 3200;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 0;
                pitch_x = 900;
                pitch_y = 100;
                count_x = 0;
                count_y = 32;
                pad_shape = g_strdup ("circular pad");
                pad_shapes_type = ROUND;
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.0;
                fiducial_pad_solder_mask_clearance = 0.0;
                silkscreen_line_width = 8;
                courtyard_line_width = 2;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIPS64900");
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


/*!
 * \brief Set GUI constraints for the DIPS package type.
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Returns:</b> none.
 */
#if GUI
int
dips_set_gui_constraints (GtkWidget *widget)
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
        gtk_widget_set_sensitive (number_of_rows_entry, FALSE);
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                "count_x_entry");
        gtk_entry_set_text (GTK_ENTRY (count_x_entry), "");
        gtk_widget_set_sensitive (count_x_entry, FALSE);
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (widget),
                "count_y_entry");
        gtk_entry_set_text (GTK_ENTRY (count_y_entry), "");
        gtk_widget_set_sensitive (count_y_entry, TRUE);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (number_1_position_entry), UPPER_LEFT);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}
#endif /* GUI */


/*!
 * \brief Write a DIPS pin through hole footprint.
 *
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
dips_write_footprint ()
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
                (-pitch_x / 2.0) -
                (((pad_diameter > pad_length) ? pad_diameter : pad_length) / 2.0) -
                pad_solder_mask_clearance
        );
        xmax = multiplier *
        (
                (pitch_x / 2.0) +
                (((pad_diameter > pad_length) ? pad_diameter : pad_length) / 2.0) +
                pad_solder_mask_clearance
        );
        ymin = multiplier *
        (
                ((((-count_y - 1) / 2.0) + 1) * pitch_y) -
                (((pad_diameter > pad_width) ? pad_diameter : pad_width) / 2.0) -
                pad_solder_mask_clearance
        );
        ymax = multiplier *
        (
                (((count_y - 1) / 2.0) * pitch_y) +
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
        for (i = 0; (i < count_y); i++)
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
                        multiplier * ((((-count_y - 1) / 2.0) +1 + i) * pitch_y), /* y0-coordinate */
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
                                multiplier * (-pitch_x + pad_length - pad_width) / 2.0, /* x0 coordinate */
                                multiplier * ((((-count_y - 1) / 2.0) + 1 + i) * pitch_y), /* y0-coordinate */
                                multiplier * (-pitch_x - pad_length + pad_width) / 2.0, /* x1 coordinate */
                                multiplier * ((((-count_y - 1) / 2.0) + 1 + i) * pitch_y), /* y1-coordinate */
                                multiplier * pad_width, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                }
                pin_number = (number_of_columns * count_y) - i;
                if (pin1_square && (pin_number == 1))
                        pin_pad_flags = g_strdup ("square");
                else
                        pin_pad_flags = g_strdup ("");
                write_pin
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        multiplier * pitch_x / 2.0, /* x0 coordinate */
                        multiplier * ((((-count_y - 1) / 2.0) + 1 + i) * pitch_y), /* y0-coordinate */
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
                                multiplier * (pitch_x - pad_length + pad_width) / 2.0, /* x0 coordinate */
                                multiplier * ((((-count_y - 1) / 2.0) + 1 + i) * pitch_y), /* y0-coordinate */
                                multiplier * (pitch_x + pad_length - pad_width) / 2.0, /* x1 coordinate */
                                multiplier * ((((-count_y - 1) / 2.0) + 1 + i) * pitch_y), /* y0-coordinate */
                                multiplier * pad_width, /* width of the pad */
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
                        multiplier * (-package_body_length / 2) ,
                        multiplier * (-package_body_width / 2) ,
                        multiplier * (package_body_length / 2) ,
                        multiplier * (package_body_width / 2) ,
                        multiplier * silkscreen_line_width
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                write_element_arc
                (
                        (0.0), /* already in mil/100 */
                        ymin, /* already in mil/100 */
                        multiplier * (pitch_x / 8),
                        multiplier * (pitch_x / 8),
                        0,
                        180,
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
 * \brief A list containing all DIPS related functions.
 */
static fpw_function_t
dips_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                dips_set_gui_constraints,
                "Set GUI constraints for a DIPS package",
                NULL
        },
#endif /* GUI */
        {
                "Create Element",
                dips_create_element,
                "Create a pcb element for a DIPS package",
                NULL
        },
        {
                "Create Package List",
                dips_create_packages_list,
                "Create a list of packages with known values",
                NULL
        },
        {
                "DRC DIPS Element",
                dips_drc,
                "Design Rule Check for a DIPS package",
                NULL
        },
        {
                "Default Element Values",
                dips_get_default_footprint_values,
                "Get default values for a selected DIPS package",
                NULL
        },
        {
                "Write footprint",
                dips_write_footprint,
                "Write a footprint for a selected DIPS package",
                NULL
        }
};


/*!
 * \brief A list containing all DIPS related functions.
 */
REGISTER_FUNCTIONS (dips_function_list)


/*!
 * \brief Initialise by registering all DIPS related functions.
 *
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> none.
 */
void
dips_init ()
{
        register_dips_function_list ();
}


/* EOF */
