/*!
 * \file bga.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Functions for BGA footprints.
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
 * \brief Create an Element for a BGA package.
 */
ElementTypePtr
bga_create_element ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble dx;
        gint pin_number;
        gchar *pin_pad_name = g_strdup ("");
        gint i;
        gint j;
        FlagType pad_flag;
        ElementTypePtr element;

        if (!element)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("could not create a valid element pointer for a BGA package."));
                return (NULL);
        }
        /* Define the center of our universe and guess for a place where to
         * put the element mark. */
        element->MarkX = 0;
        element->MarkY = 0;
        /* Determine (extreme) courtyard dimensions based on pin/pad
         * properties. */
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
        pin_number = 1;
        for (i = 0; (i < number_of_rows); i++)
        /* one row at a time [A .. ZZ ..] etc.
         * where i is one or more letters of the alphabet,
         * excluding "I", "O", "Q", "S" and "Z". */
        {
                for (j = 0; (j < number_of_columns); j++)
                /* all columns of a row [1 .. n]
                 * where j is a member of the positive Natural numbers (N). */
                {
                        if (pin1_square && (pin_number == 1))
                                pad_flag.f = SQUARE;
                        else
                                pad_flag.f = CLEAR;
                        pin_pad_name = g_strdup_printf ("%s%d", (row_letters[i]), (j + 1));
                        if (get_pin_pad_exception (pin_pad_name))
                        {
                                create_new_pad
                                (
                                        element,
                                        (int) (multiplier * ((((-number_of_columns -1) / 2.0) + 1 + j) * pitch_x)), /* x0 coordinate */
                                        (int) (multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y)), /* y0-coordinate */
                                        (int) (multiplier * ((((-number_of_columns -1) / 2.0) + 1 + j) * pitch_x)), /* x1 coordinate */
                                        (int) (multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y)), /* y1-coordinate */
                                        (int) (multiplier * pad_diameter), /* pad width */
                                        (int) (multiplier * pad_clearance), /* clearance */
                                        (int) (multiplier * (pad_diameter + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                                        pin_pad_name, /* pin name */
                                        g_strdup_printf ("%d", pin_number), /* pin number */
                                        pad_flag /* flags */
                                );
                        }
                        pin_number++;
                }
        }
        /* Create fiducials if the package seem to have them. */
        if (fiducial)
        {
                pin_pad_name = g_strdup ("");
                pad_flag.f = NOPASTE;
                create_new_pad
                (
                        element,
                        (int) (multiplier * ((silkscreen_length - courtyard_length > 2) ?
                                (courtyard_length / 2) :
                                ((courtyard_length / 2 ) + 1))),
                                /* x0 coordinate */
                        (int) (multiplier * ((silkscreen_width - courtyard_width > 2) ?
                                (-courtyard_width / 2) :
                                ((-courtyard_width / 2 ) - 1))),
                                /* y0 coordinate */
                        (int) (multiplier * ((silkscreen_length - courtyard_length > 2) ?
                                (courtyard_length / 2) :
                                ((courtyard_length / 2 ) + 1))),
                                /* x1 coordinate */
                        (int) (multiplier * ((silkscreen_width - courtyard_width > 2) ?
                                (-courtyard_width / 2) :
                                ((-courtyard_width / 2 ) - 1))),
                                /* y1 coordinate */
                        (int) (multiplier * fiducial_pad_diameter), /* pad width */
                        (int) (multiplier * fiducial_pad_solder_mask_clearance),
                                /* pad clearance */
                        (int) (multiplier * (fiducial_pad_diameter +
                                (2 * fiducial_pad_solder_mask_clearance))),
                                /* solder mask clearance */
                        pin_pad_name, /* pin name */
                        g_strdup_printf ("%d", pin_number), /* pin number */
                        pad_flag /* flags */
                );
                pin_number++;
                create_new_pad
                (
                        element,
                        (int) (multiplier * ((silkscreen_length - courtyard_length > 2) ?
                                (-courtyard_length / 2) :
                                ((-courtyard_length / 2 ) - 1))),
                                /* x0 coordinate */
                        (int) (multiplier * ((silkscreen_width - courtyard_width > 2) ?
                                (courtyard_width / 2) :
                                ((courtyard_width / 2 ) + 1))),
                                /* y0 coordinate */
                        (int) (multiplier * ((silkscreen_length - courtyard_length > 2) ?
                                (-courtyard_length / 2) :
                                ((-courtyard_length / 2 ) - 1))),
                                /* x1 coordinate */
                        (int) (multiplier * ((silkscreen_width - courtyard_width > 2) ?
                                (courtyard_width / 2) :
                                ((courtyard_width / 2 ) + 1))),
                                /* y1 coordinate */
                        (int) (multiplier * fiducial_pad_diameter), /* pad width */
                        (int) (multiplier * fiducial_pad_solder_mask_clearance),
                                /* pad clearance */
                        (int) (multiplier * (fiducial_pad_diameter +
                                (2 * fiducial_pad_solder_mask_clearance))),
                                /* solder mask clearance */
                        pin_pad_name, /* pin name */
                        g_strdup_printf ("%d", pin_number), /* pin number */
                        pad_flag /* flags */
                );
        }
        /* Create a package body. */
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
        }
        /* Create a pin #1 marker. */
        if (silkscreen_indicate_1)
        {
                for (dx = 0.0; dx < (pitch_x / 2.0); dx = dx + silkscreen_line_width)
                {
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (-package_body_length / 2.0)),
                                (int) (multiplier * ((-package_body_width / 2.0) + dx)),
                                (int) (multiplier * ((-package_body_length / 2.0) + dx)),
                                (int) (multiplier * (-package_body_width / 2.0)),
                                (int) (multiplier * (silkscreen_line_width))
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
        /* Create attributes here. */
        if (attributes_in_footprint)
                element = create_attributes_in_element (element);
        /* We are ready creating an element. */
        if (verbose)
                g_log ("", G_LOG_LEVEL_INFO,
                        _("created an element for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
        return (element);
}


/*!
 * \brief Create a list of BGA packages with pre-defined values.
 *
 * The data in this list can be used in a combo box to select a
 * pre-defined package.
 */
GList
bga_create_packages_list ()
{
        GList *bga_packages_list = NULL;
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C100P10X10_1100X1100X140");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C100P10X10_1100X1100X170");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C100P10X10_1100X1100X170A");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C100P10X10_1100X1100X200");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C100P10X10_1100X1100X350");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C50P10X10_600X600X110");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C50P11X11_600X600X100");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C50P14X14_800X800X120");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C50P14X14_800X800X135");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C50P15X15_1000X1000X120");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C65P10X10_800X800X140");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C80P10X10_1000X1000X140");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C80P10X10_1000X1000X150");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C80P10X10_900X900X100");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C80P10X10_900X900X150");
        bga_packages_list = g_list_append (bga_packages_list, "BGA100C80P11X11_1100X1100X140");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1020C100P32X32_3300X3300X350");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1023C100P32X32_3300X3300X350");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1024C100P32X32_3300X3300X350");
        bga_packages_list = g_list_append (bga_packages_list, "BGA103C65P8X13_600X900X100");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1056C100P39X39_4000X4000X380");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1056C100P39X39_4000X4000X400");
        bga_packages_list = g_list_append (bga_packages_list, "BGA105C50P15X15_800X800X140");
        bga_packages_list = g_list_append (bga_packages_list, "BGA107C80P10X14_1050X1300X120");
        bga_packages_list = g_list_append (bga_packages_list, "BGA107C80P10X14_1050X1300X140");
        bga_packages_list = g_list_append (bga_packages_list, "BGA107C80P10X14_1050X1600X140");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1089C100P33X33_3500X3500X350");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1089C127P33X33_4250X4250X350");
        bga_packages_list = g_list_append (bga_packages_list, "BGA109C50P12X12_700X700X100");
        bga_packages_list = g_list_append (bga_packages_list, "BGA10C50P3X4_220X250X60");
        bga_packages_list = g_list_append (bga_packages_list, "BGA10N50P3X4_200X250X94");
        bga_packages_list = g_list_append (bga_packages_list, "BGA111C80P12X13_1000X1100X140");
        bga_packages_list = g_list_append (bga_packages_list, "BGA111C80P12X13_1100X1100X140");
        bga_packages_list = g_list_append (bga_packages_list, "BGA112C80P11X11_1000X1000X130");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1148C100P34X34_3500X3500X340");
        bga_packages_list = g_list_append (bga_packages_list, "BGA114C80P6X19_550X1600X140");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1152C100P34X34_3500X3500X340");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1152C100P34X34_3500X3500X350");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1156C100P34X34_3500X3500X260");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1156C100P34X34_3500X3500X311");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1156C100P34X34_3500X3500X350");
        bga_packages_list = g_list_append (bga_packages_list, "BGA1156C100P34X34_3500X3500X380");
        return (*bga_packages_list);
}


