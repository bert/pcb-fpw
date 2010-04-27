/*!
 * \file filechooser.c
 * \author Copyright 2007, 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief A filechooser dialog for pcb-gfpw (GTK UI).
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
#include <stdlib.h>

#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>


#include "../globals.h"


/*!
 * \brief The file chooser dialog "Cancel" button is clicked.
 *
 * <ul>
 * <li>lookup the dialog widget.
 * <li>destroy the file chooser widget.
 * </ul>
 *
 * \todo - maybe restore the preview widget ?
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_filechooser_dialog_cancel_button_clicked
                                        (GtkButton       *button,
                                        gpointer         user_data)
{
        GtkWidget *filechooser_dialog = lookup_widget (GTK_WIDGET (button),
                "filechooser_dialog");
        gtk_widget_destroy (filechooser_dialog);
}


/*!
 * \brief The file chooser dialog "close" signal is emitted.
 *
 * <ul>
 * <li>lookup the dialog widget.
 * <li>destroy the file chooser widget.
 * </ul>
 *
 * <b>Parameters:</b> \c *dialog is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_filechooser_dialog_close            (GtkDialog       *dialog,
                                        gpointer         user_data)
{
        GtkWidget *filechooser_dialog = lookup_widget (GTK_WIDGET (dialog),
                "filechooser_dialog");
        gtk_widget_destroy (filechooser_dialog);
}



/*!
 * \brief The file chooser dialog "current folder changed" signal is emitted.
 *
 * <ul>
 * <li>lookup the dialog widget.
 * <li>get the current folder.
 * <li>test the current folder for null pointer or empty string and if
 *   true, please log a message and return.
 * <li>store the (new) current folder name in \c temp_dir.
 * </ul>
 *
 * <b>Parameters:</b> \c *filechooser is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_filechooser_dialog_current_folder_changed
(
        GtkFileChooser *filechooser,
        gpointer user_data
)
{
        GtkWidget *filechooser_dialog = lookup_widget (GTK_WIDGET (filechooser),
                "filechooser_dialog");
        gchar *current_folder = g_strdup (gtk_file_chooser_get_current_folder
                (GTK_FILE_CHOOSER (filechooser_dialog)));
        /* Test if current folder is a null pointer.
         * If so, please log a message. */
        if (!current_folder)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("current folder is not initialised  (null pointer)."));
        }
        /* Test if current folder is an empty string pointer.
         * If so, please log a message. */
        else if (!strcmp (current_folder, ""))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("current folder contains an empty string."));
        }
        /* Test if current folder is a directory.
         * If so, store in temp_dir. */
        else if (g_file_test (current_folder, G_FILE_TEST_IS_DIR))
        {
                temp_dir = g_strdup (current_folder);
                if (verbose)
                        g_log ("", G_LOG_LEVEL_INFO, _("Changed cwd to: %s"),
                                current_folder);
        }
        /* Clean up used variable(s). */
        g_free (current_folder);
}


