/*!
 * \file src/preview.c
 *
 * \author Copyright (C) 2007-2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
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
#include <cairo.h>
#include "preview.h"


/* Default color definitions (in hexadecimal triplets). */
#define COLOR_COPPER 0xb87333 /* copper-like */
        /*!< : color of pins and pads. */
#define COLOR_COURTYARD 0xff00ff /* magenta */
        /*!< : color for the courtyard (keepout area of packages). */
#define COLOR_DIMENSION 0x000000 /* black */
        /*!< : color for dimensions. */
#define COLOR_FR4 0xdbd640 /* a kind of sand-like color */
        /*!< : color of the base material FR4. */
#define COLOR_MARKER 0xff0000 /* red */
        /*!< : color for the center marker. */
#define COLOR_SILKSCREEN 0xffffff /* white */
        /*!< : color of the silkscreen. */
#define COLOR_SOLDERMASK 0x009900 /* greenish */
        /*!< : color of the solder resist mask. */
#define COLOR_TRANSPARENT 0x000000 /* is that a color */
        /*!< : transparent color. */
#define TRANSPARENCY 0.9
        /*!< : factor for transparency. */
#define MARK_SIZE_LINE_WIDTH 100 /* in mils/100 ? */
        /*!< Size of diamond element mark. */


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
 * \brief Create a preview window containing a pixmap with the
 * footprint.
 *
 * The \c footprint_name variable is used in the dialog title.
 *
 * \return 0 when successful.
 */
int
preview_create_window
(
        ElementType *element
)
{
        gint width_pixels;
        gint height_pixels;

        width_pixels = (int) (element->VBox.X2 - element->VBox.X1);
        height_pixels = (int) (element->VBox.Y2 - element->VBox.Y1);
        
        GtkWidget *preview_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
        /* Destroy the preview window when the main window of pcb-gfpw gets
         * destroyed */
        gtk_window_set_destroy_with_parent (GTK_WINDOW (preview_window), TRUE);
        /* Set the preview window title */
        gchar *preview_window_title = g_strdup_printf ("pcb-fpw preview: %s",
                footprint_name);
        gtk_window_set_title (GTK_WINDOW (preview_window),
                preview_window_title);
        g_free (preview_window_title);
        gtk_container_set_border_width (GTK_CONTAINER (preview_window), 10);
        /* Set signals for the window */
        g_signal_connect
        (
                GTK_OBJECT (preview_window),
                "delete_event",
                (GtkSignalFunc) preview_delete_event,
                NULL
        );
        /* Create a vertical box */
        GtkWidget *vbox = gtk_vbox_new (FALSE, 10);
        gtk_container_add (GTK_CONTAINER (preview_window), vbox);
        /* Create a preview drawing area */
        GtkWidget *preview_drawing_area = gtk_drawing_area_new ();
        gtk_widget_set_size_request (preview_drawing_area,
                width_pixels,
                height_pixels);
        /* Set signals for the drawing area */
        g_signal_connect
        (
                GTK_OBJECT (preview_drawing_area),
                "expose_event",
                (GtkSignalFunc) preview_expose_event,
                NULL
        );
        g_signal_connect
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
                width_pixels + 50,
                height_pixels + 50
        );
        /* Show the window */
        gtk_widget_realize (preview_window);
        gtk_widget_show_all (preview_window);
        /* Enter the GTK main loop */
        gtk_main ();
        return 0;
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
 * \brief Draw an arc on the preview pixmap.
 *
 * Draws an arc or a filled 'pie slice'.\n
 * The arc is defined by the bounding rectangle of the entire ellipse, and
 * the start and end angles of the part of the ellipse to be drawn.
 */
static void
preview_draw_arc
(
        cairo_t *cr,
                /*!< : is a cairo drawing context. */
        ArcType *arc
                /*!< : is a preview line. */
)
{
        gdouble start_angle;
        gdouble delta_angle;
        gdouble dashes[] = 
        {
                5.0,  /* ink */
                1.0,  /* skip */
                1.0,  /* ink */
                1.0   /* skip*/
        };
        gint num_dashes;
        gdouble offset;


        if ((!arc) || (!cr))
        {
                fprintf (stderr, "WARNING: passed arc was invalid.\n");
                return;
        }
        /* Modify angles from degrees to cairo format */
        start_angle = arc->StartAngle * (M_PI / 180.0);
        delta_angle = arc->Delta * (M_PI / 180.0);
        /* Set up the cairo context. */
        cairo_set_line_width (cr, arc->Thickness);
        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
        num_dashes = 0;
        offset = -5.0;
        cairo_set_dash (cr, dashes, num_dashes, offset);
        /* Draw the arc. */
        cairo_arc
        (
                cr,
                arc->X,
                arc->Y,
                arc->Width / 2,
                start_angle,
                delta_angle
        );
        cairo_stroke (cr);
}


