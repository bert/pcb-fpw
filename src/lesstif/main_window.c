/*!
 * \file src/lesstif/main_window.c
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Main window of the pcb footprintwizard (pcb-lfpw).
 *
 * pcb-lfpw (Lesstif FootPrintWizard) is a program for the creation of footprint
 * files to be used by with the pcb layout application
 * (see http://pcb.sourgeforge.net) for the placement of parts in a pcb
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
#include <stdlib.h>
#include <stdarg.h>

#include "xincludes.h"

#include "util.h"
#include "pcb_lfpw.h"
#include "main_window.h"


/*!
 * \brief Change the main window title.
 *
 * <b>Parameters:</b> \c *widget is the caller widget.\n
 * \n
 * <b>Parameters:</b> \c *main_window_title is the string containing
 * the new title.\n
 * \n
 * <b>Returns:</b> none.
 */
int
change_main_window_title (Widget *widget, char *filename)
{
        char title[256];
        char *p = NULL;

        program_name = XtNewString ("pcb-lfpw");
        fpw_filename = XtNewString ("no_name.fpw");
        /* strip any path info from the filename */
        if (filename)
        {
                p = strrchr (filename, '/');
                if (p)
                {
                        p++;
                }
                else
                {
                        p = filename;
                }
        }
        sprintf
        (
                title,
                "pcb-lfpw FootPrint Wizard%s%s",
                (p ? ": " : ""),
                (p ? p : ""));
        /* title in main window bar */
        n = 0;
        stdarg (XmNtitle, title);
        stdarg (XmNiconName, "gFootprintWizard.xpm");
        XtSetValues (main_window, args, n);
        return (EXIT_SUCCESS);
}


/*!
 * \brief Create the main window.
 *
 * \return .
 */