/*!
 * \brief The file chooser dialog "Open" button is clicked.
 *
 * <ul>
 * <li>lookup the dialog widget.
 * <li>get the selected filename.
 * <li>test the selected filename for null pointer or empty string and if true,
 *   please log a message.
 * <li>test if the selected filename is not a directory and if true,
 *   please log a message.
 * <li>store the selected filename in \c fpw_filename.
 * <li>duplicate the (new) current directory name from \c temp_dir into
 *   \c work_dir.
 * <li>read new global values from the selected footprintwizard file.
 * <li>update the entry widgets to reflect the changes.
 * </ul>
 *
 * <b>Parameters:</b> \c *button is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_filechooser_dialog_open_button_clicked
(
        GtkButton *button,
        gpointer user_data
)
{
        GtkWidget *filechooser_dialog = lookup_widget (GTK_WIDGET (button),
                "filechooser_dialog");
        gchar *selected_filename = NULL;
        selected_filename = g_strdup (gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (filechooser_dialog)));
        /* Test if selected filename is a null pointer.
         * If so, please log a message and return. */
        if (!selected_filename)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("selected filename is not initialised (NULL pointer)."));
        }
        /* Test if selected filename is an empty string.
         * If so, please log a message and return. */
        else if (!strcmp (selected_filename, ""))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("selected filename contains an empty string."));
        }
        /* Test if selected filename is a directory.
         * If so, please notify the user (in the statusbar), to select a file
         * instead. */
        else if (g_file_test (selected_filename, G_FILE_TEST_IS_DIR))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING, _("selected filename is a directory."));
        }
        else
        {
                /* Store the (now validated) selected filename. */
                gchar *fpw_filename = g_strdup (selected_filename);
                if (temp_dir)
                        work_dir = g_strdup (temp_dir);
                /* Read new global values from the selected footprintwizard file. */
                if (read_footprintwizard_file (fpw_filename) == EXIT_SUCCESS)
                {
                        if (verbose)
                                g_log ("", G_LOG_LEVEL_INFO, _("Read footprintwizard file %s."), fpw_filename);
                        /* Update the entry widgets to reflect the changes. */
                        GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET (button));
                        if (GTK_WIDGET_TOPLEVEL (toplevel))
                        {
                                all_entries_need_updated (GTK_WIDGET (toplevel));
                        }
                        /* Clean up used variable(s). */
                        g_free (toplevel);
                }
                else
                {
                        GtkWidget *toplevel = gtk_widget_get_toplevel (GTK_WIDGET (button));
                        if (GTK_WIDGET_TOPLEVEL (toplevel))
                        {
                                GtkWidget *dialog = gtk_message_dialog_new
                                (
                                        GTK_WINDOW (toplevel),
                                        GTK_DIALOG_DESTROY_WITH_PARENT,
                                        GTK_MESSAGE_ERROR,
                                        GTK_BUTTONS_CLOSE,
                                        g_strdup_printf (_("ERROR: Unable to read footprint wizard file %s."), fpw_filename)
                                );
                                gtk_dialog_run (GTK_DIALOG (dialog));
                                gtk_widget_destroy (dialog);
                                g_free (dialog);
                                return;
                        }
                        g_free (toplevel);
                }
                /* Clean up used variable(s). */
                g_free (fpw_filename);
        }
        /* Clean up used variable(s). */
        g_free (selected_filename);
}


/*!
 * \brief The file chooser dialog "selection changed" signal is emitted.
 *
 * \todo - store the selected filename in \c temp_fpw_filename.
 * \todo - read the values from the selected footprintwizard file in a
 * temporary set of variables \c temp_*.
 * \todo - generate a new preview image.
 * \todo - update the preview widget.
 *
 * <b>Parameters:</b> \c *filechooser is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_filechooser_dialog_selection_changed
                                        (GtkFileChooser  *filechooser,
                                        gpointer         user_data)
{

}


/*!
 * \brief The file chooser dialog "update preview" signal is emitted.
 *
 * \todo - generate a new preview image.
 * \todo - update the preview widget.
 *
 * <b>Parameters:</b> \c *filechooser is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c user_data.\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_filechooser_dialog_update_preview   (GtkFileChooser  *filechooser,
                                        gpointer         user_data)
{

}


/*!
 * \brief Create a filechooser dialog.
 *
 * <b>Parameters:</b> \c void.\n
 * \n
 * <b>Returns:</b> GtkWidget \c filechooser dialog.
 */
