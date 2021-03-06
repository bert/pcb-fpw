/*!
 * \file src/callbacks.h
 *
 * \author Copyright (C) 2007-2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Callback functions header file for the pcb footprintwizard.
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


#include <gtk/gtk.h>

G_BEGIN_DECLS /* keep c++ happy */

void
on_C1_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_C1_radiobutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_C2_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_C2_radiobutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_G1_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_G1_radiobutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_G2_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_G2_radiobutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_Z1_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_Z1_radiobutton_toggled (GtkToggleButton *togglebutton,gpointer user_data);

void
on_Z2_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_Z2_radiobutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_about_dialog_close (GtkDialog *dialog, gint response_id, gpointer user_data);

void
on_about_dialog_destroy  (GtkObject *object, gpointer user_data);

void
on_add_attribs_checkbutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_add_license_checkbutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_clear_button_clicked (GtkButton *button, gpointer user_data);

void
on_close_button_clicked (GtkButton *button, gpointer user_data);

void
on_count_x_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_count_y_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_courtyard_checkbutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_courtyard_clearance_with_package_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_courtyard_length_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_courtyard_line_width_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_courtyard_width_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_dimensions_button_clicked  (GtkButton *button, gpointer user_data);

void
on_fiducial_checkbutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_fiducial_pad_clearance_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_fiducial_pad_diameter_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_fiducial_pad_solder_mask_clearance_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_filechooser_dialog_cancel_button_clicked (GtkButton *button, gpointer user_data);

void
on_filechooser_dialog_close (GtkDialog *dialog, gpointer user_data);

void
on_filechooser_dialog_current_folder_changed (GtkFileChooser *filechooser, gpointer user_data);

void
on_filechooser_dialog_open_button_clicked (GtkButton *button, gpointer user_data);

void
on_filechooser_dialog_selection_changed (GtkFileChooser *filechooser, gpointer user_data);

void
on_filechooser_dialog_update_preview (GtkFileChooser *filechooser, gpointer user_data);

void
on_footprint_author_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_footprint_button_clicked (GtkButton *button, gpointer user_data);

void
on_footprint_dist_license_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_footprint_name_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_footprint_refdes_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_footprint_status_entry_changed (GtkComboBox *combobox, gpointer user_data);

void
on_footprint_type_entry_changed (GtkComboBox *combobox, gpointer user_data);

void
on_footprint_units_entry_changed (GtkComboBox *combobox, gpointer user_data);

void
on_footprint_use_license_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_footprint_value_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_number_1_position_entry_changed (GtkComboBox *combobox, gpointer user_data);

void
on_number_of_columns_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_number_of_rows_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_number_total_pins_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_open_button_clicked (GtkButton *button, gpointer user_data);

void
on_package_body_height_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_package_body_length_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_package_body_width_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_package_is_radial_checkbutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_pad_clearance_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_pad_diameter_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_pad_length_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_pad_shape_entry_changed (GtkComboBox *combobox, gpointer user_data);

void
on_pad_solder_mask_clearance_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_pad_width_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_pcb_gfpw_destroy (GtkObject *object, gpointer user_data);

void
on_pin_drill_diameter_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_pin_pad_exceptions_button_clicked (GtkButton *button, gpointer user_data);

void
on_pin_pad_exceptions_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_pin_square_checkbutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_pitch_x_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_pitch_y_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_preview_button_clicked (GtkButton *button, gpointer user_data);

void
on_refresh_button_clicked (GtkButton *button, gpointer user_data);

void
on_save_button_clicked (GtkButton *button, gpointer user_data);

void
on_silkscreen_indicate_1_checkbutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_silkscreen_line_width_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_silkscreen_package_outline_checkbutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_thermal_checkbutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_thermal_clearance_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_thermal_length_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_thermal_nopaste_checkbutton_toggled (GtkToggleButton *togglebutton, gpointer user_data);

void
on_thermal_solder_mask_clearance_entry_changed (GtkEditable *editable, gpointer user_data);

void
on_thermal_width_entry_changed (GtkEditable *editable, gpointer user_data);

G_END_DECLS /* keep c++ happy */

/* EOF */
