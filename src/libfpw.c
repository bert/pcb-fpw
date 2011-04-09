/*!
 * \file src/libfpw.c
 *
 * \author Copyright (C) 2007, 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief libfpw contains helper functions for both fpw (CLI) and
 * pcb-gfpw (GUI) versions of the pcb FootPrintWizard.
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


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <gdk/gdkkeysyms.h>
#include <gtk/gtk.h>
#include <glib.h>

#include "globals.h"
#include "pcb_globals.h"
#include "libfpw.h"


/*!
 * \brief Create all defining attributes of a footprint in the \c
 * element and add the values to the \c Attributes struct inside the
 * \c element.
 *
 * \todo Add tests to check if \c Attributes are already present and do
 * not contain the defining value already, thus avoiding duplication.\n
 *
 * \return an \c element with \c Attributes added.
 */
ElementTypePtr
create_attributes_in_element
(
        ElementTypePtr element
                /*!< : a pointer to an \c element without \c Attributes.*/
)
{
        create_new_attribute (&element->Attributes, "author", g_strdup_printf ("%s", footprint_author));
        create_new_attribute (&element->Attributes, "dist-license", g_strdup_printf ("%s", footprint_dist_license));
        create_new_attribute (&element->Attributes, "use-license", g_strdup_printf ("%s", footprint_use_license));
        create_new_attribute (&element->Attributes, "status\" \"%s\")\n", footprint_status);
        create_new_attribute (&element->Attributes, "attributes in footprint", g_strdup_printf ("%d", (int) attributes_in_footprint));
        create_new_attribute (&element->Attributes, "package body length", g_strdup_printf ("%f", package_body_length));
        create_new_attribute (&element->Attributes, "package body width", g_strdup_printf ("%f", package_body_width));
        create_new_attribute (&element->Attributes, "package height", g_strdup_printf ("%f", package_body_height));
        create_new_attribute (&element->Attributes, "package is radial", g_strdup_printf ("%d", package_is_radial));
        create_new_attribute (&element->Attributes, "number of pins", g_strdup_printf ("%d", (int) number_of_pins));
        create_new_attribute (&element->Attributes, "number of columns", g_strdup_printf ("%d", (int) number_of_columns));
        create_new_attribute (&element->Attributes, "number of rows", g_strdup_printf ("%d", (int) number_of_rows));
        create_new_attribute (&element->Attributes, "pitch_x", g_strdup_printf ("%f", pitch_x));
        create_new_attribute (&element->Attributes, "pitch_y", g_strdup_printf ("%f", pitch_y));
        create_new_attribute (&element->Attributes, "count_x", g_strdup_printf ("%d", (int) count_x));
        create_new_attribute (&element->Attributes, "count_x", g_strdup_printf ("%d", (int) count_y));
        create_new_attribute (&element->Attributes, "pad_shape", g_strdup_printf ("%s", pad_shape));
        create_new_attribute (&element->Attributes, "pin_pad_exceptions", g_strdup_printf ("%s", pin_pad_exceptions_string));
        create_new_attribute (&element->Attributes, "pin_1_position", g_strdup_printf ("%s", pin_1_position));
        create_new_attribute (&element->Attributes, "pad_diameter", g_strdup_printf ("%f", pad_diameter));
        create_new_attribute (&element->Attributes, "pin_drill_diameter", g_strdup_printf ("%f", pin_drill_diameter));
        create_new_attribute (&element->Attributes, "pin1_square", g_strdup_printf ("%d", (int) pin1_square));
        create_new_attribute (&element->Attributes, "pad_length", g_strdup_printf ("%f", pad_length));
        create_new_attribute (&element->Attributes, "pad_width", g_strdup_printf ("%f", pad_width));
        create_new_attribute (&element->Attributes, "pad_clearance", g_strdup_printf ("%f", pad_clearance));
        create_new_attribute (&element->Attributes, "pad_solder_mask_clearance", g_strdup_printf ("%f", pad_solder_mask_clearance));
        create_new_attribute (&element->Attributes, "thermal", g_strdup_printf ("%d", (int) thermal));
        create_new_attribute (&element->Attributes, "thermal_nopaste", g_strdup_printf ("%d", (int) thermal_nopaste));
        create_new_attribute (&element->Attributes, "thermal_length", g_strdup_printf ("%f", thermal_length));
        create_new_attribute (&element->Attributes, "thermal_width", g_strdup_printf ("%f", thermal_width));
        create_new_attribute (&element->Attributes, "thermal_clearance", g_strdup_printf ("%f", thermal_clearance));
        create_new_attribute (&element->Attributes, "thermal_solder_mask_clearance", g_strdup_printf ("%f", thermal_solder_mask_clearance));
        create_new_attribute (&element->Attributes, "silkscreen_package_outline", g_strdup_printf ("%d", (int) silkscreen_package_outline));
        create_new_attribute (&element->Attributes, "silkscreen_indicate_1", g_strdup_printf ("%d", (int) silkscreen_indicate_1));
        create_new_attribute (&element->Attributes, "silkscreen_line_width", g_strdup_printf ("%f", silkscreen_line_width));
        create_new_attribute (&element->Attributes, "courtyard", g_strdup_printf ("%d", (int) courtyard));
        create_new_attribute (&element->Attributes, "courtyard_length", g_strdup_printf ("%f", courtyard_length));
        create_new_attribute (&element->Attributes, "courtyard_width", g_strdup_printf ("%f", courtyard_width));
        create_new_attribute (&element->Attributes, "courtyard_line_width", g_strdup_printf ("%f", courtyard_line_width));
        create_new_attribute (&element->Attributes, "courtyard_clearance_with_package", g_strdup_printf ("%f", courtyard_clearance_with_package));
        create_new_attribute (&element->Attributes, "c1", g_strdup_printf ("%f", c1));
        create_new_attribute (&element->Attributes, "g1", g_strdup_printf ("%f", g1));
        create_new_attribute (&element->Attributes, "z1", g_strdup_printf ("%f", z1));
        create_new_attribute (&element->Attributes, "c2", g_strdup_printf ("%f", c2));
        create_new_attribute (&element->Attributes, "g2", g_strdup_printf ("%f", g2));
        create_new_attribute (&element->Attributes, "z2", g_strdup_printf ("%f", z2));
        return element;
}


/*!
 * \brief Creates a new \c arc entity in the \c element.
 *
 * \todo Check all existing \c Arc entities in the \c element to avoid
 * duplication.
 *
 * \return a newly created \c arc within the specified \c element.
 */
ArcTypePtr
create_new_arc
(
        ElementTypePtr element,
                /*!< : the \c element to create an \c arc in.*/
        LocationType X,
                /*!< : X-coordinate of the \c arc.*/
        LocationType Y,
                /*!< : Y-coordinate of the \c arc.*/
        BDimension width,
                /*!< : width of the \c arc.*/
        BDimension height,
                /*!< : height of the \c arc.*/
        int angle,
                /*!< : start angle.*/
        int delta,
                /*!< : angle of sweep.*/
        BDimension thickness)
                /*!< : line thickness.*/
{
        ArcTypePtr arc = element->Arc;
        /* Reallocate new memory if necessary and clear it. */
        if (element->ArcN >= element->ArcMax)
        {
                element->ArcMax += 5;
                size_t size = element->ArcMax * sizeof (ArcType);
                if (size == 0)
                {
                        size = 1;
                }
                void *p;
                p = arc ? realloc (arc, size) : malloc (size);
                if (!p)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("out of memory during realloc() in create_new_arc()."));
                arc = realloc (arc, element->ArcMax * sizeof (ArcType));
                element->Arc = arc;
                memset ((arc + element->ArcN), 0, (5 * sizeof (ArcType)));
        }
        /* Set Delta (0,360], StartAngle in [0,360). */
        if ((delta = delta % 360) == 0)
                delta = 360;
        if (delta < 0)
        {
                angle += delta;
                delta = -delta;
        }
        if ((angle = angle % 360) < 0)
                angle += 360;
        /* copy values */
        arc = arc + element->ArcN++;
        arc->X = X;
        arc->Y = Y;
        arc->Width = width;
        arc->Height = height;
        arc->StartAngle = angle;
        arc->Delta = delta;
        arc->Thickness = thickness;
        arc->ID = ID++;
        return (arc);
}


/*!
 * \brief Add an \c Attribute to an \c AttributeList.
 *
 * \todo Check all existing \c Attributes in the \c element to avoid
 * duplication.
 *
 * \return the newly created \c Attribute in the \c AttributeList.
 */
AttributeTypePtr
create_new_attribute
(
        AttributeListTypePtr list,
                /*!< : an \c AttributeList to add the \c Attribute to.*/
        char *name,
                /*!< : a \c name for the \c Attribute.*/
        char *value
                /*!< : a \c value for the \c Attribute.*/
)
{
        if (list->Number >= list->Max)
        {
                list->Max += 10;
                size_t size = list->Max * sizeof (AttributeType);
                if (size == 0)
                {
                        size = 1;
                }
                void *p;
                p = list->List ? realloc (list, size) : malloc (size);
                if (!p)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("out of memory during realloc() in create_new_attribute()."));
        }
        list->List[list->Number].name = g_strdup (name);
        list->List[list->Number].value = g_strdup (value);
        list->Number++;
        return &list->List[list->Number - 1];
}


