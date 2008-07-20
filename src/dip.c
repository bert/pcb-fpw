/*!
 * \file dip.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Predefined values for DIP footprints.
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

/*!
 * \brief Look up default values for DIP footprint.
 */
int
dip_get_default_footprint_values
(
        gchar *footprint_name)
{
        if (!strcmp (footprint_name, "?DIP06300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 6;
                package_body_width = 300;
                package_body_length = 300;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 3;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 4;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 4;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP08400");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP14300"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 14;
                package_body_width = 300;
                package_body_length = 700;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 7;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                number_of_rows = 4;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 8;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                number_of_rows = 8;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 9;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 9;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 10;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                number_of_rows = 10;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 11;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                number_of_rows = 11;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 12;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 12;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 12;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 14;
                pitch_x = 300;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                number_of_rows = 14;
                pitch_x = 400;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 14;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP28600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP32600"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 32;
                package_body_width = 600;
                package_body_length = 1600;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 16;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                number_of_rows = 18;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP36600");
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (footprint_name, "?DIP40600"))
        {
                footprint_units = g_strdup ("mil");
                number_of_pins = 40;
                package_body_width = 600;
                package_body_length = 2000;
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 20;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                number_of_rows = 21;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                package_is_radial = FALSE;
                number_of_columns = 2;
                number_of_rows = 24;
                pitch_x = 600;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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
                number_of_rows = 25;
                pitch_x = 900;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
                pad_shape = g_strdup ("circular pad");
                pin_drill_diameter = 28;
                pad_diameter = 60;
                pad_clearance = 15;
                pad_solder_mask_clearance = 6;
                g_free (footprint_name);
                footprint_name = g_strdup ("DIP50900");
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
                number_of_rows = 32;
                pitch_x = 900;
                pitch_y = 100;
                count_x = 0;
                count_y = 0;
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

/* EOF */
