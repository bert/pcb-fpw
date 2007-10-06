/*!
 * \file callbacks.c
 * \author Copyright (C) 2007 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Callback functions for the gFootprintWizard.
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
 * \brief The top to bottom pads/pins center-center distance (C1) entry is
 * changed, store in c1.
 *
 * The top to bottom pads/pins center-center distance (C1) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the c1 variable (global).
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
 * \brief The top to bottom pads/pins center-center distance (C1) radiobutton
 * is clicked, set inner-inner (G1) and outer-outer (Z1) entries to
 * insensitive.
 *
 * The top to bottom pads/pins center-center distance (C1) radiobutton
 * is clicked.
 * - set center-center (C1) entry to sensitive.
 * - set the inner-inner (G1) and outer-outer (Z1) entries to insensitive.
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
 * \brief The left to right pads/pins center-center distance (C2) entry is
 * changed, store in c2.
 *
 * The left to right pads/pins center-center distance (C2) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the c2 variable (global).
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
 * \brief The left to right pads/pins center-center distance (C2) radiobutton
 * is clicked, set inner-inner (G2) and outer-outer (Z2) entries to
 * insensitive.
 *
 * The left to right pads/pins center-center distance (C2) radiobutton
 * is clicked.
 * - set center-center (C2) entry to sensitive.
 * - set inner-inner (G2) and outer-outer (Z2) entries to insensitive.
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
 * \brief The vertical spacing of the pads/pins (E1) entry is changed,
 * store in e1.
 *
 * The vertical spacing of the pads/pins (E1) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the e1 variable (global).
 */
void
on_E1_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *E1_string = NULL;
        gchar *leftovers;

        E1_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        e1 = g_ascii_strtod (E1_string, &leftovers);
}


/*!
 * \brief The horizontal spacing of the pads/pins (E2) entry is changed,
 * store in e2.
 *
 * The horizontal spacing of the pads/pins (E2) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the e2 variable (global).
 */
void
on_E2_entry_changed                    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *E2_string = NULL;
        gchar *leftovers;

        E2_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        e2 = g_ascii_strtod (E2_string, &leftovers);
}


/*!
 * \brief The top to bottom pads/pins inner-inner distance (G1) entry is
 * changed, store in g1.
 *
 * The top to bottom pads/pins inner-inner distance (G1) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the g1 variable (global).
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
 * is clicked, set center-center (C1) and outer-outer (Z1) entries to
 * insensitive.
 *
 * The top to bottom pads/pins inner-inner distance (G1) radiobutton
 * is clicked.
 * - set inner-inner (G1) entry to sensitive.
 * - set the center-center (C1) and outer-outer (Z1) entries to insensitive.
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
 * changed, store in g2.
 *
 * The left to right pads/pins inner-inner distance (G2) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the g2 variable (global).
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
 * is clicked, set center-center (C2) and outer-outer (Z2) entries to
 * insensitive.
 *
 * The left to right pads/pins inner-inner distance (G2) radiobutton
 * is clicked.
 * - set inner-inner (G2) entry to sensitive.
 * - set center-centr (C2) and outer-outer (Z2) entries to insensitive.
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
 * changed, store in z1.
 *
 * The top to bottom pads/pins outer-outer distance (Z1) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the z1 variable (global).
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
 * is clicked, set center-center (C1) and inner-inner distance (G1) entries to
 * insensitive.
 *
 * The top to bottom pads/pins outer-outer (Z1) radiobutton
 * is clicked.
 * - set the outer-outer (Z1) entry to sensitive.
 * - set the center-center (C1) and inner-inner (G1) entries to insensitive.
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
 * changed, store in z2.
 *
 * The left to right pads/pins outer-outer distance (Z2) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the z2 variable (global).
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
 * is clicked, set center-center (C2) and inner-inner distance (G2) entries to
 * insensitive.
 *
 * The left to right pads/pins outer-outer (Z2) radiobutton is clicked.
 * - set center-center (C2) and inner-inner distance (G2) entries to
 * insensitive.
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
 * \brief The "Close" button is clicked, close the application.
 *
 */
void
on_close_button_clicked                (GtkButton       *button,
                                        gpointer         user_data)
{
        /* Do we really want to quit ? */
        gtk_main_quit();
}


/*!
 * \brief The line width entry of the courtyard is changed,
 * store in courtyard_line_thickness.
 *
 * The line width entry of the courtyard is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the courtyard_line_thickness variable
 * (global).
 */
void
on_courtyard_line_thickness_entry_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *courtyard_line_width_string = NULL;
        gchar *leftovers;

        courtyard_line_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        courtyard_line_width = g_ascii_strtod (courtyard_line_width_string, &leftovers);
}


/*!
 * \brief The footprint name entry is changed, store in footprint_name.
 *
 * The footprint name entry is changed.
 * - store in the footprint_name variable (global).
 */
void
on_footprint_name_entry_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        footprint_name = gtk_entry_get_text (GTK_EDITABLE (editable));
}