/*!
 * \brief Do some Design Rule Checking for the BGA package type.
 *
 * - check for allowed pad shapes.
 * - check for zero sized packages.
 * - check for a zero sized courtyard.
 * - check for minimum clearance between copper (X-direction).
 * - check for minimum clearance between copper (Y-direction).
 * - If any fiducials exist:
 *   - check for zero fiducial pad diameter.
 *   - check for zero width solder mask clearance.
 *   - check for minimum clearance between copper (between pads and fiducials,
 *     if any fiducials exist).
 * - check for clearance of the package length with regard to the courtyard
 *   dimensions.
 * - check for clearance of the package width with regard to the courtyard
 *   dimensions.
 * - check for any silk lines or texts touching bare copper.
 * - check for soldermask clearance (solder mask overlapping copper at the
 *   solder fillet area or worse).
 * - check for a reasonable silk line width.
 */
int
bga_drc ()
{
        int result = EXIT_SUCCESS;
        if (verbose)
                g_log ("", G_LOG_LEVEL_INFO,
                        _("DRC Check: checking BGA package %s."), footprint_name);
        /* Check for allowed pad shapes. */
        switch (pad_shapes_type)
        {
                case NO_SHAPE:
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: NO_SHAPE specified for check for allowed pad shapes."));
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
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: square pad shape specified for check for allowed pad shapes."));
                        result = EXIT_FAILURE;
                        break;
                }
                case OCTAGONAL:
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: octagonal pad shape specified for check for allowed pad shapes."));
                        result = EXIT_FAILURE;
                        break;
                }
                case ROUND_ELONGATED:
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: round elongated pad shape specified for check for allowed pad shapes."));
                        result = EXIT_FAILURE;
                        break;
                }
                default:
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: no valid pad shape type specified."));
                        result = EXIT_FAILURE;
                        break;
                }
        }
        /* Check for zero sized packages. */
        if (package_body_length <= 0.0)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for package body length is <= 0.0."));
                result = EXIT_FAILURE;
        }
        if (package_body_width <= 0.0)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for package body width is <= 0.0."));
                result = EXIT_FAILURE;
        }
        if (package_body_height <= 0.0)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for package body height is <= 0.0."));
                result = EXIT_FAILURE;
        }
        /* Check for a zero sized courtyard. */
        if (courtyard_length <= 0.0)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for courtyard length is <= 0.0."));
                result = EXIT_FAILURE;
        }
        if (courtyard_width <= 0.0)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for courtyard width is <= 0.0."));
                result = EXIT_FAILURE;
        }
        /* Check for minimum clearance between copper (X-direction). */
        if (pitch_x - pad_diameter < pad_clearance)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for minimum clearance between copper (X-direction)."));
                result = EXIT_FAILURE;
        }
        /* Check for minimum clearance between copper (Y-direction). */
        if (pitch_y - pad_diameter < pad_clearance)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for minimum clearance between copper (Y-direction)."));
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
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: check for zero width fiducial pad."));
                        result = EXIT_FAILURE;
                }
                /* Check for a clearance of zero. */
                if (fiducial_pad_solder_mask_clearance == 0.0)
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: check for zero width solder mask clearance."));
                        result = EXIT_FAILURE;
                }
                /* Check for minimum clearance between pad copper and fiducial pad
                 * copper (including solder mask clearances). */
#if 0
                if ()
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: check for distance between fiducial and nearest pad."));
                        result = EXIT_FAILURE;
                }
