/*!
 * \file src/lesstif/util.c
 *
 * \author Copyright 2007 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief utilities for the pcb footprintwizard (pcb-lfpw).
 *
 * pcb-lfpw (LesstifFootPrintWizard) is a program for the creation of footprint
 * files to be used by with the pcb layout application
 * (see http://pcb.geda-project.org) for the placement of parts in a pcb
 * layout.\n
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


#include <stdio.h>

#include "xincludes.h"

#include "util.h"


/*!
 * \brief Get the fontlist.
 *
 * \return \c fontlist.
 */
XmFontList
get_fontlist (Widget w, char *fontname)
{
        XFontStruct *font;
        XmFontList fontlist;

        font = XLoadQueryFont (XtDisplay (w), fontname);
        if (font == NULL)
        {
                fprintf (stderr, "\tCould not load font: %s\n\n",
                        fontname);
                fprintf (stderr, "\tUsing this system's default font instead.\n\n");
                font = XLoadQueryFont (XtDisplay (w), XtDefaultFont);
        };
        fontlist = XmFontListCreate (font, XmSTRING_DEFAULT_CHARSET);
        return (fontlist);
}


/*!
 * \brief Get the pixel color.
 *
 * \return \c color.pixel.
 */
Pixel
get_pixel (Widget w, char *resource_value)
{
        Colormap colormap;
        Boolean status;
        XColor exact, color;

        colormap = DefaultColormapOfScreen
        (
                DefaultScreenOfDisplay (XtDisplay (w))
        );
        status = XAllocNamedColor
        (
                XtDisplay (w),
                colormap,
                resource_value,
                &color,
                &exact
        );
        if (status == 0)
        {
                fprintf (stderr, "Unknown color: %s", resource_value);
                color.pixel = BlackPixelOfScreen 
                (
                        DefaultScreenOfDisplay (XtDisplay (w))
                );
        };
        return (color.pixel);
}


/* EOF */
