/*!
 * \file callbacks.c
 * \version 0.0.2
 * \author Copyright (C) 2007 by Bert Timmerman <bert.timmerman@xs4all.nl>
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
        gchar *C1_string = NULL;
        gchar *leftovers;

        C1_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        c1 = g_ascii_strtod (C1_string, &leftovers);
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
        GtkWidget *C1_entry = NULL;
        GtkWidget *G1_entry = NULL;
        GtkWidget *Z1_entry = NULL;

        C1_entry = lookup_widget (GTK_WIDGET (togglebutton), "C1_entry");
        G1_entry = lookup_widget (GTK_WIDGET (togglebutton), "G1_entry");
        Z1_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z1_entry");
        gtk_widget_set_sensitive (C1_entry, TRUE);
        gtk_widget_set_sensitive (G1_entry, FALSE);
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
        gchar *C2_string = NULL;
        gchar *leftovers;

        C2_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        c2 = g_ascii_strtod (C2_string, &leftovers);
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
        GtkWidget *C2_entry = NULL;
        GtkWidget *G2_entry = NULL;
        GtkWidget *Z2_entry = NULL;

        C2_entry = lookup_widget (GTK_WIDGET (togglebutton), "C2_entry");
        G2_entry = lookup_widget (GTK_WIDGET (togglebutton), "G2_entry");
        Z2_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z2_entry");
        gtk_widget_set_sensitive (C2_entry, TRUE);
        gtk_widget_set_sensitive (G2_entry, FALSE);
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
        gchar *G1_string = NULL;
        gchar *leftovers;

        G1_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        g1 = g_ascii_strtod (G1_string, &leftovers);
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
        GtkWidget *C1_entry = NULL;
        GtkWidget *G1_entry = NULL;
        GtkWidget *Z1_entry = NULL;

        C1_entry = lookup_widget (GTK_WIDGET (togglebutton), "C1_entry");
        G1_entry = lookup_widget (GTK_WIDGET (togglebutton), "G1_entry");
        Z1_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z1_entry");
        gtk_widget_set_sensitive (C1_entry, FALSE);
        gtk_widget_set_sensitive (G1_entry, TRUE);
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
        gchar *G2_string = NULL;
        gchar *leftovers;

        G2_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        g2 = g_ascii_strtod (G2_string, &leftovers);
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
        GtkWidget *C2_entry = NULL;
        GtkWidget *G2_entry = NULL;
        GtkWidget *Z2_entry = NULL;

        C2_entry = lookup_widget (GTK_WIDGET (togglebutton), "C2_entry");
        G2_entry = lookup_widget (GTK_WIDGET (togglebutton), "G2_entry");
        Z2_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z2_entry");
        gtk_widget_set_sensitive (C2_entry, FALSE);
        gtk_widget_set_sensitive (G2_entry, TRUE);
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
        gchar *Z1_string = NULL;
        gchar *leftovers;

        Z1_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        z1 = g_ascii_strtod (Z1_string, &leftovers);
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
        GtkWidget *C1_entry = NULL;
        GtkWidget *G1_entry = NULL;
        GtkWidget *Z1_entry = NULL;

        C1_entry = lookup_widget (GTK_WIDGET (togglebutton), "C1_entry");
        G1_entry = lookup_widget (GTK_WIDGET (togglebutton), "G1_entry");
        Z1_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z1_entry");
        gtk_widget_set_sensitive (C1_entry, FALSE);
        gtk_widget_set_sensitive (G1_entry, FALSE);
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
        gchar *Z2_string = NULL;
        gchar *leftovers;

        Z2_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        z2 = g_ascii_strtod (Z2_string, &leftovers);
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
        GtkWidget *C2_entry = NULL;
        GtkWidget *G2_entry = NULL;
        GtkWidget *Z2_entry = NULL;

        C2_entry = lookup_widget (GTK_WIDGET (togglebutton), "C2_entry");
        G2_entry = lookup_widget (GTK_WIDGET (togglebutton), "G2_entry");
        Z2_entry = lookup_widget (GTK_WIDGET (togglebutton), "Z2_entry");
        gtk_widget_set_sensitive (C2_entry, FALSE);
        gtk_widget_set_sensitive (G2_entry, FALSE);
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
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *footprint_name_entry = NULL;
        GtkWidget *footprint_type_entry = NULL;
        GtkWidget *footprint_units_entry = NULL;
        GtkWidget *footprint_value_entry = NULL;
        GtkWidget *package_body_length_entry = NULL;
        GtkWidget *package_body_width_entry = NULL;
        GtkWidget *package_body_height_entry = NULL;
        GtkWidget *package_is_radial_checkbutton = NULL;
        GtkWidget *footprint_author_entry = NULL;
        GtkWidget *footprint_dist_license_entry = NULL;
        GtkWidget *footprint_use_license_entry = NULL;
        GtkWidget *footprint_status_entry = NULL;
        /* Look up widgets on tab 1 "Footprint" */
        footprint_name_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_name_entry");
        footprint_type_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_type_entry");
        footprint_units_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_units_entry");
        footprint_value_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_value_entry");
        package_body_length_entry = lookup_widget (GTK_BUTTON (button),
                "package_body_length_entry");
        package_body_width_entry = lookup_widget (GTK_BUTTON (button),
                "package_body_width_entry");
        package_body_height_entry = lookup_widget (GTK_BUTTON (button),
                "package_body_height_entry");
        package_is_radial_checkbutton = lookup_widget (GTK_BUTTON (button),
                "package_is_radial_checkbutton");
        footprint_author_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_author_entry");
        footprint_dist_license_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_dist_license_entry");
        footprint_use_license_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_use_license_entry");
        footprint_status_entry = lookup_widget (GTK_BUTTON (button),
                "footprint_status_entry");
        /* Clear entries (remove characters) on tab 1"Footprint" */
        gtk_entry_set_text (GTK_WIDGET (footprint_name_entry), "");
        gtk_combo_box_set_active (GTK_WIDGET (footprint_type_entry), 0);
        gtk_combo_box_set_active (GTK_WIDGET (footprint_units_entry), 0);
        gtk_entry_set_text (GTK_WIDGET (footprint_value_entry), "");
        gtk_entry_set_text (GTK_WIDGET (package_body_length_entry), "");
        gtk_entry_set_text (GTK_WIDGET (package_body_width_entry), "");
        gtk_entry_set_text (GTK_WIDGET (package_body_height_entry), "");
        gtk_entry_set_text (GTK_WIDGET (footprint_author_entry), "");
        gtk_combo_box_set_active (GTK_WIDGET (footprint_status_entry), 0);
        gtk_entry_set_text (GTK_WIDGET (footprint_dist_license_entry), "");
        gtk_entry_set_text (GTK_WIDGET (footprint_use_license_entry), "");
        /* Set checkbuttons to their initial state on tab 1 "Footprint" */
        gtk_toggle_button_set_active (package_is_radial_checkbutton, FALSE);
        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_total_pins_entry = NULL;
        GtkWidget *number_of_rows_entry = NULL;
        GtkWidget *number_of_columns_entry = NULL;
        GtkWidget *pitch_x_entry = NULL;
        GtkWidget *pitch_y_entry = NULL;
        GtkWidget *pad_shape_entry = NULL;
        GtkWidget *number_1_position_entry = NULL;
        GtkWidget *pad_diameter_entry = NULL;
        GtkWidget *pin_drill_diameter_entry = NULL;
        GtkWidget *pin1_square_checkbutton = NULL;
        GtkWidget *pad_length_entry = NULL;
        GtkWidget *pad_width_entry = NULL;
        GtkWidget *pad_clearance_entry = NULL;
        GtkWidget *pad_solder_mask_clearance_entry = NULL;
        /* Look up widgets on tab 2 "Pins/Pads"*/
        number_total_pins_entry = lookup_widget (GTK_BUTTON (button),
                "number_total_pins_entry");
        number_of_rows_entry = lookup_widget (GTK_BUTTON (button),
                "number_of_rows_entry");
        number_of_columns_entry = lookup_widget (GTK_BUTTON (button),
                "number_of_columns_entry");
        pitch_x_entry = lookup_widget (GTK_BUTTON (button), "pitch_x_entry");
        pitch_y_entry = lookup_widget (GTK_BUTTON (button), "pitch_y_entry");
        pad_shape_entry = lookup_widget (GTK_BUTTON (button),
                "pad_shape_entry");
        number_1_position_entry = lookup_widget (GTK_BUTTON (button),
                "number_1_position_entry");
        pad_diameter_entry = lookup_widget (GTK_BUTTON (button),
                "pad_diameter_entry");
        pin_drill_diameter_entry = lookup_widget (GTK_BUTTON (button),
                "pin_drill_diameter_entry");
        pin1_square_checkbutton = lookup_widget (GTK_BUTTON (button),
                "pin_square_checkbutton");
        pad_length_entry = lookup_widget (GTK_BUTTON (button),
                "pad_length_entry");
        pad_width_entry = lookup_widget (GTK_BUTTON (button),
                "pad_width_entry");
        pad_clearance_entry = lookup_widget (GTK_BUTTON (button),
                "pad_clearance_entry");
        pad_solder_mask_clearance_entry = lookup_widget (GTK_BUTTON (button),
                "pad_solder_mask_clearance_entry");
        /* Clear entries (remove characters) on tab 2 "Pins/Pads" */
        gtk_entry_set_text (GTK_WIDGET (number_total_pins_entry), "");
        gtk_entry_set_text (GTK_WIDGET (number_of_rows_entry), "");
        gtk_entry_set_text (GTK_WIDGET (number_of_columns_entry), "");
        gtk_entry_set_text (GTK_WIDGET (pitch_x_entry), "");
        gtk_entry_set_text (GTK_WIDGET (pitch_y_entry), "");
        gtk_combo_box_set_active (GTK_WIDGET (pad_shape_entry), 0);
        gtk_combo_box_set_active (GTK_WIDGET (number_1_position_entry), 0);
        gtk_entry_set_text (GTK_WIDGET (pad_diameter_entry), "");
        gtk_entry_set_text (GTK_WIDGET (pin_drill_diameter_entry), "");
        gtk_entry_set_text (GTK_WIDGET (pad_length_entry), "");
        gtk_entry_set_text (GTK_WIDGET (pad_width_entry), "");
        gtk_entry_set_text (GTK_WIDGET (pad_clearance_entry), "");
        gtk_entry_set_text (GTK_WIDGET (pad_solder_mask_clearance_entry), "");
        /* Set any checkbuttons to their initial state on tab 2 "Pins/Pads" */
        gtk_toggle_button_set_active (pin1_square_checkbutton, FALSE);
        /* Widgets on tab 3 "Thermal Pad" */
        GtkWidget *thermal_checkbutton = NULL;
        GtkWidget *thermal_nopaste_checkbutton = NULL;
        GtkWidget *thermal_length_entry = NULL;
        GtkWidget *thermal_width_entry = NULL;
        GtkWidget *thermal_clearance_entry = NULL;
        GtkWidget *thermal_solder_mask_clearance_entry = NULL;
        /* Look up widgets on tab 3 "Thermal Pad" */
        thermal_checkbutton = lookup_widget (GTK_BUTTON (button),
                "thermal_checkbutton");
        thermal_nopaste_checkbutton = lookup_widget (GTK_BUTTON (button),
                "thermal_nopaste_checkbutton");
        thermal_length_entry = lookup_widget (GTK_BUTTON (button),
                "thermal_length_entry");
        thermal_width_entry = lookup_widget (GTK_BUTTON (button),
                "thermal_width_entry");
        thermal_clearance_entry = lookup_widget (GTK_BUTTON (button),
                "thermal_clearance_entry");
        thermal_solder_mask_clearance_entry = lookup_widget (GTK_BUTTON (button),
                "thermal_solder_mask_clearance_entry");
        /* Clear entries (remove characters) on tab 3 "Thermal Pad" */
        gtk_entry_set_text (GTK_WIDGET (thermal_length_entry), "");
        gtk_entry_set_text (GTK_WIDGET (thermal_width_entry), "");
        gtk_entry_set_text (GTK_WIDGET (thermal_clearance_entry), "");
        gtk_entry_set_text (GTK_WIDGET (thermal_solder_mask_clearance_entry), "");
        /* Set any entries, which have a default value, to that value on
         * tab 3 "thermal Pads" */
        /* Set any checkbuttons to their initial state on tab 3 "Thermal Pad" */
        gtk_toggle_button_set_active (thermal_checkbutton, FALSE);
        gtk_toggle_button_set_active (thermal_nopaste_checkbutton, FALSE);
        gtk_widget_set_sensitive (thermal_length_entry, FALSE);
        gtk_widget_set_sensitive (thermal_width_entry, FALSE);
        gtk_widget_set_sensitive (thermal_clearance_entry, FALSE);
        gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, FALSE);
        /* Widgets on tab 4 "Silkscreen" */
        GtkWidget *silkscreen_package_outline_checkbutton = NULL;
        GtkWidget *silkscreen_line_width_entry = NULL;
        GtkWidget *silkscreen_indicate_1_checkbutton = NULL;
        GtkWidget *courtyard_checkbutton = NULL;
        GtkWidget *courtyard_length_entry = NULL;
        GtkWidget *courtyard_width_entry = NULL;
        GtkWidget *courtyard_line_width_entry = NULL;
        GtkWidget *courtyard_clearance_with_package_entry = NULL;
        /* Look up widgets on tab 4 "Silkscreen" */
        silkscreen_package_outline_checkbutton = lookup_widget (GTK_BUTTON (button),
                "silkscreen_package_outline_checkbutton");
        silkscreen_line_width_entry = lookup_widget (GTK_BUTTON (button),
                "silkscreen_line_width_entry");
        silkscreen_indicate_1_checkbutton = lookup_widget (GTK_BUTTON (button),
                "silkscreen_indicate_1_checkbutton");
        courtyard_checkbutton = lookup_widget (GTK_BUTTON (button),
                "courtyard_checkbutton");
        courtyard_length_entry = lookup_widget (GTK_BUTTON (button),
                "courtyard_length_entry");
        courtyard_width_entry = lookup_widget (GTK_BUTTON (button),
                "courtyard_width_entry");
        courtyard_line_width_entry = lookup_widget (GTK_BUTTON (button),
                "courtyard_line_width_entry");
        courtyard_clearance_with_package_entry = lookup_widget (GTK_BUTTON (button),
                "courtyard_clearance_with_package_entry");
        /* Clear entries (remove characters) on tab 4 "Silkscreen" */
        gtk_entry_set_text (GTK_WIDGET (silkscreen_line_width_entry), "");
        gtk_entry_set_text (GTK_WIDGET (courtyard_length_entry), "");
        gtk_entry_set_text (GTK_WIDGET (courtyard_width_entry), "");
        gtk_entry_set_text (GTK_WIDGET (courtyard_line_width_entry), "");
        gtk_entry_set_text (GTK_WIDGET (courtyard_clearance_with_package_entry), "");
        /* Set any checkbuttons to their initial state on tab 4 "Silkscreen" */
        gtk_toggle_button_set_active (silkscreen_package_outline_checkbutton, FALSE);
        gtk_toggle_button_set_active (silkscreen_indicate_1_checkbutton, FALSE);
        gtk_toggle_button_set_active (courtyard_checkbutton, FALSE);
        /* Widgets on tab 5 "Silkscreen" */
        GtkWidget *C1_entry = NULL;
        GtkWidget *C2_entry = NULL;
        GtkWidget *G1_entry = NULL;
        GtkWidget *G2_entry = NULL;
        GtkWidget *Z1_entry = NULL;
        GtkWidget *Z2_entry = NULL;
        GtkWidget * C1_radiobutton;
        GtkWidget * C2_radiobutton;
        /* Look up widgets on tab 5 "Heel & Toe Goals" */
        C1_entry = lookup_widget (GTK_BUTTON (button), "C1_entry");
        C2_entry = lookup_widget (GTK_BUTTON (button), "C2_entry");
        G1_entry = lookup_widget (GTK_BUTTON (button), "G1_entry");
        G2_entry = lookup_widget (GTK_BUTTON (button), "G2_entry");
        Z1_entry = lookup_widget (GTK_BUTTON (button), "Z1_entry");
        Z2_entry = lookup_widget (GTK_BUTTON (button), "Z2_entry");
        C1_radiobutton = lookup_widget (GTK_BUTTON (button), "C1_radiobutton");
        C2_radiobutton = lookup_widget (GTK_BUTTON (button), "C2_radiobutton");
        /* Clear entries (remove characters) on tab 5 "Heel & Toe Goals" */
        gtk_entry_set_text (GTK_WIDGET (C1_entry), "");
        gtk_entry_set_text (GTK_WIDGET (C2_entry), "");
        gtk_entry_set_text (GTK_WIDGET (G1_entry), "");
        gtk_entry_set_text (GTK_WIDGET (G2_entry), "");
        gtk_entry_set_text (GTK_WIDGET (Z1_entry), "");
        gtk_entry_set_text (GTK_WIDGET (Z2_entry), "");
        /* Set any entries to their initial state on tab 5 "Heel & Toe Goals" */
        gtk_widget_set_sensitive (C1_entry, TRUE);
        gtk_widget_set_sensitive (C2_entry, TRUE);
        gtk_widget_set_sensitive (G1_entry, FALSE);
        gtk_widget_set_sensitive (G2_entry, FALSE);
        gtk_widget_set_sensitive (Z1_entry, FALSE);
        gtk_widget_set_sensitive (Z2_entry, FALSE);
        /* Set any checkbuttons to their initial state on tab 5 "Heel & Toe Goals" */
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C1_radiobutton), TRUE);
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (C2_radiobutton), TRUE);

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
 * \brief The "courtyard" checkbutton is toggled.
 *
 * - get active state.
 * - store in the \c courtyard variable (global).
 */
