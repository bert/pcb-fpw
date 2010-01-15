/*!
 * \file to.c
 * \author Copyright (C) 2007, 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Functions for TO (Transistor Outline) footprints.
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

#include "register_functions.c"
#include "to.h"


/*!
 * \brief Create an Element for a TO92 package.
 *
 * \return the created \c element.
 */
ElementTypePtr
to_create_element_to92 ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gdouble dx;
        gint pin_number;
        gchar *pin_pad_name = g_strdup ("");
        FlagType pad_flag;
        ElementTypePtr element;

        if (!element)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("could not create a valid element pointer for a %s package."),
                                footprint_type);
                return (NULL);
        }
        /* Define the center of our universe and guess for a place where to
         * put the element mark */
        element->MarkX = 0;
        element->MarkY = 0;
        /* Determine (extreme) courtyard dimensions based on pin/pad
         * properties */

        /* Determine (extreme) courtyard dimensions based on package
         * properties */
        if ((multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package)) < xmin)
        {
                xmin = (multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package));
        }
        if ((multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package)) > xmax)
        {
                xmax = (multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package));
        }
        if ((multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package)) < ymin)
        {
                ymin = (multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package));
        }
        if ((multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package)) > ymax)
        {
                ymax = (multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package));
        }
        /* If the user input is using even more real-estate then use it */
        if (multiplier * (-courtyard_length / 2.0) < xmin)
        {
                xmin = multiplier * (-courtyard_length / 2.0);
        }
        if (multiplier * (courtyard_length / 2.0) > xmax)
        {
                xmax = multiplier * (courtyard_length / 2.0);
        }
        if (multiplier * (-courtyard_width / 2.0) < ymin)
        {
                ymin = multiplier * (-courtyard_width / 2.0);
        }
        if (multiplier * (courtyard_width / 2.0) > ymax)
        {
                ymax = multiplier * (courtyard_width / 2.0);
        }
        /* Guess for a place where to put the element name */
        element->Name[1].Scale = 100; /* 100 percent */
        element->Name[1].X = 0.0 ; /* already in mil/100 */
        element->Name[1].Y = (ymin - 10000.0); /* already in mil/100 */
        element->Name[1].TextString = footprint_name;
        element->Name[1].Element = element;
        element->Name[1].Direction = EAST;
        element->Name[1].ID = ID++;
        /* Guess for a place where to put the element refdes */
        element->Name[2].Scale = 100; /* 100 percent */
        element->Name[2].X = 0.0 ; /* already in mil/100 */
        element->Name[2].Y = (ymin - 10000.0); /* already in mil/100 */
        element->Name[2].TextString = footprint_refdes;
        element->Name[2].Element = element;
        element->Name[2].Direction = EAST;
        element->Name[2].ID = ID++;
        /* Guess for a place where to put the element value */
        element->Name[3].Scale = 100; /* 100 percent */
        element->Name[3].X = 0.0 ; /* already in mil/100 */
        element->Name[3].Y = (ymin - 10000.0); /* already in mil/100 */
        element->Name[3].TextString = footprint_value;
        element->Name[3].Element = element;
        element->Name[3].Direction = EAST;
        element->Name[3].ID = ID++;
        /* Create pin and/or pad entities */
        if (pad_shapes_type == SQUARE)
        {
                pad_flag.f = SQUARE;
        }
        else
        {
                pad_flag.f = CLEAR;
        }
        create_new_pin
        (
                element,
                (int) (5000), /* x0 coordinate */
                (int) (0), /* y0-coordinate */
                (int) (multiplier * pad_diameter), /* pad width */
                (int) (multiplier * pad_clearance), /* clearance */
                (int) (multiplier * (pad_diameter + pad_solder_mask_clearance)), /* solder mask clearance */
                (int) (multiplier * pin_drill_diameter), /* pin drill diameter */
                "", /* pin name */
                "3", /* pin number */
                pad_flag /* flags */
        );
        create_new_pin
        (
                element,
                (int) (0), /* x0 coordinate */
                (int) (0), /* y0-coordinate */
                (int) (multiplier * pad_diameter), /* pad width */
                (int) (multiplier * pad_clearance), /* clearance */
                (int) (multiplier * (pad_diameter + pad_solder_mask_clearance)), /* solder mask clearance */
                (int) (multiplier * pin_drill_diameter), /* pin drill diameter */
                "", /* pin name */
                "2", /* pin number */
                pad_flag /* flags */
        );
        if (pin1_square || (pad_shapes_type == SQUARE))
        {
                pad_flag.f = SQUARE;
        }
        else
        {
                pad_flag.f = CLEAR;
        }
        create_new_pin
        (
                element,
                -5000, /* x0 coordinate, already in mil/100 */
                0, /* y0-coordinate, already in mil/100 */
                (int) (multiplier * pad_diameter), /* pad width */
                (int) (multiplier * pad_clearance), /* clearance */
                (int) (multiplier * (pad_diameter + pad_solder_mask_clearance)), /* solder mask clearance */
                (int) (multiplier * pin_drill_diameter), /* pin drill diameter */
                "", /* pin name */
                "1", /* pin number */
                pad_flag /* flags */
        );
        /* Create a package body. */
        create_new_line
        (
                element,
                -8600, /* x0 coordinate, already in mil/100 */
                -6000, /* y0-coordinate, already in mil/100 */
                8600, /* x1-coordinate, already in mil/100 */
                -6000, /* y1-coordinate, already in mil/100 */
                (int) (multiplier * silkscreen_line_width) /* line width */
        );
        create_new_arc
        (
                element,
                0, /* x coordinate of center point, already in mil/100 */
                0, /* y coordinate of center point, already in mil/100 */
                10500, /* width, already in mil/100 */
                10500, /* height, already in mil/100 */
                -35, /* start angle */
                250, /* delta angle */
                (int) (multiplier * silkscreen_line_width) /* line width */
        );
        /* Create a pin #1 marker. */
                /* package has marker in package body outline geometry */
        /* Create a courtyard outline. */
        create_new_arc
        (
                element,
                0, /* x coordinate of center point, already in mil/100 */
                0, /* y coordinate of center point, already in mil/100 */
                xmax, /* width, already in mil/100 */
                ymax, /* height, already in mil/100 */
                0, /* start angle */
                360, /* delta angle */
                (int) (multiplier * silkscreen_line_width) /* line width */
        );
        /* Create attributes. */
        if (attributes_in_footprint)
        {
                element = create_attributes_in_element (element);
        }
        /* We are ready creating an element. */
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("created an element for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
        }
        return (element);
}


