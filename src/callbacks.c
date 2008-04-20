/*!
 * \file callbacks.c
 * \author Copyright (C) 2007, 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Callback functions for the pcb footprintwizard (pcb-gfpw).
 *
 * pcb-gfpw (GtkFootPrintWizard) is a program for the creation of footprint
 * files to be used by the pcb layout application
 * (see http://pcb.sourgeforge.net) for the placement of parts in a pcb
 * layout.\n
 */


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "libfpw.c"


gboolean main_window_title_has_asterisk = FALSE;
        /*!< Keep track whether the main window title has an asterisk between
         * brackets or not. */
gboolean fpw_file_saved = FALSE;
        /*!< Keep track whether the FootPrintWizard file is saved, and thus
         * has a valid filename. */
gchar *temp_dir = NULL;
        /*! Temporary directory from the GUI filechooser. */
gchar *work_dir = NULL;
        /*! Working directory. */


/*!
 * \brief Set all entries widgets to default sensitivity.
 */
int
all_entries_to_default_sensitivity (GtkWidget *widget)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *footprint_type_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_type_entry");
        gtk_widget_set_sensitive (footprint_type_entry, TRUE);
        GtkWidget *footprint_name_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_name_entry");
        gtk_widget_set_sensitive (footprint_name_entry, TRUE);
        GtkWidget *footprint_units_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_units_entry");
        gtk_widget_set_sensitive (footprint_units_entry, TRUE);
        GtkWidget *footprint_refdes_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_refdes_entry");
        gtk_widget_set_sensitive (footprint_refdes_entry, TRUE);
        GtkWidget *footprint_value_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_value_entry");
        gtk_widget_set_sensitive (footprint_value_entry, TRUE);
        GtkWidget *package_body_length_entry = lookup_widget (GTK_WIDGET (widget),
                "package_body_length_entry");
        gtk_widget_set_sensitive (package_body_length_entry, TRUE);
        GtkWidget *package_body_width_entry = lookup_widget (GTK_WIDGET (widget),
                "package_body_width_entry");
        gtk_widget_set_sensitive (package_body_width_entry, TRUE);
        GtkWidget *package_body_height_entry = lookup_widget (GTK_WIDGET (widget),
                "package_body_height_entry");
        gtk_widget_set_sensitive (package_body_height_entry, TRUE);
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (package_is_radial_checkbutton, FALSE);
        GtkWidget *footprint_author_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_author_entry");
        gtk_widget_set_sensitive (footprint_author_entry, TRUE);
        GtkWidget *footprint_dist_license_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_dist_license_entry");
        gtk_widget_set_sensitive (footprint_dist_license_entry, TRUE);
        GtkWidget *footprint_use_license_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_use_license_entry");
        gtk_widget_set_sensitive (footprint_use_license_entry, TRUE);
        GtkWidget *footprint_status_entry = lookup_widget (GTK_WIDGET (widget),
                "footprint_status_entry");
        gtk_widget_set_sensitive (footprint_status_entry, TRUE);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (widget),
                "number_total_pins_entry");
        gtk_widget_set_sensitive (number_total_pins_entry, FALSE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_widget_set_sensitive (number_of_rows_entry, TRUE);
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_widget_set_sensitive (number_of_columns_entry, TRUE);
        GtkWidget *pitch_x_entry = lookup_widget (GTK_WIDGET (widget),
                "pitch_x_entry");
        gtk_widget_set_sensitive (pitch_x_entry, TRUE);
        GtkWidget *pitch_y_entry = lookup_widget (GTK_WIDGET (widget),
                "pitch_y_entry");
        gtk_widget_set_sensitive (pitch_y_entry, TRUE);
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                "count_x_entry");
        gtk_widget_set_sensitive (count_x_entry, TRUE);
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (widget),
                "count_y_entry");
        gtk_widget_set_sensitive (count_y_entry, TRUE);
        GtkWidget *pad_shape_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_shape_entry");
        gtk_widget_set_sensitive (pad_shape_entry, TRUE);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_widget_set_sensitive (number_1_position_entry, TRUE);
        GtkWidget *pad_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_diameter_entry");
        gtk_widget_set_sensitive (pad_diameter_entry, TRUE);
        GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pin_drill_diameter_entry");
        gtk_widget_set_sensitive (pin_drill_diameter_entry, TRUE);
        GtkWidget *pin1_square_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "pin_square_checkbutton");
        gtk_widget_set_sensitive (pin1_square_checkbutton, TRUE);
        GtkWidget *pad_length_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_length_entry");
        gtk_widget_set_sensitive (pad_length_entry, TRUE);
        GtkWidget *pad_width_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_width_entry");
        gtk_widget_set_sensitive (pad_width_entry, TRUE);
        GtkWidget *pad_clearance_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_clearance_entry");
        gtk_widget_set_sensitive (pad_clearance_entry, TRUE);
        GtkWidget *pad_solder_mask_clearance_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_solder_mask_clearance_entry");
        gtk_widget_set_sensitive (pad_solder_mask_clearance_entry, TRUE);

        /* Widgets on tab 3 "Thermal pad" */
        GtkWidget *thermal_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "thermal_checkbutton");
        gtk_toggle_button_set_active (thermal_checkbutton, FALSE);
        GtkWidget *thermal_nopaste_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "thermal_nopaste_checkbutton");
        gtk_toggle_button_set_active (thermal_nopaste_checkbutton, FALSE);
        GtkWidget *thermal_length_entry = lookup_widget (GTK_WIDGET (widget),
                "thermal_length_entry");
        gtk_widget_set_sensitive (thermal_length_entry, FALSE);
        GtkWidget *thermal_width_entry = lookup_widget (GTK_WIDGET (widget),
                "thermal_width_entry");
        gtk_widget_set_sensitive (thermal_width_entry, FALSE);
        GtkWidget *thermal_clearance_entry = lookup_widget (GTK_WIDGET (widget),
                "thermal_clearance_entry");
        gtk_widget_set_sensitive (thermal_clearance_entry, FALSE);
        GtkWidget *thermal_solder_mask_clearance_entry = lookup_widget (GTK_WIDGET (widget),
                "thermal_solder_mask_clearance_entry");
        gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, FALSE);

        /* Widgets on tab 4 "Silkscreen" */
        GtkWidget *silkscreen_package_outline_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "silkscreen_package_outline_checkbutton");
        gtk_toggle_button_set_active (silkscreen_package_outline_checkbutton, FALSE);
        GtkWidget *silkscreen_line_width_entry = lookup_widget (GTK_WIDGET (widget),
                "silkscreen_line_width_entry");
        gtk_widget_set_sensitive (silkscreen_line_width_entry, FALSE);
        GtkWidget *silkscreen_indicate_1_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "silkscreen_indicate_1_checkbutton");
        gtk_toggle_button_set_active (silkscreen_indicate_1_checkbutton, FALSE);
        GtkWidget *courtyard_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "courtyard_checkbutton");
        gtk_toggle_button_set_active (courtyard_checkbutton, FALSE);
        GtkWidget *courtyard_length_entry = lookup_widget (GTK_WIDGET (widget),
                "courtyard_length_entry");
        gtk_widget_set_sensitive (courtyard_length_entry, FALSE);
        GtkWidget *courtyard_width_entry = lookup_widget (GTK_WIDGET (widget),
                "courtyard_width_entry");
        gtk_widget_set_sensitive (courtyard_width_entry, FALSE);
        GtkWidget *courtyard_line_width_entry = lookup_widget (GTK_WIDGET (widget),
                "courtyard_line_width_entry");
        gtk_widget_set_sensitive (courtyard_line_width_entry, FALSE);
        GtkWidget *courtyard_clearance_with_package_entry = lookup_widget (GTK_WIDGET (widget),
                "courtyard_clearance_with_package_entry");
        gtk_widget_set_sensitive (courtyard_clearance_with_package_entry, FALSE);

        /* Widgets on tab 5 "Heel & Toe goals" */
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (widget),
                "C1_entry");
        gtk_widget_set_sensitive (C1_entry, TRUE);
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (widget),
                "C2_entry");
        gtk_widget_set_sensitive (C2_entry, TRUE);
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (widget),
                "G1_entry");
        gtk_widget_set_sensitive (G1_entry, FALSE);
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (widget),
                "G2_entry");
        gtk_widget_set_sensitive (G2_entry, FALSE);
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (widget),
                "Z1_entry");
        gtk_widget_set_sensitive (Z1_entry, FALSE);
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (widget),
                "Z2_entry");
        gtk_widget_set_sensitive (Z2_entry, FALSE);
        GtkWidget *C1_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "C1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C1_radiobutton), TRUE);
        gtk_widget_set_sensitive (C1_radiobutton, TRUE);
        GtkWidget *C2_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "C2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C2_radiobutton), TRUE);
        gtk_widget_set_sensitive (C2_radiobutton, TRUE);
        GtkWidget *G1_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "G1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (G1_radiobutton), FALSE);
        gtk_widget_set_sensitive (G1_radiobutton, TRUE);
        GtkWidget *G2_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "G2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (G2_radiobutton), FALSE);
        gtk_widget_set_sensitive (G2_radiobutton, TRUE);
        GtkWidget *Z1_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "Z1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (Z1_radiobutton), FALSE);
        gtk_widget_set_sensitive (Z1_radiobutton, TRUE);
        GtkWidget *Z2_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "Z2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (Z2_radiobutton), FALSE);
        gtk_widget_set_sensitive (Z2_radiobutton, TRUE);
}

/*!
 * \brief Change the main window title.
 */
