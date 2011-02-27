/*!
 * \file src/con_dil.h
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for functions for CON_DIL footprints
 * (Dual In Line Connector).
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


#ifndef __CON_DIL_INCLUDED__
#define __CON_DIL_INCLUDED__


int con_dil_create_element ();
GList con_dil_create_packages_list ();
int con_dil_drc ();
int con_dil_get_default_footprint_values (gchar *);
#if GUI
int con_dil_set_gui_constraints (GtkWidget *);
#endif /* GUI */
int con_dil_write_footprint ();
void con_dil_init ();


#endif /* __CON_DIL_INCLUDED__ */


/* EOF */