/*!
 * \brief Create an Element for a TO92S package.
 *
 * \return the created \c element.
 */
ElementTypePtr
to_create_element_to92_staggered ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gdouble dx;
        gint pin_number;
        gchar *pin_pad_name = g_strdup ("");
        FlagType pad_flag;
        ElementTypePtr element;

        if (!element)
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_WARNING,
                                _("could not create a valid element pointer for a %s package."),
                                footprint_type);
                return (NULL);
        }
        /* Define the center of our universe and guess for a place where to
         * put the element mark */
        element->MarkX = 0;
        element->MarkY = 0;
        /* Determine (extreme) courtyard dimensions based on pin/pad
         * properties */

        /* Determine (extreme) courtyard dimensions based on package
         * properties */
        if ((multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package)) < xmin)
        {
                xmin = (multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package));
        }
        if ((multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package)) > xmax)
        {
                xmax = (multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package));
        }
        if ((multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package)) < ymin)
        {
                ymin = (multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package));
        }
        if ((multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package)) > ymax)
        {
                ymax = (multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package));
        }
        /* If the user input is using even more real-estate then use it */
        if (multiplier * (-courtyard_length / 2.0) < xmin)
        {
                xmin = multiplier * (-courtyard_length / 2.0);
        }
        if (multiplier * (courtyard_length / 2.0) > xmax)
        {
                xmax = multiplier * (courtyard_length / 2.0);
        }
        if (multiplier * (-courtyard_width / 2.0) < ymin)
        {
                ymin = multiplier * (-courtyard_width / 2.0);
        }
        if (multiplier * (courtyard_width / 2.0) > ymax)
        {
                ymax = multiplier * (courtyard_width / 2.0);
        }
        /* Guess for a place where to put the element name */
        element->Name[1].Scale = 100; /* 100 percent */
        element->Name[1].X = 0.0 ; /* already in mil/100 */
        element->Name[1].Y = (ymin - 10000.0); /* already in mil/100 */
        element->Name[1].TextString = footprint_name;
        element->Name[1].Element = element;
        element->Name[1].Direction = EAST;
        element->Name[1].ID = ID++;
        /* Guess for a place where to put the element refdes */
        element->Name[2].Scale = 100; /* 100 percent */
        element->Name[2].X = 0.0 ; /* already in mil/100 */
        element->Name[2].Y = (ymin - 10000.0); /* already in mil/100 */
        element->Name[2].TextString = footprint_refdes;
        element->Name[2].Element = element;
        element->Name[2].Direction = EAST;
        element->Name[2].ID = ID++;
        /* Guess for a place where to put the element value */
        element->Name[3].Scale = 100; /* 100 percent */
        element->Name[3].X = 0.0 ; /* already in mil/100 */
        element->Name[3].Y = (ymin - 10000.0); /* already in mil/100 */
        element->Name[3].TextString = footprint_value;
        element->Name[3].Element = element;
        element->Name[3].Direction = EAST;
        element->Name[3].ID = ID++;
        /* Create pin and/or pad entities */
        if (pad_shapes_type == SQUARE)
        {
                pad_flag.f = SQUARE;
        }
        else
        {
                pad_flag.f = CLEAR;
        }
        create_new_pin
        (
                element,
                5000, /* x0 coordinate */
                0, /* y0-coordinate */
                (int) (multiplier * pad_diameter), /* pad width */
                (int) (multiplier * pad_clearance), /* clearance */
                (int) (multiplier * (pad_diameter + pad_solder_mask_clearance)), /* solder mask clearance */
                (int) (multiplier * pin_drill_diameter), /* pin drill diameter */
                "", /* pin name */
                "3", /* pin number */
                pad_flag /* flags */
        );
        create_new_pin
        (
                element,
                0, /* x0 coordinate */
                -5000, /* y0-coordinate */
                (int) (multiplier * pad_diameter), /* pad width */
                (int) (multiplier * pad_clearance), /* clearance */
                (int) (multiplier * (pad_diameter + pad_solder_mask_clearance)), /* solder mask clearance */
                (int) (multiplier * pin_drill_diameter), /* pin drill diameter */
                "", /* pin name */
                "2", /* pin number */
                pad_flag /* flags */
        );
        if (pin1_square || (pad_shapes_type == SQUARE))
        {
                pad_flag.f = SQUARE;
        }
        else
        {
                pad_flag.f = CLEAR;
        }
        create_new_pin
        (
                element,
                -5000, /* x0 coordinate, already in mil/100 */
                0, /* y0-coordinate, already in mil/100 */
                (int) (multiplier * pad_diameter), /* pad width */
                (int) (multiplier * pad_clearance), /* clearance */
                (int) (multiplier * (pad_diameter + pad_solder_mask_clearance)), /* solder mask clearance */
                (int) (multiplier * pin_drill_diameter), /* pin drill diameter */
                "", /* pin name */
                "1", /* pin number */
                pad_flag /* flags */
        );
        /* Create a package body. */
        create_new_line
        (
                element,
                -8600, /* x0 coordinate, already in mil/100 */
                -6000, /* y0-coordinate, already in mil/100 */
                8600, /* x1-coordinate, already in mil/100 */
                -6000, /* y1-coordinate, already in mil/100 */
                (int) (multiplier * silkscreen_line_width) /* line width */
        );
        create_new_arc
        (
                element,
                0, /* x coordinate of center point, already in mil/100 */
                0, /* y coordinate of center point, already in mil/100 */
                10500, /* width, already in mil/100 */
                10500, /* height, already in mil/100 */
                -35, /* start angle */
                250, /* delta angle */
                (int) (multiplier * silkscreen_line_width) /* line width */
        );
        /* Create a pin #1 marker. */
                /* package has marker in package body outline geometry */
        /* Create a courtyard outline. */
        create_new_arc
        (
                element,
                0, /* x coordinate of center point, already in mil/100 */
                0, /* y coordinate of center point, already in mil/100 */
                xmax, /* width, already in mil/100 */
                ymax, /* height, already in mil/100 */
                0, /* start angle */
                360, /* delta angle */
                (int) (multiplier * silkscreen_line_width) /* line width */
        );
        /* Create attributes. */
        if (attributes_in_footprint)
        {
                element = create_attributes_in_element (element);
        }
        /* We are ready creating an element. */
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("created an element for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
        }
        return (element);
}


