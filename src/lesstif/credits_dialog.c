/*!
 * \file src/lesstif/credits_dialog.c
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Credits dialog for the pcb footprintwizard (pcb-lfpw).
 *
 * pcb-lfpw (Lesstif FootPrintWizard) is a program for the creation of
 * footprint files to be used by the pcb layout application
 * (see http://pcb.gpleda.org) for the placement of parts in a pcb
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
#include "credits_dialog.h"


/* local variables */
Widget credits_dialog = NULL;


/*!
 * \brief The "Close" button of the "Credits" dialog is clicked.
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
on_credits_dialog_close_button_clicked
(
        Widget w,
        XtPointer client_data,
        XtPointer call_data
)   
{
        XtUnmanageChild (w);
}


/*!
 * \brief Create the "Credits" dialog.
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
create_credits_dialog (Widget w)
{
        Widget credits_dialog_drawing_area;
        Widget credits_dialog_frame;
        Widget credits_dialog_close_button;
        Widget credits_dialog_label;
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
        stdarg (XmNtitle, "Credits");
        stdarg (XmNdeleteResponse, XmDO_NOTHING);
        stdarg (XmNmwmFunctions, MWM_FUNC_RESIZE | MWM_FUNC_MOVE | MWM_FUNC_MINIMIZE | MWM_FUNC_MAXIMIZE);
        stdarg (XmNbackground, get_pixel (w, "gray"));
        credits_dialog = XmCreateBulletinBoardDialog
        (
                main_window,
                "credits_dialog",
                args,
                n
        );
        /* Create a drawing area. */
        n = 0;
        stdarg (XmNbackground, get_pixel (w, "gray"));
        credits_dialog_drawing_area = XtCreateManagedWidget
        (
                "credits_dialog_drawing_area",
                xmDrawingAreaWidgetClass,
                credits_dialog,
                args,
                n
        );
        /* Create a frame around the drawing area. */
        stdarg (XmNshadowThickness, 5);
        stdarg (XmNshadowType, XmSHADOW_OUT);
        credits_dialog_frame = XtCreateManagedWidget
        (
                "credits_dialog_frame",
                xmFrameWidgetClass,
                credits_dialog_drawing_area,
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
        credits_dialog_close_button = XtCreateManagedWidget
                (
                        "credits_dialog_close_button",
                        xmPushButtonWidgetClass,
                        credits_dialog_drawing_area,
                        args,
                        n
                );
        XtAddCallback
        (
                credits_dialog_close_button,
                XmNactivateCallback,
                on_credits_dialog_close_button_clicked,
                NULL
        );
        XmStringFree (xmstrings[0]);
        /* Create the credits dialog text label. */
        xmstrings[0] = create_credits_dialog_xmstring ();
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
        credits_dialog_label = XtCreateManagedWidget
        (
                "credits_dialog_label",
                xmLabelWidgetClass,
                credits_dialog_frame,
                args,
                n
        );
        /* Clean up. */
        XmStringFree (xmstrings[0]);
        XmFontListFree (fontlist);

}


/*!
 * \brief This puts together the XmString text for display on the
 * "Credits" dialog.
 * 
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> \c xms.
 */
XmString
create_credits_dialog_xmstring (void)
{
        XmString xms;
        XmString nxt;
        XmString lst;

        /* Create a credits string. */
        lst = XmStringCreateLtoR
        (
                "Written by:\n",
                XmSTRING_DEFAULT_CHARSET
        );
        nxt = XmStringCreateLtoR
        (
                "Bert Timmerman <bert.timmerman@xs4all.nl>\n",
                XmSTRING_DEFAULT_CHARSET
        );
        xms = XmStringConcat (lst, nxt);
        XmStringFree (lst);
        XmStringFree (nxt);
        nxt = xms;
        /* The next entry goes in here. */
        lst = XmStringCreateLtoR
        (
                "\n",
                XmSTRING_DEFAULT_CHARSET
        );
        xms = XmStringConcat (xms, lst);
        /* Clean up temporary stuff. */
        XmStringFree (lst);
        XmStringFree (nxt);
        return (xms);
}


/*!
 * \brief Show the "Credits" dialog.
 *
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> none.
 */
void
show_credits_dialog (void)
{
        if (!credits_dialog)
        {
                create_credits_dialog (main_window);
        }
        XtManageChild (credits_dialog);
}


/* EOF */