void
on_courtyard_checkbutton_toggled       (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        GtkWidget *courtyard_line_width_entry = NULL;
        GtkWidget *courtyard_length_entry = NULL;
        GtkWidget *courtyard_width_entry = NULL;
        GtkWidget *courtyard_clearance_with_package_entry = NULL;

        /* Save the state of checkbutton in a global variable */
        courtyard = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        /* Look up widgets */
        courtyard_line_width_entry = lookup_widget (GTK_BUTTON (togglebutton), "courtyard_line_width_entry");
        courtyard_length_entry = lookup_widget (GTK_BUTTON (togglebutton), "courtyard_length_entry");
        courtyard_width_entry = lookup_widget (GTK_BUTTON (togglebutton), "courtyard_width_entry");
        courtyard_clearance_with_package_entry = lookup_widget (GTK_BUTTON (togglebutton), "courtyard_clearance_with_package_entry");
        /* Set entities to (in)sensitive according to the state of the
         * checkbutton variable */
        gtk_widget_set_sensitive (courtyard_line_width_entry, courtyard);
        gtk_widget_set_sensitive (courtyard_length_entry, courtyard);
        gtk_widget_set_sensitive (courtyard_width_entry, courtyard);
        gtk_widget_set_sensitive (courtyard_clearance_with_package_entry, courtyard);
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
        gchar *courtyard_clearance_with_package_string = NULL;
        gchar *leftovers;

        courtyard_clearance_with_package_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        courtyard_clearance_with_package = g_ascii_strtod (courtyard_clearance_with_package_string, &leftovers);
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
        gchar *courtyard_length_string = NULL;
        gchar *leftovers;

        courtyard_length_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        courtyard_length = g_ascii_strtod (courtyard_length_string, &leftovers);
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
        gchar *courtyard_line_width_string = NULL;
        gchar *leftovers;

        courtyard_line_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        courtyard_line_width = g_ascii_strtod (courtyard_line_width_string, &leftovers);
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
        gchar *courtyard_width_string = NULL;
        gchar *leftovers;

        courtyard_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        courtyard_width = g_ascii_strtod (courtyard_width_string, &leftovers);
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
}


