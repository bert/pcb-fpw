/*!
 * \file preview.c
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Just some rambling code for a preview widget.
 *
 * This program is free software; you can redistribute it and/or modify\n
 * it under the terms of the GNU General Public License as published by\n
 * the Free Software Foundation; either version 2 of the License, or\n
 * (at your option) any later version.\n
 * \n
 * This program is distributed in the hope that it will be useful,\n
 * but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
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


GdkPixmap *pixmap = NULL;
        /*!< Backing pixmap for drawing area */

GtkDrawingArea *drawing_area = NULL;
gint width = 200;
gint height = 200;
gint depth = -1;


/*!
 * \brief Close the preview window (destroy the preview widget).
 */
static void
preview_close_cb (GtkWidget * widget, GtkWidget *preview_window)
{
        gtk_widget_destroy (preview_window);
}


/*!
 * \brief Create a new backing pixmap of the appropriate size.
 */
static gboolean
preview_configure_event (GtkWidget *widget, GdkEventConfigure *event)
{
        if (pixmap)
                g_object_unref (pixmap);
        pixmap = gdk_pixmap_new (widget->window,
                widget->allocation.width,
                widget->allocation.height,
                depth);
        gdk_draw_rectangle (
                pixmap,
                widget->style->white_gc,
                TRUE,
                0,
                0,
                widget->allocation.width,
                widget->allocation.height);
        return TRUE;
}


/*!
 * \brief Delete the window.
 */
void
preview_delete_event (GtkWidget *widget, GdkEvent *event)
{
        gtk_main_quit ();
}


/*!
 * \brief Set the foreground color of the Graphics Context.
 */
int
preview_set_fg_color
(
        GdkGC *gc,
        const char *color_name
)
{
        if (!gc)
                return 0;
        if (color_name == NULL)
        {
                fprintf (stderr, "WARNING in %s():  name = NULL, setting color to magenta\n",
                        __FUNCTION__);
                color_name = "magenta";
        }
        GdkColor color;
        if (!gdk_color_parse (color_name, &color))
                return 0;
        gdk_gc_set_foreground (gc, &color);
        return (gc);
}


/*!
 * \brief Use a Graphics Context when drawing entities.
 *
 * If the passed Graphics Context is NULL , create a Graphics Context.
 */
int
preview_use_gc
(
        GdkDrawable *drawable,
        GdkGC *gc,
        const char * color_name
)
{
        if (!drawable)
                return 0;
        if (!gc)
        {
                GdkGC *gc = gdk_gc_new (drawable);
                preview_set_fg_color (gc, color_name);
//                preview_set_font (gc, gc->font);
//                preview_set_line_width (gc, gc->width);
//                preview_set_line_cap (gc, gc->cap);
//                preview_set_line_style (gc, gc->style);
//                preview_set_fill (gc, gc->fill);
//                preview_set_draw_xor (gc, gc->xor);
                return (&gc);
        }
}


/*!
 * \brief Draw an arc on the preview pixmap.
 */
static void
preview_draw_arc
(
        GtkWidget *widget
)
{
}


/*!
 * \brief Draw a white background (rectangle) on the screen.
 */
static void
preview_draw_background (GtkWidget *widget, gdouble x, gdouble y)
{
        GdkRectangle update_rect;
        update_rect.x = x - 5;
        update_rect.y = y - 5;
        update_rect.width = 10;
        update_rect.height = 10;
        gdk_draw_rectangle
        (
                pixmap,
                widget->style->black_gc,
                TRUE,
                update_rect.x,
                update_rect.y,
                update_rect.width,
                update_rect.height
        );
        gtk_widget_queue_draw_area
        (
                widget,
                update_rect.x,
                update_rect.y,
                update_rect.width,
                update_rect.height
        );
}


/*!
 * \brief Draw a line on the preview pixmap.
 */
static void
preview_draw_line
(
        GtkWidget *widget, /*!< The toplevel widget containing the drawable. */
        GdkDrawable *drawable, /*!< The drawable to draw the line onto.*/
        const gchar * color_name, /*!< */
        gint x1, /*!< X-coordinate of start point of the line. */
        gint y1, /*!< Y-coordinate of start point of the line. */
        gint x2, /*!< X-coordinate of the end point of the line. */
        gint y2 /*!< Y-coordinate of the end point of the line. */
)
{
        GdkGC *gc;
        preview_use_gc (drawable, gc, color_name);
        gdk_draw_line (drawable, gc, x1, y1, x2, y2 );
}


