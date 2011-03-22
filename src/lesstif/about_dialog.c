/*!
 * \file src/lesstif/about_dialog.c
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief About dialog for the pcb footprintwizard (pcb-lfpw).
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
#include <stdlib.h>
#include <stdarg.h>

#include "xincludes.h"

#include "../../config.h"
#include "util.h"
#include "pcb_lfpw.h"
#include "main_window.h"
#include "about_dialog.h"


/*!
 * \brief The "Close" button of the "About pcb-lfpw" dialog is clicked.
 *
 * <b>Returns:</b> none.
 */
void
on_about_dialog_close_button_clicked (Widget w, XtPointer client_data, XtPointer call_data)   
{
        XtUnmanageChild (about_dialog);
}


/*!
 * \brief The "Credits" button of the "About pcb-lfpw" dialog is clicked.
 *
 * <b>Returns:</b> none.
 */
void
on_about_dialog_credits_button_clicked (Widget w, XtPointer client_data, XtPointer call_data)   
{
        /*! \todo Add code ... */
}


/*!
 * \brief The "License" button of the "About pcb-lfpw" dialog is clicked.
 *
 * \n
 * <b>Returns:</b> none.
 */
void
on_about_dialog_license_button_clicked (Widget w, XtPointer client_data, XtPointer call_data)   
{
        /*! \todo Add code ... */
}


/*!
 * \brief Create the "About pcb-lfpw" dialog.
 *
 * The advantage to using the XmCreate*Dialog functions
 * over Xt ones is that the Popup Dialog is auto-centered over
 * parent widget.
 * 
 * <b>Parameters:</b> \c parent is the ...\n
 * \n
 * <b>Returns:</b> none.
 */
int
create_about_dialog (int argc, char **argv)
{
        Widget about_dialog_drawing_area;
        Widget about_dialog_frame;
        Widget about_dialog_credits_button;
        Widget about_dialog_license_button;
        Widget about_dialog_close_button;
        Widget about_dialog_label;
        XmString xmstrings[10];
        XmFontList fontlist;

        about_dialog = XtVaAppInitialize
        (
                &pcb_lfpw_app_context,
                "about dialog",
                NULL,
                0,
                &argc,
                argv,
                NULL
        );
        fontlist = get_fontlist (main_window, "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1");
        /* Create a BulletinBoard type dialog. */
        n = 0;
        stdarg (XmNtitle, "About pcb-lfpw");
        stdarg (XmNdeleteResponse, XmDO_NOTHING);
        stdarg
        (
                XmNmwmFunctions,
                MWM_FUNC_RESIZE |
                MWM_FUNC_MOVE |
                MWM_FUNC_MINIMIZE |
                MWM_FUNC_MAXIMIZE
        );
        stdarg (XmNbackground, get_pixel (main_window, "gray"));
        about_dialog = XmCreateBulletinBoardDialog
        (
                main_window,
                "about_dialog",
                args,
                n
        );
        /* Create a drawing area. */
        n = 0;
        stdarg (XmNbackground, get_pixel (main_window, "gray"));
        about_dialog_drawing_area = XtCreateManagedWidget
        (
                "about_dialog_drawing_area",
                xmDrawingAreaWidgetClass,
                about_dialog,
                args,
                n
        );
        /* Create a frame around the drawing area. */
        n = 0;
        stdarg (XmNshadowThickness, 5);
        stdarg (XmNshadowType, XmSHADOW_OUT);
        about_dialog_frame = XtCreateManagedWidget
        (
                "about_dialog_frame",
                xmFrameWidgetClass,
                about_dialog_drawing_area,
                args,
                n
        );
        /* Create a "Credits" button. */
        xmstrings[0] = XmStringCreateSimple ("Credits");
        n = 0;
        stdarg (XmNforeground, get_pixel (main_window, "black"));
        stdarg (XmNbackground, get_pixel (main_window, "gray"));
        stdarg (XmNfontList, fontlist);
        stdarg (XmNlabelString, xmstrings[0]);
        stdarg (XmNshowAsDefault, 1);
        stdarg (XmNy, 200);
        stdarg (XmNx, 155);
        about_dialog_credits_button = XtCreateManagedWidget
        (
                "about_dialog_credits_button",
                xmPushButtonWidgetClass,
                about_dialog_drawing_area,
                args,
                n
        );
        XtAddCallback
        (
                about_dialog_credits_button,
                XmNactivateCallback, 
                on_about_dialog_credits_button_clicked,
                NULL
        );
        XmStringFree (xmstrings[0]);
        /* Create a "License" button. */
        xmstrings[0] = XmStringCreateSimple ("License");
        n = 0;
        stdarg (XmNforeground, get_pixel (main_window, "black"));
        stdarg (XmNbackground, get_pixel (main_window, "gray"));
        stdarg (XmNfontList, fontlist);
        stdarg (XmNlabelString, xmstrings[0]);
        stdarg (XmNshowAsDefault, 1);
        stdarg (XmNy, 200);
        stdarg (XmNx, 155);
        about_dialog_license_button = XtCreateManagedWidget
        (
                "about_dialog_license_button",
                xmPushButtonWidgetClass,
                about_dialog_drawing_area,
                args,
                n
        );
        XtAddCallback
        (
                about_dialog_license_button,
                XmNactivateCallback, 
                on_about_dialog_license_button_clicked,
                NULL
        );
        XmStringFree (xmstrings[0]);
        /* Create a "Close" button. */
        xmstrings[0] = XmStringCreateSimple ("Close");
        n = 0;
        stdarg (XmNforeground, get_pixel (main_window, "black"));
        stdarg (XmNbackground, get_pixel (main_window, "gray"));
        stdarg (XmNfontList, fontlist);
        stdarg (XmNlabelString, xmstrings[0]);
        stdarg (XmNshowAsDefault, 1);
        stdarg (XmNy, 200);
        stdarg (XmNx, 155);
        about_dialog_close_button = XtCreateManagedWidget
        (
                "about_dialog_close_button",
                xmPushButtonWidgetClass,
                about_dialog_drawing_area,
                args,
                n
        );
        XtAddCallback
        (
                about_dialog_close_button,
                XmNactivateCallback,
                on_about_dialog_close_button_clicked,
                NULL
        );
        XmStringFree (xmstrings[0]);
        /* Create the about dialog text label. */
        xmstrings[0] = create_about_dialog_xmstring ();
        n = 0;
        stdarg (XmNalignment, XmALIGNMENT_BEGINNING);
        stdarg (XmNtraversalOn, False);
        stdarg (XmNmarginHeight, 10);
        stdarg (XmNmarginWidth, 10);
        stdarg (XmNrecomputeSize, True);
        stdarg (XmNforeground, get_pixel (main_window, "black"));
        stdarg (XmNbackground, get_pixel (main_window, "gray"));
        stdarg (XmNlabelString, xmstrings[0]);
        stdarg (XmNfontList, fontlist);
        about_dialog_label = XtCreateManagedWidget
        (
                "about_dialog_label",
                xmLabelWidgetClass,
                about_dialog_frame,
                args,
                n
        );
        XmStringFree (xmstrings[0]);
        /* Realize the about dialog. */
        XtRealizeWidget (about_dialog);
        /* Clean up. */
        XmFontListFree (fontlist);
        return (EXIT_SUCCESS);

}