/*!
 * \brief The "footprint type" entry is changed.
 *
 * - store in the \c footprint_type variable (global).
 */
void
on_footprint_type_entry_changed        (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        footprint_type = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
}


/*!
 * \brief The "footprint units" entry is changed.
 *
 * - store in the \c footprint_units variable (global).
 */
void
on_footprint_units_entry_changed       (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        footprint_units = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
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
        gchar *number_of_columns_string = NULL;
        gchar *leftovers;

        number_of_columns_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        number_of_columns = (int) g_ascii_strtod (number_of_columns_string, &leftovers);
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
        gchar *number_of_rows_string = NULL;
        gchar *leftovers;

        number_of_rows_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        number_of_rows = (int) g_ascii_strtod (number_of_rows_string, &leftovers);
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
        gchar *number_of_pins_string = NULL;
        gchar *leftovers;

        number_of_pins_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        number_of_pins = (int) g_ascii_strtod (number_of_pins_string, &leftovers);
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
        gchar *package_body_height_string = NULL;
        gchar *leftovers;

        package_body_height_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        package_body_height = g_ascii_strtod (package_body_height_string, &leftovers);
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
        gchar *package_body_length_string = NULL;
        gchar *leftovers;

        package_body_length_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        package_body_length = g_ascii_strtod (package_body_length_string, &leftovers);
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
        gchar *package_body_width_string = NULL;
        gchar *leftovers;

        package_body_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        package_body_width = g_ascii_strtod (package_body_width_string, &leftovers);
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
        gchar *pad_clearance_string = NULL;
        gchar *leftovers;

        pad_clearance_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pad_clearance = g_ascii_strtod (pad_clearance_string, &leftovers);
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
        gchar *pad_diameter_string = NULL;
        gchar *leftovers;

        pad_diameter_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pad_diameter = g_ascii_strtod (pad_diameter_string, &leftovers);
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
        gchar *pad_length_string = NULL;
        gchar *leftovers;

        pad_length_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pad_length = g_ascii_strtod (pad_length_string, &leftovers);
}