int
change_main_window_title (GtkWidget *widget, gchar *main_window_title)
{
        /* lookup the window */
        GtkWidget *main_window;
        main_window = lookup_widget (GTK_WIDGET (widget), "pcb_gfpw");
        gtk_window_set_title (main_window, main_window_title);
}


/*!
 * \brief The value in one of the entries in the GUI has changed.
 *
 * - add an asterix between brackets [*] before the current window title.
 */
int
entry_has_changed (GtkWidget *widget)
{
        if (!main_window_title_has_asterisk)
        {
                /* lookup the window */
                GtkWidget *main_window;
                main_window = lookup_widget (GTK_WIDGET (widget), "pcb_gfpw");
                /* get the current title */
                gchar *main_window_title = NULL;
                main_window_title = gtk_window_get_title (main_window);
                if (!fpw_file_saved)
                {
                        /* fpw file has not been saved before */
                        change_main_window_title (main_window,
                                g_strconcat ("pcb-gfpw : Unsaved fpw file",
                                NULL));
                }
                else
                {
                        /* fpw file has been saved before, assume the fpw
                         * filename is already listed in the main window
                         * title, add an asterix between brackets [*] before
                         * the current window title */
                        change_main_window_title (main_window,
                                g_strconcat ("[*] ",
                                main_window_title, NULL));
                        main_window_title_has_asterisk = TRUE;
                }
        }
}


/*!
 * \brief Set GUI constraints: disable the entries in the
 * "Heel and Toe goals" tab.
 */
int
gui_constraints_disable_heel_and_toe_goals_tab_widgets (GtkWidget *widget)
{
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (widget),
                "C1_entry");
        gtk_entry_set_text (GTK_WIDGET (C1_entry), "");
        gtk_widget_set_sensitive (C1_entry, FALSE);
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (widget),
                "C2_entry");
        gtk_entry_set_text (GTK_WIDGET (C2_entry), "");
        gtk_widget_set_sensitive (C2_entry, FALSE);
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (widget),
                "G1_entry");
        gtk_entry_set_text (GTK_WIDGET (G1_entry), "");
        gtk_widget_set_sensitive (G1_entry, FALSE);
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (widget),
                "G2_entry");
        gtk_entry_set_text (GTK_WIDGET (G2_entry), "");
        gtk_widget_set_sensitive (G2_entry, FALSE);
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (widget),
                "Z1_entry");
        gtk_entry_set_text (GTK_WIDGET (Z1_entry), "");
        gtk_widget_set_sensitive (Z1_entry, FALSE);
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (widget),
                "Z2_entry");
        gtk_entry_set_text (GTK_WIDGET (Z2_entry), "");
        gtk_widget_set_sensitive (Z2_entry, FALSE);
        GtkWidget * C1_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "C1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C1_radiobutton), TRUE);
        gtk_widget_set_sensitive (C1_radiobutton, FALSE);
        GtkWidget * C2_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "C2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C2_radiobutton), TRUE);
        gtk_widget_set_sensitive (C2_radiobutton, FALSE);
        GtkWidget * G1_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "G1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (G1_radiobutton), FALSE);
        gtk_widget_set_sensitive (G1_radiobutton, FALSE);
        GtkWidget * G2_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "G2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (G2_radiobutton), FALSE);
        gtk_widget_set_sensitive (G2_radiobutton, FALSE);
        GtkWidget * Z1_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "Z1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (Z1_radiobutton), FALSE);
        gtk_widget_set_sensitive (Z1_radiobutton, FALSE);
        GtkWidget * Z2_radiobutton = lookup_widget (GTK_WIDGET (widget),
                "Z2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (Z2_radiobutton), FALSE);
        gtk_widget_set_sensitive (Z2_radiobutton, FALSE);
}


/*!
 * \brief Set GUI constraints: disable the entries in the
 * "Thermal Pad" tab.
 */
int
gui_constraints_disable_thermal_tab_widgets (GtkWidget *widget)
{
        GtkWidget *thermal_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "thermal_checkbutton");
        gtk_toggle_button_set_active (thermal_checkbutton, FALSE);
        gtk_widget_set_sensitive (thermal_checkbutton, FALSE);
}


/*!
 * \brief Set GUI constraints for the BGA package type.
 */
int
gui_constraints_set_bga (GtkWidget *widget)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (package_is_radial_checkbutton, FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                "count_x_entry");
        gtk_entry_set_text (GTK_WIDGET (count_x_entry), "");
        gtk_widget_set_sensitive (count_x_entry, FALSE);
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (widget),
                "count_y_entry");
        gtk_entry_set_text (GTK_WIDGET (count_y_entry), "");
        gtk_widget_set_sensitive (count_y_entry, FALSE);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_WIDGET (number_1_position_entry), 1);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);
        GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pin_drill_diameter_entry");
        gtk_entry_set_text (GTK_WIDGET (pin_drill_diameter_entry), "");
        gtk_widget_set_sensitive (pin_drill_diameter_entry, FALSE);
        GtkWidget *pad_shape_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_shape_entry");
        gtk_combo_box_set_active (GTK_WIDGET (pad_shape_entry), 1);
        gtk_widget_set_sensitive (pad_shape_entry, FALSE);
        GtkWidget *pad_length_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_length_entry");
        gtk_entry_set_text (GTK_WIDGET (pad_length_entry), "");
        gtk_widget_set_sensitive (pad_length_entry, FALSE);
        GtkWidget *pad_width_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_width_entry");
        gtk_entry_set_text (GTK_WIDGET (pad_width_entry), "");
        gtk_widget_set_sensitive (pad_width_entry, FALSE);

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}


/*!
 * \brief Set GUI constraints for the DIP package type.
 */
int
gui_constraints_set_dip (GtkWidget *widget)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (package_is_radial_checkbutton, FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_WIDGET (number_of_columns_entry), "2");
        gtk_widget_set_sensitive (number_of_columns_entry, FALSE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_WIDGET (number_of_rows_entry), "");
        gtk_widget_set_sensitive (number_of_rows_entry, FALSE);
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                "count_x_entry");
        gtk_entry_set_text (GTK_WIDGET (count_x_entry), "");
        gtk_widget_set_sensitive (count_x_entry, FALSE);
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (widget),
                "count_y_entry");
        gtk_entry_set_text (GTK_WIDGET (count_y_entry), "");
        gtk_widget_set_sensitive (count_y_entry, TRUE);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_WIDGET (number_1_position_entry), 1);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}


/*!
 * \brief Set GUI constraints for the PGA package type.
 */
int
gui_constraints_set_pga (GtkWidget *widget)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (package_is_radial_checkbutton, FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                "count_x_entry");
        gtk_entry_set_text (GTK_WIDGET (count_x_entry), "");
        gtk_widget_set_sensitive (count_x_entry, FALSE);
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (widget),
                "count_y_entry");
        gtk_entry_set_text (GTK_WIDGET (count_y_entry), "");
        gtk_widget_set_sensitive (count_y_entry, FALSE);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_WIDGET (number_1_position_entry), 1);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);
        GtkWidget *pad_shape_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_shape_entry");
        gtk_combo_box_set_active (GTK_WIDGET (pad_shape_entry), 1);
        gtk_widget_set_sensitive (pad_shape_entry, FALSE);
        GtkWidget *pad_length_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_length_entry");
        gtk_entry_set_text (GTK_WIDGET (pad_length_entry), "");
        gtk_widget_set_sensitive (pad_length_entry, FALSE);
        GtkWidget *pad_width_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_width_entry");
        gtk_entry_set_text (GTK_WIDGET (pad_width_entry), "");
        gtk_widget_set_sensitive (pad_width_entry, FALSE);

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}


/*!
 * \brief Set GUI constraints for the PLCC package type.
 */
int
gui_constraints_set_plcc (GtkWidget *widget)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (package_is_radial_checkbutton, FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_WIDGET (number_1_position_entry), 4);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);
        GtkWidget *pad_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_diameter_entry");
        gtk_entry_set_text (GTK_WIDGET (pad_diameter_entry), "");
        gtk_widget_set_sensitive (pad_diameter_entry, FALSE);
        GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pin_drill_diameter_entry");
        gtk_entry_set_text (GTK_WIDGET (pin_drill_diameter_entry), "");
        gtk_widget_set_sensitive (pin_drill_diameter_entry, FALSE);
        GtkWidget *pad_shape_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_shape_entry");
        gtk_combo_box_set_active (GTK_WIDGET (pad_shape_entry), 2);

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);
}


/*!
 * \brief Set GUI constraints for SMT package types.
 *
 * The following types are applicable:
 * CAPC, CAPM, CAPMP, DIOM, DIOMELF, INDC, INDM, INDP, RESC, RESM and RESMELF.
 */
int
gui_constraints_set_smt (GtkWidget *widget)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (package_is_radial_checkbutton, FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_WIDGET (number_of_columns_entry), "");
        gtk_widget_set_sensitive (number_of_columns_entry, FALSE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_WIDGET (number_of_rows_entry), "");
        gtk_widget_set_sensitive (number_of_rows_entry, FALSE);
        GtkWidget *pitch_y_entry = lookup_widget (GTK_WIDGET (widget),
                "pitch_y_entry");
        gtk_entry_set_text (GTK_WIDGET (pitch_y_entry), "");
        gtk_widget_set_sensitive (pitch_y_entry, FALSE);
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                "count_x_entry");
        gtk_entry_set_text (GTK_WIDGET (count_x_entry), "");
        gtk_widget_set_sensitive (count_x_entry, FALSE);
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (widget),
                "count_y_entry");
        gtk_entry_set_text (GTK_WIDGET (count_y_entry), "");
        gtk_widget_set_sensitive (count_y_entry, FALSE);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_WIDGET (number_1_position_entry), 1);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);
        GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_WIDGET (widget),
                "pin_drill_diameter_entry");
        gtk_entry_set_text (GTK_WIDGET (pin_drill_diameter_entry), "");
        gtk_widget_set_sensitive (pin_drill_diameter_entry, FALSE);
        GtkWidget *pad_shape_entry = lookup_widget (GTK_WIDGET (widget),
                "pad_shape_entry");
        gtk_combo_box_set_active (GTK_WIDGET (pad_shape_entry), 2);

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}