/*!
 * \brief Creates a new \c Line in an \c Element.
 *
 * \todo Check all existing \c Line entities in the \c element to avoid
 * duplication.
 *
 * \return a newly created \c Line within the specified \c element.
 */
LineTypePtr
create_new_line
(
        ElementTypePtr element,
                /*!< : the \c element to create a \c line in.*/
        LocationType X1,
                /*!< : the X-value of the start point.*/
        LocationType Y1,
                /*!< : the Y-value of the start point.*/
        LocationType X2,
                /*!< : the X-value of the end point.*/
        LocationType Y2,
                /*!< : the Y-value of the end point.*/
        BDimension thickness)
                /*!< : the line thickness.*/
{
        LineTypePtr line = element->Line;
        if (thickness == 0)
                return (NULL);
        /* Reallocate new memory if necessary and clear it. */
        if (element->LineN >= element->LineMax)
        {
                element->LineMax += 10;
                size_t size = element->LineMax * sizeof (LineType);
                if (size == 0)
                {
                        size = 1;
                }
                void *p;
                p = line ? realloc (line, size) : malloc (size);
                if (!p)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("out of memory during realloc() in create_new_line()."));
                element->Line = line;
                memset ((line + element->LineN), 0, (10 * sizeof (LineType)));
        }
        /* copy values */
        line = line + element->LineN++;
        line->Point1.X = X1;
        line->Point1.Y = Y1;
        line->Point2.X = X2;
        line->Point2.Y = Y2;
        line->Thickness = thickness;
//        line->Flags = NoFlags ();
        line->ID = ID++;
        return (line);
}


/*!
 * \brief Creates a new \c pad in an \c element.
 *
 * \todo Check all existing \c Pad entities in the \c element to avoid
 * duplication.
 *
 * \return a newly created \c Pad within the specified \c element.
 */
PadTypePtr
create_new_pad
(
        ElementTypePtr element,
                /*!< : the \c element to add the \c pad to.*/
        LocationType X1,
                /*!< : the X-value of the start point.*/
        LocationType Y1,
                /*!< : the Y-value of the start point.*/
        LocationType X2,
                /*!< : the X-value of the end point.*/
        LocationType Y2,
                /*!< : the Y-value of the end point.*/
        BDimension thickness,
                /*!< : the line thickness.*/
        BDimension clearance,
                /*!< : the clearance of copper around the \c pad. */
        BDimension mask,
                /*!< : the clearance of the solder mask around the \c pad.*/
        char *name,
                /*!< : the name of the \c pad.*/
        char *number,
                /*!< : the number of the \c pad.*/
        FlagType flags
                /*!< : flags separated by commas:
                 * <ul>
                 * <li> \c CLEAR : default is round pads on the
                 * component side of the pcb.
                 * <li> \c EDGE2 : indicates that the second point is
                 * closer to the edge.
                 * <li> \c LOCK : for locked objects.
                 * <li> \c NOPASTE : set to prevent a solderpaste
                 * stencil opening for the pad.
                 * <li> \c ONSOLDER : for pads on the solder side.
                 * <li> \c SQUARE : for rectangular pads.
                 * <li> \c WARN : set to indicate a warning.
                 * </ul>
                 */
)
{
        PadTypePtr pad;
        /* copy values */
        if (X1 > X2 || (X1 == X2 && Y1 > Y2))
        {
                pad->Point1.X = X2;
                pad->Point1.Y = Y2;
                pad->Point2.X = X1;
                pad->Point2.Y = Y1;
        }
        else
        {
                pad->Point1.X = X1;
                pad->Point1.Y = Y1;
                pad->Point2.X = X2;
                pad->Point2.Y = Y2;
        }
        pad->Thickness = thickness;
        pad->Clearance = clearance;
        pad->Mask = mask;
        pad->Name = g_strdup (name);
        pad->Number = g_strdup (number);
        pad->Flags = flags;
        pad->ID = ID++;
        pad->Element = element;
        return (pad);
}


/*!
 * \brief Creates a new pin in an element.
 *
 * \todo Check all existing \c Pin entities in the \c element to avoid
 * duplication.
 *
 * \return a newly created \c Pin within the specified \c element.
 */
PinTypePtr
create_new_pin
(
        ElementTypePtr element,
                /*!< : the \c element to add the \c pad to.*/
        LocationType X,
                /*!< : the X-value of the center point.*/
        LocationType Y,
                /*!< : the Y-value of the center point.*/
        BDimension thickness,
                /*!< : the annulus thickness.*/
        BDimension clearance,
                /*!< : the clearance of copper around the \c pin. */
        BDimension mask,
                /*!< : the clearance of the solder mask around the \c pin.*/
        BDimension drillinghole,
                /*!< : the size of the drilling hole of the \c pin.*/
        char *name,
                /*!< : the name of the \c pin.*/
        char *number,
                /*!< : the number of the \c pin.*/
        FlagType flags
                /*!< : flags separated by commas:
                 * <ul>
                 * <li> \c CLEAR : default is round pads on both sides
                 * of the pcb.
                 * <li> \c EDGE2 : indicates that the pin is closer to a
                 * horizontal edge and thus pinout text should be
                 * vertical.
                 * <li> \c HOLE : for unplated holes.
                 * <li> \c LOCK : for locked objects.
                 * <li> \c OCTAGON : for octagon pads.
                 * <li> \c SQUARE : for square pads.
                 * <li> \c WARN : set to indicate a warning.
                 * <\ul>
                 */
)
{
        PinTypePtr pin;
        /* copy values */
        pin->X = X;
        pin->Y = Y;
        pin->Thickness = thickness;
        pin->Clearance = clearance;
        pin->Mask = mask;
        pin->DrillingHole = drillinghole;
        pin->Name = g_strdup (name);
        pin->Number = g_strdup (number);
        pin->Flags = flags;
        pin->ID = ID++;
        pin->Element = element;
        return (pin);
}


/*!
 * \brief Determine the package type.
 *
 * \return EXIT_SUCCESS if a valid package type was determined,
 * EXIT_FAILURE if no valid package type was determined.
 */
