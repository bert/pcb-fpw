/*!
 * \file libfpw.c
 * \author Copyright (C) 2007, 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief libfpw contains helper functions for both fpw (CLI) and
 * pcb-gfpw (GUI) versions of the pcb FootPrintWizard.
 *
 * fpw (FootPrintWizard) is a program for the creation of footprint files
 * to be used by the pcb layout application
 * (see http://pcb.sourgeforge.net) for the placement of parts in a pcb layout.\n\n
 * The functions in libfpw are called by both the CLI version of the
 * FootPrintWizard (fpw) as well as the GUI version (pcb-gfpw).\n
 *
 * This program is free software; you can redistribute it and/or modify\n
 * it under the terms of the GNU General Public License as published by\n
 * the Free Software Foundation; either version 2 of the License, or\n
 * (at your option) any later version.\n
 * \n
 * This program is distributed in the hope that it will be useful,\n
 * but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n
 * See the GNU General Public License for more details.\n
 * \n
 * You should have received a copy of the GNU General Public License\n
 * along with this program; if not, write to:\n
 * the Free Software Foundation, Inc.,\n
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\n
 */


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdlib.h>
#include <math.h>

#define FPW_VERSION "0.0.8"

#include "globals.h"


/*!
 * \brief Creates a new pad in an element.
 */
PadTypePtr
create_new_pad
(
        ElementTypePtr element,
        LocationType X1,
        LocationType Y1,
        LocationType X2,
        LocationType Y2,
        BDimension thickness,
        BDimension clearance,
        BDimension mask,
        char *name,
        char *number,
        FlagType flags
)
{
        PadTypePtr pad;
        /* copy values */
        if (X1 > X2 || (X1 == X2 && Y1 > Y2))
        {
                pad->Point1.X = X2;
                pad->Point1.Y = Y2;
                pad->Point2.X = X1;
                pad->Point2.Y = Y1;
        }
        else
        {
                pad->Point1.X = X1;
                pad->Point1.Y = Y1;
                pad->Point2.X = X2;
                pad->Point2.Y = Y2;
        }
        pad->Thickness = thickness;
        pad->Clearance = clearance;
        pad->Mask = mask;
        pad->Name = g_strdup (name);
        pad->Number = g_strdup (number);
        pad->Flags = flags;
        pad->ID = ID++;
        pad->Element = element;
        return (pad);
}


/*!
 * \brief Determine the package type.
 */