int
create_main_window (int argc, char **argv)
{
        char title[124];
        XmString xmstrings[10];
        XmFontList fontlist;
        Widget vbox;
        Widget hbox;
        Widget notebook;
        Widget footprint_tab_table;
        Widget author_frame;
        Widget author_frame_alignment;
        Widget author_table;
        Widget footprint_author_label;
        Widget footprint_dist_license_label;
        Widget footprint_author_entry;
        Widget footprint_dist_license_entry;
        Widget footprint_use_license_entry;
        Widget footprint_use_license_label;
        Widget footprint_status_label;
        Widget footprint_status_entry;
        Widget author_frame_label;
        Widget footprint_frame;
        Widget footprint_frame_alignment;
        Widget footprint_table;
        Widget footprint_units_label;
        Widget footprint_units_entry;
        Widget footprint_name_entry;
        Widget footprint_type_entry;
        Widget footprint_type_label;
        Widget footprint_name_label;
        Widget package_body_height_entry;
        Widget package_body_height_label;
        Widget pacakge_body_width_label;
        Widget package_body_length_label;
        Widget footprint_value_label;
        Widget package_body_width_entry;
        Widget package_body_length_entry;
        Widget footprint_value_entry;
        Widget footprint_refdes_label;
        Widget footprint_refdes_entry;
        Widget add_license_checkbutton;
        Widget package_is_radial_checkbutton;
        Widget add_attribs_checkbutton;
        Widget footprint_frame_label;
        Widget footprint_tab_label;
        Widget pins_pads_table;
        Widget pads_frame;
        Widget pads_alignment;
        Widget pads_table;
        Widget pad_solder_mask_clearance_label;
        Widget pad_solder_mask_clearance_entry;
        Widget pad_clearance_label;
        Widget pad_width_label;
        Widget pad_length_label;
        Widget pad_clearance_entry;
        Widget pad_width_entry;
        Widget pad_length_entry;
        Widget pad_shape_label;
        Widget pad_shape_entry;
        Widget pads_label;
        Widget pins_frame;
        Widget pins_alignment;
        Widget pins_table;
        Widget pad_diameter_entry;
        Widget pin_drill_diameter_label;
        Widget pin_pad_diameter_label;
        Widget pin_square_checkbutton;
        Widget pin_drill_diameter_entry;
        Widget pins_label;
        Widget pins_pads_pattern_frame;
        Widget pins_pads_pattern_alignment;
        Widget pins_pads_pattern_table;
        Widget total_pins_and_pads_label;
        Widget pitch_x_label;
        Widget pitch_y_label;
        Widget number_total_pins_entry;
        Widget pitch_x_entry;
        Widget pitch_y_entry;
        Widget label1;
        Widget label2;
        Widget count_x_entry;
        Widget count_y_entry;
        Widget number_1_position_label;
        Widget number_1_position_entry;
        Widget number_of_columns_label;
        Widget number_of_columns_entry;
        Widget number_of_rows_label;
        Widget number_of_rows_entry;
        Widget pin_pad_exceptions_entry;
        Widget pin_pad_exceptions_button;
        Widget pins_pads_pattern_label;
        Widget pins_pads_tab_tab_label;
        Widget silkscreen_table;
        Widget courtyard_frame;
        Widget courtyard_alignment;
        Widget courtyard_table;
        Widget courtyard_checkbutton;
        Widget courtyard_width_label;
        Widget courtyard_length_label;
        Widget courtyard_length_entry;
        Widget courtyard_width_entry;
        Widget courtyard_line_width_label;
        Widget courtyard_line_width_entry;
        Widget courtyard_clearance_with_package_label;
        Widget courtyard_clearance_with_package_entry;
        Widget courtyard_label;
        Widget package_frame;
        Widget package_alignment;
        Widget package_table;
        Widget silkscreen_package_outline_checkbutton;
        Widget silkscreen_indicate_1_checkbutton;
        Widget silkscreen_line_width_label;
        Widget silkscreen_line_width_entry;
        Widget package_label;
        Widget silkscreen_tab_label;
        Widget thermal_table;
        Widget thermal_pad_frame;
        Widget thermal_pad_alignment;
        Widget thermal_pad_table;
        Widget thermal_checkbutton;
        Widget thermal_pad_length_label;
        Widget thermal_pad_width_label;
        Widget thermal_width_entry;
        Widget thermal_length_entry;
        Widget thermal_nopaste_checkbutton;
        Widget thermal_pad_solder_mask_clearance_label;
        Widget thermal_pad_clearance_label;
        Widget thermal_solder_mask_clearance_entry;
        Widget thermal_clearance_entry;
        Widget thermal_pad_label;
        Widget fiducials_frame;
        Widget fiducials_alignment;
        Widget fiducials_table;
        Widget fiducial_pad_diameter_label;
        Widget fiducial_pad_diameter_entry;
        Widget fiducial_checkbutton;
        Widget fiducial_solder_mask_clearance_label;
        Widget fiducial_pad_solder_mask_clearance_entry;
        Widget fiducial_pad_clearance_label;
        Widget fiducial_pad_clearance_entry;
        Widget fiducials_label;
        Widget thermal_pad_tab_label;
        Widget heel_and_toe_goals_vbox;
        Widget top_to_bottom_frame;
        Widget top_to_bottom_alignment;
        Widget top_to_bottom_table;
        Widget G1_radiobutton_group;
        Widget G1_radiobutton;
        Widget C1_radiobutton;
        Widget Z1_radiobutton;
        Widget G1_entry;
        Widget C1_entry;
        Widget Z1_entry;
        Widget top_to_bottom_label;
        Widget left_to_right_frame;
        Widget left_to_right_alignment;
        Widget left_to_right_table;
        Widget G2_radiobutton_group;
        Widget G2_radiobutton;
        Widget C2_radiobutton;
        Widget Z2_radiobutton;
        Widget G2_entry;
        Widget C2_entry;
        Widget Z2_entry;
        Widget left_to_right_label;
        Widget heel_and_toe_goals_tab_label;
        Widget hbuttonbox0;
        Widget refresh_button;
        Widget dimensions_button;
        Widget alignment4;
        Widget hbox4;
        Widget image4;
        Widget label6;
        Widget preview_button;
        Widget alignment1;
        Widget hbox1;
        Widget image1;
        Widget label3;
        Widget clear_button;
        Widget hbuttonbox1;
        Widget close_button;
        Widget footprint_button;
        Widget alignment3;
        Widget hbox3;
        Widget image3;
        Widget label5;
        Widget open_button;
        Widget save_button;
        Widget statusbar;
        Widget tooltips;

        main_window = XtVaAppInitialize
        (
                &lfpw_app_context,
                "pcb-lfpw",
                NULL,
                0,
                &argc,
                argv,
                NULL
        );
        /* Create a single fontlist for all widgets to get a consistent
         * look for the UI. */
        fontlist = get_fontlist
        (
                main_window,
                "-adobe-helvetica-bold-r-normal--14-140-75-75-p-82-iso8859-1"
        );


        /* Create the "Top to Bottom" frame. */
        xmstrings[0] = XmStringCreateSimple ("Top to Bottom");
        n = 0;
        stdarg (XmNfontList, fontlist);
        stdarg (XmNmarginWidth, FRAME_MARGIN_WIDTH);
        stdarg (XmNmarginHeight,FRAME_MARGIN_HEIGHT );
        stdarg (XmNshadowType, XmSHADOW_IN);
        stdarg (XmNchildType, XmFRAME_TITLE_CHILD);
        stdarg (XmNchildHorizontalAlignment, XmALIGNMENT_BEGINNING);
        stdarg (XmNtitle, xmstrings[0]);
        top_to_bottom_frame = XmCreateFrame
        (
                main_window,
                "top_to_bottom_frame",
                args,
                n
        );
        /* Create the "Top to Bottom" label. */
        xmstrings[0] = XmStringCreateSimple ("Top to Bottom");
        n = 0;
        stdarg (XmNfontList, fontlist);
        stdarg (XmNlabelType, XmSTRING);
        stdarg (XmNalignment, XmALIGNMENT_BEGINNING);
        stdarg (XmNlabelString, xmstrings[0]);
        top_to_bottom_label = XmCreateLabel
        (
                top_to_bottom_frame,
                "top_to_bottom_label",
                args,
                n
        );
        /* Create the "Top to Bottom" table (actually a XmForm). */
        n = 0; 
        stdarg (XmNtopOffset, WIDGET_TOP_OFFSET);
        stdarg (XmNleftOffset, WIDGET_LEFT_OFFSET);
        stdarg (XmNrightOffset, WIDGET_TOP_OFFSET);
        stdarg (XmNbottomOffset, WIDGET_LEFT_OFFSET);
        
        top_to_bottom_table = XmCreateForm
        (
                top_to_bottom_frame,
                "top_to_bottom_table",
                args,
                n
        );
        /* Create the "G1" radiobuttongroup. */
        n = 0; 
        stdarg (XmNpacking, XmPACK_COLUMN);
        stdarg (XmNtopAttachment, XmATTACH_FORM);
        stdarg (XmNleftAttachment, XmATTACH_FORM);
        stdarg (XmNbottomAttachment, XmATTACH_FORM);
        stdarg (XmNtopOffset, WIDGET_TOP_OFFSET);
        stdarg (XmNleftOffset, WIDGET_LEFT_OFFSET);
        G1_radiobutton_group = (Widget) XmCreateRadioBox
        (
                top_to_bottom_table,
                "G1_radiobutton_group",
                args,
                n
        );
        XtManageChild(G1_radiobutton_group);
        /* Create the "C1" radiobutton. */
        xmstrings[0] = XmStringCreateSimple ("Center-Center (C1)");
        n = 0;
        stdarg (XmNfontList, fontlist);
        stdarg (XmNlabelString, xmstrings[0]);
        stdarg (XmNindicatorOn, TRUE);
        stdarg (XmNindicatorType, XmONE_OF_MANY);
        stdarg (XmNset, FALSE);
        C1_radiobutton = XtCreateManagedWidget
        (
                "C1_radiobutton",
                xmToggleButtonWidgetClass,
                G1_radiobutton_group,
                args,
                n
        );
       XtAddCallback
        (
                C1_radiobutton,
                XmCArmCallback, 
                on_C1_radiobutton_toggled,
                NULL
        );
         XmStringFree (xmstrings[0]);
        /* Create the "G1" radiobutton. */
        xmstrings[0] = XmStringCreateSimple ("Inner-Inner (G1)");
        n = 0;
        stdarg (XmNfontList, fontlist);
        stdarg (XmNlabelString, xmstrings[0]);
        stdarg (XmNindicatorOn, TRUE);
        stdarg (XmNindicatorType, XmONE_OF_MANY);
        stdarg (XmNset, TRUE);
        G1_radiobutton = XtCreateManagedWidget
        (
                "G1_radiobutton",
                xmToggleButtonWidgetClass,
                G1_radiobutton_group,
                args,
                n
        );
        XtAddCallback
        (
                G1_radiobutton,
                XmCArmCallback, 
                on_G1_radiobutton_toggled,
                NULL
        );
        XmStringFree (xmstrings[0]);
        /* Create the "Z1" radiobutton. */
        xmstrings[0] = XmStringCreateSimple ("Outer-Outer (Z1)");
        n = 0;
        stdarg (XmNfontList, fontlist);
        stdarg (XmNlabelString, xmstrings[0]);
        stdarg (XmNindicatorOn, TRUE);
        stdarg (XmNindicatorType, XmONE_OF_MANY);
        stdarg (XmNset, FALSE);
        Z1_radiobutton = XtCreateManagedWidget
        (
                "Z1_radiobutton",
                xmToggleButtonWidgetClass,
                G1_radiobutton_group,
                args,
                n
        );
        XtAddCallback
        (
                Z1_radiobutton,
                XmCArmCallback, 
                on_Z1_radiobutton_toggled,
                NULL
        );
        XmStringFree (xmstrings[0]);
        /* Create the "C1" entry. */
        n = 0;
        stdarg (XmNfontList, fontlist);
        stdarg (XmNtopAttachment, XmATTACH_WIDGET);
        stdarg (XmNtopWidget, top_to_bottom_table);
        stdarg (XmNleftAttachment, XmATTACH_WIDGET);
        stdarg (XmNleftWidget, G1_radiobutton_group);
        stdarg (XmNrightAttachment, XmATTACH_WIDGET);
        stdarg (XmNrightWidget, top_to_bottom_table);
        stdarg (XmNbottomAttachment, XmATTACH_WIDGET);
        stdarg (XmNbottomWidget, top_to_bottom_table);
        stdarg (XmNtopOffset, WIDGET_TOP_OFFSET);
        stdarg (XmNleftOffset, WIDGET_LEFT_OFFSET);
        stdarg (XmNeditable, TRUE);
        stdarg (XmNeditMode, XmSINGLE_LINE_EDIT);
        stdarg (XmNmaxLength, ENTRY_DOUBLE_MAX_LENGTH);
        stdarg (XmNmarginHeight, ENTRY_MARGIN_HEIGHT);
        stdarg (XmNmarginWidth, ENTRY_MARGIN_WIDTH);
        C1_entry = XmCreateTextField
        (
                main_window,
                "C1_entry",
                args,
                n
        );
        /* Create the "G1" entry. */
        n = 0;
        stdarg (XmNfontList, fontlist);
        stdarg (XmNtopAttachment, XmATTACH_WIDGET);
        stdarg (XmNtopWidget, C1_entry);
        stdarg (XmNleftAttachment, XmATTACH_WIDGET);
        stdarg (XmNleftWidget, G1_radiobutton_group);
        stdarg (XmNtopOffset, WIDGET_TOP_OFFSET);
        stdarg (XmNleftOffset, WIDGET_LEFT_OFFSET);
        G1_entry = XmCreateTextField
        (
                main_window,
                "G1_entry",
                args,
                n
        );
        /* Create the "Z1" entry. */
        n = 0;
        stdarg (XmNfontList, fontlist);
        stdarg (XmNtopAttachment, XmATTACH_WIDGET);
        stdarg (XmNtopWidget, G1_entry);
        stdarg (XmNleftAttachment, XmATTACH_WIDGET);
        stdarg (XmNleftWidget, G1_radiobutton_group);
        stdarg (XmNtopOffset, WIDGET_TOP_OFFSET);
        stdarg (XmNleftOffset, WIDGET_LEFT_OFFSET);
        Z1_entry = XmCreateTextField
        (
                main_window,
                "Z1_entry",
                args,
                n
        );



        XtRealizeWidget (main_window);
        /* Clean up. */
        XmFontListFree (fontlist);
        return (EXIT_SUCCESS);
}


