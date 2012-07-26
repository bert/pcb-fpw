/*!
 * \file src/gtk2/support.h
 *
 * \author Copyright 2007, 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for support functions for pcb-gfpw (GTK2 UI).
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


#ifndef __SUPPORT_INCLUDED__
#define __SUPPORT_INCLUDED__


#ifdef HAVE_CONFIG_H
#        include <config.h>
#endif

#include <gtk/gtk.h>


/* Standard gettext macros. */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  define Q_(String) g_strip_context ((String), gettext (String))
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define Q_(String) g_strip_context ((String), (String))
#  define N_(String) (String)
#endif /* ENABLE_NLS */


#define GLADE_HOOKUP_OBJECT(component,widget,name) \
        g_object_set_data_full (G_OBJECT (component), name, \
        gtk_widget_ref (widget), (GDestroyNotify) gtk_widget_unref)

#define GLADE_HOOKUP_OBJECT_NO_REF(component,widget,name) \
        g_object_set_data (G_OBJECT (component), name, widget)


GtkWidget* lookup_widget (GtkWidget  *widget, const gchar *widget_name);
void add_pixmap_directory (const gchar *directory);
GtkWidget* create_pixmap (GtkWidget *widget, const gchar *filename);
GdkPixbuf* create_pixbuf (const gchar *filename);
void glade_set_atk_action_description (AtkAction *action, const gchar *action_name, const gchar *description);


#endif /* __SUPPORT_INCLUDED__ */


/* EOF */