int
get_package_type ()
{
        /* Determine the package type */
        if (!footprint_type)
        {
                package_type = NO_PACKAGE;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type is not valid."));
                return (EXIT_FAILURE);
        }
        if (!strcmp (footprint_type, ""))
        {
                package_type = NO_PACKAGE;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("empty footprint type entered."));
                return (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "BGA"))
        {
                package_type = BGA;
        }
        else if (!strcmp (footprint_type, "CAPA"))
        {
                package_type = CAPA;
        }
        else if (!strcmp (footprint_type, "CAPAD"))
        {
                package_type = CAPAD;
        }
        else if (!strcmp (footprint_type, "CAPAE"))
        {
                package_type = CAPAE;
        }
        else if (!strcmp (footprint_type, "CAPC"))
        {
                package_type = CAPC;
        }
        else if (!strcmp (footprint_type, "CAPM"))
        {
                package_type = CAPM;
        }
        else if (!strcmp (footprint_type, "CAPMP"))
        {
                package_type = CAPMP;
        }
        else if (!strcmp (footprint_type, "CON_DIL"))
        {
                package_type = CON_DIL;
        }
        else if (!strcmp (footprint_type, "CON_DIP"))
        {
                package_type = CON_DIP;
        }
        else if (!strcmp (footprint_type, "CON_HDR"))
        {
                package_type = CON_HDR;
        }
        else if (!strcmp (footprint_type, "CON_SIL"))
        {
                package_type = CON_SIL;
        }
        else if (!strcmp (footprint_type, "DIL"))
        {
                package_type = DIL;
        }
        else if (!strcmp (footprint_type, "DIOAD"))
        {
                package_type = DIOAD;
        }
        else if (!strcmp (footprint_type, "DIOM"))
        {
                package_type = DIOM;
        }
        else if (!strcmp (footprint_type, "DIOMELF"))
        {
                package_type = DIOMELF;
        }
        else if (!strcmp (footprint_type, "DIP"))
        {
                package_type = DIP;
        }
        else if (!strcmp (footprint_type, "DIPS"))
        {
                package_type = DIPS;
        }
        else if (!strcmp (footprint_type, "INDC"))
        {
                package_type = INDC;
        }
        else if (!strcmp (footprint_type, "INDP"))
        {
                package_type = INDP;
        }
        else if (!strcmp (footprint_type, "INDM"))
        {
                package_type = INDM;
        }
        else if (!strcmp (footprint_type, "PGA"))
        {
                package_type = PGA;
        }
        else if (!strcmp (footprint_type, "QFN"))
        {
                package_type = QFN;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type %s not yet implemented."),
                        footprint_type);
                return (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "QFP"))
        {
                package_type = QFP;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type %s not yet implemented."),
                        footprint_type);
                return (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "RES"))
        {
                package_type = RES;
        }
        else if (!strcmp (footprint_type, "RESAD"))
        {
                package_type = RESAD;
        }
        else if (!strcmp (footprint_type, "RESAR"))
        {
                package_type = RESAR;
        }
        else if (!strcmp (footprint_type, "RESC"))
        {
                package_type = RESC;
        }
        else if (!strcmp (footprint_type, "SIL"))
        {
                package_type = SIL;
        }
        else if (!strcmp (footprint_type, "SIP"))
        {
                package_type = SIP;
        }
        else if (!strcmp (footprint_type, "SO"))
        {
                package_type = SO;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type %s not yet implemented."),
                        footprint_type);
                return (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "SOT"))
        {
                package_type = SOT;
        }
        else if (!strcmp (footprint_type, "TO92"))
        {
                package_type = TO92;
        }
        else if (!strcmp (footprint_type, "TO220"))
        {
                package_type = TO220;
        }
        else if (!strcmp (footprint_type, "TO220S"))
        {
                package_type = TO220S;
        }
        else if (!strcmp (footprint_type, "TO220SW"))
        {
                package_type = TO220SW;
        }
        else if (!strcmp (footprint_type, "TO220W"))
        {
                package_type = TO220W;
        }
        else
        {
                package_type = NO_PACKAGE;
                g_log ("", G_LOG_LEVEL_CRITICAL,
                        _("footprint type %s is not valid."),
                        footprint_type);
                return (EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Determine if the pin/pad is a non-existing pin or pad.
 *
 * \return EXIT_SUCCESS if pin/pad is non-existing (it is found in the
 * \c pin_pad_exception_string), EXIT_FAILURE if pin/pad exists (it is
 * not found in the \c pin_pad_exception_string).
 */
int
get_pin_pad_exception
(
        gchar *pin_pad_name
                /*!< : name of the pin/pad. */
)
{
        /* Test if a NULL pointer or empty string was passed. */
        if (!pin_pad_name)
                return EXIT_FAILURE;
        if (!pin_pad_exceptions_string)
                return EXIT_FAILURE;
        if (!strcmp (pin_pad_name, ""))
                return EXIT_FAILURE;
        if (!strcmp (pin_pad_exceptions_string, ""))
                return EXIT_FAILURE;
        /* Disect the pin_pad_exceptions_string by tokenizing it and test
         * the tokens against the pin_pad_name. */
        gchar *delimiters = g_strdup (", ");
        gchar *search_string = g_strdup (pin_pad_exceptions_string);
        /* Test the first token. */
        gchar *token = strtok (search_string, delimiters);
        if (!strcmp (pin_pad_name, token))
        {
                return EXIT_SUCCESS;
        }
        else
        {
                /* Test following tokens in a loop. */
                while (token)
                {
                        token = strtok (NULL, delimiters);
                        if (!token)
                                return EXIT_FAILURE;
                        if (!strcmp (pin_pad_name, token))
                        {
                                return EXIT_SUCCESS;
                        }
                }
        }
        /* If we do get until here, let's assume the pin/pad exists. */
        return EXIT_FAILURE;
}


/*!
 * \brief Determine the status type.
 *
 * \return EXIT_SUCCESS if a known status is found in
 * \c footprint_status, EXIT_FAILURE if no known status was found in
 * \c footprint_status.
 */
int
get_status_type ()
{
        /* Determine the status type */
        if ((!strcmp (footprint_status, "")) || (!footprint_status))
        {
                status_type = NO_STATUS;
        }
        else if (!strcmp (footprint_status, "Experimental"))
        {
                status_type = EXPERIMENTAL;
        }
        else if (!strcmp (footprint_status, "Private (not published)"))
        {
                status_type = PRIVATE;
        }
        else if (!strcmp (footprint_status, "Public (released)"))
        {
                status_type = PUBLIC;
        }
        else if (!strcmp (footprint_status, "Stable (confirmed by peers)"))
        {
                status_type = STABLE;
        }
        else
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("footprint status %s is not valid."),
                        footprint_status);
                return (EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Calculate the total number of pins value.
 *
 * Calculate the total number of pins/pads and include fiducials.\n
 * For now assume that there are only two fiducials per package.\n 
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> \c number_of_pins total number of pins.
 */
int
get_total_number_of_pins ()
{
        /* Calculate the total number of pins/pads depending on the package
         * type */
        switch (package_type)
        {
                case BGA :
                        number_of_pins = (number_of_columns * number_of_rows) -
                        number_of_exceptions + (fiducial * 2);
                        break;
                case CAPA :
                        number_of_pins = 2;
                        break;
                case CAPAD :
                        number_of_pins = 2;
                        break;
                case CAPC :
                        number_of_pins = 2;
                        break;
                case CAPM :
                        number_of_pins = 2;
                        break;
                case CAPMP :
                        number_of_pins = 2;
                        break;
                case CON_DIL :
                        number_of_pins = number_of_rows * count_x;
                        break;
                case CON_DIP :
                        number_of_pins = number_of_columns * number_of_rows;
                        break;
                case CON_HDR :
                        number_of_pins = number_of_rows * count_x;
                        break;
                case CON_SIL :
                        number_of_pins = number_of_rows;
                        break;
                case DIL :
                        number_of_pins = number_of_columns * number_of_rows;
                        break;
                case DIOAD :
                        number_of_pins = 2;
                        break;
                case DIOM :
                        number_of_pins = 2;
                        break;
                case DIOMELF :
                        number_of_pins = 2;
                        break;
                case DIP :
                        number_of_pins = number_of_columns * count_y;
                        break;
                case DIPS :
                        number_of_pins = number_of_columns * count_y;
                        break;
                case INDC :
                        number_of_pins = 2;
                        break;
                case INDM :
                        number_of_pins = 2;
                        break;
                case INDP :
                        number_of_pins = 2;
                        break;
                case PGA :
                        number_of_pins = (number_of_columns * number_of_rows) - number_of_exceptions;
                        break;
                case PLCC :
                        number_of_pins = (number_of_columns * count_x +
                                number_of_rows * count_y) + thermal;
                        break;
                case QFN :
                        number_of_pins = (number_of_columns * count_x +
                                number_of_rows * count_y) + thermal;
                        break;
                case QFP :
                        number_of_pins = (number_of_columns * count_x +
                                number_of_rows * count_y) + thermal;
                        break;
                case RES :
                        number_of_pins = 2;
                        break;
                case RESAD :
                        number_of_pins = 2;
                        break;
                case RESAR :
                        number_of_pins = 2;
                        break;
                case RESC :
                        number_of_pins = 2;
                        break;
                case RESM :
                        number_of_pins = 2;
                        break;
                case RESMELF :
                        number_of_pins = 2;
                        break;
                case SIL :
                        number_of_pins = number_of_rows;
                        break;
                case SIP :
                        number_of_pins = number_of_rows;
                        break;
                case SO :
                        break;
                case SOT :
                        break;
                case TO92 :
                        number_of_pins = 3;
                        break;
                default :
                        break;
        }
        return (number_of_pins);
}


/*!
 * \brief Read a footprintwizard file into the global variables.
 *
 * \return EXIT_SUCCESS if footprintwizard is completely read and parsed,
 * EXIT_FAILURE if an error was encountered.
 */
int
read_footprintwizard_file
(
        gchar *fpw_filename
                /*!< : name of the footprintwizard file. */
)
{
        /* Get global variables from footprintwizard file with .fpw suffix */
        FILE *fpw = fopen (fpw_filename, "r");
        if (!fpw)
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("could not open footprint wizard file: %s for reading.\n"),
                                fpw_filename);
                }
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%s\n", footprint_filename);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading footprint_filename value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Check for null pointers or meaningless values. */
        if (!footprint_filename || (!strcmp (footprint_filename, "(null)")))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("footprint filename with a null pointer found in: %s.\n"),
                                fpw_filename);
                }
                footprint_filename = g_strdup ("");
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%s\n", dummy); /* do not (re)use this value ! */
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading a dummy value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%s\n", footprint_type);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading footprint_type value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Check for null pointers or meaningless values. */
        if (!footprint_type || (!strcmp (footprint_type, "(null)")))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("footprint type with a null pointer found in: %s.\n"),
                                fpw_filename);
                }
                footprint_type = g_strdup ("");
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Determine the package type */
        if (get_package_type () == EXIT_FAILURE)
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("footprint type contains an unknown package type."));
                }
                footprint_type = g_strdup ("");
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        else
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                _("determined the package type successful."));
                }
        }
        fscanf (fpw, "%s\n", footprint_units);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading footprint_units value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Check for null pointers or meaningless values. */
        if (!footprint_units || (!strcmp (footprint_units, "(null)")))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("footprint units with null pointer found in: %s.\n"),
                                fpw_filename);
                }
                footprint_units = g_strdup ("");
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Update the units related variables. */
        if (update_units_variables () == EXIT_FAILURE)
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("footprint units contains an unknown units type."));
                }
                footprint_units = g_strdup ("");
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        else
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                _("footprint units variables updated successful."));
                }
        }
        fscanf (fpw, "%s\n", footprint_refdes);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading footprint_refdes value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Check for null pointers or meaningless values. */
        if (!footprint_refdes || (!strcmp (footprint_refdes, "(null)")))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("footprint refdes with a null pointer found in: %s.\n"),
                                fpw_filename);
                }
                footprint_refdes = g_strdup ("");
        }
        fscanf (fpw, "%s\n", footprint_value);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading footprint_value value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Check for null pointers or meaningless values. */
        if (!footprint_value || (!strcmp (footprint_value, "(null)")))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("footprint value with a null pointer found in: %s.\n"),
                                fpw_filename);
                }
                footprint_value = g_strdup ("");
        }
        fscanf (fpw, "%f\n", package_body_length);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading package_body_length value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (package_body_length)) || (isinf (package_body_length)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN found in package body length, in: %s.\n"),
                                fpw_filename);
                }
                package_body_length = 0.0;
        }
        fscanf (fpw, "%f\n", package_body_width);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading package_body_width value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (package_body_width)) || (isinf (package_body_width)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN found in package body width, in: %s.\n"),
                                fpw_filename);
                }
                package_body_width = 0.0;
        }
        fscanf (fpw, "%f\n", package_body_height);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading package_body_height value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (package_body_height)) || (isinf (package_body_height)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN found in package body heigth, in: %s.\n"),
                                fpw_filename);
                }
                package_body_height = 0.0;
        }
        fscanf (fpw, "%d\n", package_is_radial);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading package_is_radial value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%s\n", footprint_author);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading footprint_author value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Check for null pointers or meaningless values. */
        if (!footprint_author || (!strcmp (footprint_author, "(null)")))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("footprint author with a null pointer found in: %s.\n"),
                                fpw_filename);
                }
                footprint_author = g_strdup ("");
        }
        fscanf (fpw, "%s\n", footprint_dist_license);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading footprint_dist_license value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Check for null pointers or meaningless values. */
        if (!footprint_dist_license
                || (!strcmp (footprint_dist_license, "(null)")))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("footprint distribution license with a null pointer found in: %s.\n"),
                                fpw_filename);
                }
                footprint_dist_license = g_strdup ("");
        }
        fscanf (fpw, "%s\n", footprint_use_license);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading footprint_use_license value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Check for null pointers or meaningless values. */
        if (!footprint_use_license
                || (!strcmp (footprint_use_license, "(null)")))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("footprint usage license with a null pointer found in: %s.\n"),
                                fpw_filename);
                }
                footprint_use_license = g_strdup ("");
        }
        fscanf (fpw, "%s\n", footprint_status);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading footprint_status value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Check for null pointers or meaningless values. */
        if (!footprint_status || (!strcmp (footprint_status, "(null)")))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("footprint status with a null pointer found in: %s.\n"),
                                fpw_filename);
                }
                footprint_status = g_strdup ("");
        }
        fscanf (fpw, "%d\n", attributes_in_footprint);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading attributes_in_footprint value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%d\n", number_of_pins);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading number_of_pins value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%d\n", number_of_columns);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading number_of_columns value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%d\n", number_of_rows);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading number_of_rows value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%f\n", pitch_x);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading pitch_x value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (pitch_x)) || (isinf (pitch_x)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number of pitch in X-direction found in: %s.\n"),
                                fpw_filename);
                }
                pitch_x = 0.0;
        }
        fscanf (fpw, "%f\n", pitch_y);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading pitch_y value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (pitch_y)) || (isinf (pitch_y)))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number of pitch in Y-direction found in: %s.\n"),
                                fpw_filename);
                pitch_y = 0.0;
        }
        fscanf (fpw, "%d\n", count_x);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading count_x value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%d\n", count_y);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading count_y value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%s\n", pad_shape);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading pad_shape value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Check for null pointers or meaningless values. */
        if (!pad_shape || (!strcmp (pad_shape, "(null)")))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("pad shape with a null pointer found in: %s.\n"),
                                fpw_filename);
                }
                pad_shape = g_strdup ("");
                return (EXIT_FAILURE);
        }
        /* Update the pad shape related variables. */
        if (update_pad_shapes_variables () == EXIT_FAILURE)
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("pad shape contains an unknown pad shape type."));
                }
                return (EXIT_FAILURE);
        }
        else
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                _("pad shape variables updated successful."));
                }
        }
        fscanf (fpw, "%s\n", pin_pad_exceptions_string);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading pin_pad_exceptions_string value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Check for null pointers or meaningless values. */
        if (!pin_pad_exceptions_string || (!strcmp (pin_pad_exceptions_string, "(null)")))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("pin/pad exceptions with a null pointer found in: %s.\n"),
                                fpw_filename);
                }
                pin_pad_exceptions_string = g_strdup ("");
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%s\n", pin_1_position);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading pin_1_position value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        /* Check for null pointers or meaningless values. */
        if (!pin_1_position || (!strcmp (pin_1_position, "(null)")))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("pin #1 position with a null pointer found in: %s.\n"),
                                fpw_filename);
                }
                pin_1_position = g_strdup ("");
        }
        fscanf (fpw, "%f\n", pad_length);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading pad_length value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (pad_length)) || (isinf (pad_length)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in pad length found in: %s.\n"),
                                fpw_filename);
                }
                pad_length = 0.0;
        }
        fscanf (fpw, "%f\n", pad_width);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading pad_width value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (pad_width)) || (isinf (pad_width)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in pad width found in: %s.\n"),
                                fpw_filename);
                }
                pad_width = 0.0;
        }
        fscanf (fpw, "%f\n", pad_diameter);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading pad_diameter value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (pad_diameter)) || (isinf (pad_diameter)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in pad diameter found in: %s.\n"),
                                fpw_filename);
                }
                pad_diameter = 0.0;
        }
        fscanf (fpw, "%f\n", pin_drill_diameter);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading pin_drill_diameter value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (pin_drill_diameter)) || (isinf (pin_drill_diameter)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in pin drill diameter found in: %s.\n"),
                                fpw_filename);
                }
                pin_drill_diameter = 0.0;
        }
        fscanf (fpw, "%d\n", pin1_square);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading pin1_square value in: %s.\n"),
                                fpw_filename);
                }
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%f\n", pad_clearance);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading pad_clearance value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (pad_clearance)) || (isinf (pad_clearance)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in pad clearance found in: %s.\n"),
                                fpw_filename);
                }
                pad_clearance = 0.0;
        }
        fscanf (fpw, "%f\n", pad_solder_mask_clearance);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading pad_solder_mask_clearance value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (pad_solder_mask_clearance)) ||
                (isinf (pad_solder_mask_clearance)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in pad solder mask clearance found in: %s.\n"),
                                fpw_filename);
                }
                pad_solder_mask_clearance = 0.0;
        }
        fscanf (fpw, "%d\n", thermal);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading thermal value in: %s.\n"),
                                fpw_filename);
                }
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%d\n", thermal_nopaste);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading thermal_nopaste value in: %s.\n"),
                                fpw_filename);
                }
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%f\n", thermal_length);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading thermal_length value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (thermal_length)) || (isinf (thermal_length)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in thermal length found in: %s.\n"),
                                fpw_filename);
                }
                thermal_length = 0.0;
        }
        fscanf (fpw, "%f\n", thermal_width);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading thermal_width value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (thermal_width)) || (isinf (thermal_width)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in thermal width found in: %s.\n"),
                                fpw_filename);
                }
                thermal_width = 0.0;
        }
        fscanf (fpw, "%f\n", thermal_clearance);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading thermal_clearance value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (thermal_clearance)) || (isinf (thermal_clearance)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in thermal clearance found in: %s.\n"),
                                fpw_filename);
                }
                thermal_clearance = 0.0;
        }
        fscanf (fpw, "%f\n", thermal_solder_mask_clearance);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading thermal_solder_mask value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (thermal_solder_mask_clearance)) ||
                (isinf (thermal_solder_mask_clearance)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in thermal solder mask clearance found in: %s.\n"),
                                fpw_filename);
                }
                thermal_solder_mask_clearance = 0.0;
        }
        fscanf (fpw, "%d\n", fiducial);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading fiducial value in: %s.\n"),
                                fpw_filename);
                }
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%f\n", fiducial_pad_diameter);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading fiducial_pad_diameter value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (fiducial_pad_diameter)) || (isinf (fiducial_pad_diameter)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in fiducial pad diameter found in: %s.\n"),
                                fpw_filename);
                }
                fiducial_pad_diameter = 0.0;
        }
        fscanf (fpw, "%f\n", fiducial_pad_solder_mask_clearance);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading fiducial_pad_solder_mask value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (fiducial_pad_solder_mask_clearance)) ||
                (isinf (fiducial_pad_solder_mask_clearance)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in fiducial pad solder mask clearance found in: %s.\n"),
                                fpw_filename);
                }
                fiducial_pad_solder_mask_clearance = 0.0;
        }
        fscanf (fpw, "%d\n", silkscreen_package_outline);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading silkscreen_package_outline value in: %s.\n"),
                                fpw_filename);
                }
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%d\n", silkscreen_indicate_1);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading silkscreen_indicate_1 value in: %s.\n"),
                                fpw_filename);
                }
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%f\n", silkscreen_line_width);
        if ((isnan (silkscreen_line_width)) || (isinf (silkscreen_line_width)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in silkscreen line width found in: %s.\n"),
                                fpw_filename);
                }
                silkscreen_line_width = 0.0;
        }
        fscanf (fpw, "%d\n", courtyard);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading courtyard value in: %s.\n"),
                                fpw_filename);
                }
                return (EXIT_FAILURE);
        }
        fscanf (fpw, "%f\n", courtyard_length);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading courtyard_length value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (courtyard_length)) || (isinf (courtyard_length)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in courtyard length found in: %s.\n"),
                                fpw_filename);
                }
                courtyard_length = 0.0;
        }
        fscanf (fpw, "%f\n", courtyard_width);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading courtyard_width value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (courtyard_width)) || (isinf (courtyard_width)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in courtyard width found in: %s.\n"),
                                fpw_filename);
                }
                courtyard_width = 0.0;
        }
        fscanf (fpw, "%f\n", courtyard_line_width);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading courtyard_line_width value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (courtyard_line_width)) || (isinf (courtyard_line_width)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in courtyard line width found in: %s.\n"),
                                fpw_filename);
                }
                courtyard_line_width = 0.0;
        }
        fscanf (fpw, "%f\n", courtyard_clearance_with_package);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading courtyard_clearance_with_package value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (courtyard_clearance_with_package)) ||
                (isinf (courtyard_clearance_with_package)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in courtyard clearance with package found in: %s.\n"),
                                fpw_filename);
                }
                courtyard_clearance_with_package = 0.0;
        }

        fscanf (fpw, "%f\n", c1);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading c1 value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (c1)) || (isinf (c1)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in top to bottom center-center distance found in: %s.\n"),
                                fpw_filename);
                }
                c1 = 0.0;
        }
        fscanf (fpw, "%f\n", g1);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading g1 value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (g1)) || (isinf (g1)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in top to bottom inner-inner distance found in: %s.\n"),
                                fpw_filename);
                }
                g1 = 0.0;
        }
        fscanf (fpw, "%f\n", z1);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading z1 value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (z1)) || (isinf (z1)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in top to bottom outer-outer distance found in: %s.\n"),
                                fpw_filename);
                }
                z1 = 0.0;
        }
        fscanf (fpw, "%f\n", c2);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading c2 value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (c2)) || (isinf (c2)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in left to right center-center distance found in: %s.\n"),
                                fpw_filename);
                }
                c2 = 0.0;
        }
        fscanf (fpw, "%f\n", g2);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading g2 value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (g2)) || (isinf (g2)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in left to right inner-inner distance found in: %s.\n"),
                                fpw_filename);
                }
                g2 = 0.0;
        }
        fscanf (fpw, "%f\n", z2);
        if (ferror (fpw))
        {
                if ((verbose) || (!silent))
                {
                        g_log ("", G_LOG_LEVEL_CRITICAL,
                                _("error while reading z2 value in: %s.\n"),
                                fpw_filename);
                }
                fclose (fpw);
                return (EXIT_FAILURE);
        }
        if ((isnan (z2)) || (isinf (z2)))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("NaN number in left to right outer-outer distance found in: %s.\n"),
                                fpw_filename);
                }
                z2 = 0.0;
        }
        if (feof (fpw))
        {
                fclose (fpw);
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                "read footprint wizard file: %s.\n",
                                fpw_filename);
                }
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Update locations type variables.
 *
 * \return \c EXIT_SUCCESS when a the locations variables were updated,
 * \c EXIT_FAILURE when errors were encountered.
 */
