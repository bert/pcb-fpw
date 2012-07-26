/*!
 * \file src/lesstif/util.h
 *
 * \author Copyright 2007 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief utilities for the pcb footprintwizard (pcb-lfpw).
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


#ifndef __UTIL_H_INCLUDED__
#define __UTIL_H_INCLUDED__


static Arg args[30];
static int n;

#define stdarg(t,v) XtSetArg(args[n], t, v); n++


XmFontList get_fontlist(Widget w, char *fontname);
Pixel get_pixel(Widget w, char *resource_value);


#endif /* __UTIL_H_INCLUDED__ */


/* EOF */
