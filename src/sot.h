/*!
 * \file sot.h
 * \author Copyright (C) 2007, 2008, 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Header file for functions for SOT footprints.
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


#ifndef __SOT_INCLUDED__
#define __SOT_INCLUDED__


ElementTypePtr sot_create_element ();
GList sot_create_packages_list (GList *);
int sot_drc ();
int sot_get_default_footprint_values (gchar *footprint_name);
#if GUI
int sot_set_gui_constraints (GtkWidget *widget);
#endif /* GUI */
int sot_write_footprint ();
void sot_init ();


#endif /* __SOT_INCLUDED__ */


/* EOF */
