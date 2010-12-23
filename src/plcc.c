/*!
 * \file src/plcc.c
 *
 * \author Copyright (C) 2007, 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
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
#include "plcc.h"


/*!
 * \brief Create an Element for a PLCC package.
 *
 * \return the created \c element.
 */
ElementTypePtr
plcc_create_element ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gdouble x0;
        gdouble x1;
        gdouble y0;
        gdouble y1;
        gdouble y_dot;
        gdouble dx;
        gint i;
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
                {
                        pad_flag.f = SQUARE;
                }
                else if (pad_shapes_type == SQUARE)
                {
                        pad_flag.f = SQUARE;
                }
                else
                {
                        pad_flag.f = CLEAR;
                }
                create_new_pad
                (
                        element,
                        (int) (multiplier * ((-pin_number + 1) * pitch_x)), /* x0 coordinate */
                        (int) (multiplier * y0), /* y0-coordinate */
                        (int) (multiplier * ((-pin_number + 1) * pitch_x)), /* x1 coordinate */
                        (int) (multiplier * y1), /* y1-coordinate */
                        (int) (multiplier * pad_width), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * (pad_diameter + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        pin_pad_name, /* pin name */
                        g_strdup_printf ("%d", pin_number), /* pin number */
                        pad_flag /* flags */
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
                create_new_pad
                (
                        element,
                        (int) (multiplier * x0), /* x0 coordinate */
                        (int) (multiplier * ((-count_y / 2) - 1 + i) * pitch_y), /* y0-coordinate */
                        (int) (multiplier * x1), /* x1 coordinate */
                        (int) (multiplier * ((-count_y / 2) - 1 + i) * pitch_y), /* y1-coordinate */
                        (int) (multiplier * pad_width), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * (pad_diameter + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        pin_pad_name, /* pin name */
                        g_strdup_printf ("%d", pin_number), /* pin number */
                        pad_flag /* flags */
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
                create_new_pad
                (
                        element,
                        (int) (multiplier * ((-count_x / 2) - 1 + i) * pitch_x), /* x0 coordinate */
                        (int) (multiplier * y0), /* y0-coordinate */
                        (int) (multiplier * ((-count_x / 2) - 1 + i) * pitch_x), /* x1 coordinate */
                        (int) (multiplier * y1), /* y1-coordinate */
                        (int) (multiplier * pad_width), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * (pad_diameter + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        pin_pad_name, /* pin name */
                        g_strdup_printf ("%d", pin_number), /* pin number */
                        pad_flag /* flags */
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
                create_new_pad
                (
                        element,
                        (int) (multiplier * x0), /* x0 coordinate */
                        (int) (multiplier * ((count_y / 2) + 1 - i) * pitch_y), /* y0-coordinate */
                        (int) (multiplier * x1), /* x1 coordinate */
                        (int) (multiplier * ((count_y / 2) + 1 - i) * pitch_y), /* y1-coordinate */
                        (int) (multiplier * pad_width), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * (pad_diameter + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        pin_pad_name, /* pin name */
                        g_strdup_printf ("%d", pin_number), /* pin number */
                        pad_flag /* flags */
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
                create_new_pad
                (
                        element,
                        (int) (multiplier * ((count_x / 2) + 1 - i) * pitch_x), /* x0 coordinate */
                        (int) (multiplier * y0), /* y0-coordinate */
                        (int) (multiplier * ((count_x / 2) + 1 - i) * pitch_x), /* x1 coordinate */
                        (int) (multiplier * y1), /* y1-coordinate */
                        (int) (multiplier * pad_width), /* pad width */
                        (int) (multiplier * pad_clearance), /* clearance */
                        (int) (multiplier * (pad_diameter + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                        pin_pad_name, /* pin name */
                        g_strdup_printf ("%d", pin_number), /* pin number */
                        pad_flag /* flags */
                );
                i++;
        }
        /* Create a package body. */
        if (silkscreen_package_outline)
        {
                /* Upper right corner */
                create_new_line
                (
                        element,
                        (int) (multiplier * (package_body_length / 2.0)),
                        (int) (multiplier * (-package_body_width / 2.0)),
                        (int) (multiplier * (package_body_length / 2.0)),
                        (int) (multiplier * (-1 * ((((count_y - 1) * pitch_y) + pad_length) / 2.0) - pad_solder_mask_clearance)),
                        (int) (multiplier * (silkscreen_line_width))
                );
                create_new_line
                (
                        element,
                        (int) (multiplier * (package_body_length / 2.0)),
                        (int) (multiplier * (-package_body_width / 2.0)),
                        (int) (multiplier * (((((count_x - 1) * pitch_x) + pad_length) / 2.0) + pad_solder_mask_clearance)),
                        (int) (multiplier * (-package_body_width / 2.0)),
                        (int) (multiplier * (silkscreen_line_width))
                );
                /* Lower right corner */
                create_new_line
                (
                        element,
                        (int) (multiplier * (package_body_length / 2.0)),
                        (int) (multiplier * (package_body_width / 2.0)),
                        (int) (multiplier * (package_body_length / 2.0)),
                        (int) (multiplier * (((((count_y - 1) * pitch_y) + pad_length) / 2.0) + pad_solder_mask_clearance)),
                        (int) (multiplier * (silkscreen_line_width))
                );
                create_new_line
                (
                        element,
                        (int) (multiplier * (package_body_length / 2.0)),
                        (int) (multiplier * (package_body_width / 2.0)),
                        (int) (multiplier * (((((count_x - 1) * pitch_x) + pad_length) / 2.0) + pad_solder_mask_clearance)),
                        (int) (multiplier * (package_body_width / 2.0)),
                        (int) (multiplier * (silkscreen_line_width))
                );
                /* Lower left corner */
                create_new_line
                (
                        element,
                        (int) (multiplier * (-package_body_length / 2.0)),
                        (int) (multiplier * (package_body_width / 2.0)),
                        (int) (multiplier * (-package_body_length / 2.0)),
                        (int) (multiplier * (((((count_y - 1) * pitch_y) + pad_length) / 2.0) + pad_solder_mask_clearance)),
                        (int) (multiplier * (silkscreen_line_width))
                );
                create_new_line
                (
                        element,
                        (int) (multiplier * (-package_body_length / 2.0)),
                        (int) (multiplier * (package_body_width / 2.0)),
                        (int) (multiplier * (-1 * ((((count_x - 1) * pitch_x) + pad_length) / 2.0) - pad_solder_mask_clearance)),
                        (int) (multiplier * (package_body_width / 2.0)),
                        (int) (multiplier * (silkscreen_line_width))
                );
                /* Upper left corner */
                create_new_line
                (
                        element,
                        (int) (multiplier * (-1 * ((((count_x - 1) * pitch_x) + pad_length) / 2.0) - pad_solder_mask_clearance)),
                        (int) (multiplier * (-package_body_width / 2.0)),
                        (int) (multiplier * (-package_body_length / 2.0)),
                        (int) (multiplier * (-1 * ((((count_y - 1) * pitch_y) + pad_length) / 2.0) - pad_solder_mask_clearance)),
                        (int) (multiplier * (silkscreen_line_width))
                );
        }
        /* Create a pin #1 marker. */
        if (silkscreen_indicate_1)
        {
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
                create_new_arc
                (
                        element,
                        0,
                        (int) (multiplier * y_dot),
                        (int) (multiplier * 0.5 * silkscreen_line_width),
                        (int) (multiplier * 0.5 * silkscreen_line_width),
                        0,
                        360,
                        (int) (multiplier * silkscreen_line_width)
                );
        }
        /* Create a courtyard outline. */
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
 * \brief Create a list of known PLCC packages.
 *
 * The data in this list can be used in a combobox to select a
 * pre-defined package.
 *
 * \return a list containing all package names of this footprint type
 * known by pcb-fpw.
 */
GList
plcc_create_packages_list ()
{
        GList *plcc_packages_list = NULL;
        plcc_packages_list = g_list_append (plcc_packages_list, "INDC0603X33N");
        return (*plcc_packages_list);
}


/*!
 * \brief Do some Design Rule Checking for the PLCC package type.
 *
 * <ul>
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
plcc_drc ()
{
        int result = EXIT_SUCCESS;
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("DRC Check: checking BGA package %s."), footprint_name);
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
                                        _("DRC Error: round pad shape specified for check for allowed pad shapes."));
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
                /*! \todo Check for minimum clearance between pad copper and fiducial pad
                 *   copper (including solder mask clearances).
                 */
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
                        _("DRC Check: no errors while checking PLCC package %s."), footprint_name);
        }
        return (result);
}


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
        /* Widgets on tab "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab "Pins/Pads" */
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

        /* Widgets on tab "Thermal Pad" */
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
        gchar *pin_pad_flags = g_strdup ("");
        gint i;
        gdouble x0;
        gdouble x1;
        gdouble y0;
        gdouble y1;
        gdouble y_dot;

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
                "Create element",
                plcc_create_element,
                "Create an element for a PLCC package",
                NULL
        },
        {
                "Create Packages List",
                plcc_create_packages_list,
                "Create a list of known PLCC packages",
                NULL
        },
        {
                "DRC PLCC Element",
                plcc_drc,
                "Design Rule Check for a PLCC package",
                NULL
        },
        {
                "Default Element Values",
                plcc_get_default_footprint_values,
                "Get default values for a PLCC package",
                NULL
        },
        {
                "Write footprint",
                plcc_write_footprint,
                "Write a footprint for a PLCC package",
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
