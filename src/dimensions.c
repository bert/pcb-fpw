/*!
 * \file src/dimensions.c
 *
 * \author Copyright 2007-2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Functions for a footprint dimensions preview widget.
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
#include <cairo.h>

#include "dimensions.h"

/*!
 * \brief Close the dimensions window (destroy the \c dimensions_window widget).
 */
static void
dimensions_window_close_cb
(
        GtkWidget *widget,
                /*!< : is the caller widget.*/
        GtkWidget *dimensions_window
                /*!< : is the widget to be closed.*/
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
                /*!< : is the widget to be deleted.*/
        GdkEvent *event
                /*!< : is the event passed from the caller.*/
)
{
        gtk_widget_destroy (widget);
}


/*!
 * \brief Expose the window.
 */
void
dimensions_window_expose_event
(
        GtkWidget *widget,
                /*!< : is the (drawable) widget to contain the image.*/
        GdkEventExpose *event,
                /*!< : is the event passed from the caller.*/
        GdkPixbuf *buf
                /*!< : is the image to (re)draw.*/
)
{
        cairo_t *cr;

        /* Get a cairo drawing context. */
        cr = gdk_cairo_create (widget->window);
        /* Setup the background to transparent. */
        cairo_set_source_rgba (cr, 1.0f, 1.0f, 1.0f, 1.0f);
        /* Put the pixbuf on top. */
        gdk_cairo_set_source_pixbuf (cr, buf, 0, 0);
        cairo_paint (cr);
        /* Clean up. */
        cairo_destroy (cr);
}


/*!
 * \brief Create a dialog window containing a pre-defined pixbuf (from
 * file).
 *
 * The \c footprint_name variable is used in the dialog title.
 *
 * \return 0 when successful.
 */
int
dimensions_create_window
(
        gchar *image_filename,
                /*!< : is the filename of the image to draw in the
                 * window.*/
        gchar *footprint_type
                /*!< : is the footprint type.*/
)
{
        /* Create a dimensions window */
        GtkWidget *dimensions_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        /* Destroy the dimensions window when the main window of pcb-gfpw gets
         * destroyed */
        gtk_window_set_destroy_with_parent (GTK_WINDOW (dimensions_window),
                TRUE);
        /* Set the preview window title */
        gchar *dimensions_window_title = g_strdup_printf (_("dimensions of %s"),
                footprint_type);
        gtk_window_set_title (GTK_WINDOW (dimensions_window),
                dimensions_window_title);
        g_free (dimensions_window_title);
        gtk_container_set_border_width (GTK_CONTAINER (dimensions_window), 10);
        /* Set the delete signal for the window */
        g_signal_connect
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
        GdkPixbuf *dimensions_image = gdk_pixbuf_new_from_file (image_filename, NULL);
        GtkWidget *drawing_area = gtk_drawing_area_new ();
        gtk_widget_set_app_paintable (drawing_area, TRUE);
        /* Set the expose signal for the window */
        g_signal_connect
        (
                GTK_OBJECT (drawing_area),
                "expose-event",
                (GtkSignalFunc) dimensions_window_expose_event,
                dimensions_image
        );
        /* Get size of drawing_area and resize */
        gint width = gdk_pixbuf_get_width (dimensions_image);
        gint height = gdk_pixbuf_get_height (dimensions_image);
        gtk_widget_set_size_request (GTK_WIDGET (drawing_area), width, height);
        gtk_container_add (GTK_CONTAINER (vbox), drawing_area);
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
        gtk_window_set_resizable (GTK_WINDOW (dimensions_window), FALSE);
        gtk_widget_realize (dimensions_window);
        gtk_widget_show_all (dimensions_window);
        /* Enter the GTK main loop */
        gtk_main ();
        return 0;
}


/* EOF */
