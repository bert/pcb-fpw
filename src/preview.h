/*!
 * \file src/preview.h
 *
 * \author Copyright (C) 2007, 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for footprint preview widget functions.
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


#ifndef __PREVIEW_INCLUDED__
#define __PREVIEW_INCLUDED__


GdkPixmap *pixmap = NULL;
        /*!< Backing pixmap for drawing area */


/*!
 * \brief Struct containing all data to draw an arc on the preview canvas.
 */
typedef struct preview_arc
{
        GdkDrawable *drawable;
                /*!< a GdkDrawable (a GdkWindow or a GdkPixmap). */
        GdkGC *gc;
                /*!< Graphics Context */
        gboolean filled;
                /*!< \c TRUE if the arc should be filled, producing a 'pie slice'. */
        gint x;
                /*!< The x coordinate of the left edge of the bounding rectangle. */
        gint y;
                /*!< The y coordinate of the top edge of the bounding rectangle. */
        gint width;
                /*!< The width of the bounding rectangle. */
        gint height;
                /*!< The height of the bounding rectangle. */
        gint angle1;
                /*!< The start angle of the arc, relative to the 3 o'clock
                 * position, counter-clockwise, in 1/64ths of a degree. */
        gint angle2;
                /*!< The end angle of the arc, relative to angle1, in 1/64ths
                 * of a degree. */
} *preview_arc;


/*!
 * \brief Struct containing all data to draw a line on the preview canvas.
 */
typedef struct preview_line
{
        GdkDrawable *drawable;
                /*!< a GdkDrawable (a GdkWindow or a GdkPixmap). */
        GdkGC *gc;
                /*!< Graphics Context */
        gint x1;
                /*!< X-coordinate of start point of the line. */
        gint y1;
                /*!< Y-coordinate of start point of the line. */
        gint x2;
                /*!< X-coordinate of the end point of the line. */
        gint y2;
                /*!< Y-coordinate of the end point of the line. */
} *preview_line;


/*!
 * \brief Struct containing all data to draw a polygon on the preview canvas.
 */
typedef struct preview_polygon
{
        GdkDrawable *drawable;
                /*!< a GdkDrawable (a GdkWindow or a GdkPixmap). */
        GdkGC *gc;
                /*!< Graphics Context. */
        gboolean filled;
                /*!< \c TRUE if the polygon should be filled. */
        GdkPoint *points;
                /*!< An array of GdkPoint structures specifying the points
                 * making up the polygon. */
        gint npoints;
                /*!< The number of points. */
} *preview_polygon;


/*!
 * \brief Struct containing all data to draw a rectangle on the preview canvas.
 */
typedef struct preview_rectangle
{
        GdkDrawable *drawable;
                /*!< a GdkDrawable (a GdkWindow or a GdkPixmap). */
        GdkGC *gc;
                /*!< Graphics Context. */
        gboolean filled;
                /*!< \c TRUE if the polygon should be filled.\n
                * The polygon is closed automatically, connecting the last
                * point to the first point if necessary. */
        gint x;
                /*!< The X-coordinate of the left edge of the rectangle. */
        gint y;
                /*!< The Y-coordinate of the top edge of the rectangle. */
        gint width;
                /*!< The width of the rectangle. */
        gint height;
                /*!< The height of the rectangle. */
} *preview_rectangle;


static void preview_close_cb (GtkWidget * widget, GtkWidget *preview_window);
static gboolean preview_configure_event (GtkWidget *widget, GdkEventConfigure *event);
void preview_delete_event (GtkWidget *widget, GdkEvent *event);
int preview_set_fg_color (GdkGC *gc, const char *color_name);
int preview_set_fill_mode (GdkGC *gc, GdkFill fill_mode);
int preview_set_line_cap (GdkGC *gc, GdkCapStyle line_cap);
int preview_set_line_style (GdkGC *gc, GdkLineStyle line_style);
int preview_set_line_width (GdkGC *gc, gint line_width);
int preview_use_gc (GdkDrawable *drawable, GdkGC *gc, const char * color_name, gint line_width, GdkCapStyle line_cap, GdkLineStyle line_style, GdkFill fill_mode);
static void preview_draw_arc (GtkWidget *widget, preview_arc arc);
static void preview_draw_background (GtkWidget *widget, gdouble x, gdouble y);
static void preview_draw_line (GtkWidget *widget, preview_line line);
static void preview_draw_pad (GtkWidget *widget );
static void preview_draw_pin (GtkWidget *widget );
static void preview_draw_polygon (GtkWidget *widget, preview_polygon polygon);
static void preview_draw_rectangle (GtkWidget *widget, preview_rectangle rectangle);
static gboolean preview_expose_event (GtkWidget *widget, GdkEventExpose *event);
int preview_create_window (gchar *footprint_name, gint width, gint height);


#endif /* __PREVIEW_INCLUDED__ */


/* EOF */
