/*!
 * \file src/con_sil.c
 *
 * \author Copyright 2007-2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Functions for CON_SIL (connector) footprints.
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
#include "con_sil.h"


/*!
 * \brief Create an Element for a CON_SIL package.
 *
 * \return \c EXIT_SUCCESS when an element was created,
 * \c EXIT_FAILURE when errors were encountered.
 */
int
con_sil_create_element ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gint i;
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
                return (EXIT_FAILURE);
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
        /* Store the courtyard dimensions in Virtual (bounding) Box. */
        element->VBox.X1 = (int) xmin;
        element->VBox.Y1 = (int) ymin;
        element->VBox.X2 = (int) xmax;
        element->VBox.Y2 = (int) ymax;
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
        for (i = 0; (i < number_of_rows); i++)
        {
                pin_number = 1 + i;
                if (pad_shapes_type == SQUARE)
                {
                        pad_flag.f = SQUARE;
                }
                else if (pin1_square && (pin_number == 1))
                {
                        pad_flag.f = SQUARE;
                }
                else
                {
                        pad_flag.f = CLEAR;
                }
                create_new_pin
                (
                        element,
                        (int) (multiplier * (-pitch_x / 2.0)), /* x0 coordinate */
                        (int) (multiplier * ((((-number_of_rows - 1) / 2.0) +1 + i) * pitch_y)), /* y0-coordinate */
                        (int) (multiplier * pad_diameter), /* width of the annulus ring (pad) */
                        (int) (multiplier * 2 * pad_clearance), /* clearance */
                        (int) (multiplier * (pad_diameter + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
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
                                (int) (multiplier * (-pitch_x - pad_width + pad_length) / 2.0), /* x0 coordinate */
                                (int) (multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y)), /* y0-coordinate */
                                (int) (multiplier * (-pitch_x + pad_width - pad_length) / 2.0), /* x1 coordinate */
                                (int) (multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y)), /* y1-coordinate */
                                (int) (multiplier * pad_width), /* pad width */
                                (int) (multiplier * 2 * pad_clearance), /* clearance */
                                (int) (multiplier * (pad_width + (2 * pad_solder_mask_clearance))), /* solder mask clearance */
                                "", /* pad name */
                                g_strdup_printf ("%d", pin_number), /* pin number */
                                pad_flag /* flags */
                        );
                }
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
        /* Create a pin #1 marker on the silkscreen. */
        if (silkscreen_indicate_1)
        {
                /* Write a marker around pin #1 inside the package outline */
                create_new_line
                (
                        element,
                        (int) (multiplier * (-package_body_length / 2.0)), /* x0-coordinate */
                        (int) (multiplier * ((((-number_of_rows - 1) / 2.0) + 1.5) * pitch_y)), /* y0-coordinate */
                        (int) (multiplier * (package_body_length / 2.0)), /* x1-coordinate */
                        (int) (multiplier * ((((-number_of_rows - 1) / 2.0) + 1.5) * pitch_y)), /* y1-coordinate */
                        (int) (multiplier * silkscreen_line_width)
                );
                /* Write a triangle shaped marker between package outline and maximum used real estate */
                if (xmax > ((multiplier * package_body_length) / 2))
                {
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (-package_body_length / 2.0)), /* x0-coordinate */
                                (int) (multiplier * (((-number_of_rows + 1) / 2.0) * pitch_y)), /* y0-coordinate */
                                (int) ((multiplier * (-package_body_length / 2.0)) - 2500), /* x1-coordinate */
                                (int) ((multiplier * (((-number_of_rows + 1) / 2.0) * pitch_y)) - 1250), /* y1-coordinate */
                                (int) (multiplier * silkscreen_line_width)
                        );
                        create_new_line
                        (
                                element,
                                (int) (multiplier * (-package_body_length / 2.0)), /* x0-coordinate */
                                (int) (multiplier * (((-number_of_rows + 1) / 2.0) * pitch_y)), /* y0-coordinate */
                                (int) ((multiplier * (-package_body_length / 2.0)) - 2500), /* x1-coordinate */
                                (int) ((multiplier * (((-number_of_rows + 1) / 2.0) * pitch_y)) + 1250), /* y1-coordinate */
                                (int) (multiplier * silkscreen_line_width)
                        );
                        create_new_line
                        (
                                element,
                                (int) ((multiplier * (-package_body_length / 2.0)) - 2500), /* x0-coordinate */
                                (int) ((multiplier * (((-number_of_rows + 1) / 2.0) * pitch_y)) - 1250), /* y0-coordinate */
                                (int) ((multiplier * (-package_body_length / 2.0)) - 2500), /* x1-coordinate */
                                (int) ((multiplier * (((-number_of_rows + 1) / 2.0) * pitch_y)) + 1250), /* y1-coordinate */
                                (int) (multiplier * silkscreen_line_width)
                        );
                }
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
        current_element = (ElementTypePtr) &element;
        return (EXIT_SUCCESS);
}


