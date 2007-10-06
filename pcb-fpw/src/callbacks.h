#include <gtk/gtk.h>


void
on_gFootprintWizard_destroy            (GtkObject       *object,
                                        gpointer         user_data);

void
on_footprint_name_entry_changed        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_footprint_type_entry_changed        (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_footprint_units_entry_changed       (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_pad_length_entry_changed            (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_number_total_pins_entry_changed     (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_thermal_checkbutton_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_thermal_length_entry_changed        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_E1_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_pad_diameter_entry_changed          (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_number_of_rows_entry_changed        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_pin_drill_diameter_entry_changed    (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_pad_width_entry_changed             (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_E2_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_thermal_width_entry_changed         (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_pad_shape_combobox_entry_changed    (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_number_1_position_combobox_entry_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data);

void
on_pad_solder_mask_clearance_entry_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_number_of_columns_entry_changed     (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_thermal_solder_mask_clearance_entry_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_vertical_silkscreen_entry_changed   (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_vertical_courtyard_entry_changed    (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_silkscreen_line_thickness_entry_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_courtyard_line_thickness_entry_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_horizontal_silkscreen_entry_changed (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_horizontal_courtyard_entry_changed  (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_G1_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_C1_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_Z1_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_Z1_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_C1_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_G1_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_G2_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_C2_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_Z2_radiobutton_toggled              (GtkToggleButton *togglebutton,
                                        gpointer         user_data);

void
on_G2_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_C2_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_Z2_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data);

void
on_close_button_clicked                (GtkButton       *button,
                                        gpointer         user_data);

void
on_ok_button_clicked                   (GtkButton       *button,
                                        gpointer         user_data);

void
on_preview_button_clicked              (GtkButton       *button,
                                        gpointer         user_data);