/*!
 * \brief Set GUI constraints for the TO92 package type.
 */
int
gui_constraints_set_to92 (GtkWidget *widget)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (package_is_radial_checkbutton, TRUE);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_WIDGET (number_of_columns_entry), "");
        gtk_widget_set_sensitive (number_of_columns_entry, FALSE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_WIDGET (number_of_rows_entry), "");
        gtk_widget_set_sensitive (number_of_rows_entry, FALSE);
        GtkWidget *pitch_x_entry = lookup_widget (GTK_WIDGET (widget),
                "pitch_x_entry");
        gtk_entry_set_text (GTK_WIDGET (pitch_x_entry), "");
        gtk_widget_set_sensitive (pitch_x_entry, FALSE);
        GtkWidget *pitch_y_entry = lookup_widget (GTK_WIDGET (widget),
                "pitch_y_entry");
        gtk_entry_set_text (GTK_WIDGET (pitch_y_entry), "");
        gtk_widget_set_sensitive (pitch_y_entry, FALSE);
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                "count_x_entry");
        gtk_entry_set_text (GTK_WIDGET (count_x_entry), "");
        gtk_widget_set_sensitive (count_x_entry, FALSE);
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (widget),
                "count_y_entry");
        gtk_entry_set_text (GTK_WIDGET (count_y_entry), "");
        gtk_widget_set_sensitive (count_y_entry, FALSE);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_WIDGET (number_1_position_entry), 1);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);

        /* Widgets on tab 3 "Thermal Pad" */
        gui_constraints_disable_thermal_tab_widgets (widget);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
}


/*!
 * \brief Send a message to the statusbar.
 */
int
message_to_statusbar (GtkWidget *widget, gchar *message)
{
        /* lookup the statusbar */
        GtkStatusbar *statusbar;
        guint context_id;
        guint message_id;
        statusbar = lookup_widget (GTK_WIDGET (widget), "statusbar");
        context_id = gtk_statusbar_get_context_id (statusbar, message);
        message_id = gtk_statusbar_push (statusbar, context_id, message);
}


/*!
 * \brief Update the value in the "number_total_pins" entry.
 *
 * This function is to be called on one of the following events:
 * <ul>
 * <li>Number of columns entry is changed: \c number_of_columns changes.
 * <li>Number of rows entry is changed: \c number_of_rows changes.
 * <li>Count of pin/pads (on a row) in the X-direction entry is changed: \c count_x changes.
 * <li>Count of pin/pads (on a column) in the Y-direction entry is changed: \c count_y changes.
 * <li>The thermal pad button is toggled: \c thermal changes.
 * </ul>
 */
int
number_of_pins_has_changed (GtkWidget *widget)
{
        /* Recalculate the total number of pins/pads depending on the package
         * type */
        switch (package_type)
        {
                case BGA :
                        number_of_pins = number_of_columns * number_of_rows;
                        break;
                case CAPC :
                        number_of_pins = 2;
                        break;
                case CAPM :
                        number_of_pins = 2;
                        break;
                case CAPMP :
                        number_of_pins = 2;
                        break;
                case DIL :
                        number_of_pins = number_of_columns * number_of_rows;
                        break;
                case DIOM :
                        number_of_pins = 2;
                        break;
                case DIOMELF :
                        number_of_pins = 2;
                        break;
                case DIP :
                        number_of_pins = number_of_columns * count_y;
                        break;
                case INDC :
                        number_of_pins = 2;
                        break;
                case INDM :
                        number_of_pins = 2;
                        break;
                case INDP :
                        number_of_pins = 2;
                        break;
                case PGA :
                        number_of_pins = number_of_columns * number_of_rows;
                        break;
                case PLCC :
                        number_of_pins = (number_of_columns * count_x +
                                number_of_rows * count_y) + thermal;
                        break;
                case QFN :
                        number_of_pins = (number_of_columns * count_x +
                                number_of_rows * count_y) + thermal;
                        break;
                case QFP :
                        number_of_pins = (number_of_columns * count_x +
                                number_of_rows * count_y) + thermal;
                        break;
                case RESC :
                        number_of_pins = 2;
                        break;
                case RESM :
                        number_of_pins = 2;
                        break;
                case RESMELF :
                        number_of_pins = 2;
                        break;
                case SIL :
                        number_of_pins = count_x;
                        break;
                case SIP :
                        number_of_pins = count_x;
                        break;
                case SO :
                        break;
                case TO92 :
                        number_of_pins = 3;
                        break;
                default :
                        break;
        }
        /* Update the "total number of pins/pads" entry */
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (widget),
                "number_total_pins_entry");
        gtk_entry_set_text (GTK_WIDGET (number_total_pins_entry),
                g_strdup_printf ("%d", number_of_pins));
}


/*!
 * \brief The "top to bottom pads/pins center-center distance (C1)" entry is
 * changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c c1 variable (global).
 */
void
on_C1_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *C1_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        c1 = g_ascii_strtod (C1_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "top to bottom pads/pins center-center distance (C1)"
 * radiobutton is clicked.
 *
 * - set the "center-center distance (C1)" entry to sensitive.
 * - set the "inner-inner distance (G1)" entry to insensitive.
 * - set the "outer-outer distance (Z1)" entry to insensitive.
 */
void
on_C1_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        c1_state = gtk_toggle_button_get_active (togglebutton);
        g1_state = !c1_state;
        z1_state = !c1_state;
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (togglebutton), "C1_entry");
        gtk_widget_set_sensitive (C1_entry, TRUE);
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (togglebutton), "G1_entry");
        gtk_widget_set_sensitive (G1_entry, FALSE);
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z1_entry");
        gtk_widget_set_sensitive (Z1_entry, FALSE);
}


/*!
 * \brief The "left to right pads/pins center-center distance (C2)" entry is
 * changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c c2 variable (global).
 */
void
on_C2_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *C2_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        c2 = g_ascii_strtod (C2_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "left to right pads/pins center-center distance (C2)"
 * radiobutton is clicked.
 *
 * - set the "center-center distance (C2)" entry to sensitive.
 * - set the "inner-inner distance (G2)" entry to insensitive.
 * - set the "outer-outer distance (Z2)" entry to insensitive.
 */
void
on_C2_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        c2_state = gtk_toggle_button_get_active (togglebutton);
        g2_state = !c2_state;
        z2_state = !c2_state;
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (togglebutton), "C2_entry");
        gtk_widget_set_sensitive (C2_entry, TRUE);
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (togglebutton), "G2_entry");
        gtk_widget_set_sensitive (G2_entry, FALSE);
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z2_entry");
        gtk_widget_set_sensitive (Z2_entry, FALSE);
}


/*!
 * \brief The top to bottom pads/pins inner-inner distance (G1) entry is
 * changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c g1 variable (global).
 */
void
on_G1_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *G1_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        g1 = g_ascii_strtod (G1_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The top to bottom pads/pins inner-inner distance (G1) radiobutton
 * is clicked.
 *
 * - set the inner-inner (G1) entry to sensitive.
 * - set the center-center (C1) entry to insensitive.
 * - set the outer-outer (Z1) entry to insensitive.
 */
void
on_G1_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        g1_state = gtk_toggle_button_get_active (togglebutton);
        c1_state = !g1_state;
        z1_state = !g1_state;
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (togglebutton), "C1_entry");
        gtk_widget_set_sensitive (C1_entry, FALSE);
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (togglebutton), "G1_entry");
        gtk_widget_set_sensitive (G1_entry, TRUE);
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z1_entry");
        gtk_widget_set_sensitive (Z1_entry, FALSE);
}


/*!
 * \brief The left to right pads/pins inner-inner distance (G2) entry is
 * changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c g2 variable (global).
 */
void
on_G2_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *G2_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        g2 = g_ascii_strtod (G2_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The left to right pads/pins inner-inner distance (G2) radiobutton
 * is clicked.
 *
 * - set the inner-inner (G2) entry to sensitive.
 * - set the center-centr (C2) entry to insensitive.
 * - set the outer-outer (Z2) entry to insensitive.
 */
void
on_G2_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        g2_state = gtk_toggle_button_get_active (togglebutton);
        c2_state = !g2_state;
        z2_state = !g2_state;
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (togglebutton), "C2_entry");
        gtk_widget_set_sensitive (C2_entry, FALSE);
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (togglebutton), "G2_entry");
        gtk_widget_set_sensitive (G2_entry, TRUE);
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z2_entry");
        gtk_widget_set_sensitive (Z2_entry, FALSE);
}


/*!
 * \brief The top to bottom pads/pins outer-outer distance (Z1) entry is
 * changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c z1 variable (global).
 */
