/*!
 * \file sot.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Predefined values for SOT footprints.
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
 * \brief Look up default values for SOT footprint.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised known values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * SOT80P330X140-8N, SOT95P228X102-3N, SOT95P230X109-3N, SOT95P230X110-3N,
 * SOT95P230X124-3N, SOT95P237X112-3N, SOT95P240X110-3N, SOT95P251X112-3N,
 * SOT95P270X145-5N, SOT95P275X130-3N, SOT95P275X145-6N, SOT95P279X142-5N,
 * SOT95P280X100-5N, SOT95P280X100-6N, SOT95P280X110-5N, SOT95P280X110-6N,
 * SOT95P280X115-6N, SOT95P280X135-3AN, SOT95P280X135-3N, SOT95P280X135-5N,
 * SOT95P280X145-5AN, SOT95P280X145-5N, SOT95P280X145-6AN, SOT95P280X145-6N,
 * SOT95P284X122-5N, SOT95P284X122-6N, SOT95P285X140-3N, SOT95P285X90-6N,
 * SOT95P470X124-8N.
 */
int
sot_get_default_footprint_values
(
        gchar *footprint_name)
{
        if (!strcmp (footprint_name, "?SOT80P330X140-8N"))
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
                silkscreen_length = ;
                silkscreen_width = ;
                courtyard_length = ;
                courtyard_width = ;
*/
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
/*! \todo Look up datasheet and check values.
                pitch_x = ;
                pad_length = ;
                pad_width = ;
                silkscreen_length = ;
                silkscreen_width = ;
                courtyard_length = ;
                courtyard_width = ;
*/
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("SOT95P470X124-8N");
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

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}
#endif /* GUI */


static fpw_function_t
sot_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                sot_set_gui_constraints,
                "Set GUI constraints for a BGA package",
                NULL
        },
#endif /* GUI */
        {
                "Default Element Values",
                sot_get_default_footprint_values,
                "Get default values for a slected BGA package",
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
