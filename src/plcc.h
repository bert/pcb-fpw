/*!
 * \file src/plcc.h
 *
 * \author Copyright (C) 2007-2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for functions for PLCC footprints.
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


#ifndef __PLCC_INCLUDED__
#define __PLCC_INCLUDED__

G_BEGIN_DECLS /* keep c++ happy */

int plcc_create_element ();
int plcc_create_packages_list ();
int plcc_drc ();
int plcc_get_default_footprint_values ();
#if GUI
int plcc_set_gui_constraints ();
#endif /* GUI */
int plcc_write_footprint ();
void plcc_init ();

G_END_DECLS /* keep c++ happy */

#endif /* __PLCC_INCLUDED__ */


/* EOF */
