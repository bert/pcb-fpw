/*!
 * \file src/lesstif/license_dialog.h
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for the License dialog for the pcb footprintwizard (pcb-lfpw).
 *
 * pcb-lfpw (Lesstif FootPrintWizard) is a program for the creation of
 * footprint files to be used by the pcb layout application
 * (see http://pcb.gpleda.org) for the placement of parts in a pcb
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


#ifndef __LICENSE_DIALOG_H_INCLUDED__
#define __LICENSE_DIALOG_H_INCLUDED__


void create_license_dialog (Widget main_window);
XmString create_license_dialog_xmstring (void);
void on_license_dialog_close_button_clicked
(
        Widget w,
        XtPointer client_data,
        XtPointer call_data
);       
void show_license_dialog (void);


#endif /* __LICENSE_DIALOG_H_INCLUDED__ */


/* EOF */