/*!
 * \brief Draw a pad on the preview pixmap.
 */
static void
preview_draw_pad
(
        GtkWidget *widget
)
{
}


/*!
 * \brief Draw a pin on the preview pixmap.
 */
static void
preview_draw_pin
(
        GtkWidget *widget
)
{
}


/*!
 * \brief Redraw the screen from the backing pixmap.
 */
static gboolean
preview_expose_event (GtkWidget *widget, GdkEventExpose *event)
{
        gdk_draw_drawable (widget->window,
                widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                pixmap,
                event->area.x,
                event->area.y,
                event->area.x,
                event->area.y,
                event->area.width,
                event->area.height);
        return FALSE;
}


int
main (int argc, char** argv)
{
        gtk_init (&argc, &argv);
        /* Create a preview window */
        GtkWindow *preview_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        /* Destroy the preview window when the main window of pcb-gfpw gets
         * destroyed */
        gtk_window_set_destroy_with_parent (preview_window, TRUE);
        /* Set the preview window title */
        /*!
         * \todo In the near future, when the preview window is called from
         * pcb-gfpw, include the name of the footprint.\n
         */
//        gchar *preview_window_title = g_strdup_printf ("pcb-fpw preview: %s",
//                footprint_name);
//        gtk_window_set_title (preview_window, preview_window_title);
//        g_free (preview_window_title);
        gtk_window_set_title (preview_window, "pcb-fpw preview");
        gtk_container_set_border_width (GTK_CONTAINER (preview_window), 10);
        /* Set signals for the window */
        gtk_signal_connect
        (
                GTK_OBJECT (preview_window),
                "delete_event",
                (GtkSignalFunc) preview_delete_event,
                NULL
        );
        /* Create a vertical box */
        GtkWindow *vbox = gtk_vbox_new (FALSE, 10);
        gtk_container_add (GTK_CONTAINER (preview_window), vbox);
        /* Create a preview drawing area */
        GtkWidget *preview_drawing_area = gtk_drawing_area_new ();
        gtk_widget_set_size_request (preview_drawing_area, width, height);
        /* Set signals for the drawing area */
        gtk_signal_connect
        (
                GTK_OBJECT (preview_drawing_area),
                "expose_event",
                (GtkSignalFunc) preview_expose_event,
                NULL
        );
        gtk_signal_connect
        (
                GTK_OBJECT (preview_drawing_area),
                "configure_event",
                (GtkSignalFunc) preview_configure_event,
                NULL
        );
        gtk_widget_set_events
        (
                preview_drawing_area,
                GDK_EXPOSURE_MASK | GDK_LEAVE_NOTIFY_MASK
        );
        /* Create an adjustable viewport */
        GtkWidget *preview_viewport = gtk_viewport_new (NULL, NULL);
        gtk_viewport_set_shadow_type (GTK_VIEWPORT (preview_viewport), GTK_SHADOW_IN);
        /* Pack the viewport into the vbox */
        gtk_box_pack_start (GTK_BOX (vbox), preview_viewport, TRUE, TRUE, 0);
        /* Add the drawing area to the viewport container */
        gtk_container_add (GTK_CONTAINER (preview_viewport), preview_drawing_area);
        /* Create a horizontal button box */
        GtkWidget *hbox = gtk_hbutton_box_new ();
        gtk_button_box_set_layout (GTK_BUTTON_BOX (hbox), GTK_BUTTONBOX_END);
        /* Create a close button */
        GtkWidget *button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
        g_signal_connect
        (
                G_OBJECT (button),
                "clicked",
                G_CALLBACK (preview_close_cb),
                preview_window
        );
        /* Pack the button into the hbox */
        gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0);
        /* Pack the hbox into the vbox */
        gtk_box_pack_start (GTK_BOX (vbox), hbox, FALSE, FALSE, 0);
        /* Get the correct size for the preview window */
        gtk_window_set_default_size
        (
                GTK_WINDOW (preview_window),
                width + 50,
                height + 50
        );
        /* Show the window */
        gtk_widget_realize (preview_window);
        gtk_widget_show_all (preview_window);
        /* Enter the GTK main loop */
        gtk_main ();
        return 0;
}

/* EOF */