void
on_Z1_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *Z1_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        z1 = g_ascii_strtod (Z1_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The top to bottom pads/pins outer-outer (Z1) radiobutton
 * is clicked.
 *
 * - set the outer-outer (Z1) entry to sensitive.
 * - set the center-center (C1) entry to insensitive.
 * - set the inner-inner (G1) entry to insensitive.
 */
void
on_Z1_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        z1_state = gtk_toggle_button_get_active (togglebutton);
        c1_state = !z1_state;
        g1_state = !z1_state;
        GtkWidget *C1_entry = lookup_widget (GTK_WIDGET (togglebutton), "C1_entry");
        gtk_widget_set_sensitive (C1_entry, FALSE);
        GtkWidget *G1_entry = lookup_widget (GTK_WIDGET (togglebutton), "G1_entry");
        gtk_widget_set_sensitive (G1_entry, FALSE);
        GtkWidget *Z1_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z1_entry");
        gtk_widget_set_sensitive (Z1_entry, TRUE);
}


/*!
 * \brief The left to right pads/pins outer-outer distance (Z2) entry is
 * changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c z2 variable (global).
 */
void
on_Z2_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *Z2_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        z2 = g_ascii_strtod (Z2_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The left to right pads/pins outer-outer (Z2) radiobutton
 * is clicked.
 *
 * - set the "outer-outer distance (Z2)" entry to sensitive.
 * - set the "center-center distance (C2)" entry to insensitive.
 * - set the "inner-inner distance (G2)" entry to insensitive.
 */
void
on_Z2_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        z2_state = gtk_toggle_button_get_active (togglebutton);
        c2_state = !z2_state;
        g2_state = !z2_state;
        GtkWidget *C2_entry = lookup_widget (GTK_WIDGET (togglebutton), "C2_entry");
        gtk_widget_set_sensitive (C2_entry, FALSE);
        GtkWidget *G2_entry = lookup_widget (GTK_WIDGET (togglebutton), "G2_entry");
        gtk_widget_set_sensitive (G2_entry, FALSE);
        GtkWidget *Z2_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z2_entry");
        gtk_widget_set_sensitive (Z2_entry, TRUE);
}


/*!
 * \brief The "Clear" button is clicked.
 *
 * - clear all entries or set entries which have a default values to that
 *   value,
 * - set all togglebuttons to the initial state.
 *
 * \todo Combobox entries to be stripped of characters with something like
 * gtk_combo_box_remove_text ().
 *
 */
void
on_clear_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
        entry_has_changed (button);
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *footprint_type_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_type_entry");
        gtk_combo_box_set_active (GTK_WIDGET (footprint_type_entry), 0);
        GtkWidget *footprint_name_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_name_entry");
        gtk_entry_set_text (GTK_WIDGET (footprint_name_entry), "");
        GtkWidget *footprint_units_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_units_entry");
        gtk_combo_box_set_active (GTK_WIDGET (footprint_units_entry), 0);
        GtkWidget *footprint_refdes_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_refdes_entry");
        gtk_entry_set_text (GTK_WIDGET (footprint_refdes_entry), "");
        GtkWidget *footprint_value_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_value_entry");
        gtk_entry_set_text (GTK_WIDGET (footprint_value_entry), "");
        GtkWidget *package_body_length_entry = lookup_widget (GTK_BUTTON (button),
                "package_body_length_entry");
        gtk_entry_set_text (GTK_WIDGET (package_body_length_entry), "");
        GtkWidget *package_body_width_entry = lookup_widget (GTK_BUTTON (button),
                "package_body_width_entry");
        gtk_entry_set_text (GTK_WIDGET (package_body_width_entry), "");
        GtkWidget *package_body_height_entry = lookup_widget (GTK_BUTTON (button),
                "package_body_height_entry");
        gtk_entry_set_text (GTK_WIDGET (package_body_height_entry), "");
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_BUTTON (button),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (package_is_radial_checkbutton, FALSE);
        GtkWidget *footprint_author_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_author_entry");
        gtk_entry_set_text (GTK_WIDGET (footprint_author_entry), "");
        GtkWidget *footprint_dist_license_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_dist_license_entry");
        gtk_entry_set_text (GTK_WIDGET (footprint_dist_license_entry), "");
        GtkWidget *footprint_use_license_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_use_license_entry");
        gtk_entry_set_text (GTK_WIDGET (footprint_use_license_entry), "");
        GtkWidget *footprint_status_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_status_entry");
        gtk_combo_box_set_active (GTK_WIDGET (footprint_status_entry), 0);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_BUTTON (button),
                "number_total_pins_entry");
        gtk_entry_set_text (GTK_WIDGET (number_total_pins_entry), "");
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_BUTTON (button),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_WIDGET (number_of_rows_entry), "");
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_BUTTON (button),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_WIDGET (number_of_columns_entry), "");
        GtkWidget *pitch_x_entry = lookup_widget (GTK_BUTTON (button),
                "pitch_x_entry");
        gtk_entry_set_text (GTK_WIDGET (pitch_x_entry), "");
        GtkWidget *pitch_y_entry = lookup_widget (GTK_BUTTON (button),
                "pitch_y_entry");
        gtk_entry_set_text (GTK_WIDGET (pitch_y_entry), "");
        GtkWidget *count_x_entry = lookup_widget (GTK_BUTTON (button),
                "count_x_entry");
        gtk_entry_set_text (GTK_WIDGET (count_x_entry), "");
        GtkWidget *count_y_entry = lookup_widget (GTK_BUTTON (button),
                "count_y_entry");
        gtk_entry_set_text (GTK_WIDGET (count_y_entry), "");
        GtkWidget *pad_shape_entry = lookup_widget (GTK_BUTTON (button),
                "pad_shape_entry");
        gtk_combo_box_set_active (GTK_WIDGET (pad_shape_entry), 0);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_BUTTON (button),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_WIDGET (number_1_position_entry), 0);
        GtkWidget *pad_diameter_entry = lookup_widget (GTK_BUTTON (button),
                "pad_diameter_entry");
        gtk_entry_set_text (GTK_WIDGET (pad_diameter_entry), "");
        GtkWidget *pin_drill_diameter_entry = lookup_widget (GTK_BUTTON (button),
                "pin_drill_diameter_entry");
        gtk_entry_set_text (GTK_WIDGET (pin_drill_diameter_entry), "");
        GtkWidget *pin1_square_checkbutton = lookup_widget (GTK_BUTTON (button),
                "pin_square_checkbutton");
        gtk_toggle_button_set_active (pin1_square_checkbutton, FALSE);
        GtkWidget *pad_length_entry = lookup_widget (GTK_BUTTON (button),
                "pad_length_entry");
        gtk_entry_set_text (GTK_WIDGET (pad_length_entry), "");
        GtkWidget *pad_width_entry = lookup_widget (GTK_BUTTON (button),
                "pad_width_entry");
        gtk_entry_set_text (GTK_WIDGET (pad_width_entry), "");
        GtkWidget *pad_clearance_entry = lookup_widget (GTK_BUTTON (button),
                "pad_clearance_entry");
        gtk_entry_set_text (GTK_WIDGET (pad_clearance_entry), "");
        GtkWidget *pad_solder_mask_clearance_entry = lookup_widget (GTK_BUTTON (button),
                "pad_solder_mask_clearance_entry");
        gtk_entry_set_text (GTK_WIDGET (pad_solder_mask_clearance_entry), "");

        /* Widgets on tab 3 "Thermal Pad" */
        GtkWidget *thermal_checkbutton = lookup_widget (GTK_BUTTON (button),
                "thermal_checkbutton");
        gtk_toggle_button_set_active (thermal_checkbutton, FALSE);
        GtkWidget *thermal_nopaste_checkbutton = lookup_widget (GTK_BUTTON (button),
                "thermal_nopaste_checkbutton");
        gtk_toggle_button_set_active (thermal_nopaste_checkbutton, FALSE);
        GtkWidget *thermal_length_entry = lookup_widget (GTK_BUTTON (button),
                "thermal_length_entry");
        gtk_entry_set_text (GTK_WIDGET (thermal_length_entry), "");
        gtk_widget_set_sensitive (thermal_length_entry, FALSE);
        GtkWidget *thermal_width_entry = lookup_widget (GTK_BUTTON (button),
                "thermal_width_entry");
        gtk_entry_set_text (GTK_WIDGET (thermal_width_entry), "");
        gtk_widget_set_sensitive (thermal_width_entry, FALSE);
        GtkWidget *thermal_clearance_entry = lookup_widget (GTK_BUTTON (button),
                "thermal_clearance_entry");
        gtk_entry_set_text (GTK_WIDGET (thermal_clearance_entry), "");
        gtk_widget_set_sensitive (thermal_clearance_entry, FALSE);
        GtkWidget *thermal_solder_mask_clearance_entry = lookup_widget (GTK_BUTTON (button),
                "thermal_solder_mask_clearance_entry");
        gtk_entry_set_text (GTK_WIDGET (thermal_solder_mask_clearance_entry), "");
        gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, FALSE);

        /* Widgets on tab 4 "Silkscreen" */
        GtkWidget *silkscreen_package_outline_checkbutton = lookup_widget (GTK_BUTTON (button),
                "silkscreen_package_outline_checkbutton");
        gtk_toggle_button_set_active (silkscreen_package_outline_checkbutton, FALSE);
        GtkWidget *silkscreen_line_width_entry = lookup_widget (GTK_BUTTON (button),
                "silkscreen_line_width_entry");
        gtk_entry_set_text (GTK_WIDGET (silkscreen_line_width_entry), "");
        GtkWidget *silkscreen_indicate_1_checkbutton = lookup_widget (GTK_BUTTON (button),
                "silkscreen_indicate_1_checkbutton");
        gtk_toggle_button_set_active (silkscreen_indicate_1_checkbutton, FALSE);
        GtkWidget *courtyard_checkbutton = lookup_widget (GTK_BUTTON (button),
                "courtyard_checkbutton");
        gtk_toggle_button_set_active (courtyard_checkbutton, FALSE);
        GtkWidget *courtyard_length_entry = lookup_widget (GTK_BUTTON (button),
                "courtyard_length_entry");
        gtk_entry_set_text (GTK_WIDGET (courtyard_length_entry), "");
        GtkWidget *courtyard_width_entry = lookup_widget (GTK_BUTTON (button),
                "courtyard_width_entry");
        gtk_entry_set_text (GTK_WIDGET (courtyard_width_entry), "");
        GtkWidget *courtyard_line_width_entry = lookup_widget (GTK_BUTTON (button),
                "courtyard_line_width_entry");
        gtk_entry_set_text (GTK_WIDGET (courtyard_line_width_entry), "");
        GtkWidget *courtyard_clearance_with_package_entry = lookup_widget (GTK_BUTTON (button),
                "courtyard_clearance_with_package_entry");
        gtk_entry_set_text (GTK_WIDGET (courtyard_clearance_with_package_entry), "");

        /* Widgets on tab 5 "Heel & Toe goals" */
        GtkWidget *C1_entry = lookup_widget (GTK_BUTTON (button),
                "C1_entry");
        gtk_entry_set_text (GTK_WIDGET (C1_entry), "");
        gtk_widget_set_sensitive (C1_entry, TRUE);
        GtkWidget *C2_entry = lookup_widget (GTK_BUTTON (button),
                "C2_entry");
        gtk_entry_set_text (GTK_WIDGET (C2_entry), "");
        gtk_widget_set_sensitive (C2_entry, TRUE);
        GtkWidget *G1_entry = lookup_widget (GTK_BUTTON (button),
                "G1_entry");
        gtk_entry_set_text (GTK_WIDGET (G1_entry), "");
        gtk_widget_set_sensitive (G1_entry, FALSE);
        GtkWidget *G2_entry = lookup_widget (GTK_BUTTON (button),
                "G2_entry");
        gtk_entry_set_text (GTK_WIDGET (G2_entry), "");
        gtk_widget_set_sensitive (G2_entry, FALSE);
        GtkWidget *Z1_entry = lookup_widget (GTK_BUTTON (button),
                "Z1_entry");
        gtk_entry_set_text (GTK_WIDGET (Z1_entry), "");
        gtk_widget_set_sensitive (Z1_entry, FALSE);
        GtkWidget *Z2_entry = lookup_widget (GTK_BUTTON (button),
                "Z2_entry");
        gtk_entry_set_text (GTK_WIDGET (Z2_entry), "");
        gtk_widget_set_sensitive (Z2_entry, FALSE);
        GtkWidget *C1_radiobutton = lookup_widget (GTK_BUTTON (button),
                "C1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C1_radiobutton), TRUE);
        GtkWidget *C2_radiobutton = lookup_widget (GTK_BUTTON (button),
                "C2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C2_radiobutton), TRUE);
        GtkWidget *G1_radiobutton = lookup_widget (GTK_BUTTON (button),
                "G1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (G1_radiobutton), FALSE);
        GtkWidget *G2_radiobutton = lookup_widget (GTK_BUTTON (button),
                "G2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (G2_radiobutton), FALSE);
        GtkWidget *Z1_radiobutton = lookup_widget (GTK_BUTTON (button),
                "Z1_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (Z1_radiobutton), FALSE);
        GtkWidget *Z2_radiobutton = lookup_widget (GTK_BUTTON (button),
                "Z2_radiobutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (Z2_radiobutton), FALSE);
}


/*!
 * \brief The "Close" button is clicked.
 *
 * - close the application.
 */
void
on_close_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
        gtk_main_quit();
}


/*!
 * \brief The "Count X-direction" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to an integer and store in the \c count_x variable (global).
 */
void
on_count_x_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *count_x_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        count_x = (int) g_ascii_strtod (count_x_string, &leftovers);
        number_of_pins = (number_of_rows * count_x + number_of_columns * count_y) + thermal;
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (editable),
                "number_total_pins_entry");
        gtk_entry_set_text (number_total_pins_entry,
                g_strdup_printf ("%d", number_of_pins));
        entry_has_changed (editable);
        number_of_pins_has_changed (editable);
}


/*!
 * \brief The "Count Y-direction" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to an integer and store in the \c count_y variable (global).
 */
void
on_count_y_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *count_y_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        count_y = (int) g_ascii_strtod (count_y_string, &leftovers);
        number_of_pins = (number_of_rows * count_x + number_of_columns * count_y) + thermal;
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (editable),
                "number_total_pins_entry");
        gtk_entry_set_text (number_total_pins_entry,
                g_strdup_printf ("%d", number_of_pins));
        entry_has_changed (editable);
        number_of_pins_has_changed (editable);
}