/*!
 * \brief Draw a white background (rectangle) on the screen.
 */
static int
preview_draw_background
(
        cairo_t *cr
                /*!< : is a cairo drawing context. */
)
{
        gdouble _red;
        gdouble _green;
        gdouble _blue;
        gdouble _alpha;

        if (!cr)
        {
                return (EXIT_FAILURE);
        }
        /* Convert hexadecimal color triplet to cairo RGBA values. */
        _red = ((COLOR_FR4 >> 16) & 0xff) / 255.0;  /* Extract the RR byte. */
        _green = ((COLOR_FR4 >> 8) & 0xff) / 255.0;  /* Extract the GG byte. */
        _blue = ((COLOR_FR4) & 0xff) / 255.0;  /* Extract the BB byte. */
        _alpha = TRANSPARENCY;
        cairo_set_source_rgba (cr, _red, _green, _blue, _alpha);
        /* Setup the background to transparent fill. */
        cairo_fill (cr);
        return (EXIT_SUCCESS);
}


/*!
 * \brief Draw a line on the preview canvas.
 */
static int
preview_draw_courtyard
(
        cairo_t *cr,
                /*!< : is a cairo drawing context. */
        gint xmin,
                /*!< : X-value of the upper left corner coordinate. */
        gint ymin,
                /*!< : Y-value of the upper left corner coordinate. */
        gint xmax,
                /*!< : X-value of the lower right corner coordinate. */
        gint ymax
                /*!< : Y-value of the lower right corner coordinate. */
)
{
        gdouble dashes[] = 
        {
                5.0,  /* ink */
                1.0,  /* skip */
                1.0,  /* ink */
                1.0   /* skip*/
        };
        gint num_dashes;
        gdouble offset;

        if (!cr)
        {
                fprintf (stderr, "WARNING: passed preview data was invalid.\n");
                return (EXIT_FAILURE);
        }
        num_dashes = sizeof (dashes) / sizeof (dashes[0]);
        //num_dashes = 0;
        offset = -5.0;
        cairo_set_dash (cr, dashes, num_dashes, offset);
        cairo_move_to (cr, xmin, ymin);
        cairo_line_to (cr, xmax, ymin);
        cairo_line_to (cr, xmax, ymax);
        cairo_line_to (cr, xmin, ymax);
        cairo_close_path (cr);
        cairo_stroke (cr);
        return (EXIT_SUCCESS);
}

/*!
 * \brief Draw a line on the preview canvas.
 */
static int
preview_draw_line
(
        cairo_t *cr,
                /*!< : is a cairo drawing context. */
        LineType *line
                /*!< : is the line to be drawn on the preview canvas. */
)
{
        if (!line)
        {
                fprintf (stderr, "WARNING: passed line was invalid.\n");
                return (EXIT_FAILURE);
        }
        /* Set up the cairo context. */
        cairo_set_line_width (cr, line->Thickness);
        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
        /* Draw the line. */
        cairo_stroke (cr);
        return (EXIT_SUCCESS);
}


/*!
 * \brief Draw a mark on the preview canvas.
 */
static int
preview_draw_mark
(
        cairo_t *cr,
                /*!< : is a cairo drawing context. */
        LocationType Mark_X,
                /*!< : is the X-value of the location of the mark to be
                 * drawn on the preview canvas. */
        LocationType Mark_Y
                /*!< : is the Y-value of the location of the mark to be
                 * drawn on the preview canvas. */
)
{
        if (!Mark_X)
        {
                fprintf (stderr, "WARNING: passed mark was invalid.\n");
                return;
        }
        /* Set up the cairo context. */
        cairo_set_line_width (cr, (MARK_SIZE_LINE_WIDTH)); 
        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
        /* Draw the line. */
        cairo_move_to (cr, (Mark_X - (MARK_SIZE / 2.0)), Mark_Y);
        cairo_line_to (cr, (Mark_X + (MARK_SIZE / 2.0)), Mark_Y);
        cairo_move_to (cr, Mark_X, (Mark_Y - (MARK_SIZE / 2.0)));
        cairo_line_to (cr, Mark_X, (Mark_Y + (MARK_SIZE / 2.0)));
        cairo_stroke (cr);
}


