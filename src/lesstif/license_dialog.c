/*!
 * \file src/lesstif/license_dialog.c
 *
 * \author Copyright 2007 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief License dialog for the pcb footprintwizard (pcb-lfpw).
 *
 * pcb-lfpw (Lesstif FootPrintWizard) is a program for the creation of
 * footprint files to be used by the pcb layout application
 * (see http://pcb.geda-project.org) for the placement of parts in a pcb
 * layout.\n
 * \n
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

#include "../../config.h"
#include "util.h"
#include "main_window.h"
#include "license_dialog.h"


/* local variables */
Widget license_dialog = NULL;


/*!
 * \brief The "Close" button of the "License" dialog is clicked.
 *
 * <b>Parameters:</b> \c w is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c *client_data is the ...\n
 * \n
 * <b>Parameters:</b> \c *call_data is the ...\n
 * \n
 * <b>Returns:</b> none.
 */
void
on_license_dialog_close_button_clicked
(
        Widget w,
        XtPointer client_data,
        XtPointer call_data
)   
{
        XtUnmanageChild (w);
}


/*!
 * \brief Create the "License" dialog.
 *
 * The advantage to using the XmCreate*Dialog functions
 * over Xt ones is that the Popup Dialog is auto-centered over
 * parent widget.
 * 
 * <b>Parameters:</b> \c w is the toplevel widget.\ n
 * \n
 * <b>Returns:</b> none.
 */
void
create_license_dialog (Widget w)
{
        Widget license_dialog_drawing_area;
        Widget license_dialog_frame;
        Widget license_dialog_close_button;
        Widget license_dialog_label;
        XmString xmstrings[10];
        XmFontList fontlist;

        /* Get the font list. */
        fontlist = get_fontlist
        (
                w,
                "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
        );
        /* Create a BulletinBoard type dialog. */
        n=0;
        stdarg (XmNtitle, "License");
        stdarg (XmNdeleteResponse, XmDO_NOTHING);
        stdarg (XmNmwmFunctions, MWM_FUNC_RESIZE | MWM_FUNC_MOVE | MWM_FUNC_MINIMIZE | MWM_FUNC_MAXIMIZE);
        stdarg (XmNbackground, get_pixel (w, "gray"));
        license_dialog = XmCreateBulletinBoardDialog
        (
                main_window,
                "license_dialog",
                args,
                n
        );
        /* Create a drawing area. */
        n = 0;
        stdarg (XmNbackground, get_pixel (w, "gray"));
        license_dialog_drawing_area = XtCreateManagedWidget
        (
                "license_dialog_drawing_area",
                xmDrawingAreaWidgetClass,
                license_dialog,
                args,
                n
        );
        /* Create a frame around the drawing area. */
        stdarg (XmNshadowThickness, 5);
        stdarg (XmNshadowType, XmSHADOW_OUT);
        license_dialog_frame = XtCreateManagedWidget
        (
                "license_dialog_frame",
                xmFrameWidgetClass,
                license_dialog_drawing_area,
                args,
                n
        );
        /* Create a "Close" button. */
        xmstrings[0] = XmStringCreateSimple ("Close");
        n = 0;
        stdarg (XmNforeground, get_pixel (w, "black"));
        stdarg (XmNbackground, get_pixel (w, "gray"));
        stdarg (XmNfontList, fontlist);
        stdarg (XmNlabelString, xmstrings[0]);
        stdarg (XmNshowAsDefault, 1);
        stdarg (XmNy, 200);
        stdarg (XmNx, 155);
        license_dialog_close_button = XtCreateManagedWidget
                (
                        "license_dialog_close_button",
                        xmPushButtonWidgetClass,
                        license_dialog_drawing_area,
                        args,
                        n
                );
        XtAddCallback
        (
                license_dialog_close_button,
                XmNactivateCallback,
                on_license_dialog_close_button_clicked,
                NULL
        );
        XmStringFree (xmstrings[0]);
        /* Create the license dialog text label. */
        xmstrings[0] = create_license_dialog_xmstring ();
        n = 0;
        stdarg (XmNalignment, XmALIGNMENT_BEGINNING);
        stdarg (XmNtraversalOn, False);
        stdarg (XmNmarginHeight, 10);
        stdarg (XmNmarginWidth, 10);
        stdarg (XmNrecomputeSize, True);
        stdarg (XmNforeground, get_pixel (w, "black"));
        stdarg (XmNbackground, get_pixel (w, "gray"));
        stdarg (XmNlabelString, xmstrings[0]);
        stdarg (XmNfontList, fontlist);
        license_dialog_label = XtCreateManagedWidget
        (
                "license_dialog_label",
                xmLabelWidgetClass,
                license_dialog_frame,
                args,
                n
        );
        /* Clean up. */
        XmStringFree (xmstrings[0]);
        XmFontListFree (fontlist);

}


/*!
 * \brief This puts together the XmString text for display on the
 * "license" dialog.
 * 
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> \c xms.
 */
XmString
create_license_dialog_xmstring (void)
{
        XmString xms;

        /* Create a license string. */
        xms = XmStringCreateLtoR
        (
                "This program is free software; you can redistribute it and/or modify\nit under the terms of the GNU General Public License as published by\nthe Free Software Foundation; either version 2 of the License, or\n(at your option) any later version.\n\nThis program is distributed in the hope that it will be useful,\nbut WITHOUT ANY WARRANTY; without even the implied warranty of\nMERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\nSee the GNU General Public License for more details.\n\nYou should have received a copy of the GNU General Public License\nalong with this program; if not, write to:\nthe Free Software Foundation, Inc.,\n51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\n",
                XmSTRING_DEFAULT_CHARSET
        );
        return (xms);
}


/*!
 * \brief Show the "license" dialog.
 *
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> none.
 */
void
show_license_dialog (void)
{
        if (!license_dialog)
        {
                create_license_dialog (main_window);
        }
        XtManageChild (license_dialog);
}


/* EOF */
