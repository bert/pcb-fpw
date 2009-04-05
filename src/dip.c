/*!
 * \file dip.c
 * \author Copyright (C) 2008 ... 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Functions for DIP footprints.
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
 * \brief Create an Element for a DIP package.
 *
 * <b>Parameters:</b> \c none .\n
 * \n
 * <b>Returns:</b> a pointer to the created element.
 */
ElementTypePtr
dip_create_element ()
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
                                _("could not create a valid element pointer for a DIP package."));
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
                        (int) (multiplier * (((-pitch_x + pad_diameter + silkscreen_line_width) / 2) + pad_solder_mask_clearance)),
                        (int) ymin, /* already in mil/100 */
                        (int) (multiplier * (((-pitch_x + pad_diameter + silkscreen_line_width) / 2) + pad_solder_mask_clearance)),
                        (int) ymax, /* already in mil/100 */
                        (int) (multiplier * silkscreen_line_width)
                );
                create_new_line
                (
                        element,
                        (int) (multiplier * (((-pitch_x + pad_diameter + silkscreen_line_width) / 2) + pad_solder_mask_clearance)),
                        (int) ymax, /* already in mil/100 */
                        (int) (multiplier * (((pitch_x - pad_diameter - silkscreen_line_width) / 2) - pad_solder_mask_clearance)),
                        (int) ymax, /* already in mil/100 */
                        (int) (multiplier * silkscreen_line_width)
                );
                create_new_line
                (
                        element,
                        (int) (multiplier * (((pitch_x - pad_diameter - silkscreen_line_width) / 2) - pad_solder_mask_clearance)),
                        (int) ymax, /* already in mil/100 */
                        (int) (multiplier * (((pitch_x - pad_diameter - silkscreen_line_width) / 2) - pad_solder_mask_clearance)),
                        (int) ymin, /* already in mil/100 */
                        (int) (multiplier * silkscreen_line_width)
                );
                create_new_line
                (
                        element,
                        (int) (multiplier * (((-pitch_x + pad_diameter + silkscreen_line_width) / 2) + pad_solder_mask_clearance)),
                        (int) ymin, /* already in mil/100 */
                        (int) (multiplier * (((pitch_x - pad_diameter - silkscreen_line_width) / 2) - pad_solder_mask_clearance)),
                        (int) ymin, /* already in mil/100 */
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
                g_log ("", G_LOG_LEVEL_INFO,
                        _("created an element for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
        return (element);
}


/*!
 * \brief Create a list of DIP packages with pre-defined values.
 *
 * The data in this list can be used in a combo box to select a
 * pre-defined package.
 * \n
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> a list containing all package names of this footprint
 * type known by pcb-fpw.
 */
GList
dip_create_packages_list ()
{
        GList *dip_packages_list = NULL;
        dip_packages_list = g_list_append (dip_packages_list, "DIP04300");
        dip_packages_list = g_list_append (dip_packages_list, "DIP06300");
        dip_packages_list = g_list_append (dip_packages_list, "DIP08300");
        dip_packages_list = g_list_append (dip_packages_list, "DIP08400");
        dip_packages_list = g_list_append (dip_packages_list, "DIP10300");
        dip_packages_list = g_list_append (dip_packages_list, "DIP14300");
        dip_packages_list = g_list_append (dip_packages_list, "DIP14400");
        dip_packages_list = g_list_append (dip_packages_list, "DIP16300");
        dip_packages_list = g_list_append (dip_packages_list, "DIP16400");
        dip_packages_list = g_list_append (dip_packages_list, "DIP18300");
        dip_packages_list = g_list_append (dip_packages_list, "DIP18400");
        dip_packages_list = g_list_append (dip_packages_list, "DIP20300");
        dip_packages_list = g_list_append (dip_packages_list, "DIP20400");
        dip_packages_list = g_list_append (dip_packages_list, "DIP22300");
        dip_packages_list = g_list_append (dip_packages_list, "DIP22400");
        dip_packages_list = g_list_append (dip_packages_list, "DIP24300");
        dip_packages_list = g_list_append (dip_packages_list, "DIP24400");
        dip_packages_list = g_list_append (dip_packages_list, "DIP24600");
        dip_packages_list = g_list_append (dip_packages_list, "DIP28300");
        dip_packages_list = g_list_append (dip_packages_list, "DIP28400");
        dip_packages_list = g_list_append (dip_packages_list, "DIP28600");
        dip_packages_list = g_list_append (dip_packages_list, "DIP32300");
        dip_packages_list = g_list_append (dip_packages_list, "DIP32600");
        dip_packages_list = g_list_append (dip_packages_list, "DIP36600");
        dip_packages_list = g_list_append (dip_packages_list, "DIP38600");
        dip_packages_list = g_list_append (dip_packages_list, "DIP40600");
        dip_packages_list = g_list_append (dip_packages_list, "DIP42600");
        dip_packages_list = g_list_append (dip_packages_list, "DIP48600");
        dip_packages_list = g_list_append (dip_packages_list, "DIP50900");
        dip_packages_list = g_list_append (dip_packages_list, "DIP52600");
        dip_packages_list = g_list_append (dip_packages_list, "DIP64900");
        return (*dip_packages_list);
}


/*!
 * \brief Do some Design Rule Checking for the DIP package type.
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
dip_drc ()
{
        int result = EXIT_SUCCESS;
        if (verbose)
                g_log ("", G_LOG_LEVEL_INFO,
                        _("DRC Check: checking DIP package %s."), footprint_name);
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
        if ((pitch_x - pad_diameter < pad_clearance) || (pitch_x - pad_length < pad_clearance))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("DRC Error: check for minimum clearance between copper (X-direction)."));
                result = EXIT_FAILURE;
        }
        /* Check for minimum clearance between copper (Y-direction). */
        if ((pitch_y - pad_diameter < pad_clearance) || (pitch_y - pad_width < pad_clearance))
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
        /* No failures on DRC found. */
        if (verbose || (result == EXIT_SUCCESS))
                g_log ("", G_LOG_LEVEL_INFO,
                        _("DRC Check: no errors while checking DIP package %s."), footprint_name);
        return (result);
}


/*!
 * \brief Look up default values for DIP footprint.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised the values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - DIP04300,
 * - DIP06300,
 * - DIP08300,
 * - DIP08400,
 * - DIP10300,
 * - DIP14300,
 * - DIP14400,
 * - DIP16300,
 * - DIP16400,
 * - DIP18300,
 * - DIP18400,
 * - DIP20300,
 * - DIP20400,
 * - DIP22300,
 * - DIP22400,
 * - DIP24300,
 * - DIP24400,
 * - DIP24600,
 * - DIP28300,
 * - DIP28400,
 * - DIP28600,
 * - DIP32300,
 * - DIP32600,
 * - DIP36600,
 * - DIP38600,
 * - DIP40600,
 * - DIP42600,
 * - DIP48600,
 * - DIP50900,
 * - DIP52600,
 * - DIP64900.
 *
 * <b>Parameters:</b> \c *footprint_name a \c NULL terminated footprint name.\n
 * \n
 * <b>Returns:</b> \c EXIT_SUCCESS when default values for a footprint were
 * found, \c EXIT_FAILURE when the footprint name was not found.
 */
int
dip_get_default_footprint_values
(
        gchar *footprint_name)
{
        if (!strcmp (footprint_name, "?DIP04300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 4;
                package_body_width = 300;
                package_body_length = 200;
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
                footprint_name = g_strdup ("DIP04300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP06300"))
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
                footprint_name = g_strdup ("DIP06300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP08300"))
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
                footprint_name = g_strdup ("DIP08300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP08400"))
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
                footprint_name = g_strdup ("DIP08400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP10300"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP10300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP14300"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP14300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP14400"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP14400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP16300"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP16300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP16400"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP16400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP18300"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP18300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP18400"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP18400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP20300"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP20300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP20400"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP20400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP22300"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP22300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP22400"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP22400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP24300"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP24300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP24400"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP24400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP24600"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP24600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP28300"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP28300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP28400"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP28400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP28600"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP28600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP32300"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP32300");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP32600"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP32600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP36600"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP36600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP38600"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP38600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP40600"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP40600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP42600"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP42600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP48600"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP48600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP50900"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP50900");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP52600"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP52600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP64900"))
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
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP64900");
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
 * \brief Set GUI constraints for the DIP package type.
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Returns:</b> none.
 */
