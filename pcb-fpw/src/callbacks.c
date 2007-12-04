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
 * \todo Code me !
 *
 * - clear all entry fields and set all togglebuttons to the initial state.
 */
void
on_clear_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{

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
        courtyard = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
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
 * - store in the \c footprint_dist_license variable (global).
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
 * \brief The "indicate pin/pad number 1" checkbutton is toggled.
 *
 * - store the state of the checkbutton in the \c silkscreen_indicate_1
 *   variable (global).
 */
void
on_indicate_1_checkbutton_toggled      (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        silkscreen_indicate_1 = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
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
        n1_pos = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
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
        gchar *n_col_string = NULL;
        gchar *leftovers;

        n_col_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        n_col = (int) g_ascii_strtod (n_col_string, &leftovers);
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
        gchar *n_row_string = NULL;
        gchar *leftovers;

        n_row_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        n_row = (int) g_ascii_strtod (n_row_string, &leftovers);
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
        gchar *N_string = NULL;
        gchar *leftovers;

        N_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        n = (int) g_ascii_strtod (N_string, &leftovers);
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
 * \brief The "package outline" checkbutton is toggled.
 *
 * - save the state of the checkbutton in the \c package_outline
 *   variable (global).
 * - if the "package outline" checkbutton is not "checked", set the linewidth
 *   entry to insensitive.
 * - if the "package outline" checkbutton is "checked", set the line width
 *   entry to sensitive.
 */
void
on_package_outline_checkbutton_toggled (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        GtkWidget *silkscreen_line_width_entry = NULL;

        /* Save the state of checkbutton in global variable */
        package_outline = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
        /* Set entities to (in)sensitive according to the state of the
         * checkbutton variable */
        silkscreen_line_width_entry = lookup_widget (GTK_BUTTON (togglebutton), "silkscreen_line_width_entry");
        if (package_outline == FALSE)
        {
                gtk_widget_set_sensitive (silkscreen_line_width_entry, FALSE);
        }
        else
        {
                gtk_widget_set_sensitive (silkscreen_line_width_entry, TRUE);
        }
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
        gchar *SMC_string = NULL;
        gchar *leftovers;

        SMC_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        solder_mask_clearance = g_ascii_strtod (SMC_string, &leftovers);
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
 * - convert to a double and store in the \c d_hole variable (global).
 */
void
on_pin_drill_diameter_entry_changed    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *pin_hole_diameter_string = NULL;
        gchar *leftovers;

        pin_hole_diameter_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        pin_hole_diameter = g_ascii_strtod (pin_hole_diameter_string, &leftovers);
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
        write_footprint ();
        fprintf (stderr, "Footprint %s is written successful.", footprint_name);
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
 * \brief The "thermal pad" checkbutton is toggled.
 *
 * - save the state of the checkbutton in the \c thermal variable (global).
 * - if the "thermal pad" checkbutton is not "checked", set the length and
 *   width entries to insensitive.
 * - if the "thermal pad" checkbutton is "checked", set the length and width
 *   entries to sensitive.
 */
void
on_thermal_checkbutton_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        GtkWidget *thermal_length_entry = NULL;
        GtkWidget *thermal_width_entry = NULL;
        GtkWidget *thermal_solder_mask_clearance_entry = NULL;

        /* Save the state of checkbutton in global variable */
        thermal = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));

        /* Set entities to (in)sensitive according to the state of the
         * checkbutton variable */
        thermal_length_entry = lookup_widget (GTK_BUTTON (togglebutton), "thermal_length_entry");
        thermal_width_entry = lookup_widget (GTK_BUTTON (togglebutton), "thermal_width_entry");
        thermal_solder_mask_clearance_entry = lookup_widget (GTK_BUTTON (togglebutton), "thermal_solder_mask_clearance_entry");
        if (thermal == FALSE)
        {
                gtk_widget_set_sensitive (thermal_length_entry, FALSE);
                gtk_widget_set_sensitive (thermal_width_entry, FALSE);
                gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, FALSE);
        }
        else
        {
                gtk_widget_set_sensitive (thermal_length_entry, TRUE);
                gtk_widget_set_sensitive (thermal_width_entry, TRUE);
                gtk_widget_set_sensitive (thermal_solder_mask_clearance_entry, TRUE);
        }
}


/*!
 * \brief The "thermal pad length" entry is changed.
 *
 * - get the chars from the entry.
 * - convert to a double and store in the \c thermal_x variable (global).
 */
void
on_thermal_length_entry_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *X_string = NULL;
        gchar *leftovers;

        X_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        thermal_x = g_ascii_strtod (X_string, &leftovers);
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
 * - convert to a double and store in the \c thermal_y variable (global).
 */
void
on_thermal_width_entry_changed         (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *Y_string = NULL;
        gchar *leftovers;

        Y_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        thermal_y = g_ascii_strtod (Y_string, &leftovers);
}

/* EOF */
