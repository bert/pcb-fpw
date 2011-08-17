/*!
 * \file src/fpw.h
 *
 * \author Copyright (C) 2007-2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for fpw.
 *
 * fpw (FootPrintWizard) is a program run from the Command Line Interface
 * (CLI) for the creation of footprints files.\n
 * These footprint files can be used by the pcb layout application
 * (see http://pcb.gpleda.org) to allow for the placement of parts on a
 * pcb layout.\n
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


#ifndef __FPW_INCLUDED__
#define __FPW_INCLUDED__

G_BEGIN_DECLS /* keep c++ happy */

int print_version ();
int print_usage ();
int main (int , char **);

G_END_DECLS /* keep c++ happy */

#endif /* __FPW_INCLUDED__ */


/* EOF */
