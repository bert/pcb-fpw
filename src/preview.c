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
 * \brief Draw a white rectangle on the screen
 */
static void
draw_brush (GtkWidget *widget, gdouble x, gdouble y)
{
        GdkRectangle update_rect;
        update_rect.x = x - 5;
        update_rect.y = y - 5;
        update_rect.width = 10;
        update_rect.height = 10;
        gdk_draw_rectangle (pixmap,
                widget->style->black_gc,
                TRUE,
                update_rect.x,
                update_rect.y,
                update_rect.width,
                update_rect.height);
        gtk_widget_queue_draw_area (widget,
                update_rect.x,
                update_rect.y,
                update_rect.width,
                update_rect.height);
}


/*!
 * \brief Create a new backing pixmap of the appropriate size
 */
static gboolean
configure_event (GtkWidget *widget, GdkEventConfigure *event)
{
               if (pixmap)
                       g_object_unref (pixmap);
               pixmap = gdk_pixmap_new (widget->window,
                       widget->allocation.width,
                       widget->allocation.height,
                       depth);
               gdk_draw_rectangle (pixmap,
                       widget->style->white_gc,
                       TRUE,
                       0,
                       0,
                       widget->allocation.width,
                       widget->allocation.height);
        return TRUE;
}


/*!
 * \brief Delete the window
 */
void
delete_event (GtkWidget *widget, GdkEvent *event)
{
        gtk_main_quit ();
}


/*!
 * \brief Redraw the screen from the backing pixmap
 */
static gboolean
expose_event (GtkWidget *widget, GdkEventExpose *event)
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
        GtkWindow  *window = NULL;
        window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        gtk_window_set_title (window, "pcb-fpw preview");
        /* Set signals for the window */
        gtk_signal_connect (GTK_OBJECT (window),
                "delete_event",
                (GtkSignalFunc) delete_event,
                NULL);
        /* Create a drawing area */
        drawing_area = gtk_drawing_area_new ();
        gtk_widget_set_size_request (drawing_area, width, height);
        /* Set signals for the drawing area */
        gtk_signal_connect (GTK_OBJECT (drawing_area),
                "expose_event",
                (GtkSignalFunc) expose_event,
                NULL);
        gtk_signal_connect (GTK_OBJECT (drawing_area),
                "configure_event",
                (GtkSignalFunc) configure_event,
                NULL);
        gtk_widget_set_events (drawing_area,
                GDK_EXPOSURE_MASK
                | GDK_LEAVE_NOTIFY_MASK);
        /* Add the drawing area to the window container */
        gtk_container_add (GTK_CONTAINER (window), drawing_area);
        /* Show the window */
        gtk_widget_show (window);
        /* Enter the GTK main loop */
        gtk_main ();
        return 0;
}

/* EOF */