#endif
        }
        /* Check for clearance of the package length with regard to the
         * courtyard dimensions. */
        if (package_body_length - courtyard_length < courtyard_clearance_with_package)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for clearance of the package length with regard to the courtyard dimensions."));
                result = EXIT_FAILURE;
        }
        /* Check for clearance of the package width with regard to the
         * courtyard dimensions. */
        if (package_body_width - courtyard_width < courtyard_clearance_with_package)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for clearance of the package width with regard to the courtyard dimensions."));
                result = EXIT_FAILURE;
        }
        /*! \todo Check for any silk lines or texts touching bare copper. */

        /*! \todo Check for soldermask clearance (solder mask overlapping copper at
         * the solder fillet area or worse). */

        /* Check for a reasonable silk line width. */
        if (silkscreen_package_outline || (silkscreen_line_width == 0.0))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: line width 0.0 specified for check for a reasonable silk line width."));
                result = EXIT_FAILURE;
        }
        switch (units_type)
        {
                case NO_UNITS:
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: no units specified for check for a reasonable silk line width."));
                        result = EXIT_FAILURE;
                        break;
                }
                case MIL:
                if (silkscreen_line_width > 40.0)
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: line width > 40.0 mil specified check for a reasonable silk line width."));
                        result = EXIT_FAILURE;
                        break;
                }
                case MIL_100:
                if (silkscreen_line_width > 4000.0)
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: line width > 40.0 mil specified check for a reasonable silk line width."));
                        result = EXIT_FAILURE;
                        break;
                }
                case MM:
                if (silkscreen_line_width > 1.0)
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: line width > 1.0 mm specified check for a reasonable silk line width."));
                        result = EXIT_FAILURE;
                        break;
                }
                default:
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("DRC Error: no valid units type specified for check for a reasonable silk line width."));
                        result = EXIT_FAILURE;
                        break;
                }
        }
        /*! \todo Create attributes here. */
        /* No failures on DRC found. */
        if (verbose || (result == EXIT_SUCCESS))
                g_log ("", G_LOG_LEVEL_INFO,
                        _("DRC Check: no errors while checking BGA package %s."), footprint_name);
        return (result);
}


/*!
 * \brief Look up default values for BGA footprints.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised the known values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - BGA100C100P10X10_1100X1100X140,
 * - BGA100C100P10X10_1100X1100X170,
 * - BGA100C100P10X10_1100X1100X170A,
 * - BGA100C100P10X10_1100X1100X200,
 * - BGA100C100P10X10_1100X1100X350,
 * - BGA100C50P10X10_600X600X110,
 * - BGA100C50P11X11_600X600X100,
 * - BGA100C50P14X14_800X800X120,
 * - BGA100C50P14X14_800X800X135,
 * - BGA100C50P15X15_1000X1000X120,
 * - BGA100C65P10X10_800X800X140,
 * - BGA100C80P10X10_1000X1000X140,
 * - BGA100C80P10X10_1000X1000X150,
 * - BGA100C80P10X10_900X900X100,
 * - BGA100C80P10X10_900X900X150,
 * - BGA100C80P11X11_1100X1100X140,
 * - BGA1020C100P32X32_3300X3300X350,
 * - BGA1023C100P32X32_3300X3300X350,
 * - BGA1024C100P32X32_3300X3300X350,
 * - BGA103C65P8X13_600X900X100,
 * - BGA1056C100P39X39_4000X4000X380,
 * - BGA1056C100P39X39_4000X4000X400,
 * - BGA105C50P15X15_800X800X140,
 * - BGA107C80P10X14_1050X1300X120,
 * - BGA107C80P10X14_1050X1300X140,
 * - BGA107C80P10X14_1050X1600X140,
 * - BGA1089C100P33X33_3500X3500X350,
 * - BGA1089C127P33X33_4250X4250X350,
 * - BGA109C50P12X12_700X700X100,
 * - BGA10C50P3X4_220X250X60,
 * - BGA10N50P3X4_200X250X94,
 * - BGA111C80P12X13_1000X1100X140,
 * - BGA111C80P12X13_1100X1100X140,
 * - BGA112C80P11X11_1000X1000X130,
 * - BGA1148C100P34X34_3500X3500X340,
 * - BGA114C80P6X19_550X1600X140,
 * - BGA1152C100P34X34_3500X3500X340,
 * - BGA1152C100P34X34_3500X3500X350,
 * - BGA1156C100P34X34_3500X3500X260,
 * - BGA1156C100P34X34_3500X3500X311,
 * - BGA1156C100P34X34_3500X3500X350,
 * - BGA1156C100P34X34_3500X3500X380,
 */
