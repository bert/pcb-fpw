/*!
 * \file select_exceptions.c
 * \author Copyright (C) 2007, 2008, 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief A widget for selecting exception pin/pads in an array type footprint.
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


#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>


#define MAX_ROWS 100
#define MAX_COLUMNS 100

/*!
 * \brief Selection button wrapper type.
 */
typedef struct
{
        GtkWidget *button_widget;
                /*!< : is the button widget appearing in the dialog window.*/
        gchar *name;
                /*!< : is the name of the button widget.*/
        gboolean active;
                /*!< : is the state of the button,*/
        gint id;
                /*!< : is the identificatoion number (sequential) of the
                 * button.*/
} SelectionButtonSet;

static SelectionButtonSet selection_buttons[MAX_ROWS * MAX_COLUMNS];

GtkWidget *select_exceptions_window = NULL;


/*!
 * \brief The "Clear" button is clicked.
 *
 * <ul>
 * <li>set the "active" field of all the selection_buttons members to \c TRUE.
 * <li>set all selection buttons in the GUI to the active state.
 * </ul>
 */
static void
select_exceptions_clear_cb
(
        GtkWidget *widget,
                /*!< : is the caller widget.*/
        GtkWidget *window
                /*!< : is the window widget.*/
)
{
        gint i;
        gint j;
        SelectionButtonSet *selection_button;
        gint selection_button_index = 0;
        for (i = 0; (i < MAX_ROWS); i++)
        {
                for (j = 0; (j < MAX_COLUMNS); j++)
                {
                        selection_button = &selection_buttons[selection_button_index];
                        selection_button->active = FALSE;
                        selection_button_index++;
                }
        }
        pin_pad_exceptions_string = g_strdup ("");
        /* Set the existing array of selection buttons to active. */
        selection_button_index = 0;
        for (i = 0; (i < number_of_rows); i++)
        {
                for (j = 0; (j < number_of_columns); j++)
                /* all columns of a row [1 .. n]
                 * where j is a member of the positive Natural numbers
                 * (N). */
                {
                        selection_button = &selection_buttons[selection_button_index];
                        selection_button->active = FALSE;
                        gtk_toggle_button_set_active
                                (GTK_TOGGLE_BUTTON (selection_button->button_widget),
                                FALSE);
                        selection_button_index++;
                }
        }
}


/*!
 * \brief The "Close" button is clicked.
 *
 * <ul>
 * <li>close the window (destroy the widget).
 * <li>reset the pointer value of the select exceptions window (global).
 * </ul>
 */
static void
select_exceptions_close_cb
(
        GtkWidget *widget,
                /*!< : is the caller widget.*/
        GtkWidget *window
                /*!< : is the window widget to close (destroy).*/
)
{
        gtk_widget_destroy (window);
        select_exceptions_window = NULL;
}


/*!
 * \brief Delete the window.
 *
 * <ul>
 * <li>close the window (destroy the widget).
 * <li>reset the pointer value of the select exceptions window (global).
 * </ul>
 */
static void
select_exceptions_delete_event
(
        GtkWidget *widget,
                /*!< : is the caller widget.*/
        GdkEvent *event
		/*!< : is the event passed from the caller.*/
)
{
        gtk_widget_destroy (widget);
        select_exceptions_window = NULL;
}


/*!
 * \brief The "OK" button is clicked.
 *
 * <ul>
 * <li>save the state of all selection buttons.
 * <li>collect all the exceptions in the \c pin_pad_exception_string
 * (global).
 * <li>close the window (destroy the widget).
 * <li>reset the pointer value of the select exceptions window (global).
 * </ul>
 */
static void
select_exceptions_ok_cb
(
        GtkWidget *widget,
                /*!< : is the caller widget (the OK button).*/
        GtkWidget *window
                /*!< : is the window widget to close (destroy).*/
)
{
        /* Lookup all togglebuttons and save the state in the exceptions
         * array. */
        gint i;
        gint j;
        SelectionButtonSet *selection_button;
        gint selection_button_index = 0;
        gchar *exceptions = g_strdup ("");
        number_of_exceptions = 0;
        /* parse the array for active selection buttons. */
        for (i = 0; (i < number_of_rows); i++)
        /* one row at a time [A .. Y, AA .. YY] etc.
         * where rowletter[i] is one or more letters of the alphabet,
         * excluding all instances with "I", "O", "Q", "S" and "Z". */
        {
                for (j = 0; (j < number_of_columns); j++)
                /* all columns of a row [1 .. n]
                 * where j is a member of the positive Natural numbers
		 * (N). */
                {
                        gchar *selection_button_name = g_strdup_printf ("%s%d",
                                (row_letters[i]), (j + 1));
                        selection_button = &selection_buttons[selection_button_index];
                        if (selection_button->active)
                        {
                                exceptions = g_strconcat (exceptions,
                                        selection_button->name, ",", NULL);
                                number_of_exceptions++;
                        }
                        selection_button_index++;
                        g_free (selection_button_name);
                }
        }
        pin_pad_exceptions_string = g_strdup_printf ("%s", exceptions);
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        (_("found a total of %d exceptions for pins/pads.")),
                        number_of_exceptions);
                g_log ("", G_LOG_LEVEL_INFO,
                        (_("found the following exceptions for pins/pads: %s.")),
                        pin_pad_exceptions_string);
        }
        g_free (exceptions);
        /* Destroy the widget and reset the value in the pointer */
        gtk_widget_destroy (select_exceptions_window);
        select_exceptions_window = NULL;
}