/*!
 * \brief Create a list of CON_SIL packages with pre-defined values.
 *
 * The data in this list can be used in a combo box to select a
 * pre-defined package.
 *
 * \return \c EXIT_SUCCESS when a packages list was created,
 * \c EXIT_FAILURE when errors were encountered.
 */
int
con_sil_create_packages_list ()
{
        g_list_free (packages_list);
        packages_list = g_list_append (packages_list, "CON_SIL-127P-2N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-3N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-4N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-5N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-6N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-7N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-8N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-9N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-10N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-12N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-20N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-24N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-31N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-36N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-40N");
        packages_list = g_list_append (packages_list, "CON_SIL-127P-50N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-2N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-3N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-4N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-5N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-6N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-7N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-8N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-9N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-10N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-12N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-20N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-24N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-31N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-36N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-40N");
        packages_list = g_list_append (packages_list, "CON_SIL-254P-50N");
        packages_list = g_list_append (packages_list, "CON_SIL-350P-2N");
        packages_list = g_list_append (packages_list, "CON_SIL-350P-3N");
        packages_list = g_list_append (packages_list, "CON_SIL-350P-4N");
        packages_list = g_list_append (packages_list, "CON_SIL-350P-5N");
        packages_list = g_list_append (packages_list, "CON_SIL-350P-6N");
        packages_list = g_list_append (packages_list, "CON_SIL-350P-7N");
        packages_list = g_list_append (packages_list, "CON_SIL-350P-8N");
        packages_list = g_list_append (packages_list, "CON_SIL-350P-10N");
        packages_list = g_list_append (packages_list, "CON_SIL-350P-12N");
        packages_list = g_list_append (packages_list, "CON_SIL-508P-2N");
        packages_list = g_list_append (packages_list, "CON_SIL-508P-3N");
        packages_list = g_list_append (packages_list, "CON_SIL-508P-4N");
        packages_list = g_list_append (packages_list, "CON_SIL-508P-5N");
        packages_list = g_list_append (packages_list, "CON_SIL-508P-6N");
        packages_list = g_list_append (packages_list, "CON_SIL-508P-7N");
        packages_list = g_list_append (packages_list, "CON_SIL-508P-8N");
        packages_list = g_list_append (packages_list, "CON_SIL-508P-9N");
        packages_list = g_list_append (packages_list, "CON_SIL-508P-10N");
        packages_list = g_list_append (packages_list, "CON_SIL-508P-12N");
        packages_list = g_list_append (packages_list, "CON_SIL-508P-24N");
        return (EXIT_SUCCESS);
}


