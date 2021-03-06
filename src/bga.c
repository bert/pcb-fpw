/*!
 * \file src/bga.c
 *
 * \author Copyright 2007-2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Functions for BGA footprints (Ball Gate Array).
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
#include "bga.h"


/*!
 * \brief Create an Element for a BGA package.
 *
 * \return \c EXIT_SUCCESS when an element was created,
 * \c EXIT_FAILURE when errors were encountered.
 */
int
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
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] could not create a valid element pointer for an element.")),
                                footprint_type);
                }
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
        /* If the user input is using even more real-estate then use it. */
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
        /* Store the courtyard dimensions in Virtual (bounding) Box. */
        element->VBox.X1 = (int) xmin;
        element->VBox.Y1 = (int) ymin;
        element->VBox.X2 = (int) xmax;
        element->VBox.Y2 = (int) ymax;
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
                        {
                                pad_flag.f = SQUARE;
                        }
                        else
                        {
                                pad_flag.f = CLEAR;
                        }
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
                        "0", /* pin number */
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
                        "0", /* pin number */
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
 * \brief Create a list of known BGA packages.
 *
 * The data in this list can be used in a combo box to select a
 * pre-defined package.\n
 *
 * \return \c EXIT_SUCCESS when a packages list was created,
 * \c EXIT_FAILURE when errors were encountered.
 */
int
bga_create_packages_list ()
{
        g_list_free (packages_list);
        packages_list = g_list_prepend (packages_list, "BGA100C100P10X10_1100X1100X140");
        packages_list = g_list_prepend (packages_list, "BGA100C100P10X10_1100X1100X170");
        packages_list = g_list_prepend (packages_list, "BGA100C100P10X10_1100X1100X170A");
        packages_list = g_list_prepend (packages_list, "BGA100C100P10X10_1100X1100X200");
        packages_list = g_list_prepend (packages_list, "BGA100C100P10X10_1100X1100X350");
        packages_list = g_list_prepend (packages_list, "BGA100C50P10X10_600X600X110");
        packages_list = g_list_prepend (packages_list, "BGA100C50P11X11_600X600X100");
        packages_list = g_list_prepend (packages_list, "BGA100C50P14X14_800X800X120");
        packages_list = g_list_prepend (packages_list, "BGA100C50P14X14_800X800X135");
        packages_list = g_list_prepend (packages_list, "BGA100C50P15X15_1000X1000X120");
        packages_list = g_list_prepend (packages_list, "BGA100C65P10X10_800X800X140");
        packages_list = g_list_prepend (packages_list, "BGA100C80P10X10_1000X1000X140");
        packages_list = g_list_prepend (packages_list, "BGA100C80P10X10_1000X1000X150");
        packages_list = g_list_prepend (packages_list, "BGA100C80P10X10_900X900X100");
        packages_list = g_list_prepend (packages_list, "BGA100C80P10X10_900X900X120");
        packages_list = g_list_prepend (packages_list, "BGA100C80P10X10_900X900X120A");
        packages_list = g_list_prepend (packages_list, "BGA100C80P10X10_900X900X140");
        packages_list = g_list_prepend (packages_list, "BGA100C80P10X10_900X900X150");
        packages_list = g_list_prepend (packages_list, "BGA100C80P10X10_900X900X160");
        packages_list = g_list_prepend (packages_list, "BGA100C80P11X11_1100X1100X140");
        packages_list = g_list_prepend (packages_list, "BGA100C80P12X12_1200X1200X140");
        packages_list = g_list_prepend (packages_list, "BGA1020C100P32X32_3300X3300X350");
        packages_list = g_list_prepend (packages_list, "BGA1023C100P32X32_3300X3300X272");
        packages_list = g_list_prepend (packages_list, "BGA1023C100P32X32_3300X3300X287");
        packages_list = g_list_prepend (packages_list, "BGA1023C100P32X32_3300X3300X350");
        packages_list = g_list_prepend (packages_list, "BGA1024C100P32X32_3300X3300X350");
        packages_list = g_list_prepend (packages_list, "BGA1036C100P44X44_4500X4500X275");
        packages_list = g_list_prepend (packages_list, "BGA103C65P8X13_600X900X100");
        packages_list = g_list_prepend (packages_list, "BGA1056C100P39X39_4000X4000X380");
        packages_list = g_list_prepend (packages_list, "BGA1056C100P39X39_4000X4000X400");
        packages_list = g_list_prepend (packages_list, "BGA105C50P15X15_800X800X140");
        packages_list = g_list_prepend (packages_list, "BGA105C65P11X11_800X800X140");
        packages_list = g_list_prepend (packages_list, "BGA107C80P10X14_1050X1300X120");
        packages_list = g_list_prepend (packages_list, "BGA107C80P10X14_1050X1300X140");
        packages_list = g_list_prepend (packages_list, "BGA107C80P10X14_1050X1600X140");
        packages_list = g_list_prepend (packages_list, "BGA1089C100P33X33_3500X3500X350");
        packages_list = g_list_prepend (packages_list, "BGA1089C127P33X33_4250X4250X350");
        packages_list = g_list_prepend (packages_list, "BGA108C100P12X12_1300X1300X185");
        packages_list = g_list_prepend (packages_list, "BGA108C80P12X12_1000X1000X140");
        packages_list = g_list_prepend (packages_list, "BGA109C50P12X12_700X700X100");
        packages_list = g_list_prepend (packages_list, "BGA109C80P12X12_1000X1000X140");
        packages_list = g_list_prepend (packages_list, "BGA10C50P3X4_150X200X63");
        packages_list = g_list_prepend (packages_list, "BGA10C50P3X4_220X250X60");
        packages_list = g_list_prepend (packages_list, "BGA10C50P3X4_200X250X94");
        packages_list = g_list_prepend (packages_list, "BGA10N50P3X4_200X250X94");
        packages_list = g_list_prepend (packages_list, "BGA111C80P12X13_1000X1100X140");
        packages_list = g_list_prepend (packages_list, "BGA111C80P12X13_1100X1100X140");
        packages_list = g_list_prepend (packages_list, "BGA112C50P12X12_700X700X112");
        packages_list = g_list_prepend (packages_list, "BGA112C80P11X11_1000X1000X130");
        packages_list = g_list_prepend (packages_list, "BGA1148C100P34X34_3500X3500X340");
        packages_list = g_list_prepend (packages_list, "BGA114C80P6X19_550X1600X140");
        packages_list = g_list_prepend (packages_list, "BGA114C80P6X19_550X1600X150");
        packages_list = g_list_prepend (packages_list, "BGA1152C100P34X34_3500X3500X244");
        packages_list = g_list_prepend (packages_list, "BGA1152C100P34X34_3500X3500X332");
        packages_list = g_list_prepend (packages_list, "BGA1152C100P34X34_3500X3500X340");
        packages_list = g_list_prepend (packages_list, "BGA1152C100P34X34_3500X3500X350");
        packages_list = g_list_prepend (packages_list, "BGA1156C100P34X34_3500X3500X260");
        packages_list = g_list_prepend (packages_list, "BGA1156C100P34X34_3500X3500X311");
        packages_list = g_list_prepend (packages_list, "BGA1156C100P34X34_3500X3500X350");
        packages_list = g_list_prepend (packages_list, "BGA1156C100P34X34_3500X3500X380");
        packages_list = g_list_prepend (packages_list, "BGA1156C100P34X34_3500X3500X400");
        packages_list = g_list_prepend (packages_list, "BGA1156C100P34X34_3600X3600X450");
        packages_list = g_list_prepend (packages_list, "BGA115C80P10X14_800X1200X140");
        packages_list = g_list_prepend (packages_list, "BGA1160C100P39X39_4000X4000X245");
        packages_list = g_list_prepend (packages_list, "BGA1172C100P39X39_4000X4000X310");
        packages_list = g_list_prepend (packages_list, "BGA119C127P7X17_1400X2200X196");
        packages_list = g_list_prepend (packages_list, "BGA119C127P7X17_1400X2200X221");
        packages_list = g_list_prepend (packages_list, "BGA119C127P7X17_1400X2200X240");
        packages_list = g_list_prepend (packages_list, "BGA120C50P11X11_600X600X100");
        packages_list = g_list_prepend (packages_list, "BGA120C50P11X11_600X600X80");
        packages_list = g_list_prepend (packages_list, "BGA120C50P13X13_700X700X140");
        packages_list = g_list_prepend (packages_list, "BGA120C80P10X13_1000X1300X120");
        packages_list = g_list_prepend (packages_list, "BGA1216C100P41X41_4250X4250X380");
        packages_list = g_list_prepend (packages_list, "BGA1216C100P41X41_4250X4250X400");
        packages_list = g_list_prepend (packages_list, "BGA121C100P11X11_1200X1200X185");
        packages_list = g_list_prepend (packages_list, "BGA121C100P11X11_1200X1200X350");
        packages_list = g_list_prepend (packages_list, "BGA121C50P14X14_1000X1300X110");
        packages_list = g_list_prepend (packages_list, "BGA121C50P14X14_1000X1300X130");
        packages_list = g_list_prepend (packages_list, "BGA121C50P14X14_1050X1600X130");
        packages_list = g_list_prepend (packages_list, "BGA121C65P11X11_800X800X130");
        packages_list = g_list_prepend (packages_list, "BGA124C100P14X14_1500X1500X170");
        packages_list = g_list_prepend (packages_list, "BGA124C50P13X13_800X800X120");
        packages_list = g_list_prepend (packages_list, "BGA124C65P12X12_900X900X140");
        packages_list = g_list_prepend (packages_list, "BGA127C80P12X13_10500X1200X140");
        packages_list = g_list_prepend (packages_list, "BGA1284C100P36X36_3750X3750X380");
        packages_list = g_list_prepend (packages_list, "BGA1284C100P36X36_3750X3750X400");
        packages_list = g_list_reverse (packages_list);
        return (EXIT_SUCCESS);
}


