/*!
 * \file preview.c
 * \author Copyright (C) 2008 ... 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief A footprint preview widget.
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

#include "globals.h"

#define PREVIEW_BG_COLOR "Black"
#define PREVIEW_FG_COLOR "Red"
#define PREVIEW_COPPER_COLOR "Copper"
#define PREVIEW_MASK_COLOR "Green"
#define PREVIEW_SILK_COLOR "White"

GdkPixmap *pixmap = NULL;
        /*!< Backing pixmap for drawing area */


/*!
 * \brief The element to view in the dialog window.
 */
ElementType *preview_element;


/*!
 * \brief Struct containing all data to draw an arc on the preview canvas.
 */
typedef struct
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
} *preview_arc_t;


/*!
 * \brief Struct containing all data to draw a line on the preview canvas.
 */
typedef struct
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
} *preview_line_t;


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


/*!
 * \brief Close the preview window (destroy the preview widget).
 */
static void
preview_close_cb
(
        GtkWidget * widget,
                /*!< : is the caller widget.*/
        GtkWidget *preview_window
		/*!< : is the widget to be closed.*/
)
{
        gtk_widget_destroy (preview_window);
}


/*!
 * \brief Create a new backing pixmap of the appropriate size.
 *
 * \return \c TRUE when function is completed.
 */
