/*!
 * \file libfpw.h
 * \author Copyright (C) 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief header file for libfpw.
 *
 * fpw (FootPrintWizard) is a program for the creation of footprint files
 * to be used by the pcb layout application
 * (see http://pcb.gpleda.org) for the placement of parts in a pcb
 * layout.\n
 * \n
 * The functions in libfpw are called by both the CLI version of the
 * FootPrintWizard (fpw) as well as the GUI version (pcb-gfpw).\n
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


#ifndef __LIBFPW_INCLUDED__
#define __LIBFPW_INCLIDED__

#include "globals.h"
#include "packages.h"


/* Forward declaration of functions. */
ElementTypePtr create_attributes_in_element (ElementTypePtr);
AttributeTypePtr create_new_attribute (AttributeListTypePtr, char *, char *);
ArcTypePtr create_new_arc (ElementTypePtr, LocationType, LocationType, BDimension, BDimension, int, int, BDimension);
ElementTypePtr create_new_element ();
LineTypePtr create_new_line (ElementTypePtr, LocationType, LocationType, LocationType, LocationType, BDimension);
PadTypePtr create_new_pad (ElementTypePtr, LocationType, LocationType, LocationType, LocationType, BDimension, BDimension, BDimension, char *, char *, FlagType);
PinTypePtr create_new_pin (ElementTypePtr, LocationType, LocationType, BDimension, BDimension, BDimension, BDimension, char *, char *, FlagType);
int get_package_type ();
int get_pin_pad_exception (gchar *);
int get_status_type ();
int read_footprintwizard_file (gchar *);
int update_location_variables ();
int update_pad_shapes_variables ();
int update_units_variables ();
int write_attributes ();
int write_element_arc (gdouble, gdouble, gdouble, gdouble, gdouble, gdouble, gdouble);
int write_element_header (gdouble, gdouble);
int write_element_line (gdouble, gdouble, gdouble, gdouble, gdouble);
int write_license ();
int write_pad (gint, gchar *, gdouble, gdouble, gdouble, gdouble, gdouble, gdouble, gdouble, gchar *);
int write_pin (gint, gchar *, gdouble, gdouble, gdouble, gdouble, gdouble, gdouble, gchar *);
int write_rectangle (gdouble, gdouble, gdouble, gdouble, gdouble);
int write_footprintwizard_file (gchar *);
int write_footprint();


#endif /* __LIBFPW_INCLUDED__ */

/* EOF */