int
update_location_variables ()
{
        if (!strcmp (pin_1_position, "Upper left"))
        {
                pin1_location = UPPER_LEFT;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Middle left"))
        {
                pin1_location = MIDDLE_LEFT;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Lower left"))
        {
                pin1_location = LOWER_LEFT;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Upper middle"))
        {
                pin1_location = UPPER_MIDDLE;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Middle middle"))
        {
                pin1_location = MIDDLE_MIDDLE;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Lower middle"))
        {
                pin1_location = LOWER_MIDDLE;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Upper right"))
        {
                pin1_location = UPPER_RIGHT;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Middle right"))
        {
                pin1_location = MIDDLE_RIGHT;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Lower right"))
        {
                pin1_location = LOWER_RIGHT;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Left topside"))
        {
                pin1_location = LEFT_TOP;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Right topside"))
        {
                pin1_location = RIGHT_TOP;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Left bottomside"))
        {
                pin1_location = LEFT_BOTTOM;
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pin_1_position, "Right bottomside"))
        {
                pin1_location = RIGHT_BOTTOM;
                return (EXIT_SUCCESS);
        }
        return (EXIT_FAILURE);
}


/*!
 * \brief Update pad shapes type variables.
 *
 * \return \c EXIT_SUCCESS when a known pad shape was determined,
 * \c EXIT_FAILURE when an unknown pad shape was encountered.
 */
int
update_pad_shapes_variables ()
{
        if (!strcmp (pad_shape, "circular pad"))
        {
                pad_shapes_type = ROUND;
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                              _("pad shape is %s, setting pad_shapes_type to ROUND."),
                              pad_shape);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pad_shape, "rectangular pad"))
        {
                pad_shapes_type = SQUARE;
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                              _("pad shape is %s, setting pad_shapes_type to SQUARE."),
                              pad_shape);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pad_shape, "octagonal pad"))
        {
                pad_shapes_type = OCTAGONAL;
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                              _("pad shape is %s, setting pad_shapes_type to OCTOGONAL."),
                              pad_shape);
                }
                return (EXIT_SUCCESS);
        }
        else if (!strcmp (pad_shape, "rounded pad, elongated"))
        {
                pad_shapes_type = ROUND_ELONGATED;
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                              _("pad shape is %s, setting pad_shapes_type to ROUND_ELONGATED."),
                              pad_shape);
                }
                return (EXIT_SUCCESS);
        }
        else
        {
                pad_shapes_type = NO_SHAPE;
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_WARNING,
                              _("encountered a %s pad shape, resetting pad_shapes_type to NO_SHAPE."),
                              pad_shape);
                }
                return (EXIT_FAILURE);
        }
}