static gboolean
preview_configure_event
(
        GtkWidget *widget,
                /*!< : is the (drawable) widget to contain the image.*/
        GdkEventConfigure *event
		/*!< : is the configure event passed from the caller.*/
)
{
        gint depth = -1;
        if (pixmap)
                g_object_unref (pixmap);
        pixmap = gdk_pixmap_new (
                widget->window,
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
preview_delete_event
(
        GtkWidget *widget,
		/*!< : is the widget to be deleted.*/
        GdkEvent *event
		/*!< : is the delete event passed from the caller.*/
)
{
        gtk_widget_destroy (widget);
}


/*!
 * \brief Set the foreground color of the Graphics Context.
 *
 * \return \c EXIT_SUCCESS when function is completed,
 * \c EXIT_FAILURE when an eror occurred.
 */
int
preview_set_fg_color
(
        GdkGC *gc,
                /*!< : is the Graphics Context. */
        const char *color_name
                /*!< : is a \c NULL terminated color name.*/
)
{
        if (!gc)
                return (EXIT_FAILURE);
        if (!color_name)
        {
                fprintf (stderr, "WARNING in %s():  color_name = NULL, setting color to magenta.\n",
                        __FUNCTION__);
                color_name = "magenta";
                return (EXIT_FAILURE);
        }
        GdkColor color;
        if (!gdk_color_parse (color_name, &color))
        {
                fprintf (stderr, "WARNING in %s():  could not parse color %s.\n",
                        __FUNCTION__, color_name);
                return (EXIT_FAILURE);
        }
        gdk_gc_set_foreground (gc, &color);
        return (EXIT_SUCCESS);
}


/*!
 * \brief Set the fill mode of the Graphics Context.
 *
 * \return \c EXIT_SUCCESS when function is completed,
 * \c EXIT_FAILURE when an eror occurred.
 */
int
preview_set_fill_mode
(
        GdkGC *gc,
                /*!< : is the Graphics Context. */
        GdkFill fill_mode
                /*!< : determines how primitives are drawn.\n
                 * Valid values are:\n
                 * <ul>
                 * <li> \c GDK_SOLID : draw with the foreground color.\n
                 * <li> \c GDK_TILED : draw with a tiled pixmap.\n
                 * <li> \c GDK_STIPPLED : draw using the stipple bitmap.\n
                 * Pixels corresponding to bits in the stipple bitmap
                 * that are set will be drawn in the foreground color;\n
                 * pixels corresponding to bits that are not set will be
                 * left untouched.
                 * <li> \c GDK_OPAQUE_STIPPLED : draw using the stipple
                 * bitmap.\n
                 * Pixels corresponding to bits in the stipple bitmap
                 * that are set will be drawn in the foreground color;\n
                 * pixels corresponding to bits that are not set will be
                 * drawn with the background color.\n
                 * </ul>
                 */
)
{
        if (!gc)
                return (EXIT_FAILURE);
        if (!fill_mode)
        {
                fprintf (stderr, "WARNING in %s():  fill mode = NULL, setting fill mode to SOLID.\n",
                        __FUNCTION__);
                fill_mode = GDK_SOLID;
                return (EXIT_FAILURE);
        }
        gdk_gc_set_fill
        (
                gc,
                fill_mode
        );
        return (EXIT_SUCCESS);
}


/*!
 * \brief Set the line capsulation of the Graphics Context.
 *
 * \return \c EXIT_SUCCESS when function is completed,
 * \c EXIT_FAILURE when an eror occurs.
 */
int
preview_set_line_cap
(
        GdkGC *gc,
                /*!< : is the Graphics Context. */
        GdkCapStyle line_cap
                /*!< : determines how the end of lines are drawn.\n
                 * Valid values are:\n
                 * <ul>
                 * <li> \c GDK_CAP_NOT_LAST : the same as GDK_CAP_BUTT
                 * for lines of non-zero width.\n
                 * for zero width lines, the final point on the line
                 * will not be drawn.
                 * <li> \c GDK_CAP_BUTT : the ends of the lines are
                 * drawn squared off and extending to the coordinates of
                 * the end point.
                 * <li> \c GDK_CAP_ROUND : the ends of the lines are
                 * drawn as semicircles with the diameter equal to the
                 * line width and centered at the end point.
                 * <li> \c GDK_CAP_PROJECTING : the ends of the lines
                 * are drawn squared off and extending half the width of
                 * the line beyond the end point.
                 * </ul>
                 */
)
{
        if (!gc)
                return (EXIT_FAILURE);
        if (!line_cap)
        {
                fprintf (stderr, "WARNING in %s():  line cap = NULL, setting line cap to ROUND.\n",
                        __FUNCTION__);
                line_cap = GDK_CAP_ROUND;
                return (EXIT_FAILURE);
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
        return (EXIT_SUCCESS);
}


/*!
 * \brief Set the line style of the Graphics Context.
 *
 * \return \c EXIT_SUCCESS when function is completed,
 * \c EXIT_FAILURE when an eror occurs.
 */
int
preview_set_line_style
(
        GdkGC *gc,
                /*!< : is the Graphics Context. */
        GdkLineStyle line_style
                /*!< : determines how lines are drawn.\n
                 * Valid values are:\n
                 * <ul>
                 * <li> \c GDK_LINE_SOLID : lines are drawn solid.
                 * <li> \c GDK_LINE_ON_OFF_DASH : even segments are
                 * drawn;\n
                 * odd segments are not drawn.
                 * <li> \c GDK_LINE_DOUBLE_DASH : even segments are
                 * normally.\n
                 * Odd segments are drawn in the background color if the
                 * fill style is GDK_SOLID, or in the background color
                 * masked by the stipple if the fill style is
                 * GDK_STIPPLED.
                 * </ul>
                 */
)
{
        if (!gc)
                return (EXIT_FAILURE);
        if (!line_style)
        {
                fprintf (stderr, "WARNING in %s():  line style = NULL, setting line style  to SOLID.\n",
                        __FUNCTION__);
                line_style = GDK_LINE_SOLID;
                return (EXIT_FAILURE);
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
        return (EXIT_SUCCESS);
}


/*!
 * \brief Set the line width of the Graphics Context.
 *
 * \return \c EXIT_SUCCESS when function is completed,
 * \c EXIT_FAILURE when an eror occurs.
 */
int
preview_set_line_width
(
        GdkGC *gc,
                /*!< : is the Graphics Context. */
        gint line_width
                /*!< : is the line width in pixels [px]. */
)
{
        if ((!gc) || (line_width == 0))
	{
                return (EXIT_FAILURE);
	}
        GdkGCValues gc_values;
        gdk_gc_get_values (gc, &gc_values);
        if (line_width < 0)
        {
                gdk_gc_set_line_attributes
                (
                        gc,
                        abs (line_width),
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
        return (EXIT_SUCCESS);
}


/*!
 * \brief Use a Graphics Context when drawing entities.
 *
 * If the passed Graphics Context is NULL , create a Graphics Context.
 *
 * \return \c EXIT_SUCCESS when function is completed,
 * \c EXIT_FAILURE when an eror occurs.
 */
int
preview_use_gc
(
        GdkDrawable *drawable,
                /*!< : is an opaque structure representing an object that can
                 * be drawn onto.\n
                 * This can be a GdkPixmap, a GdkBitmap, or a GdkWindow.
                 */
        GdkGC *gc,
                /*!< : is the Graphics Context. */
        const char * color_name,
                /*!< : is a \c NULL terminated color name.*/
        gint line_width,
                /*!< : is the line width in pixels [px]. */
        GdkCapStyle line_cap,
                /*!< : determines how the end of lines are drawn.\n
                 * Valid values are:\n
                 * <ul>
                 * <li> \c GDK_CAP_NOT_LAST : the same as GDK_CAP_BUTT
                 * for lines of non-zero width.\n
                 * for zero width lines, the final point on the line
                 * will not be drawn.
                 * <li> \c GDK_CAP_BUTT : the ends of the lines are
                 * drawn squared off and extending to the coordinates of
                 * the end point.
                 * <li> \c GDK_CAP_ROUND : the ends of the lines are
                 * drawn as semicircles with the diameter equal to the
                 * line width and centered at the end point.
                 * <li> \c GDK_CAP_PROJECTING : the ends of the lines
                 * are drawn squared off and extending half the width of
                 * the line beyond the end point.
                 * </ul>
                 */
        GdkLineStyle line_style,
                /*!< : determines how lines are drawn.\n
                 * Valid values are:\n
                 * <ul>
                 * <li> \c GDK_LINE_SOLID : lines are drawn solid.
                 * <li> \c GDK_LINE_ON_OFF_DASH : even segments are
                 * drawn;\n
                 * odd segments are not drawn.
                 * <li> \c GDK_LINE_DOUBLE_DASH : even segments are
                 * normally.\n
                 * Odd segments are drawn in the background color if the
                 * fill style is GDK_SOLID, or in the background color
                 * masked by the stipple if the fill style is
                 * GDK_STIPPLED.
                 * </ul>
                 */
        GdkFill fill_mode
                /*!< : determines how primitives are drawn.\n
                 * Valid values are:\n
                 * <ul>
                 * <li> \c GDK_SOLID : draw with the foreground color.\n
                 * <li> \c GDK_TILED : draw with a tiled pixmap.\n
                 * <li> \c GDK_STIPPLED : draw using the stipple bitmap.\n
                 * Pixels corresponding to bits in the stipple bitmap
                 * that are set will be drawn in the foreground color;\n
                 * pixels corresponding to bits that are not set will be
                 * left untouched.
                 * <li> \c GDK_OPAQUE_STIPPLED : draw using the stipple
                 * bitmap.\n
                 * Pixels corresponding to bits in the stipple bitmap
                 * that are set will be drawn in the foreground color;\n
                 * pixels corresponding to bits that are not set will be
                 * drawn with the background color.\n
                 * </ul>
                 */
)
{
        if (!drawable)
        {
                fprintf (stderr, "WARNING: couldn't allocate a gc, invalid drawable was passed.\n");
                return (EXIT_FAILURE);
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
                return (EXIT_SUCCESS);
        }
}


/*!
 * \brief Draw an arc on the preview pixmap.
 *
 * Draw an arc or a filled 'pie slice'.\n
 * The arc is defined by the bounding rectangle of the entire ellipse, and
 * the start and end angles of the part of the ellipse to be drawn.
 */
static void
preview_draw_arc
(
        GtkWidget *widget,
                /*!< : is the toplevel widget containing the drawable. */
        ArcType *arc
                /*!< : is a pcb arc. */
)
{
        if (!arc)
        {
                fprintf (stderr, "WARNING: passed arc was invalid.\n");
                return;
        }
        /* Create a Graphics Context. */
        GdkGC *gc;
        preview_set_fg_color (gc, PREVIEW_SILK_COLOR);
        preview_set_line_width (gc, arc->Thickness);
        preview_set_line_cap (gc, GDK_CAP_ROUND);
        preview_set_line_style (gc, GDK_SOLID);
        gdk_draw_arc
        (
                widget->window,
                gc,
                FALSE,
                arc->X,
                arc->Y,
                arc->Width,
                arc->Height,
                arc->StartAngle * 64,
                arc->Delta * 64
        );
}


/*!
 * \brief Draw a black background (rectangle) on the screen.
 */
static void
preview_draw_background
(
        GtkWidget *widget,
                /*!< : is the toplevel widget containing the drawable. */
        gdouble x,
                /*!< : is the X-coordinate of the left edge of the background. */
        gdouble y
                /*!< : is the Y-coordinate of the top edge of the background. */
)
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
 * \brief Draw a circle on the preview pixmap.
 *
 * Draw a filled circle, using the background color and other
 * attributes of the GdkGC.
 */
static void
preview_draw_filled_circle
(
        GtkWidget *widget,
                /*!< : is the toplevel widget containing the drawable. */
        ArcType *arc
                /*!< : is a pcb line. */
)
{
        if (!arc)
        {
                fprintf (stderr, "WARNING: passed arc was invalid.\n");
                return;
        }
        /* Create a Graphics Context. */
        GdkGC *gc;
        preview_set_fg_color (gc, PREVIEW_BG_COLOR);
        preview_set_line_width (gc, arc->Thickness);
        preview_set_line_cap (gc, GDK_CAP_ROUND);
        preview_set_line_style (gc, GDK_SOLID);
        gdk_draw_arc
        (
                widget->window,
                gc,
                TRUE,
                arc->X,
                arc->Y,
                arc->Width,
                arc->Height,
                arc->StartAngle,
                arc->Delta
        );
}


/*!
 * \brief Draw a line on the preview pixmap.
 *
 * Draw a line, using the silkscreen color and other attributes of the
 * GdkGC.
 */
static void
preview_draw_line
(
        GtkWidget *widget,
                /*!< : is the toplevel widget containing the drawable. */
        LineType *line
                /*!< : is a pcb line. */
)
{
        if (!line)
        {
                fprintf (stderr, "WARNING: passed line was invalid.\n");
                return;
        }
        /* Create a Graphics Context. */
        GdkGC *gc;
        preview_set_fg_color (gc, PREVIEW_SILK_COLOR);
        preview_set_line_width (gc, line->Thickness);
        preview_set_line_cap (gc, GDK_CAP_ROUND);
        preview_set_line_style (gc, GDK_SOLID);
        gdk_draw_line
        (
                widget->window,
                gc,
                line->Point1.X,
                line->Point1.Y,
                line->Point2.X,
                line->Point2.Y
        );
}


/*!
 * \brief Draw a pad on the preview pixmap.
 *
 * Draw a pad, using the copper color and other attributes of the
 * GdkGC.
 */
static void
preview_draw_pad
(
        GtkWidget *widget,
                /*!< : is the toplevel widget containing the drawable. */
        ElementType *element,
                /*!< : is an pcb element. */
        PadType *pad
                /*!< : is a pcb pad. */
)
{
        if (TEST_FLAG (SQUAREFLAG, pad))
        {
                /* Create a Graphics Context with a \c SQUARE line cap
                 * extending with half the thickness. */
                GdkGC *gc;
                preview_set_fg_color (gc, PREVIEW_COPPER_COLOR);
                preview_set_line_width (gc, pad->Thickness);
                preview_set_line_cap (gc, GDK_CAP_PROJECTING);
                preview_set_line_style (gc, GDK_SOLID);
                gdk_draw_line
                (
                        widget->window,
                        gc,
                        pad->Point1.X,
                        pad->Point1.Y,
                        pad->Point2.X,
                        pad->Point2.Y
                );
        }
        else
        {
                /* Create a Graphics Context with a \c ROUND line cap. */
                GdkGC *gc;
                preview_set_fg_color (gc, PREVIEW_COPPER_COLOR);
                preview_set_line_width (gc, pad->Thickness);
                preview_set_line_cap (gc, GDK_CAP_ROUND);
                preview_set_line_style (gc, GDK_SOLID);
                gdk_draw_line
                (
                        widget->window,
                        gc,
                        pad->Point1.X,
                        pad->Point1.Y,
                        pad->Point2.X,
                        pad->Point2.Y
                );
        }
}


/*!
 * \brief Draw a pin on the preview pixmap.
 *
 * Draw a pin, using the copper color and other attributes of the
 * GdkGC.

 */
static void
preview_draw_pin
(
        GtkWidget *widget,
                /*!< : is the toplevel widget containing the drawable. */
        ElementType *element,
                /*!< : is an pcb element. */
        PinType *pin
                /*!< : is a pcb pad. */
)
{
        /* First draw the anulus in copper color.*/
        if (TEST_FLAG (OCTAGONFLAG, pin))
        {
                /*
                 * Draw a polygon.
                 * x and y are already in display coordinates.
                 * The points are numbered:
                 *
                 *          5 --- 6
                 *         /       \
                 *        4         7
                 *        |         |
                 *        3         0
                 *         \       /
                 *          2 --- 1
                 */
                static FloatPolyType p[8] =
                {
                    {0.5, -TAN_22_5_DEGREE_2},
                    {TAN_22_5_DEGREE_2, -0.5},
                    {-TAN_22_5_DEGREE_2, -0.5},
                    {-0.5, -TAN_22_5_DEGREE_2},
                    {-0.5, TAN_22_5_DEGREE_2},
                    {-TAN_22_5_DEGREE_2, 0.5},
                    {TAN_22_5_DEGREE_2, 0.5},
                    {0.5, TAN_22_5_DEGREE_2}
                };
                GdkPoint *points[9];
                int polygon_x[9]; /* X-coordinates of vertices */
                int polygon_y[9]; /* Y-coordinates of vertices */
                int i;

                for (i = 0; i < 8; i++)
                {
                        points[i]->x = pin->X + (p[i].X * pin->Thickness);
                        points[i]->y = pin->Y + (p[i].Y * pin->Thickness);
                }
                /* Create a Graphics Context with a \c ROUND line cap
                 * extending with half the thickness. */
                GdkGC *gc;
                preview_set_fg_color (gc, PREVIEW_COPPER_COLOR);
                preview_set_line_width (gc, pin->Thickness);
                preview_set_line_cap (gc, GDK_CAP_ROUND);
                preview_set_line_style (gc, GDK_SOLID);
                gdk_draw_polygon
                (
                        widget->window,
                        gc,
                        TRUE,
                        points,
                        8
                );
        }
        else if (TEST_FLAG (SQUAREFLAG, pin))
        {
                /* Create a Graphics Context with a \c SQUARE line cap
                 * extending with half the thickness. */
                GdkGC *gc;
                preview_set_fg_color (gc, PREVIEW_COPPER_COLOR);
                preview_set_line_width (gc, pin->Thickness);
                preview_set_line_cap (gc, GDK_CAP_PROJECTING);
                preview_set_line_style (gc, GDK_SOLID);
                /* Draw a zero length line. */
                gdk_draw_line
                (
                        widget->window,
                        gc,
                        pin->X,
                        pin->Y,
                        pin->X,
                        pin->Y
                );
        }
        else
        {
                /* Create a Graphics Context with a \c ROUND line cap. */
                GdkGC *gc;
                preview_set_fg_color (gc, PREVIEW_COPPER_COLOR);
                preview_set_line_width (gc, pin->Thickness);
                preview_set_line_cap (gc, GDK_CAP_ROUND);
                preview_set_line_style (gc, GDK_SOLID);
                /* Draw a zero length line. */
                gdk_draw_line
                (
                        widget->window,
                        gc,
                        pin->X,
                        pin->Y,
                        pin->X,
                        pin->Y
                );
        }
        /* Create a Graphics Context with a \c ROUND line cap. */
        GdkGC *gc;
        preview_set_fg_color (gc, PREVIEW_BG_COLOR);
        preview_set_line_width (gc, (int) (0.5 * pin->DrillingHole));
        preview_set_line_cap (gc, GDK_CAP_ROUND);
        preview_set_line_style (gc, GDK_SOLID);
        /* Draw a drilling hole for the pin in background color. */
        gdk_draw_arc
        (
                widget->window,
                gc,
                TRUE,
                pin->X,
                pin->Y,
                pin->DrillingHole,
                pin->DrillingHole,
                0,
                360 * 64
        );
}


/*!
 * \brief Draw a pin on the preview pixmap.
 */
static void
preview_draw_polygon
(
        GtkWidget *widget,
                /*!< : is the toplevel widget containing the drawable. */
        preview_polygon polygon
                /*!< : is a preview polygon. */
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
        GtkWidget *widget,
                /*!< : is the toplevel widget containing the drawable. */
        preview_rectangle rectangle
                /*!< : is a preview rectangle. */
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
 *
 * \return \c FALSE when function is completed.
 */
static gboolean
preview_expose_event
(
        GtkWidget *widget,
                /*!< : is the toplevel widget containing the drawable. */
        GdkEventExpose *event
                /*!< : is the event passed from the caller.*/
)
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

        /*! \todo Add code here to draw footprints.*/
        /* Draw all element pads. */
	PAD_LOOP (preview_element);
                preview_draw_pad (widget, preview_element, pad);
        END_LOOP;
        /* Draw all element pins. */
	PIN_LOOP (preview_element);
        END_LOOP;
        /* Draw the soldermask. */
        /* Draw all element arcs. */
        ELEMENTARC_LOOP (preview_element);
                preview_draw_arc (widget, arc);
        END_LOOP;
        /* Draw all element lines. */
        ELEMENTLINE_LOOP (preview_element);
                preview_draw_line (widget, line);
        END_LOOP;
        /* Draw all element texts. */
        /* Draw a marker. */
        return FALSE;
}


/*!
 * \brief Create a preview window containing a pixmap with the
 * footprint.
 *
 * The \c footprint_name variable is used in the dialog title.
 *
 * \return 0 when successfull.
 */
int
preview_create_window
(
        ElementType *preview_element
                /*!< : is the element we want to preview.*/
)
{
        gint width; /* is the width of the pixmap.*/
        gint height; /* is the height of the pixmap.*/

        /* Create a preview window. */
        GtkWidget *preview_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        /* Destroy the preview window when the main window of pcb-gfpw gets
         * destroyed. */
        gtk_window_set_destroy_with_parent (GTK_WINDOW (preview_window), TRUE);
        /* Set the preview window title. */
        gchar *preview_window_title = g_strdup_printf ("pcb-fpw preview: %s",
                preview_element->Name[0]);
        gtk_window_set_title (GTK_WINDOW (preview_window),
                preview_window_title);
        g_free (preview_window_title);
        gtk_container_set_border_width (GTK_CONTAINER (preview_window), 10);
        /* Set signals for the window. */
        gtk_signal_connect
        (
                GTK_OBJECT (preview_window),
                "delete_event",
                (GtkSignalFunc) preview_delete_event,
                NULL
        );
        /* Create a horizontal box. */
        /* Create a vertical box for the solderside. */
        GtkWidget *vbox = gtk_vbox_new (FALSE, 10);
        gtk_container_add (GTK_CONTAINER (preview_window), vbox);
        /* Create a preview drawing area. */
        GtkWidget *preview_drawing_area = gtk_drawing_area_new ();
        width = 300;
	height = 200;
        gtk_widget_set_size_request (preview_drawing_area, width, height);
        /* Set signals for the drawing area. */
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