/*!
 * \brief Do some Design Rule Checking for the BGA package type.
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
bga_drc ()
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
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        (_("[%s] DRC Error: square pad shape specified for check for allowed pad shapes.")),
                                        footprint_type);
                        }
                        result = EXIT_FAILURE;
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
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        (_("[%s] DRC Error: round elongated pad shape specified for check for allowed pad shapes.")),
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
                                        (_("[%s] DRC Error: no valid pad shape type specified.")),
                                        footprint_type);
                        }
                        result = EXIT_FAILURE;
                        break;
                }
        }
        /* Check for a square pad #1. */
        if (pin1_square)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: package should not have a square pad #1.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
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
                result = EXIT_FAILURE;
        }
        /* Check for minimum clearance between copper (X-direction). */
        if (pitch_x - pad_diameter < pad_clearance)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: minimum clearance between copper (X-direction) is too small.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        /* Check for minimum clearance between copper (Y-direction). */
        if (pitch_y - pad_diameter < pad_clearance)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: minimum clearance between copper (Y-direction) is too small.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        /* Check for fiducials */
        if (fiducial)
        {
                /* Check for a zero width fiducial pad. */
                if (fiducial_pad_diameter == 0.0)
                {
                        if (verbose)
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        (_("[%s] DRC Error: zero width fiducial pad.")),
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
                                        (_("[%s] DRC Error: fiducial has zero width solder mask clearance.")),
                                        footprint_type);
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
                                        (_("[%s] DRC Error: specified distance between fiducial and nearest pad is to small.")),
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
                                (_("[%s] DRC Error: clearance of the package length with regard to the courtyard dimensions is too small.")),
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
                                (_("[%s] DRC Error: clearance of the package width with regard to the courtyard dimensions is too small.")),
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
        return (result);
}


/*!
 * \brief Look up default values for BGA footprints.
 *
 * Footprint values can be looked up by placing a question mark "?" in
 * front of the footprint name.\n
 * If the footprint name is recognised the known values will be loaded
 * and the entries involved in the GUI will be updated accordingly.\n
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
 * - BGA100C80P10X10_900X900X120,
 * - BGA100C80P10X10_900X900X120A,
 * - BGA100C80P10X10_900X900X140,
 * - BGA100C80P10X10_900X900X150,
 * - BGA100C80P10X10_900X900X160,
 * - BGA100C80P11X11_1100X1100X140,
 * - BGA100C80P12X12_1000X1000X140,
 * - BGA1020C100P32X32_3300X3300X350,
 * - BGA1023C100P32X32_3300X3300X272,
 * - BGA1023C100P32X32_3300X3300X287,
 * - BGA1023C100P32X32_3300X3300X350,
 * - BGA1024C100P32X32_3300X3300X350,
 * - BGA103C65P8X13_600X900X100,
 * - BGA1036C100P44X44_4500X4500X275,
 * - BGA1056C100P39X39_4000X4000X380,
 * - BGA1056C100P39X39_4000X4000X400,
 * - BGA105C50P15X15_800X800X140,
 * - BGA105C65P11X11_800X800X140,
 * - BGA107C80P10X14_1050X1300X120,
 * - BGA107C80P10X14_1050X1300X140,
 * - BGA107C80P10X14_1050X1600X140,
 * - BGA1089C100P33X33_3500X3500X350,
 * - BGA1089C127P33X33_4250X4250X350,
 * - BGA108C100P12X12_1300X1300X85,
 * - BGA108C80P12X12_1000X1000X140,
 * - BGA109C50P12X12_700X700X100,
 * - BGA109C80P12X12_1000X1000X140,
 * - BGA10C50P3X4_150X200X63,
 * - BGA10C50P3X4_220X250X60,
 * - BGA10C50P3X4_220X250X94,
 * - BGA10N50P3X4_200X250X94,
 * - BGA111C80P12X13_1000X1100X140,
 * - BGA111C80P12X13_1100X1100X140,
 * - BGA112C50P12X12_700X700X112,
 * - BGA112C80P11X11_1000X1000X130,
 * - BGA1148C100P34X34_3500X3500X340,
 * - BGA114C80P6X19_550X1600X140,
 * - BGA114C80P6X19_550X1600X150,
 * - BGA1152C100P34X34_3500X3500X244,
 * - BGA1152C100P34X34_3500X3500X332,
 * - BGA1152C100P34X34_3500X3500X340,
 * - BGA1152C100P34X34_3500X3500X350,
 * - BGA1156C100P34X34_3500X3500X260,
 * - BGA1156C100P34X34_3500X3500X311,
 * - BGA1156C100P34X34_3500X3500X350,
 * - BGA1156C100P34X34_3500X3500X380,
 * - BGA1156C100P34X34_3500X3500X400,
 * - BGA1156C100P34X34_3600X3600X450,
 * - BGA115C80P10X14_800X1200X140,
 * - BGA1160C100P39X39_4000X4000X245,
 * - BGA1172C100P39X39_4000X4000X310,
 * - BGA119C127P7X17_1400X2200X196,
 * - BGA119C127P7X17_1400X2200X221,
 * - BGA119C127P7X17_1400X2200X240,
 * - BGA120C50P11X11_600X600X100,
 * - BGA120C50P11X11_600X600X80,
 * - BGA120C50P13X13_700X700X140,
 * - BGA120C80P10X13_1000X1300X120,
 * - BGA1216C100P41X41_4250X4250X380,
 * - BGA1216C100P41X41_4250X4250X400,
 * - BGA121C100P11X11_1200X1200X185,
 * - BGA121C100P11X11_1200X1200X350,
 * - BGA121C50P14X14_1000X1300X110,
 * - BGA121C50P14X14_1000X1300X130,
 * - BGA121C50P14X14_1050X1600X130,
 * - BGA121C65P11X11_800X800X130,
 * - BGA124C100P14X14_1500X1500X170,
 * - BGA124C50P13X13_800X800X120,
 * - BGA124C65P12X12_900X900X140,
 * - BGA127C80P12X13_10500X1200X140,
 * - BGA1284C100P36X36_3750X3750X380,
 * - BGA1284C100P36X36_3750X3750X400,
 *
 * \return \c EXIT_SUCCESS when default values for a footprint were
 * found, \c EXIT_FAILURE when the footprint name was not found.
 */
