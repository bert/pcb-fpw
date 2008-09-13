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


/*!
 * \brief The "apply" button is clicked.
 *
 * Save the state of all togglebuttons.
 * Close the window (destroy the widget).
 */
static void
select_exceptions_apply_cb
(
        GtkWidget * widget,
        GtkWidget *selection_window
)
{
        /* Lookup all togglebuttons and save the state in the exceptions
         * array. */

        gtk_widget_destroy (selection_window);
}


/*!
 * \brief Close the window (destroy the widget).
 */
static void
select_exceptions_close_cb
(
        GtkWidget * widget,
        GtkWidget *selection_window
)
{
        gtk_widget_destroy (selection_window);
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
}


int
select_exceptions_create_window
(
        gchar *footprint_name,
        gint number_of_rows,
        gint number_of_columns
)
{

        /* Create a dialog window */
        GtkWidget *select_exceptions_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
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
        /* Create top row of labels with pin/pad index numbers. */
        for (j = 1; (j < (number_of_columns + 1)); j++)
        {
                GtkWidget *column_label = gtk_label_new (g_strdup_printf ("%d", j));
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
                        gchar *radio_button_name = g_strdup_printf ("%s%d",
                                (row_letters[i]), (j + 1));
                        GtkWidget *radio_button = gtk_radio_button_new (NULL);
                        gtk_widget_set_name (radio_button, radio_button_name);
                        gtk_table_attach_defaults (GTK_TABLE (table), radio_button,
                                (j + 1), (j + 2), (i + 1), (i + 2));
//                        gtk_toggle_action_set_active (radio_button,
//                                !get_pin_pad_exception (radio_button_name));
                        /*! \todo Maybe connect some signals here ? */

                        g_free (radio_button_name);
                }
        }
        /* Create bottom row of labels with pin/pad index numbers. */
        /* Pack the table into the vbox */
        gtk_box_pack_start (GTK_BOX (vbox), table, FALSE, FALSE, 0);

        /* Create a horizontal button box */
        GtkWidget *hbox = gtk_hbutton_box_new ();
        gtk_button_box_set_layout (GTK_BUTTON_BOX (hbox), GTK_BUTTONBOX_END);
        /* Create a close button */
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
        GtkWidget *apply_button = gtk_button_new_from_stock (GTK_STOCK_APPLY);
        g_signal_connect
        (
                G_OBJECT (apply_button),
                "clicked",
                G_CALLBACK (select_exceptions_apply_cb),
                select_exceptions_window
        );
        /* Pack the button into the hbox */
        gtk_box_pack_start (GTK_BOX (hbox), apply_button, TRUE, TRUE, 0);
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