/*!
 * \brief Update (units) multiplier and units type variables.
 *
 * \return \c EXIT_SUCCESS when a known units type was determined,
 * \c EXIT_FAILURE when an unknown units type was encountered.
 */
int
update_units_variables ()
{
        if (!strcmp (footprint_units, "mil"))
        {
                multiplier = 100.0;
                units_type = MIL;
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                              _("footprint units_type set to MIL, multiplier set to 100.0"));
                }
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_units, "mil/100"))
        {
                multiplier = 1.0;
                units_type = MIL_100;
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                              _("footprint units_type set to MIL/100, multiplier set to 1.0"));
                }
                return (EXIT_SUCCESS);
        }
        if (!strcmp (footprint_units, "mm"))
        {
                multiplier = (1000 / 25.4) * 100;
                units_type = MM;
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                              _("footprint units_type set to MM, multiplier set to 3937.00..."));
                }
                return (EXIT_SUCCESS);
        }
        return (EXIT_FAILURE);
}


/*!
 * \brief Write attributes based on the global variables.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
write_attributes ()
{
        /* Attributes in the form "Attribute("name" "value")" */
        fprintf (fp, "# Write attributes\n");
        fprintf (fp, "\tAttribute(\"author\" \"%s\")\n", footprint_author);
        fprintf (fp, "\tAttribute(\"dist-license\" \"%s\")\n", footprint_dist_license);
        fprintf (fp, "\tAttribute(\"use-license\" \"%s\")\n", footprint_use_license);
        fprintf (fp, "\tAttribute(\"status\" \"%s\")\n", footprint_status);
        fprintf (fp, "\tAttribute(\"attributes in footprint\" \"%d\")\n", (int) attributes_in_footprint);
        fprintf (fp, "\tAttribute(\"footprint type\" \"%s\")\n", footprint_type);
        fprintf (fp, "\tAttribute(\"footprint name\" \"%s\")\n", footprint_name);
        fprintf (fp, "\tAttribute(\"footprint units\" \"%s\")\n", footprint_units);
        fprintf (fp, "\tAttribute(\"footprint refdes\" \"%s\")\n", footprint_refdes);
        fprintf (fp, "\tAttribute(\"footprint value\" \"%s\")\n", footprint_value);
        fprintf (fp, "\tAttribute(\"package body length\" \"%f\")\n", package_body_length);
        fprintf (fp, "\tAttribute(\"package body width\" \"%f\")\n", package_body_width);
        fprintf (fp, "\tAttribute(\"package height\" \"%f\")\n", package_body_height);
        fprintf (fp, "\tAttribute(\"package is radial\" \"%d\")\n", package_is_radial);
        fprintf (fp, "\tAttribute(\"number of pins\" \"%d\")\n", (int) number_of_pins);
        fprintf (fp, "\tAttribute(\"number of columns\" \"%d\")\n", (int) number_of_columns);
        fprintf (fp, "\tAttribute(\"number of rows\" \"%d\")\n", (int) number_of_rows);
        fprintf (fp, "\tAttribute(\"pitch_x\" \"%f\")\n", pitch_x);
        fprintf (fp, "\tAttribute(\"pitch_y\" \"%f\")\n", pitch_y);
        fprintf (fp, "\tAttribute(\"count_x\" \"%d\")\n", (int) count_x);
        fprintf (fp, "\tAttribute(\"count_x\" \"%d\")\n", (int) count_y);
        fprintf (fp, "\tAttribute(\"pad_shape\" \"%s\")\n", pad_shape);
        fprintf (fp, "\tAttribute(\"pin_pad_exceptions\" \"%s\")\n", pin_pad_exceptions_string);
        fprintf (fp, "\tAttribute(\"pin_1_position\" \"%s\")\n", pin_1_position);
        fprintf (fp, "\tAttribute(\"pad_diameter\" \"%f\")\n", pad_diameter);
        fprintf (fp, "\tAttribute(\"pin_drill_diameter\" \"%f\")\n", pin_drill_diameter);
        fprintf (fp, "\tAttribute(\"pin1_square\" \"%d\")\n", (int) pin1_square);
        fprintf (fp, "\tAttribute(\"pad_length\" \"%f\")\n", pad_length);
        fprintf (fp, "\tAttribute(\"pad_width\" \"%f\")\n", pad_width);
        fprintf (fp, "\tAttribute(\"pad_clearance\" \"%f\")\n", pad_clearance);
        fprintf (fp, "\tAttribute(\"pad_solder_mask_clearance\" \"%f\")\n", pad_solder_mask_clearance);
        fprintf (fp, "\tAttribute(\"thermal\" \"%d\")\n", (int) thermal);
        fprintf (fp, "\tAttribute(\"thermal_nopaste\" \"%d\")\n", (int) thermal_nopaste);
        fprintf (fp, "\tAttribute(\"thermal_length\" \"%f\")\n", thermal_length);
        fprintf (fp, "\tAttribute(\"thermal_width\" \"%f\")\n", thermal_width);
        fprintf (fp, "\tAttribute(\"thermal_clearance\" \"%f\")\n", thermal_clearance);
        fprintf (fp, "\tAttribute(\"thermal_solder_mask_clearance\" \"%f\")\n", thermal_solder_mask_clearance);
        fprintf (fp, "\tAttribute(\"silkscreen_package_outline\" \"%d\")\n", (int) silkscreen_package_outline);
        fprintf (fp, "\tAttribute(\"silkscreen_indicate_1\" \"%d\")\n", (int) silkscreen_indicate_1);
        fprintf (fp, "\tAttribute(\"silkscreen_line_width\" \"%f\")\n", silkscreen_line_width);
        fprintf (fp, "\tAttribute(\"courtyard\" \"%d\")\n", (int) courtyard);
        fprintf (fp, "\tAttribute(\"courtyard_length\" \"%f\")\n", courtyard_length);
        fprintf (fp, "\tAttribute(\"courtyard_width\" \"%f\")\n", courtyard_width);
        fprintf (fp, "\tAttribute(\"courtyard_line_width\" \"%f\")\n", courtyard_line_width);
        fprintf (fp, "\tAttribute(\"courtyard_clearance_with_package\" \"%f\")\n", courtyard_clearance_with_package);
        fprintf (fp, "\tAttribute(\"c1\" \"%f\")\n", c1);
        fprintf (fp, "\tAttribute(\"g1\" \"%f\")\n", g1);
        fprintf (fp, "\tAttribute(\"z1\" \"%f\")\n", z1);
        fprintf (fp, "\tAttribute(\"c2\" \"%f\")\n", c2);
        fprintf (fp, "\tAttribute(\"g2\" \"%f\")\n", g2);
        fprintf (fp, "\tAttribute(\"z2\" \"%f\")\n", z2);
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write an element arc.
 *
 * This function is here to avoid the exhaustive changes of boiler plate code
 * when the file format of pcb footprint changes.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
