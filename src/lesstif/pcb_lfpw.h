/*!
 * \file src/lesstif/pcb_lfpw.h
 *
 * \author Copyright 2007 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for Lesstif program for the pcb footprintwizard (pcb-lfpw).
 *
 * pcb-lfpw (LesstifFootPrintWizard) is a program for the creation of footprint
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


#ifndef __PCB_LFPW_H_INCLUDED__
#define __PCB_LFPW_H_INCLUDED__


char fpw_filename;
        /*!< global variable for storing the current fpw filename. */
char program_name;
        /*!< global variable for remembering how we are called today. */
Boolean debug;
        /*!< global variable for being verbose on debugging information. */
Boolean silent;
        /*!< global variable for suppressing the logging of critical messages. */
Boolean verbose;
        /*!< global variable for being verbose on logging of information. */
XtAppContext lfpw_app_context;
        /*!< variable for storing the application context. */
Display *lfpw_display;
        /*!< global variable (pointer) to the display. */
int lfpw_screen;
int nTextScreen;
int nGraphicsScreen;
int NumScrns;
int lfpw_root_window;
int lfpw_screen_width;
int lfpw_screen_height;
unsigned long white_pixel;
unsigned long black_pixel;
Colormap DefaultColorMap;
int NumDisplayCells;
int ScreenDepth;
Visual * ScrnVisual;

Dimension lfpw_main_x;
Dimension lfpw_main_y;
Dimension lfpw_main_width;
Dimension lfpw_main_height;

int lfpw_cmdline_options (int argc, char *argv[]);
int lfpw_print_debug_info (int argc, char **argv);
int lfpw_print_usage (void);
int lfpw_print_version (void);


#endif /* __PCB_LFPW_H_INCLUDED__ */


/* EOF */
