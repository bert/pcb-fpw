/*!
 * \file sot.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Functions for SOT footprints.
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
 * \brief Create a list of SOT packages with pre-defined values.
 *
 * The data in this list can be used in a combo box to select a
 * pre-defined package.
 */
GList
sot_create_packages_list ()
{
        GList *sot_packages_list = NULL;
        sot_packages_list = g_list_append (sot_packages_list, "SOT50P160X90-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT50P210X110-8N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT65P210X100-6N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT65P210X110-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT65P210X110-5N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT65P210X110-6N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT65P275X110-8N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT65P280X100-8N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT65P280X130-8N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT65P280X145-8AN");
        sot_packages_list = g_list_append (sot_packages_list, "SOT65P280X145-8BN");
        sot_packages_list = g_list_append (sot_packages_list, "SOT65P280X145-8N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT80P330X140-8N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P228X102-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P230X109-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P230X110-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P230X124-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P237X112-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P240X110-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P251X112-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P270X145-5N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P275X130-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P275X145-6N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P279X142-5N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P280X100-5N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P280X100-6N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P280X110-5N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P280X110-6N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P280X115-6N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P280X135-3AN");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P280X135-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P280X135-5N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P280X145-5AN");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P280X145-5N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P280X145-6AN");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P280X145-6N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P284X122-5N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P284X122-6N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P285X140-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P285X90-6N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT95P470X124-8N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT100P230X110-3N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT127P700X180-6N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT150P700X180-5N");
        sot_packages_list = g_list_append (sot_packages_list, "SOT230P700X180-4N");
        return (*sot_packages_list);
}


/*!
 * \brief Look up default values for SOT footprint.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised known values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - SOT50P160X90-3N,
 * - SOT50P210X110-8N,
 * - SOT65P210X100-6N,
 * - SOT65P210X110-3N,
 * - SOT65P210X110-5N,
 * - SOT65P210X110-6N,
 * - SOT65P275X110-8N,
 * - SOT65P280X100-8N,
 * - SOT65P280X130-8N,
 * - SOT65P280X145-8AN,
 * - SOT65P280X145-8BN,
 * - SOT65P280X145-8N,
 * - SOT80P330X140-8N,
 * - SOT95P228X102-3N,
 * - SOT95P230X109-3N,
 * - SOT95P230X110-3N,
 * - SOT95P230X124-3N,
 * - SOT95P237X112-3N,
 * - SOT95P240X110-3N,
 * - SOT95P251X112-3N,
 * - SOT95P270X145-5N,
 * - SOT95P275X130-3N,
 * - SOT95P275X145-6N,
 * - SOT95P279X142-5N,
 * - SOT95P280X100-5N,
 * - SOT95P280X100-6N,
 * - SOT95P280X110-5N,
 * - SOT95P280X110-6N,
 * - SOT95P280X115-6N,
 * - SOT95P280X135-3AN,
 * - SOT95P280X135-3N,
 * - SOT95P280X135-5N,
 * - SOT95P280X145-5AN,
 * - SOT95P280X145-5N,
 * - SOT95P280X145-6AN,
 * - SOT95P280X145-6N,
 * - SOT95P284X122-5N,
 * - SOT95P284X122-6N,
 * - SOT95P285X140-3N,
 * - SOT95P285X90-6N,
 * - SOT95P470X124-8N,
 * - SOT100P230X110-3N,
 * - SOT127P700X180-6N,
 * - SOT150P700X180-5N,
 * - SOT230P700X180-4N.
 */