/*!
 * \brief Do some Design Rule Checking for the CON_SIL package type.
 *
 * <ul>
 * <li> check for total number of pins is even.
 * <li> check for number of rows is > 1.
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
con_sil_drc ()
{
        int result = EXIT_SUCCESS;
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        (_("[%s] DRC Check: checking package %s.")),
                        footprint_type, footprint_name);
        }
        /* Check for number of rows is < 1. */
        if (number_of_rows < 1)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: number of rows < 1.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        /* Check for number of columns != 1. */
        if (number_of_columns != 1)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: number of columns is > 1.")),
                                footprint_type);
                }
                number_of_columns = 1;
                result = EXIT_FAILURE;
        }
        /* Check for pich (X-direction) != 0.0. */
        if (pitch_x != 0.0)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: pitch (X-direction) should be 0.")),
                                footprint_type);
                }
                pitch_x = 0.0;
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
        if (pitch_y - pad_width < pad_clearance)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: minimum clearance between copper (Y-direction) is too small.")),
                                footprint_type);
                }
                result = EXIT_FAILURE;
        }
        /* Checking for fiducials. */
        if (fiducial)
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                (_("[%s] DRC Error: package should not have any fiducials.")),
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
 * \brief Look up default values for CON_SIL footprints.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised the values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * CON_SIL-127P-2N,
 * CON_SIL-127P-3N,
 * CON_SIL-127P-4N,
 * CON_SIL-127P-5N,
 * CON_SIL-127P-6N,
 * CON_SIL-127P-7N,
 * CON_SIL-127P-8N,
 * CON_SIL-127P-9N,
 * CON_SIL-127P-10N,
 * CON_SIL-127P-12N,
 * CON_SIL-127P-20N,
 * CON_SIL-127P-24N,
 * CON_SIL-127P-31N,
 * CON_SIL-127P-36N,
 * CON_SIL-127P-40N,
 * CON_SIL-127P-50N,
 * CON_SIL-254P-2N,
 * CON_SIL-254P-3N,
 * CON_SIL-254P-4N,
 * CON_SIL-254P-5N,
 * CON_SIL-254P-6N,
 * CON_SIL-254P-7N,
 * CON_SIL-254P-8N,
 * CON_SIL-254P-9N,
 * CON_SIL-254P-10N,
 * CON_SIL-254P-12N,
 * CON_SIL-254P-20N,
 * CON_SIL-254P-24N,
 * CON_SIL-254P-31N,
 * CON_SIL-254P-36N,
 * CON_SIL-254P-40N,
 * CON_SIL-254P-50N,
 * CON_SIL-350P-2N,
 * CON_SIL-350P-3N,
 * CON_SIL-350P-4N,
 * CON_SIL-350P-5N,
 * CON_SIL-350P-6N,
 * CON_SIL-350P-7N,
 * CON_SIL-350P-8N,
 * CON_SIL-350P-10N,
 * CON_SIL-350P-12N,
 * CON_SIL-508P-2N,
 * CON_SIL-508P-3N,
 * CON_SIL-508P-4N,
 * CON_SIL-508P-5N,
 * CON_SIL-508P-6N,
 * CON_SIL-508P-7N,
 * CON_SIL-508P-8N,
 * CON_SIL-508P-9N,
 * CON_SIL-508P-10N,
 * CON_SIL-508P-12N,
 * CON_SIL-508P-24N,
 *
 * \return \c EXIT_SUCCESS when default values for a footprint were
 * found, \c EXIT_FAILURE when the footprint name was not found.
 */