/*!
 * \brief Create a list of TO packages with pre-defined values.
 *
 * The data in this list can be used in a combobox to select a
 * pre-defined package.
 *
 * \return a list containing all package names of this footprint type
 * known by pcb-fpw.
 */
GList
to_create_packages_list ()
{
        GList *to_packages_list = NULL;
        to_packages_list = g_list_append (to_packages_list, "TO92");
        return (*to_packages_list);
}


/*!
 * \brief Look up default values for TO footprint.
 *
 * Footprint values can be looked up by placing a question mark "?" in front
 * of the footprint name.\n
 * If the footprint name is recognised known values will be loaded and the
 * entries involved in the GUI will be updated accordingly.\n
 * Currently the following footprints are supported:\n
 * - .
 *
 * \return \c EXIT_SUCCESS when default values for a footprint were
 * found, \c EXIT_FAILURE when the footprint name was not found.
 */
int
to_get_default_footprint_values
(
        gchar *footprint_name
                /*!< : a \c NULL terminated footprint name.*/
)
{
        if (!strcmp (footprint_name, "?TO92"))
        {
                number_of_pins = 3;
                package_body_length = 0.0;
                package_body_width = 0.0;
                package_body_height = 0.0;
                package_is_radial = TRUE;
                number_of_columns = 0;
                number_of_rows = 0;
                pitch_x = 0.0;
                pitch_y = 0.0;
                pad_diameter = 1.00; /* approx. 40 mil */
                pin_drill_diameter = 0.72; /* approx. 28 mil */
                pad_length = 0.0;
                pad_width = 0.0;
                pad_shape = g_strdup ("rounded pad");
                pad_shapes_type = ROUND;
                thermal = FALSE;
                thermal_length = 0.0;
                thermal_width = 0.0;
                silkscreen_package_outline = FALSE;
                silkscreen_length = 0.0;
                silkscreen_width = 0.0;
                courtyard_length = 0.0;
                courtyard_width = 0.0;
                count_x = 0;
                count_y = 0;
                footprint_units = g_strdup ("mm");
                g_free (footprint_name);
                footprint_name = g_strdup ("TO92");
                return (EXIT_SUCCESS);
        }
        else
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("default values for footprint %s not found.\n"),
                        footprint_name);
                return (EXIT_FAILURE);
        }
}


/*!
 * \brief Set GUI constraints for the TO package type.
 *
 * This function is only to be compiled for GUI targets.
 *
 * \return \c EXIT_SUCCESS when the function is completed.
 */
#if GUI
int
to_set_gui_constraints
(
        GtkWidget *widget
                /*!< : the caller widget.*/
)
{
        /* Widgets on tab 1 "Footprint" */
        GtkWidget *package_is_radial_checkbutton = lookup_widget (GTK_WIDGET (widget),
                "package_is_radial_checkbutton");
        gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (package_is_radial_checkbutton), FALSE);
        gtk_widget_set_sensitive (package_is_radial_checkbutton, FALSE);

        /* Widgets on tab 2 "Pins/Pads" */
        GtkWidget *number_of_columns_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_columns_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_columns_entry), "3");
        gtk_widget_set_sensitive (number_of_columns_entry, FALSE);
        GtkWidget *number_of_rows_entry = lookup_widget (GTK_WIDGET (widget),
                "number_of_rows_entry");
        gtk_entry_set_text (GTK_ENTRY (number_of_rows_entry), "1");
        gtk_widget_set_sensitive (number_of_rows_entry, FALSE);
        GtkWidget *count_x_entry = lookup_widget (GTK_WIDGET (widget),
                "count_x_entry");
        gtk_entry_set_text (GTK_ENTRY (count_x_entry), "");
        gtk_widget_set_sensitive (count_x_entry, FALSE);
        GtkWidget *count_y_entry = lookup_widget (GTK_WIDGET (widget),
                "count_y_entry");
        gtk_entry_set_text (GTK_ENTRY (count_y_entry), "");
        gtk_widget_set_sensitive (count_y_entry, FALSE);
        GtkWidget *number_1_position_entry = lookup_widget (GTK_WIDGET (widget),
                "number_1_position_entry");
        gtk_combo_box_set_active (GTK_COMBO_BOX (number_1_position_entry), UPPER_LEFT);
        gtk_widget_set_sensitive (number_1_position_entry, FALSE);

        /* Widgets on tab 5 "Heel & Toe goals" */
        gui_constraints_disable_heel_and_toe_goals_tab_widgets (widget);
        return (EXIT_SUCCESS);
}
#endif /* GUI */