/*!
 * \brief One of the selection buttons is clicked.
 *
 * <ul>
 * <li>lookup the selection button in the array \c selection_button.
 * <li>save the state of the selection button in \c
 * selection_button->active.
 * </ul>
 */
static void
select_exceptions_selection_button_clicked_cb
(
        GtkWidget *widget,
                /*!< : is the caller widget (the clicked button).*/
        GtkWidget *window
                /*!< : is the parent window widget of the clicked button).*/
)
{
        const gchar *widget_name;
        SelectionButtonSet *selection_button;
        gint selection_button_index = -1;
        widget_name = gtk_widget_get_name (widget);
        do
        {
                selection_button_index++;
                selection_button = &selection_buttons[selection_button_index];
        } while (strcmp (widget_name, selection_button->name));
        selection_button->active = gtk_toggle_button_get_active
                (GTK_TOGGLE_BUTTON (widget));
}


/*!
 * \brief Create a selection exceptions window.
 *
 * <ul>
 * <li>create only <b>one</b> single window with a title "select exceptions".
 * <li>depending on the package type create the pattern of selection
 * buttons.
 * <li>add "Close", "Clear" and "OK" stock buttons.
 * </ul>
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
select_exceptions_create_window
(
        gint number_of_rows,
                /*!< : is the number of pin/pad rows (selection buttons).*/
        gint number_of_columns
                /*!< : is the number of pin/pad columns (selection buttons).*/
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
        /* Write pin and/or pad selection buttons. */
        gint i;
        gint j;
        SelectionButtonSet *selection_button;
        gint selection_button_index = 0;
        /* Create the top row with column labels with pin/pad index numbers. */
        for (j = 1; (j < (number_of_columns + 1)); j++)
        {
                GtkWidget *column_label = gtk_label_new (g_strdup_printf ("%d", j));
                gtk_label_set_justify (GTK_LABEL (column_label), GTK_JUSTIFY_CENTER);
                gtk_table_attach_defaults (GTK_TABLE (table), column_label,
                        j, (j + 1),
                        0, 1);
        }
        /* Create an array of selection buttons and add a label at the begin and
         * end of the row stating the pin/pad index (valid) alphabet letter. */
        for (i = 0; (i < number_of_rows); i++)
        /* one row at a time [A .. Y, AA .. YY] etc.
         * where i is one or more letters of the alphabet,
         * excluding "I", "O", "Q", "S" and "Z" */
        {
                /* Create a label in the first column with the pin/pad
                 * index character. */
                GtkWidget *row_label = gtk_label_new (g_strdup_printf ("%s",
                        (row_letters[i])));
                gtk_table_attach_defaults (GTK_TABLE (table), row_label,
                        0, 1,
                        (i + 1), (i + 2));
                for (j = 0; (j < number_of_columns); j++)
                /* all columns of a row [1 .. n]
                 * where j is a member of the positive Natural numbers (N) */
                {
                        selection_button = &selection_buttons[selection_button_index];
                        selection_button->button_widget =
                                gtk_check_button_new ();
                        gtk_widget_show (selection_button->button_widget);
                        selection_button->id = selection_button_index;
                        gchar *selection_button_name = g_strdup_printf ("%s%d",
                                (row_letters[i]), (j + 1));
                        selection_button->name = g_strdup (selection_button_name);
                        gtk_widget_set_name (selection_button->button_widget,
                                selection_button_name);
                        gtk_table_attach_defaults (GTK_TABLE (table),
                                selection_button->button_widget,
                                (j + 1), (j + 2), (i + 1), (i + 2));
                        selection_button->active = !get_pin_pad_exception
                                (selection_button_name);
                        if (get_pin_pad_exception (selection_button_name) == EXIT_SUCCESS)
                        {
                                gtk_toggle_button_set_active
                                        (GTK_TOGGLE_BUTTON (selection_button->button_widget),
                                        TRUE);
                        }
                        else
                        {
                                gtk_toggle_button_set_active
                                        (GTK_TOGGLE_BUTTON (selection_button->button_widget),
                                        FALSE);
                        }
                        /* connect the button clicked signal for all selection buttons
                         * to one single callback function.
                         * this saves generating a callback for every single selection
                         * button in the array, but this comes with the cost (time) of parsing
                         * all the buttons in the array when one button is clicked */
                        g_signal_connect
                        (
                                G_OBJECT (selection_button->button_widget),
                                "clicked",
                                G_CALLBACK (select_exceptions_selection_button_clicked_cb),
                                select_exceptions_window
                        );
                        selection_button_index++;
                        g_free (selection_button_name);
                }
        }
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
        return (EXIT_SUCCESS);
}

/* EOF */