int
bga_get_default_footprint_values ()
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
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
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
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 13.00;
                courtyard_width = 13.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C100P10X10_1100X1100X170");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-192AAC-1.");
                }
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
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
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
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
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
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 13.00;
                courtyard_width = 13.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                silkscreen_line_width = 0.20;
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
                footprint_name = g_strdup ("BGA100C50P10X10_600X600X110");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-195.");
                }
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
                fiducial_pad_clearance = 1.00;
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
                fiducial_pad_clearance = 1.00;
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
                fiducial_pad_clearance = 1.00;
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
                fiducial_pad_clearance = 1.00;
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
                fiducial_pad_clearance = 1.00;
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
                fiducial_pad_clearance = 1.00;
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
                fiducial_pad_clearance = 1.00;
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
                fiducial_pad_clearance = 1.00;
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
        else if (!strcmp (footprint_name, "?BGA100C80P10X10_900X900X120"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 9.00;
                package_body_length = 9.00;
                package_body_height = 1.20;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 11.00;
                courtyard_width = 11.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 9.00;
                silkscreen_width = 9.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C80P10X10_900X900X120");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C80P10X10_900X900X120A"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 9.00;
                package_body_length = 9.00;
                package_body_height = 1.20;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 11.00;
                courtyard_width = 11.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 9.00;
                silkscreen_width = 9.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C80P10X10_900X900X120A");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-216.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C80P10X10_900X900X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 9.00;
                package_body_length = 9.00;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 11.00;
                courtyard_width = 11.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 9.00;
                silkscreen_width = 9.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C80P10X10_900X900X140");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-205AB.");
                }
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
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 11.00;
                courtyard_width = 11.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 9.00;
                silkscreen_width = 9.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C80P10X10_900X900X150");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C80P10X10_900X900X160"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 9.00;
                package_body_length = 9.00;
                package_body_height = 1.60;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 11.00;
                courtyard_width = 11.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 9.00;
                silkscreen_width = 9.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C80P10X10_900X900X160");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MS-205.");
                }
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
                pad_diameter = 0.45;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 13.00;
                courtyard_width = 13.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C80P11X11_1100X1100X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA100C80P12X12_1000X1000X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strconcat
                (
                        "C3,C4,C5,C6,C7,C8,C9,C10,",
                        "D3,D10,",
                        "E3,E5,E6,E7,E8,E10,",
                        "F3,F5,F6,F7,F8,F10,",
                        "G3,G5,E6,G7,G8,G10,",
                        "H3,H5,H6,H7,H8,H10,",
                        "J3,J10,",
                        "K3,K4,K5,K6,K7,K8,K9,K10,",
                        NULL
                );
                package_body_width = 10.00;
                package_body_length = 10.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 12;
                number_of_rows = 12;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 12.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.00;
                silkscreen_width = 10.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C80P12X12_1000X1000X140");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-205AC.");
                }
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
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 37.00;
                courtyard_width = 37.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 33.00;
                silkscreen_width = 33.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1020C100P32X32_3300X3300X350");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MS-034AAP-1.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1023C100P32X32_3300X3300X272"))
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
                package_body_height = 2.72;
                package_is_radial = FALSE;
                number_of_columns = 32;
                number_of_rows = 32;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 37.00;
                courtyard_width = 37.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 33.00;
                silkscreen_width = 33.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1023C100P32X32_3300X3300X272");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1023C100P32X32_3300X3300X287"))
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
                package_body_height = 2.87;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 35.00;
                courtyard_width = 35.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 33.00;
                silkscreen_width = 33.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1023C100P32X32_3300X3300X287");
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
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 35.00;
                courtyard_width = 35.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 33.00;
                silkscreen_width = 33.00;
                silkscreen_line_width = 0.20;
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
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 35.00;
                courtyard_width = 35.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 33.00;
                silkscreen_width = 33.00;
                silkscreen_line_width = 0.20;
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
                package_body_length = 6.00;
                package_body_width = 9.00;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 8.00;
                courtyard_width = 11.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 6.00;
                silkscreen_width = 9.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA103C65P8X13_600X900X100");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1036C100P44X44_4500X4500X275"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1036;
                pin_pad_exceptions_string = g_strconcat
                (
                        "H8,H9,H10,H11,H12,H13,H14,H15,H16,H17,H18,H19,H20,H21,H22,",
                        "H23,H24,H25,H26,H27,H28,H29,H30,H31,H32,H33,H34,H35,H36,H37,",
                        "J8,J9,J10,J11,J12,J13,J14,J15,J16,J17,J18,J19,J20,J21,J22,",
                        "J23,J24,J25,J26,J27,J28,J29,J30,J31,J32,J33,J34,J35,J36,J37,",
                        "K8,K9,K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K20,K21,K22,",
                        "K23,K24,K25,K26,K27,K28,K29,K30,K31,K32,K33,K34,K35,K36,K37,",
                        "L8,L9,L10,L11,L12,L13,L14,L15,L16,L17,L18,L19,L20,L21,L22,",
                        "L23,L24,L25,L26,L27,L28,L29,L30,L31,L32,L33,L34,L35,L36,L37,",
                        "M8,M9,M10,M11,M12,M13,M14,M15,M16,M17,M18,M19,M20,M21,M22,",
                        "M23,M24,M25,M26,M27,M28,M29,M30,M31,M32,M33,M34,M35,M36,M37,",
                        "N8,N9,N10,N11,N12,N13,N14,N15,N16,N17,N18,N19,N20,N21,N22,",
                        "N23,N24,N25,N26,N27,N28,N29,N30,N31,N32,N33,N34,N35,N36,N37,",
                        "P8,P9,P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,P21,P22,",
                        "P23,P24,P25,P26,P27,P28,P29,P30,P31,P32,P33,P34,P35,P36,P37,",
                        "R8,R9,R10,R11,R12,R13,R14,R15,R16,R17,R18,R19,R20,R21,R22,",
                        "R23,R24,R25,R26,R27,R28,R29,R30,R31,R32,R33,R34,R35,R36,R37,",
                        "T8,T9,T10,T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,T21,T22,",
                        "T23,T24,T25,T26,T27,T28,T29,T30,T31,T32,T33,T34,T35,T36,T37,",
                        "U8,U9,U10,U11,U12,U13,U14,U15,U16,U17,U18,U19,U20,U21,U22,",
                        "U23,U24,U25,U26,U27,U28,U29,U30,U31,U32,U33,U34,U35,U36,U37,",
                        "V8,V9,V10,V11,V12,V13,V14,V15,V16,V17,V18,V19,V20,V21,V22,",
                        "V23,V24,V25,V26,V27,V28,V29,V30,V31,V32,V33,V34,V35,V36,V37,",
                        "W8,W9,W10,W11,W12,W13,W14,W15,W16,W17,W18,W19,W20,W21,W22,",
                        "W23,W24,W25,W26,W27,W28,W29,W30,W31,W32,W33,W34,W35,W36,W37,",
                        "Y8,Y9,Y10,Y11,Y12,Y13,Y14,Y15,Y16,Y17,Y18,Y19,Y20,Y21,Y22,",
                        "Y23,Y24,Y25,Y26,Y27,Y28,Y29,Y30,Y31,Y32,Y33,Y34,Y35,Y36,Y37,",
                        "AA8,AA9,AA10,AA11,AA12,AA13,AA14,AA15,AA16,AA17,AA18,AA19,AA20,AA21,AA22,",
                        "AA23,AA24,AA25,AA26,AA27,AA28,AA29,AA30,AA31,AA32,AA33,AA34,AA35,AA36,AA37,",
                        "AB8,AB9,AB10,AB11,AB12,AB13,AB14,AB15,AB16,AB17,AB18,AB19,AB20,AB21,AB22,",
                        "AB23,AB24,AB25,AB26,AB27,AB28,AB29,AB30,AB31,AB32,AB33,AB34,AB35,AB36,AB37,",
                        "AC8,AC9,AC10,AC11,AC12,AC13,AC14,AC15,AC16,AC17,AC18,AC19,AC20,AC21,AC22,",
                        "AC23,AC24,AC25,AC26,AC27,AC28,AC29,AC30,AC31,AC32,AC33,AC34,AC35,AC36,AC37,",
                        "AD8,AD9,AD10,AD11,AD12,AD13,AD14,AD15,AD16,AD17,AD18,AD19,AD20,AD21,AD22,",
                        "AD23,AD24,AD25,AD26,AD27,AD28,AD29,AD30,AD31,AD32,AD33,AD34,AD35,AD36,AD37,",
                        "AE8,AE9,AE10,AE11,AE12,AE13,AE14,AE15,AE16,AE17,AE18,AE19,AE20,AE21,AE22,",
                        "AE23,AE24,AE25,AE26,AE27,AE28,AE29,AE30,AE31,AE32,AE33,AE34,AE35,AE36,AE37,",
                        "AF8,AF9,AF10,AF11,AF12,AF13,AF14,AF15,AF16,AF17,AF18,AF19,AF20,AF21,AF22,",
                        "AF23,AF24,AF25,AF26,AF27,AF28,AF29,AF30,AF31,AF32,AF33,AF34,AF35,AF36,AF37,",
                        "AG8,AG9,AG10,AG11,AG12,AG13,AG14,AG15,AG16,AG17,AG18,AG19,AG20,AG21,AG22,",
                        "AG23,AG24,AG25,AG26,AG27,AG28,AG29,AG30,AG31,AG32,AG33,AG34,AG35,AG36,AG37,",
                        "AH8,AH9,AH10,AH11,AH12,AH13,AH14,AH15,AH16,AH17,AH18,AH19,AH20,AH21,AH22,",
                        "AH23,AH24,AH25,AH26,AH27,AH28,AH29,AH30,AH31,AH32,AH33,AH34,AH35,AH36,AH37,",
                        "AJ8,AJ9,AJ10,AJ11,AJ12,AJ13,AJ14,AJ15,AJ16,AJ17,AJ18,AJ19,AJ20,AJ21,AJ22,",
                        "AJ23,AJ24,AJ25,AJ26,AJ27,AJ28,AJ29,AJ30,AJ31,AJ32,AJ33,AJ34,AJ35,AJ36,AJ37,",
                        "AK8,AK9,AK10,AK11,AK12,AK13,AK14,AK15,AK16,AK17,AK18,AK19,AK20,AK21,AK22,",
                        "AK23,AK24,AK25,AK26,AK27,AK28,AK29,AK30,AK31,AK32,AK33,AK34,AK35,AK36,AK37,",
                        "AL8,AL9,AL10,AL11,AL12,AL13,AL14,AL15,AL16,AL17,AL18,AL19,AL20,AL21,AL22,",
                        "AL23,AL24,AL25,AL26,AL27,AL28,AL29,AL30,AL31,AL32,AL33,AL34,AL35,AL36,AL37,",
                        "AM8,AM9,AM10,AM11,AM12,AM13,AM14,AM15,AM16,AM17,AM18,AM19,AM20,AM21,AM22,",
                        "AM23,AM24,AM25,AM26,AM27,AM28,AM29,AM30,AM31,AM32,AM33,AM34,AM35,AM36,AM37,",
                        "AN8,AN9,AN10,AN11,AN12,AN13,AN14,AN15,AN16,AN17,AN18,AN19,AN20,AN21,AN22,",
                        "AN23,AN24,AN25,AN26,AN27,AN28,AN29,AN30,AN31,AN32,AN33,AN34,AN35,AN36,AN37,",
                        "AP8,AP9,AP10,AP11,AP12,AP13,AP14,AP15,AP16,AP17,AP18,AP19,AP20,AP21,AP22,",
                        "AP23,AP24,AP25,AP26,AP27,AP28,AP29,AP30,AP31,AP32,AP33,AP34,AP35,AP36,AP37,",
                        "AR8,AR9,AR10,AR11,AR12,AR13,AR14,AR15,AR16,AR17,AR18,AR19,AR20,AR21,AR22,",
                        "AR23,AR24,AR25,AR26,AR27,AR28,AR29,AR30,AR31,AR32,AR33,AR34,AR35,AR36,AR37,",
                        "AT8,AT9,AT10,AT11,AT12,AT13,AT14,AT15,AT16,AT17,AT18,AT19,AT20,AT21,AT22,",
                        "AT23,AT24,AT25,AT26,AT27,AT28,AT29,AT30,AT31,AT32,AT33,AT34,AT35,AT36,AT37,",
                        "AU8,AU9,AU10,AU11,AU12,AU13,AU14,AU15,AU16,AU17,AU18,AU19,AU20,AU21,AU22,",
                        "AU23,AU24,AU25,AU26,AU27,AU28,AU29,AU30,AU31,AU32,AU33,AU34,AU35,AU36,AU37,",
                        NULL
                );
                package_body_width = 45.00;
                package_body_length = 45.00;
                package_body_height = 2.75;
                package_is_radial = FALSE;
                number_of_columns = 44;
                number_of_rows = 44;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.55;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 49.00;
                courtyard_width = 49.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 45.00;
                silkscreen_width = 45.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1036C100P44X44_4500X4500X275");
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
                pad_diameter = 0.50;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 44.00;
                courtyard_width = 44.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 40.00;
                silkscreen_width = 40.00;
                silkscreen_line_width = 0.20;
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
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 44.00;
                courtyard_width = 44.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 40.00;
                silkscreen_width = 40.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1056C100P39X39_4000X4000X400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA105C65P11X11_800X800X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 105;
                pin_pad_exceptions_string = g_strconcat
                (
                        "D4,D5,D6,D7,D8,",
                        "E4,E8,",
                        "F4,F8,",
                        "G4,G8,",
                        "H4,H5,H6,H7,H8,",
                        NULL
                );
                package_body_width = 8.00;
                package_body_length = 8.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 11;
                number_of_rows = 11;
                pitch_x = 0.65;
                pitch_y = 0.65;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.35;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 10.00;
                courtyard_width = 10.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 8.00;
                silkscreen_width = 8.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA105C65P11X11_800X800X140");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-225.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA105C50P15X15_800X800X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 105;
                pin_pad_exceptions_string = g_strconcat
                (
                        "B14,",
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 10.00;
                courtyard_width = 10.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 8.00;
                silkscreen_width = 8.00;
                silkscreen_line_width = 0.20;
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
                package_body_length = 10.50;
                package_body_width = 13.00;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.50;
                courtyard_width = 15.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.50;
                silkscreen_width = 13.00;
                silkscreen_line_width = 0.20;
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
                package_body_length = 10.50;
                package_body_width = 13.00;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.50;
                courtyard_width = 15.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.50;
                silkscreen_width = 13.00;
                silkscreen_line_width = 0.20;
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
                package_body_length = 10.50;
                package_body_width = 16.00;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.50;
                courtyard_width = 18.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.50;
                silkscreen_width = 16.00;
                silkscreen_line_width = 0.20;
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
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 37.00;
                courtyard_width = 37.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                silkscreen_line_width = 0.20;
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
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 46.50;
                courtyard_width = 46.50;
                courtyard_line_width = 0.05;
                silkscreen_length = 42.50;
                silkscreen_width = 42.50;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1089C127P33X33_4250X4250X350");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA108C100P12X12_1300X1300X185"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 108;
                pin_pad_exceptions_string = g_strconcat
                (
                        "D4,D5,D6,D7,D8,D9,",
                        "E4,E5,E6,E7,E8,E9,",
                        "F4,F5,F6,F7,F8,F9,",
                        "G4,G5,G6,G7,G8,G9,",
                        "H4,H5,H6,H7,H8,H9,",
                        "J4,J5,J6,J7,J8,J9,",
                        NULL
                );
                package_body_width = 13.00;
                package_body_length = 13.00;
                package_body_height = 1.85;
                package_is_radial = FALSE;
                number_of_columns = 12;
                number_of_rows = 12;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.55;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 17.00;
                courtyard_width = 17.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 13.00;
                silkscreen_width = 13.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA108C100P12X12_1300X1300X185");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-192AAD-1.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA108C80P12X12_1000X1000X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 108;
                pin_pad_exceptions_string = g_strconcat
                (
                        "D4,D5,D6,D7,D8,D9,",
                        "E4,E5,E6,E7,E8,E9,",
                        "F4,F5,F6,F7,F8,F9,",
                        "G4,G5,G6,G7,G8,G9,",
                        "H4,H5,H6,H7,H8,H9,",
                        "J4,J5,J6,J7,J8,J9,",
                        NULL
                );
                package_body_width = 10.00;
                package_body_length = 10.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 12;
                number_of_rows = 12;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 12.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.00;
                silkscreen_width = 10.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA108C80P12X12_1000X1000X140");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-205AC.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA109C50P12X12_700X700X100"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 109;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 9.00;
                courtyard_width = 9.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 7.00;
                silkscreen_width = 7.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA109C50P12X12_700X700X100");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA109C80P12X12_1000X1000X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 109;
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
                package_body_width = 10.00;
                package_body_length = 10.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 12;
                number_of_rows = 12;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 12.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.00;
                silkscreen_width = 10.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA109C80P12X12_1000X1000X140");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-205AC.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA10C50P3X4_150X200X63"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 10;
                pin_pad_exceptions_string = g_strconcat
                (
                        "B2,",
                        "C2,",
                        NULL
                );
                package_body_length = 1.50;
                package_body_width = 2.00;
                package_body_height = 0.63;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 3.50;
                courtyard_width = 4.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 2.00;
                silkscreen_width = 2.50;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA10C50P3X4_150X200X63");
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
                package_body_length = 2.20;
                package_body_width = 2.50;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 4.20;
                courtyard_width = 4.50;
                courtyard_line_width = 0.05;
                silkscreen_length = 2.20;
                silkscreen_width = 2.50;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA10C50P3X4_220X250X60");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-211BD.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA10C50P3X4_200X250X94"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 10;
                pin_pad_exceptions_string = g_strconcat
                (
                        "B2,",
                        "C2,",
                        NULL
                );
                package_body_length = 2.00;
                package_body_width = 2.50;
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
                pad_diameter = 0.25;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 4.20;
                courtyard_width = 4.50;
                courtyard_line_width = 0.05;
                silkscreen_length = 2.20;
                silkscreen_width = 2.50;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA10C50P3X4_200X250X94");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-211BD.");
                }
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
                package_body_length = 2.00;
                package_body_width = 2.50;
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
                pad_diameter = 0.21;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 3.00;
                courtyard_width = 3.50;
                courtyard_line_width = 0.05;
                silkscreen_length = 2.00;
                silkscreen_width = 2.50;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA10N50P3X4_200X250X94");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-211BC.");
                }
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
                package_body_length = 10.00;
                package_body_width = 11.00;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 13.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.00;
                silkscreen_width = 11.00;
                silkscreen_line_width = 0.20;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 13.00;
                courtyard_width = 13.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA111C80P12X13_1100X1100X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA112C50P12X12_700X700X112"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 112;
                pin_pad_exceptions_string = g_strconcat
                (
                        "D5,D6,D7,D8,",
                        "E4,E5,E6,E7,E8,E9,",
                        "E4,F5,F6,F7,F8,F9,",
                        "G4,G5,G6,G7,G8,G9,",
                        "H4,H5,H6,H7,H8,H9,",
                        "J5,J6,J7,J8,",
                        NULL
                );
                package_body_width = 7.00;
                package_body_length = 7.00;
                package_body_height = 1.12;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 9.00;
                courtyard_width = 9.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 7.00;
                silkscreen_width = 7.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA112C50P12X12_700X700X112");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MO-195.");
                }
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 12.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.00;
                silkscreen_width = 10.00;
                silkscreen_line_width = 0.20;
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
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 39.00;
                courtyard_width = 39.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1148C100P34X34_3500X3500X340");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MS-034AAR-1.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA114C80P6X19_550X1600X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 114;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_length = 5.50;
                package_body_width = 16.00;
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
                pad_diameter = 0.45;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 7.50;
                courtyard_width = 18.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 5.50;
                silkscreen_width = 16.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA114C80P6X19_550X1600X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA114C80P6X19_550X1600X150"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 114;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_length = 5.50;
                package_body_width = 16.00;
                package_body_height = 1.50;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 7.50;
                courtyard_width = 18.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 5.50;
                silkscreen_width = 16.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA114C80P6X19_550X1600X150");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1152C100P34X34_3500X3500X244"))
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
                package_body_height = 2.44;
                package_is_radial = FALSE;
                number_of_columns = 34;
                number_of_rows = 34;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 39.00;
                courtyard_width = 39.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1152C100P34X34_3500X3500X244");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MS-034AAR-1.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1152C100P34X34_3500X3500X332"))
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
                package_body_height = 3.32;
                package_is_radial = FALSE;
                number_of_columns = 34;
                number_of_rows = 34;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 39.00;
                courtyard_width = 39.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1152C100P34X34_3500X3500X332");
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
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 37.00;
                courtyard_width = 37.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1152C100P34X34_3500X3500X340");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MS-034AAR-1.");
                }
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
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 39.00;
                courtyard_width = 39.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1152C100P34X34_3500X3500X350");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MS-034AAR-1.");
                }
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
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 39.00;
                courtyard_width = 39.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1156C100P34X34_3500X3500X260");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MS-034AAR-1.");
                }
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
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 39.00;
                courtyard_width = 39.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1156C100P34X34_3500X3500X311");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MS-034AAR-1.");
                }
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
                fiducial_pad_clearance = 0.00;
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
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 39.00;
                courtyard_width = 39.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1156C100P34X34_3500X3500X380");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1156C100P34X34_3500X3500X400"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1156;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 35.00;
                package_body_length = 35.00;
                package_body_height = 4.00;
                package_is_radial = FALSE;
                number_of_columns = 34;
                number_of_rows = 34;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 39.00;
                courtyard_width = 39.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 35.00;
                silkscreen_width = 35.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1156C100P34X34_3500X3500X400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1156C100P34X34_3600X3600X400"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1156;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 36.00;
                package_body_length = 36.00;
                package_body_height = 4.50;
                package_is_radial = FALSE;
                number_of_columns = 34;
                number_of_rows = 34;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 40.00;
                courtyard_width = 40.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 36.00;
                silkscreen_width = 36.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1156C100P34X34_3600X3600X450");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA115C80P10X14_800X1200X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 115;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A3,A4,A5,A6,A7,A8,",
                        "B3,B4,B5,B6,B7,B8,",
                        "C1,",
                        "N3,N4,N5,N6,N7,N8,",
                        "P3,P4,P5,P6,P7,P8,",
                        NULL
                );
                package_body_length = 8.00;
                package_body_width = 12.00;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 10.00;
                courtyard_width = 14.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 8.30;
                silkscreen_width = 12.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA115C80P10X14_800X1200X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1160C100P39X39_4000X4000X245"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1160;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,",
                        "K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,",
                        "K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K30,",
                        "L10,L11,L12,L13,L14,L15,L16,L17,L18,L19,",
                        "L20,L21,L22,L23,L24,L25,L26,L27,L28,L29,L30,",
                        "M10,M11,M12,M13,M14,M15,M16,M17,M18,M19,",
                        "M20,M21,M22,M23,M24,M25,M26,M27,M28,M29,M30,",
                        "N10,N11,N12,N13,N14,N15,N16,N17,N18,N19,",
                        "N20,N21,N22,N23,N24,N25,N26,N27,N28,N29,N30,",
                        "P10,P11,P12,P13,P14,P15,P16,P17,P18,P19,",
                        "P20,P21,P22,P23,P24,P25,P26,P27,P28,P29,P30,",
                        "R10,R11,R12,R13,R14,R15,R16,R17,R18,R19,",
                        "R20,R21,R22,R23,R24,R25,R26,R27,R28,R29,R30,",
                        "T10,T11,T12,T13,T14,T15,T25,T26,T27,T28,T29,T30,",
                        "U10,U11,U12,U13,U14,U15,U25,U26,U27,U28,U29,U30,",
                        "V10,V11,V12,V13,V14,V15,V25,V26,V27,V28,V29,V30,",
                        "W10,W11,W12,W13,W14,W15,W25,W26,W27,W28,W29,W30,",
                        "Y10,Y11,Y12,Y13,Y14,Y15,Y25,Y26,Y27,Y28,Y29,Y30,",
                        "AA10,AA11,AA12,AA13,AA14,AA15,AA25,AA26,AA27,AA28,AA29,AA30,",
                        "AB10,AB11,AB12,AB13,AB14,AB15,AB25,AB26,AB27,AB28,AB29,AB30,",
                        "AC10,AC11,AC12,AC13,AC14,AC15,AC25,AC26,AC27,AC28,AC29,AC30,",
                        "AD10,AD11,AD12,AD13,AD14,AD15,AD25,AD26,AD27,AD28,AD29,AD30,",
                        "AE10,AE11,AE12,AE13,AE14,AE15,AE16,AE17,AE18,AE19,",
                        "AE20,AE21,AE22,AE23,AE24,AE25,AE26,AE27,AE28,AE29,AE30,",
                        "AF10,AF11,AF12,AF13,AF14,AF15,AF16,AF17,AF18,AF19,",
                        "AF20,AF21,AF22,AF23,AF24,AF25,AF26,AF27,AF28,AF29,AF30,",
                        "AG10,AG11,AG12,AG13,AG14,AG15,AG16,AG17,AG18,AG19,",
                        "AG20,AG21,AG22,AG23,AG24,AG25,AG26,AG27,AG28,AG29,AG30,",
                        "AH10,AH11,AH12,AH13,AH14,AH15,AH16,AH17,AH18,AH19,",
                        "AH20,AH21,AH22,AH23,AH24,AH25,AH26,AH27,AH28,AH29,AH30,",
                        "AJ10,AJ11,AJ12,AJ13,AJ14,AJ15,AJ16,AJ17,AJ18,AJ19,",
                        "AJ20,AJ21,AJ22,AJ23,AJ24,AJ25,AJ26,AJ27,AJ28,AJ29,AJ30,",
                        "AK10,AK11,AK12,AK13,AK14,AK15,AK16,AK17,AK18,AK19,",
                        "AK20,AK21,AK22,AK23,AK24,AK25,AK26,AK27,AK28,AK29,AK30,",
                        NULL
                );
                package_body_width = 40.00;
                package_body_length = 40.00;
                package_body_height = 2.45;
                package_is_radial = FALSE;
                number_of_columns = 39;
                number_of_rows = 39;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 44.00;
                courtyard_width = 44.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 40.00;
                silkscreen_width = 40.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1160C100P39X39_4000X4000X245");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")),
                                footprint_name,
                                " JEDEC MS-034.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1172C100P39X39_4000X4000X310"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1172;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A2,A3,A4,A5,A6,A7,A33,A34,A35,A36,A37,A38,A39,",
                        "B1,B2,B3,B4,B5,B6,B34,B35,B36,B37,B38,B39,",
                        "C1,C2,C3,C4,C5,C35,C36,C37,C38,C39,",
                        "D1,D2,D3,D4,D36,D37,D38,D39,",
                        "E1,E2,E3,E37,E38,E39,",
                        "F1,F2,F38,F39,",
                        "G1,G39,"
                        "L12,L13,L14,L15,L16,L17,L18,L19,",
                        "L20,L21,L22,L23,L24,L25,L26,L27,L28,",
                        "M11,M12,M13,M14,M15,M16,M17,M18,M19,",
                        "M20,M21,M22,M23,M24,M25,M26,M27,M28,M29,",
                        "N11,N12,N13,N14,N15,N16,N17,N18,N19,",
                        "N20,N21,N22,N23,N24,N25,N26,N27,N28,N29,",
                        "P11,P12,P13,P14,P15,P16,P17,P18,P19,",
                        "P20,P21,P22,P23,P24,P25,P26,P27,P28,P29,",
                        "R11,R12,R13,R14,R15,R26,R27,R28,R29,",
                        "T11,T12,T13,T14,T26,T27,T28,T29,",
                        "U11,U12,U13,U14,U26,U27,U28,U29,",
                        "V11,V12,V13,V14,V26,V27,V28,V29,",
                        "W11,W12,W13,W14,W26,W27,W28,W29,",
                        "Y11,Y12,Y13,Y14,Y26,Y27,Y28,Y29,",
                        "AA11,AA12,AA13,AA14,AA26,AA27,AA28,AA29,",
                        "AB11,AB12,AB13,AB14,AB26,AB27,AB28,AB29,",
                        "AC11,AC12,AC13,AC14,AC26,AC27,AC28,AC29,",
                        "AD11,AD12,AD13,AD14,AD26,AD27,AD28,AD29,",
                        "AE11,AE12,AE13,AE14,AE26,AE27,AE28,AE29,",
                        "AF11,AF12,AF13,AF14,AF15,AF16,AF17,AF18,AF19,",
                        "AF20,AF21,AF22,AF23,AF24,AF25,AF26,AF27,AF28,AF29,",
                        "AG11,AG12,AG13,AG14,AG15,AG16,AG17,AG18,AG19,",
                        "AG20,AG21,AG22,AG23,AG24,AG25,AG26,AG27,AG28,AG29,",
                        "AH11,AH12,AH13,AH14,AH15,AH16,AH17,AH18,AH19,",
                        "AH20,AH21,AH22,AH23,AH24,AH25,AH26,AH27,AH28,AH29,",
                        "AJ12,AJ13,AJ14,AJ15,AJ16,AJ17,AJ18,AJ19,",
                        "AJ20,AJ21,AJ22,AJ23,AJ24,AJ25,AJ26,AJ27,AJ28,",
                        "AN1,AN39,",
                        "AP1,AP2,AK38,AK39,",
                        "AR1,AR2,AR3,AR37,AR38,AR39,",
                        "AT1,AT2,AT3,AT4,AT36,AT37,AT38,AT39,",
                        "AU1,AU2,AU3,AU4,AU5,AU35,AU36,AU37,AU38,AU39,",
                        "AV1,AV2,AV3,AV4,AV5,AV6,AV34,AV35,AV36,AV37,AV38,AV39,",
                        "AW1,AW2,AW3,AW4,AW5,AW6,AW7,AW33,AW34,AW35,AW36,AW37,AW38,AW39,",
                        NULL
                );
                package_body_width = 40.00;
                package_body_length = 40.00;
                package_body_height = 3.10;
                package_is_radial = FALSE;
                number_of_columns = 39;
                number_of_rows = 39;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 44.00;
                courtyard_width = 44.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 40.00;
                silkscreen_width = 40.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1172C100P39X39_4000X4000X310");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " JEDEC MS-034.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA119C127P7X17_1400X2200X196"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 119;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_length = 14.00;
                package_body_width = 22.00;
                package_body_height = 1.96;
                package_is_radial = FALSE;
                number_of_columns = 7;
                number_of_rows = 17;
                pitch_x = 1.27;
                pitch_y = 1.27;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.60;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 18.00;
                courtyard_width = 26.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 14.00;
                silkscreen_width = 22.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA119C127P7X17_1400X2200X196");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA119C127P7X17_1400X2200X221"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 119;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_length = 14.00;
                package_body_width = 22.00;
                package_body_height = 2.21;
                package_is_radial = FALSE;
                number_of_columns = 7;
                number_of_rows = 17;
                pitch_x = 1.27;
                pitch_y = 1.27;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.60;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 18.00;
                courtyard_width = 26.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 14.00;
                silkscreen_width = 22.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA119C127P7X17_1400X2200X221");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA119C127P7X17_1400X2200X240"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 119;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_length = 14.00;
                package_body_width = 22.00;
                package_body_height = 2.40;
                package_is_radial = FALSE;
                number_of_columns = 7;
                number_of_rows = 17;
                pitch_x = 1.27;
                pitch_y = 1.27;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.60;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 18.00;
                courtyard_width = 26.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 14.00;
                silkscreen_width = 22.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA119C127P7X17_1400X2200X240");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA120C50P11X11_600X600X100"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 120;
                pin_pad_exceptions_string = g_strconcat
                (
                        "C3,",
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 8.00;
                courtyard_width = 8.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 6.00;
                silkscreen_width = 6.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA120C50P11X11_600X600X100");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA120C50P11X11_600X600X80"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 120;
                pin_pad_exceptions_string = g_strconcat
                (
                        "C3,",
                        NULL
                );
                package_body_width = 6.00;
                package_body_length = 6.00;
                package_body_height = 0.80;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 8.00;
                courtyard_width = 8.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 6.00;
                silkscreen_width = 6.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA120C50P11X11_600X600X80");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA120C50P13X13_700X700X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 120;
                pin_pad_exceptions_string = g_strconcat
                (
                        "D4,D5,D6,D7,D8,D9,D10,",
                        "E4,E5,E6,E7,E8,E9,E10,",
                        "F4,F5,F6,F7,F8,F9,F10,",
                        "G4,G5,G6,G7,G8,G9,G10,",
                        "H4,H5,H6,H7,H8,H9,H10,",
                        "J4,J5,J6,J7,J8,J9,J10,",
                        "K4,K5,K6,K7,K8,K9,K10,",
                        NULL
                );
                package_body_width = 7.00;
                package_body_length = 7.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 13;
                number_of_rows = 13;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 9.00;
                courtyard_width = 9.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 7.00;
                silkscreen_width = 7.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA120C50P13X13_700X700X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA120C80P10X13_1000X1300X120"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 120;
                pin_pad_exceptions_string = g_strconcat
                (
                        "E5,E6,",
                        "F5,F6,",
                        "G5,G6,",
                        "H5,H6,",
                        "J5,J6,",
                        NULL
                );
                package_body_length = 10.00;
                package_body_width = 13.00;
                package_body_height = 1.20;
                package_is_radial = FALSE;
                number_of_columns = 10;
                number_of_rows = 13;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 15.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.00;
                silkscreen_width = 13.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA120C80P10X13_1000X1300X120");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1216C100P41X41_4250X4250X380"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1216;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A2,A3,A39,A40,A41,",
                        "B1,B2,B40,B41,",
                        "C1,C41,",
                        "L11,L12,L13,L14,L15,L16,L17,L18,L19,L20,",
                        "L21,L22,L23,L24,L25,L26,L27,L28,L29,L30,L31,",
                        "M11,M12,M13,M14,M15,M16,M17,M18,M19,M20,",
                        "M21,M22,M23,M24,M25,M26,M27,M28,M29,M30,M31,",
                        "N11,N12,N13,N14,N15,N16,N17,N18,N19,N20,",
                        "N21,N22,N23,N24,N25,N26,N27,N28,N29,N30,N31,",
                        "P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,",
                        "P21,P22,P23,P24,P25,P26,P27,P28,P29,P30,P31,",
                        "R11,R12,R13,R14,R15,R16,R17,R18,R19,R20,",
                        "R21,R22,R23,R24,R25,R26,R27,R28,R29,R30,R31,",
                        "T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,",
                        "T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,",
                        "U11,U12,U13,U14,U15,U16,U17,U18,U19,U20,",
                        "U21,U22,U23,U24,U25,U26,U27,U28,U29,U30,U31,",
                        "V11,V12,V13,V14,V15,V16,V17,V18,V19,V20,",
                        "V21,V22,V23,V24,V25,V26,V27,V28,V29,V30,V31,",
                        "W11,W12,W13,W14,W15,W16,W17,W18,W19,W20,",
                        "W21,W22,W23,W24,W25,W26,W27,W28,W29,W30,W31,",
                        "Y11,Y12,Y13,Y14,Y15,Y16,Y17,Y18,Y19,Y20,",
                        "Y21,Y22,Y23,Y24,Y25,Y26,Y27,Y28,Y29,Y30,Y31,",
                        "AA11,AA12,AA13,AA14,AA15,AA16,AA17,AA18,AA19,AA20,",
                        "AA21,AA22,AA23,AA24,AA25,AA26,AA27,AA28,AA29,AA30,AA31,",
                        "AB11,AB12,AB13,AB14,AB15,AB16,AB17,AB18,AB19,AB20,",
                        "AB21,AB22,AB23,AB24,AB25,AB26,AB27,AB28,AB29,AB30,AB31,",
                        "AC11,AC12,AC13,AC14,AC15,AC16,AC17,AC18,AC19,AC20,",
                        "AC21,AC22,AC23,AC24,AC25,AC26,AC27,AC28,AC29,AC30,AC31,",
                        "AD11,AD12,AD13,AD14,AD15,AD16,AD17,AD18,AD19,AD20,",
                        "AD21,AD22,AD23,AD24,AD25,AD26,AD27,AD28,AD29,AD30,AD31,",
                        "AE11,AE12,AE13,AE14,AE15,AE16,AE17,AE18,AE19,AE20,",
                        "AE21,AE22,AE23,AE24,AE25,AE26,AE27,AE28,AE29,AE30,AE31,",
                        "AF11,AF12,AF13,AF14,AF15,AF16,AF17,AF18,AF19,AF20,",
                        "AF21,AF22,AF23,AF24,AF25,AF26,AF27,AF28,AF29,AF30,AF31,",
                        "AG11,AG12,AG13,AG14,AG15,AG16,AG17,AG18,AG19,AG20,",
                        "AG21,AG22,AG23,AG24,AG25,AG26,AG27,AG28,AG29,AG30,AG31,",
                        "AH11,AH12,AH13,AH14,AH15,AH16,AH17,AH18,AH19,AH20,",
                        "AH21,AH22,AH23,AH24,AH25,AH26,AH27,AH28,AH29,AH30,AH31,",
                        "AJ11,AJ12,AJ13,AJ14,AJ15,AJ16,AJ17,AJ18,AJ19,AJ20,",
                        "AJ21,AJ22,AJ23,AJ24,AJ25,AJ26,AJ27,AJ28,AJ29,AJ30,AJ31,",
                        "AK11,AK12,AK13,AK14,AK15,AK16,AK17,AK18,AK19,AK20,",
                        "AK21,AK22,AK23,AK24,AK25,AK26,AK27,AK28,AK29,AK30,AK31,",
                        "AL11,AL12,AL13,AL14,AL15,AL16,AL17,AL18,AL19,AL20,",
                        "AL21,AL22,AL23,AL24,AL25,AL26,AL27,AL28,AL29,AL30,AL31,",
                        "AW1,AW41,",
                        "AY1,AY2,AY40,AY41,",
                        "BA1,BA2,BA3,BA39,BA40,BA41,",
                        NULL
                );
                package_body_width = 42.50;
                package_body_length = 42.50;
                package_body_height = 3.80;
                package_is_radial = FALSE;
                number_of_columns = 41;
                number_of_rows = 41;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 46.50;
                courtyard_width = 46.50;
                courtyard_line_width = 0.05;
                silkscreen_length = 42.50;
                silkscreen_width = 42.50;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1216C100P41X41_4250X4250X380");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1216C100P41X41_4250X4250X400"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1216;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A2,A3,A39,A40,A41,",
                        "B1,B2,B40,B41,",
                        "C1,C41,",
                        "L11,L12,L13,L14,L15,L16,L17,L18,L19,L20,",
                        "L21,L22,L23,L24,L25,L26,L27,L28,L29,L30,L31,",
                        "M11,M12,M13,M14,M15,M16,M17,M18,M19,M20,",
                        "M21,M22,M23,M24,M25,M26,M27,M28,M29,M30,M31,",
                        "N11,N12,N13,N14,N15,N16,N17,N18,N19,N20,",
                        "N21,N22,N23,N24,N25,N26,N27,N28,N29,N30,N31,",
                        "P11,P12,P13,P14,P15,P16,P17,P18,P19,P20,",
                        "P21,P22,P23,P24,P25,P26,P27,P28,P29,P30,P31,",
                        "R11,R12,R13,R14,R15,R16,R17,R18,R19,R20,",
                        "R21,R22,R23,R24,R25,R26,R27,R28,R29,R30,R31,",
                        "T11,T12,T13,T14,T15,T16,T17,T18,T19,T20,",
                        "T21,T22,T23,T24,T25,T26,T27,T28,T29,T30,T31,",
                        "U11,U12,U13,U14,U15,U16,U17,U18,U19,U20,",
                        "U21,U22,U23,U24,U25,U26,U27,U28,U29,U30,U31,",
                        "V11,V12,V13,V14,V15,V16,V17,V18,V19,V20,",
                        "V21,V22,V23,V24,V25,V26,V27,V28,V29,V30,V31,",
                        "W11,W12,W13,W14,W15,W16,W17,W18,W19,W20,",
                        "W21,W22,W23,W24,W25,W26,W27,W28,W29,W30,W31,",
                        "Y11,Y12,Y13,Y14,Y15,Y16,Y17,Y18,Y19,Y20,",
                        "Y21,Y22,Y23,Y24,Y25,Y26,Y27,Y28,Y29,Y30,Y31,",
                        "AA11,AA12,AA13,AA14,AA15,AA16,AA17,AA18,AA19,AA20,",
                        "AA21,AA22,AA23,AA24,AA25,AA26,AA27,AA28,AA29,AA30,AA31,",
                        "AB11,AB12,AB13,AB14,AB15,AB16,AB17,AB18,AB19,AB20,",
                        "AB21,AB22,AB23,AB24,AB25,AB26,AB27,AB28,AB29,AB30,AB31,",
                        "AC11,AC12,AC13,AC14,AC15,AC16,AC17,AC18,AC19,AC20,",
                        "AC21,AC22,AC23,AC24,AC25,AC26,AC27,AC28,AC29,AC30,AC31,",
                        "AD11,AD12,AD13,AD14,AD15,AD16,AD17,AD18,AD19,AD20,",
                        "AD21,AD22,AD23,AD24,AD25,AD26,AD27,AD28,AD29,AD30,AD31,",
                        "AE11,AE12,AE13,AE14,AE15,AE16,AE17,AE18,AE19,AE20,",
                        "AE21,AE22,AE23,AE24,AE25,AE26,AE27,AE28,AE29,AE30,AE31,",
                        "AF11,AF12,AF13,AF14,AF15,AF16,AF17,AF18,AF19,AF20,",
                        "AF21,AF22,AF23,AF24,AF25,AF26,AF27,AF28,AF29,AF30,AF31,",
                        "AG11,AG12,AG13,AG14,AG15,AG16,AG17,AG18,AG19,AG20,",
                        "AG21,AG22,AG23,AG24,AG25,AG26,AG27,AG28,AG29,AG30,AG31,",
                        "AH11,AH12,AH13,AH14,AH15,AH16,AH17,AH18,AH19,AH20,",
                        "AH21,AH22,AH23,AH24,AH25,AH26,AH27,AH28,AH29,AH30,AH31,",
                        "AJ11,AJ12,AJ13,AJ14,AJ15,AJ16,AJ17,AJ18,AJ19,AJ20,",
                        "AJ21,AJ22,AJ23,AJ24,AJ25,AJ26,AJ27,AJ28,AJ29,AJ30,AJ31,",
                        "AK11,AK12,AK13,AK14,AK15,AK16,AK17,AK18,AK19,AK20,",
                        "AK21,AK22,AK23,AK24,AK25,AK26,AK27,AK28,AK29,AK30,AK31,",
                        "AL11,AL12,AL13,AL14,AL15,AL16,AL17,AL18,AL19,AL20,",
                        "AL21,AL22,AL23,AL24,AL25,AL26,AL27,AL28,AL29,AL30,AL31,",
                        "AW1,AW41,",
                        "AY1,AY2,AY40,AY41,",
                        "BA1,BA2,BA3,BA39,BA40,BA41,",
                        NULL
                );
                package_body_width = 42.50;
                package_body_length = 42.50;
                package_body_height = 4.00;
                package_is_radial = FALSE;
                number_of_columns = 41;
                number_of_rows = 41;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 46.50;
                courtyard_width = 46.50;
                courtyard_line_width = 0.05;
                silkscreen_length = 42.50;
                silkscreen_width = 42.50;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1216C100P41X41_4250X4250X400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA121C100P11X11_1200X1200X185"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 121;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 12.00;
                package_body_length = 12.00;
                package_body_height = 1.85;
                package_is_radial = FALSE;
                number_of_columns = 11;
                number_of_rows = 11;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 16.00;
                courtyard_width = 16.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 12.00;
                silkscreen_width = 12.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA121C100P11X11_1200X1200X185");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " JEDEC MO-192ABD-1.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA121C100P11X11_1200X1200X350"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 121;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 12.00;
                package_body_length = 12.00;
                package_body_height = 3.50;
                package_is_radial = FALSE;
                number_of_columns = 11;
                number_of_rows = 11;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 16.00;
                courtyard_width = 16.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 12.00;
                silkscreen_width = 12.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA121C100P11X11_1200X1200X350");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " JEDEC MO-192ABD-1.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA121C50P14X14_1000X1300X110"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 121;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A2,A13,A14,",
                        "B1,B14,",
                        "D5,D6,D7,D8,D9,D10,D11,",
                        "E4,E5,E6,E7,E8,E9,E10,E11,",
                        "F4,F5,F6,F7,F8,F9,F10,F11,",
                        "G4,G5,G6,G7,G8,G9,G10,G11,",
                        "H4,H5,H6,H7,H8,H9,H10,H11,",
                        "J4,J5,J6,J7,J8,J9,J10,J11,",
                        "K4,K5,K6,K7,K8,K9,K10,K11",
                        "L4,L5,L6,L7,L8,L9,L10,L11",
                        "N1,N14,",
                        "P1,P2,P13,P14,",
                        NULL
                );
                package_body_length = 10.00;
                package_body_width = 13.00;
                package_body_height = 1.10;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 15.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.00;
                silkscreen_width = 13.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA121C50P14X14_1000X1300X110");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA121C50P14X14_1000X1300X130"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 121;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A2,A13,A14,",
                        "B1,B14,",
                        "D5,D6,D7,D8,D9,D10,D11,",
                        "E4,E5,E6,E7,E8,E9,E10,E11,",
                        "F4,F5,F6,F7,F8,F9,F10,F11,",
                        "G4,G5,G6,G7,G8,G9,G10,G11,",
                        "H4,H5,H6,H7,H8,H9,H10,H11,",
                        "J4,J5,J6,J7,J8,J9,J10,J11,",
                        "K4,K5,K6,K7,K8,K9,K10,K11",
                        "L4,L5,L6,L7,L8,L9,L10,L11",
                        "N1,N14,",
                        "P1,P2,P13,P14,",
                        NULL
                );
                package_body_length = 10.00;
                package_body_width = 13.00;
                package_body_height = 1.30;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 15.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.00;
                silkscreen_width = 13.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA121C50P14X14_1000X1300X130");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA121C50P14X14_1050X1600X130"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 121;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A2,A13,A14,",
                        "B1,B14,",
                        "D5,D6,D7,D8,D9,D10,D11,",
                        "E4,E5,E6,E7,E8,E9,E10,E11,",
                        "F4,F5,F6,F7,F8,F9,F10,F11,",
                        "G4,G5,G6,G7,G8,G9,G10,G11,",
                        "H4,H5,H6,H7,H8,H9,H10,H11,",
                        "J4,J5,J6,J7,J8,J9,J10,J11,",
                        "K4,K5,K6,K7,K8,K9,K10,K11",
                        "L4,L5,L6,L7,L8,L9,L10,L11",
                        "N1,N14,",
                        "P1,P2,P13,P14,",
                        NULL
                );
                package_body_length = 10.50;
                package_body_width = 16.00;
                package_body_height = 1.30;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.50;
                courtyard_width = 18.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.50;
                silkscreen_width = 16.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA121C50P14X14_1050X1600X130");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA121C65P11X11_800X800X130"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 121;
                pin_pad_exceptions_string = g_strdup ("");
                package_body_width = 8.00;
                package_body_length = 8.00;
                package_body_height = 1.30;
                package_is_radial = FALSE;
                number_of_columns = 11;
                number_of_rows = 11;
                pitch_x = 0.65;
                pitch_y = 0.65;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.25;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 10.00;
                courtyard_width = 10.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 8.00;
                silkscreen_width = 8.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA121C65P11X11_800X800X130");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA124C100P14X14_1500X1500X170"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 124;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A3,A5,A7,A9,A11,A13,",
                        "B2,B4,B6,B8,B10,B12,B14,",
                        "C1,C3,C4,C5,C6,C7,C8,C9,C10,C11,C13,",
                        "D2,D3,D4,D5,D6,D7,D8,D9,D10,D11,D12,D14,",
                        "E1,E3,E5,E7,E9,E11,E13,",
                        "F2,F4,F6,F8,F10,F11,F12,F14,",
                        "G1,G2,G3,G4,G5,G6,G7,G8,G9,G10,G11,G12,G13,",
                        "H3,H12,H14,",
                        "J1,J2,J13,J14,",
                        NULL
                );
                package_body_width = 15.00;
                package_body_length = 15.00;
                package_body_height = 1.70;
                package_is_radial = FALSE;
                number_of_columns = 14;
                number_of_rows = 14;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.40;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 17.00;
                courtyard_width = 17.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 15.00;
                silkscreen_width = 15.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA124C100P14X14_1500X1500X170");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " JEDEC MO-192AAE-1.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA124C50P13X13_800X800X120"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 124;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A7,",
                        "D5,D6,D7,D8,D9,D10,",
                        "E4,E5,E6,E7,E8,E9,E10,",
                        "F4,F5,F9,F10,",
                        "G1,G4,G5,G7,G9,G10,G13,",
                        "H4,H5,H9,H10,",
                        "J4,J5,J6,J7,J8,J9,J10,",
                        "K4,K5,K6,K7,K8,K9,K10,",
                        "N7,",
                        NULL
                );
                package_body_width = 8.00;
                package_body_length = 8.00;
                package_body_height = 1.20;
                package_is_radial = FALSE;
                number_of_columns = 13;
                number_of_rows = 13;
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
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 10.00;
                courtyard_width = 10.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 8.00;
                silkscreen_width = 8.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA124C50P13X13_800X800X120");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA124C65P12X12_900X900X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 124;
                pin_pad_exceptions_string = g_strconcat
                (
                        "D4,D5,D6,D7,D8,D9,",
                        "E4,E9,",
                        "F4,F9,",
                        "G4,G9,",
                        "H4,H9,",
                        "J4,J5,J6,J7,J8,J9,",
                        NULL
                );
                package_body_width = 9.00;
                package_body_length = 9.00;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 12;
                number_of_rows = 12;
                pitch_x = 0.65;
                pitch_y = 0.65;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.35;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 11.00;
                courtyard_width = 11.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 9.00;
                silkscreen_width = 9.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA124C65P12X12_900X900X140");
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                (_("%s is also known as")), footprint_name,
                                " JEDEC MO-225.");
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA127C80P12X13_1050X1200X140"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 127;
                pin_pad_exceptions_string = g_strconcat
                (
                        "C1,C12,",
                        "D1,D5,D12,",
                        "E1,E6,E7,E12,",
                        "F1,F6,F7,F12,",
                        "G1,G6,G7,G12,",
                        "H1,H6,H7,H12,",
                        "J1,J6,J7,J12,",
                        "K1,K12,",
                        "L1,L12,",
                        NULL
                );
                package_body_length = 10.50;
                package_body_width = 12.00;
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
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_clearance = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.50;
                courtyard_width = 14.00;
                courtyard_line_width = 0.05;
                silkscreen_length = 10.50;
                silkscreen_width = 12.00;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA127C80P12X13_1050X1200X140");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1284C100P36X36_3750X3750X380"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1284;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A2,A35,A36,",
                        "B1,B36,",
                        "AR1,AR36,",
                        "AT1,AT2,AT35,AT36,",
                        NULL
                );
                package_body_width = 37.50;
                package_body_length = 37.50;
                package_body_height = 3.80;
                package_is_radial = FALSE;
                number_of_columns = 36;
                number_of_rows = 36;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 41.50;
                courtyard_width = 41.50;
                courtyard_line_width = 0.05;
                silkscreen_length = 37.50;
                silkscreen_width = 37.50;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1284C100P36X36_3750X3750X380");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?BGA1284C100P36X36_3750X3750X400"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 1284;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A2,A35,A36,",
                        "B1,B36,",
                        "AR1,AR36,",
                        "AT1,AT2,AT35,AT36,",
                        NULL
                );
                package_body_width = 37.50;
                package_body_length = 37.50;
                package_body_height = 4.00;
                package_is_radial = FALSE;
                number_of_columns = 36;
                number_of_rows = 36;
                pitch_x = 1.00;
                pitch_y = 1.00;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 0.0;
                pad_diameter = 0.50;
                pad_clearance = 0.075;
                pad_solder_mask_clearance = 0.075;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_clearance = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                courtyard_length = 41.50;
                courtyard_width = 41.50;
                courtyard_line_width = 0.05;
                silkscreen_length = 37.50;
                silkscreen_width = 37.50;
                silkscreen_line_width = 0.20;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA1284C100P36X36_3750X3750X400");
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
 * \brief Set GUI constraints for the BGA package type.
 *
 * This function is only to be compiled for GUI targets.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
