/*!
 * \file src/capm.h
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for functions for CAPM footprints
 * (Surface Mount Technology Molded Capacitor).
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


#ifndef __CAPM_INCLUDED__
#define __CAPM_INCLUDED__


int capm_create_element ();
GList capm_create_packages_list ();
int capm_drc ();
int capm_get_default_footprint_values (gchar *);
#if GUI
int capm_set_gui_constraints (GtkWidget *);
#endif /* GUI */
int capm_write_footprint ();
void capm_init ();


#endif /* __CAPM_INCLUDED__ */


/* EOF */
