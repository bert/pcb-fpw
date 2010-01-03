/*!
 * \file capmp.h
 * \author Copyright 2007, 2008, 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Header file for functions for CAPMP footprints.
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


#ifndef __CAPMP_INCLUDED__
#define __CAPMP_INCLUDED__


ElementTypePtr capmp_create_element ();
GList capmp_create_packages_list ();
int capmp_drc ();
int capmp_get_default_footprint_values (gchar *);
#if GUI
int capmp_set_gui_constraints (GtkWidget *);
#endif /* GUI */
int capmp_write_footprint ();
void capmp_init ();


#endif /* __CAPMP_INCLUDED__ */


/* EOF */