/*!
 * \brief The footprint type entry is changed, store in footprint_type.
 *
 * The footprint type entry is changed.
 * - store in the footprint_type variable (global).
 */
void
on_footprint_type_entry_changed        (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        footprint_type = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
}


/*!
 * \brief The footprint units entry is changed, store in footprint_units.
 *
 * The footprint units entry is changed.
 * - store in the footprint_units variable (global).
 */
void
on_footprint_units_entry_changed       (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        footprint_units = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
}


/*!
 * \brief The top-right "X" is clicked, close the application.
 *
 */
void
on_gFootprintWizard_destroy            (GtkObject       *object,
                                        gpointer         user_data)
{
        gtk_main_quit();
}


/*!
 * \brief The horizontal courtyard dimension (V1) entry is changed, store in
 * v1.
 *
 * The horizontal courtyard dimension (V1) entry is changed, .
 * - get the chars from the entry.
 * - convert to a double and store in the v1 variable (global).
 */
void
on_horizontal_courtyard_entry_changed  (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *V1_string = NULL;
        gchar *leftovers;

        V1_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        v1 = g_ascii_strtod (V1_string, &leftovers);
}


/*!
 * \brief The horizontal silkscreen dimension (R2) entry is changed, store in
 * r2.
 *
 * The horizontal silkscreen dimension (R2) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the r2 variable (global).
 */
void
on_horizontal_silkscreen_entry_changed (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *R2_string = NULL;
        gchar *leftovers;

        R2_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        r2 = g_ascii_strtod (R2_string, &leftovers);
}


/*!
 * \brief The position of number 1 pad/pin entry is changed, store in n1_pos.
 *
 * The position of number 1 pad/pin entry is changed.
 * - store in the n1_pos variable (global).
 */
void
on_number_1_position_combobox_entry_changed
                                        (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        n1_pos = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
}


/*!
 * \brief The number of columns (n_col) entry is changed,
 * store in n_col.
 *
 * The number of columns (n_col) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the n_col variable (global).
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
 * \brief The number of rows (n_row) entry is changed,
 * store in n_row.
 *
 * The number of rows (n_row) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the n_row variable (global).
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
 * \brief The number of pads/pins (N) entry is changed,
 * store in n.
 *
 * The number of pads/pins (N) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the n variable (global).
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
 * \brief The "OK" button is clicked, write the footprint to file.
 *
 * The "OK" button is clicked, make preparations to write the footprint to
 * file.
 * - write the global variables to a footprintwizard file, with a .fpw
 * suffix, for debugging purposes.
 * - invoke the write_footprint() function to write the actual footprint
 * file.
 * When this wizard becomes really quit popular, we can write a function to
 * read from these files as to allow for editing or any other purpose you can
 * think of.
 */
void
on_ok_button_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
        FILE *fp;
        gchar *suffix = ".fp";

        /* Write global variables to footprintwizard file with .fpw suffix */
        if (g_str_has_suffix (footprint_name, suffix))
        {
                /* Footprintname has a .fp suffix, add a w */
                footprint_filename = g_strconcat (footprint_name, "w", NULL);
        }
        else
        {
                /* Footprintname has no .fp suffix, add a .fpw suffix */
                footprint_filename = g_strconcat (footprint_name, ".fpw", NULL);
        }
        if (fp = g_fopen (footprint_filename, "w"))
        {
                fprintf (fp, "%s\n", footprint_filename);
                fprintf (fp, "%s\n", footprint_name);
                fprintf (fp, "%s\n", footprint_type);
                fprintf (fp, "%s\n", footprint_units);
                fprintf (fp, "%s\n", n1_pos);
                fprintf (fp, "%s\n", pad_shape);
                fprintf (fp, "%d\n", n);
                fprintf (fp, "%d\n", n_col);
                fprintf (fp, "%d\n", n_row);
                fprintf (fp, "%f\n", x);
                fprintf (fp, "%f\n", y);
                fprintf (fp, "%f\n", d_pad);
                fprintf (fp, "%f\n", d_hole);
                fprintf (fp, "%f\n", c1);
                fprintf (fp, "%f\n", g1);
                fprintf (fp, "%f\n", z1);
                fprintf (fp, "%f\n", c2);
                fprintf (fp, "%f\n", g2);
                fprintf (fp, "%f\n", z2);
                fprintf (fp, "%f\n", e1);
                fprintf (fp, "%f\n", e2);
                fprintf (fp, "%f\n", solder_mask_clearance);
                fprintf (fp, "%f\n", r1);
                fprintf (fp, "%f\n", r2);
                fprintf (fp, "%f\n", silkscreen_line_width);
                fprintf (fp, "%f\n", v1);
                fprintf (fp, "%f\n", v2);
                fprintf (fp, "%f\n", courtyard_line_width);
                fprintf (fp, "%d\n", thermal);
                fprintf (fp, "%f\n", thermal_x);
                fprintf (fp, "%f\n", thermal_y);
                fprintf (fp, "%f\n", thermal_solder_mask_clearance);
        }
        close (fp);
        /* Pass control to libfpw */
        write_footprint ();
        fprintf (stderr, "Footprint %s is written successful.", footprint_name);
}