int
sot_get_default_footprint_values
(
        gchar *footprint_name)
{
        if (!strcmp (footprint_name, "?SOT50P160X90-3N"))
        {
                pitch_y = 0.50;
                number_of_pins = 3;
                package_body_length = 0.85;
                package_body_width = 1.70;
                package_body_height = 0.90;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 2;
                pitch_x = 1.40;
                pad_length = 1.10;
                pad_width = 0.30;
                pad_shape = g_strdup ("circular pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.00;
                silkscreen_width = 0.00;
                courtyard_length = 3.00;
                courtyard_width = 2.20;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("SOT50P160X90-3N: footprint is too small for package outline on silkscreen."));
                footprint_name = g_strdup ("SOT50P160X90-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT50P210X110-8N"))
        {
                pitch_y = 0.50;
                number_of_pins = 8;
                package_body_length = 1.40;
                package_body_width = 2.15;
                package_body_height = 1.10;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 4;
                pitch_x = 1.90;
                pad_length = 1.20;
                pad_width = 0.30;
                pad_shape = g_strdup ("circular pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.20;
                silkscreen_width = 2.20;
                courtyard_length = 3.60;
                courtyard_width = 2.20;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT50P210X110-8N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT65P210X100-6N"))
        {
                pitch_y = 0.65;
                number_of_pins = 6;
                package_body_length = 1.35;
                package_body_width = 2.20;
                package_body_height = 1.00;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 1.90;
                pad_length = 1.25;
                pad_width = 0.40;
                pad_shape = g_strdup ("circular pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.20;
                silkscreen_width = 2.20;
                courtyard_length = 3.70;
                courtyard_width = 2.70;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT65P210X100-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT65P210X110-3N"))
        {
                pitch_y = 0.65;
                number_of_pins = 3;
                package_body_length = 1.35;
                package_body_width = 2.20;
                package_body_height = 1.10;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 1.90;
                pad_length = 1.00;
                pad_width = 0.55;
                pad_shape = g_strdup ("circular pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.20;
                silkscreen_width = 2.20;
                courtyard_length = 3.40;
                courtyard_width = 2.70;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT65P210X110-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT65P210X110-5N"))
        {
                pitch_y = 0.65;
                number_of_pins = 5;
                package_body_length = 1.40;
                package_body_width = 2.15;
                package_body_height = 1.10;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 1.90;
                pad_length = 1.20;
                pad_width = 0.40;
                pad_shape = g_strdup ("circular pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.20;
                silkscreen_width = 2.20;
                courtyard_length = 3.60;
                courtyard_width = 2.70;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT65P210X110-5N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT65P210X110-6N"))
        {
                pitch_y = 0.65;
                number_of_pins = 6;
                package_body_length = 1.40;
                package_body_width = 2.15;
                package_body_height = 1.10;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 1.90;
                pad_length = 1.20;
                pad_width = 0.40;
                pad_shape = g_strdup ("circular pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.20;
                silkscreen_width = 2.20;
                courtyard_length = 3.60;
                courtyard_width = 2.70;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT65P210X110-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT65P275X110-8N"))
        {
                pitch_y = 0.65;
                number_of_pins = 8;
                package_body_length = 1.65;
                package_body_width = 3.00;
                package_body_height = 1.10;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 4;
                pitch_x = 2.30;
                pad_length = 1.35;
                pad_width = 0.45;
                pad_shape = g_strdup ("circular pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.20;
                silkscreen_width = 3.00;
                courtyard_length = 4.20;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("SOT65P275X110-8N: side of pads is being trimmed to maintain pad to pad clearance."));
                footprint_name = g_strdup ("SOT65P275X110-8N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT65P280X100-8N"))
        {
                pitch_y = 0.65;
                number_of_pins = 8;
                package_body_length = 1.75;
                package_body_width = 3.00;
                package_body_height = 1.00;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 4;
                pitch_x = 2.40;
                pad_length = 1.35;
                pad_width = 0.45;
                pad_shape = g_strdup ("circular pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.00;
                courtyard_length = 4.30;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("SOT65P280X100-8N: side of pads is being trimmed to maintain pad to pad clearance."));
                footprint_name = g_strdup ("SOT65P280X100-8N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT65P280X130-8N"))
        {
                pitch_y = 0.65;
                number_of_pins = 8;
                package_body_length = 1.75;
                package_body_width = 3.00;
                package_body_height = 1.30;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 4;
                pitch_x = 2.50;
                pad_length = 1.25;
                pad_width = 0.45;
                pad_shape = g_strdup ("circular pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.00;
                courtyard_length = 4.30;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("SOT65P280X130-8N: side of pads is being trimmed to maintain pad to pad clearance."));
                footprint_name = g_strdup ("SOT65P280X130-8N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT65P280X145-8AN"))
        {
                pitch_y = 0.65;
                number_of_pins = 8;
                package_body_length = 1.75;
                package_body_width = 3.05;
                package_body_height = 1.45;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 4;
                pitch_x = 2.50;
                pad_length = 1.20;
                pad_width = 0.45;
                pad_shape = g_strdup ("circular pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.50;
                silkscreen_width = 3.00;
                courtyard_length = 4.20;
                courtyard_width = 3.60;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("SOT65P280X145-8AN: side of pads is being trimmed to maintain pad to pad clearance."));
                footprint_name = g_strdup ("SOT65P280X145-8AN");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT65P280X145-8BN"))
        {
                pitch_y = 0.65;
                number_of_pins = 8;
                package_body_length = 1.75;
                package_body_width = 3.00;
                package_body_height = 1.45;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 4;
                pitch_x = 2.40;
                pad_length = 1.35;
                pad_width = 0.45;
                pad_shape = g_strdup ("circular pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.00;
                courtyard_length = 4.30;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("SOT65P280X145-8BN: side of pads is being trimmed to maintain pad to pad clearance."));
                footprint_name = g_strdup ("SOT65P280X145-8BN");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT65P280X145-8N"))
        {
                pitch_y = 0.65;
                number_of_pins = 8;
                package_body_length = 1.75;
                package_body_width = 3.05;
                package_body_height = 1.45;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 4;
                pitch_x = 2.50;
                pad_length = 1.25;
                pad_width = 0.45;
                pad_shape = g_strdup ("circular pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.00;
                courtyard_length = 4.30;
                courtyard_width = 3.60;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("SOT65P280X145-8N: side of pads is being trimmed to maintain pad to pad clearance."));
                footprint_name = g_strdup ("SOT65P280X145-8N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT80P330X140-8N"))
        {
                /* SOT80P330X140-8N
                 * SOT, 0.80mm pitch;
                 * 8 pin, 2.27mm W X 3.80mm L X 1.40mm H body
                 * SOT23-8 National Semiconductor 8L SOT23 MF08A */
                pitch_y = 0.80;
                number_of_pins = 8;
                package_body_width = 2.27;
                package_body_length = 3.80;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 4;
                pitch_x = 3.00;
                pad_length = 1.15;
                pad_width = 0.50;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 1.00;
                silkscreen_width = 3.80;
                courtyard_length = 4.70;
                courtyard_width = 4.30;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT80P330X140-8N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P228X102-3N"))
        {
                /* SOT95P228X102-3N
                 * SOT, 0.95mm pitch;
                 * 3 pin, 1.50mm W X 3.04mm L X 1.02mm H body
                 * Dallas/Maxim 56-G2017-001 SOT23 */
                pitch_y = 0.95;
                number_of_pins = 3;
                package_body_width = 1.50;
                package_body_length = 3.04;
                package_body_height = 1.02;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 0.65;
                pad_length = 1.05;
                pad_width = 0.65;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.50;
                silkscreen_width = 3.00;
                courtyard_length = 3.80;
                courtyard_width = 3.60;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P228X102-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P230X109-3N"))
        {
                /* SOT95P230X109-3N
                 * SOT, 0.95mm pitch;
                 * 3 pin, 1.40mm W X 3.00mm L X 1.09mm H Body
                 * TO-236AB Fairchild SOT-23 FS-49 */
                pitch_y = 0.95;
                number_of_pins = 3;
                package_body_width = 1.40;
                package_body_length = 3.00;
                package_body_height = 1.09;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
/*! \todo Look up datasheet and check values.
                pitch_x = ;
                pad_length = ;
                pad_width = ;
                pad_shape = g_strdup ("rectangular pad");
                silkscreen_length = ;
                silkscreen_width = ;
                courtyard_length = ;
                courtyard_width = ;
*/
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P230X109-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P230X110-3N"))
        {
                /* SOT95P230X110-3N
                 * SOT, 0.95mm pitch;
                 * 3 pin, 1.40mm W X 3.00mm L X 1.10mm H Body
                 * JEDEC TO-236AB Philips SOT23 */
                pitch_y = 0.95;
                number_of_pins = 3;
                package_body_width = 1.40;
                package_body_length = 3.00;
                package_body_height = 1.10;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.00;
                pad_length = 1.25;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.20;
                silkscreen_width = 3.00;
                courtyard_length = 3.80;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P230X110-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P230X124-3N"))
        {
                /* SOT95P230X124-3N
                 * SOT, 0.95mm pitch;
                 * 3 pin, 1.40mm W X 3.04mm L X 1.24mm H body
                 * JEDEC TO-236AA, SOT23 National Semiconductor 3L SOT23 M03A */
                pitch_y = 0.95;
                number_of_pins = 3;
                package_body_width = 1.40;
                package_body_length = 3.00;
                package_body_height = 1.24;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.00;
                pad_length = 1.25;
                pad_width = 0.65;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.20;
                silkscreen_width = 3.00;
                courtyard_length = 3.80;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P230X124-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P237X112-3N"))
        {
                /* SOT95P237X112-3N
                 * SOT, 0.95mm pitch;
                 * 3 pin, 1.40mm W X 3.04mm L X 1.12mm H Body
                 * JEDEC TO-236AB Analog Devices 3 LEAD SOT23 RT-3
                 * JEDEC TO-236AB Dallas/Maxim 21-0051 SOT23
                 * JEDEC TO-236AB Dallas/Maxim 3L SOT-23 3L SOT-23
                 * JEDEC TO-236AB Linear 3-Lead Plastic SOT-23 S3 Package
                 * JEDEC TO-236AB National Semiconductor 3L SOT23 MF03A
                 * JEDEC TO-236AB Texas Instruments 3 SOT-23 DBZ
                 * JEDEC TO-236AB JEDEC STD Package TO-236 R-PDSO-G */
                pitch_y = 0.95;
                number_of_pins = 3;
                package_body_width = 1.40;
                package_body_length = 3.04;
                package_body_height = 1.12;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.10;
                pad_length = 1.30;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.20;
                silkscreen_width = 3.00;
                courtyard_length = 3.90;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P237X112-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P240X110-3N"))
        {
                /* SOT95P240X110-3N
                 * SOT, 0.95mm pitch;
                 * 3 pin, 1.40mm W X 3.00mm L X 1.10mm H Body
                 * SOT23 Diodes, Inc. SOT-23 SOT-23 */
                pitch_y = 0.95;
                number_of_pins = 3;
                package_body_width = 1.40;
                package_body_length = 3.00;
                package_body_height = 1.10;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.10;
                pad_length = 1.30;
                pad_width = 0.65;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.20;
                silkscreen_width = 3.00;
                courtyard_length = 3.80;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P240X110-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P240X114-3N"))
        {
                /* SOT95P240X114-3N
                 * SOT, 0.95mm pitch;
                 * 3 pin, 1.40mm W X 3.00mm L X 1.14mm H body
                 * Fairchild SOT-23 FS-AU */
                pitch_y = 0.95;
                number_of_pins = 3;
                package_body_width = 1.40;
                package_body_length = 3.00;
                package_body_height = 1.14;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
/*! \todo Look up datasheet and check values.
                pitch_x = ;
                pad_length = ;
                pad_width = ;
                silkscreen_length = ;
                silkscreen_width = ;
                courtyard_length = ;
                courtyard_width = ;
*/
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P240X114-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P251X112-3N"))
        {
                /* SOT95P251X112-3N
                 * SOT, 0.95mm pitch;
                 * 3 pin, 1.52mm W X 3.04mm L X 1.12mm H body
                 * Fairchild SSOT-3 MA03, FS-32 */
                pitch_y = 0.95;
                number_of_pins = 3;
                package_body_width = 1.52;
                package_body_length = 3.04;
                package_body_height = 1.12;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
/*! \todo Look up datasheet and check values.
                pitch_x = ;
                pad_length = ;
                pad_width = ;
                silkscreen_length = ;
                silkscreen_width = ;
                courtyard_length = ;
                courtyard_width = ;
*/
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P251X112-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P270X145-5N"))
        {
                /* SOT95P270X145-5N
                 * SOT, 0.95mm pitch;
                 * 5 pin, 1.80mm W X 3.10mm L X 1.45mm H body
                 * EIAJ SC-74A Fairchild SOT-23-5 S5, T5
                 * EIAJ SC-74A Fairchild SOT-23-5 MA05B, M5, M5X */
                pitch_y = 0.95;
                number_of_pins = 5;
                package_body_width = 1.80;
                package_body_length = 3.10;
                package_body_height = 1.45;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
/*! \todo Look up datasheet and check values.
                pitch_x = ;
                pad_length = ;
                pad_width = ;
                silkscreen_length = ;
                silkscreen_width = ;
                courtyard_length = ;
                courtyard_width = ;
*/
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P270X145-5N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P275X130-3N"))
        {
                /* SOT95P275X130-3N
                 * SOT, 0.95mm pitch;
                 * 3 pin, 1.70mm W X 3.10mm L X 1.30mm H Body
                 * SOT346 SOT346 */
                pitch_y = 0.95;
                number_of_pins = 3;
                package_body_width = 1.70;
                package_body_length = 3.10;
                package_body_height = 1.30;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.50;
                pad_length = 1.25;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.10;
                courtyard_length = 4.30;
                courtyard_width = 3.60;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P275X130-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P275X145-6N"))
        {
                /* SOT95P275X145-6N
                 * SOT, 0.95mm pitch;
                 * 6 pin, 1.80mm W X 3.10mm L X 1.45mm H Body
                 * SOT26 SOT26 */
                pitch_y = 0.95;
                number_of_pins = 6;
                package_body_width = 1.80;
                package_body_length = 3.10;
                package_body_height = 1.45;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.50;
                pad_length = 1.25;
                pad_width = 0.65;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.10;
                courtyard_length = 4.30;
                courtyard_width = 3.60;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P275X145-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P279X142-5N"))
        {
                /* SOT95P279X142-5N
                 * SOT, 0.95mm pitch;
                 * 5 pin, 1.76mm W X 3.04mm L X 1.42mm H body
                 * SOT23-5 National Semiconductor 5L SOT23 MA05A
                 * SOT23-5 National Semiconductor 5L SOT23 MA05B */
                pitch_y = 0.95;
                number_of_pins = 5;
                package_body_width = 1.76;
                package_body_length = 3.04;
                package_body_height = 1.42;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.50;
                pad_length = 1.25;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.00;
                courtyard_length = 4.30;
                courtyard_width = 3.60;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P279X142-5N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P280X100-5N"))
        {
                /* SOT95P280X100-5N
                 * SOT, 0.95mm pitch;
                 * 5 pin, 1.75mm W X 3.00mm L X 1.00mm H Body
                 * JEDEC MO-193 Linear 5-Lead Plastic TSOT-23 S5 Package */
                pitch_x = 0.95;
                number_of_pins = 5;
                package_body_width = 1.75;
                package_body_length = 3.00;
                package_body_height = 1.00;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.40;
                pad_length = 1.35;
                pad_width = 0.55;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.00;
                courtyard_length = 4.30;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P280X100-5N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P280X100-6N"))
        {
                /* SOT95P280X100-6N
                 * SOT, 0.95mm pitch;
                 * 6 pin, 1.75mm W X 3.00mm L X 1.00mm H Body
                 * JEDEC MO-193 Linear 6-Lead Plastic TSOT-23 S6 Package */
                pitch_y = 0.95;
                number_of_pins = 6;
                package_body_width = 1.75;
                package_body_length = 3.00;
                package_body_height = 1.00;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.40;
                pad_length = 1.35;
                pad_width = 0.55;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.00;
                courtyard_length = 4.30;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P280X100-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P280X110-5N"))
        {
                /* SOT95P280X110-5N
                 * SOT, 0.95mm pitch;
                 * 5 pin, 1.75mm W X 3.05mm L X 1.10mm H Body
                 * JEDEC MO-193AB Analog Devices 5 LEAD TSOT UJ-5
                 * JEDEC MO-193AB Dallas/Maxim 21-0113 Thin SOT23
                 * JEDEC MO-193AB Texas Instruments 5 TO/SOT DDC */
                pitch_y = 0.95;
                number_of_pins = 5;
                package_body_width = 1.75;
                package_body_length = 3.05;
                package_body_height = 1.10;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.50;
                pad_length = 1.25;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.00;
                courtyard_length = 4.30;
                courtyard_width = 3.60;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P280X110-5N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P280X110-6N"))
        {
                /* SOT95P280X110-6N
                 * SOT, 0.95mm pitch;
                 * 6 pin, 1.75mm W X 3.05mm L X 1.10mm H Body
                 * JEDEC MO-193AA Analog Devices 6 LEAD TSOT UJ-6
                 * JEDEC MO-193AA Dallas/Maxim 21-0114 Thin SOT23
                 * JEDEC MO-193AA Fairchild TSOP-6
                 * JEDEC MO-193AA Texas Instruments 6 TO/SOT DDC */
                pitch_y = 0.95;
                number_of_pins = 6;
                package_body_width = 1.75;
                package_body_length = 3.05;
                package_body_height = 1.10;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.50;
                pad_length = 1.25;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.00;
                courtyard_length = 4.30;
                courtyard_width = 3.60;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P280X110-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P280X115-6N"))
        {
                /* SOT95P280X115-6N
                 * SOT, 0.95mm pitch;
                 * 6 pin, 2.00mm W X 3.10mm L X 1.15mm H body
                 * JEDEC MO-178 Philips Plastic/Surface mount/Dual/SO SO6/SOP004 */
                pitch_y = 0.95;
                number_of_pins = 6;
                package_body_width = 2.00;
                package_body_length = 3.10;
                package_body_height = 1.15;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
/*! \todo Look up datasheet and check values.
                pitch_x = ;
                pad_length = ;
                pad_width = ;
                silkscreen_length = ;
                silkscreen_width = ;
                courtyard_length = ;
                courtyard_width = ;
*/
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P280X115-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P280X135-3AN"))
        {
                /* SOT95P280X135-3AN
                 * SOT, 0.95mm pitch;
                 * 3 pin, 1.70mm W X 3.00mm L X 1.35mm H body
                 * Philips Plastic/Surface mount/Dual/SO SO3/SOP015 */
                pitch_y = 0.95;
                number_of_pins = 3;
                package_body_width = 1.70;
                package_body_length = 3.00;
                package_body_height = 1.35;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
/*! \todo Look up datasheet and check values.
                pitch_x = ;
                pad_length = ;
                pad_width = ;
                silkscreen_length = ;
                silkscreen_width = ;
                courtyard_length = ;
                courtyard_width = ;
*/
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P280X135-3AN");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P280X135-3N"))
        {
                /* SOT95P280X135-3N
                 * SOT, 0.95mm pitch;
                 * 3 pin, 1.30mm W X 2.90mm L X 1.35mm H Body
                 * SOT23 Texas Instruments 3 SOT-23 DBV */
                pitch_y = 0.95;
                number_of_pins = 3;
                package_body_width = 1.30;
                package_body_length = 2.90;
                package_body_height = 1.35;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.30;
                pad_length = 1.40;
                pad_width = 0.65;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.20;
                silkscreen_width = 2.90;
                courtyard_length = 4.20;
                courtyard_width = 3.40;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P280X135-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P280X135-5N"))
        {
                /* SOT95P280X135-5N
                 * SOT, 0.95mm pitch;
                 * 5 pin, 1.70mm W X 3.00mm L X 1.35mm H body
                 * JEDEC MO-178 Philips Plastic/Surface mount/Dual/SO SO5/SOP003 */
                pitch_y = 0.95;
                number_of_pins = 5;
                package_body_width = 1.70;
                package_body_length = 3.00;
                package_body_height = 1.35;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
/*! \todo Look up datasheet and check values.
                pitch_x = ;
                pad_length = ;
                pad_width = ;
                silkscreen_length = ;
                silkscreen_width = ;
                courtyard_length = ;
                courtyard_width = ;
*/
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P280X135-5N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P280X145-5AN"))
        {
                /* SOT95P280X145-5AN
                 * SOT, 0.95mm pitch;
                 * 5 pin, 1.75mm W X 3.00mm L X 1.45mm H Body
                 * JEDEC MO-178AA Analog Devices 5 LEAD SOT23 RJ-5
                 * JEDEC MO-178AA Texas Instruments 5 ZZ (BB) ZZ331 */
                pitch_y = 0.95;
                number_of_pins = 5;
                package_body_width = 1.75;
                package_body_length = 3.00;
                package_body_height = 1.45;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.50;
                pad_length = 1.20;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.50;
                silkscreen_width = 3.00;
                courtyard_length = 4.20;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P280X145-5AN");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P280X145-5N"))
        {
                /* SOT95P280X145-5N
                 * SOT, 0.95mm pitch;
                 * 5 pin, 1.75mm W X 3.05mm L X 1.45mm H Body
                 * JEDEC MO-178AA Dallas/Maxim 21-0057 SOT23
                 * JEDEC MO-178AA Dallas/Maxim 56-G2017-002 SOT23
                 * JEDEC MO-178AA Texas Instruments 5 SOT-23 DBV */
                pitch_y = 0.95;
                number_of_pins = 5;
                package_body_width = 1.75;
                package_body_length = 3.05;
                package_body_height = 1.45;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.50;
                pad_length = 1.20;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.50;
                silkscreen_width = 3.00;
                courtyard_length = 4.20;
                courtyard_width = 3.60;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P280X145-5N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P280X145-6AN"))
        {
                /* SOT95P280X145-6AN
                 * SOT, 0.95mm pitch;
                 * 6 pin, 1.70mm W X 3.00mm L X 1.45mm H Body
                 * JEDEC MO-178AB Analog Devices 6 LEAD SOT23 RJ-6
                 * JEDEC MO-178AB Texas Instruments 6 ZZ (BB) ZZ332 */
                pitch_y = 0.95;
                number_of_pins = 6;
                package_body_width = 1.70;
                package_body_length = 3.00;
                package_body_height = 1.45;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.50;
                pad_length = 1.20;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.50;
                silkscreen_width = 3.00;
                courtyard_length = 4.20;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P280X145-6AN");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P280X145-6N"))
        {
                /* SOT95P280X145-6N
                 * SOT, 0.95mm pitch;
                 * 6 pin, 1.75mm W X 3.05mm L X 1.45mm H Body
                 * JEDEC MO-178AB Dallas/Maxim 21-0058 SOT23
                 * JEDEC MO-178AB Texas Instruments 6 SOT-23 DBV */
                pitch_y = 0.95;
                number_of_pins = 6;
                package_body_width = 1.75;
                package_body_length = 3.05;
                package_body_height = 1.45;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.50;
                pad_length = 1.20;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.50;
                silkscreen_width = 3.00;
                courtyard_length = 4.20;
                courtyard_width = 3.60;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P280X145-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P284X122-5N"))
        {
                /* SOT95P284X122-5N
                 * SOT, 0.95mm pitch;
                 * 5 pin, 1.67mm W X 2.99mm L X 1.22mm H body
                 * JEDEC MO-178AA, SOT23-5 National Semiconductor 5L SOT23 MF05A */
                pitch_y = 0.95;
                number_of_pins = 5;
                package_body_width = 1.67;
                package_body_length = 2.99;
                package_body_height = 1.22;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.40;
                pad_length = 1.35;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.00;
                courtyard_length = 4.30;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P284X122-5N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P284X122-6N"))
        {
                /* SOT95P284X122-6N
                 * SOT, 0.95mm pitch;
                 * 6 pin, 1.67mm W X 2.99mm L X 1.22mm H body
                 * JEDEC MO-178AB, SOT23-6 Fairchild SSOT-6 FS-31, 33
                 * JEDEC MO-178AB, SOT23-6 National Semiconductor 6L SOT23 MF06A
                 * JEDEC MO-178AB, SOT23-6 National Semiconductor 6L SOT23 MA06A */
                pitch_y = 0.95;
                number_of_pins = 6;
                package_body_width = 1.67;
                package_body_length = 2.99;
                package_body_height = 1.22;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.40;
                pad_length = 1.35;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.00;
                courtyard_length = 4.30;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P284X122-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P285X140-3N"))
        {
                /* SOT95P285X140-3N
                 * SOT, 0.95mm pitch;
                 * 3 pin, 1.70mm W X 3.10mm L X 1.40mm H Body
                 * SC-59 Diodes, Inc. SC-59 SC-59 */
                pitch_y = 0.95;
                number_of_pins = 3;
                package_body_width = 1.70;
                package_body_length = 3.10;
                package_body_height = 1.40;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.40;
                pad_length = 1.35;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.10;
                courtyard_length = 4.30;
                courtyard_width = 3.60;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P285X140-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P285X90-6N"))
        {
                /* SOT95P285X90-6N
                 * SOT, 0.95mm pitch;
                 * 6 pin, 1.75mm W X 3.07mm L X 0.90mm H body
                 * JEDEC MO-193AA, SOT23-6 National Semiconductor 6L TSOT MK06A */
                pitch_y = 0.95;
                number_of_pins = 6;
                package_body_width = 1.75;
                package_body_length = 3.07;
                package_body_height = 0.90;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 2.40;
                pad_length = 1.30;
                pad_width = 0.60;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.50;
                silkscreen_width = 3.10;
                courtyard_length = 4.20;
                courtyard_width = 3.60;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P285X90-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT95P470X124-8N"))
        {
                /* SOT95P470X124-8N
                 * SOT, 0.95mm pitch;
                 * 8 pin, 3.42mm W X 4.18mm L X 1.24mm H body
                 * Fairchild SSOT-8 MA08C */
                pitch_y = 0.95;
                number_of_pins = 8;
                package_body_width = 3.42;
                package_body_length = 4.18;
                package_body_height = 1.24;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 4.40;
                pad_length = 1.00;
                pad_width = 0.70;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 3.30;
                silkscreen_width = 4.06;
//                courtyard_length = ;
                courtyard_width = 4.85;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P470X124-8N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT100P230X110-3N"))
        {
                pitch_y = 1.00;
                number_of_pins = 3;
                package_body_width = 1.40;
                package_body_length = 3.00;
                package_body_height = 1.10;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 1.00;
                pad_length = 1.10;
                pad_width = 0.60;
                pad_shape = g_strdup ("rounded pad, elongated");
                pad_shapes_type = ROUND_ELONGATED;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_length = 0.40;
                silkscreen_width = 3.00;
                courtyard_length = 3.70;
                courtyard_width = 3.50;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT100P230X110-3N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT127P700X180-6N"))
        {
                pitch_y = 1.27;
                number_of_pins = 6;
                package_body_width = 3.55;
                package_body_length = 6.55;
                package_body_height = 1.80;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 5;
                pitch_x = 6.00;
                pad_length = 2.05;
                pad_width = 0.65;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = TRUE;
                thermal_length = 2.05;
                thermal_width = 3.20;
                silkscreen_length = 3.20;
                silkscreen_width = 6.60;
                courtyard_length = 8.60;
                courtyard_width = 7.10;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT127P700X180-6N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT150P700X180-5N"))
        {
                pitch_y = 1.50;
                number_of_pins = 5;
                package_body_width = 3.70;
                package_body_length = 6.70;
                package_body_height = 1.80;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 4;
                pitch_x = 5.80;
                pad_length = 2.15;
                pad_width = 0.95;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = TRUE;
                thermal_length = 2.15;
                thermal_width = 3.15;
                silkscreen_length = 2.80;
                silkscreen_width = 6.70;
                courtyard_length = 8.50;
                courtyard_width = 7.20;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT150P700X180-5N");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?SOT230P700X180-4N"))
        {
                pitch_y = 2.30;
                number_of_pins = 4;
                package_body_width = 3.70;
                package_body_length = 6.70;
                package_body_height = 1.80;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 5.80;
                pad_length = 2.15;
                pad_width = 0.95;
                pad_shape = g_strdup ("rectangular pad");
                pad_shapes_type = SQUARE;
                thermal = TRUE;
                thermal_length = 2.15;
                thermal_width = 3.25;
                silkscreen_length = 2.80;
                silkscreen_width = 6.70;
                courtyard_length = 8.50;
                courtyard_width = 7.20;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT230P700X180-4N");
                return (EXIT_SUCCESS);
        }
        else
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("default values for footprint %s not found.\n"),
                        footprint_name);
                return (EXIT_FAILURE);
        }
}


#if GUI
/*!
 * \brief Set GUI constraints for the SOT package type.
 */
int
sot_set_gui_constraints (GtkWidget *widget)
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

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}
#endif /* GUI */


/*!
 * \brief Write a footprint for a SOT package.
 */
int
sot_write_footprint ()
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
                (pad_length / 2.0) -
                pad_solder_mask_clearance
        );
        xmax = multiplier *
        (
                ((pitch_x * number_of_columns) / 2.0) +
                (pad_length / 2.0) +
                pad_solder_mask_clearance
        );
        ymin = multiplier *
        (
                ((-pitch_y * number_of_rows) / 2.0) -
                (pad_width / 2.0) -
                pad_solder_mask_clearance
        );
        ymax = multiplier *
        (
                ((pitch_y * number_of_rows) / 2.0) +
                (pad_width / 2.0) +
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
        if (!strcmp (pad_shape, "rectangular pad"))
                pin_pad_flags = g_strdup ("square");
        /* Write pin and/or pad entities */
        if (number_of_pins == 3)
        {
                if (!thermal)
                {
                        /* Pad #1 */
                        pin_number = 1;
                        write_pad
                        (
                                pin_number, /* pin number */
                                "", /* pin name */
                                multiplier * ((-pitch_x - pad_length + pad_width) / 2.0), /* x0 coordinate */
                                multiplier * (-pitch_y), /* y0-coordinate */
                                multiplier * ((-pitch_x + pad_length - pad_width) / 2.0), /* x1 coordinate */
                                multiplier * (-pitch_y), /* y1-coordinate */
                                multiplier * pad_width, /* pad width */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                        /* Pad #2 */
                        pin_number++;
                        write_pad
                        (
                                pin_number, /* pin number */
                                "", /* pin name */
                                multiplier * ((-pitch_x - pad_length + pad_width) / 2.0), /* x0 coordinate */
                                multiplier * (pitch_y), /* y0-coordinate */
                                multiplier * ((-pitch_x + pad_length - pad_width) / 2.0), /* x1 coordinate */
                                multiplier * (pitch_y), /* y1-coordinate */
                                multiplier * pad_width, /* pad width */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                        /* Pad #3 */
                        pin_number++;
                        write_pad
                        (
                                pin_number, /* pin number */
                                "", /* pin name */
                                multiplier * ((pitch_x + pad_length - pad_width) / 2.0), /* x0 coordinate */
                                0, /* y0-coordinate */
                                multiplier * ((pitch_x - pad_length + pad_width) / 2.0), /* x1 coordinate */
                                0, /* y1-coordinate */
                                multiplier * pad_width, /* pad width */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                }
        }
        else if (number_of_pins == 4)
        {
                if (thermal)
                {
                        /* Left side pads */
                        int i;
                        for (i = 0; (i < (number_of_rows)); i++)
                        {
                                pin_number = 1 + i;
                                write_pad
                                (
                                        pin_number, /* pin number */
                                        "", /* pin name */
                                        multiplier * ((-pitch_x - pad_length + pad_width) / 2.0), /* x0 coordinate */
                                        multiplier * ((((-number_of_rows - 1) / 2.0) +1 + i) * pitch_y), /* y0-coordinate */
                                        multiplier * ((-pitch_x + pad_length - pad_width) / 2.0), /* x1 coordinate */
                                        multiplier * ((((-number_of_rows - 1) / 2.0) +1 + i) * pitch_y), /* y1-coordinate */
                                        multiplier * pad_width, /* pad width */
                                        multiplier * pad_clearance, /* clearance */
                                        multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                        pin_pad_flags /* flags */
                                );
                        }
                        /* Thermal pad */
                        pin_number++;
                        write_pad
                        (
                                pin_number, /* pin number */
                                "", /* pin name */
                                thermal_length > thermal_width
                                ? multiplier * ((pitch_x - pad_length + pad_width) / 2.0)
                                : multiplier * (pitch_x / 2.0), /* x0 coordinate */
                                thermal_length > thermal_width
                                ? 0
                                : multiplier * ((- thermal_width + thermal_length) / 2.0), /* y0-coordinate */
                                thermal_length > thermal_width
                                ? multiplier * ((pitch_x + pad_length - pad_width) / 2.0)
                                : multiplier * (pitch_x / 2.0), /* x1 coordinate */
                                thermal_length > thermal_width
                                ? 0
                                : multiplier * ((+ thermal_width - thermal_length) / 2.0), /* y1-coordinate */
                                thermal_length > thermal_width
                                ? multiplier * thermal_width
                                : multiplier * thermal_length, /* pad width */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * ((thermal_length > thermal_width ? thermal_width : thermal_length) + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                }
        }
        else if (number_of_pins == 5)
        {
                if (thermal)
                {
                        /* Left side pads */
                        int i;
                        for (i = 0; (i < (number_of_rows)); i++)
                        {
                                pin_number = 1 + i;
                                write_pad
                                (
                                        pin_number, /* pin number */
                                        "", /* pin name */
                                        multiplier * ((-pitch_x - pad_length + pad_width) / 2.0), /* x0 coordinate */
                                        multiplier * ((((-number_of_rows - 1) / 2.0) +1 + i) * pitch_y), /* y0-coordinate */
                                        multiplier * ((-pitch_x + pad_length - pad_width) / 2.0), /* x1 coordinate */
                                        multiplier * ((((-number_of_rows - 1) / 2.0) +1 + i) * pitch_y), /* y1-coordinate */
                                        multiplier * pad_width, /* pad width */
                                        multiplier * pad_clearance, /* clearance */
                                        multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                        pin_pad_flags /* flags */
                                );
                        }
                        /* Thermal pad */
                        pin_number++;
                        write_pad
                        (
                                pin_number, /* pin number */
                                "", /* pin name */
                                thermal_length > thermal_width
                                ? multiplier * ((pitch_x - pad_length + pad_width) / 2.0)
                                : multiplier * (pitch_x / 2.0), /* x0 coordinate */
                                thermal_length > thermal_width
                                ? 0
                                : multiplier * ((- thermal_width + thermal_length) / 2.0), /* y0-coordinate */
                                thermal_length > thermal_width
                                ? multiplier * ((pitch_x + pad_length - pad_width) / 2.0)
                                : multiplier * (pitch_x / 2.0), /* x1 coordinate */
                                thermal_length > thermal_width
                                ? 0
                                : multiplier * ((+ thermal_width - thermal_length) / 2.0), /* y1-coordinate */
                                thermal_length > thermal_width
                                ? multiplier * thermal_width
                                : multiplier * thermal_length, /* pad width */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * ((thermal_length > thermal_width ? thermal_width : thermal_length) + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                }
                else
                {
                        /* Left side pads */
                        int i;
                        for (i = 0; (i < (number_of_rows)); i++)
                        {
                                pin_number = 1 + i;
                                write_pad
                                (
                                        pin_number, /* pin number */
                                        "", /* pin name */
                                        multiplier * ((-pitch_x - pad_length + pad_width) / 2.0), /* x0 coordinate */
                                        multiplier * ((((-number_of_rows - 1) / 2.0) +1 + i) * pitch_y), /* y0-coordinate */
                                        multiplier * ((-pitch_x + pad_length - pad_width) / 2.0), /* x1 coordinate */
                                        multiplier * ((((-number_of_rows - 1) / 2.0) +1 + i) * pitch_y), /* y1-coordinate */
                                        multiplier * pad_width, /* pad width */
                                        multiplier * pad_clearance, /* clearance */
                                        multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                        pin_pad_flags /* flags */
                                );
                                /* Right side pads */
                                pin_number++;
                                write_pad
                                (
                                        pin_number, /* pin number */
                                        "", /* pin name */
                                        multiplier * ((pitch_x - pad_length + pad_width) / 2.0), /* x0 coordinate */
                                        multiplier * (pitch_y), /* y0-coordinate */
                                        multiplier * ((pitch_x + pad_length - pad_width) / 2.0), /* x1 coordinate */
                                        multiplier * (pitch_y), /* y1-coordinate */
                                        multiplier * pad_width, /* pad width */
                                        multiplier * pad_clearance, /* clearance */
                                        multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                        pin_pad_flags /* flags */
                                );
                                pin_number++;
                                write_pad
                                (
                                        pin_number, /* pin number */
                                        "", /* pin name */
                                        multiplier * ((pitch_x - pad_length + pad_width) / 2.0), /* x0 coordinate */
                                        multiplier * (-pitch_y), /* y0-coordinate */
                                        multiplier * ((pitch_x + pad_length - pad_width) / 2.0), /* x1 coordinate */
                                        multiplier * (-pitch_y), /* y1-coordinate */
                                        multiplier * pad_width, /* pad width */
                                        multiplier * pad_clearance, /* clearance */
                                        multiplier * ((pad_length > pad_width ? pad_width : pad_length) + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                        pin_pad_flags /* flags */
                                );
                        }
                }
        }
        else
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("number of pins of %d is not defined in sot_write_footprint()."),
                        number_of_pins);
        }
        /* Write a package body on the silkscreen */
        if (silkscreen_package_outline)
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
                write_rectangle
                (
                        multiplier * (-silkscreen_length / 2.0),
                        multiplier * (-silkscreen_width / 2.0),
                        multiplier * (silkscreen_length / 2.0),
                        multiplier * (silkscreen_width / 2.0),
                        multiplier * silkscreen_line_width
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                fprintf (fp, "# Write a pin 1 marker on the silkscreen\n");
                write_element_arc
                (
                        multiplier * (-pitch_x / 2.0), /* x-coordinate */
                        multiplier * (-pitch_y * (number_of_rows) / 2.0), /* y-coordinate */
                        multiplier * 0.5 * silkscreen_line_width, /* width */
                        multiplier * 0.5 * silkscreen_line_width, /*height */
                        0, /* start angke */
                        360, /* delta angle */
                        multiplier * silkscreen_line_width /* line width */
                );
        }
        /* Write a courtyard on the silkscreen */
        if (courtyard)
        {
                fprintf (fp, "# Write a courtyard on the silkscreen\n");
                write_rectangle
                (
                        courtyard_length > (package_body_length + courtyard_clearance_with_package)
                        ? (multiplier * (-courtyard_length / 2.0))
                        : (multiplier * ((-package_body_length - courtyard_clearance_with_package) / 2.0)),
                        courtyard_width > (package_body_width + courtyard_clearance_with_package)
                        ? (multiplier * (-courtyard_width / 2.0))
                        : (multiplier * ((-package_body_width - courtyard_clearance_with_package) / 2.0)),
                        courtyard_length > (package_body_length + courtyard_clearance_with_package)
                        ? (multiplier * (courtyard_length / 2.0))
                        : (multiplier * ((package_body_length + courtyard_clearance_with_package) / 2.0)),
                        courtyard_width > (package_body_width + courtyard_clearance_with_package)
                        ? (multiplier * (courtyard_width / 2.0))
                        : (multiplier * ((package_body_width + courtyard_clearance_with_package) / 2.0)),
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
sot_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                sot_set_gui_constraints,
                "Set GUI constraints for a SOT package",
                NULL
        },
#endif /* GUI */
        {
                "Packages list",
                sot_create_packages_list,
                "Create a list of known SOT packages",
                NULL
        },
        {
                "Default Element Values",
                sot_get_default_footprint_values,
                "Get default values for a selected SOT package",
                NULL
        },
        {
                "Write footprint",
                sot_write_footprint,
                "Write a footprint for a SOT package",
                NULL
        }
};


REGISTER_FUNCTIONS (sot_function_list)

void
sot_init ()
{
        register_sot_function_list ();
}


/* EOF */
