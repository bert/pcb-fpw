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
 * \brief Struct containing all data to draw an arc on the preview canvas.
 */
typedef struct preview_arc
{
        GdkDrawable *drawable; /*!< a GdkDrawable (a GdkWindow or a GdkPixmap). */
        GdkGC *gc; /*!< Graphics Context */
        gboolean filled; /*!< TRUE if the arc should be filled, producing a 'pie slice'. */
        gint x; /*!< The x coordinate of the left edge of the bounding rectangle. */
        gint y; /*!< The y coordinate of the top edge of the bounding rectangle. */
        gint width; /*!< The width of the bounding rectangle. */
        gint height; /*!< The height of the bounding rectangle. */
        gint angle1; /*!< The start angle of the arc,
                      * relative to the 3 o'clock position,
                      * counter-clockwise,
                      * in 1/64ths of a degree. */
        gint angle2; /*!< The end angle of the arc,
                     * relative to angle1,
                     * in 1/64ths of a degree. */
} *preview_arc;


/*!
 * \brief Struct containing all data to draw a line on the preview canvas.
 */
typedef struct preview_line
{
        GdkDrawable *drawable; /*!< a GdkDrawable (a GdkWindow or a GdkPixmap). */
        GdkGC *gc; /*!< Graphics Context */
        gint x1; /*!< X-coordinate of start point of the line. */
        gint y1; /*!< Y-coordinate of start point of the line. */
        gint x2; /*!< X-coordinate of the end point of the line. */
        gint y2; /*!< Y-coordinate of the end point of the line. */
} *preview_line;


/*!
 * \brief Struct containing all data to draw a polygon on the preview canvas.
 */
typedef struct preview_polygon
{
        GdkDrawable *drawable; /*!< a GdkDrawable (a GdkWindow or a GdkPixmap). */
        GdkGC *gc; /*!< Graphics Context. */
        gboolean filled; /*!< TRUE if the polygon should be filled. */
        GdkPoint *points; /*!< An array of GdkPoint structures specifying the points making up the polygon. */
        gint npoints; /*!< The number of points. */
} *preview_polygon;


/*!
 * \brief Struct containing all data to draw a rectangle on the preview canvas.
 */
