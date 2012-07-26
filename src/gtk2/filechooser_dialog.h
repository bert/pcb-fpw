/*!
 * \file src/gtk2/filechooser_dialog.h
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for the filechooser dialog for pcb-gfpw (GTK2 UI).
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


#ifndef __FILECHOOSER_DIALOG_INCLUDED__
#define __FILECHOOSER_DIALOG_INCLUDED__


void on_filechooser_dialog_cancel_button_clicked (GtkButton *button, gpointer user_data);
void on_filechooser_dialog_close (GtkDialog *dialog, gpointer user_data);
void on_filechooser_dialog_current_folder_changed (GtkFileChooser *filechooser, gpointer user_data);
void on_filechooser_dialog_open_button_clicked (GtkButton *button, gpointer user_data);
void on_filechooser_dialog_selection_changed (GtkFileChooser *filechooser, gpointer user_data);
void on_filechooser_dialog_update_preview (GtkFileChooser *filechooser, gpointer user_data);
GtkWidget* create_filechooser_dialog (void);


#endif /* __FILECHOOSER_INCLUDED__ */


/* EOF */
