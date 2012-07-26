/*!
 * \file src/gtk2/about_dialog.c
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief About dialog for pcb-gfpw (GTK UI).
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


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>

#include "../globals.h"
#include "about_dialog.h"
#include "callbacks.h"
#include "support.h"


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
on_about_dialog_close                  (GtkDialog       *dialog,
                                        gpointer         user_data)
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
on_about_dialog_destroy                (GtkDialog       *dialog,
                                        gpointer         user_data)
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
GtkWidget*
create_about_dialog (void)
{
        GtkWidget *about_dialog;
        const gchar *authors[] =
        {
                "Bert Timmerman <bert.timmerman@xs4all.nl>",
                NULL
        };
        /* TRANSLATORS: Replace this string with your names, one name per line. */
        gchar *translators = "Bert Timmerman (nl)";
        GdkPixbuf *about_dialog_logo_pixbuf;

        about_dialog = gtk_about_dialog_new ();
        gtk_widget_set_name (about_dialog, "about_dialog");
        gtk_about_dialog_set_version (GTK_ABOUT_DIALOG (about_dialog), GIT_VERSION);
        gtk_about_dialog_set_name (GTK_ABOUT_DIALOG (about_dialog), _("pcb-gfpw"));
        gtk_about_dialog_set_copyright (GTK_ABOUT_DIALOG (about_dialog), _("(C) 2007, 2008, 2009, 2010 Bert Timmerman."));
        gtk_about_dialog_set_comments (GTK_ABOUT_DIALOG (about_dialog), _("The pcb FootPrintWizard generates footprint files for the pcb layout editor.\n(see http://pcb.gpleda.org)\n"));
        gtk_about_dialog_set_license (GTK_ABOUT_DIALOG (about_dialog), _("This program is free software; you can redistribute it and/or modify\nit under the terms of the GNU General Public License as published by\nthe Free Software Foundation; either version 2 of the License, or\n(at your option) any later version.\n\nThis program is distributed in the hope that it will be useful,\nbut WITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\nSee the GNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License\nalong with this program; if not, write to:\nthe Free Software Foundation, Inc.,\n51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\n"));
        gtk_about_dialog_set_website (GTK_ABOUT_DIALOG (about_dialog), "http://www.xs4all.nl/~ljh4timm/pcb-fpw/pcb-fpw.html");
        gtk_about_dialog_set_authors (GTK_ABOUT_DIALOG (about_dialog), authors);
        gtk_about_dialog_set_translator_credits (GTK_ABOUT_DIALOG (about_dialog), translators);
        about_dialog_logo_pixbuf = create_pixbuf ("splash_wiz.xpm");
        gtk_about_dialog_set_logo (GTK_ABOUT_DIALOG (about_dialog), about_dialog_logo_pixbuf);
        g_signal_connect
        (
                (gpointer) about_dialog,
                "close",
                G_CALLBACK (on_about_dialog_close),
                NULL
        );
        g_signal_connect
        (
                (gpointer) about_dialog,
                "destroy",
                G_CALLBACK (on_about_dialog_destroy),
                NULL
        );
        /* Store pointers to all widgets, for use by lookup_widget(). */
        GLADE_HOOKUP_OBJECT_NO_REF (about_dialog, about_dialog, "about_dialog");
        return about_dialog;
}


/* EOF */