typedef struct preview_rectangle
{
        GdkDrawable *drawable; /*!< a GdkDrawable (a GdkWindow or a GdkPixmap). */
        GdkGC *gc; /*!< Graphics Context. */
        gboolean filled; /*!< TRUE if the rectangle should be filled. */
        gint x; /*!< The X-coordinate of the left edge of the rectangle. */
        gint y; /*!< The Y-coordinate of the top edge of the rectangle. */
        gint width; /*!< The width of the rectangle. */
        gint height; /*!< The height of the rectangle. */
} *preview_rectangle;


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
        gtk_widget_destroy (widget);
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
                fprintf (stderr, "WARNING in %s():  name = NULL, setting color to magenta.\n",
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
 * \brief Set the fill mode of the Graphics Context.
 */
int
preview_set_fill_mode
(
        GdkGC *gc,
        GdkFill fill_mode
)
{
        if (!gc)
                return 0;
        if (fill_mode == NULL)
        {
                fprintf (stderr, "WARNING in %s():  fill mode = NULL, setting fill mode to SOLID.\n",
                        __FUNCTION__);
                fill_mode = GDK_SOLID;
        }
        gdk_gc_set_fill
        (
                gc,
                fill_mode
        );
        return (&gc);
}


/*!
 * \brief Set the line capsulation of the Graphics Context.
 */
int
preview_set_line_cap
(
        GdkGC *gc,
        GdkCapStyle line_cap
)
{
        if (!gc)
                return 0;
        if (line_cap == NULL)
        {
                fprintf (stderr, "WARNING in %s():  line cap = NULL, setting line cap  to ROUND.\n",
                        __FUNCTION__);
                line_cap = GDK_CAP_ROUND;
        }
        GdkGCValues gc_values;
        gdk_gc_get_values (gc, &gc_values);
        gdk_gc_set_line_attributes
        (
                gc,
                gc_values.line_width,
                gc_values.line_style,
                line_cap,
                gc_values.join_style
        );
        return (&gc);
}


/*!
 * \brief Set the line style of the Graphics Context.
 */
int
preview_set_line_style
(
        GdkGC *gc,
        GdkLineStyle line_style
)
{
        if (!gc)
                return 0;
        if (line_style == NULL)
        {
                fprintf (stderr, "WARNING in %s():  line style = NULL, setting line style  to SOLID.\n",
                        __FUNCTION__);
                line_style = GDK_LINE_SOLID;
        }
        GdkGCValues gc_values;
        gdk_gc_get_values (gc, &gc_values);
        gdk_gc_set_line_attributes
        (
                gc,
                gc_values.line_width,
                line_style,
                gc_values.cap_style,
                gc_values.join_style
        );
        return (&gc);
}


/*!
 * \brief Set the line width of the Graphics Context.
 */
int
preview_set_line_width
(
        GdkGC *gc,
        gint line_width
)
{
        if (!gc)
                return 0;
        if (line_width == 0)
                return 0;
        GdkGCValues gc_values;
        gdk_gc_get_values (gc, &gc_values);
        if (line_width == 1)
        {
                gdk_gc_set_line_attributes
                (
                        gc,
                        line_width,
                        GDK_LINE_DOUBLE_DASH,
                        gc_values.cap_style,
                        gc_values.join_style
                );
        }
        else
        {
                gdk_gc_set_line_attributes
                (
                        gc,
                        line_width,
                        gc_values.line_style,
                        gc_values.cap_style,
                        gc_values.join_style
                );
        }
        return (&gc);
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
        const char * color_name,
        gint line_width,
        GdkCapStyle line_cap,
        GdkLineStyle line_style,
        GdkFill fill_mode
)
{
        if (!drawable)
        {
                fprintf (stderr, "WARNING: couldn't allocate a gc, invalid drawable was passed.\n");
                return 0;
        }
        if (!gc)
        {
                GdkGC *gc = gdk_gc_new (drawable);
                preview_set_fg_color (gc, color_name);
                preview_set_line_width (gc, line_width);
                preview_set_line_cap (gc, line_cap);
                preview_set_line_style (gc, line_style);
                preview_set_fill_mode (gc, fill_mode);
//                preview_set_draw_xor (gc, gc->xor);
                return (&gc);
        }
}


/*!
 * \brief Draw an arc on the preview pixmap.
 *
 * Draws an arc or a filled 'pie slice'.\n
 * The arc is defined by the bounding rectangle of the entire ellipse, and
 * the start and end angles of the part of the ellipse to be drawn.
 */
static void
preview_draw_arc
(
        GtkWidget *widget, /*!< The toplevel widget containing the drawable. */
        preview_arc arc /*!< A preview arc. */
)
{
        if (!arc)
        {
                fprintf (stderr, "WARNING: passed arc was invalid.\n");
                return;
        }
        /* Modify angles from degrees to Gdk format */
        arc->angle1 = 64.0 * arc->angle1;
        gdk_draw_arc
        (
                arc->drawable,
                arc->gc,
                arc->filled,
                arc->x,
                arc->y,
                arc->width,
                arc->height,
                arc->angle1,
                arc->angle2
        );
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
 *
 * Draws a line, using the foreground color and other attributes of the GdkGC.
 */
static void
preview_draw_line
(
        GtkWidget *widget, /*!< The toplevel widget containing the drawable. */
        preview_line line /*!< A preview line. */
)
{
        gdk_draw_line
        (
                line->drawable,
                line->gc,
                line->x1,
                line->y1,
                line->x2,
                line->y2
        );
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
 * \brief Draw a pin on the preview pixmap.
 */
static void
preview_draw_polygon
(
        GtkWidget *widget, /*!< The toplevel widget containing the drawable. */
        preview_polygon polygon /*!< A preview polygon. */
)
{
        if (!polygon)
        {
                fprintf (stderr, "WARNING: passed polygon was invalid.\n");
                return;
        }
        gdk_draw_polygon
        (
                polygon->drawable,
                polygon->gc,
                polygon->filled,
                polygon->points,
                polygon->npoints
        );
}


/*!
 * \brief Draws a rectangle on the preview canvas.
 *
 * Draws a rectangular outline or filled rectangle, using the foreground
 * color and other attributes of the GdkGC.\n
 * A rectangle drawn filled is 1 pixel smaller in both dimensions than a
 * rectangle outlined.\n
 * Calling gdk_draw_rectangle (window, gc, TRUE, 0, 0, 20, 20) results in a
 * filled rectangle 20 pixels wide and 20 pixels high.\n
 * Calling gdk_draw_rectangle (window, gc, FALSE, 0, 0, 20, 20) results in an
 * outlined rectangle with corners at (0, 0), (0, 20), (20, 20), and (20, 0),
 * which makes it 21 pixels wide and 21 pixels high.
 */
static void
preview_draw_rectangle
(
        GtkWidget *widget, /*!< The toplevel widget containing the drawable. */
        preview_rectangle rectangle
)
{
        if (!rectangle)
        {
                fprintf (stderr, "WARNING: passed rectangle was invalid.\n");
                return;
        }
        gdk_draw_rectangle
        (
                rectangle->drawable,
                rectangle->gc,
                rectangle->filled,
                rectangle->x,
                rectangle->y,
                rectangle->width,
                rectangle->height
        );
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


