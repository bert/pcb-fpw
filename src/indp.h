/*!
 * \file src/indp.h
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for functions for INDP footprints.
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


#ifndef __INDP_INCLUDED__
#define __INDP_INCLUDED__


int indp_create_element ();
int indp_create_packages_list ();
int indp_drc ();
int indp_get_default_footprint_values ();
#if GUI
int indp_set_gui_constraints (GtkWidget *);
#endif /* GUI */
int indp_write_footprint ();
void indp_init ();


#endif /* _INDP_INCLUDED__ */


/* EOF */