write_element_arc
(
        gdouble x,
                /*!< : X-coordinate of center. */
        gdouble y,
                /*!< : Y-coordinate of center. */
        gdouble width,
                /*!< : width from center to edge. */
        gdouble height,
                /*!< : height from center to edge. */
        gdouble start_angle,
                /*!< : the angle of the start of the arc in degrees.
                 * 0 = negative X-axis, 90 = positive Y-axis. */
        gdouble delta_angle,
                /*!< : the angle of sweep in degrees.
                 * positive = CCW, negative = CW. */
        gdouble line_width
                /*!< The width of the line which forms the arc. */
)
{
        fprintf
        (
                fp,
                "\tElementArc[%d %d %d %d %d %d %d]\n",
                (int) x,
                (int) y,
                (int) width,
                (int) height,
                (int) start_angle,
                (int) delta_angle,
                (int) line_width
        );
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write an element header based on the global variables.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
write_element_header
(
        gdouble x_text,
                /*!< : X-coordinate of the text insertion point.*/
        gdouble y_text
                /*!< : Y-coordinate of the text insertion point.*/
)
{
        /* Write header to file */
        fprintf
        (
                fp,
                "Element[\"\" \"%s\" \"%s?\" \"%s\" 0 0 %d %d 0 100 \"\"]\n(\n",
                footprint_name,
                footprint_refdes,
                footprint_value,
                (int) (x_text),
                (int) (y_text)
        );
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write an element line.
 *
 * This function is here to avoid the exhaustive changes of boiler plate code
 * when the file format of pcb footprint changes.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
write_element_line
(
        gdouble x0,
                /*!< : X-coordinate of the starting point of the line.
                 * These are relative to the Elements mark point for
                 * new element formats, or absolute for older formats.*/
        gdouble y0,
                /*!< : Y-coordinate of the starting point of the line.
                 * These are relative to the Elements mark point for
                 * new element formats, or absolute for older formats.*/
        gdouble x1,
                /*!< : X-coordinate of the ending point of the line.\n
                 * These are relative to the Elements mark point for
                 * new element formats, or absolute for older formats.*/
        gdouble y1,
                /*!< : Y-coordinate of the ending point of the line.
                 * These are relative to the Elements mark point for
                 * new element formats, or absolute for older formats.*/
        gdouble line_width
                /*!< : the width of the silk for this line.*/
)
{
        fprintf
        (
                fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) x0,
                (int) y0,
                (int) x1,
                (int) y1,
                (int) line_width
        );
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a GPL alike license statement (at the begin of the footprint file).
 *
 * This license text is not identical to the GPL version 2, due to the
 * fact that generated footprints are not a program or (shared) library.\n
 * All software components of pcb-fpw is released under the GNU General
 * Public License (GPL) version 2 or later.\n
 * However, some confusion may exist about the footprints.\n
 * What license do they use?\n
 * Will GPL footprints "infect" your design, thereby requiring you to
 * release your design to the public?\n
 * If you modify any of these footprints, must you release the modified
 * versions under the GPL?\n
 * \n
 * The goal of the pcb-fpw Project is to provide an open-source program
 * which may be used for non-commerical as well as commercial
 * projects.\n
 * This program is aimed for use by students, hobbyists, educators,
 * consultants, and -- yes -- corporate engineers.\n
 * We are not interested in exerting any control over your designs, or
 * forcing you to reveal proprietary information contained in your
 * designs.\n
 * \n
 * Footprints are similar to the font files used in document processing
 * software -- they are graphical objects used to express your ideas.\n
 * We want you to retain control of your own ideas (your design), while
 * the pcb-fpw Project retains a say in how you redistribute the
 * footprints themselves.\n
 * \n
 * There are three ways a footprint might be distributed:
 * <ol>
 * <li>As part of a footprint library, or individually as a .fp file
 * (i.e. as a footprint itself).
 * <li>Embedded in a .pcb file (i.e. part of the soft, or editable copy
 * of a design).\n
 * N.B.: In the pcb application this license text is being stripped, as
 * are all comments, the pcb footprint file parser simply ignores
 * them.\n
 * <li>The resulting graphical expression in gerber files of a pcb
 * design (i.e. as part of the hard, or non-editable copy of a design).
 * </ol>
 * There is a distinction between cases 1 and (2, 3).\n
 * In case 1, the object of interest is the symbol library (or
 * individual symbol) itself.\n
 * In case (2, 3), the object of interest is the design.\n
 * Some label case 1 "distribution", and case (2, 3) "use" of the
 * symbol.
 * Our goals for the footprints are:
 * <ul>
 * <li> We wish to distribute the footprints under a licencing scheme
 * which encourages that you give back to the community if you
 * redistribute the the footprints themselves -- whether modified or
 * unmodified.\n
 * This is case 1 distribution; the GPL ensures this.\n
 * <li> We wish to specifically prohibit anybody from building pcb-fpw
 * footprints into their *software* products, and then place
 * restrictions on how the resulting product may be used.\n
 * If you bundle pcb-fpw footprints -- whether modified or unmodified --
 * into your software and then distribute it, then you must allow for
 * the software's (and footprints') continued redistribution under the
 * GPL.\n
 * Again, this is case 1 distribution; the GPL ensures this.\n
 * However, we do not wish to "infect" your *electronic* design, or
 * force you to release your proprietary design information if you use
 * or embedd pcb-fpw footprints in your design.\n
 * This is case (2, 3) use.\n
 * </ul>
 * \n
 * The Free Software Foundation has recognized a possible conflict of
 * the base GPL with the use of fonts -- and, by analogy, footprints
 * used in case (2, 3).\n
 * Their solution is to use an exemption clause in the GPL which you
 * explicitly insert for fonts.\n
 * Read about it here:
 * http://www.fsf.org/licensing/licenses/gpl-faq.html#FontException
 * \n
 * \n
 * Therefore, using this as a template, all footprints released with
 * pcb-fpw are covered under the GPL with the following exception
 * clause:\n
 * <pre>
 * # This footprint is free software; you may redistribute it and/or modify
 * # it under the terms of the GNU General Public License as published by the
 * # Free Software Foundation; either version 2 of the License, or (at your
 * # option) any later version.
 * # As a special exception, if you create a design which uses this
 * # footprint, and embed this footprint or unaltered portions of this
 * # footprint into the design, this footprint does not by itself cause
 * # the resulting design to be covered by the GNU General Public
 * # License.
 * # This exception does not however invalidate any other reasons why
 * # the design itself might be covered by the GNU General Public
 * # License.
 * # If you modify this footprint, you may extend this exception to your
 * # version of the footprint, but you are not obligated to do so.
 * # If you do not wish to do so, delete this exception statement from
 * # your version.
 * </pre>
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
write_license
(
)
{
        /* Write the license statement for footprints for the GPL version to file */
        fprintf (fp, "# This footprint is free software; you may redistribute it and/or modify\n");
        fprintf (fp, "# it under the terms of the GNU General Public License as published by the\n");
        fprintf (fp, "# Free Software Foundation; either version 2 of the License, or (at your\n");
        fprintf (fp, "# option) any later version.\n");
        fprintf (fp, "# As a special exception, if you create a design which uses this\n");
        fprintf (fp, "# footprint, and embed this footprint or unaltered portions of this\n");
        fprintf (fp, "# footprint into the design, this footprint does not by itself cause\n");
        fprintf (fp, "# the resulting design to be covered by the GNU General Public\n");
        fprintf (fp, "# License.\n");
        fprintf (fp, "# This exception does not however invalidate any other reasons why\n");
        fprintf (fp, "# the design itself might be covered by the GNU General Public\n");
        fprintf (fp, "# License.\n");
        fprintf (fp, "# If you modify this footprint, you may extend this exception to your\n");
        fprintf (fp, "# version of the footprint, but you are not obligated to do so.\n");
        fprintf (fp, "# If you do not wish to do so, delete this exception statement from\n");
        fprintf (fp, "# your version.\n");
        fprintf (fp, "#\n");
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a pad for any given footprint.
 *
 * This function is here to avoid the exhaustive changes of boiler plate code
 * when the file format of pcb footprint changes.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
write_pad
(
        gint pad_number,
                /*!< : pad number */
        gchar *pad_name,
                /*!< : pad name */
        gdouble x0,
                /*!< : X-coordinate of the starting point of the pad.*/
        gdouble y0,
                /*!< : Y-coordinate of the starting point of the pad.*/
        gdouble x1,
                /*!< : X-coordinate of the end point of the pad.*/
        gdouble y1,
                /*!< : Y-coordinate of the end point of the pad.*/
        gdouble width,
                /*!< : the width of the pad.*/
        gdouble clearance,
                /*!< : clearance of other copper around the pad.*/
        gdouble pad_solder_mask_clearance,
                /*!< : solder mask clearance araound the pad.*/
        gchar *flags
                /*!< : flags separated by commas:
                 * <ul>
                 * <li> \c CLEAR : default is round pads on the
                 * component side of the pcb.
                 * <li> \c EDGE2 : indicates that the second point is
                 * closer to the edge.
                 * <li> \c LOCK : for locked objects.
                 * <li> \c NOPASTE : set to prevent a solderpaste
                 * stencil opening for the pad.
                 * <li> \c ONSOLDER : for pads on the solder side.
                 * <li> \c SQUARE : for rectangular pads.
                 * <li> \c WARN : set to indicate a warning.
                 * </ul>
                 */
)
{
        fprintf
        (
                fp,
                "\tPad[%d %d %d %d %d %d %d \"%s\" \"%d\" \"%s\"]\n",
                (int) x0,
                (int) y0,
                (int) x1,
                (int) y1,
                (int) width,
                (int) clearance,
                (int) pad_solder_mask_clearance,
                pad_name,
                pad_number,
                flags
        );
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a pin for any given footprint.
 *
 * This function is here to avoid the exhaustive changes of boiler plate code
 * when the file format of pcb footprint changes.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
write_pin
(
        gint pin_number,
                /*!< : pin number */
        gchar *pin_name,
                /*!< : pin name */
        gdouble x0,
                /*!< : X-coordinate of the pin.*/
        gdouble y0,
                /*!< : Y-coordinate of the pin.*/
        gdouble width,
                /*!< : width of the annulus ring of the pin (pad).*/
        gdouble clearance,
                /*!< : clearance of other copper around the pin.*/
        gdouble pad_solder_mask_clearance,
                /*!< : solder mask clearance around the pin (pad)*/
        gdouble drill,
                /*!< : pin drill diameter.*/
        gchar *flags
                /*!< : flags separated by commas:
                 * <ul>
                 * <li> \c CLEAR : default is round pads on both sides
                 * of the pcb.
                 * <li> \c EDGE2 : indicates that the pin is closer to a
                 * horizontal edge and thus pinout text should be
                 * vertical.
                 * <li> \c HOLE : for unplated holes.
                 * <li> \c LOCK : for locked objects.
                 * <li> \c OCTAGON : for octagon pads.
                 * <li> \c SQUARE : for square pads.
                 * <li> \c WARN : set to indicate a warning.
                 * <\ul>
                 */
)
{
        fprintf
        (
                fp,
                "\tPin[%d %d %d %d %d %d \"%s\" \"%d\" \"%s\"]\n",
                (int) x0,
                (int) y0,
                (int) width,
                (int) clearance,
                (int) pad_solder_mask_clearance,
                (int) drill,
                pin_name,
                pin_number,
                flags
        );
        return (EXIT_SUCCESS);
}

/*!
 * \brief Write a rectangle for any given footprint.
 *
 * Write a rectangle for any given footprint.
 * If line_width is 0.0 no rectangle is drawn.
 * If line_width is < 0.0 a rectangle with a linewidth of 1/100 of
 * a mil is drawn (#define THIN_DRAW 1).
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
write_rectangle
(
        gdouble xmin,
                /*!< : minimum X-coordinate of rectangle.*/
        gdouble ymin,
                /*!< : minimum Y-coordinate of rectangle.*/
        gdouble xmax,
                /*!< : maximum X-coordinate of rectangle.*/
        gdouble ymax,
                /*!< : maximum Y-coordinate of rectangle.*/
        gdouble line_width
                /*!< : line width. */
)
{
        /* If line_width is 0.0 do not draw a rectangle */
        if (line_width == 0.0)
        {
                return;
        }
        /* If line_width is < 0.0 a rectangle with a linewidth of
         * 1/100 of a mil is drawn (#define THIN_DRAW 1)
         */
        if (line_width < 0.0)
        {
                line_width = THIN_DRAW;
        }
        /* Print rectangle ends (perpendicular to x-axis) */
        fprintf
        (
                fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) xmin,
                (int) ymin,
                (int) xmin,
                (int) ymax,
                (int) line_width
        );
        fprintf
        (
                fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) xmax,
                (int) ymin,
                (int) xmax,
                (int) ymax,
                (int) line_width
        );
        /* Print rectangle sides (parallel with x-axis) */
        fprintf
        (
                fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) xmin,
                (int) ymin,
                (int) xmax,
                (int) ymin,
                (int) line_width
        );
        fprintf
        (
                fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) xmax,
                (int) ymax,
                (int) xmin,
                (int) ymax,
                (int) line_width
        );
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a footprintwizard file based on the current global
 * variables.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
