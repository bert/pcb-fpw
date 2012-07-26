/*!
 * \file src/gtk3/about_dialog.h
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for the about dialog for pcb-gfpw (GTK3 UI).
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


#ifndef __ABOUT_DIALOG_INCLUDED__
#define __ABOUT_DIALOG_INCLUDED__


void on_about_dialog_close (GtkDialog *dialog, gpointer user_data);
void on_about_dialog_destroy  (GtkDialog *dialog, gpointer user_data);
GtkWidget *create_about_dialog (void);


#endif /* __ABOUT_DIALOG_INCLUDED__ */


/* EOF */