/*!
 * \brief The "top to bottom pads/pins center-center distance (C1)"
 * entry is changed.
 *
 * Actions: \n
 * <ul>
 * <li>get the chars from the entry.
 * <li>convert the chars to a double and store in the \c c1 variable
 * (global).
 * </ul>
 * \n
 * <b>Returns:</b> none.
 */
void
on_C1_entry_changed
(
        Widget w,
        XtPointer client_data,
        XtPointer call_data
)
{
}


/*!
 * \brief The "top to bottom pads/pins center-center distance (C1)"
 * radiobutton is clicked.
 *
 * Actions: \n
 * <ul>
 * <li>set the inner-inner (C1) entry to sensitive.
 * <li>set the center-center (G1) entry to insensitive.
 * <li>set the outer-outer (Z1) entry to insensitive.
 * </ul>
 * \n
 * <b>Returns:</b> none.
 */
void
on_C1_radiobutton_toggled
(
        Widget w,
                /*!< \c w is the caller widget.\n */
        XtPointer client_data,
                /*!< \c *client_data is the ...\n */
        XtPointer call_data
                /*!< \c *call_data is the ...\n */
)
{
}


/*!
 * \brief The top to bottom pads/pins inner-inner distance (G1)
 * radiobutton is clicked.
 *
 * Actions: \n
 * <ul>
 * <li>set the inner-inner (G1) entry to sensitive.
 * <li>set the center-center (C1) entry to insensitive.
 * <li>set the outer-outer (Z1) entry to insensitive.
 * </ul>
 * \n
 * <b>Returns:</b> none.
 */