write_footprintwizard_file
(
        gchar *fpw_filename
                /*!< : a \c NULL terminated fpw_filename.*/
)
{
        /* Write global variables to footprintwizard file with .fpw suffix */
        FILE *fpw = fopen (fpw_filename, "w");
        if (!fpw)
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not open footprint wizard file: %s for writing."),
                        fpw_filename);
                return (EXIT_FAILURE);
        }
        /* Footprint filename may not be null or empty. */
        if (!footprint_filename || (!strcmp (footprint_filename, "")))
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not write footprint wizard file (null or empty footprint filename string)."));
                return (EXIT_FAILURE);
        }
        /* Footprint name may not be null or empty. */
        if (!footprint_name || (!strcmp (footprint_name, "")))
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not write footprint wizard file (null or empty footprint name string)."));
                return (EXIT_FAILURE);
        }
        /* Footprint type may not be null or empty. */
        if (!footprint_type || (!strcmp (footprint_type, "")))
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not write footprint wizard file (null or empty footprint type string)."));
                return (EXIT_FAILURE);
        }
        /* Footprint units may not be null or empty. */
        if (!footprint_units || (!strcmp (footprint_units, "")))
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not write footprint wizard file (null or empty footprint units string)."));
                return (EXIT_FAILURE);
        }
        /* The pad shape needs to be defined. */
        if (!pad_shape)
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not write footprint wizard file (null or empty pad shape string)."));
                return (EXIT_FAILURE);
        }
        if (!pin_pad_exceptions_string)
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not write footprint wizard file (null or empty pin/pad exception string)."));
                return (EXIT_FAILURE);
        }
        /* These variables have been checked for valid content above. */
        fprintf (fpw, "%s\n", footprint_filename);
        fprintf (fpw, "%s\n", footprint_name);
        fprintf (fpw, "%s\n", footprint_type);
        fprintf (fpw, "%s\n", footprint_units);
        /* The following string values may contain an empty string.
         * If a null pointer is encountered an empty string is written as to
         * prevent "(null)" string values from emerging in the fpw file.
         * The following values of type double are allowed to be 0.0 .
         * The following values of type integer are allowed to be 0 .
         */
        (!footprint_refdes) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", footprint_refdes);
        (!footprint_value) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", footprint_value);
        fprintf (fpw, "%f\n", package_body_length);
        fprintf (fpw, "%f\n", package_body_width);
        fprintf (fpw, "%f\n", package_body_height);
        fprintf (fpw, "%d\n", package_is_radial);
        (!footprint_author) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", footprint_author);
        (!footprint_dist_license) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", footprint_dist_license);
        (!footprint_use_license) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", footprint_use_license);
        (!footprint_status) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", footprint_status);
        fprintf (fpw, "%d\n", attributes_in_footprint);
        fprintf (fpw, "%d\n", number_of_pins);
        fprintf (fpw, "%d\n", number_of_columns);
        fprintf (fpw, "%d\n", number_of_rows);
        fprintf (fpw, "%f\n", pitch_x);
        fprintf (fpw, "%f\n", pitch_y);
        fprintf (fpw, "%f\n", count_x);
        fprintf (fpw, "%f\n", count_y);
        fprintf (fpw, "%s\n", pad_shape);
        fprintf (fpw, "%s\n", pin_pad_exceptions_string);
        (!pin_1_position) ? fprintf (fpw, "\n") :
                fprintf (fpw, "%s\n", pin_1_position);
        fprintf (fpw, "%f\n", pad_diameter);
        fprintf (fpw, "%f\n", pin_drill_diameter);
        fprintf (fpw, "%d\n", pin1_square);
        fprintf (fpw, "%f\n", pad_length);
        fprintf (fpw, "%f\n", pad_width);
        fprintf (fpw, "%f\n", pad_clearance);
        fprintf (fpw, "%f\n", pad_solder_mask_clearance);
        fprintf (fpw, "%d\n", thermal);
        fprintf (fpw, "%d\n", thermal_nopaste);
        fprintf (fpw, "%f\n", thermal_length);
        fprintf (fpw, "%f\n", thermal_width);
        fprintf (fpw, "%f\n", thermal_clearance);
        fprintf (fpw, "%f\n", thermal_solder_mask_clearance);
        fprintf (fpw, "%d\n", fiducial);
        fprintf (fpw, "%f\n", fiducial_pad_diameter);
        fprintf (fpw, "%f\n", fiducial_pad_solder_mask_clearance);
        fprintf (fpw, "%d\n", silkscreen_package_outline);
        fprintf (fpw, "%d\n", silkscreen_indicate_1);
        fprintf (fpw, "%f\n", silkscreen_line_width);
        fprintf (fpw, "%d\n", courtyard);
        fprintf (fpw, "%f\n", courtyard_length);
        fprintf (fpw, "%f\n", courtyard_width);
        fprintf (fpw, "%f\n", courtyard_line_width);
        fprintf (fpw, "%f\n", courtyard_clearance_with_package);
        fprintf (fpw, "%f\n", c1);
        fprintf (fpw, "%f\n", g1);
        fprintf (fpw, "%f\n", z1);
        fprintf (fpw, "%f\n", c2);
        fprintf (fpw, "%f\n", g2);
        fprintf (fpw, "%f\n", z2);
        fclose (fpw);
        fprintf (stderr, "SUCCESS: wrote Footprintwizard file %s.\n",
                fpw_filename);
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a footprint based on the global variables.
 *
 * This function does not write the footprint file itself.\n
 * It is a dispatcher for helper functions who <b>actually</b> do write
 * the contents for the footprint to file.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