/*!
 * \brief The "courtyard" checkbutton is toggled.
 *
 * - get active state.
 * - store in the \c courtyard variable (global).
 */
void
on_courtyard_checkbutton_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        courtyard = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        GtkWidget *courtyard_line_width_entry = lookup_widget (GTK_BUTTON (togglebutton),
                "courtyard_line_width_entry");
        gtk_widget_set_sensitive (courtyard_line_width_entry, courtyard);
        GtkWidget *courtyard_length_entry = lookup_widget (GTK_BUTTON (togglebutton),
                "courtyard_length_entry");
        gtk_widget_set_sensitive (courtyard_length_entry, courtyard);
        GtkWidget *courtyard_width_entry = lookup_widget (GTK_BUTTON (togglebutton),
                "courtyard_width_entry");
        gtk_widget_set_sensitive (courtyard_width_entry, courtyard);
        GtkWidget *courtyard_clearance_with_package_entry = lookup_widget (GTK_BUTTON (togglebutton),
                "courtyard_clearance_with_package_entry");
        gtk_widget_set_sensitive (courtyard_clearance_with_package_entry, courtyard);
        entry_has_changed (togglebutton);
}


/*!
 * \brief The "courtyard clearance with package" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c courtyard_clearance_with_package
 *   variable (global).
 */
