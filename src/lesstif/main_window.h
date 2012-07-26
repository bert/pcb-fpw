/*!
 * \file src/lesstif/main_window.h
 *
 * \author Copyright 2007 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for the main window of the pcb footprintwizard (pcb-lfpw).
 *
 * pcb-lfpw (Lesstif FootPrintWizard) is a program for the creation of footprint
 * files to be used by with the pcb layout application
 * (see http://pcb.geda-project.org) for the placement of parts in a pcb
 * layout.\n
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


#ifndef __MAIN_WINDOW_H_INCLUDED__
#define __MAIN_WINDOW_H_INCLUDED__


#define ENTRY_MARGIN_WIDTH 3
        /*!< in pixels */
#define ENTRY_MARGIN_HEIGHT 3
        /*!< in pixels */
#define ENTRY_DOUBLE_MAX_LENGTH 12
        /*!< 11 digits and a decimal point somewhere should suffice. */
#define ENTRY_INT_MAX_LENGTH 8 
        /*!< digits */
#define FRAME_MARGIN_WIDTH 3
        /*!< in pixels */
#define FRAME_MARGIN_HEIGHT 3
        /*!< in pixels */
#define WIDGET_BOTTOM_OFFSET 3
        /*!< in pixels */
#define WIDGET_TOP_OFFSET 3
        /*!< in pixels */
#define WIDGET_LEFT_OFFSET 30
        /*!< in pixels */
#define WIDGET_RIGHT_OFFSET 30
        /*!< in pixels */

Widget main_window;
        /*!< global main pcb-lfpw window */

int change_main_window_title (Widget *widget, char *filename);
int create_main_window (int argc, char **argv);
void on_C1_entry_changed (Widget w, XtPointer client_data, XtPointer call_data);
void on_C1_radiobutton_toggled (Widget w, XtPointer client_data, XtPointer call_data);
void on_C2_entry_changed (Widget w, XtPointer client_data, XtPointer call_data);
void on_C2_radiobutton_toggled (Widget w, XtPointer client_data, XtPointer call_data);
void on_G1_entry_changed (Widget w, XtPointer client_data, XtPointer call_data);
void on_G1_radiobutton_toggled (Widget w, XtPointer client_data, XtPointer call_data);
void on_G2_entry_changed (Widget w, XtPointer client_data, XtPointer call_data);
void on_G2_radiobutton_toggled (Widget w, XtPointer client_data, XtPointer call_data);
void on_Z1_entry_changed (Widget w, XtPointer client_data, XtPointer call_data);
void on_Z1_radiobutton_toggled (Widget w, XtPointer client_data, XtPointer call_data);
void on_Z2_entry_changed (Widget w, XtPointer client_data, XtPointer call_data);
void on_Z2_radiobutton_toggled (Widget w, XtPointer client_data, XtPointer call_data);
void on_close_button_clicked (Widget w, XtPointer client_data, XtPointer call_data);
void show_main_window (int argc, char **argv);


#endif /* __MAIN_WINDOW_H_INCLUDED__ */


/* EOF */
