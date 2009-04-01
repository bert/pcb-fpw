/*!
 * \file dimensions.c
 * \author Copyright 2008 ... 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
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


/*!
 * \brief Close the dimensions window (destroy the \c dimensions_window widget).
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c *dimension_window is the widget to be closed.\n
 * \n
 * <b>Returns:</b> none.
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
 *
 * <b>Parameters:</b> \c *widget is the widget to be deleted.\n
 * \n
 * <b>Parameters:</b> \c *event is the event passed from the caller.\n
 * \n
 * <b>Returns:</b> none.
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


/*!
 * \brief Expose the window.
 *
 * <b>Parameters:</b> \c *widget is the (drawable) widget to contain the
 * image.\n
 * \n
 * <b>Parameters:</b> \c *event is the event passed from the caller.\n
 * \n
 * <b>Parameters:</b> \c *buf is the image to (re)draw.\n
 * \n
 * <b>Returns:</b> none.
 */
void
dimensions_window_expose_event
(
        GtkWidget *widget,
        GdkEventExpose *event,
        GdkPixbuf *buf
)
{
        gdk_draw_pixbuf
        (
                widget->window,
                NULL,
                buf,
                0,
                0,
                0,
                0,
                -1,
                -1,
                GDK_RGB_DITHER_NONE,
                0,
                0
        );
}


/*!
 * \brief Create a dialog window containing a pre-defined pixbuf (from file).
 *
 * The \c footprint_name variable is used in the dialog title. \n
 * \n
 * <b>Parameters:</b> \c *image_filename is the image to draw in the
 * window.\n
 * \n
 * <b>Parameters:</b> \c *footprint_type.\n
 * \n
 * <b>Returns:</b> 0 when successfull.
 */
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
        gchar *dimensions_window_title = g_strdup_printf (_("dimensions of %s"),
                footprint_type);
        gtk_window_set_title (GTK_WINDOW (dimensions_window),
                dimensions_window_title);
        g_free (dimensions_window_title);
        gtk_container_set_border_width (GTK_CONTAINER (dimensions_window), 10);
        /* Set the delete signal for the window */
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
