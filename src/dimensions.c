/*!
 * \file dimensions.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief A footprint dimensions widget.
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
 * \brief Close the dimensions window (destroy the \c dimensions_window widget).
 */
static void
dimensions_window_close_cb
(
        GtkWidget *widget,
        GtkWidget *dimensions_window
)
{
        gtk_widget_destroy (dimensions_window);
}


/*!
 * \brief Delete the window.
 */
void
dimensions_window_delete_event
(
        GtkWidget *widget,
        GdkEvent *event
)
{
        gtk_widget_destroy (widget);
}


int
dimensions_create_window
(
        gchar *image_filename,
        gchar *footprint_type
)
{
        /* Create a dimensions window */
        GtkWidget *dimensions_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        /* Destroy the dimensions window when the main window of pcb-gfpw gets
         * destroyed */
        gtk_window_set_destroy_with_parent (GTK_WINDOW (dimensions_window),
                TRUE);
        /* Set the preview window title */
        gchar *dimensions_window_title = g_strdup_printf ("dimensions of %s",
                footprint_type);
        gtk_window_set_title (GTK_WINDOW (dimensions_window),
                dimensions_window_title);
        g_free (dimensions_window_title);
        gtk_container_set_border_width (GTK_CONTAINER (dimensions_window), 10);
        /* Set signals for the window */
        gtk_signal_connect
        (
                GTK_OBJECT (dimensions_window),
                "delete_event",
                (GtkSignalFunc) dimensions_window_delete_event,
                NULL
        );
        /* Create a vertical box */
        GtkWidget *vbox = gtk_vbox_new (FALSE, 10);
        gtk_container_add (GTK_CONTAINER (dimensions_window), vbox);
        /* Load a pre-cooked dimensions image for the footprint type
         * and set the name accordingly */
        GtkWidget *dimensions_image = gtk_image_new_from_file (image_filename);
        gtk_widget_set_name (dimensions_image, "dimensions_image");
        /* Display the pre-cooked dimensions image for the footprint type */
        gtk_widget_show (dimensions_image);
        gtk_container_add (GTK_CONTAINER (dimensions_window),
                dimensions_image);
        /* Create a horizontal button box */
        GtkWidget *hbox = gtk_hbutton_box_new ();
        gtk_button_box_set_layout (GTK_BUTTON_BOX (hbox), GTK_BUTTONBOX_END);
        /* Create a close button */
        GtkWidget *button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
        g_signal_connect
        (
                G_OBJECT (button),
                "clicked",
                G_CALLBACK (dimensions_window_close_cb),
                dimensions_window
        );
        /* Pack the button into the hbox */
        gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);
        /* Pack the hbox into the vbox */
        gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
        /* Show the window */
        gtk_widget_realize (dimensions_window);
        gtk_widget_show_all (dimensions_window);
        /* Enter the GTK main loop */
        gtk_main ();
        return 0;
}

/* EOF */


