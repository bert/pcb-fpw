/*!
 * \file select_exceptions.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief A widget for selecting exception pin/pads in an array type footprint.
 *
 * This program is free software; you can redistribute it and/or modify\n
 * it under the terms of the GNU General Public License as published by\n
 * the Free Software Foundation; either version 2 of the License, or\n
 * (at your option) any later version.\n
 * \n
 * This program is distributed in the hope that it will be useful,\n
 * but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n
 * See the GNU General Public License for more details.\n
 * \n
 * You should have received a copy of the GNU General Public License\n
 * along with this program; if not, write to:\n
 * the Free Software Foundation, Inc.,\n
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\n
 */


#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>


#define MAX_ROWS 100
#define MAX_COLUMNS 100

/*!
 * \brief Radio button wrapper type.
 */
typedef struct
{
        GtkWidget *radio_select_button;
        gchar *name;
        gboolean active;
        gint id;
} SelectionButtonSet;

static SelectionButtonSet radio_buttons[MAX_ROWS * MAX_COLUMNS];

static gint radio_button_index;

GtkWidget *select_exceptions_window = NULL;
/*!
 * \brief The "Clear" button is clicked.
 *
 * - set the "active" field of all the radio_buttons members to \c TRUE.
 * - set all radio buttons in the GUI to the active state.
 */
static void
select_exceptions_clear_cb
(
        GtkWidget *widget,
        GtkWidget *select_exceptions_window
)
{
        gint i;
        gint j;
        SelectionButtonSet *radio_button;
        radio_button_index = 0;
        for (i = 0; (i < MAX_ROWS); i++)
        {
                for (j = 0; (j < MAX_COLUMNS); j++)
                {
                        radio_button = &radio_buttons[radio_button_index];
                        radio_button->active = TRUE;
                        radio_button_index++;
                }
        }
        pin_pad_exceptions_string = g_strdup ("");
        /* Set the existing array of radiobuttons to active. */
        radio_button_index = 0;
        for (i = 0; (i < number_of_rows); i++)
        {
                for (j = 0; (j < number_of_columns); j++)
                /* all columns of a row [1 .. n]
                 * where j is a member of the positive Natural numbers (N) */
                {
                        radio_button = &radio_buttons[radio_button_index];
                        radio_button->active = TRUE;
                        gtk_toggle_button_set_active
                                (GTK_TOGGLE_BUTTON (radio_button->radio_select_button),
                                TRUE);
                        radio_button_index++;
                }
        }
}


/*!
 * \brief The "Close" button is clicked.
 *
 * - close the window (destroy the widget).
 */
static void
select_exceptions_close_cb
(
        GtkWidget *widget,
        GtkWidget *window
)
{
        gtk_widget_destroy (window);
        select_exceptions_window = NULL;
}


/*!
 * \brief Delete the window.
 */
void
select_exceptions_delete_event
(
        GtkWidget *widget,
        GdkEvent *event
)
{
        gtk_widget_destroy (widget);
        select_exceptions_window = NULL;
}


/*!
 * \brief The "OK" button is clicked.
 *
 * - save the state of all toggle (radio) buttons.
 * - close the window (destroy the widget).
 */
static void
select_exceptions_ok_cb
(
        GtkWidget *widget,
        GtkWidget *select_exceptions_window
)
{
        /* Lookup all togglebuttons and save the state in the exceptions
         * array. */
        gint i;
        gint j;
        SelectionButtonSet *radio_button;
        radio_button_index = 0;
        gchar *exceptions = g_strdup ("");
        for (i = 0; (i < number_of_rows); i++)
        /* one row at a time [A .. Y, AA .. YY] etc.
         * where i is one or more letters of the alphabet,
         * excluding "I", "O", "Q", "S" and "Z" */
        {
                for (j = 0; (j < number_of_columns); j++)
                /* all columns of a row [1 .. n]
                 * where j is a member of the positive Natural numbers (N) */
                {
                        gchar *radio_button_name = g_strdup_printf ("%s%d",
                                (row_letters[i]), (j + 1));
                        radio_button = &radio_buttons[radio_button_index];
                        if (radio_button->active)
                        {
                                exceptions = g_strconcat (exceptions,
                                        radio_button->name, ",", NULL);
                        }
                        radio_button_index++;
                        g_free (radio_button_name);
                }
        }
        pin_pad_exceptions_string = g_strdup (exceptions);
        /*!
         * \todo How to update the pin_pad_exceptions_entry in the main
         * window ? */
        g_free (exceptions);
        gtk_widget_destroy (select_exceptions_window);
}


