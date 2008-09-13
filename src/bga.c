/*!
 * \file bga.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Predefined values for BGA footprints.
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
 * \brief Look up default values for BGA footprints.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised the known values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * BGA100C100P10X10_1100X1100X140, BGA100C100P10X10_1100X1100X170,
 * BGA100C100P10X10_1100X1100X350, BGA100C50P11X11_600X600X100,
 * BGA100C50P14X14_800X800X120, BGA100C50P15X15_1000X1000X120,
 * BGA100C65P10X10_800X800X140, BGA100C80P10X10_1000X1000X140,
 * BGA100C80P10X10_1000X1000X150, BGA100C80P10X10_900X900X100,
 * BGA100C80P10X10_900X900X150, BGA100C80P11X11_1100X1100X140,
 * BGA1020C100P32X32_3300X3300X350, BGA1023C100P32X32_3300X3300X350,
 * BGA1024C100P32X32_3300X3300X350, BGA103C65P8X13_600X900X100,
 * BGA1056C100P39X39_4000X4000X380, BGA1056C100P39X39_4000X4000X400,
 * BGA105C50P15X15_800X800X140, BGA107C80P10X14_1050X1300X120,
 * BGA107C80P10X14_1050X1300X140, BGA107C80P10X14_1050X1600X140,
 * BGA1089C100P33X33_3500X3500X350, BGA1089C127P33X33_4250X4250X350,
 * BGA109C50P12X12_700X700X100, BGA10C50P3X4_220X250X60,
 * BGA10N50P3X4_200X250X94, BGA111C80P12X13_1000X1100X140,
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
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
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
                silkscreen_length = 11.00;
                silkscreen_width = 11.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C100P10X10_1100X1100X170");
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
        else if (!strcmp (footprint_name, "?BGA100C50P11X11_600X600X100"))
        {
                footprint_units = g_strdup ("mm");
                number_of_pins = 100;
                pin_pad_exceptions_string = g_strconcat
                (
                        "A1,A6,A11,",
                        "D5,D6,D7,",
                        "E4,E8,",
                        "F1,F4,F8,F11,",
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
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 7.00;
                courtyard_width = 7.00;
                silkscreen_length = 6.10;
                silkscreen_width = 6.10;
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
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 9.00;
                courtyard_width = 9.00;
                silkscreen_length = 8.00;
                silkscreen_width = 8.00;
                g_free (footprint_name);
                footprint_name = g_strdup ("BGA100C50P14X14_800X800X120");
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
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 11.00;
                courtyard_width = 11.00;
                silkscreen_length = 10.00;
                silkscreen_width = 10.00;
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
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 10.00;
                courtyard_width = 10.00;
                silkscreen_length = 8.00;
                silkscreen_width = 8.00;
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
                pad_diameter = 0.40;
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 12.00;
                silkscreen_length = 10.00;
                silkscreen_width = 10.00;
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
                pad_clearance = 0.15;
                pad_solder_mask_clearance = 0.15;
                fiducial = TRUE;
                fiducial_pad_diameter = 1.00;
                fiducial_pad_solder_mask_clearance = 1.00;
                courtyard_length = 12.00;
                courtyard_width = 12.00;
                silkscreen_length = 10.00;
                silkscreen_width = 10.00;
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
        else
        {
                fprintf (stderr,
                         _("WARNING: default values for footprint %s not found.\n"),
                         footprint_name);
                return (EXIT_FAILURE);
        }
}


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


/* EOF */