GtkWidget*
create_filechooser_dialog (void)
{
  GtkWidget *filechooser_dialog;
  GdkPixbuf *filechooser_dialog_icon_pixbuf;
  GtkWidget *filechooser_dialog_vbox;
  GtkWidget *filechooser_dialog_action_area;
  GtkWidget *filechooser_dialog_cancel_button;
  GtkWidget *filechooser_dialog_open_button;

  filechooser_dialog = gtk_file_chooser_dialog_new (_("pcb-gfpw: choose a .fpw file"), NULL, GTK_FILE_CHOOSER_ACTION_OPEN, NULL);
  gtk_widget_set_name (filechooser_dialog, "filechooser_dialog");
  filechooser_dialog_icon_pixbuf = create_pixbuf ("gFootprintWizard.xpm");
  if (filechooser_dialog_icon_pixbuf)
    {
      gtk_window_set_icon (GTK_WINDOW (filechooser_dialog), filechooser_dialog_icon_pixbuf);
      gdk_pixbuf_unref (filechooser_dialog_icon_pixbuf);
    }
  gtk_window_set_type_hint (GTK_WINDOW (filechooser_dialog), GDK_WINDOW_TYPE_HINT_DIALOG);
        /* Create a vbox. */
  filechooser_dialog_vbox = GTK_DIALOG (filechooser_dialog)->vbox;
  gtk_widget_set_name (filechooser_dialog_vbox, "filechooser_dialog_vbox");
  gtk_widget_show (filechooser_dialog_vbox);
        /* Create an action area. */
  filechooser_dialog_action_area = GTK_DIALOG (filechooser_dialog)->action_area;
  gtk_widget_set_name (filechooser_dialog_action_area, "filechooser_dialog_action_area");
  gtk_widget_show (filechooser_dialog_action_area);
  gtk_button_box_set_layout (GTK_BUTTON_BOX (filechooser_dialog_action_area), GTK_BUTTONBOX_END);
        /* Create a "cancel" button. */
  filechooser_dialog_cancel_button = gtk_button_new_from_stock ("gtk-cancel");
  gtk_widget_set_name (filechooser_dialog_cancel_button, "filechooser_dialog_cancel_button");
  gtk_widget_show (filechooser_dialog_cancel_button);
  gtk_dialog_add_action_widget (GTK_DIALOG (filechooser_dialog), filechooser_dialog_cancel_button, GTK_RESPONSE_CANCEL);
  GTK_WIDGET_SET_FLAGS (filechooser_dialog_cancel_button, GTK_CAN_DEFAULT);
        /* Create an "open" button.*/
  filechooser_dialog_open_button = gtk_button_new_from_stock ("gtk-open");
  gtk_widget_set_name (filechooser_dialog_open_button, "filechooser_dialog_open_button");
  gtk_widget_show (filechooser_dialog_open_button);
  gtk_dialog_add_action_widget (GTK_DIALOG (filechooser_dialog), filechooser_dialog_open_button, GTK_RESPONSE_OK);
  GTK_WIDGET_SET_FLAGS (filechooser_dialog_open_button, GTK_CAN_DEFAULT);
      /* Connect signals to callback functions. */
  g_signal_connect ((gpointer) filechooser_dialog, "selection_changed",
                    G_CALLBACK (on_filechooser_dialog_selection_changed),
                    NULL);
  g_signal_connect ((gpointer) filechooser_dialog, "close",
                    G_CALLBACK (on_filechooser_dialog_close),
                    NULL);
  g_signal_connect ((gpointer) filechooser_dialog, "current_folder_changed",
                    G_CALLBACK (on_filechooser_dialog_current_folder_changed),
                    NULL);
  g_signal_connect ((gpointer) filechooser_dialog, "update_preview",
                    G_CALLBACK (on_filechooser_dialog_update_preview),
                    NULL);
  g_signal_connect ((gpointer) filechooser_dialog_cancel_button, "clicked",
                    G_CALLBACK (on_filechooser_dialog_cancel_button_clicked),
                    NULL);
  g_signal_connect ((gpointer) filechooser_dialog_open_button, "clicked",
                    G_CALLBACK (on_filechooser_dialog_open_button_clicked),
                    NULL);
  /* Store pointers to all widgets, for use by lookup_widget(). */
  GLADE_HOOKUP_OBJECT_NO_REF (filechooser_dialog, filechooser_dialog, "filechooser_dialog");
  GLADE_HOOKUP_OBJECT_NO_REF (filechooser_dialog, filechooser_dialog_vbox, "filechooser_dialog_vbox");
  GLADE_HOOKUP_OBJECT_NO_REF (filechooser_dialog, filechooser_dialog_action_area, "filechooser_dialog_action_area");
  GLADE_HOOKUP_OBJECT (filechooser_dialog, filechooser_dialog_cancel_button, "filechooser_dialog_cancel_button");
  GLADE_HOOKUP_OBJECT (filechooser_dialog, filechooser_dialog_open_button, "filechooser_dialog_open_button");
  gtk_widget_grab_default (filechooser_dialog_open_button);
  return filechooser_dialog;
}


/* EOF */