void
on_G1_radiobutton_toggled
(
        Widget w,
                /*!< \c w is the caller widget.\n */
        XtPointer client_data,
                /*!< \c *client_data is the ...\n */
        XtPointer call_data
                /*!< \c *call_data is the ...\n */
)
{
}


/*!
 * \brief The top to bottom pads/pins outer-outer (Z1) radiobutton
 * is clicked.
 *
 * Actions: \n
 * <ul>
 * <li>set the outer-outer (Z1) entry to sensitive.
 * <li>set the center-center (C1) entry to insensitive.
 * <li>set the inner-inner (G1) entry to insensitive.
 * </ul>
 * \n
 * <b>Returns:</b> none.
 */
void
on_Z1_radiobutton_toggled
(
        Widget w,
                /*!< \c w is the caller widget.\n */
        XtPointer client_data,
                /*!< \c *client_data is the ...\n */
        XtPointer call_data
                /*!< \c *call_data is the ...\n */
)
{
}


/*!
 * \brief The "Close" button of the "Main Window" dialog is clicked.
 *
 * Actions: \n
 * <ul>
 * <li>close the pcb-lfpw application main window.
 * </ul>
 * \n
 * <b>Returns:</b> none.
 */
void
on_close_button_clicked
(
        Widget w,
                /*!< \c w is the caller widget.\n */
        XtPointer client_data,
                /*!< \c *client_data is the ...\n */
        XtPointer call_data
                /*!< \c *call_data is the ...\n */
)
{
        XtUnmanageChild (w);
}


/*!
 * \brief Show the "main window".
 *
 * <b>Returns:</b> none.
 */
void
show_main_window (int argc, char **argv)
{
        if (!main_window)
        {
                create_main_window (argc, argv);
        }
        XtManageChild (main_window);
}


/* EOF */