/*!
 * \brief One of the radio buttons is toggled.
 *
 * - lookup the radio button in the array \c radio_button.
 * - save the state of the radio button in \c radio_button->active.
 *
 * \todo Radio buttons seem to be a poor choice here.
 * The look of the radio button is highly wanted for it
 * resembles a PGA pin/BGA pad in the GUI.
 * OTOH, the behaviour of the button is that once clicked (TRUE)
 * it doesn't get reset (FALSE) when clicked again.
 * This has to be solved with code in the callback
 * (if possible at all), or switch to GtkCheckButtons ?
 */
static void
select_exceptions_radio_button_toggled_cb
(
        GtkWidget *widget,
        GtkWidget *select_exceptions_window
)
{
        const gchar *widget_name;
        SelectionButtonSet *radio_button;
        radio_button_index = -1;
        widget_name = gtk_widget_get_name (widget);
        do
        {
                radio_button_index++;
                radio_button = &radio_buttons[radio_button_index];
        } while (strcmp (widget_name, radio_button->name));
        radio_button->active = gtk_toggle_button_get_active (widget);
}


/*!
 * \brief Create a selection exceptions window.
 *
 * - create only one single window with a title "select exceptions".
 * - depending on the package type create the pattern of radio buttons.
 * - add "Close", "Clear" and "OK" stock buttons.
 */
