/*!
 * \file src/libfpw.h
 *
 * \author Copyright (C) 2007-2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for libfpw, contains helper functions for both
 * fpw (CLI) and pcb-gfpw (GUI) versions of the pcb FootPrintWizard.
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
#define __LIBFPW_INCLUDED__

G_BEGIN_DECLS /* keep c++ happy */

AttributeTypePtr create_new_attribute (AttributeListTypePtr list, char *name, char *value);

ElementTypePtr current_element;

GList *packages_list;

ElementTypePtr create_attributes_in_element (ElementTypePtr element);
ArcTypePtr create_new_arc 
(
        ElementTypePtr element,
        LocationType X,
        LocationType Y,
        BDimension width,
        BDimension height,
        int angle,
        int delta,
        BDimension thickness
);
AttributeTypePtr create_new_attribute
(
        AttributeListTypePtr list,
        char *name,
        char *value
);
LineTypePtr create_new_line
(
        ElementTypePtr element,
        LocationType X1,
        LocationType Y1,
        LocationType X2,
        LocationType Y2,
        BDimension thickness
);
PadTypePtr create_new_pad
(
        ElementTypePtr element,
        LocationType X1,
        LocationType Y1,
        LocationType X2,
        LocationType Y2,
        BDimension thickness,
        BDimension clearance,
        BDimension mask,
        char *name,
        char *number,
        FlagType flags
);
PinTypePtr create_new_pin
(
        ElementTypePtr element,
        LocationType X,
        LocationType Y,
        BDimension thickness,
        BDimension clearance,
        BDimension mask,
        BDimension drillinghole,
        char *name,
        char *number,
        FlagType flags
);
int get_package_type ();
int get_pin_pad_exception (gchar *pin_pad_name);
int get_status_type ();
int get_total_number_of_pins ();
int read_footprintwizard_file (gchar *fpw_filename);
char *strip_prefix (char *name, const char *prefix);
char *strip_suffix (char *name, const char *suffix);
int update_location_variables ();
int update_pad_shapes_variables ();
int update_units_variables ();
int write_attributes ();
int write_element_arc
(
        gdouble x,
        gdouble y,
        gdouble width,
        gdouble height,
        gdouble start_angle,
        gdouble delta_angle,
        gdouble line_width
);
int write_element_header
(
        gdouble x_text,
        gdouble y_text
);
int write_element_line
(
        gdouble x0,
        gdouble y0,
        gdouble x1,
        gdouble y1,
        gdouble line_width
);
int write_license ();
int write_pad
(
        gint pad_number,
        gchar *pad_name,
        gdouble x0,
        gdouble y0,
        gdouble x1,
        gdouble y1,
        gdouble width,
        gdouble clearance,
        gdouble pad_solder_mask_clearance,
        gchar *flags
);
int write_pin
(
        gint pin_number,
        gchar *pin_name,
        gdouble x0,
        gdouble y0,
        gdouble width,
        gdouble clearance,
        gdouble pad_solder_mask_clearance,
        gdouble drill,
        gchar *flags
);
int write_rectangle
(
        gdouble xmin,
        gdouble ymin,
        gdouble xmax,
        gdouble ymax,
        gdouble line_width
);
int
write_footprintwizard_file (gchar *fpw_filename);
int write_footprint ();

G_END_DECLS /* keep c++ happy */

#endif /* __LIBFPW_INCLUDED__ */


/* EOF */
