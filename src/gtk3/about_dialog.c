/*!
 * \file src/gtk3/about_dialog.c
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief About dialog for pcb-gfpw (GTK3 UI).
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


#include "about_dialog.h"


/*!
 * \brief The close button of the about dialog is clicked.
 *
 * <b>Parameters:</b> \c *dialog is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_about_dialog_close
(
        GtkDialog *dialog,
        gpointer user_data
)
{
        GtkWidget *about_dialog = lookup_widget (GTK_WIDGET (dialog),
                "about_dialog");
        gtk_widget_destroy (about_dialog);
}


/*!
 * \brief The destroy button of the about dialog is clicked.
 *
 * <b>Parameters:</b> \c *object is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_about_dialog_destroy
(
        GtkDialog *dialog,
        gpointer user_data
)
{
        GtkWidget *about_dialog = lookup_widget (GTK_WIDGET (dialog),
                "about_dialog");
        gtk_widget_destroy (about_dialog);
}


/*!
 * \brief Create an about dialog.
 *
 * <b>Parameters:</b> \c void.\n
 * \n
 * <b>Returns:</b> GtkWidget \c about_dialog.
 */
GtkWidget
*create_about_dialog (void)
{
    GtkBuilder *builder; 
    GtkWidget *about_dialog;

    builder = gtk_builder_new ();
    gtk_builder_add_from_file (builder, "about_dialog.glade", NULL);
    about_dialog = GTK_WIDGET (gtk_builder_get_object (builder, "about_dialog"));
    gtk_builder_connect_signals (builder, NULL);
    g_object_unref (G_OBJECT (builder));
    gtk_widget_show (about_dialog);                
    return about_dialog;
}


/* EOF */
