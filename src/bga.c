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
 * If the footprint name is recognised the values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * BGA100C100P10X10_1100X1100X140, BGA100C100P10X10_1100X1100X170,
 * BGA100C100P10X10_1100X1100X350, BGA100C50P11X11_600X600X100,
 * BGA100C50P14X14_800X800X120,
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
                pin_pad_exception_string = g_strconcat
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
                pin_pad_exception_string = g_strconcat
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
        GtkToggleButton *fiducial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "fiducial_checkbutton");
        gtk_toggle_button_set_active (fiducial_checkbutton, FALSE);
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
