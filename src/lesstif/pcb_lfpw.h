/*!
 * \file src/lesstif/pcb_lfpw.h
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for Lesstif program for the pcb footprintwizard (pcb-lfpw).
 *
 * pcb-lfpw (LesstifFootPrintWizard) is a program for the creation of footprint
 * files to be used by with the pcb layout application
 * (see http://pcb.sourgeforge.net) for the placement of parts in a pcb
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


char *fpw_filename = NULL;
        /*!< Global for storing the curent fpw filename. */
char *program_name = NULL;
        /*!< Global for remembering how we are called today. */
Boolean debug = 0;
        /*!< Global for being verbose on debugging information. */
Boolean silent = 0;
        /*!< Global for suppressing the logging of critical messages. */
Boolean verbose = 0;
        /*!< Global for being verbose on logging of information. */
XtAppContext pcb_lfpw_app_context;


int lfpw_cmdline_options (int argc, char *argv[]);
int lfpw_print_usage (void);
int lfpw_print_version (void);


#endif /* __PCB_LFPW_H_INCLUDED__ */


/* EOF */