int
bga_get_default_footprint_values
(
        gchar *footprint_name)
{
        if (!strcmp (footprint_name, "?BGA100C100P10X10_1100X1100X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
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
                courtyard_line_width = 0.05;
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C100P10X10_1100X1100X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C100P10X10_1100X1100X170"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 11.00;
                package_body_length = 11.00;
                package_body_height = 1.70;
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
                courtyard_line_width = 0.05;
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                g_log ("", G_LOG_LEVEL_INFO,
                        _("BGA100C100P10X10_1100X1100X170: also known as JEDEC MO-192AAC-1."));
                footprint_name = g_strdup ("BGA100C100P10X10_1100X1100X170");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C100P10X10_1100X1100X170A"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 11.00;
                package_body_length = 11.00;
                package_body_height = 1.70;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 10;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                courtyard_length = 13.00;
                courtyard_width = 13.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C100P10X10_1100X1100X170A");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C100P10X10_1100X1100X200"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 11.00;
                package_body_length = 11.00;
                package_body_height = 2.00;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                courtyard_length = 13.00;
                courtyard_width = 13.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C100P10X10_1100X1100X200");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C100P10X10_1100X1100X350"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 11.00;
                package_body_length = 11.00;
                package_body_height = 1.70;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 10;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                courtyard_length = 13.00;
                courtyard_width = 13.00;
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C100P10X10_1100X1100X350");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C50P10X10_600X600X110"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 6.00;
                package_body_length = 6.00;
                package_body_height = 1.10;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 10;
                pitch_x = 0.50;
                pitch_y = 0.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.25;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 8.00;
                courtyard_width = 8.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 6.00;
                silkscreen_width = 6.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                g_log ("", G_LOG_LEVEL_INFO,
                        _("BGA100C50P10X10_600X600X110: also known as JEDEC MO-195."));
                footprint_name = g_strdup ("BGA100C50P10X10_600X600X110");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C50P11X11_600X600X100"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A6,A11,",
                        "D5,D6,D7,",
                        "E4,E8,",
                        "F1,F4,F6,F8,F11,",
                        "G4,G8,",
                        "H5,H6,H7,",
                        "L1,L6,L11",
                        NULL
                );
                package_body_width = 6.00;
                package_body_length = 6.00;
                package_body_height = 1.00;
                package_is_radial = FALSE;
                number_of_columns = 11;
                number_of_rows = 11;
                pitch_x = 0.50;
                pitch_y = 0.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.25;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 7.00;
                courtyard_width = 7.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 6.00;
                silkscreen_width = 6.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C50P11X11_600X600X100");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C50P14X14_800X800X120"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strconcat
                (
                        "C3,C4,C5,C6,C7,C9,C10,C11,C12,",
                        "D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,",
                        "E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,",
                        "F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,",
                        "G4,G5,G6,G7,G8,G9,G10,G11,G12,",
                        "H3,H4,H5,H6,H7,H8,H9,H10,H11,",
                        "J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,",
                        "K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,",
                        "L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,",
                        "M3,M4,M5,M6,M8,M9,M10,M11,M12,",
                        NULL
                );
                package_body_width = 8.00;
                package_body_length = 8.00;
                package_body_height = 1.20;
                package_is_radial = FALSE;
                number_of_columns = 14;
                number_of_rows = 14;
                pitch_x = 0.50;
                pitch_y = 0.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.25;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 10.00;
                courtyard_width = 10.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 8.00;
                silkscreen_width = 8.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C50P14X14_800X800X120");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C50P14X14_800X800X135"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strconcat
                (
                        "C4,C5,C6,C7,C8,C9,C10,C11,",
                        "D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,",
                        "E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,",
                        "F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,",
                        "G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,",
                        "H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,",
                        "J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,",
                        "K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,",
                        "L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,",
                        "M4,M5,M6,M7,M8,M9,M10,M11,",
                        NULL
                );
                package_body_width = 8.00;
                package_body_length = 8.00;
                package_body_height = 1.35;
                package_is_radial = FALSE;
                number_of_columns = 14;
                number_of_rows = 14;
                pitch_x = 0.50;
                pitch_y = 0.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.25;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 10.00;
                courtyard_width = 10.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 8.00;
                silkscreen_width = 8.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C50P14X14_800X800X135");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C50P15X15_1000X1000X120"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strconcat
                (
                        "B2,B14,",
                        "C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,",
                        "D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13,",
                        "E3,E4,E5,E6,E7,E8,E9,E10,E11,E12,E13,",
                        "F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,",
                        "G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,G13,",
                        "H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,H13,",
                        "J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,J13,",
                        "K3,K4,K5,K6,K7,K8,K9,K10,K11,K12,K13,",
                        "L3,L4,L5,L6,L7,L8,L9,L10,L11,L12,L13,",
                        "M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,",
                        "N3,N4,N5,N6,N7,N8,N9,N10,N11,N12,N13,",
                        "P2,P14,",
                        NULL
                );
                package_body_width = 10.00;
                package_body_length = 10.00;
                package_body_height = 1.20;
                package_is_radial = FALSE;
                number_of_columns = 15;
                number_of_rows = 15;
                pitch_x = 0.50;
                pitch_y = 0.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.25;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 12.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.00;
                silkscreen_width = 10.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C50P15X15_1000X1000X120");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C65P10X10_800X800X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 8.00;
                package_body_length = 8.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 10;
                pitch_x = 0.65;
                pitch_y = 0.65;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.30;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 10.00;
                courtyard_width = 10.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 8.00;
                silkscreen_width = 8.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C65P10X10_800X800X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C80P10X10_1000X1000X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 10.00;
                package_body_length = 10.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 10;
                pitch_x = 0.80;
                pitch_y = 0.80;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 12.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.00;
                silkscreen_width = 10.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C80P10X10_1000X1000X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C80P10X10_1000X1000X150"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 10.00;
                package_body_length = 10.00;
                package_body_height = 1.50;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 10;
                pitch_x = 0.80;
                pitch_y = 0.80;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.40;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 12.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.00;
                silkscreen_width = 10.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C80P10X10_1000X1000X150");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C80P10X10_900X900X100"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 9.00;
                package_body_length = 9.00;
                package_body_height = 1.00;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 10;
                pitch_x = 0.80;
                pitch_y = 0.80;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.35;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 11.00;
                courtyard_width = 11.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 9.00;
                silkscreen_width = 9.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C80P10X10_900X900X100");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C80P10X10_900X900X150"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 9.00;
                package_body_length = 9.00;
                package_body_height = 1.50;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 10;
                pitch_x = 0.80;
                pitch_y = 0.80;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.40;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 11.00;
                courtyard_width = 11.00;
                silkscreen_length = 9.00;
                silkscreen_width = 9.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C80P10X10_900X900X150");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C80P11X11_1100X1100X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strconcat
                (
                        "D5,D6,D7,",
                        "E4,E5,E6,E7,E8,",
                        "F4,F5,F6,F7,F8,",
                        "G4,G5,G6,G7,G8,",
                        "H5,H6,H7,",
                        NULL
                );
                package_body_width = 11.00;
                package_body_length = 11.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 11;
                number_of_rows = 11;
                pitch_x = 0.80;
                pitch_y = 0.80;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.40;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 13.00;
                courtyard_width = 13.00;
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C80P11X11_1100X1100X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1020C100P32X32_3300X3300X350"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1020;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A32,",
                        "AM1,AM32,",
                        NULL
                );
                package_body_width = 33.00;
                package_body_length = 33.00;
                package_body_height = 3.50;
                package_is_radial = FALSE;
                number_of_columns = 32;
                number_of_rows = 32;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 35.00;
                courtyard_width = 35.00;
                silkscreen_length = 33.00;
                silkscreen_width = 33.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1020C100P32X32_3300X3300X350");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1023C100P32X32_3300X3300X350"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1023;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1",
                        NULL
                );
                package_body_width = 33.00;
                package_body_length = 33.00;
                package_body_height = 3.50;
                package_is_radial = FALSE;
                number_of_columns = 32;
                number_of_rows = 32;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.40;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 35.00;
                courtyard_width = 35.00;
                silkscreen_length = 33.00;
                silkscreen_width = 33.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1023C100P32X32_3300X3300X350");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1024C100P32X32_3300X3300X350"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1024;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 33.00;
                package_body_length = 33.00;
                package_body_height = 3.50;
                package_is_radial = FALSE;
                number_of_columns = 32;
                number_of_rows = 32;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 35.00;
                courtyard_width = 35.00;
                silkscreen_length = 33.00;
                silkscreen_width = 33.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1024C100P32X32_3300X3300X350");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA103C65P8X13_600X900X100"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 103;
                pin_pad_exceptions_string = g_strconcat
                (
                        "C3",
                        NULL
                );
                package_body_width = 6.00;
                package_body_length = 9.00;
                package_body_height = 1.00;
                package_is_radial = FALSE;
                number_of_columns = 8;
                number_of_rows = 13;
                pitch_x = 0.65;
                pitch_y = 0.65;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.25;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 8.00;
                courtyard_width = 11.00;
                silkscreen_length = 6.00;
                silkscreen_width = 9.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA103C65P8X13_600X900X100");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1056C100P39X39_4000X4000X380"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1056;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A2,A3,A37,A38,A39,",
                        "B1,B2,B38,B39,",
                        "C1,C39,",
                        "K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K30,",
                        "L10,L11,L12,L13,L14,L15,L16,L17,L18,L19,L20,L21,L22,L23,L24,L25,L26,L27,L28,L29,L30,",
                        "M10,M11,M12,M13,M14,M15,M16,M17,M18,M19,M20,M21,M22,M23,M24,M25,M26,M27,M28,M29,M30,",
                        "N10,N11,N12,N13,N14,N15,N16,N17,N18,N19,N20,N21,N22,N23,N24,N25,N26,N27,N28,N29,N30,",
                        "P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28,P29,P30,",
                        "R10,R11,R12,R13,R14,R15,R16,R17,R18,R19,R20,R21,R22,R23,R24,R25,R26,R27,R28,R29,R30,",
                        "T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,",
                        "U10,U11,U12,U13,U14,U15,U16,U17,U18,U19,U20,U21,U22,U23,U24,U25,U26,U27,U28,U29,U30,",
                        "V10,V11,V12,V13,V14,V15,V16,V17,V18,V19,V20,V21,V22,V23,V24,V25,V26,V27,V28,V29,V30,",
                        "W10,W11,W12,W13,W14,W15,W16,W17,W18,W19,W20,W21,W22,W23,W24,W25,W26,W27,W28,W29,W30,",
                        "Y10,Y11,Y12,Y13,Y14,Y15,Y16,Y17,Y18,Y19,Y20,Y21,Y22,Y23,Y24,Y25,Y26,Y27,Y28,Y29,Y30,",
                        "AA10,AA11,AA12,AA13,AA14,AA15,AA16,AA17,AA18,AA19,AA20,AA21,AA22,AA23,AA24,AA25,AA26,AA27,AA28,AA29,AA30,",
                        "AB10,AB11,AB12,AB13,AB14,AB15,AB16,AB17,AB18,AB19,AB20,AB21,AB22,AB23,AB24,AB25,AB26,AB27,AB28,AB29,AB30,",
                        "AC10,AC11,AC12,AC13,AC14,AC15,AC16,AC17,AC18,AC19,AC20,AC21,AC22,AC23,AC24,AC25,AC26,AC27,AC28,AC29,AC30,",
                        "AD10,AD11,AD12,AD13,AD14,AD15,AD16,AD17,AD18,AD19,AD20,AD21,AD22,AD23,AD24,AD25,AD26,AD27,AD28,AD29,AD30,",
                        "AE10,AE11,AE12,AE13,AE14,AE15,AE16,AE17,AE18,AE19,AE20,AE21,AE22,AE23,AE24,AE25,AE26,AE27,AE28,AE29,AE30,",
                        "AF10,AF11,AF12,AF13,AF14,AF15,AF16,AF17,AF18,AF19,AF20,AF21,AF22,AF23,AF24,AF25,AF26,AF27,AF28,AF29,AF30,",
                        "AG10,AG11,AG12,AG13,AG14,AG15,AG16,AG17,AG18,AG19,AG20,AG21,AG22,AG23,AG24,AG25,AG26,AG27,AG28,AG29,AG30,",
                        "AH10,AH11,AH12,AH13,AH14,AH15,AH16,AH17,AH18,AH19,AH20,AH21,AH22,AH23,AH24,AH25,AH26,AH27,AH28,AH29,AH30,",
                        "AJ10,AJ11,AJ12,AJ13,AJ14,AJ15,AJ16,AJ17,AJ18,AJ19,AJ20,AJ21,AJ22,AJ23,AJ24,AJ25,AJ26,AJ27,AJ28,AJ29,AJ30,",
                        "AK10,AK11,AK12,AK13,AK14,AK15,AK16,AK17,AK18,AK19,AK20,AK21,AK22,AK23,AK24,AK25,AK26,AK27,AK28,AK29,AK30,",
                        "AU1,AU39,",
                        "AV1,AV2,AV38,AV39,",
                        "AW1,AW2,AW3,AW37,AW38,AW39,",
                        NULL
                );
                package_body_width = 40.00;
                package_body_length = 40.00;
                package_body_height = 3.80;
                package_is_radial = FALSE;
                number_of_columns = 39;
                number_of_rows = 39;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 42.00;
                courtyard_width = 42.00;
                silkscreen_length = 40.00;
                silkscreen_width = 40.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1056C100P39X39_4000X4000X380");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1056C100P39X39_4000X4000X400"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1056;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A2,A3,A37,A38,A39,",
                        "B1,B2,B38,B39,",
                        "C1,C39,",
                        "K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K30,",
                        "L10,L11,L12,L13,L14,L15,L16,L17,L18,L19,L20,L21,L22,L23,L24,L25,L26,L27,L28,L29,L30,",
                        "M10,M11,M12,M13,M14,M15,M16,M17,M18,M19,M20,M21,M22,M23,M24,M25,M26,M27,M28,M29,M30,",
                        "N10,N11,N12,N13,N14,N15,N16,N17,N18,N19,N20,N21,N22,N23,N24,N25,N26,N27,N28,N29,N30,",
                        "P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,P23,P24,P25,P26,P27,P28,P29,P30,",
                        "R10,R11,R12,R13,R14,R15,R16,R17,R18,R19,R20,R21,R22,R23,R24,R25,R26,R27,R28,R29,R30,",
                        "T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,",
                        "U10,U11,U12,U13,U14,U15,U16,U17,U18,U19,U20,U21,U22,U23,U24,U25,U26,U27,U28,U29,U30,",
                        "V10,V11,V12,V13,V14,V15,V16,V17,V18,V19,V20,V21,V22,V23,V24,V25,V26,V27,V28,V29,V30,",
                        "W10,W11,W12,W13,W14,W15,W16,W17,W18,W19,W20,W21,W22,W23,W24,W25,W26,W27,W28,W29,W30,",
                        "Y10,Y11,Y12,Y13,Y14,Y15,Y16,Y17,Y18,Y19,Y20,Y21,Y22,Y23,Y24,Y25,Y26,Y27,Y28,Y29,Y30,",
                        "AA10,AA11,AA12,AA13,AA14,AA15,AA16,AA17,AA18,AA19,AA20,AA21,AA22,AA23,AA24,AA25,AA26,AA27,AA28,AA29,AA30,",
                        "AB10,AB11,AB12,AB13,AB14,AB15,AB16,AB17,AB18,AB19,AB20,AB21,AB22,AB23,AB24,AB25,AB26,AB27,AB28,AB29,AB30,",
                        "AC10,AC11,AC12,AC13,AC14,AC15,AC16,AC17,AC18,AC19,AC20,AC21,AC22,AC23,AC24,AC25,AC26,AC27,AC28,AC29,AC30,",
                        "AD10,AD11,AD12,AD13,AD14,AD15,AD16,AD17,AD18,AD19,AD20,AD21,AD22,AD23,AD24,AD25,AD26,AD27,AD28,AD29,AD30,",
                        "AE10,AE11,AE12,AE13,AE14,AE15,AE16,AE17,AE18,AE19,AE20,AE21,AE22,AE23,AE24,AE25,AE26,AE27,AE28,AE29,AE30,",
                        "AF10,AF11,AF12,AF13,AF14,AF15,AF16,AF17,AF18,AF19,AF20,AF21,AF22,AF23,AF24,AF25,AF26,AF27,AF28,AF29,AF30,",
                        "AG10,AG11,AG12,AG13,AG14,AG15,AG16,AG17,AG18,AG19,AG20,AG21,AG22,AG23,AG24,AG25,AG26,AG27,AG28,AG29,AG30,",
                        "AH10,AH11,AH12,AH13,AH14,AH15,AH16,AH17,AH18,AH19,AH20,AH21,AH22,AH23,AH24,AH25,AH26,AH27,AH28,AH29,AH30,",
                        "AJ10,AJ11,AJ12,AJ13,AJ14,AJ15,AJ16,AJ17,AJ18,AJ19,AJ20,AJ21,AJ22,AJ23,AJ24,AJ25,AJ26,AJ27,AJ28,AJ29,AJ30,",
                        "AK10,AK11,AK12,AK13,AK14,AK15,AK16,AK17,AK18,AK19,AK20,AK21,AK22,AK23,AK24,AK25,AK26,AK27,AK28,AK29,AK30,",
                        "AU1,AU39,",
                        "AV1,AV2,AV38,AV39,",
                        "AW1,AW2,AW3,AW37,AW38,AW39,",
                        NULL
                );
                package_body_width = 40.00;
                package_body_length = 40.00;
                package_body_height = 4.00;
                package_is_radial = FALSE;
                number_of_columns = 39;
                number_of_rows = 39;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 42.00;
                courtyard_width = 42.00;
                silkscreen_length = 40.00;
                silkscreen_width = 40.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1056C100P39X39_4000X4000X400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA105C50P15X15_800X800X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 105;
                pin_pad_exceptions_string = g_strconcat
                (
                        "B14",
                        "C3,C4,C5,C6,C7,C8,C9,C10,C11,C12,C13,",
                        "D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D13,",
                        "E3,E4,E6,E7,E8,E9,E10,E12,E13,",
                        "F3,F4,F5,F6,F7,F8,F9,F10,F11,F12,F13,",
                        "G2,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,G13,",
                        "H3,H4,H5,H6,H7,H8,H9,H10,H11,H12,H13,",
                        "J3,J4,J5,J6,J7,J8,J9,J10,J11,J12,J13,",
                        "K3,K4,K5,K6,K7,K8,K9,K10,K12,K13,",
                        "L3,L4,L6,L7,L8,L9,L10,L12,L13,",
                        "M3,M4,M5,M6,M7,M8,M9,M10,M11,M12,M13,",
                        "N3,N4,N5,N6,N7,N8,N9,N10,N11,N12,N13,",
                        "P2,P14,",
                        NULL
                );
                package_body_width = 8.00;
                package_body_length = 8.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 15;
                number_of_rows = 15;
                pitch_x = 0.50;
                pitch_y = 0.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.25;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 9.00;
                courtyard_width = 9.00;
                silkscreen_length = 8.10;
                silkscreen_width = 8.10;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA105C50P15X15_800X800X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA107C80P10X14_1050X1300X120"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 107;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A3,A4,A5,A6,A7,A8,",
                        "C1,C10,",
                        "D1,D10,",
                        "E1,E10,",
                        "F1,F10,",
                        "G1,G10,",
                        "H1,H10,",
                        "J1,J10,",
                        "K1,K10,",
                        "L1,L10,",
                        "M1,M10,",
                        "P3,P4,P5,P6,P7,P8,",
                        NULL
                );
                package_body_width = 10.50;
                package_body_length = 13.00;
                package_body_height = 1.20;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 14;
                pitch_x = 0.80;
                pitch_y = 0.80;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.40;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.50;
                courtyard_width = 15.00;
                silkscreen_length = 10.50;
                silkscreen_width = 13.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA107C80P10X14_1050X1300X120");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA107C80P10X14_1050X1300X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 107;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A3,A4,A5,A6,A7,A8,",
                        "C1,C10,",
                        "D1,D10,",
                        "E1,E10,",
                        "F1,F10,",
                        "G1,G10,",
                        "H1,H10,",
                        "J1,J10,",
                        "K1,K10,",
                        "L1,L10,",
                        "M1,M10,",
                        "P3,P4,P5,P6,P7,P8,",
                        NULL
                );
                package_body_width = 10.50;
                package_body_length = 13.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 14;
                pitch_x = 0.80;
                pitch_y = 0.80;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.40;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.50;
                courtyard_width = 15.00;
                silkscreen_length = 10.50;
                silkscreen_width = 13.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA107C80P10X14_1050X1300X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA107C80P10X14_1050X1600X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 107;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A3,A4,A5,A6,A7,A8,",
                        "C1,C10,",
                        "D1,D10,",
                        "E1,E10,",
                        "F1,F10,",
                        "G1,G10,",
                        "H1,H10,",
                        "J1,J10,",
                        "K1,K10,",
                        "L1,L10,",
                        "M1,M10,",
                        "P3,P4,P5,P6,P7,P8,",
                        NULL
                );
                package_body_width = 10.50;
                package_body_length = 16.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 14;
                pitch_x = 0.80;
                pitch_y = 0.80;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.40;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.50;
                courtyard_width = 15.00;
                silkscreen_length = 10.50;
                silkscreen_width = 16.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA107C80P10X14_1050X1600X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1089C100P33X33_3500X3500X350"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1089;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 35.00;
                package_body_length = 35.00;
                package_body_height = 3.50;
                package_is_radial = FALSE;
                number_of_columns = 33;
                number_of_rows = 33;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 37.00;
                courtyard_width = 37.00;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1089C100P33X33_3500X3500X350");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1089C127P33X33_4250X4250X350"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1089;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 42.50;
                package_body_length = 42.50;
                package_body_height = 3.50;
                package_is_radial = FALSE;
                number_of_columns = 33;
                number_of_rows = 33;
                pitch_x = 1.27;
                pitch_y = 1.27;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.55;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 46.50;
                courtyard_width = 46.50;
                silkscreen_length = 42.50;
                silkscreen_width = 42.50;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1089C127P33X33_4250X4250X350");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA109C50P12X12_700X700X100"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 108;
                pin_pad_exceptions_string = g_strconcat
                (
                        "D5,D6,D7,D8,D9,",
                        "E4,E5,E6,E7,E8,E9,",
                        "F4,F5,F6,F7,F8,F9,",
                        "G4,G5,G6,G7,G8,G9,",
                        "H4,H5,H6,H7,H8,H9,",
                        "J4,J5,J6,J7,J8,J9,",
                        NULL
                );
                package_body_width = 7.00;
                package_body_length = 7.00;
                package_body_height = 1.00;
                package_is_radial = FALSE;
                number_of_columns = 12;
                number_of_rows = 12;
                pitch_x = 0.50;
                pitch_y = 0.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.25;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 8.00;
                courtyard_width = 8.00;
                silkscreen_length = 7.00;
                silkscreen_width = 7.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA109C50P12X12_700X700X100");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA10C50P3X4_220X250X60"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 10;
                pin_pad_exceptions_string = g_strconcat
                (
                        "B2,",
                        "C2,",
                        NULL
                );
                package_body_width = 2.20;
                package_body_length = 2.50;
                package_body_height = 0.60;
                package_is_radial = FALSE;
                number_of_columns = 3;
                number_of_rows = 4;
                pitch_x = 0.50;
                pitch_y = 0.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.25;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 3.20;
                courtyard_width = 3.50;
                silkscreen_length = 2.20;
                silkscreen_width = 2.60;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA10C50P3X4_220X250X60");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA10N50P3X4_200X250X94"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 10;
                pin_pad_exceptions_string = g_strconcat
                (
                        "B2,",
                        "C2,",
                        NULL
                );
                package_body_width = 2.00;
                package_body_length = 2.50;
                package_body_height = 0.94;
                package_is_radial = FALSE;
                number_of_columns = 3;
                number_of_rows = 4;
                pitch_x = 0.50;
                pitch_y = 0.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.24;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 3.00;
                courtyard_width = 3.50;
                silkscreen_length = 2.10;
                silkscreen_width = 2.60;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA10N50P3X4_200X250X94");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA111C80P12X13_1000X1100X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 111;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A3,A4,A5,A6,A7,A8,A9,A10",
                        "D1,D2,D11,D12,",
                        "E1,E2,E11,E12,",
                        "F1,F2,F11,F12,",
                        "G1,G2,G11,G12,",
                        "H1,H2,H11,H12,",
                        "J1,J2,J11,J12,",
                        "K1,K2,K11,K12,",
                        "N3,N4,N5,N6,N7,N8,N9,N10",
                        NULL
                );
                package_body_width = 10.00;
                package_body_length = 11.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 12;
                number_of_rows = 13;
                pitch_x = 0.80;
                pitch_y = 0.80;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.40;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 13.00;
                silkscreen_length = 10.00;
                silkscreen_width = 11.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA111C80P12X13_1000X1100X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA111C80P12X13_1100X1100X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 111;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A3,A4,A5,A6,A7,A8,A9,A10",
                        "D1,D2,D11,D12,",
                        "E1,E2,E11,E12,",
                        "F1,F2,F11,F12,",
                        "G1,G2,G11,G12,",
                        "H1,H2,H11,H12,",
                        "J1,J2,J11,J12,",
                        "K1,K2,K11,K12,",
                        "N3,N4,N5,N6,N7,N8,N9,N10",
                        NULL
                );
                package_body_width = 11.00;
                package_body_length = 11.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 12;
                number_of_rows = 13;
                pitch_x = 0.80;
                pitch_y = 0.80;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.40;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 13.00;
                courtyard_width = 13.00;
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA111C80P12X13_1100X1100X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA112C80P11X11_1000X1000X130"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 112;
                pin_pad_exceptions_string = g_strconcat
                (
                        "E5,E6,E7,",
                        "F5,F6,F7,",
                        "G5,G6,G7,",
                        NULL
                );
                package_body_width = 10.00;
                package_body_length = 10.00;
                package_body_height = 1.30;
                package_is_radial = FALSE;
                number_of_columns = 11;
                number_of_rows = 11;
                pitch_x = 0.80;
                pitch_y = 0.80;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.35;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 12.00;
                courtyard_width = 12.00;
                silkscreen_length = 10.00;
                silkscreen_width = 10.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA112C80P11X11_1000X1000X130");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1148C100P34X34_3500X3500X340"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1148;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A34,",
                        "P14,P21,",
                        "AA14,AA21,",
                        "AP1,AP34,",
                        NULL
                );
                package_body_width = 35.00;
                package_body_length = 35.00;
                package_body_height = 3.40;
                package_is_radial = FALSE;
                number_of_columns = 34;
                number_of_rows = 34;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 37.00;
                courtyard_width = 37.00;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1148C100P34X34_3500X3500X340");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA114C80P6X19_550X1600X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 114;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 5.50;
                package_body_length = 16.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 6;
                number_of_rows = 19;
                pitch_x = 0.80;
                pitch_y = 0.80;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.40;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 7.50;
                courtyard_width = 18.00;
                silkscreen_length = 5.50;
                silkscreen_width = 16.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA114C80P6X19_550X1600X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1152C100P34X34_3500X3500X340"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1148;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A34,",
                        "AP1,AP34,",
                        NULL
                );
                package_body_width = 35.00;
                package_body_length = 35.00;
                package_body_height = 3.40;
                package_is_radial = FALSE;
                number_of_columns = 34;
                number_of_rows = 34;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 37.00;
                courtyard_width = 37.00;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1152C100P34X34_3500X3500X340");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1152C100P34X34_3500X3500X350"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1148;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A34,",
                        "AP1,AP34,",
                        NULL
                );
                package_body_width = 35.00;
                package_body_length = 35.00;
                package_body_height = 3.50;
                package_is_radial = FALSE;
                number_of_columns = 34;
                number_of_rows = 34;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 37.00;
                courtyard_width = 37.00;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1152C100P34X34_3500X3500X350");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1156C100P34X34_3500X3500X260"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1156;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 35.00;
                package_body_length = 35.00;
                package_body_height = 2.60;
                package_is_radial = FALSE;
                number_of_columns = 34;
                number_of_rows = 34;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 37.00;
                courtyard_width = 37.00;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1156C100P34X34_3500X3500X260");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1156C100P34X34_3500X3500X311"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1156;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 35.00;
                package_body_length = 35.00;
                package_body_height = 3.11;
                package_is_radial = FALSE;
                number_of_columns = 34;
                number_of_rows = 34;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 37.00;
                courtyard_width = 37.00;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1156C100P34X34_3500X3500X311");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1156C100P34X34_3500X3500X350"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1156;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 35.00;
                package_body_length = 35.00;
                package_body_height = 3.50;
                package_is_radial = FALSE;
                number_of_columns = 34;
                number_of_rows = 34;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 37.00;
                courtyard_width = 37.00;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1156C100P34X34_3500X3500X350");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1156C100P34X34_3500X3500X380"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1156;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 35.00;
                package_body_length = 35.00;
                package_body_height = 3.80;
                package_is_radial = FALSE;
                number_of_columns = 34;
                number_of_rows = 34;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 37.00;
                courtyard_width = 37.00;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1156C100P34X34_3500X3500X380");
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
 * \brief Set GUI constraints for the BGA package type.
 */