/*!
 * \brief The "shape of pads" entry is changed.
 *
 * - store in the \c pad_shape variable (global).
 */
void
on_pad_shape_entry_changed    (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        pad_shape = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
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
        gchar *pad_SMC_string = NULL;
        gchar *leftovers;

        pad_SMC_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pad_solder_mask_clearance = g_ascii_strtod (pad_SMC_string, &leftovers);
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
 * \brief The "width of the pads (Y)" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c pad_with variable (global).
 */
void
on_pad_width_entry_changed             (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *pad_width_string = NULL;
        gchar *leftovers;

        pad_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pad_width = g_ascii_strtod (pad_width_string, &leftovers);
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
        gchar *pin_drill_diameter_string = NULL;
        gchar *leftovers;

        pin_drill_diameter_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pin_drill_diameter = g_ascii_strtod (pin_drill_diameter_string, &leftovers);
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
}

/*!
 * \brief The "Pitch (X)" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c e2 variable (global).
 */
void
on_pitch_x_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *pitch_x_string = NULL;
        gchar *leftovers;

        pitch_x_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pitch_x = g_ascii_strtod (pitch_x_string, &leftovers);
}


/*!
 * \brief The "Pitch (y)" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c e1 variable (global).
 */
void
on_pitch_y_entry_changed               (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *pitch_y_string = NULL;
        gchar *leftovers;

        pitch_y_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pitch_y = g_ascii_strtod (pitch_y_string, &leftovers);
}