void
on_courtyard_clearance_with_package_entry_changed
                                        (GtkEditable     *editable,
                                         gpointer         user_data)
{
        gchar *leftovers;
        gchar *courtyard_clearance_with_package_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        courtyard_clearance_with_package = g_ascii_strtod (courtyard_clearance_with_package_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "length of the courtyard (X)" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c courtyard_length variable
 *   (global).
 */
void
on_courtyard_length_entry_changed      (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *courtyard_length_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        courtyard_length = g_ascii_strtod (courtyard_length_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "courtyard line width" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c courtyard_line_width variable
 * (global).
 */
void
on_courtyard_line_width_entry_changed  (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *courtyard_line_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        courtyard_line_width = g_ascii_strtod (courtyard_line_width_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "width of the courtyard (Y)" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c courtyard_width variable
 *   (global).
 */
void
on_courtyard_width_entry_changed       (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *courtyard_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        courtyard_width = g_ascii_strtod (courtyard_width_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The file chooser dialog "Cancel" button is clicked.
 *
 * - lookup the dialog widget.
 * - destroy the file chooser widget.
 * \todo - maybe restore the preview widget ?
 */
void
on_filechooser_dialog_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
        GtkWidget *filechooser_dialog = lookup_widget (GTK_BUTTON (button),
                "filechooser_dialog");
        gtk_widget_destroy (filechooser_dialog);
}


/*!
 * \brief The file chooser dialog "close" signal is emitted.
 *
 * - lookup the dialog widget.
 * - destroy the file chooser widget.
 */
void
on_filechooser_dialog_close            (GtkDialog       *dialog,
                                        gpointer         user_data)
{
        GtkWidget *filechooser_dialog = lookup_widget (GTK_DIALOG (dialog),
                "filechooser_dialog");
        gtk_widget_destroy (filechooser_dialog);
}



/*!
 * \brief The file chooser dialog "current folder changed" signal is emitted.
 *
 * - lookup the dialog widget.
 * - get the current folder.
 * - test the current folder for null pointer or empty string and if true,
 *   please notify the user (in the statusbar).
 * - store the (new) current folder name in \c temp_dir.
 */
void
on_filechooser_dialog_current_folder_changed
                                        (GtkFileChooser  *filechooser,
                                        gpointer         user_data)
{
        GtkWidget *filechooser_dialog = lookup_widget (GTK_FILE_CHOOSER (filechooser),
                "filechooser_dialog");
        gchar *current_folder = g_strdup (gtk_file_chooser_get_current_folder (filechooser_dialog));
        /* Test if current folder is a null pointer.
         * If so, please notify the user (in the statusbar). */
        if (!current_folder)
        {
                gchar *message = g_strdup_printf (_("ERROR: current folder is not initialised  (null pointer)."));
                message_to_statusbar (filechooser, message);
                return;
        }
        /* Test if current folder is an empty string pointer.
         * If so, please notify the user (in the statusbar). */
        if (!strcmp (current_folder, ""))
        {
                gchar *message = g_strdup_printf (_("ERROR: current folder contains an empty string."));
                message_to_statusbar (filechooser, message);
                return;
        }
        /* Test if current folder is a directory.
         * If so, store in temp_dir. */
        if (g_file_test (current_folder, G_FILE_TEST_IS_DIR))
        {
                temp_dir = g_strdup (current_folder);
        }
}


/*!
 * \brief The file chooser dialog "Open" button is clicked.
 *
 * - lookup the dialog widget.
 * - get the selected filename.
 * - test the selected filename for null pointer or empty string and if true,
 *   please notify the user (in the statusbar).
 * - test if the selected filename is not a directory and if true,
 *   please notify the user (in the statusbar), to select a file.
 * - store the selected filename in \c fpw_filename.
 * - read the (new) current directory name from \c temp_dir and\n
 *   store in \c work_dir.
 * - read new global values from the selected footprintwizard file.
 * \todo update the entry widgets to reflect the changes.
 */
void
on_filechooser_dialog_open_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
        GtkWidget *filechooser_dialog = lookup_widget (GTK_BUTTON (button),
                "filechooser_dialog");
        gchar *selected_filename = g_strdup (gtk_file_chooser_get_filename (filechooser_dialog));
        /* Test if selected filename is a null pointer.
         * If so, please notify the user (in the statusbar). */
        if (!selected_filename)
        {
                gchar *message = g_strdup_printf (_("ERROR: selected filename is not initialised  (null pointer)."));
                message_to_statusbar (button, message);
                return;
        }
        /* Test if selected filename is a null pointer.
         * If so, please notify the user (in the statusbar). */
        if (!strcmp (selected_filename, ""))
        {
                gchar *message = g_strdup_printf (_("ERROR: selected filename contains an empty string."));
                message_to_statusbar (button, message);
                return;
        }
        /* Test if selected filename is a directory.
         * If so, please notify the user (in the statusbar), to select a file
         * instead. */
        if (g_file_test (selected_filename, G_FILE_TEST_IS_DIR))
        {
                gchar *message = g_strdup_printf (_("ERROR: selected filename is a directory."));
                message_to_statusbar (button, message);
                return;
        }
        /* Store the (now validated) selected filename */
        fpw_filename = g_strdup (selected_filename);
        /* Update the working directory (test for null pointer) */
        if (!temp_dir)
                work_dir = g_strdup (temp_dir);
        /* Read new global values from the selected footprintwizard file */
        if (read_footprintwizard_file (fpw_filename))
        {
                gchar *message = g_strdup_printf (_("Read footprintwizard file %s."), fpw_filename);
                message_to_statusbar (button, message);
        }
        else
        {
                gchar *message = g_strdup_printf (_("ERROR: Unable to read footprint wizard file %s."), fpw_filename);
                message_to_statusbar (button, message);
        }
        /* Update the entry widgets to reflect the changes */
}


/*!
 * \brief The file chooser dialog "selection changed" signal is emitted.
 *
 * \todo - store the selected filename in \c temp_fpw_filename.
 * \todo - read the values from the selected footprintwizard file in a
 * temporary set of variables \c temp_*.
 * \todo - generate a new preview image.
 * \todo - update the preview widget.
 */
void
on_filechooser_dialog_selection_changed
                                        (GtkFileChooser  *filechooser,
                                        gpointer         user_data)
{

}


/*!
 * \brief The file chooser dialog "update preview" signal is emitted.
 *
 * \todo - generate a new preview image.
 * \todo - update the preview widget.
 */
void
on_filechooser_dialog_update_preview   (GtkFileChooser  *filechooser,
                                        gpointer         user_data)
{

}


/*!
 * \brief The "footprint author name" entry is changed.
 *
 * - store in the \c footprint_author variable (global).
 */
void
on_footprint_author_entry_changed      (GtkEditable     *editable,
                                        gpointer         user_data)
{
        footprint_author = gtk_entry_get_text (GTK_EDITABLE (editable));
        entry_has_changed (editable);
}


/*!
 * \brief The "footprint distribution license" entry is changed.
 *
 * - store in the \c footprint_dist_license variable (global).
 */
void
on_footprint_dist_license_entry_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        footprint_dist_license = gtk_entry_get_text (GTK_EDITABLE (editable));
        entry_has_changed (editable);
}


/*!
 * \brief The "footprint name" entry is changed.
 *
 * - store in the \c footprint_name variable (global).
 */
void
on_footprint_name_entry_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        footprint_name = gtk_entry_get_text (GTK_EDITABLE (editable));
        entry_has_changed (editable);
        /* Check for a null pointer in footprint_name for this might cause a
         * segmentation fault or undefined behaviour.
         */
        if (!footprint_name)
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint name not initialised (null pointer)."));
                message_to_statusbar (editable, message);
                return;
        }
        /* Check for an empty footprint_name string for this might cause a
         * segmentation fault or undefined behaviour.
         */
        else if (!strcmp (footprint_name, ""))
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint name contains an empty string."));
                message_to_statusbar (editable, message);
                return;
        }
        else
        {
                gchar *message = g_strdup_printf ("");
                message_to_statusbar (editable, message);
                return;
        }
}


/*!
 * \brief The "footprint refdes prefix" entry is changed.
 *
 * - store in the \c footprint_refdes variable (global).
 */
void
on_footprint_refdes_entry_changed      (GtkEditable     *editable,
                                        gpointer         user_data)
{
        entry_has_changed (editable);
        footprint_refdes = gtk_entry_get_text (GTK_EDITABLE (editable));
}

/*!
 * \brief The "footprint status" entry is changed.
 *
 * - store in the \c footprint_status variable (global).
 */
void
on_footprint_status_entry_changed      (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        footprint_status = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
        entry_has_changed (combobox);
}


/*!
 * \brief The "footprint type" entry is changed.
 *
 * - test if the footprint name is equal with the footprint type or has a
 *   null pointer or is an empty string, if so copy the footprint type into
 *   the footprint name entry.
 * - store the new value in the \c footprint_type variable (global).
 */
void
on_footprint_type_entry_changed        (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        /* Test if the existing footprint name is equal to the footprint
         * type or is empty or has a null pointer, if this is true the user
         * did not add any characters to the footprint name yet (he/she
         * probably made up his/her mind on the footprint type), so we can
         * safely copy the new footprint type into the footprint name entry.
         */
        if
                (
                        !footprint_name ||
                        (!strcmp (footprint_name, "")) ||
                        (!strcmp (footprint_type, footprint_name))
                )
        {
                footprint_type = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
                footprint_name = g_strdup (footprint_type);
                GtkEntry *footprint_name_entry = lookup_widget (GTK_WIDGET (combobox),
                        "footprint_name_entry");
                gtk_entry_set_text (footprint_name_entry, footprint_name);
        }
        else
                footprint_type = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
        entry_has_changed (combobox);
        /* Determine the package type */
        if (!strcmp (footprint_type, "BGA"))
        {
                all_entries_to_default_sensitivity (combobox);
                gui_constraints_set_bga (combobox);
                package_type = BGA;
                return;
        }
        else if (!strcmp (footprint_type, "CAPC"))
        {
                all_entries_to_default_sensitivity (combobox);
                gui_constraints_set_smt (combobox);
                package_type = CAPC;
                return;
        }
        else if (!strcmp (footprint_type, "CAPM"))
        {
                all_entries_to_default_sensitivity (combobox);
                gui_constraints_set_smt (combobox);
                package_type = CAPM;
                return;
        }
        else if (!strcmp (footprint_type, "DIL"))
        {
                package_type = DIL;
                all_entries_to_default_sensitivity (combobox);
                return;
        }
        else if (!strcmp (footprint_type, "DIP"))
        {
                all_entries_to_default_sensitivity (combobox);
                gui_constraints_set_dip (combobox);
                package_type = DIP;
                return;
        }
        else if (!strcmp (footprint_type, "INDC"))
        {
                all_entries_to_default_sensitivity (combobox);
                gui_constraints_set_smt (combobox);
                package_type = INDC;
                return;
        }
        else if (!strcmp (footprint_type, "INDM"))
        {
                all_entries_to_default_sensitivity (combobox);
                gui_constraints_set_smt (combobox);
                package_type = INDM;
                return;
        }
        else if (!strcmp (footprint_type, "PGA"))
        {
                all_entries_to_default_sensitivity (combobox);
                gui_constraints_set_pga (combobox);
                package_type = PGA;
                return;
        }
        else if (!strcmp (footprint_type, "PLCC"))
        {
                all_entries_to_default_sensitivity (combobox);
                gui_constraints_set_plcc (combobox);
                package_type = PLCC;
                return;
        }
        else if (!strcmp (footprint_type, "QFN"))
        {
                all_entries_to_default_sensitivity (combobox);
                package_type = QFN;
                gchar *message = g_strdup_printf (_("ERROR: footprint type QFN is not yet implemented."));
                message_to_statusbar (combobox, message);
                return;
        }
        else if (!strcmp (footprint_type, "QFP"))
        {
                all_entries_to_default_sensitivity (combobox);
                package_type = QFP;
                gchar *message = g_strdup_printf (_("ERROR: footprint type QFP is not yet implemented."));
                message_to_statusbar (combobox, message);
                return;
        }
        else if (!strcmp (footprint_type, "RESC"))
        {
                all_entries_to_default_sensitivity (combobox);
                gui_constraints_set_smt (combobox);
                package_type = RESC;
                return;
        }
        else if (!strcmp (footprint_type, "RESM"))
        {
                all_entries_to_default_sensitivity (combobox);
                gui_constraints_set_smt (combobox);
                package_type = RESM;
                return;
        }
        else if (!strcmp (footprint_type, "SIL"))
        {
                all_entries_to_default_sensitivity (combobox);
                package_type = SIL;
                gchar *message = g_strdup_printf (_("ERROR: footprint type SIL is not yet implemented."));
                message_to_statusbar (combobox, message);
                return;
        }
        else if (!strcmp (footprint_type, "SIP"))
        {
                all_entries_to_default_sensitivity (combobox);
                package_type = SIP;
                gchar *message = g_strdup_printf (_("ERROR: footprint type SIP is not yet implemented."));
                message_to_statusbar (combobox, message);
                return;
        }
        else if (!strcmp (footprint_type, "SO"))
        {
                all_entries_to_default_sensitivity (combobox);
                package_type = SO;
                gchar *message = g_strdup_printf (_("ERROR: footprint type SO is not yet implemented."));
                message_to_statusbar (combobox, message);
                return;
        }
        else if (!strcmp (footprint_type, "TO92"))
        {
                all_entries_to_default_sensitivity (combobox);
                gui_constraints_set_to92 (combobox);
                package_type = TO92;
                return;
        }
        gchar *message = g_strdup_printf (_("ERROR: unknown or not yet implemented footprint type entered."));
        message_to_statusbar (combobox, message);
}


/*!
 * \brief The "footprint units" entry is changed.
 *
 * - store in the \c footprint_units variable (global).
 * - check for null pointer and empty string.
 */
void
on_footprint_units_entry_changed       (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        entry_has_changed (combobox);
        footprint_units = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
        /* Check for a null pointer in footprint units for this might cause a
         * segmentation fault or undefined behaviour.
         */
        if (!footprint_units)
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint units not initialised (null pointer)."));
                message_to_statusbar (combobox, message);
                return;
        }
        /* Check for an empty footprint units string for this might cause a
         * segmentation fault or undefined behaviour.
         */
        else if (!strcmp (footprint_units, ""))
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint units contains an empty string."));
                message_to_statusbar (combobox, message);
                return;
        }
        else
        {
                gchar *message = g_strdup_printf ("");
                message_to_statusbar (combobox, message);
        }
        /* Determine the multiplier based upon the units type */
        if (!strcmp (footprint_units, "mil"))
        {
                multiplier = 100.0;
                return;
        }
        if (!strcmp (footprint_units, "mil/100"))
        {
                multiplier = 1.0;
                return;
        }
        if (!strcmp (footprint_units, "mm"))
        {
                multiplier = (1000 / 25.4) * 100;
                return;
        }
        gchar *message = g_strdup_printf (_("ERROR: footprint units contains an unknown units type."));
        message_to_statusbar (combobox, message);
}


