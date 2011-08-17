/*!
 * \file src/select_exceptions.h
 *
 * \author Copyright (C) 2007-2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for a widget for selecting exception pin/pads in an array type footprint.
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


#ifndef __SELECT_EXCEPTIONS_INCLUDED__
#define __SELECT_EXCEPTIONS_INCLUDED__

G_BEGIN_DECLS /* keep c++ happy */

#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib.h>


#define MAX_ROWS 100
#define MAX_COLUMNS 100


/*!
 * \brief Selection button wrapper type.
 */
typedef struct
{
        GtkWidget *button_widget;
                /*!< : is the button widget appearing in the dialog window.*/
        gchar *name;
                /*!< : is the name of the button widget.*/
        gboolean active;
                /*!< : is the state of the button,*/
        gint id;
                /*!< : is the identificatoion number (sequential) of the
                 * button.*/
} SelectionButtonSet;


static void select_exceptions_clear_cb (GtkWidget *, GtkWidget *);
static void select_exceptions_close_cb (GtkWidget *, GtkWidget *);
static void select_exceptions_delete_event (GtkWidget *, GdkEvent *);
static void select_exceptions_ok_cb (GtkWidget *, GtkWidget *);
static void select_exceptions_selection_button_clicked_cb (GtkWidget *, GtkWidget *);
int select_exceptions_create_window (gint, gint);

G_END_DECLS /* keep c++ happy */

#endif /* __SELECT_EXCEPTIONS_INCLUDED__ */


/* EOF */