int
get_package_type ()
{
        /* Determine the package type */
        if (!footprint_type)
        {
                package_type = NO_PACKAGE;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type is not valid."));
                return (EXIT_FAILURE);
        }
        if (!strcmp (footprint_type, ""))
        {
                package_type = NO_PACKAGE;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("empty footprint type entered."));
                return (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "BGA"))
        {
                package_type = BGA;
        }
        else if (!strcmp (footprint_type, "CAPC"))
        {
                package_type = CAPC;
        }
        else if (!strcmp (footprint_type, "DIL"))
        {
                package_type = DIL;
        }
        else if (!strcmp (footprint_type, "DIP"))
        {
                package_type = DIP;
        }
        else if (!strcmp (footprint_type, "INDC"))
        {
                package_type = INDC;
        }
        else if (!strcmp (footprint_type, "PGA"))
        {
                package_type = PGA;
        }
        else if (!strcmp (footprint_type, "QFN"))
        {
                package_type = QFN;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type %s not yet implemented."),
                        footprint_type);
                return (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "QFP"))
        {
                package_type = QFP;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type %s not yet implemented."),
                        footprint_type);
                return (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "RESC"))
        {
                package_type = RESC;
        }
        else if (!strcmp (footprint_type, "SIL"))
        {
                package_type = SIP;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type %s not yet implemented."),
                        footprint_type);
                return (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "SIP"))
        {
                package_type = SIP;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type %s not yet implemented."),
                        footprint_type);
                return (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "SO"))
        {
                package_type = SO;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type %s not yet implemented."),
                        footprint_type);
                return (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "SOT"))
        {
                package_type = SOT;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type %s not yet implemented."),
                        footprint_type);
                return (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "TO92"))
        {
                package_type = TO92;
        }
        else
        {
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type %s is not valid."),
                        footprint_type);
                return (EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Determine if the pin/pad is a non-existing pin or pad.
 *
 * \retval EXIT_SUCCESS if pin/pad is non-existing (it is found in the
 * \c pin_pad_exception_string).\n
 * \retval EXIT_FAILURE if pin/pad exists (it is not found in the
 * \c pin_pad_exception_string).
 */
int
get_pin_pad_exception (gchar *pin_pad_name)
{
        /* Test if a NULL pointer or empty string was passed. */
        if (!pin_pad_name)
                return EXIT_FAILURE;
        if (!pin_pad_exceptions_string)
                return EXIT_FAILURE;
        if (!strcmp (pin_pad_name, ""))
                return EXIT_FAILURE;
        if (!strcmp (pin_pad_exceptions_string, ""))
                return EXIT_FAILURE;
        /* Disect the pin_pad_exceptions_string by tokenizing it and test
         * the tokens against the pin_pad_name. */
        gchar *delimiters = g_strdup (", ");
        gchar *search_string = g_strdup (pin_pad_exceptions_string);
        /* Test the first token. */
        gchar *token = strtok (search_string, delimiters);
        if (!strcmp (pin_pad_name, token))
        {
                return EXIT_SUCCESS;
        }
        else
        {
                /* Test following tokens in a loop. */
                while (token)
                {
                        token = strtok (NULL, delimiters);
                        if (!token)
                                return EXIT_FAILURE;
                        if (!strcmp (pin_pad_name, token))
                        {
                                return EXIT_SUCCESS;
                        }
                }
        }
        /* If we do get until here, let's assume the pin/pad exists. */
        return EXIT_FAILURE;
}


/*!
 * \brief Determine the status type.
 */
int
get_status_type ()
{
        /* Determine the status type */
        if ((!strcmp (footprint_status, "")) || (!footprint_status))
        {
                status_type = NO_STATUS;
        }
        else if (!strcmp (footprint_status, "Experimental"))
        {
                status_type = EXPERIMENTAL;
        }
        else if (!strcmp (footprint_status, "Private (not published)"))
        {
                status_type = PRIVATE;
        }
        else if (!strcmp (footprint_status, "Public (released)"))
        {
                status_type = PUBLIC;
        }
        else if (!strcmp (footprint_status, "Stable (confirmed by peers)"))
        {
                status_type = STABLE;
        }
        else
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("footprint status %s is not valid."),
                        footprint_status);
                return (EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Read a footprintwizard file into the global variables.
 */
int
read_footprintwizard_file (gchar *fpw_filename)
{
        /* Get global variables from footprintwizard file with .fpw suffix */
        FILE *fpw = fopen (fpw_filename, "r");
        if (!fpw)
        {
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("could not open footprint wizard file: %s for reading.\n"),
                        fpw_filename);
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%s\n", footprint_filename);
        /* Check for null pointers or meaningless values. */
        if (!footprint_filename || (!strcmp (footprint_filename, "(null)")))
        {
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint filename with a null pointer found in: %s.\n"),
                        fpw_filename);
                footprint_filename = g_strdup ("");
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%s\n", dummy); /* do not (re)use this value ! */
        fscanf (fpw, "%s\n", footprint_type);
        /* Check for null pointers or meaningless values. */
        if (!footprint_type || (!strcmp (footprint_type, "(null)")))
        {
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type with a null pointer found in: %s.\n"),
                        fpw_filename);
                footprint_type = g_strdup ("");
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Determine the package type */
        if (get_package_type () == EXIT_FAILURE)
        {
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type contains an unknown package type."));
                footprint_type = g_strdup ("");
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        else
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_INFO,
                                _("determined the package type successfull."));
        }
        fscanf (fpw, "%s\n", footprint_units);
        /* Check for null pointers or meaningless values. */
        if (!footprint_units || (!strcmp (footprint_units, "(null)")))
        {
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint units with null pointer found in: %s.\n"),
                        fpw_filename);
                footprint_units = g_strdup ("");
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Update the units related variables. */
        if (update_units_variables () == EXIT_FAILURE)
        {
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint units contains an unknown units type."));
                footprint_units = g_strdup ("");
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        else
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_INFO,
                                _("footprint units variables updated successfull."));
        }
        fscanf (fpw, "%s\n", footprint_refdes);
        /* Check for null pointers or meaningless values. */
        if (!footprint_refdes || (!strcmp (footprint_refdes, "(null)")))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("footprint refdes with a null pointer found in: %s.\n"),
                                fpw_filename);
                footprint_refdes = g_strdup ("");
        }
        fscanf (fpw, "%s\n", footprint_value);
        /* Check for null pointers or meaningless values. */
        if (!footprint_value || (!strcmp (footprint_value, "(null)")))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("footprint value with a null pointer found in: %s.\n"),
                                fpw_filename);
                footprint_value = g_strdup ("");
        }
        fscanf (fpw, "%f\n", package_body_length);
        if ((isnan (package_body_length)) || (isinf (package_body_length)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN found in package body length, in: %s.\n"),
                                fpw_filename);
                package_body_length = 0.0;
        }
        fscanf (fpw, "%f\n", package_body_width);
        if ((isnan (package_body_width)) || (isinf (package_body_width)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN found in package body width, in: %s.\n"),
                                fpw_filename);
                package_body_width = 0.0;
        }
        fscanf (fpw, "%f\n", package_body_height);
        if ((isnan (package_body_height)) || (isinf (package_body_height)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN found in package body heigth, in: %s.\n"),
                                fpw_filename);
                package_body_height = 0.0;
        }
        fscanf (fpw, "%d\n", package_is_radial);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%s\n", footprint_author);
        /* Check for null pointers or meaningless values. */
        if (!footprint_author || (!strcmp (footprint_author, "(null)")))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("footprint author with a null pointer found in: %s.\n"),
                                fpw_filename);
                footprint_author = g_strdup ("");
        }
        fscanf (fpw, "%s\n", footprint_dist_license);
        /* Check for null pointers or meaningless values. */
        if (!footprint_dist_license ||
                (!strcmp (footprint_dist_license, "(null)")))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("footprint dirstribution license with a null pointer found in: %s.\n"),
                                fpw_filename);
                footprint_dist_license = g_strdup ("");
        }
        fscanf (fpw, "%s\n", footprint_use_license);
        /* Check for null pointers or meaningless values. */
        if (!footprint_use_license ||
                (!strcmp (footprint_use_license, "(null)")))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("footprint usage license with a null pointer found in: %s.\n"),
                                fpw_filename);
                footprint_use_license = g_strdup ("");
        }
        fscanf (fpw, "%s\n", footprint_status);
        /* Check for null pointers or meaningless values. */
        if (!footprint_status || (!strcmp (footprint_status, "(null)")))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("footprint status with a null pointer found in: %s.\n"),
                                fpw_filename);
                footprint_status = g_strdup ("");
        }
        fscanf (fpw, "%d\n", attributes_in_footprint);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%d\n", number_of_pins);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%d\n", number_of_columns);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%d\n", number_of_rows);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%f\n", pitch_x);
        if ((isnan (pitch_x)) || (isinf (pitch_x)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number of pitch in X-direction found in: %s.\n"),
                                fpw_filename);
                pitch_x = 0.0;
        }
        fscanf (fpw, "%f\n", pitch_y);
        if ((isnan (pitch_y)) || (isinf (pitch_y)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number of pitch in Y-direction found in: %s.\n"),
                                fpw_filename);
                pitch_y = 0.0;
        }
        fscanf (fpw, "%d\n", count_x);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%d\n", count_y);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%s\n", pad_shape);
        /* Check for null pointers or meaningless values. */
        if (!pad_shape || (!strcmp (pad_shape, "(null)")))
        {
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("pad shape with a null pointer found in: %s.\n"),
                        fpw_filename);
                pad_shape = g_strdup ("");
                return (EXIT_FAILURE);
        }
        /* Update the pad shape related variables. */
        if (update_pad_shapes_variables () == EXIT_FAILURE)
        {
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("pad shape contains an unknown pad shape type."));
                return (EXIT_FAILURE);
        }
        else
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_INFO,
                                _("pad shape variables updated successfull."));
        }
        fscanf (fpw, "%s\n", pin_1_position);
        /* Check for null pointers or meaningless values. */
        if (!pin_1_position || (!strcmp (pin_1_position, "(null)")))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("pin #1 position with a null pointer found in: %s.\n"),
                                fpw_filename);
                pin_1_position = g_strdup ("");
        }
        fscanf (fpw, "%f\n", pad_length);
        if ((isnan (pad_length)) || (isinf (pad_length)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in pad length found in: %s.\n"),
                                fpw_filename);
                pad_length = 0.0;
        }
        fscanf (fpw, "%f\n", pad_width);
        if ((isnan (pad_width)) || (isinf (pad_width)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in pad width found in: %s.\n"),
                                fpw_filename);
                pad_width = 0.0;
        }
        fscanf (fpw, "%f\n", pad_diameter);
        if ((isnan (pad_diameter)) || (isinf (pad_diameter)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in pad diameter found in: %s.\n"),
                                fpw_filename);
                pad_diameter = 0.0;
        }
        fscanf (fpw, "%f\n", pin_drill_diameter);
        if ((isnan (pin_drill_diameter)) || (isinf (pin_drill_diameter)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in pin drill diameter found in: %s.\n"),
                                fpw_filename);
                pin_drill_diameter = 0.0;
        }
        fscanf (fpw, "%d\n", pin1_square);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%f\n", pad_clearance);
        if ((isnan (pad_clearance)) || (isinf (pad_clearance)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in pad clearance found in: %s.\n"),
                                fpw_filename);
                pad_clearance = 0.0;
        }
        fscanf (fpw, "%f\n", pad_solder_mask_clearance);
        if ((isnan (pad_solder_mask_clearance)) ||
                (isinf (pad_solder_mask_clearance)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in pad solder mask clearance found in: %s.\n"),
                                fpw_filename);
                pad_solder_mask_clearance = 0.0;
        }
        fscanf (fpw, "%d\n", thermal);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%d\n", thermal_nopaste);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%f\n", thermal_length);
        if ((isnan (thermal_length)) || (isinf (thermal_length)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in thermal length found in: %s.\n"),
                                fpw_filename);
                thermal_length = 0.0;
        }
        fscanf (fpw, "%f\n", thermal_width);
        if ((isnan (thermal_width)) || (isinf (thermal_width)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in thermal width found in: %s.\n"),
                                fpw_filename);
                thermal_width = 0.0;
        }
        fscanf (fpw, "%f\n", thermal_clearance);
        if ((isnan (thermal_clearance)) || (isinf (thermal_clearance)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in thermal clearance found in: %s.\n"),
                                fpw_filename);
                thermal_clearance = 0.0;
        }
        fscanf (fpw, "%f\n", thermal_solder_mask_clearance);
        if ((isnan (thermal_solder_mask_clearance)) ||
                (isinf (thermal_solder_mask_clearance)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in thermal solder mask clearance found in: %s.\n"),
                                fpw_filename);
                thermal_solder_mask_clearance = 0.0;
        }
        fscanf (fpw, "%d\n", fiducial);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%f\n", fiducial_pad_diameter);
        if ((isnan (fiducial_pad_diameter)) || (isinf (fiducial_pad_diameter)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in fiducial pad diameter found in: %s.\n"),
                                fpw_filename);
                fiducial_pad_diameter = 0.0;
        }
        fscanf (fpw, "%f\n", fiducial_pad_solder_mask_clearance);
        if ((isnan (fiducial_pad_solder_mask_clearance)) ||
                (isinf (fiducial_pad_solder_mask_clearance)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in fiducial pad solder mask clearance found in: %s.\n"),
                                fpw_filename);
                fiducial_pad_solder_mask_clearance = 0.0;
        }
        fscanf (fpw, "%d\n", silkscreen_package_outline);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%d\n", silkscreen_indicate_1);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%f\n", silkscreen_line_width);
        if ((isnan (silkscreen_line_width)) || (isinf (silkscreen_line_width)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in silkscreen line width found in: %s.\n"),
                                fpw_filename);
                silkscreen_line_width = 0.0;
        }
        fscanf (fpw, "%d\n", courtyard);
        /*! \todo Check contents here !*/
        fscanf (fpw, "%f\n", courtyard_length);
        if ((isnan (courtyard_length)) || (isinf (courtyard_length)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in courtyard length found in: %s.\n"),
                                fpw_filename);
                courtyard_length = 0.0;
        }
        fscanf (fpw, "%f\n", courtyard_width);
        if ((isnan (courtyard_width)) || (isinf (courtyard_width)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in courtyard width found in: %s.\n"),
                                fpw_filename);
                courtyard_width = 0.0;
        }
        fscanf (fpw, "%f\n", courtyard_line_width);
        if ((isnan (courtyard_line_width)) || (isinf (courtyard_line_width)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in courtyard line width found in: %s.\n"),
                                fpw_filename);
                courtyard_line_width = 0.0;
        }
        fscanf (fpw, "%f\n", courtyard_clearance_with_package);
        if ((isnan (courtyard_clearance_with_package)) ||
                (isinf (courtyard_clearance_with_package)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in courtyard clearance with package found in: %s.\n"),
                                fpw_filename);
                courtyard_clearance_with_package = 0.0;
        }

        fscanf (fpw, "%f\n", c1);
        if ((isnan (c1)) || (isinf (c1)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in top to bottom center-center distance found in: %s.\n"),
                                fpw_filename);
                c1 = 0.0;
        }
        fscanf (fpw, "%f\n", g1);
        if ((isnan (g1)) || (isinf (g1)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in top to bottom inner-inner distance found in: %s.\n"),
                                fpw_filename);
                g1 = 0.0;
        }
        fscanf (fpw, "%f\n", z1);
        if ((isnan (z1)) || (isinf (z1)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in top to bottom outer-outer distance found in: %s.\n"),
                                fpw_filename);
                z1 = 0.0;
        }
        fscanf (fpw, "%f\n", c2);
        if ((isnan (c2)) || (isinf (c2)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in left to right center-center distance found in: %s.\n"),
                                fpw_filename);
                c2 = 0.0;
        }
        fscanf (fpw, "%f\n", g2);
        if ((isnan (g2)) || (isinf (g2)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in left to right inner-inner distance found in: %s.\n"),
                                fpw_filename);
                g2 = 0.0;
        }
        fscanf (fpw, "%f\n", z2);
        if ((isnan (z2)) || (isinf (z2)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in left to right outer-outer distance found in: %s.\n"),
                                fpw_filename);
                z2 = 0.0;
        }
        fclose (fpw);
        if (verbose)
                g_log ("", G_LOG_LEVEL_INFO,
                        "read footprint wizard file: %s.\n", fpw_filename);
        return (EXIT_SUCCESS);
}


