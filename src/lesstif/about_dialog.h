/*!
 * \file src/lesstif/about_dialog.h
 *
 * \author Copyright 2007 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for the About dialog for the pcb footprintwizard (pcb-lfpw).
 *
 * pcb-lfpw (Lesstif FootPrintWizard) is a program for the creation of
 * footprint files to be used by the pcb layout application
 * (see http://pcb.geda-project.org) for the placement of parts in a pcb
 * layout.\n
 * \n
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


#ifndef __ABOUT_DIALOG_H_INCLUDED__
#define __ABOUT_DIALOG_H_INCLUDED__


Widget about_dialog;   
        /*!< about_dialog window */


int create_about_dialog (int argc, char **argv);
XmString create_about_dialog_xmstring (void);
void on_about_dialog_close_button_clicked (Widget w, XtPointer client_data, XtPointer call_data);       
void on_about_dialog_credits_button_clicked (Widget w, XtPointer client_data, XtPointer call_data);       
void on_about_dialog_license_button_clicked (Widget w, XtPointer client_data, XtPointer call_data);       


#endif /* __ABOUT_DIALOG_H_INCLUDED__ */


/* EOF */