/*!
 * \brief This puts together the XmString text for display on the
 * "About" dialog.
 * 
 * <b>Parameters:</b> none.\n
 * \n
 * <b>Returns:</b> \c xms.
 */
XmString
create_about_dialog_xmstring (void)
{
        XmString xms;
        XmString nxt;
        XmString lst;

        lst = XmStringCreateLtoR
        (
                "\npcb-lfpw - pcb footprintwizard\n",
                XmSTRING_DEFAULT_CHARSET
        );
        nxt = XmStringCreateLtoR
        (
                "        Version: ",
                XmSTRING_DEFAULT_CHARSET
        );
        xms = XmStringConcat (lst, nxt);
        XmStringFree (lst);
        XmStringFree (nxt);
        nxt = xms;
        lst = XmStringCreateLtoR (VERSION, XmSTRING_DEFAULT_CHARSET);
        xms = XmStringConcat (xms, lst);
        XmStringFree (lst);
        XmStringFree (nxt);
        nxt = xms;
        lst = XmStringCreateLtoR ("\n", XmSTRING_DEFAULT_CHARSET);
        xms = XmStringConcat (xms, lst);
        XmStringFree (lst);
        XmStringFree (nxt);
        nxt = xms;
        lst = XmStringCreateLtoR
        (
                "\npcb-lfpw is a program for the creation of\n",
                XmSTRING_DEFAULT_CHARSET
        );
        xms = XmStringConcat (xms, lst);
        XmStringFree (lst);
        XmStringFree (nxt);
        nxt = xms;
        lst = XmStringCreateLtoR
        (
                "\nfootprint files to be used by the pcb layout\n",
                XmSTRING_DEFAULT_CHARSET
        );
        xms = XmStringConcat (xms, lst);
        XmStringFree (lst);
        XmStringFree (nxt);
        nxt = xms;
        lst = XmStringCreateLtoR
        (
                "\napplication.\n",
                XmSTRING_DEFAULT_CHARSET
        );
        xms = XmStringConcat (xms, lst);
        XmStringFree (lst);
        XmStringFree (nxt);
        nxt = xms;
        lst = XmStringCreateLtoR
        (
                "\nFurther information about pcb-lfpw ",
                XmSTRING_DEFAULT_CHARSET
        );
        xms = XmStringConcat (xms, lst);
        XmStringFree (lst);
        XmStringFree (nxt);
        nxt = xms;
        lst = XmStringCreateLtoR
        (
                "can be found at:\n",
                XmSTRING_DEFAULT_CHARSET
        );
        xms = XmStringConcat (xms, lst);
        XmStringFree (lst);
        XmStringFree (nxt);
        nxt = xms;
        lst = XmStringCreateLtoR
        (
                "\nhttp://www.xs4all.nl/~ljh4timm/pcb-fpw/pcb-fpw.html",
                XmSTRING_DEFAULT_CHARSET
        );
        xms = XmStringConcat (xms, lst);
        XmStringFree (lst);
        XmStringFree (nxt);
        return (xms);
}


/* EOF */