/*!
 * \brief Draw a pad on the preview canvas.
 */
static int
preview_draw_pad
(
        cairo_t *cr,
                /*!< : is a cairo drawing context. */
        PadType *pad
                /*!< : is the pad to be drawn on the preview canvas. */
)
{
        if (!pad)
        {
                fprintf (stderr, "WARNING: passed pad was invalid.\n");
                return (EXIT_FAILURE);
        }
        /* Set up the cairo context. */
        cairo_set_line_width (cr, pad->Thickness);
        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
        if (TEST_FLAG (SQUAREFLAG, pad))
        {
                cairo_set_line_cap (cr, CAIRO_LINE_CAP_SQUARE);
        }
        else if (TEST_FLAG (OCTAGONFLAG, pad))
        {
                fprintf (stderr, "WARNING: octagon end cap is not valid for a pad entity.\n");
                return (EXIT_FAILURE);
        }
        else
        {
        }
        /* Draw the pad. */
        /*! \todo Add code here.*/
        cairo_stroke (cr);
}


/*!
 * \brief Draw a pin on the preview canvas.
 */
static int
preview_draw_pin
(
        cairo_t *cr,
                /*!< : is a cairo drawing context. */
        PinType *pin
                /*!< : is the pin to be drawn on the preview canvas. */
)
{
        if (!pin)
        {
                fprintf (stderr, "WARNING: passed pin was invalid.\n");
                return (EXIT_FAILURE);
        }
        /* Set up the cairo context. */
        cairo_set_line_width (cr, 1.0);
        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
        /* Draw the pin. */
        if (TEST_FLAG (SQUAREFLAG, pin))
        {
                preview_set_fg_color (cr, COLOR_COPPER);
                cairo_move_to (cr, (pin->X - pin->Thickness),
                        (pin->Y - pin->Thickness)); /* Top left corner. */
                cairo_line_to (cr, (pin->X + pin->Thickness),
                        (pin->Y - pin->Thickness)); /* Top right corner. */
                cairo_move_to (cr, (pin->X + pin->Thickness),
                        (pin->Y + pin->Thickness)); /* Bottom right corner. */
                cairo_line_to (cr, (pin->X - pin->Thickness),
                        (pin->Y + pin->Thickness)); /* Bottom left corner. */
                cairo_close_path (cr); /* Back to the top left corner. */
                cairo_fill (cr);
        }
        else if (TEST_FLAG (OCTAGONFLAG, pin))
        {
                return (EXIT_FAILURE);
        }
        else /* Default is ROUND. */
        {
                preview_set_fg_color (cr, COLOR_COPPER);
                cairo_arc (cr, pin->X, pin->Y, (pin->Thickness / 2.0), 0, (2 * M_PI));
                cairo_fill (cr);
        }
        /* Draw the drill hole. */
        preview_set_fg_color (cr, COLOR_TRANSPARENT);
        cairo_arc (cr, pin->X, pin->Y, (pin->DrillingHole / 2.0), 0, (2 * M_PI));
        cairo_fill (cr);
}


/*!
 * \brief Draw a mask on the preview canvas.
 */
static int
preview_draw_soldermask
(
        cairo_t *cr,
                /*!< : is a cairo drawing context. */
        PolygonType *polygon
                /*!< : is a polygon. */
)
{
        if (!polygon)
        {
                fprintf (stderr, "WARNING: passed polygon was invalid.\n");
                return;
        }
        /* Set up the cairo context. */
        cairo_set_line_width (cr, 1.0);
        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
        preview_set_fg_color (cr, COLOR_SOLDERMASK);
        /*! \todo Add code here. */
}


/*!
 * \brief Draw a text on the preview canvas.
 */
static int
preview_draw_text
(
        cairo_t *cr,
                /*!< : is a cairo drawing context. */
        ElementTypePtr element
                /*!< : is the element containing the text string to be
                 * drawn. */
)
{
        /* Set up the cairo context. */
        cairo_set_line_width (cr, 1.0);
        cairo_set_line_cap (cr, CAIRO_LINE_CAP_ROUND);
        preview_set_fg_color (cr, COLOR_SILKSCREEN);
        /*! \todo Add code here. */
}