int
write_footprint()
{
        int error_found;
        error_found = FALSE;
        /* Switch depending the package type */
        switch (package_type)
        {
                case BGA:
                        if (bga_drc() == EXIT_SUCCESS)
                        {
                                bga_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case CAPA:
                        if (capa_drc () == EXIT_SUCCESS)
                        {
                                capa_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case CAPC:
                        if (capc_drc () == EXIT_SUCCESS)
                        {
                                capc_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case CAPM:
                        if (capm_drc () == EXIT_SUCCESS)
                        {
                                capm_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case CAPMP:
                        if (capmp_drc () == EXIT_SUCCESS)
                        {
                                capmp_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case CAPPR:
                        if (cappr_drc () == EXIT_SUCCESS)
                        {
                                cappr_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case CON_DIL:
                        if (con_dil_drc() == EXIT_SUCCESS)
                        {
                                con_dil_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case CON_DIP:
                        if (con_dip_drc() == EXIT_SUCCESS)
                        {
                                con_dip_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case CON_HDR:
                        if (con_hdr_drc () == EXIT_SUCCESS)
                        {
                                con_hdr_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case CON_SIL:
                        if (con_sil_drc () == EXIT_SUCCESS)
                        {
                                con_sil_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case DIL:
                        return (EXIT_FAILURE);
                        break;
                case DIOAD:
                        if (dioad_drc () == EXIT_SUCCESS)
                        {
                                dioad_write_footprint ();                        break;
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case DIOM:
                        if (diom_drc () == EXIT_SUCCESS)
                        {
                                diom_write_footprint ();                        break;
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case DIOMELF:
                        if (diomelf_drc () == EXIT_SUCCESS)
                        {
                                diomelf_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case DIP:
                        if (dip_drc () == EXIT_SUCCESS)
                        {
                                dip_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case DIPS:
                        if (dips_drc () == EXIT_SUCCESS)
                        {
                                dips_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case INDC:
                        if (indc_drc () == EXIT_SUCCESS)
                        {
                                indc_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case INDM:
                        if (indm_drc () == EXIT_SUCCESS)
                        {
                                indm_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case INDP:
                        if (indp_drc () == EXIT_SUCCESS)
                        {
                                indp_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case PGA:
                        if (pga_drc () == EXIT_SUCCESS)
                        {
                                pga_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case PLCC:
                        if (plcc_drc () == EXIT_SUCCESS)
                        {
                                plcc_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case QFN:
                        return (EXIT_FAILURE);
                        break;
                case QFP:
                        return (EXIT_FAILURE);
                        break;
                case RES:
                        if (res_drc () == EXIT_SUCCESS)
                        {
                                res_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case RESAD:
                        if (resad_drc () == EXIT_SUCCESS)
                        {
                                resad_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case RESAR:
                        if (resar_drc () == EXIT_SUCCESS)
                        {
                                resar_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case RESC:
                        if (resc_drc () == EXIT_SUCCESS)
                        {
                                resc_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case RESM:
                        if (resm_drc () == EXIT_SUCCESS)
                        {
                                resm_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case RESMELF:
                        if (resmelf_drc () == EXIT_SUCCESS)
                        {
                                resmelf_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case SIL:
                        if (sil_drc () == EXIT_SUCCESS)
                        {
                                sil_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case SIP:
                        if (sip_drc () == EXIT_SUCCESS)
                        {
                                sip_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case SO:
                        return (EXIT_FAILURE);
                        break;
                case SOT:
                        if (sot_drc () == EXIT_SUCCESS)
                        {
                                sot_write_footprint ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case TO92:
                        if (to_drc () == EXIT_SUCCESS)
                        {
                                to_write_footprint_to92 ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case TO220:
                        if (to_drc () == EXIT_SUCCESS)
                        {
                                to_write_footprint_to220 ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case TO220S:
                        if (to_drc () == EXIT_SUCCESS)
                        {
                                to_write_footprint_to220_staggered ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case TO220SW:
                        if (to_drc () == EXIT_SUCCESS)
                        {
                                to_write_footprint_to220_standing_staggered ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                case TO220W:
                        if (to_drc () == EXIT_SUCCESS)
                        {
                                to_write_footprint_to220_standing ();
                        }
                        else
                        {
                                error_found = TRUE;
                        }
                        break;
                default:
                        if ((verbose) || (!silent))
                        {
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("unknown or not yet implemented footprint type entered.\n"));
                        }
                        return (EXIT_FAILURE);
                        break;
        }
        if (error_found)
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        (_("no [%s] footprint written: found DRC errors while checking package %s.")),
                        footprint_type, footprint_name);
        }
        return (EXIT_SUCCESS);
}

/* EOF */