/*!
 * \brief Write a footprint for a TO220 transistor package.
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
to_write_footprint_to220 ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gchar *pin_pad_flags = g_strdup ("");

        /* Attempt to open a file with write permission. */
        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not open file for %s footprint: %s."),
                        footprint_type, footprint_filename);
                fclose (fp);
                return (EXIT_FAILURE);
        }
        /* Print a license if requested. */
        if (license_in_footprint)
        {
                write_license ();
        }
        /* Determine (extreme) courtyard dimensions based on pin/pad/
         * package body properties */
        xmin = -20000 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        xmax = 20000 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymin = -79000 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymax = 10000 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        /* Determine (extreme) courtyard dimensions based on package
         * properties */
        if ((multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package)) < xmin)
                xmin = (multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package)) > xmax)
                xmax = (multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package));
        if ((multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package)) < ymin)
                ymin = (multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package)) > ymax)
                ymax = (multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package));
        /* If the user input is using even more real-estate then use it */
        if (multiplier * (-courtyard_length / 2.0) < xmin)
                xmin = multiplier * (-courtyard_length / 2.0);
        if (multiplier * (courtyard_length / 2.0) > xmax)
                xmax = multiplier * (courtyard_length / 2.0);
        if (multiplier * (-courtyard_width / 2.0) < ymin)
                ymin = multiplier * (-courtyard_width / 2.0);
        if (multiplier * (courtyard_width / 2.0) > ymax)
                ymax = multiplier * (courtyard_width / 2.0);
        /* Write element header
         * Guess for a place where to put the refdes text */
        x_text = 0.0 ; /* already in mil/100 */
        y_text = (ymin - 10000.0); /* already in mil/100 */
        write_element_header (x_text, y_text);
        /* Write pin and/or pad entities */
        if (!strcmp (pad_shape, "rectangular pad"))
                pin_pad_flags = g_strdup ("square");
        else
                pin_pad_flags = g_strdup ("");
        write_pin
        (
                1, /* pin number */
                "", /* pin name */
                -10000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                /* Write pin #1 with a square pad */
                (pin1_square) ? "square" : "" /* flags */
        );
        write_pin
        (
                2, /* pin number */
                "", /* pin name */
                0.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        write_pin
        (
                3, /* pin number */
                "", /* pin name */
                10000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        /* Attachment drill hole (PTH). */
        write_pin
        (
                0, /* pin number */
                "", /* pin name */
                10000.0, /* x0 coordinate */
                -67000.0, /* y0-coordinate */
                15000.0, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                15000.0 + (multiplier * pad_solder_mask_clearance), /* solder mask clearance */
                13000.0, /* pin drill diameter */
                "hole" /* flags */
        );
        /* Add a thermal pad if the user requests for it. */
        if (thermal)
        {
                write_pad
                (
                        0, /* pin number */
                        "", /* pin name */
                        0, /* x0 coordinate */
                        -67000 - (multiplier * (thermal_width + (thermal_length / 2))), /* y0-coordinate */
                        0, /* x1 coordinate */
                        -67000 + (multiplier * (thermal_width + (thermal_length / 2))), /* y1-coordinate */
                        multiplier * thermal_length, /* pad width */
                        multiplier * pad_clearance, /* clearance with other copper */
                        multiplier * (thermal_length + (2 * thermal_solder_mask_clearance)), /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
        }
        /* Write package body on the silkscreen */
        if (silkscreen_package_outline)
        {
	        /* Leads. */
                fprintf (fp, "# Write leads on the silkscreen\n");
                write_element_line
                (
                        -10000,
                        (int) (multiplier * (-pad_diameter)),
                        -10000,
                        -18000,
                        (int) multiplier * (2 * silkscreen_line_width)
                );
                write_element_line
                (
                        0,
                        (int) (multiplier * (-pad_diameter)),
                        0,
                        -18000,
                        (int) multiplier * (2 * silkscreen_line_width)
                );
                write_element_line
                (
                        10000,
                        (int) (multiplier * (-pad_diameter)),
                        10000,
                        -18000,
                        (int) multiplier * (2 * silkscreen_line_width)
                );
	        /* Body. */
                fprintf (fp, "# Write a package body on the silkscreen\n");
                write_element_line
                (
                        -20000,
                        -18000,
                        -20000,
                        -55500,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20000,
                        -18000,
                        20000,
                        -55500,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -20000,
                        -55500,
                        20000,
                        -55500,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -20000,
                        -18000,
                        20000,
                        -18000,
                        (int) multiplier * (silkscreen_line_width)
                );
	        /* Cooling tab with notches. */
                fprintf (fp, "# Write a Cooling tab with notches on the silkscreen\n");
                write_element_line
                (
                        -20000,
                        -55500,
                        20000,
                        -55500,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20000,
                        -55500,
                        20000,
                        -68000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20000,
                        -68000,
                        18500,
                        -68000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        18500,
                        -68000,
                        18500,
                        -75000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        18500,
                        -75000,
                        20000,
                        -75000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20000,
                        -75000,
                        20000,
                        -79000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20000,
                        -79000,
                        -20000,
                        -79000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -20000,
                        -79000,
                        -20000,
                        -75000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -20000,
                        -75000,
                        -18500,
                        -75000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -18500,
                        -75000,
                        -18500,
                        -68000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -18500,
                        -68000,
                        -20000,
                        -68000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -20000,
                        -68000,
                        -20000,
                        -55500,
                        (int) multiplier * (silkscreen_line_width)
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                /*! \todo Write a pin #1 marker on the silkscreen ! */
        }
        /* Write a courtyard on the silkscreen */
        if (courtyard)
        {
                fprintf (fp, "# Write a courtyard on the silkscreen\n");
                write_rectangle
                (
                        xmin, /* already in mil/100 */
                        ymin, /* already in mil/100 */
                        xmax, /* already in mil/100 */
                        ymax, /* already in mil/100 */
                        multiplier * courtyard_line_width
                );
        }
        /* Write attributes to the footprint file. */
        if (attributes_in_footprint)
        {
                write_attributes ();
        }
        /* Finishing touch. */
        fprintf (fp, "\n");
        fprintf (fp, ")\n");
        fclose (fp);
        /* We are ready creating a footprint. */
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("wrote a footprint for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a footprint for a TO220S transistor package (with
 * staggered pins).
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
to_write_footprint_to220_staggered ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gchar *pin_pad_flags = g_strdup ("");

        /* Attempt to open a file with write permission. */
        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not open file for %s footprint: %s."),
                        footprint_type, footprint_filename);
                fclose (fp);
                return (EXIT_FAILURE);
        }
        /* Print a license if requested. */
        if (license_in_footprint)
        {
                write_license ();
        }
        /* Determine (extreme) courtyard dimensions based on pin/pad/
         * package body properties */
        xmin = -20000 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        xmax = 20000 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymin = -79000 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymax = 10000 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        /* Determine (extreme) courtyard dimensions based on package
         * properties */
        if ((multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package)) < xmin)
                xmin = (multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package)) > xmax)
                xmax = (multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package));
        if ((multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package)) < ymin)
                ymin = (multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package)) > ymax)
                ymax = (multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package));
        /* If the user input is using even more real-estate then use it */
        if (multiplier * (-courtyard_length / 2.0) < xmin)
                xmin = multiplier * (-courtyard_length / 2.0);
        if (multiplier * (courtyard_length / 2.0) > xmax)
                xmax = multiplier * (courtyard_length / 2.0);
        if (multiplier * (-courtyard_width / 2.0) < ymin)
                ymin = multiplier * (-courtyard_width / 2.0);
        if (multiplier * (courtyard_width / 2.0) > ymax)
                ymax = multiplier * (courtyard_width / 2.0);
        /* Write element header
         * Guess for a place where to put the refdes text */
        x_text = 0.0 ; /* already in mil/100 */
        y_text = (ymin - 10000.0); /* already in mil/100 */
        write_element_header (x_text, y_text);
        /* Write pin and/or pad entities */
        if (!strcmp (pad_shape, "rectangular pad"))
                pin_pad_flags = g_strdup ("square");
        else
                pin_pad_flags = g_strdup ("");
        write_pin
        (
                1, /* pin number */
                "", /* pin name */
                -10000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                /* Write pin #1 with a square pad */
                (pin1_square) ? "square" : "" /* flags */
        );
        write_pin
        (
                2, /* pin number */
                "", /* pin name */
                0.0, /* x0 coordinate */
                10000.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        write_pin
        (
                3, /* pin number */
                "", /* pin name */
                10000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        /* Attachment drill hole (PTH). */
        write_pin
        (
                0, /* pin number */
                "", /* pin name */
                10000.0, /* x0 coordinate */
                -67000.0, /* y0-coordinate */
                15000.0, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                15000.0 + (multiplier * pad_solder_mask_clearance), /* solder mask clearance */
                13000.0, /* pin drill diameter */
                "hole" /* flags */
        );
        /* Add a thermal pad if the user requests for it. */
        if (thermal)
        {
                write_pad
                (
                        0, /* pin number */
                        "", /* pin name */
                        0, /* x0 coordinate */
                        -67000 - (multiplier * (thermal_width + (thermal_length / 2))), /* y0-coordinate */
                        0, /* x1 coordinate */
                        -67000 + (multiplier * (thermal_width + (thermal_length / 2))), /* y1-coordinate */
                        multiplier * thermal_length, /* pad width */
                        multiplier * pad_clearance, /* clearance with other copper */
                        multiplier * (thermal_length + (2 * thermal_solder_mask_clearance)), /* solder mask clearance */
                        pin_pad_flags /* flags */
                );
        }
        /* Write package body on the silkscreen */
        if (silkscreen_package_outline)
        {
	        /* Leads. */
                fprintf (fp, "# Write leads on the silkscreen\n");
                write_element_line
                (
                        -10000,
                        (int) (multiplier * (-pad_diameter)),
                        -10000,
                        -18000,
                        (int) multiplier * (2 * silkscreen_line_width)
                );
                write_element_line
                (
                        0,
                        (int) (multiplier * (-pad_diameter)),
                        0,
                        -8000,
                        (int) multiplier * (2 * silkscreen_line_width)
                );
                write_element_line
                (
                        10000,
                        (int) (multiplier * (-pad_diameter)),
                        10000,
                        -18000,
                        (int) multiplier * (2 * silkscreen_line_width)
                );
	        /* Body. */
                fprintf (fp, "# Write a package body on the silkscreen\n");
                write_element_line
                (
                        -20000,
                        -18000,
                        -20000,
                        -55500,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20000,
                        -18000,
                        20000,
                        -55500,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -20000,
                        -55500,
                        20000,
                        -55500,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -20000,
                        -18000,
                        20000,
                        -18000,
                        (int) multiplier * (silkscreen_line_width)
                );
	        /* Cooling tab with notches. */
                fprintf (fp, "# Write a Cooling tab with notches on the silkscreen\n");
                write_element_line
                (
                        -20000,
                        -55500,
                        20000,
                        -55500,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20000,
                        -55500,
                        20000,
                        -68000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20000,
                        -68000,
                        18500,
                        -68000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        18500,
                        -68000,
                        18500,
                        -75000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        18500,
                        -75000,
                        20000,
                        -75000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20000,
                        -75000,
                        20000,
                        -79000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20000,
                        -79000,
                        -20000,
                        -79000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -20000,
                        -79000,
                        -20000,
                        -75000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -20000,
                        -75000,
                        -18500,
                        -75000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -18500,
                        -75000,
                        -18500,
                        -68000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -18500,
                        -68000,
                        -20000,
                        -68000,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -20000,
                        -68000,
                        -20000,
                        -55500,
                        (int) multiplier * (silkscreen_line_width)
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                /*! \todo Write a pin #1 marker on the silkscreen ! */
        }
        /* Write a courtyard on the silkscreen */
        if (courtyard)
        {
                fprintf (fp, "# Write a courtyard on the silkscreen\n");
                write_rectangle
                (
                        xmin, /* already in mil/100 */
                        ymin, /* already in mil/100 */
                        xmax, /* already in mil/100 */
                        ymax, /* already in mil/100 */
                        multiplier * courtyard_line_width
                );
        }
        /* Write attributes to the footprint file. */
        if (attributes_in_footprint)
        {
                write_attributes ();
        }
        /* Finishing touch. */
        fprintf (fp, "\n");
        fprintf (fp, ")\n");
        fclose (fp);
        /* We are ready creating a footprint. */
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("wrote a footprint for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a footprint for a TO220W transistor package (standing).
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
to_write_footprint_to220_standing ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gchar *pin_pad_flags = g_strdup ("");

        /* Attempt to open a file with write permission. */
        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not open file for %s footprint: %s."),
                        footprint_type, footprint_filename);
                fclose (fp);
                return (EXIT_FAILURE);
        }
        /* Print a license if requested. */
        if (license_in_footprint)
        {
                write_license ();
        }
        /* Determine (extreme) courtyard dimensions based on pin/pad/
         * package body properties */
        xmin = -20750 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        xmax = 20750 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymin = -12600 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymax = 5900 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        /* Determine (extreme) courtyard dimensions based on package
         * properties */
        if ((multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package)) < xmin)
                xmin = (multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package)) > xmax)
                xmax = (multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package));
        if ((multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package)) < ymin)
                ymin = (multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package)) > ymax)
                ymax = (multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package));
        /* If the user input is using even more real-estate then use it */
        if (multiplier * (-courtyard_length / 2.0) < xmin)
                xmin = multiplier * (-courtyard_length / 2.0);
        if (multiplier * (courtyard_length / 2.0) > xmax)
                xmax = multiplier * (courtyard_length / 2.0);
        if (multiplier * (-courtyard_width / 2.0) < ymin)
                ymin = multiplier * (-courtyard_width / 2.0);
        if (multiplier * (courtyard_width / 2.0) > ymax)
                ymax = multiplier * (courtyard_width / 2.0);
        /* Write element header
         * Guess for a place where to put the refdes text */
        x_text = 0.0 ; /* already in mil/100 */
        y_text = (ymin - 10000.0); /* already in mil/100 */
        write_element_header (x_text, y_text);
        /* Write pin and/or pad entities */
        if (!strcmp (pad_shape, "rectangular pad"))
                pin_pad_flags = g_strdup ("square");
        else
                pin_pad_flags = g_strdup ("");
        write_pin
        (
                1, /* pin number */
                "", /* pin name */
                -10000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                /* Write pin #1 with a square pad */
                (pin1_square) ? "square" : "" /* flags */
        );
        write_pin
        (
                2, /* pin number */
                "", /* pin name */
                0.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        write_pin
        (
                3, /* pin number */
                "", /* pin name */
                10000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        /* Write package body on the silkscreen */
        if (silkscreen_package_outline)
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
                write_element_line
                (
                        -20750,
                        -12600,
                        -20750,
                        5900,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -20750,
                        5900,
                        20750,
                        5900,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20750,
                        5900,
                        20750,
                        -12600,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20750,
                        -12600,
                        -20750,
                        -12600,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -18750,
                        -10000,
                        18750,
                        -10000,
                        5200
                );
                write_element_line
                (
                        -20750,
                        -7600,
                        20750,
                        -7600,
                        (int) multiplier * (silkscreen_line_width)
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                /*! \todo Write a pin #1 marker on the silkscreen ! */
        }
        /* Write a courtyard on the silkscreen */
        if (courtyard)
        {
                fprintf (fp, "# Write a courtyard on the silkscreen\n");
                write_rectangle
                (
                        xmin, /* already in mil/100 */
                        ymin, /* already in mil/100 */
                        xmax, /* already in mil/100 */
                        ymax, /* already in mil/100 */
                        multiplier * courtyard_line_width
                );
        }
        /* Write attributes to the footprint file. */
        if (attributes_in_footprint)
        {
                write_attributes ();
        }
        /* Finishing touch. */
        fprintf (fp, "\n");
        fprintf (fp, ")\n");
        fclose (fp);
        /* We are ready creating a footprint. */
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("wrote a footprint for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a footprint for a TO220SW transistor package (standing
 * with staggered pins).
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
to_write_footprint_to220_standing_staggered ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gchar *pin_pad_flags = g_strdup ("");

        /* Attempt to open a file with write permission. */
        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not open file for %s footprint: %s."),
                        footprint_type, footprint_filename);
                fclose (fp);
                return (EXIT_FAILURE);
        }
        /* Print a license if requested. */
        if (license_in_footprint)
        {
                write_license ();
        }
        /* Determine (extreme) courtyard dimensions based on pin/pad/
         * package body properties */
        xmin = -30750 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        xmax = 20750 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymin = -12600 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymax = 5900 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        /* Determine (extreme) courtyard dimensions based on package
         * properties */
        if ((multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package)) < xmin)
                xmin = (multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package)) > xmax)
                xmax = (multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package));
        if ((multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package)) < ymin)
                ymin = (multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package)) > ymax)
                ymax = (multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package));
        /* If the user input is using even more real-estate then use it */
        if (multiplier * (-courtyard_length / 2.0) < xmin)
                xmin = multiplier * (-courtyard_length / 2.0);
        if (multiplier * (courtyard_length / 2.0) > xmax)
                xmax = multiplier * (courtyard_length / 2.0);
        if (multiplier * (-courtyard_width / 2.0) < ymin)
                ymin = multiplier * (-courtyard_width / 2.0);
        if (multiplier * (courtyard_width / 2.0) > ymax)
                ymax = multiplier * (courtyard_width / 2.0);
        /* Write element header
         * Guess for a place where to put the refdes text */
        x_text = 0.0 ; /* already in mil/100 */
        y_text = (ymin - 10000.0); /* already in mil/100 */
        write_element_header (x_text, y_text);
        /* Write pin and/or pad entities */
        if (!strcmp (pad_shape, "rectangular pad"))
                pin_pad_flags = g_strdup ("square");
        else
                pin_pad_flags = g_strdup ("");
        write_pin
        (
                1, /* pin number */
                "", /* pin name */
                -10000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                /* Write pin #1 with a square pad */
                (pin1_square) ? "square" : "" /* flags */
        );
        write_pin
        (
                2, /* pin number */
                "", /* pin name */
                0.0, /* x0 coordinate */
                -10000.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        write_pin
        (
                3, /* pin number */
                "", /* pin name */
                10000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        /* Write package body on the silkscreen */
        if (silkscreen_package_outline)
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
                write_element_line
                (
                        -30750,
                        -12600,
                        -30750,
                        5900,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -30750,
                        5900,
                        20750,
                        5900,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20750,
                        5900,
                        20750,
                        -12600,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        20750,
                        -12600,
                        -30750,
                        -12600,
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_line
                (
                        -18750,
                        -10000,
                        18750,
                        -10000,
                        5200
                );
                write_element_line
                (
                        -30750,
                        -7600,
                        20750,
                        -7600,
                        (int) multiplier * (silkscreen_line_width)
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                /*! \todo Write a pin #1 marker on the silkscreen ! */
        }
        /* Write a courtyard on the silkscreen */
        if (courtyard)
        {
                fprintf (fp, "# Write a courtyard on the silkscreen\n");
                write_rectangle
                (
                        xmin, /* already in mil/100 */
                        ymin, /* already in mil/100 */
                        xmax, /* already in mil/100 */
                        ymax, /* already in mil/100 */
                        multiplier * courtyard_line_width
                );
        }
        /* Write attributes to the footprint file. */
        if (attributes_in_footprint)
        {
                write_attributes ();
        }
        /* Finishing touch. */
        fprintf (fp, "\n");
        fprintf (fp, ")\n");
        fclose (fp);
        /* We are ready creating a footprint. */
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("wrote a footprint for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a footprint for a TO92 transistor package.
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
to_write_footprint_to92 ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gchar *pin_pad_flags = g_strdup ("");

        /* Attempt to open a file with write permission. */
        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not open file for %s footprint: %s."),
                        footprint_type, footprint_filename);
                fclose (fp);
                return (EXIT_FAILURE);
        }
        /* Print a license if requested. */
        if (license_in_footprint)
        {
                write_license ();
        }
        /* Determine (extreme) courtyard dimensions based on pin/pad
         * properties */
        xmin = -10500 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        xmax = 10500 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymin = -8600 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymax = 10500 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        /* Determine (extreme) courtyard dimensions based on package
         * properties */
        if ((multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package)) < xmin)
                xmin = (multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package)) > xmax)
                xmax = (multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package));
        if ((multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package)) < ymin)
                ymin = (multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package)) > ymax)
                ymax = (multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package));
        /* If the user input is using even more real-estate then use it */
        if (multiplier * (-courtyard_length / 2.0) < xmin)
                xmin = multiplier * (-courtyard_length / 2.0);
        if (multiplier * (courtyard_length / 2.0) > xmax)
                xmax = multiplier * (courtyard_length / 2.0);
        if (multiplier * (-courtyard_width / 2.0) < ymin)
                ymin = multiplier * (-courtyard_width / 2.0);
        if (multiplier * (courtyard_width / 2.0) > ymax)
                ymax = multiplier * (courtyard_width / 2.0);
        /* Write element header
         * Guess for a place where to put the refdes text */
        x_text = 0.0 ; /* already in mil/100 */
        y_text = (ymin - 10000.0); /* already in mil/100 */
        write_element_header (x_text, y_text);
        /* Write pin and/or pad entities */
        if (!strcmp (pad_shape, "rectangular pad"))
                pin_pad_flags = g_strdup ("square");
        else
                pin_pad_flags = g_strdup ("");
        write_pin
        (
                1, /* pin number */
                "", /* pin name */
                -5000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                /* Write pin #1 with a square pad */
                (pin1_square) ? "square" : "" /* flags */
        );
        write_pin
        (
                2, /* pin number */
                "", /* pin name */
                0.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        write_pin
        (
                3, /* pin number */
                "", /* pin name */
                5000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        /* Write package body on the silkscreen */
        if (silkscreen_package_outline)
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
                write_element_line
                (
                        -8600, /* x0-coordinate */
                        -6000, /* y0-coordinate */
                        8600, /* x1-coordinate */
                        -6000, /* y1-coordinate */
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_arc
                (
                        0, /* x-coordinate */
                        0, /* y-coordinate */
                        10500, /* width */
                        10500, /*height */
                        -35, /* start angke */
                        250, /* delta angle */
                        multiplier * silkscreen_line_width /* line width */
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                /*! \todo Write a pin #1 marker on the silkscreen ! */
        }
        /* Write a courtyard on the silkscreen */
        if (courtyard)
        {
                fprintf (fp, "# Write a courtyard on the silkscreen\n");
                if (package_is_radial)
                {
                        write_element_arc
                        (
                                0.0,
                                0.0,
                                xmax, /* already in mil/100 */
                                ymax, /* already in mil/100 */
                                0,
                                360,
                                multiplier * courtyard_line_width
                        );
                }
                else
                {
                        write_rectangle
                        (
                                xmin, /* already in mil/100 */
                                ymin, /* already in mil/100 */
                                xmax, /* already in mil/100 */
                                ymax, /* already in mil/100 */
                                multiplier * courtyard_line_width
                        );
                }
        }
        /* Write attributes to the footprint file. */
        if (attributes_in_footprint)
        {
                write_attributes ();
        }
        /* Finishing touch. */
        fprintf (fp, "\n");
        fprintf (fp, ")\n");
        fclose (fp);
        /* We are ready creating a footprint. */
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("wrote a footprint for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a footprint for a TO92S transistor package (with
 * staggered pins).
 *
 * \return \c EXIT_FAILURE when errors were encountered,
 * \c EXIT_SUCCESS when OK.
 */
int
to_write_footprint_to92_staggered ()
{
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gchar *pin_pad_flags = g_strdup ("");

        /* Attempt to open a file with write permission. */
        fp = fopen (footprint_filename, "w");
        if (!fp)
        {
                g_log ("", G_LOG_LEVEL_WARNING,
                        _("could not open file for %s footprint: %s."),
                        footprint_type, footprint_filename);
                fclose (fp);
                return (EXIT_FAILURE);
        }
        /* Print a license if requested. */
        if (license_in_footprint)
        {
                write_license ();
        }
        /* Determine (extreme) courtyard dimensions based on pin/pad
         * properties */
        xmin = -10500 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        xmax = 10500 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymin = -8600 - (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        ymax = 10500 + (multiplier * courtyard_clearance_with_package); /* in mil/100 */
        /* Determine (extreme) courtyard dimensions based on package
         * properties */
        if ((multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package)) < xmin)
                xmin = (multiplier * ((-package_body_length / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package)) > xmax)
                xmax = (multiplier * ((package_body_length / 2.0) + courtyard_clearance_with_package));
        if ((multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package)) < ymin)
                ymin = (multiplier * ((-package_body_width / 2.0) - courtyard_clearance_with_package));
        if ((multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package)) > ymax)
                ymax = (multiplier * ((package_body_width / 2.0) + courtyard_clearance_with_package));
        /* If the user input is using even more real-estate then use it */
        if (multiplier * (-courtyard_length / 2.0) < xmin)
                xmin = multiplier * (-courtyard_length / 2.0);
        if (multiplier * (courtyard_length / 2.0) > xmax)
                xmax = multiplier * (courtyard_length / 2.0);
        if (multiplier * (-courtyard_width / 2.0) < ymin)
                ymin = multiplier * (-courtyard_width / 2.0);
        if (multiplier * (courtyard_width / 2.0) > ymax)
                ymax = multiplier * (courtyard_width / 2.0);
        /* Write element header
         * Guess for a place where to put the refdes text */
        x_text = 0.0 ; /* already in mil/100 */
        y_text = (ymin - 10000.0); /* already in mil/100 */
        write_element_header (x_text, y_text);
        /* Write pin and/or pad entities */
        if (!strcmp (pad_shape, "rectangular pad"))
                pin_pad_flags = g_strdup ("square");
        else
                pin_pad_flags = g_strdup ("");
        write_pin
        (
                1, /* pin number */
                "", /* pin name */
                -5000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                /* Write pin #1 with a square pad */
                (pin1_square) ? "square" : "" /* flags */
        );
        write_pin
        (
                2, /* pin number */
                "", /* pin name */
                0.0, /* x0 coordinate */
                -5000.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        write_pin
        (
                3, /* pin number */
                "", /* pin name */
                5000.0, /* x0 coordinate */
                0.0, /* y0-coordinate */
                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                multiplier * pad_clearance, /* clearance */
                multiplier * (pad_diameter + pad_solder_mask_clearance), /* solder mask clearance */
                multiplier * pin_drill_diameter, /* pin drill diameter */
                pin_pad_flags /* flags */
        );
        /* Write package body on the silkscreen */
        if (silkscreen_package_outline)
        {
                fprintf (fp, "# Write a package body on the silkscreen\n");
                write_element_line
                (
                        -8600, /* x0-coordinate */
                        -6000, /* y0-coordinate */
                        8600, /* x1-coordinate */
                        -6000, /* y1-coordinate */
                        (int) multiplier * (silkscreen_line_width)
                );
                write_element_arc
                (
                        0, /* x-coordinate */
                        0, /* y-coordinate */
                        10500, /* width */
                        10500, /*height */
                        -35, /* start angke */
                        250, /* delta angle */
                        multiplier * silkscreen_line_width /* line width */
                );
        }
        /* Write a pin #1 marker on the silkscreen */
        if (silkscreen_indicate_1)
        {
                /*! \todo Write a pin #1 marker on the silkscreen ! */
        }
        /* Write a courtyard on the silkscreen */
        if (courtyard)
        {
                fprintf (fp, "# Write a courtyard on the silkscreen\n");
                if (package_is_radial)
                {
                        write_element_arc
                        (
                                0.0,
                                0.0,
                                xmax, /* already in mil/100 */
                                ymax, /* already in mil/100 */
                                0,
                                360,
                                multiplier * courtyard_line_width
                        );
                }
                else
                {
                        write_rectangle
                        (
                                xmin, /* already in mil/100 */
                                ymin, /* already in mil/100 */
                                xmax, /* already in mil/100 */
                                ymax, /* already in mil/100 */
                                multiplier * courtyard_line_width
                        );
                }
        }
        /* Write attributes to the footprint file. */
        if (attributes_in_footprint)
        {
                write_attributes ();
        }
        /* Finishing touch. */
        fprintf (fp, "\n");
        fprintf (fp, ")\n");
        fclose (fp);
        /* We are ready creating a footprint. */
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                        _("wrote a footprint for a %s package: %s."),
                        footprint_type,
                        footprint_filename);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief A list containing all TO related functions.
 */
static fpw_function_t
to_function_list[] =
{
#if GUI
        {
                "Set GUI constraints",
                to_set_gui_constraints,
                "Set GUI constraints for a TO package",
                NULL
        },
#endif /* GUI */
        {
                "Create element",
                to_create_element_to92,
                "Create an element for a TO92 package",
                NULL
        },
        {
                "Packages list",
                to_create_packages_list,
                "Create a list of known TO packages",
                NULL
        },
        {
                "Default Element Values",
                to_get_default_footprint_values,
                "Get default values for a INDC SMT package",
                NULL
        },
        {
                "Write footprint",
                to_write_footprint_to220,
                "Write a footprint for a TO220 package",
                NULL
        },
        {
                "Write footprint",
                to_write_footprint_to220_staggered,
                "Write a footprint for a TO220S package",
                NULL
        },
        {
                "Write footprint",
                to_write_footprint_to220_standing,
                "Write a footprint for a TO220W package",
                NULL
        },
        {
                "Write footprint",
                to_write_footprint_to220_standing_staggered,
                "Write a footprint for a TO220SW package",
                NULL
        },
        {
                "Write footprint",
                to_write_footprint_to92,
                "Write a footprint for a TO92 package",
                NULL
        }
};


/*!
 * \brief A list containing all TO related functions.
 */
REGISTER_FUNCTIONS (to_function_list)


/*!
 * \brief Initialise by registering all TO related functions.
 */
void
to_init ()
{
        register_to_function_list ();
}


/* EOF */