/*!
 * \brief Redraw the screen.
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
        cairo_t *cr;
        LineType *line;
        PadType *pad;
        EndCapStyle end_cap;

        /* Get a cairo drawing context. */
        cr = gdk_cairo_create (widget->window);
        preview_draw_background (cr);
        /* Walk the data in the current element and create strokes
         * accordingly.
         * Start at prepreg and badger through all stuff until the
         * silkscreen is reached.
         */
        preview_set_fg_color (cr, COLOR_COPPER);
        PAD_LOOP (current_element);
        {
                if (ON_SIDE (pad, COMPONENT_LAYER))
                {
                        preview_draw_pad (cr, pad);
                }
        }
        END_LOOP;
        PIN_LOOP (current_element);
        {
                preview_draw_pin (cr, pin);
        }
        END_LOOP;
        preview_set_fg_color (cr, COLOR_SOLDERMASK);
        /* Draw the soldermask. */
        preview_set_fg_color (cr, COLOR_SILKSCREEN);
        ELEMENTLINE_LOOP (current_element);
        {
                preview_draw_line (cr, line);
        }
        END_LOOP;
        ARC_LOOP (current_element);
        {
                preview_draw_arc (cr, arc);
        }
        END_LOOP;
        preview_draw_text (cr, current_element);
        preview_set_fg_color (cr, COLOR_MARKER);
        preview_draw_mark 
        (
                cr,
                current_element->MarkX,
                current_element->MarkY
        );
        preview_set_fg_color (cr, COLOR_COURTYARD);
        preview_draw_courtyard
        (
                cr,
                current_element->VBox.X1,
                current_element->VBox.Y1,
                current_element->VBox.X2,
                current_element->VBox.Y2
        );
        cairo_paint (cr);
        /* Clean up the drawing context. */
        cairo_destroy (cr);
        return FALSE;
}


/*!
 * \brief Set the line capsulation of the Graphics Context.
 *
 * \return \c EXIT_SUCCESS when function is completed,
 * \c EXIT_FAILURE when an eror occurs.
 */
int
preview_set_end_cap
(
        EndCapStyle end_cap,
                /*!< : is the end cap style. */
        cairo_t *cr
                /*!< : is a cairo drawing context. */
)
{
        if (!cr)
                return (EXIT_FAILURE);
        if (!end_cap)
        {
                fprintf (stderr, "WARNING in %s(): end cap = NULL.\n",
                        __FUNCTION__);
                return (EXIT_FAILURE);
        }
        cairo_set_line_cap  (cr, end_cap);
        return (EXIT_SUCCESS);
}


/*!
 * \brief Set the foreground color in the cairo context.
 *
 * \return \c EXIT_SUCCESS when function is completed,
 * \c EXIT_FAILURE when an eror occurred.
 */
int
preview_set_fg_color
(
        cairo_t *cr,
                /*!< : is a cairo drawing context. */
        gint preview_color
                /*!< : is a color hexadecimal triplet (0xRRGGBB).*/
)
{
        gdouble _red;
        gdouble _green;
        gdouble _blue;
        gdouble _alpha;

        if (!cr)
        {
                return (EXIT_FAILURE);
        }
        /* Convert hexadecimal color triplet to cairo RGBA values. */
        _red = ((preview_color >> 16) & 0xff) / 255.0;  /* Extract the RR byte. */
        _green = ((preview_color >> 8) & 0xff) / 255.0;  /* Extract the GG byte. */
        _blue = ((preview_color) & 0xff) / 255.0;  /* Extract the BB byte. */
        _alpha = TRANSPARENCY;
        cairo_set_source_rgba (cr, _red, _green, _blue, _alpha);
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


static void
preview_zoom_fit
(
        PreviewDataType *preview_data,
                /*!< : all the needed stuff for the preview window. */
        gint zoom
                /*!< : new zoom factor */
)
{
        gint width_pixels;
        gint height_pixels;

        preview_data->zoom = zoom;
        preview_data->scale = 1.0 / (100.0 * exp (preview_data->zoom * LN_2_OVER_2));
        preview_data->xmax = preview_data->element.VBox.X2;
        preview_data->ymax = preview_data->element.VBox.Y2;
        width_pixels = (gint) (preview_data->scale *
                (preview_data->element.VBox.X2 -
                preview_data->element.VBox.X1));
        height_pixels = (gint) (preview_data->scale *
                (preview_data->element.VBox.Y2 -
                preview_data->element.VBox.Y1));
}


/* EOF */