#if GUI
int
dip_set_gui_constraints (GtkWidget *widget)
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
 * \brief Write a DIP pin through hole footprint.
 *
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
dip_write_footprint ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gint pin_number;
        gchar *pin_pad_name = g_strdup ("");
        gint i;

        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                fprintf
                (
                        stderr,
                        "ERROR: could not open file for %s footprint: %s.\n",
                        footprint_type,
                        footprint_filename
                );
                return (EXIT_FAILURE);
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
                        multiplier * (((-pitch_x + pad_diameter + silkscreen_line_width) / 2) + pad_solder_mask_clearance) ,
                        ymin, /* already in mil/100 */
                        multiplier * (((pitch_x - pad_diameter - silkscreen_line_width) / 2) - pad_solder_mask_clearance) ,
                        ymax, /* already in mil/100 */
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
        /* Write attributes */
        if (attributes_in_footprint)
                write_attributes ();
        fprintf (fp, "\n");
        fprintf (fp, ")\n");
        fclose (fp);
        fprintf
        (
                stderr,
                "SUCCESS: wrote a footprint file for a %s package: %s.\n",
                footprint_type,
                footprint_filename
        );
}


/*!
 * \brief A list containing all DIP related functions.
 */
static fpw_function_t
dip_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                dip_set_gui_constraints,
                "Set GUI constraints for a DIP package",
                NULL
        },
#endif /* GUI */
        {
                "Default Element Values",
                dip_get_default_footprint_values,
                "Get default values for a selected DIP package",
                NULL
        },
        {
                "Write footprint",
                dip_write_footprint,
                "Write a footprint for a selected DIP package",
                NULL
        }
};


/*!
 * \brief A list containing all DIP related functions.
 */
REGISTER_FUNCTIONS (dip_function_list)


/*!
 * \brief Initialise by registering all DIOMELF related functions.
 *
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> none.
 */
void
dip_init ()
{
        register_dip_function_list ();
}


/* EOF */