int
bga_set_gui_constraints (GtkWidget *widget)
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
        GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pin_drill_diameter_entry");
        gtk_entry_set_text (GTK_ENTRY (pin_drill_diameter_entry), "");
        gtk_widget_set_sensitive (pin_drill_diameter_entry, FALSE);
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
        GtkWidget *fiducial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "fiducial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (fiducial_checkbutton),
                FALSE);
        gtk_widget_set_sensitive (fiducial_checkbutton, TRUE);
        GtkWidget *fiducial_pad_diameter_entry = lookup_widget
                (GTK_WIDGET (widget),
                "fiducial_pad_diameter_entry");
        gtk_widget_set_sensitive (fiducial_pad_diameter_entry, TRUE);
        GtkWidget *fiducial_pad_solder_mask_clearance_entry = lookup_widget
                (GTK_WIDGET (widget),
                "fiducial_pad_solder_mask_clearance_entry");
        gtk_widget_set_sensitive (fiducial_pad_solder_mask_clearance_entry,
                TRUE);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}
#endif /* GUI */


/*!
 * \brief Write a footprint for a BGA package.
 */
int
bga_write_footprint ()
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
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not open file for %s footprint: %s."),
                        footprint_type, footprint_filename);
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
                                write_pad
                                (
                                        pin_number, /* pin number */
                                        pin_pad_name, /* pin name */
                                        multiplier * ((((-number_of_columns -1) / 2.0) + 1 + j) * pitch_x), /* x0 coordinate */
                                        multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y), /* y0-coordinate */
                                        multiplier * ((((-number_of_columns -1) / 2.0) + 1 + j) * pitch_x), /* x1 coordinate */
                                        multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y), /* y1-coordinate */
                                        multiplier * pad_diameter, /* pad width */
                                        multiplier * pad_clearance, /* clearance */
                                        multiplier * (pad_diameter + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                        pin_pad_flags /* flags */
                                );
                        }
                        pin_number++;
                }
        }
        /* Write fiducials if the package seem to have them. */
        if (fiducial)
        {
                fprintf (fp, "# Write fiducials\n");
                pin_pad_name = g_strdup ("");
                pin_pad_flags = g_strdup ("");
                write_pad
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        multiplier * ((silkscreen_length - courtyard_length > 2) ?
                                (courtyard_length / 2) :
                                ((courtyard_length / 2 ) + 1)),
                                /* x0 coordinate */
                        multiplier * ((silkscreen_width - courtyard_width > 2) ?
                                (-courtyard_width / 2) :
                                ((-courtyard_width / 2 ) - 1)),
                                /* y0 coordinate */
                        multiplier * ((silkscreen_length - courtyard_length > 2) ?
                                (courtyard_length / 2) :
                                ((courtyard_length / 2 ) + 1)),
                                /* x1 coordinate */
                        multiplier * ((silkscreen_width - courtyard_width > 2) ?
                                (-courtyard_width / 2) :
                                ((-courtyard_width / 2 ) - 1)),
                                /* y1 coordinate */
                        multiplier * fiducial_pad_diameter, /* pad width */
                        multiplier * fiducial_pad_solder_mask_clearance,
                                /* pad clearance */
                        multiplier * (fiducial_pad_diameter +
                                (2 * fiducial_pad_solder_mask_clearance)),
                                /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
                pin_number++;
                write_pad
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        multiplier * ((silkscreen_length - courtyard_length > 2) ?
                                (-courtyard_length / 2) :
                                ((-courtyard_length / 2 ) - 1)),
                                /* x0 coordinate */
                        multiplier * ((silkscreen_width - courtyard_width > 2) ?
                                (courtyard_width / 2) :
                                ((courtyard_width / 2 ) + 1)),
                                /* y0 coordinate */
                        multiplier * ((silkscreen_length - courtyard_length > 2) ?
                                (-courtyard_length / 2) :
                                ((-courtyard_length / 2 ) - 1)),
                                /* x1 coordinate */
                        multiplier * ((silkscreen_width - courtyard_width > 2) ?
                                (courtyard_width / 2) :
                                ((courtyard_width / 2 ) + 1)),
                                /* y1 coordinate */
                        multiplier * fiducial_pad_diameter, /* pad width */
                        multiplier * fiducial_pad_solder_mask_clearance,
                                /* pad clearance */
                        multiplier * (fiducial_pad_diameter +
                                (2 * fiducial_pad_solder_mask_clearance)),
                                /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
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
        g_log ("", G_LOG_LEVEL_INFO,
                _("wrote a footprint file for a %s package: %s."),
                footprint_type, footprint_filename);
}


static fpw_function_t
bga_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                bga_set_gui_constraints,
                "Set GUI constraints for a BGA package",
                NULL
        },
#endif /* GUI */
        {
                "Create Element",
                bga_create_element,
                "Create a pcb element for a BGA package",
                NULL
        },
        {
                "DRC BGA Element",
                bga_drc,
                "Design Rule Check for a BGA package",
                NULL
        },
        {
                "Default Element Values",
                bga_get_default_footprint_values,
                "Get default values for a slected BGA package",
                NULL
        },
        {
                "Write footprint",
                bga_write_footprint,
                "Write a footprint for a BGA package",
                NULL
        }
};


REGISTER_FUNCTIONS (bga_function_list)

void
bga_init ()
{
        register_bga_function_list ();
}


/* EOF */