/*!
 * \brief The "footprint usage license" entry is changed.
 *
 * - store in the \c footprint_use_license variable (global).
 */
void
on_footprint_use_license_entry_changed (GtkEditable     *editable,
                                        gpointer         user_data)
{
        entry_has_changed (editable);
        footprint_use_license = gtk_entry_get_text (GTK_EDITABLE (editable));
}


/*!
 * \brief The "footprint value" entry is changed.
 *
 * - store in the \c footprint_value variable (global).
 */
void
on_footprint_value_entry_changed       (GtkEditable     *editable,
                                        gpointer         user_data)
{
        footprint_value = gtk_entry_get_text (GTK_EDITABLE (editable));
        entry_has_changed (editable);
}


/*!
 * \brief The "position of number 1 pad/pin" entry is changed.
 *
 * - store in the \c n1_pos variable (global).
 */
void
on_number_1_position_entry_changed
                                        (GtkComboBox     *combobox,
                                         gpointer         user_data)
{
        pin_1_position = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
        entry_has_changed (combobox);
}


/*!
 * \brief The "number of columns" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c n_col variable (global).
 */
void
on_number_of_columns_entry_changed     (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *number_of_columns_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        number_of_columns = (int) g_ascii_strtod (number_of_columns_string, &leftovers);
        number_of_pins = (number_of_rows * count_x + number_of_columns * count_y) + thermal;
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (editable),
                "number_total_pins_entry");
        gtk_entry_set_text (number_total_pins_entry,
                g_strdup_printf ("%d", number_of_pins));
        entry_has_changed (editable);
        number_of_pins_has_changed (editable);
}


/*!
 * \brief The "number of rows" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c n_row variable (global).
 */
void
on_number_of_rows_entry_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *number_of_rows_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        number_of_rows = (int) g_ascii_strtod (number_of_rows_string, &leftovers);
        number_of_pins = (number_of_rows * count_x + number_of_columns * count_y) + thermal;
        GtkWidget *number_total_pins_entry = lookup_widget (GTK_WIDGET (editable),
                "number_total_pins_entry");
        gtk_entry_set_text (number_total_pins_entry,
                g_strdup_printf ("%d", number_of_pins));
        entry_has_changed (editable);
        number_of_pins_has_changed (editable);
}


/*!
 * \brief The "number of pads/pins" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c n variable (global).
 */