#if GUI
int
bga_set_gui_constraints ()
{
        /* Widgets on tab "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab "Pins/Pads" */
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
        GtkWidget *pin_pad_exceptions_button = lookup_widget (GTK_WIDGET (widget),
                "pin_pad_exceptions_button");
        gtk_widget_set_sensitive (pin_pad_exceptions_button, TRUE);
        GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pin_drill_diameter_entry");
        gtk_entry_set_text (GTK_ENTRY (pin_drill_diameter_entry), "");
        gtk_widget_set_sensitive (pin_drill_diameter_entry, FALSE);
        GtkWidget *pad_shape_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_shape_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (pad_shape_entry), ROUND);
        gtk_widget_set_sensitive (pad_shape_entry, FALSE);
        GtkWidget *pad_length_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_length_entry");
        gtk_entry_set_text (GTK_ENTRY (pad_length_entry), "");
        gtk_widget_set_sensitive (pad_length_entry, FALSE);
        GtkWidget *pad_width_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_width_entry");
        gtk_entry_set_text (GTK_ENTRY (pad_width_entry), "");
        gtk_widget_set_sensitive (pad_width_entry, FALSE);

        /* Widgets on tab "Thermal Pad" */
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
        GtkWidget *fiducial_pad_clearance_entry = lookup_widget
                (GTK_WIDGET (widget),
                "fiducial_pad_clearance_entry");
        gtk_widget_set_sensitive (fiducial_pad_clearance_entry,
                TRUE);
        GtkWidget *fiducial_pad_solder_mask_clearance_entry = lookup_widget
                (GTK_WIDGET (widget),
                "fiducial_pad_solder_mask_clearance_entry");
        gtk_widget_set_sensitive (fiducial_pad_solder_mask_clearance_entry,
                TRUE);

        /* Widgets on tab "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
        return (EXIT_SUCCESS);
}
#endif /* GUI */


/*!
 * \brief Write a footprint for a BGA package.
 *
 * \return \c EXIT_FAILURE when errors were encountered, \c EXIT_SUCCESS
 * when done.
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
        gchar *pin_pad_flags = g_strdup ("");
        gint i;
        gint j;

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
                        {
                                pin_pad_flags = g_strdup ("square");
                        }
                        else
                        {
                                pin_pad_flags = g_strdup ("");
                        }
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
                fprintf (fp, (_("# Write fiducials\n")));
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
                fprintf (fp, (_("# Write a package body on the silkscreen\n")));
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
                fprintf (fp, (_("# Write a pin 1 marker on the silkscreen\n")));
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
                        (_("[%s] wrote footprint: %s.")),
                        footprint_type,
                        footprint_filename);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief A list containing all BGA related functions.
 */
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
                "Create Packages List",
                bga_create_packages_list,
                "Create a list of known BGA packages",
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
                "Get default values for a selected BGA package",
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


/*!
 * \brief Initialise by registering all BGA related functions.
 */
void
bga_init ()
{
        register_bga_function_list ();
}


/* EOF */