/*!
 * \brief Update locations type variables.
 */
int
update_location_variables ()
{
        if (!strcmp (pin_1_position, "Upper left"))
        {
                pin1_location = UPPER_LEFT;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Middle left"))
        {
                pin1_location = MIDDLE_LEFT;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Lower left"))
        {
                pin1_location = LOWER_LEFT;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Upper middle"))
        {
                pin1_location = UPPER_MIDDLE;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Middle middle"))
        {
                pin1_location = MIDDLE_MIDDLE;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Lower middle"))
        {
                pin1_location = LOWER_MIDDLE;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Upper right"))
        {
                pin1_location = UPPER_RIGHT;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Middle right"))
        {
                pin1_location = MIDDLE_RIGHT;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Lower right"))
        {
                pin1_location = LOWER_RIGHT;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Left topside"))
        {
                pin1_location = LEFT_TOP;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Right topside"))
        {
                pin1_location = RIGHT_TOP;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Left bottomside"))
        {
                pin1_location = LEFT_BOTTOM;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Right bottomside"))
        {
                pin1_location = RIGHT_BOTTOM;
                return (EXIT_SUCCESS);
        }
        return (EXIT_FAILURE);
}


/*!
 * \brief Update pad shapes type variables.
 *
 * \return Returns \c EXIT_SUCCESS when a known pad shape was determined.\n
 * Returns \c EXIT_FAILURE when an unknown pad shape was determined.
 *
 */
int
update_pad_shapes_variables ()
{
        if (!strcmp (pad_shape, "circular pad"))
        {
                g_strconcat (pin_pad_flags, "", NULL);
                pad_shapes_type = ROUND;
                return (EXIT_SUCCESS);
        }
        if (!strcmp (pad_shape, "rectangular pad"))
        {
                g_strconcat (pin_pad_flags, "square", NULL);
                pad_shapes_type = SQUARE;
                return (EXIT_SUCCESS);
        }
        if (!strcmp (pad_shape, "octagonal pad"))
        {
                g_strconcat (pin_pad_flags, "octagon", NULL);
                pad_shapes_type = OCTAGONAL;
                return (EXIT_SUCCESS);
        }
        if (!strcmp (pad_shape, "rounded pad, elongated"))
        {
                g_strconcat (pin_pad_flags, "", NULL);
                pad_shapes_type = ROUND_ELONGATED;
                return (EXIT_SUCCESS);
        }
        return (EXIT_FAILURE);
}

/*!
 * \brief Update (units) multiplier and units type variables.
 */
int
update_units_variables ()
{
        if (!strcmp (footprint_units, "mil"))
        {
                multiplier = 100.0;
                units_type = MIL;
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_units, "mil/100"))
        {
                multiplier = 1.0;
                units_type = MIL_100;
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_units, "mm"))
        {
                multiplier = (1000 / 25.4) * 100;
                units_type = MM;
                return (EXIT_SUCCESS);
        }
        return (EXIT_FAILURE);
}


/*!
 * \brief Write attributes based on the global variables.
 *
 */
int
write_attributes
(
)
{
        /* Attributes in the form "Attribute("name" "value")" */
        fprintf (fp, "# Write attributes\n");
        fprintf (fp, "\tAttribute(\"author\" \"%s\")\n", footprint_author);
        fprintf (fp, "\tAttribute(\"dist-license\" \"%s\")\n", footprint_dist_license);
        fprintf (fp, "\tAttribute(\"use-license\" \"%s\")\n", footprint_use_license);
        fprintf (fp, "\tAttribute(\"status\" \"%s\")\n", footprint_status);
        fprintf (fp, "\tAttribute(\"attributes in footprint\" \"%d\")\n", attributes_in_footprint);
        fprintf (fp, "\tAttribute(\"package body length\" \"%d\")\n", (int) package_body_length);
        fprintf (fp, "\tAttribute(\"package body width\" \"%d\")\n", (int) package_body_width);
        fprintf (fp, "\tAttribute(\"package height\" \"%d\")\n", (int) package_body_height);
        fprintf (fp, "\tAttribute(\"package is radial\" \"%d\")\n", package_is_radial);
        fprintf (fp, "\tAttribute(\"number of pins\" \"%d\")\n", (int) number_of_pins);
        fprintf (fp, "\tAttribute(\"number of columns\" \"%d\")\n", (int) number_of_columns);
        fprintf (fp, "\tAttribute(\"number of rows\" \"%d\")\n", (int) number_of_rows);
        fprintf (fp, "\tAttribute(\"pitch_x\" \"%f\")\n", pitch_x);
        fprintf (fp, "\tAttribute(\"pitch_y\" \"%f\")\n", pitch_y);
        fprintf (fp, "\tAttribute(\"count_x\" \"%d\")\n", (int) count_x);
        fprintf (fp, "\tAttribute(\"count_x\" \"%d\")\n", (int) count_y);
        fprintf (fp, "\tAttribute(\"pad_shape\" \"%s\")\n", pad_shape);
        fprintf (fp, "\tAttribute(\"pin_1_position\" \"%s\")\n", pin_1_position);
        fprintf (fp, "\tAttribute(\"pad_diameter\" \"%f\")\n", pad_diameter);
        fprintf (fp, "\tAttribute(\"pin_drill_diameter\" \"%f\")\n", pin_drill_diameter);
        fprintf (fp, "\tAttribute(\"pin1_square\" \"%d\")\n", (int) pin1_square);
        fprintf (fp, "\tAttribute(\"pad_length\" \"%f\")\n", pad_length);
        fprintf (fp, "\tAttribute(\"pad_width\" \"%f\")\n", pad_width);
        fprintf (fp, "\tAttribute(\"pad_clearance\" \"%f\")\n", pad_clearance);
        fprintf (fp, "\tAttribute(\"pad_solder_mask_clearance\" \"%f\")\n", pad_solder_mask_clearance);
        fprintf (fp, "\tAttribute(\"thermal\" \"%d\")\n", (int) thermal);
        fprintf (fp, "\tAttribute(\"thermal_nopaste\" \"%d\")\n", (int) thermal_nopaste);
        fprintf (fp, "\tAttribute(\"thermal_length\" \"%f\")\n", thermal_length);
        fprintf (fp, "\tAttribute(\"thermal_width\" \"%f\")\n", thermal_width);
        fprintf (fp, "\tAttribute(\"thermal_clearance\" \"%f\")\n", thermal_clearance);
        fprintf (fp, "\tAttribute(\"thermal_solder_mask_clearance\" \"%f\")\n", thermal_solder_mask_clearance);
        fprintf (fp, "\tAttribute(\"silkscreen_package_outline\" \"%d\")\n", (int) silkscreen_package_outline);
        fprintf (fp, "\tAttribute(\"silkscreen_indicate_1\" \"%d\")\n", (int) silkscreen_indicate_1);
        fprintf (fp, "\tAttribute(\"silkscreen_line_width\" \"%f\")\n", silkscreen_line_width);
        fprintf (fp, "\tAttribute(\"courtyard\" \"%d\")\n", (int) courtyard);
        fprintf (fp, "\tAttribute(\"courtyard_length\" \"%f\")\n", courtyard_length);
        fprintf (fp, "\tAttribute(\"courtyard_width\" \"%f\")\n", courtyard_width);
        fprintf (fp, "\tAttribute(\"courtyard_line_width\" \"%f\")\n", courtyard_line_width);
        fprintf (fp, "\tAttribute(\"courtyard_clearance_with_package\" \"%f\")\n", courtyard_clearance_with_package);
        fprintf (fp, "\tAttribute(\"c1\" \"%f\")\n", c1);
        fprintf (fp, "\tAttribute(\"g1\" \"%f\")\n", g1);
        fprintf (fp, "\tAttribute(\"z1\" \"%f\")\n", z1);
        fprintf (fp, "\tAttribute(\"c2\" \"%f\")\n", c2);
        fprintf (fp, "\tAttribute(\"g2\" \"%f\")\n", g2);
        fprintf (fp, "\tAttribute(\"z2\" \"%f\")\n", z2);
}


/*!
 * \brief Write an element arc.
 *
 * This function is here to avoid the exhaustive changes of boiler plate code
 * when the file format of pcb footprint changes.
 */
int
write_element_arc
(
        gdouble _x, /*!< X-coordinate of center. */
        gdouble _y, /*!< Y-coordinate of center. */
        gdouble _width, /*!< Width from center to edge. */
        gdouble _height, /*!< Height from center to edge. */
        gdouble _start_angle, /*!< The angle of the start of the arc in degrees.\n
                              * 0 = negative X-axis, 90 = positive Y-axis. */
        gdouble _delta_angle, /*!< The angle of sweep in degrees.\n
                              * positive = CCW, negative = CW. */
        gdouble _line_width /*!< The width of the line which forms the arc. */
)
{
        fprintf
        (
                fp,
                "\tElementArc[%d %d %d %d %d %d %d]\n",
                (int) _x,
                (int) _y,
                (int) _width,
                (int) _height,
                (int) _start_angle,
                (int) _delta_angle,
                (int) _line_width
        );
}


/*!
 * \brief Write an element header based on the global variables.
 *
 */
int
write_element_header
(
        gdouble x_text, /*!< X-coordinate of text */
        gdouble y_text /*!< y-coordinate of text */
)
{
        /* Write header to file */
        fprintf
        (
                fp,
                "Element[\"\" \"%s\" \"%s?\" \"%s\" 0 0 %d %d 0 100 \"\"]\n(\n",
                footprint_name,
                footprint_refdes,
                footprint_value,
                (int) (x_text),
                (int) (y_text)
        );
}


/*!
 * \brief Write an element line.
 *
 * This function is here to avoid the exhaustive changes of boiler plate code
 * when the file format of pcb footprint changes.
 */
int
write_element_line
(
        gdouble x0, /*!< X-coordinate of the starting point of the line.\n
                     * These are relative to the Elements mark point for
                     * new element formats, or absolute for older formats. */
        gdouble y0, /*!< Y-coordinate of the starting point of the line.\n
                     * These are relative to the Elements mark point for
                     * new element formats, or absolute for older formats. */
        gdouble x1, /*!< X-coordinate of the ending point of the line.\n
                     * These are relative to the Elements mark point for
                     * new element formats, or absolute for older formats. */
        gdouble y1, /*!< Y-coordinate of the ending point of the line.\n
                     * These are relative to the Elements mark point for
                     * new element formats, or absolute for older formats. */
        gdouble line_width /*!< The width of the silk for this line. */
)
{
        fprintf
        (
                fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) x0,
                (int) y0,
                (int) x1,
                (int) y1,
                (int) line_width
        );
}


/*!
 * \brief Write a license statement (at the begin of the footprint file).
 *
 */
int
write_license
(
)
{
        /* Write the license statement for footprints for the GPL version to file */
        fprintf (fp, "# This footprint is free software; you may redistribute it and/or modify\n");
        fprintf (fp, "# it under the terms of the GNU General Public License as published by the\n");
        fprintf (fp, "# Free Software Foundation; either version 2 of the License, or (at your\n");
        fprintf (fp, "# option) any later version.\n");
        fprintf (fp, "# As a special exception, if you create a design which uses this\n");
        fprintf (fp, "# footprint, and embed this footprint or unaltered portions of this\n");
        fprintf (fp, "# footprint into the design, this footprint does not by itself cause\n");
        fprintf (fp, "# the resulting design to be covered by the GNU General Public\n");
        fprintf (fp, "# License.\n");
        fprintf (fp, "# This exception does not however invalidate any other reasons why\n");
        fprintf (fp, "# the design itself might be covered by the GNU General Public\n");
        fprintf (fp, "# License.\n");
        fprintf (fp, "# If you modify this footprint, you may extend this exception to your\n");
        fprintf (fp, "# version of the footprint, but you are not obligated to do so.\n");
        fprintf (fp, "# If you do not wish to do so, delete this exception statement from\n");
        fprintf (fp, "# your version.\n");
}


/*!
 * \brief Write a pad for any given footprint.
 *
 * This function is here to avoid the exhaustive changes of boiler plate code
 * when the file format of pcb footprint changes.
 */
int
write_pad
(
        gint _pad_number, /*!< pad number */
        gchar *_pad_name, /*!< pad name */
        gdouble _x0, /*!< x0 coordinate */
        gdouble _y0, /*!< y0-coordinate */
        gdouble _x1, /*!< x1 coordinate */
        gdouble _y1, /*!< y1-coordinate */
        gdouble _width, /*!< width of the pad */
        gdouble _clearance, /*!< clearance */
        gdouble _pad_solder_mask_clearance, /*!< solder mask clearance */
        gchar *_flags /*!< flags */
)
{
        fprintf (fp,
                "\tPad[%d %d %d %d %d %d %d \"%s\" \"%d\" \"%s\"]\n",
                (int) _x0,
                (int) _y0,
                (int) _x1,
                (int) _y1,
                (int) _width,
                (int) _clearance,
                (int) _pad_solder_mask_clearance,
                _pad_name,
                _pad_number,
                _flags
                );
}


/*!
 * \brief Write a pin for any given footprint.
 *
 * This function is here to avoid the exhaustive changes of boiler plate code
 * when the file format of pcb footprint changes.
 */
int
write_pin
(
        gint _pin_number, /*!< pin number */
        gchar *_pin_name, /*!< pin name */
        gdouble _x0, /*!< x0 coordinate */
        gdouble _y0, /*!< y0-coordinate */
        gdouble _width, /*!< width of the annulus ring (pad) */
        gdouble _clearance, /*!< clearance */
        gdouble _pad_solder_mask_clearance, /*!< solder mask clearance */
        gdouble _drill, /*!< pin drill diameter */
        gchar *_flags /*!< flags */
)
{
        fprintf (fp,
                "\tPin[%d %d %d %d %d %d \"%s\" \"%d\" \"%s\"]\n",
                (int) _x0,
                (int) _y0,
                (int) _width,
                (int) _clearance,
                (int) _pad_solder_mask_clearance,
                (int) _drill,
                _pin_name,
                _pin_number,
                _flags
                );
}

/*!
 * \brief Write a rectangle for any given footprint.
 *
 * Write a rectangle for any given footprint.
 * If line_width is 0.0 no rectangle is drawn.
 * If line_width is < 0.0 a rectangle with a linewidth of 1/100 of
 * a mil is drawn (#define THIN_DRAW 1).
 */
int
write_rectangle
(
        gdouble xmin, /*!< minimum x-coordinate of rectangle. */
        gdouble ymin, /*!< minimum y-coordinate of rectangle. */
        gdouble xmax, /*!< maximum x-coordinate of rectangle. */
        gdouble ymax, /*!< maximum y-coordinate of rectangle. */
        gdouble line_width /*!< courtyard line width */
)
{
        /* If line_width is 0.0 do not draw a rectangle */
        if (line_width == 0.0)
        {
                return;
        }
        /* If line_width is < 0.0 a rectangle with a linewidth of
         * 1/100 of a mil is drawn (#define THIN_DRAW 1)
         */
        if (line_width < 0.0)
        {
                line_width = THIN_DRAW;
        }
        /* Print rectangle ends (perpendicular to x-axis) */
        fprintf
        (
                fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) xmin,
                (int) ymin,
                (int) xmin,
                (int) ymax,
                (int) line_width
        );
        fprintf
        (
                fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) xmax,
                (int) ymin,
                (int) xmax,
                (int) ymax,
                (int) line_width
        );
        /* Print rectangle sides (parallel with x-axis) */
        fprintf
        (
                fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) xmin,
                (int) ymin,
                (int) xmax,
                (int) ymin,
                (int) line_width
        );
        fprintf
        (
                fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) xmax,
                (int) ymax,
                (int) xmin,
                (int) ymax,
                (int) line_width
        );
}


/*!
 * \brief Write a TH footprint for a BGA package.
 */
int
write_footprint_bga ()
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
        fprintf
        (
                stderr,
                "SUCCESS: wrote a footprint file for a %s package: %s.\n",
                footprint_type,
                footprint_filename
        );
}


/*!
 * \brief Write a CON-DIL pin through hole footprint.
 *
 * The pin/pad numbering scheme of the CON-DIP package is: \n
 * 5 6 7 8 \n
 * 1 2 3 4
 */
int
write_footprint_con_dil ()
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
                (((-number_of_columns + 1) / 2.0) * pitch_x) -
                (((pad_diameter > pad_length) ? pad_diameter : pad_length) / 2.0) -
                pad_solder_mask_clearance
        );
        xmax = multiplier *
        (
                (((number_of_columns - 1) / 2.0) * pitch_x) +
                (((pad_diameter > pad_length) ? pad_diameter : pad_length) / 2.0) +
                pad_solder_mask_clearance
                );
        ymin = multiplier *
        (
                (-pitch_y / 2.0) -
                (((pad_diameter > pad_width) ? pad_diameter : pad_width) / 2.0) -
                pad_solder_mask_clearance
        );
        ymax = multiplier *
        (
                (pitch_y / 2.0) +
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
        for (i = 0; (i < number_of_columns); i++)
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
                        multiplier * ((((-number_of_columns - 1) / 2.0) +1 + i) * pitch_x), /* x0-coordinate */
                        multiplier * (pitch_y / 2.0), /* y0 coordinate */
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
                                multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x0-coordinate */
                                multiplier * ((pitch_y + pad_length - pad_width) / 2.0), /* y0 coordinate */
                                multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x1-coordinate */
                                multiplier * ((pitch_y - pad_length + pad_width) / 2.0), /* y1 coordinate */
                                multiplier * pad_length, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                }
                pin_number = number_of_columns + 1 + i;
                if (pin1_square && (pin_number == 1))
                        pin_pad_flags = g_strdup ("square");
                else
                        pin_pad_flags = g_strdup ("");
                write_pin
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x0-coordinate */
                        multiplier * (-pitch_y / 2.0), /* y0 coordinate */
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
                                multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x0-coordinate */
                                multiplier * ((-pitch_y - pad_length + pad_width) / 2.0), /* y0 coordinate */
                                multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x1-coordinate */
                                multiplier * ((-pitch_y + pad_length - pad_width) / 2.0), /* y1 coordinate */
                                multiplier * pad_length, /* width of the pad */
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
                        multiplier * ((-package_body_length - silkscreen_line_width) / 2.0) ,
                        multiplier * ((-package_body_width - silkscreen_line_width) / 2.0) ,
                        multiplier * ((package_body_length + silkscreen_line_width) / 2.0) ,
                        multiplier * ((package_body_width + silkscreen_line_width) / 2.0) ,
                        multiplier * silkscreen_line_width
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                write_element_arc
                (
                        xmin - (multiplier * (pad_solder_mask_clearance + pad_clearance)), /* xmin already in mil/100 */
                        ymax + (multiplier * (pad_solder_mask_clearance + pad_clearance)), /* ymax already in mil/100 */
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
 * \brief Write a CON-DIP pin through hole footprint.
 *
 * The pin/pad numbering scheme of the CON-DIP package is: \n
 * 8 7 6 5 \n
 * 1 2 3 4
 */
int
write_footprint_con_dip ()
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
                (((-number_of_columns + 1) / 2.0) * pitch_x) -
                (((pad_diameter > pad_length) ? pad_diameter : pad_length) / 2.0) -
                pad_solder_mask_clearance
        );
        xmax = multiplier *
        (
                (((number_of_columns - 1) / 2.0) * pitch_x) +
                (((pad_diameter > pad_length) ? pad_diameter : pad_length) / 2.0) +
                pad_solder_mask_clearance
        );
        ymin = multiplier *
        (
                (-pitch_y / 2.0) -
                (((pad_diameter > pad_width) ? pad_diameter : pad_width) / 2.0) -
                pad_solder_mask_clearance
        );
        ymax = multiplier *
        (
                (pitch_y / 2.0) +
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
        for (i = 0; (i < number_of_columns); i++)
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
                        multiplier * ((((-number_of_columns - 1) / 2.0) +1 + i) * pitch_x), /* x0-coordinate */
                        multiplier * (pitch_y / 2.0), /* y0 coordinate */
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
                                multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x0-coordinate */
                                multiplier * (pitch_y + pad_length - pad_width) / 2.0, /* y0 coordinate */
                                multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x1-coordinate */
                                multiplier * (pitch_y - pad_length + pad_width) / 2.0, /* y1 coordinate */
                                multiplier * pad_length, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                }
                pin_number = (number_of_rows * number_of_columns) - i;
                if (pin1_square && (pin_number == 1))
                        pin_pad_flags = g_strdup ("square");
                else
                        pin_pad_flags = g_strdup ("");
                write_pin
                (
                        pin_number, /* pin number */
                        pin_pad_name, /* pin name */
                        multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x0-coordinate */
                        multiplier * (-pitch_y / 2.0), /* y0 coordinate */
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
                                multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x0-coordinate */
                                multiplier * (pitch_y - pad_length + pad_width) / 2.0, /* y0 coordinate */
                                multiplier * ((((-number_of_columns - 1) / 2.0) + 1 + i) * pitch_x), /* x1-coordinate */
                                multiplier * (pitch_y + pad_length - pad_width) / 2.0, /* y1 coordinate */
                                multiplier * pad_length, /* width of the pad */
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
                        multiplier * ((-package_body_length - silkscreen_line_width) / 2.0) ,
                        multiplier * ((-package_body_width - silkscreen_line_width) / 2.0) ,
                        multiplier * ((package_body_length + silkscreen_line_width) / 2.0) ,
                        multiplier * ((package_body_width + silkscreen_line_width) / 2.0) ,
                        multiplier * silkscreen_line_width
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                write_element_arc
                (
                        xmin - (multiplier * (pad_solder_mask_clearance + pad_clearance)), /* xmin already in mil/100 */
                        ymax + (multiplier * (pad_solder_mask_clearance + pad_clearance)), /* ymax already in mil/100 */
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
 * \brief Write a DIP or DIL pin through hole footprint.
 */
int
write_footprint_dip ()
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
 * \brief Write a TH footprint for a PGA package.
 */
int
write_footprint_pga ()
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
                                write_pin
                                (
                                        pin_number, /* pin number */
                                        pin_pad_name, /* pin name */
                                        multiplier * ((((- number_of_columns -1) / 2.0) + 1 + j) * pitch_x), /* x0 coordinate */
                                        multiplier * ((((-number_of_rows - 1) / 2.0) + 1 + i) * pitch_y), /* y0-coordinate */
                                        multiplier * pad_diameter, /* width of the annulus ring (pad) */
                                        multiplier * pad_clearance, /* clearance */
                                        multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                                        multiplier * pin_drill_diameter, /* pin drill diameter */
                                        pin_pad_flags /* flags */
                                );
                        }
                        pin_number++;
                }
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
        fprintf
        (
                stderr,
                "SUCCESS: wrote a footprint file for a %s package: %s.\n",
                footprint_type,
                footprint_filename
        );
}


/*!
 * \brief Write a SMT footprint for a PLCC package.
 */
int
write_footprint_plcc ()
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
        gdouble x0;
        gdouble x1;
        gdouble y0;
        gdouble y1;
        gdouble y_dot;

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
 * \brief Write a SMT footprint with two pads for a chip package.
 */
int
write_footprint_smt ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;

        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                fprintf
                (
                        stderr,
                        "Error: could not open file for %s footprint: %s.\n",
                        footprint_type,
                        footprint_filename
                );
                return (EXIT_FAILURE);
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
 * \brief Write a SMT footprint with two pads for a molded package.
 */
int
write_footprint_smt_molded ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;

        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                fprintf
                (
                        stderr,
                        "Error: could not open file for %s footprint: %s.\n",
                        footprint_type,
                        footprint_filename
                );
                return (EXIT_FAILURE);
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
                if (pad_width >= package_body_width)
                {
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
                else
                {
                        /* lines parallel to X-axis */
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * silkscreen_line_width
                        );
                        /* lines perpendicular to X-axis */
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (((-pad_width - silkscreen_line_width) / 2.0) - pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (((pad_width + silkscreen_line_width) / 2.0) + pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (((-pad_width - silkscreen_line_width) / 2.0) - pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (((pad_width + silkscreen_line_width) / 2.0) + pad_solder_mask_clearance),
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
 * \brief Write a SMT footprint with two pads for a molded capacitor package.
 */
int
write_footprint_smt_molded_cap ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;

        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                fprintf
                (
                        stderr,
                        "Error: could not open file for %s footprint: %s.\n",
                        footprint_type,
                        footprint_filename
                );
                return (EXIT_FAILURE);
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
                        "P", /* pad name */
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
                        "N", /* pad name */
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
                        "P", /* pad name */
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
                        "N", /* pad name */
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
                if (pad_width >= package_body_width)
                {
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
                else
                {
                        /* lines parallel to X-axis */
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * silkscreen_line_width
                        );
                        /* lines perpendicular to X-axis */
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (((-pad_width - silkscreen_line_width) / 2.0) - pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (((pad_width + silkscreen_line_width) / 2.0) + pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (((-pad_width - silkscreen_line_width) / 2.0) - pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (((pad_width + silkscreen_line_width) / 2.0) + pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                }
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                if (pad_width >= package_body_width)
                {
                        write_element_line
                        (
                                multiplier * (((-pitch_x + pad_length) / 2.0) + pad_solder_mask_clearance + silkscreen_line_width),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (((-pitch_x + pad_length) / 2.0) + pad_solder_mask_clearance + silkscreen_line_width),
                                multiplier * (package_body_width / 2.0),
                                multiplier * silkscreen_line_width
                        );
                }
                else
                {
                        write_element_arc
                        (
                                multiplier * (((-package_body_length) / 2.0) - 2 * silkscreen_line_width),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * 0.5 * silkscreen_line_width,
                                multiplier * 0.5 * silkscreen_line_width,
                                0,
                                360,
                                multiplier * silkscreen_line_width
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
        fprintf
        (
                stderr,
                "SUCCESS: wrote a footprint file for a %s package: %s.\n",
                footprint_type,
                footprint_filename
        );
}


/*!
 * \brief Write a SMT footprint with two pads for a molded diode package.
 */
int
write_footprint_smt_molded_diode ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;

        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                fprintf
                (
                        stderr,
                        "Error: could not open file for %s footprint: %s.\n",
                        footprint_type,
                        footprint_filename
                );
                return (EXIT_FAILURE);
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
                        "C", /* pad name */
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
                        "A", /* pad name */
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
                        "C", /* pad name */
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
                        "A", /* pad name */
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
                if (pad_width >= package_body_width)
                {
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
                else
                {
                        /* lines parallel to X-axis */
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * silkscreen_line_width
                        );
                        /* lines perpendicular to X-axis */
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (((-pad_width - silkscreen_line_width) / 2.0) - pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * (-package_body_length / 2.0),
                                multiplier * (((pad_width + silkscreen_line_width) / 2.0) + pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (package_body_length / 2.0),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (((-pad_width - silkscreen_line_width) / 2.0) - pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                multiplier * (package_body_length / 2.0),
                                multiplier * (package_body_width / 2.0),
                                multiplier * (package_body_length / 2.0),
                                multiplier * (((pad_width + silkscreen_line_width) / 2.0) + pad_solder_mask_clearance),
                                multiplier * silkscreen_line_width
                        );
                }
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                if (pad_width >= package_body_width)
                {
                        write_element_line
                        (
                                multiplier * (((-pitch_x + pad_length) / 2.0) + pad_solder_mask_clearance + silkscreen_line_width),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * (((-pitch_x + pad_length) / 2.0) + pad_solder_mask_clearance + silkscreen_line_width),
                                multiplier * (package_body_width / 2.0),
                                multiplier * silkscreen_line_width
                        );
                }
                else
                {
                        write_element_arc
                        (
                                multiplier * (((-package_body_length) / 2.0) - 2 * silkscreen_line_width),
                                multiplier * (-package_body_width / 2.0),
                                multiplier * 0.5 * silkscreen_line_width,
                                multiplier * 0.5 * silkscreen_line_width,
                                0,
                                360,
                                multiplier * silkscreen_line_width
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
        fprintf
        (
                stderr,
                "SUCCESS: wrote a footprint file for a %s package: %s.\n",
                footprint_type,
                footprint_filename
        );
}


/*!
 * \brief Write a TO92 footprint for a transistor package.
 */
int
write_footprint_to92 ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;

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
        xmin = -10500 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        xmax = 10500 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymin = -8600 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymax = 10500 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
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
        else
                pin_pad_flags = g_strdup ("");
        write_pin
        (
                1, /* pin number */
                "", /* pin name */
                -5000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                /* Write pin #1 with a square pad */
                (pin1_square) ? "square" : "" /* flags */
        );
        write_pin
        (
                2, /* pin number */
                "", /* pin name */
                0.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        write_pin
        (
                3, /* pin number */
                "", /* pin name */
                5000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        /* Write package body on the silkscreen */
        if (silkscreen_package_outline)
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
                fprintf (fp, "\tElementLine[-8600 -6000 8600 -6000 1000]\n");
                fprintf (fp, "\tElementArc[0 0 10500 10500 -35 250 1000]\n");
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                /*! \todo Write a pin #1 marker on the silkscreen ! */
        }
        /* Write a courtyard on the silkscreen */
        if (courtyard)
        {
                fprintf (fp, "# Write a courtyard on the silkscreen\n");
                if (package_is_radial)
                {
                        write_element_arc
                        (
                                0.0,
                                0.0,
                                xmax, /* already in mil/100 */
                                ymax, /* already in mil/100 */
                                0,
                                360,
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
 * \brief Write a TH/SMT footprint for a ? package.
 */
int
write_footprint_template ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;

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
                /*! \todo Write a pin/pad entities ! */
        /* Write package body on silkscreen */
        if (silkscreen_package_outline)
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
                /*! \todo Write a package body on the silkscreen ! */
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                /*! \todo Write a pin #1 marker ! on the silkscreen */
        }
        /* Write a courtyard on the silkscreen */
        if (courtyard)
        {
                fprintf (fp, "# Write a courtyard on the silkscreen\n");
                /*! \todo Write a courtyard on the silkscreen ! */
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
 * \brief Write a footprintwizard file based on the current global variables.
 *
 */
int
write_footprintwizard_file (gchar *fpw_filename)
{
        /* Write global variables to footprintwizard file with .fpw suffix */
        FILE *fpw = fopen (fpw_filename, "w");
        if (!fpw)
        {
                fprintf (stderr, "ERROR: could not open footprint wizard file: %s for writing.\n", fpw_filename);
                return (EXIT_FAILURE);
        }
        if (!footprint_filename)
        {
                return (EXIT_FAILURE);
        }
        else
        {
                fprintf (fpw, "%s\n", footprint_filename);
        }
        if (!footprint_name)
        {
                return (EXIT_FAILURE);
        }
        else
        {
                fprintf (fpw, "%s\n", footprint_name);
        }
        if (!footprint_type)
        {
                return (EXIT_FAILURE);
        }
        else
        {
                fprintf (fpw, "%s\n", footprint_type);
        }
        if (!footprint_units)
        {
                return (EXIT_FAILURE);
        }
        else
        {
                fprintf (fpw, "%s\n", footprint_units);
        }
        (!footprint_refdes) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", footprint_refdes);
        (!footprint_value) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", footprint_value);
        fprintf (fpw, "%f\n", package_body_length);
        fprintf (fpw, "%f\n", package_body_width);
        fprintf (fpw, "%f\n", package_body_height);
        fprintf (fpw, "%d\n", package_is_radial);
        (!footprint_author) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", footprint_author);
        (!footprint_dist_license) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", footprint_dist_license);
        (!footprint_use_license) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", footprint_use_license);
        (!footprint_status) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", footprint_status);
        fprintf (fpw, "%d\n", attributes_in_footprint);
        fprintf (fpw, "%d\n", number_of_pins);
        fprintf (fpw, "%d\n", number_of_columns);
        fprintf (fpw, "%d\n", number_of_rows);
        fprintf (fpw, "%f\n", pitch_x);
        fprintf (fpw, "%f\n", pitch_y);
        fprintf (fpw, "%f\n", count_x);
        fprintf (fpw, "%f\n", count_y);
        if (!pad_shape)
        {
                return (EXIT_FAILURE);
        }
        else
        {
                fprintf (fpw, "%s\n", pad_shape);
        }
        (!pin_1_position) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", pin_1_position);
        fprintf (fpw, "%f\n", pad_diameter);
        fprintf (fpw, "%f\n", pin_drill_diameter);
        fprintf (fpw, "%d\n", pin1_square);
        fprintf (fpw, "%f\n", pad_length);
        fprintf (fpw, "%f\n", pad_width);
        fprintf (fpw, "%f\n", pad_clearance);
        fprintf (fpw, "%f\n", pad_solder_mask_clearance);
        fprintf (fpw, "%d\n", thermal);
        fprintf (fpw, "%d\n", thermal_nopaste);
        fprintf (fpw, "%f\n", thermal_length);
        fprintf (fpw, "%f\n", thermal_width);
        fprintf (fpw, "%f\n", thermal_clearance);
        fprintf (fpw, "%f\n", thermal_solder_mask_clearance);
        fprintf (fpw, "%d\n", fiducial);
        fprintf (fpw, "%f\n", fiducial_pad_diameter);
        fprintf (fpw, "%f\n", fiducial_pad_solder_mask_clearance);
        fprintf (fpw, "%d\n", silkscreen_package_outline);
        fprintf (fpw, "%d\n", silkscreen_indicate_1);
        fprintf (fpw, "%f\n", silkscreen_line_width);
        fprintf (fpw, "%d\n", courtyard);
        fprintf (fpw, "%f\n", courtyard_length);
        fprintf (fpw, "%f\n", courtyard_width);
        fprintf (fpw, "%f\n", courtyard_line_width);
        fprintf (fpw, "%f\n", courtyard_clearance_with_package);
        fprintf (fpw, "%f\n", c1);
        fprintf (fpw, "%f\n", g1);
        fprintf (fpw, "%f\n", z1);
        fprintf (fpw, "%f\n", c2);
        fprintf (fpw, "%f\n", g2);
        fprintf (fpw, "%f\n", z2);
        fclose (fpw);
        fprintf (stderr, "SUCCESS: wrote Footprintwizard file %s.\n",
                fpw_filename);
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a footprint based on the global variables.
 *
 * This function does not write the footprint file itself.\n
 * It is a dispatcher for helper functions who <b>actually</b> do write the
 * footprint to file.
 */
int
write_footprint()
{
        /* Switch depending the package type */
        switch (package_type)
        {
                case BGA:
                        write_footprint_bga ();
                        break;
                case CAPC:
                        write_footprint_smt ();
                        break;
                case CAPM:
                        write_footprint_smt_molded ();
                        break;
                case CAPMP:
                        write_footprint_smt_molded_cap ();
                        break;
                case CON_DIL:
                        write_footprint_con_dil ();
                        break;
                case CON_DIP:
                        write_footprint_con_dip ();
                        break;
                case CON_HDR:
//                        write_footprint_con_hdr ();
                        return;
                        break;
                case DIL:
                        return;
                        break;
                case DIOM:
                        write_footprint_smt_molded_diode ();
                        break;
                case DIOMELF:
                        write_footprint_smt_molded_diode ();
                        break;
                case DIP:
                        write_footprint_dip ();
                        break;
                case INDC:
                        write_footprint_smt ();
                        break;
                case INDM:
                        write_footprint_smt_molded ();
                        break;
                case INDP:
                        write_footprint_smt ();
                        break;
                case PGA:
                        write_footprint_pga ();
                        break;
                case PLCC:
                        write_footprint_plcc ();
                        break;
                case QFN:
                        return;
                        break;
                case QFP:
                        return;
                        break;
                case RESC:
                        write_footprint_smt ();
                        break;
                case RESM:
                        write_footprint_smt_molded ();
                        break;
                case RESMELF:
                        write_footprint_smt ();
                        break;
                case SIL:
                        return;
                        break;
                case SIP:
                        return;
                        break;
                case SO:
                        return;
                        break;
                case SOT:
                        return;
                        break;
                case TO92:
                        write_footprint_to92 ();
                        break;
                default:
                        fprintf (stderr, "ERROR: unknown or not yet implemented footprint type entered.\n");
                        return (EXIT_FAILURE);
                        break;
        }
        return (EXIT_SUCCESS);
}

/* EOF */
