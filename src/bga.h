/*!
 * \file bga.h
 * \author Copyright 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Header file for BGA footprints functions.
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


#ifndef __BGA_INCLUDED__
#define __BGA_INCLIDED__

#include "globals.h"


/* Forward declaration of functions. */
ElementTypePtr *bga_create_element ();
GList bga_create_packages_list ();
int bga_drc ();
int bga_get_default_footprint_values (gchar *);
int bga_set_gui_constraints (GtkWidget *);
int bga_write_footprint ();
void bga_init ();


#endif /* __BGA_INCLUDED__ */