/* just some rambling code for a preview widget */

GdkWindow  *window = NULL;

/* we probably have to look up the widget/window */

/* Create a drawing area */
GtkWidget *drawing_area = gtk_drawing_area_new ();
gint width = 100;
gint height = 100;
gint depth = -1;
gtk_widget_set_size_request (drawing_area, width, height);


/* Backing pixmap for drawing area */
static GdkPixmap *pixmap = NULL;


/* Create a new backing pixmap of the appropriate size */
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


/* Redraw the screen from the backing pixmap */
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


/* Draw a white rectangle on the screen */
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
        | GDK_LEAVE_NOTIFY_MASK


