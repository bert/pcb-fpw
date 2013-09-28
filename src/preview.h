/*!
 * \file src/preview.h
 *
 * \author Copyright (C) 2007-2013 by Bert Timmerman <bert.timmerman@xs4all.nl>
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

G_BEGIN_DECLS /* keep c++ happy */

GdkPixmap *pixmap = NULL;
        /*!< Backing pixmap for drawing area */


typedef struct
{
        ElementType element;
                /*!< The element data to display. */
        gfloat zoom;
                /*!< Zoom factor of window. */
        gfloat scale;
                /*!< Scale factor of zoom. */
        gint xmin;
                /*!< X-value of the upper left corner coordinate. */
        gint ymin;
                /*!< Y-value of the upper left corner coordinate. */
        gint xmax;
                /*!< X-value of the lower right corner coordinate. */
        gint ymax;
                /*!< Y-value of the lower right corner coordinate. */
        gint shape;
                /*!< Shape of the courtyard.
                 * <ul>
                 * <li> 0 = rectangular.
                 * <li> 1 = circular.
                 * </ul>
                 */
} PreviewDataType, *PreviewDataTypePtr;
 

static void preview_close_cb (GtkWidget * widget, GtkWidget *preview_window);
static gboolean preview_configure_event (GtkWidget *widget, GdkEventConfigure *event);
int preview_create_window (ElementType *element);
void preview_delete_event (GtkWidget *widget, GdkEvent *event);
static void preview_draw_arc (cairo_t *cr, ArcType *arc);
static int preview_draw_background (cairo_t *cr);
static int preview_draw_courtyard (cairo_t *cr, gint xmin, gint ymin, gint xmax, gint ymax);
static int preview_draw_line (cairo_t *cr, LineType *line);
static int preview_draw_mark (cairo_t *cr, LocationType Mark_X, LocationType Mark_Y);
static int preview_draw_pad (cairo_t *cr, PadType *pad);
static int preview_draw_pin (cairo_t *cr, PinType *pin);
static int preview_draw_refdes (cairo_t *cr, ElementTypePtr element);
static int preview_draw_soldermask (cairo_t *cr, PolygonType *polygon);
static int preview_draw_text (cairo_t *cr, gchar *text, gdouble x, gdouble y, gdouble height, direction_t rotation, location_t justification);
static gboolean preview_expose_event (GtkWidget *widget, GdkEventExpose *event);
int preview_set_end_cap (cairo_t *cr,EndCapStyle endcap);
int preview_set_fg_color (cairo_t *cr, gint preview_color);
int preview_set_fill_mode (GdkGC *gc, GdkFill fill_mode);
int preview_set_line_style (GdkGC *gc, GdkLineStyle line_style);
int preview_set_line_width (GdkGC *gc, gint line_width);

G_END_DECLS /* keep c++ happy */

#endif /* __PREVIEW_INCLUDED__ */


/* EOF */