void
on_number_total_pins_entry_changed     (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *number_of_pins_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        number_of_pins = (int) g_ascii_strtod (number_of_pins_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "Open" button is clicked.
 *
 * - create a file chooser dialog.
 * - create and set a file filter "*.fpw" and add to the file chooser.
 * - show the file chooser widget to let the user select a .fpw file.
 */
void
on_open_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
        GtkWidget *filechooser_dialog = create_filechooser_dialog ();
        GtkFileFilter *file_filter = gtk_file_filter_new ();
        gtk_file_filter_add_pattern (file_filter, "*.fpw");
        gtk_file_chooser_add_filter (filechooser_dialog, file_filter);
        gtk_widget_show (filechooser_dialog);
}


/*!
 * \brief The "package body height" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c package_body_height variable
 *   (global).
 */
void
on_package_body_height_entry_changed   (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *package_body_height_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        package_body_height = g_ascii_strtod (package_body_height_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "package body length" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c package_body_length variable
 *   (global).
 */
void
on_package_body_length_entry_changed   (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *package_body_length_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        package_body_length = g_ascii_strtod (package_body_length_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "package body width" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c package_body_width variable
 *   (global).
 */
void
on_package_body_width_entry_changed    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *package_body_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        package_body_width = g_ascii_strtod (package_body_width_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "package is radial" checkbutton is toggled.
 *
 * - store the state of the checkbutton in the \c package_is_radial
 *   variable (global).
 */
void
on_package_is_radial_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        package_is_radial = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        entry_has_changed (togglebutton);
}


/*!
 * \brief The "pad clearance" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c pad_clearance variable
 *   (global).
 */
void
on_pad_clearance_entry_changed         (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *pad_clearance_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pad_clearance = g_ascii_strtod (pad_clearance_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "diameter of the pad (D)" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c d_pad variable (global).
 */
void
on_pad_diameter_entry_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *pad_diameter_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pad_diameter = g_ascii_strtod (pad_diameter_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "length of the pads (X)" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c pad_length variable (global).
 */
void
on_pad_length_entry_changed            (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *pad_length_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pad_length = g_ascii_strtod (pad_length_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "shape of pads" entry is changed.
 *
 * - store in the \c pad_shape variable (global).
 * - check for null pointer and empty string.
 */
void
on_pad_shape_entry_changed    (GtkComboBox     *combobox,
                               gpointer         user_data)
{
        pad_shape = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
        entry_has_changed (combobox);
        /* Check for a null pointer in pad shape for this might cause a
         * segmentation fault or undefined behaviour.
         */
        if (!pad_shape)
        {
                gchar *message = g_strdup_printf (_("ERROR: pad shape not initialised (null pointer)."));
                message_to_statusbar (combobox, message);
                return;
        }
        /* Check for an empty pad shape string for this might cause a
         * segmentation fault or undefined behaviour.
         */
        else if (!strcmp (pad_shape, ""))
        {
                gchar *message = g_strdup_printf (_("ERROR: pad shape contains an empty string."));
                message_to_statusbar (combobox, message);
                return;
        }
        else
        {
                gchar *message = g_strdup_printf ("");
                message_to_statusbar (combobox, message);
        }
        /* Determine the pad shape type, default is a circular pad */
        if (!strcmp (pad_shape, "circular pad"))
        {
                g_strconcat (pin_pad_flags, "", NULL);
                return;
        }
        if (!strcmp (pad_shape, "rectangular pad"))
        {
                g_strconcat (pin_pad_flags, "square", NULL);
                return;
        }
        if (!strcmp (pad_shape, "octagonal pad"))
        {
                g_strconcat (pin_pad_flags, "octagon", NULL);
                return;
        }
        if (!strcmp (pad_shape, "rounded pad, elongated"))
        {
                g_strconcat (pin_pad_flags, "", NULL);
                return;
        }
        gchar *message = g_strdup_printf (_("ERROR: pad shape contains an unknown pad shape type."));
        message_to_statusbar (combobox, message);
}


/*!
 * \brief The "pad solder mask clearance" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c solder_mask_clearance variable
 *   (global).
 */
void
on_pad_solder_mask_clearance_entry_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *pad_SMC_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pad_solder_mask_clearance = g_ascii_strtod (pad_SMC_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "width of the pads (Y)" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c pad_with variable (global).
 */
void
on_pad_width_entry_changed             (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *pad_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pad_width = g_ascii_strtod (pad_width_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The top-right "X" is clicked.
 *
 * - close the application.
 *
 */
void
on_pcb_gfpw_destroy                    (GtkObject       *object,
                                        gpointer         user_data)
{
        gtk_main_quit();
}


/*!
 * \brief The "diameter of the drill holes (d)" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c pin_drill_diameter
 *   variable (global).
 */
void
on_pin_drill_diameter_entry_changed    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *pin_drill_diameter_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pin_drill_diameter = g_ascii_strtod (pin_drill_diameter_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "pin #1 square" checkbutton is toggled.
 *
 * - save the state of the checkbutton in the \c pin1_square variable (global).
 */
void
on_pin_square_checkbutton_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        /* Save the state of checkbutton in global variable */
        pin1_square = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        entry_has_changed (togglebutton);
}

/*!
 * \brief The "Pitch X-direction" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c pitch_x variable (global).
 */
void
on_pitch_x_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *pitch_x_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pitch_x = g_ascii_strtod (pitch_x_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "Pitch Y-direction" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c pitch_y variable (global).
 */
void
on_pitch_y_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *pitch_y_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pitch_y = g_ascii_strtod (pitch_y_string, &leftovers);
        entry_has_changed (editable);
}

/*!
 * \brief The "Refresh" button is clicked.
 *
 * \todo - create a pixmap of the footprint based on the values in the entry
 * widgets.
 * \todo - (re)load the preview image.
 */
void
on_refresh_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{
}

/*!
 * \brief The "Save" button is clicked.
 *
 * - check for null pointer and empty string.\n
 * - determine the name of the footprintwizard filename.\n
 * - determine the name of the footprint filename.\n
 * - invoke the write_footprintwizard_file() to write the global variables to
 *   the footprintwizard file, with a .fpw suffix, for debugging and other
 *   (future) purposes.\n
 * - if the footprint wizard file is written successfull change the title of
 *   the main window with the latest filename.\n
 * - invoke the write_footprint() function to write the actual footprint
 *   file.\n
 * - if the footprint file is written successfull reflect this in the
 *   statusbar.\n
 */
void
on_save_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
        /* Check for a null pointer in footprint_name for this might cause a
         * segmentation fault or undefined behaviour.
         */
        if (!footprint_name)
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint name not initialised (null pointer)."));
                message_to_statusbar (button, message);
                return;
        }
        /* Check for an empty footprint_name string for this might cause a
         * segmentation fault or undefined behaviour.
         */
        else if (!strcmp (footprint_name, ""))
        {
                gchar *message = g_strdup_printf (_("ERROR: footprint name contains an empty string."));
                message_to_statusbar (button, message);
                return;
        }
        else
        {
                gchar *message = g_strdup_printf ("");
                message_to_statusbar (button, message);
        }
        /* Determine a filename for the footprintwizard file */
        fpw_filename = g_strdup (footprint_name);
        if (g_str_has_suffix (fpw_filename, fp_suffix))
        {
                /* footprint_name had the .fp suffix already,
                 * only add a "w" here, else we would end up with a filename
                 * like "footprint_name.fp.fpw" */
                fpw_filename = g_strconcat (fpw_filename, "w", NULL);
        }
        else
        {
                if (g_str_has_suffix (fpw_filename, fpw_suffix))
                {
                        /* footprint_name had the .fpw suffix already,
                         * we probably read from an existing footprintwizard
                         * file or screwed up, so do nothing here */
                }
                else
                {
                        /* fpw_filename has no (.fpw) suffix yet,
                         * so add a .fpw suffix */
                        fpw_filename = g_strconcat (fpw_filename, ".fpw", NULL);
                }
        }
        /* Determine a filename for the actual footprint file */
        footprint_filename = g_strdup (footprint_name);
        if (g_str_has_suffix (footprint_filename, fp_suffix))
        {
                /* footprint_filename has the .fp suffix already,
                 * so do nothing here */
        }
        else
        {
                /* footprint_filename has no .fp suffix,
                 * so add a .fp suffix */
                footprint_filename = g_strconcat (footprint_filename, ".fp", NULL);
        }
        /* If the footprint wizard file is written successfull change the title of
         * the main window with the latest filename */
        if (write_footprintwizard_file ())
        {
                change_main_window_title (button, g_strconcat ("pcb-gfpw : ",
                        fpw_filename, NULL));
                main_window_title_has_asterisk = FALSE;
                fpw_file_saved = TRUE;
        }
        else
        {
                gchar *message = g_strdup_printf (_("ERROR: Unable to write footprintwizard file %s."), footprint_filename);
                message_to_statusbar (button, message);
        }
        /* If the footprint file is written successfull reflect this in the
         * statusbar */
        if (write_footprint ())
        {
                gchar *message = g_strdup_printf (_("Wrote footprint %s to file."), footprint_filename);
                message_to_statusbar (button, message);
        }
        else
        {
                gchar *message = g_strdup_printf (_("ERROR: Unable to write footprint %s to file."), footprint_filename);
                message_to_statusbar (button, message);
        }
}


/*!
 * \brief The "indicate pin/pad number 1" checkbutton is toggled.
 *
 * - store the state of the checkbutton in the \c silkscreen_indicate_1
 *   variable (global).
 */
void
on_silkscreen_indicate_1_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        silkscreen_indicate_1 = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        entry_has_changed (togglebutton);
}


/*!
 * \brief The "silkscreen line width" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c silkscreen_line_thickness
 *   variable (global).
 */
void
on_silkscreen_line_width_entry_changed (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *silkscreen_line_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        silkscreen_line_width = g_ascii_strtod (silkscreen_line_width_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "package outline" checkbutton is toggled.
 *
 * - save the state of the checkbutton in the \c silkscreen_package_outline
 *   variable (global).
 * - if the "package outline" checkbutton is not "checked", set the linewidth
 *   entry to insensitive.
 * - if the "package outline" checkbutton is "checked", set the line width
 *   entry to sensitive.
 */
void
on_silkscreen_package_outline_checkbutton_toggled
                                        (GtkToggleButton *togglebutton,
                                         gpointer         user_data)
{
        /* Save the state of checkbutton in global variable */
        silkscreen_package_outline = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        /* Look up widgets */
        GtkWidget *silkscreen_line_width_entry = lookup_widget (GTK_BUTTON (togglebutton), "silkscreen_line_width_entry");
        /* Set entities to (in)sensitive according to the state of the
         * checkbutton variable */
        gtk_widget_set_sensitive (silkscreen_line_width_entry, silkscreen_package_outline);
        entry_has_changed (togglebutton);
}


/*!
 * \brief The "thermal pad" checkbutton is toggled.
 *
 * - save the state of the checkbutton in the \c thermal variable (global).
 * - if the "thermal pad" checkbutton is not "checked", set the length and
 *   width entries to insensitive.
 * - if the "thermal pad" checkbutton is "checked", set the length and width
 *   entries to sensitive.
 * - if the "thermal pad" checkbutton is "checked", set the no paste
 *   checkbutton to sensitive and active (on).
 */
void
on_thermal_checkbutton_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        /* Save the state of checkbutton in a global variable */
        thermal = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        entry_has_changed (togglebutton);
        number_of_pins_has_changed (togglebutton);
        /* Look up widgets */
        GtkToggleButton *thermal_nopaste_checkbutton = lookup_widget (GTK_BUTTON (togglebutton),
                "thermal_nopaste_checkbutton");
        GtkWidget *thermal_length_entry = lookup_widget (GTK_BUTTON (togglebutton),
                "thermal_length_entry");
        GtkWidget *thermal_width_entry = lookup_widget (GTK_BUTTON (togglebutton),
                "thermal_width_entry");
        GtkWidget *thermal_clearance_entry = lookup_widget (GTK_BUTTON (togglebutton),
                "thermal_clearance_entry");
        GtkWidget *thermal_solder_mask_clearance_entry = lookup_widget (GTK_BUTTON (togglebutton),
                "thermal_solder_mask_clearance_entry");
        /* Set entities to (in)sensitive according to the state of the
         * checkbutton variable */
        gtk_widget_set_sensitive (thermal_nopaste_checkbutton, thermal);
        gtk_widget_set_sensitive (thermal_length_entry, thermal);
        gtk_widget_set_sensitive (thermal_width_entry, thermal);
        gtk_widget_set_sensitive (thermal_clearance_entry, thermal);
        gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, thermal);
        /* We want no paste on a thermal pad as a default, so when the user
         * checks the thermal checkbutton (on), the user has to turn off
         * paste if desired while leaving the thermal checkbutton checked
         * (on) */
        gtk_toggle_button_set_active (thermal_nopaste_checkbutton, thermal);
}


/*!
 * \brief The "thermal pad clearance" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c thermal_clearance
 *   variable (global).
 */
void
on_thermal_clearance_entry_changed     (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *thermal_clearance_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        thermal_clearance = g_ascii_strtod (thermal_clearance_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "thermal pad length" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c thermal_length variable (global).
 */
void
on_thermal_length_entry_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *thermal_length_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        thermal_length = g_ascii_strtod (thermal_length_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "thermal pad no paste" checkbutton is clicked.
 *
 * - store the state of the checkbutton in the \c thermal_nopaste variable
 *   (global).
 */
void
on_thermal_nopaste_checkbutton_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        thermal_nopaste = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        entry_has_changed (togglebutton);
}


/*!
 * \brief The "thermal pad solder mask clearance" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c thermal_solder_clearance
 *   variable (global).
 */
void
on_thermal_solder_mask_clearance_entry_changed
                                        (GtkEditable     *editable,
                                         gpointer         user_data)
{
        gchar *leftovers;
        gchar *SMC_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        thermal_solder_mask_clearance = g_ascii_strtod (SMC_string, &leftovers);
        entry_has_changed (editable);
}


/*!
 * \brief The "thermal pad width" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c thermal_width variable (global).
 */
void
on_thermal_width_entry_changed         (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *leftovers;
        gchar *thermal_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        thermal_width = g_ascii_strtod (thermal_width_string, &leftovers);
        entry_has_changed (editable);
}

/* EOF */