int
select_exceptions_create_window
(
        gint number_of_rows,
        gint number_of_columns
)
{
        /* Return if a "select exceptions" window exist. */
        if (select_exceptions_window)
        {
                return (EXIT_FAILURE);
        }
        /* Create a dialog window */
        select_exceptions_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        /* Destroy the preview window when the main window of pcb-gfpw gets
         * destroyed */
        gtk_window_set_destroy_with_parent (GTK_WINDOW (select_exceptions_window), TRUE);
        /* Set the window title */
        gchar *window_title = g_strdup ("select exceptions");
        gtk_window_set_title (GTK_WINDOW (select_exceptions_window), window_title);
        g_free (window_title);
        gtk_container_set_border_width (GTK_CONTAINER (select_exceptions_window), 10);
        /* Set signals for the window */
        gtk_signal_connect
        (
                GTK_OBJECT (select_exceptions_window),
                "delete_event",
                (GtkSignalFunc) select_exceptions_delete_event,
                NULL
        );
        /* Create a vertical box with a table of radiobuttons and a button
         * box with a "close", a "clear" and an "apply" button. */
        GtkWidget *vbox = gtk_vbox_new (FALSE, 10);
        gtk_container_add (GTK_CONTAINER (select_exceptions_window),
                GTK_WIDGET (vbox));
        /* Create a table with radiobuttons depicting the pins/pads of the
         * package. */
        GtkWidget *table = gtk_table_new ((number_of_rows + 1),
                (number_of_columns + 1), TRUE);
        gtk_table_set_col_spacings (GTK_TABLE (table), 2);
        gtk_table_set_row_spacings (GTK_TABLE (table), 2);
        /* Write pin and/or pad radio buttons. */
        gint i;
        gint j;
        SelectionButtonSet *radio_button;
        radio_button_index = 0;
        /* Create top row of labels with pin/pad index numbers. */
        for (j = 1; (j < (number_of_columns + 1)); j++)
        {
                GtkWidget *column_label = gtk_label_new (g_strdup_printf ("%d", j));
                gtk_label_set_justify (GTK_LABEL (column_label), GTK_JUSTIFY_CENTER);
                gtk_table_attach_defaults (GTK_TABLE (table), column_label,
                        j, (j + 1),
                        0, 1);
        }
        /* Create array of radiobuttons and add a label at the begin and end
         * of the row stating the pin/pad index (valid) alphabet letter. */
        for (i = 0; (i < number_of_rows); i++)
        /* one row at a time [A .. Y, AA .. YY] etc.
         * where i is one or more letters of the alphabet,
         * excluding "I", "O", "Q", "S" and "Z" */
        {
                GtkWidget *row_label = gtk_label_new (g_strdup_printf ("%s",
                        (row_letters[i])));
                gtk_table_attach_defaults (GTK_TABLE (table), row_label,
                        0, 1,
                        (i + 1), (i + 2));
                for (j = 0; (j < number_of_columns); j++)
                /* all columns of a row [1 .. n]
                 * where j is a member of the positive Natural numbers (N) */
                {
                        radio_button = &radio_buttons[radio_button_index];
                        radio_button->radio_select_button =
                                gtk_radio_button_new (NULL);
                        gtk_widget_show (radio_button->radio_select_button);
                        radio_button->id = radio_button_index;
                        gchar *radio_button_name = g_strdup_printf ("%s%d",
                                (row_letters[i]), (j + 1));
                        radio_button->name = g_strdup (radio_button_name);
                        gtk_widget_set_name (radio_button->radio_select_button,
                                radio_button_name);
                        gtk_table_attach_defaults (GTK_TABLE (table),
                                radio_button->radio_select_button,
                                (j + 1), (j + 2), (i + 1), (i + 2));
                        radio_button->active = !get_pin_pad_exception
                                (radio_button_name);
                        if (!get_pin_pad_exception (radio_button_name))
                        {
                                gtk_toggle_button_set_active
                                        (GTK_TOGGLE_BUTTON (radio_button->radio_select_button),
                                        TRUE);
                        }
                        else
                        {
                                gtk_toggle_button_set_active
                                        (GTK_TOGGLE_BUTTON (radio_button->radio_select_button),
                                        FALSE);
                        }
                        g_signal_connect
                        (
                                G_OBJECT (radio_button->radio_select_button),
                                "clicked",
                                G_CALLBACK (select_exceptions_radio_button_toggled_cb),
                                select_exceptions_window
                        );
                        /*! \todo Maybe connect some signals here ? */
                        radio_button_index++;
                        g_free (radio_button_name);
                }
        }
        /* Create bottom row of labels with pin/pad index numbers. */
        /* Pack the table into the vbox */
        gtk_box_pack_start (GTK_BOX (vbox), table, FALSE, FALSE, 0);

        /* Create a horizontal button box. */
        GtkWidget *hbox = gtk_hbutton_box_new ();
        gtk_container_set_border_width (GTK_CONTAINER (hbox), 10);
        gtk_button_box_set_layout (GTK_BUTTON_BOX (hbox), GTK_BUTTONBOX_SPREAD);
        /* Create a close button. */
        GtkWidget *close_button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
        g_signal_connect
        (
                G_OBJECT (close_button),
                "clicked",
                G_CALLBACK (select_exceptions_close_cb),
                select_exceptions_window
        );
        /* Pack the button into the hbox */
        gtk_box_pack_start (GTK_BOX (hbox), close_button, TRUE, TRUE, 0);
        /* Create a clear button. */
        GtkWidget *clear_button = gtk_button_new_from_stock (GTK_STOCK_CLEAR);
        g_signal_connect
        (
                G_OBJECT (clear_button),
                "clicked",
                G_CALLBACK (select_exceptions_clear_cb),
                select_exceptions_window
        );
        /* Pack the button into the hbox */
        gtk_box_pack_start (GTK_BOX (hbox), clear_button, TRUE, TRUE, 0);
        /* Create an OK button. */
        GtkWidget *ok_button = gtk_button_new_from_stock (GTK_STOCK_OK);
        g_signal_connect
        (
                G_OBJECT (ok_button),
                "clicked",
                G_CALLBACK (select_exceptions_ok_cb),
                select_exceptions_window
        );
        /* Pack the button into the hbox */
        gtk_box_pack_start (GTK_BOX (hbox), ok_button, TRUE, TRUE, 0);
        /* Pack the hbox into the vbox */
        gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);


        gtk_window_set_resizable (GTK_WINDOW (select_exceptions_window), FALSE);
        /* Show the window */
        gtk_widget_realize (select_exceptions_window);
        gtk_widget_show_all (select_exceptions_window);
        /* Enter the GTK main loop */
        gtk_main ();
        return 0;
}

/* EOF */