/*!
 * \brief The diameter of the pad (D) entry is changed,
 * store in d_pad.
 *
 * The diameter of the pad (D) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the d_pad variable (global).
 */
void
on_pad_diameter_entry_changed          (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *D_string = NULL;
        gchar *leftovers;

        D_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        d_pad = g_ascii_strtod (D_string, &leftovers);
}


/*!
 * \brief The length of the pads (X) entry is changed, store in x.
 *
 * The length of the pads (X) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the x variable (global).
 */
void
on_pad_length_entry_changed           (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *X_string = NULL;
        gchar *leftovers;

        X_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        x = g_ascii_strtod (X_string, &leftovers);
}


/*!
 * \brief The shape pads entry is changed, store in pad_shape.
 *
 * The shape of pads entry is changed.
 * - store in the pad_shape variable (global).
 */
void
on_pad_shape_combobox_entry_changed   (GtkComboBox     *combobox,
                                        gpointer         user_data)
{
        pad_shape = gtk_combo_box_get_active_text (GTK_COMBO_BOX (combobox));
}


/*!
 * \brief The solder mask clearance of the pads (SMC) entry is changed,
 * store in SMC.
 *
 * The solder mask clearance of the pads (SMC) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the SMC variable (global).
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
 * \brief The width of the pads (Y) entry is changed, store in y.
 *
 * The width of the pads (Y) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the y variable (global).
 */
void
on_pad_width_entry_changed            (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *Y_string = NULL;
        gchar *leftovers;

        Y_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        y = g_ascii_strtod (Y_string, &leftovers);
}


/*!
 * \brief The diameter of the drill holes (d) entry is changed,
 * store in d_hole.
 *
 * The diameter of the drill holes (d) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the d_hole variable (global).
 */
void
on_pin_drill_diameter_entry_changed        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *d_string = NULL;
        gchar *leftovers;

        d_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        d_hole = g_ascii_strtod (d_string, &leftovers);
}


/*!
 * \brief The "Preview" button is clicked, create a pixmap of the footprint
 * and reload the preview image.
 *
 */
void
on_preview_button_clicked              (GtkButton       *button,
                                        gpointer         user_data)
{

}


/*!
 * \brief The line width entry of the silkscreen is changed,
 * store in silkscreen_line_thickness.
 *
 * The line width entry of the silkscreen is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the silkscreen_line_thickness variable
 * (global).
 */
void
on_silkscreen_line_thickness_entry_changed
                                        (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *silkscreen_line_width_string = NULL;
        gchar *leftovers;

        silkscreen_line_width_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        silkscreen_line_width = g_ascii_strtod (silkscreen_line_width_string, &leftovers);
}


/*!
 * \brief The thermal pad checkbutton is clicked,
 * get active state and store in the thermal variable.
 *
 * The thermal pad checkbutton is clicked.
 * - store the state of the checkbutton in the thermal variable (global).
 * - if there is no thermal pad set the length and width entries to insensitive.
 * - if there is a thermal pad set the length and with entries to sensitive.
 */
void
on_thermal_checkbutton_toggled         (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
        GtkWidget *thermal_length_entry = NULL;
        GtkWidget *thermal_width_entry = NULL;
        GtkWidget *thermal_solder_mask_clearance_entry = NULL;

        thermal = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (togglebutton));
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
 * \brief The length entry of the thermal pad is changed,
 * store in thermal_x.
 *
 * The length entry of the thermal pad is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the thermal_x variable (global).
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
 * \brief The solder mask clearance entry of the thermal pad is changed,
 * store in thermal_solder_mask_clearance.
 *
 * The solder mask clearance entry of the thermal pad is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the thermal_solder_clearance variable
 * (global).
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
 * \brief The width entry of the thermal pad is changed,
 * store in thermal_y.
 *
 * The width entry of the thermal pad is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the thermal_y variable (global).
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


/*!
 * \brief The vertical courtyard dimension (V1) entry is changed, store in
 * v1.
 *
 * The vertical courtyard dimension (V1) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the v1 variable (global).
 */
void
on_vertical_courtyard_entry_changed    (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *v1_string = NULL;
        gchar *leftovers;

        v1_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        v1 = g_ascii_strtod (v1_string, &leftovers);
}


/*!
 * \brief The vertical silkscreen dimension (R1) entry is changed, store in
 * r1.
 *
 * The vertical silkscreen dimension (R1) entry is changed.
 * - get the chars from the entry.
 * - convert to a double and store in the r1 variable (global).
 */
void
on_vertical_silkscreen_entry_changed   (GtkEditable     *editable,
                                        gpointer         user_data)
{
        gchar *r1_string = NULL;
        gchar *leftovers;

        r1_string = gtk_entry_get_text (GTK_EDITABLE (editable));
        r1 = g_ascii_strtod (r1_string, &leftovers);
}

/* EOF */