int
con_sil_get_default_footprint_values ()
{
        if (!strcmp (footprint_name, "?CON_SIL-127P-2N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 100;
                package_body_height = 78;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-127P-2N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-127P-3N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 150;
                package_body_height = 78;
                package_is_radial = FALSE;
                number_of_pins = 3;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-127P-3N");
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_name, "?CON_SIL-127P-4N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 200;
                package_body_height = 78;
                package_is_radial = FALSE;
                number_of_pins = 4;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-127P-4N");
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_name, "?CON_SIL-127P-5N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 250;
                package_body_height = 78;
                package_is_radial = FALSE;
                number_of_pins = 5;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-127P-5N");
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_name, "?CON_SIL-127P-6N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 300;
                package_body_height = 78;
                package_is_radial = FALSE;
                number_of_pins = 6;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-127P-6N");
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_name, "?CON_SIL-127P-7N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 350;
                package_body_height = 78;
                package_is_radial = FALSE;
                number_of_pins = 7;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-127P-7N");
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_name, "?CON_SIL-127P-8N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 400;
                package_body_height = 78;
                package_is_radial = FALSE;
                number_of_pins = 8;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-127P-8N");
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_name, "?CON_SIL-127P-9N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 450;
                package_body_height = 78;
                package_is_radial = FALSE;
                number_of_pins = 9;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-127P-9N");
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_name, "?CON_SIL-127P-10N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 500;
                package_body_height = 78;
                package_is_radial = FALSE;
                number_of_pins = 10;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-127P-10N");
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_name, "?CON_SIL-127P-12N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 600;
                package_body_height = 78;
                package_is_radial = FALSE;
                number_of_pins = 12;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-127P-12N");
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_name, "?CON_SIL-127P-20N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 1000;
                package_body_height = 78;
                package_is_radial = FALSE;
                number_of_pins = 20;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-127P-20N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-2N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 200;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-2N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-3N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 300;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 3;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-4N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 400;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 4;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-4N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-5N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 500;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 5;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-5N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-6N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 600;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 6;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-7N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 700;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 7;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-7N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-8N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 800;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 8;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-8N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-9N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 900;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                number_of_pins = 9;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-9N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-10N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 1000;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 10;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-10N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-12N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 1200;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 12;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-12N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-20N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 2000;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 20;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-20N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-24N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 2400;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 24;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-24N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-31N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 3100;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 31;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-31N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-36N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 3600;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 36;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-36N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-40N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 4000;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 40;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-40N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-254P-50N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 100;
                package_body_width = 5000;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 50;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-254P-50N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-350P-2N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.70;
                package_body_width = 3.50;
                package_body_height = 1.60;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 3.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 1.30;
                pad_diameter = 1.80;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-350P-2N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-350P-3N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.70;
                package_body_width = 7.00;
                package_body_height = 1.60;
                package_is_radial = FALSE;
                number_of_pins = 3;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 3.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 1.30;
                pad_diameter = 1.80;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-350P-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-350P-4N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.70;
                package_body_width = 10.50;
                package_body_height = 1.60;
                package_is_radial = FALSE;
                number_of_pins = 4;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 3.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 1.30;
                pad_diameter = 1.80;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-350P-4N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-350P-5N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.70;
                package_body_width = 14.00;
                package_body_height = 1.60;
                package_is_radial = FALSE;
                number_of_pins = 5;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 3.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 1.30;
                pad_diameter = 1.80;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-350P-5N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-350P-6N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.70;
                package_body_width = 17.50;
                package_body_height = 1.60;
                package_is_radial = FALSE;
                number_of_pins = 6;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 3.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 1.30;
                pad_diameter = 1.80;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-350P-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-350P-7N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.70;
                package_body_width = 21.00;
                package_body_height = 1.60;
                package_is_radial = FALSE;
                number_of_pins = 7;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 3.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 1.30;
                pad_diameter = 1.80;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-350P-7N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-350P-8N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.70;
                package_body_width = 24.50;
                package_body_height = 1.60;
                package_is_radial = FALSE;
                number_of_pins = 8;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 3.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 1.30;
                pad_diameter = 1.80;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-350P-8N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-350P-10N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.70;
                package_body_width = 31.50;
                package_body_height = 1.60;
                package_is_radial = FALSE;
                number_of_pins = 10;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 3.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 1.30;
                pad_diameter = 1.80;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-350P-10N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-350P-12N"))
        {
                footprint_units = g_strdup ("mm");
                package_body_length = 2.70;
                package_body_width = 38.50;
                package_body_height = 1.60;
                package_is_radial = FALSE;
                number_of_pins = 12;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 3.50;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 1.30;
                pad_diameter = 1.80;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 0.20;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 0.05;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-350P-12N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-508P-2N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 110;
                package_body_width = 400;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 2;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 200;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 36;
                pad_diameter = 76;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-508P-2N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-508P-3N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 110;
                package_body_width = 600;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 3;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 200;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 36;
                pad_diameter = 76;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-508P-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-508P-4N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 110;
                package_body_width = 800;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 4;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 200;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 36;
                pad_diameter = 76;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-508P-4N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-508P-5N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 110;
                package_body_width = 1000;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 5;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 200;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 36;
                pad_diameter = 76;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-508P-5N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-508P-6N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 110;
                package_body_width = 1200;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 6;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 200;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 36;
                pad_diameter = 76;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-508P-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-508P-7N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 110;
                package_body_width = 1400;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 7;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 200;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 36;
                pad_diameter = 76;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-508P-7N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-508P-8N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 110;
                package_body_width = 1600;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 8;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 200;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 36;
                pad_diameter = 76;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-508P-8N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-508P-9N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 110;
                package_body_width = 1800;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 9;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 200;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 36;
                pad_diameter = 76;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-508P-9N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-508P-10N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 110;
                package_body_width = 2000;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 10;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 200;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 36;
                pad_diameter = 76;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-508P-10N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-508P-12N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 110;
                package_body_width = 2400;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 12;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 200;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 36;
                pad_diameter = 76;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-508P-12N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?CON_SIL-508P-24N"))
        {
                footprint_units = g_strdup ("mil");
                package_body_length = 110;
                package_body_width = 4800;
                package_body_height = 200;
                package_is_radial = FALSE;
                number_of_pins = 24;
                number_of_columns = 1;
                number_of_rows = number_of_pins;
                pitch_x = 0;
                pitch_y = 200;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 36;
                pad_diameter = 76;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                fiducial = FALSE;
                fiducial_pad_diameter = 0.00;
                fiducial_pad_solder_mask_clearance = 0.00;
                silkscreen_package_outline = TRUE;
                silkscreen_length = package_body_length;
                silkscreen_width = package_body_width;
                silkscreen_line_width = 10;
                courtyard = FALSE;
                courtyard_length = package_body_length;
                courtyard_width = package_body_width;
                courtyard_line_width = 1;
                g_free (footprint_name);
                footprint_name = g_strdup ("CON_SIL-508P-24N");
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
 * \brief Set GUI constraints for the CON_SIL package type.
 *
 * This function is only to be compiled for GUI targets.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
#if GUI
int
con_sil_set_gui_constraints ()
{
        /* Widgets on tab "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab "Pins/Pads" */
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_columns_entry), "1");
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

        /* Widgets on tab "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
        return (EXIT_SUCCESS);
}
#endif /* GUI */


/*!
 * \brief Write a CON_SIL pin through hole footprint.
 *
 * The pin/pad numbering scheme of the CON-DIP package is: \n
 * 1 \n
 * 2 \n
 * 3 \n
 * 4 \n
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
con_sil_write_footprint ()
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

        number_of_columns = 1;
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
                (((pad_diameter > pad_length) ? pad_diameter : pad_length) / -2.0) - pad_solder_mask_clearance
        );
        xmax = multiplier *
        (
                (((pad_diameter > pad_length) ? pad_diameter : pad_length) / 2.0) + pad_solder_mask_clearance
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
                write_pin
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        0, /* x0 coordinate */
                        multiplier * ((((-number_of_rows - 1) / 2.0) +1 + i) * pitch_y), /* y0-coordinate */
                        multiplier * pad_diameter, /* width of the annulus ring (pad) */
                        multiplier * 2 * pad_clearance, /* clearance */
                        multiplier * (pad_diameter + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                        multiplier * pin_drill_diameter, /* pin drill diameter */
                        (pin1_square && (pin_number == 1)) ? "square" : pin_pad_flags /* flags */
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
                                multiplier * (-pad_width + pad_length) / 2.0, /* x0 coordinate */
                                multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y), /* y0-coordinate */
                                multiplier * (pad_width - pad_length) / 2.0, /* x1 coordinate */
                                multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y), /* y1-coordinate */
                                multiplier * pad_width, /* width of the pad */
                                multiplier * 2 * pad_clearance, /* clearance */
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
                        multiplier * ((-package_body_length) / 2.0), /* xmin-coordinate */
                        multiplier * ((-package_body_width) / 2.0), /* ymin-coordinate */
                        multiplier * ((package_body_length) / 2.0), /* xmax-coordinate */
                        multiplier * ((package_body_width) / 2.0), /* ymax-coordiante */
                        multiplier * silkscreen_line_width
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                /* Write a marker around pin #1 inside the package outline */
                write_element_line
                (
                        multiplier * (-package_body_length / 2.0), /* x0-coordinate */
                        multiplier * ((((-number_of_rows - 1) / 2.0) + 1.5) * pitch_y), /* y0-coordinate */
                        multiplier * (package_body_length / 2.0), /* x1-coordinate */
                        multiplier * ((((-number_of_rows - 1) / 2.0) + 1.5) * pitch_y), /* y1-coordinate */
                        multiplier * (silkscreen_line_width)
                );
                /* Write a triangle shaped marker between package outline and maximum used real estate */
                if (xmax > ((multiplier * package_body_length) / 2))
                {
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0), /* x0-coordinate */
                                multiplier * (((-number_of_rows + 1) / 2.0) * pitch_y), /* y0-coordinate */
                                (multiplier * (-package_body_length / 2.0)) - 2500 , /* x1-coordinate */
                                (multiplier * (((-number_of_rows + 1) / 2.0) * pitch_y)) - 1250, /* y1-coordinate */
                                multiplier * (silkscreen_line_width)
                        );
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0), /* x0-coordinate */
                                multiplier * (((-number_of_rows + 1) / 2.0) * pitch_y), /* y0-coordinate */
                                (multiplier * (-package_body_length / 2.0)) - 2500 , /* x1-coordinate */
                                (multiplier * (((-number_of_rows + 1) / 2.0) * pitch_y)) + 1250, /* y1-coordinate */
                                multiplier * (silkscreen_line_width)
                        );
                        write_element_line
                        (
                                (multiplier * (-package_body_length / 2.0)) - 2500 , /* x0-coordinate */
                                (multiplier * (((-number_of_rows + 1) / 2.0) * pitch_y)) - 1250, /* y0-coordinate */
                                (multiplier * (-package_body_length / 2.0)) - 2500 , /* x1-coordinate */
                                (multiplier * (((-number_of_rows + 1) / 2.0) * pitch_y)) + 1250, /* y1-coordinate */
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
 * \brief A list containing all CON_SIL related functions.
 */
static fpw_function_t
con_sil_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                con_sil_set_gui_constraints,
                "Set GUI constraints for a CON_SIL package",
                NULL
        },
#endif /* GUI */
        {
                "Create Package List",
                con_sil_create_packages_list,
                "Create a list of packages with known values",
                NULL
        },
        {
                "DRC CON_SIL Element",
                con_sil_drc,
                "Design Rule Check for a CON_SIL package",
                NULL
        },
        {
                "Default Element Values",
                con_sil_get_default_footprint_values,
                "Get default values for a selected CON_SIL package",
                NULL
        },
        {
                "Write footprint",
                con_sil_write_footprint,
                "Write footprint for a selected CON_SIL package",
                NULL
        }
};


/*!
 * \brief A list containing all CON_SIL related functions.
 */
REGISTER_FUNCTIONS (con_sil_function_list)


/*!
 * \brief Initialise by registering all CON_SIL related functions.
 */
void
con_sil_init ()
{
        register_con_sil_function_list ();
}


/* EOF */