/*!
 * \brief The "Refresh" button is clicked.
 *
 * - create a pixmap of the footprint.
 * - reload the preview image.
 *
 * \todo Code me !
 */
void
on_refresh_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}

/*!
 * \brief The "Save" button is clicked.
 *
 * - determine the name of the footprintwizard filename.
 * - determine the name of the footprint filename.
 * - invoke the write_footprintwizard_file() to write the global variables to
 *   the footprintwizard file, with a .fpw suffix, for debugging and other
 *   (future) purposes.
 * - invoke the write_footprint() function to write the actual footprint
 *   file.\n
 *
 * \todo When this wizard becomes really quit popular, we can write a function to
 * read from these files as to allow for editing or any other (futuristic)
 * purpose you can think of.
 */
void
on_save_button_clicked                 (GtkButton       *button,
                                        gpointer         user_data)
{
        /* Determine a filename for the footprintwizard file */
        fpw_filename = g_strdup (footprint_name);
        if (g_str_has_suffix (fpw_filename, fp_suffix))
        {
                /* Filename has the .fp suffix already,
                 * only add a "w" here, else we would end up with a filename
                 * like "footprint_name.fp.fpw" */
                fpw_filename = g_strconcat (fpw_filename, "w", NULL);
        }
        else
        {
                if (g_str_has_suffix (fpw_filename, fpw_suffix))
                {
                        /* Filename has the .fpw suffix,
                         * do nothing here */
                }
                else
                {
                        /* Filename has no (.fpw) suffix,
                         * add a .fpw suffix */
                        fpw_filename = g_strconcat (fpw_filename, ".fpw", NULL);
                }
        }
        /* Determine a filename for the actual footprint file */
        footprint_filename = g_strdup (footprint_name);
        if (g_str_has_suffix (footprint_filename, fp_suffix))
        {
                /* Footprintname has the .fp suffix,
                 * do nothing here */
        }
        else
        {
                /* Filename has no .fp suffix,
                 * add a .fp suffix */
                footprint_filename = g_strconcat (footprint_filename, ".fp", NULL);
        }
        write_footprintwizard_file ();
        fprintf (stderr, "Footprintwizardfile %s is written successful.\n", fpw_filename);
        write_footprint ();
        fprintf (stderr, "Footprint %s is written successful.\n", footprint_name);
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
        gchar *silkscreen_line_width_string = NULL;
        gchar *leftovers;

        silkscreen_line_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        silkscreen_line_width = g_ascii_strtod (silkscreen_line_width_string, &leftovers);
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
        GtkWidget *silkscreen_line_width_entry = NULL;

        /* Save the state of checkbutton in global variable */
        silkscreen_package_outline = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        /* Look up widgets */
        silkscreen_line_width_entry = lookup_widget (GTK_BUTTON (togglebutton), "silkscreen_line_width_entry");
        /* Set entities to (in)sensitive according to the state of the
         * checkbutton variable */
        gtk_widget_set_sensitive (silkscreen_line_width_entry, silkscreen_package_outline);
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
        GtkWidget *thermal_length_entry = NULL;
        GtkToggleButton *thermal_nopaste_checkbutton = NULL;
        GtkWidget *thermal_width_entry = NULL;
        GtkWidget *thermal_clearance_entry = NULL;
        GtkWidget *thermal_solder_mask_clearance_entry = NULL;

        /* Save the state of checkbutton in a global variable */
        thermal = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        /* Look up widgets */
        thermal_nopaste_checkbutton = lookup_widget (GTK_BUTTON (togglebutton),
                "thermal_nopaste_checkbutton");
        thermal_length_entry = lookup_widget (GTK_BUTTON (togglebutton),
                "thermal_length_entry");
        thermal_width_entry = lookup_widget (GTK_BUTTON (togglebutton),
                "thermal_width_entry");
        thermal_clearance_entry = lookup_widget (GTK_BUTTON (togglebutton),
                "thermal_clearance_entry");
        thermal_solder_mask_clearance_entry = lookup_widget (GTK_BUTTON (togglebutton),
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
        gchar *thermal_clearance_string = NULL;
        gchar *leftovers;

        thermal_clearance_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        thermal_clearance = g_ascii_strtod (thermal_clearance_string, &leftovers);
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
        gchar *thermal_length_string = NULL;
        gchar *leftovers;

        thermal_length_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        thermal_length = g_ascii_strtod (thermal_length_string, &leftovers);
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
        gchar *SMC_string = NULL;
        gchar *leftovers;

        SMC_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        thermal_solder_mask_clearance = g_ascii_strtod (SMC_string, &leftovers);
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
        gchar *thermal_width_string = NULL;
        gchar *leftovers;

        thermal_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        thermal_width = g_ascii_strtod (thermal_width_string, &leftovers);
}

/* EOF */
