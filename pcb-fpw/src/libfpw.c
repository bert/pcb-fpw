/*!
 * \file libfpw.c
 * \version 0.0.2
 * \author Copyright (C) 2007 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief libfpw contains helper functions for both fpw (CLI) and
 * pcb-gfpw (GUI) versions of the pcb FootPrintWizard.
 *
 * fpw (FootPrintWizard) is a program for the creation of footprint files
 * to be used by the pcb layout application (see http://pcb.sourgeforge.net)
 * for the placement of parts in a pcb layout.\n\n
 * The functions in libfpw are called by the CLI version of the
 * FootPrintWizard (fpw) as well as the GUI version (pcb-gfpw).\n
 */


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdlib.h>

#define FPW_VERSION "0.0.1"

/* Some through hole package types */
enum packages
{
        BGA, /*!< Ball Gate Array package. */
        CAPC, /*!< Capacitor, Chip package. */
        CAPM, /*!< Capacitor, Molded, Non-polarized package. */
        CAPMP, /*!< Capacitor, Molded, Polarized package. */
        DIOM, /*!< Diode, Molded package. */
        DIP, /*!< Dual Inline Package. */
        DO, /*!< Diode Outline package. */
        INDC, /*!< Inductor, Chip pacakge. */
        PGA, /*!< Pin Gate Array package. */
        PLCC, /*!< Plastic Leadless Chip Carrier package. */
        QFN, /*!< Quad Flat No-leads package. */
        QFP, /*!< Quad Flat Package. */
        RES, /*!< Resistor TH technology package. */
        RESC, /*!< Resistor, Chip package. */
        SIP, /*!< Single Inline Package. */
        SO, /*!< Small Outline package. */
        TO, /*!< Transistor Outline package. */
        TO92, /*!< Transistor Outline package. */
        TO220, /*!< Transistor Outline package. */
        NUMBER_OF_PACKAGES /*!< Number of package types. */
};

typedef enum packages package_t;

/* Some locations for pin #1 orientation */
/*   2 -- 5 -- 8  */
/*   |    |    |  */
/*   1 -- 4 -- 7  */
/*   |    |    |  */
/*   0 -- 3 -- 6  */
enum locations
{
        LOWER_LEFT, /*!< Package has the lower left pin as pin #1. */
        MIDDLE_LEFT, /*!< Package has the middle left pin as pin #1. */
        UPPER_LEFT, /*!< Package has the upper left pin as pin #1. */
        LOWER_MIDDLE, /*!< Package has the lower middle pin as pin #1. */
        MIDDLE_MIDDLE, /*!< Package has the middle middle pin as pin #1. */
        UPPER_MIDDLE, /*!< Package has the upper middle pin as pin #1. */
        LOWER_RIGHT, /*!< Package has the lower right pin as pin #1. */
        MIDDLE_RIGHT, /*!< Package has the middle right pin as pin #1. */
        UPPER_RIGHT, /*!< Package has the upper right pin as pin #1. */
        NUMBER_OF_LOCATIONS /*!< Number of location types. */
};

typedef enum locations location_t;

/* Thin lines are not printed on silkscreen (in the real world) */
#define THIN_DRAW 1 /*!< Draw with thin lines. */

/* Pin or pad types / Object flag values */
#define PIN 0x0001
        /*!< If set, this object is a pin.\n
         * This flag is for internal use only. */
#define VIA 0x0002
        /*!< Likewise, for vias. */
#define HOLE 0x0008
        /*!< For pins and vias, this flag means that the pin or via is a hole
         * without a copper annulus. */
#define PININPOLY 0x0010
        /*!< For pins and pads, this flag is used internally to indicate that
         * the pin or pad overlaps a polygon on some layer. */
#define SHOWNAME 0x0020
        /*!< For elements, when set the names of pins are shown. */
#define ONSOLDER 0x0080
        /*!< For elements and pads, indicates that they are on the solder
         * side. */
#define SQUARE 0x0100
        /*!< For pins and pads, indicates a square (vs round) pin/pad. */
#define WARN 0x0200
        /*!< For pins, vias, and pads, set to indicate a warning. */
#define OCTAGON 0x0800
        /*!< Draw pins and vias as octagons. */
#define LOCK 0x2000
        /*!< Set for locked objects. */
#define EDGE2 0x4000
        /*!< For pads, indicates that the second point is closer to the
         * edge.\n
         * For pins, indicates that the pin is closer to a horizontal edge
         * and thus pinout text should be vertical. */
#define MARKER 0x8000
        /*!< Marker used internally to avoid revisiting an object. */
#define NOPASTE 0x10000
        /*!< For pads, set to prevent a solderpaste stencil opening for the
         * pad.\n
         * Primarily used for pads used as fiducials. */

gchar *fpw_filename;
        /*!< Filename of footprintwizard file. */
gchar *fpw_suffix = "fpw";
        /*!< Suffix of footprintwizard file. */
gchar *footprint_filename = NULL;
        /*!< Filename of footprint file. */
gchar *fp_suffix = "fp";
        /*!< Suffix of footprint file. */
gchar *footprint_name = NULL;
        /*!< Name of the footprint. */
gchar *footprint_type = NULL;
        /*!< Type of the footprint. */
package_t package_type;
        /*!< Type of the package. */
gchar *footprint_units = NULL;
        /*!< Units for the footprint dimensions. */
gdouble multiplier;
        /*!< Multiplier to convert to mils/100. */
gchar *footprint_value;
        /*!< Value of the package. */

gdouble package_body_length;
        /*!< Length dimension of the package body. */
gdouble package_body_width;
        /*!< Width dimension of the package body. */
gdouble package_body_height;
        /*!< Height dimension of the package body. */
gboolean package_is_radial;
        /*!< Package has a radial body. */

gchar *footprint_author;
        /*!< Author of the footprint. */
gchar *footprint_dist_license;
        /*!< Distribution license of the footprint. */
gchar *footprint_use_license;
        /*!< Usage license of the footprint. */
gchar *footprint_status;
        /*!< Status of the footprint. */

gint number_of_pins;
        /*!< Number of pads/pins. */
gint number_of_columns;
        /*!< Number of columns. */
gint number_of_rows;
        /*!< Number of rows. */
gchar *pin_1_position = NULL;
        /*!< Position of number 1 pin. */
location_t pin1_location;
        /*!< Location of number 1 pin. */
gdouble pitch_x;
        /*!< Pitch in X-direction. */
gdouble pitch_y;
        /*!< Pitch in Y-direction. */
gdouble pin_drill_diameter;
        /*!< Diameter of pin hole. */
gdouble pad_diameter;
        /*!< Outer diameter of pin pad (annulus). */
gdouble pad_length;
        /*!< Length of pad (parallel to Element X-axis). */
gdouble pad_width;
        /*!< Width of pad (perpendicular to Element X-axis). */
gchar *pad_shape = NULL;
        /*!< Shape of pads/pins. */
gint pin_pad_type;
        /*!< Type of pads/pins. */
gboolean pin1_square;
        /*!< Pin #1 is square. */
gchar *pin_pad_flags = NULL;
        /*!< Flags of pins/pads. */
gdouble pad_solder_mask_clearance;
        /*!< Solder mask clearance of a pin/pad. */
gdouble pad_clearance;
        /*!< Clearance of a pin/pad. */

gboolean silkscreen_package_outline;
        /*!< Draw the package body outline on the silkscreen. */
gboolean silkscreen_indicate_1;
        /*!< Indicate the position of number 1 */
gdouble silkscreen_length;
        /*!< Silkscreen length (X-direction). */
gdouble silkscreen_width;
        /*!< Silkscreen width (Y-direction). */
gdouble silkscreen_line_width;
        /*!< Silkscreen line width. */

gboolean courtyard;
        /*!< Draw courtyard. */
gdouble courtyard_length;
        /*!< Courtyard length (X-direction). */
gdouble courtyard_width;
        /*!< Courtyard width (Y-direction). */
gdouble courtyard_line_width;
        /*!< Courtyard line width. */
gdouble courtyard_clearance_with_package;
        /*!< Courtyard clearance with package outline */

gboolean thermal;
        /*!< Draw thermal pad(s). */
gboolean thermal_nopaste;
        /*!< Thermal pad has no paste. */
gdouble thermal_length;
        /*!< Length of thermal pad. */
gdouble thermal_width;
        /*!< Width of thermal pad. */
gdouble thermal_solder_mask_clearance;
        /*!< Solder mask clearance of thermal pad. */
gdouble thermal_clearance;
        /*!< Clearance of a thermal pad. */

gdouble c1;
        /*!< Top to bottom pads center-center distance. */
gdouble g1;
        /*!< Top to bottom pads inner-inner distance. */
gdouble z1;
        /*!< Top to bottom pads outer-outer distance. */
gdouble c2;
        /*!< Left to right pads center-center distance. */
gdouble g2;
        /*!< Left to right pads inner-inner distance. */
gdouble z2;
        /*!< Left to right pads outer-outer distance. */

gchar *dummy = NULL;
        /*!< Every now and then the village-idot is needed ;-) */

/*!
 * \brief Read a footprintwizard file into the global variables.
 *
 */
int
read_footprintwizard_file()
{
        FILE *fp;
        /* Get global variables from footprintwizard file with .fpw suffix */
        if (fp = g_fopen (fpw_filename, "r"))
        {
                fscanf (fp, "%s\n", footprint_filename);
                fscanf (fp, "%s\n", dummy); /* do not (re)use this value ! */
                fscanf (fp, "%s\n", footprint_type);
                fscanf (fp, "%s\n", footprint_units);
                fscanf (fp, "%s\n", pin_1_position);
                fscanf (fp, "%s\n", pad_shape);
                fscanf (fp, "%d\n", number_of_pins);
                fscanf (fp, "%d\n", number_of_columns);
                fscanf (fp, "%d\n", number_of_rows);
                fscanf (fp, "%f\n", pad_length);
                fscanf (fp, "%f\n", pad_width);
                fscanf (fp, "%f\n", pad_diameter);
                fscanf (fp, "%f\n", pin_drill_diameter);
                fscanf (fp, "%f\n", pitch_x);
                fscanf (fp, "%f\n", pitch_y);
                fscanf (fp, "%f\n", pad_solder_mask_clearance);
                fscanf (fp, "%f\n", silkscreen_line_width);
                fscanf (fp, "%f\n", courtyard_length);
                fscanf (fp, "%f\n", courtyard_width);
                fscanf (fp, "%f\n", courtyard_line_width);
                fscanf (fp, "%d\n", thermal);
                fscanf (fp, "%f\n", thermal_length);
                fscanf (fp, "%f\n", thermal_width);
                fscanf (fp, "%f\n", thermal_solder_mask_clearance);
                fclose (fp);
        }
}


/*!
 * \brief Write attributes based on the global variables.
 *
 */
int
write_attributes
(
        FILE *fp /*!< file pointer */
)
{
        /* Attributes in the form "Attribute("name" "value")" */
        fprintf (fp, "\tAttribute(\"author\" \"%s\")\n", footprint_author);
        fprintf (fp, "\tAttribute(\"dist-license\" \"%s\")\n", footprint_dist_license);
        fprintf (fp, "\tAttribute(\"use-license\" \"%s\")\n", footprint_use_license);
        fprintf (fp, "\tAttribute(\"status\" \"%s\")\n", footprint_status);
        fprintf (fp, "\tAttribute(\"package body length\" \"%d\")\n", package_body_length);
        fprintf (fp, "\tAttribute(\"package body width\" \"%d\")\n", package_body_width);
        fprintf (fp, "\tAttribute(\"package height\" \"%d\")\n", package_body_height);
        fprintf (fp, "\n");
        fprintf (fp, ")\n");
}


/*!
 * \brief Write an element arc.
 *
 * This function is here to avoid the exhaustive changes of boiler plate code
 * when the file format of pcb footprint changes.
 */
int
write_element_arc
(
        FILE *fp, /*!< file pointer. */
        gdouble x, /*!< X-coordinate of center. */
        gdouble y, /*!< Y-coordinate of center. */
        gdouble width, /*!< Width from center to edge. */
        gdouble height, /*!< Height from center to edge. */
        gdouble start_angle, /*!< The angle of the start of the arc in degrees.\n
                              * 0 = negative X-axis, 90 = positive Y-axis. */
        gdouble delta_angle, /*!< The angle of sweep in degrees.\n
                              * positive = CCW, negative = CW. */
        gdouble line_width /*!< The width of the silk line which forms the arc. */
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
}


/*!
 * \brief Write an element header based on the global variables.
 *
 */
int
write_element_header
(
        FILE *fp, /*!< file pointer */
        gdouble x_text, /*!< X-coordinate of text */
        gdouble y_text /*!< y-coordinate of text */
)
{
        /* Write header to file */
        fprintf (fp, "Element[\"\" \"%s\" \"?\" \"%s\" 0 0 %d %d 0 100 \"\"]\n(\n",
                footprint_name,
                footprint_value,
                (int) (x_text * multiplier),
                (int) (y_text * multiplier)
                );
}


/*!
 * \brief Write an element line.
 *
 * This function is here to avoid the exhaustive changes of boiler plate code
 * when the file format of pcb footprint changes.
 */
int
write_element_line
(
        FILE *fp, /*!< file pointer. */
        gdouble x0, /*!< X-coordinate of the starting point of the line.\n
                     * These are relative to the Elements mark point for
                     * new element formats, or absolute for older formats. */
        gdouble y0, /*!< Y-coordinate of the starting point of the line.\n
                     * These are relative to the Elements mark point for
                     * new element formats, or absolute for older formats. */
        gdouble x1, /*!< X-coordinate of the ending point of the line.\n
                     * These are relative to the Elements mark point for
                     * new element formats, or absolute for older formats. */
        gdouble y1, /*!< Y-coordinate of the ending point of the line.\n
                     * These are relative to the Elements mark point for
                     * new element formats, or absolute for older formats. */
        gdouble line_width /*!< The width of the silk for this line. */
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
}


/*!
 * \brief Write a pad for any given footprint.
 *
 * This function is here to avoid the exhaustive changes of boiler plate code
 * when the file format of pcb footprint changes.
 */
int
write_pad
(
        FILE *fp, /*!< file pointer */
        gint pad_number, /*!< pad number */
        gchar pad_name, /*!< pad name */
        gdouble x0, /*!< x0 coordinate */
        gdouble y0, /*!< y0-coordinate */
        gdouble x1, /*!< x1 coordinate */
        gdouble y1, /*!< y1-coordinate */
        gdouble width, /*!< width of the pad */
        gdouble clearance, /*!< clearance */
        gdouble pad_solder_mask_clearance, /*!< solder mask clearance */
        gchar flags /*!< flags */
)
{
        fprintf (fp,
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
}


/*!
 * \brief Write a pin for any given footprint.
 *
 * This function is here to avoid the exhaustive changes of boiler plate code
 * when the file format of pcb footprint changes.
 */
int
write_pin
(
        FILE *fp, /*!< file pointer */
        gint pin_number, /*!< pin number */
        gchar pin_name, /*!< pin name */
        gdouble x0, /*!< x0 coordinate */
        gdouble y0, /*!< y0-coordinate */
        gdouble width, /*!< width of the annulus ring (pad) */
        gdouble clearance, /*!< clearance */
        gdouble pad_solder_mask_clearance, /*!< solder mask clearance */
        gdouble drill, /*!< pin drill diameter */
        gchar flags /*!< flags */
)
{
        fprintf (fp,
                "\tPad[%d %d %d %d %d %d %d \"%s\" \"%d\" \"%s\"]\n",
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
}

/*!
 * \brief Write a rectangle for any given footprint.
 *
 * Write a rectangle for any given footprint.
 * If line_width is 0.0 no rectangle is drawn.
 * If line_width is < 0.0 a rectangle with a linewidth of 1/100 of
 * a mil is drawn (#define THIN_DRAW 1).
 */
int
write_rectangle
(
        FILE *fp, /*!< file pointer */
        gdouble xmin, /*!< minimum x-coordinate of rectangle. */
        gdouble ymin, /*!< minimum y-coordinate of rectangle. */
        gdouble xmax, /*!< maximum x-coordinate of rectangle. */
        gdouble ymax, /*!< maximum y-coordinate of rectangle. */
        gdouble line_width /*!< courtyard line width */
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
}


/*!
 * \brief Write a DIP footprint.
 */
int
write_footprint_dip ()
{
        FILE *fp = NULL;
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;
        gint pin_number;
        gint i;

        if (fp = g_fopen (footprint_filename, "w"))
        {
                /* Determine (extreme) courtyard dimensions */
                xmin = multiplier * ((-pitch_x / 2) - (pad_diameter / 2) - pad_solder_mask_clearance);
                xmax = multiplier * (pitch_x / 2 + pad_diameter / 2 + pad_solder_mask_clearance);
                ymin = multiplier * ((-number_of_pins / 4) * pitch_y - (pad_diameter / 2) - pad_solder_mask_clearance);
                ymax = multiplier * ((number_of_pins / 4) * pitch_y + (pad_diameter / 2) + pad_solder_mask_clearance);
                /* If the user input is using more real-estate then use it */
                if (multiplier * (-courtyard_length / 2) < xmin)
                {
                        xmin = multiplier * (-courtyard_length / 2);
                }
                if (multiplier * (courtyard_length / 2) > xmax)
                {
                        xmax = multiplier * (courtyard_length / 2);
                }
                if (multiplier * (-courtyard_width / 2) < ymin)
                {
                        ymin = multiplier * (-courtyard_width / 2);
                }
                if (multiplier * (courtyard_width / 2) > ymax)
                {
                        ymax = multiplier * (courtyard_width / 2);
                }
                /* Write element header */
                x_text = 0.0 ;
                y_text = (ymin / 2) - 150.0;
                write_element_header (fp, x_text, y_text);
                /* Write encapsulated element entities */
                pin_number = 1;
                for (i = 0; i > (number_of_rows - 1); i++)
                {
                        pin_number = 1 + i;
                        write_pin
                        (
                                fp,
                                pin_number, /* pin number */
                                "", /* pin name */
                                multiplier * - pitch_x / 2, /* x0 coordinate */
                                multiplier * ((-number_of_rows / 2 + i) * pitch_y), /* y0-coordinate */
                                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * pad_solder_mask_clearance, /* solder mask clearance */
                                multiplier * pin_drill_diameter, /* pin drill diameter */
                                /* Write pin #1 with a square pad if checked */
                                (pin1_square && (pin_number == 1)) ? "square" : pin_pad_flags /* flags */
                        );
                        if (pad_shape == "rounded pad, elongated")
                        {
                                write_pad
                                (
                                        fp, /* file pointer */
                                        pin_number, /* pad number = pin_number*/
                                        "", /* pad name */
                                        multiplier * (-pitch_x + pad_length - pad_width) / 2, /* x0 coordinate */
                                        multiplier * ((-number_of_rows / 2 + i) * pitch_y), /* y0-coordinate */
                                        multiplier * (-pitch_x - pad_length + pad_width) / 2, /* x1 coordinate */
                                        multiplier * ((-number_of_rows / 2 + i) * pitch_y), /* y0-coordinate */
                                        multiplier * pad_width, /* width of the pad */
                                        multiplier * pad_clearance, /* clearance */
                                        multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                        /* Write pad #1 with a square pad if checked */
                                        (pin1_square && (pin_number == 1)) ? "square" : pin_pad_flags /* flags */
                                );
                        }
                        pin_number = (number_of_rows * number_of_columns) - i;
                        write_pin
                        (
                                fp,
                                pin_number, /* pin number */
                                "", /* pin name */
                                multiplier * pitch_x / 2, /* x0 coordinate */
                                multiplier * ((-number_of_rows / 2 + i) * pitch_y), /* y0-coordinate */
                                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * pad_solder_mask_clearance, /* solder mask clearance */
                                multiplier * pin_drill_diameter, /* pin drill diameter */
                                pin_pad_flags /* flags */
                        );
                        if (pad_shape == "rounded pad, elongated")
                        {
                                write_pad
                                (
                                        fp, /* file pointer */
                                        pin_number, /* pad number = pin_number*/
                                        "", /* pad name */
                                        multiplier * (pitch_x - pad_length + pad_width) / 2, /* x0 coordinate */
                                        multiplier * ((-number_of_rows / 2 + i) * pitch_y), /* y0-coordinate */
                                        multiplier * (pitch_x + pad_length - pad_width) / 2, /* x1 coordinate */
                                        multiplier * ((-number_of_rows / 2 + i) * pitch_y), /* y0-coordinate */
                                        multiplier * pad_width, /* width of the pad */
                                        multiplier * pad_clearance, /* clearance */
                                        multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                        /* Write pad #1 with a square pad if checked */
                                        (pin1_square && (pin_number == 1)) ? "square" : pin_pad_flags /* flags */
                                );
                        }
                        pin_number++;
                }
                /* Write a package body on the silkscreen */
                if (silkscreen_package_outline)
                {
                        write_rectangle
                        (
                                fp,
                                multiplier * (((-pitch_x + pad_diameter + silkscreen_line_width) / 2) + pad_solder_mask_clearance) ,
                                multiplier * ymin,
                                multiplier * (((pitch_x - pad_diameter - silkscreen_line_width) / 2) - pad_solder_mask_clearance) ,
                                multiplier * ymax,
                                multiplier * silkscreen_line_width
                        );
                }
                /* Write a pin #1 marker */
                if (silkscreen_indicate_1)
                {
                        write_element_arc
                        (
                                fp,
                                multiplier * (xmin / 4),
                                multiplier * ymin,
                                multiplier * (xmax / 4),
                                multiplier * ymin,
                                0,
                                180,
                                multiplier * courtyard_line_width
                        );
                }
                /* Write a courtyard */
                write_rectangle
                (
                        fp,
                        multiplier * xmin,
                        multiplier * ymin,
                        multiplier * xmax,
                        multiplier * ymax,
                        multiplier * courtyard_line_width
                );
                /* Write attributes */
                write_attributes (fp);
                fclose (fp);
        }
        else
        {
                fprintf (stderr, "Error: could not open file for DIP footprint: %s.\n", footprint_filename);
                return (EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a SMT footprint with two pads for a chip package.
 */
int
write_footprint_smt ()
{
        FILE *fp;
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;

        if (fp = g_fopen (footprint_filename, "w"))
        {
                /* Determine (extreme) courtyard dimensions */
                xmin = multiplier * ((-pitch_x / 2) - (pad_length / 2) - pad_solder_mask_clearance);
                xmax = multiplier * (pitch_x / 2 + pad_length / 2 + pad_solder_mask_clearance);
                ymin = multiplier * ((-pad_width / 2) - pad_solder_mask_clearance);
                ymax = multiplier * (pad_width / 2 + pad_solder_mask_clearance);
                /* If the user input is using more real-estate then use it */
                if (multiplier * (-courtyard_length / 2) < xmin)
                {
                        xmin = multiplier * (-courtyard_length / 2);
                }
                if (multiplier * (courtyard_length / 2) > xmax)
                {
                        xmax = multiplier * (courtyard_length / 2);
                }
                if (multiplier * (-courtyard_width / 2) < ymin)
                {
                        ymin = multiplier * (-courtyard_width / 2);
                }
                if (multiplier * (courtyard_width / 2) > ymax)
                {
                        ymax = multiplier * (courtyard_width / 2);
                }
                /* Write element header */
                x_text = 0.0 ;
                y_text = (ymin / 2) - 150.0;
                write_element_header (fp, x_text, y_text);
                /* Write encapsulated element entities */
                if (pad_length > pad_width) /* Write pads parallel to x-axis */
                {
                        fprintf (stderr, "Pads are drawn parallel on X-axis.\n");
                        /* Pad #1 */
                        write_pad
                        (
                                fp, /* file pointer */
                                1, /* pad number */
                                "", /* pad name */
                                multiplier * -1 * (pitch_x + pad_length - pad_width) / 2, /* x0 coordinate */
                                0, /* y0-coordinate */
                                multiplier * (-pitch_x + pad_length - pad_width) / 2, /* x1 coordinate */
                                0, /* y1-coordinate */
                                multiplier * pad_width, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                /* Write pin #1 with a square pad if checked */
                                (pin1_square) ? "square" : pin_pad_flags /* flags */
                        );
                        /* Pad #2 */
                        write_pad
                        (
                                fp, /* file pointer */
                                2, /* pad number */
                                "", /* pad name */
                                multiplier * -1 * (-pitch_x + pad_length - pad_width) / 2, /* x0 coordinate */
                                0, /* y0-coordinate */
                                multiplier * (pitch_x + pad_length - pad_width) / 2, /* x1 coordinate */
                                0, /* y1-coordinate */
                                multiplier * pad_width, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                }
                else /* write pads perpendiclar to x-axis */
                {
                        fprintf (stderr, "Pads are drawn perpendicular to X-axis.\n");
                        /* Pad #1 */
                        write_pad
                        (
                                fp, /* file pointer */
                                1, /* pad number */
                                "", /* pad name */
                                multiplier * (-pitch_x / 2), /* x0-coordinate */
                                multiplier * (pad_width - pad_length) / 2, /* y0-coordinate */
                                multiplier * (-pitch_x / 2), /* x0-coordinate */
                                multiplier * (-pad_width + pad_length) / 2, /* y1-coordinate */
                                multiplier * pad_length, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_length + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                /* Write pin #1 with a square pad if checked */
                                (pin1_square) ? "square" : pin_pad_flags /* flags */
                        );
                        /* Pad #2 */
                        write_pad
                        (
                                fp, /* file pointer */
                                1, /* pad number */
                                "", /* pad name */
                                multiplier * (pitch_x / 2), /* x1-coordinate */
                                multiplier * (pad_width - pad_length) / 2, /* y0-coordinate */
                                multiplier * (pitch_x / 2), /* x1-coordinate */
                                multiplier * (-pad_width + pad_length) / 2, /* y1-coordinate */
                                multiplier * pad_length, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_length + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                }
                /* Write a package body on the silkscreen */
                if (silkscreen_package_outline)
                {
                        write_element_line
                        (
                                fp,
                                multiplier * (((-pitch_x + pad_length) / 2) + pad_solder_mask_clearance + silkscreen_line_width),
                                multiplier * (package_body_width / 2),
                                multiplier * (((pitch_x - pad_length) / 2) - pad_solder_mask_clearance - silkscreen_line_width),
                                multiplier * (package_body_width / 2),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                fp,
                                multiplier * (((-pitch_x + pad_length) / 2) + pad_solder_mask_clearance + silkscreen_line_width),
                                multiplier * (-package_body_width / 2),
                                multiplier * (((pitch_x - pad_length) / 2) - pad_solder_mask_clearance - silkscreen_line_width),
                                multiplier * (-package_body_width / 2),
                                multiplier * silkscreen_line_width
                        );
                }
                /* Write a pin #1 marker */
                if (silkscreen_indicate_1)
                {
                        /* package has no pin/pad #1 indications */
                }
                /* Write a courtyard */
                if (courtyard)
                {
                        write_rectangle
                        (
                                fp,
                                multiplier * (-courtyard_length / 2),
                                multiplier * (-courtyard_width / 2),
                                multiplier * (courtyard_length / 2),
                                multiplier * (courtyard_width / 2),
                                multiplier * courtyard_line_width
                        );
                }
                /* Write attributes */
                write_attributes (fp);
                fclose (fp);
        }
        else
        {
                fprintf (stderr, "Error: could not open file for SMT footprint: %s.\n", footprint_filename);
                return (EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a SMT footprint with two pads for a molded chip package.
 */
int
write_footprint_smt_molded ()
{
        FILE *fp;
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;

        if (fp = g_fopen (footprint_filename, "w"))
        {
                /* Determine (extreme) courtyard dimensions */
                xmin = multiplier * ((-pitch_x / 2) - (pad_length / 2) - pad_solder_mask_clearance);
                xmax = multiplier * (pitch_x / 2 + pad_length / 2 + pad_solder_mask_clearance);
                ymin = multiplier * ((-pad_width / 2) - pad_solder_mask_clearance);
                ymax = multiplier * (pad_width / 2 + pad_solder_mask_clearance);
                /* If the user input is using more real-estate then use it */
                if (multiplier * (-courtyard_length / 2) < xmin)
                {
                        xmin = multiplier * (-courtyard_length / 2);
                }
                if (multiplier * (courtyard_length / 2) > xmax)
                {
                        xmax = multiplier * (courtyard_length / 2);
                }
                if (multiplier * (-courtyard_width / 2) < ymin)
                {
                        ymin = multiplier * (-courtyard_width / 2);
                }
                if (multiplier * (courtyard_width / 2) > ymax)
                {
                        ymax = multiplier * (courtyard_width / 2);
                }
                /* Write element header */
                x_text = 0.0 ;
                y_text = (ymin / 2) - 150.0;
                write_element_header (fp, x_text, y_text);
                /* Write encapsulated element entities to file*/
                if (pad_length > pad_width) /* Write pads parallel to x-axis */
                {
                        fprintf (stderr, "Pads are drawn parallel on X-axis.\n");
                        /* Pad #1 */
                        write_pad
                        (
                                fp, /* file pointer */
                                1, /* pad number */
                                "", /* pad name */
                                multiplier * -1 * (pitch_x + pad_length - pad_width) / 2, /* x0 coordinate */
                                0, /* y0-coordinate */
                                multiplier * (-pitch_x + pad_length - pad_width) / 2, /* x1 coordinate */
                                0, /* y1-coordinate */
                                multiplier * pad_width, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                /* Write pin #1 with a square pad if checked */
                                (pin1_square) ? "square" : pin_pad_flags /* flags */
                        );
                        /* Pad #2 */
                        write_pad
                        (
                                fp, /* file pointer */
                                2, /* pad number */
                                "", /* pad name */
                                multiplier * -1 * (-pitch_x + pad_length - pad_width) / 2, /* x0 coordinate */
                                0, /* y0-coordinate */
                                multiplier * (pitch_x + pad_length - pad_width) / 2, /* x1 coordinate */
                                0, /* y1-coordinate */
                                multiplier * pad_width, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_width + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                }
                else /* write pads perpendiclar to x-axis */
                {
                        fprintf (stderr, "Pads are drawn perpendicular to X-axis.\n");
                        /* Pad #1 */
                        write_pad
                        (
                                fp, /* file pointer */
                                1, /* pad number */
                                "", /* pad name */
                                multiplier * (-pitch_x / 2), /* x0-coordinate */
                                multiplier * (pad_width - pad_length) / 2, /* y0-coordinate */
                                multiplier * (-pitch_x / 2), /* x0-coordinate */
                                multiplier * (-pad_width + pad_length) / 2, /* y1-coordinate */
                                multiplier * pad_length, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_length + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                /* Write pin #1 with a square pad if checked */
                                (pin1_square) ? "square" : pin_pad_flags /* flags */
                        );
                        /* Pad #2 */
                        write_pad
                        (
                                fp, /* file pointer */
                                1, /* pad number */
                                "", /* pad name */
                                multiplier * (pitch_x / 2), /* x1-coordinate */
                                multiplier * (pad_width - pad_length) / 2, /* y0-coordinate */
                                multiplier * (pitch_x / 2), /* x1-coordinate */
                                multiplier * (-pad_width + pad_length) / 2, /* y1-coordinate */
                                multiplier * pad_length, /* width of the pad */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * (pad_length + (2 * pad_solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                }
                /* Write a package body on the silkscreen */
                if (silkscreen_package_outline)
                {
                        write_element_line
                        (
                                fp,
                                multiplier * (((-pitch_x + pad_length + silkscreen_line_width) / 2) + pad_solder_mask_clearance),
                                multiplier * ((package_body_width + silkscreen_line_width) / 2),
                                multiplier * (((pitch_x - pad_length - silkscreen_line_width) / 2) - pad_solder_mask_clearance),
                                multiplier * ((package_body_width + silkscreen_line_width) / 2),
                                multiplier * silkscreen_line_width
                        );
                        write_element_line
                        (
                                fp,
                                multiplier * (((-pitch_x + pad_length + silkscreen_line_width) / 2) + pad_solder_mask_clearance),
                                multiplier * ((-package_body_width - silkscreen_line_width) / 2),
                                multiplier * (((pitch_x - pad_length - silkscreen_line_width) / 2) - pad_solder_mask_clearance),
                                multiplier * ((-package_body_width - silkscreen_line_width) / 2),
                                multiplier * silkscreen_line_width
                        );
                }
                /* Write a pin #1 marker */
                if (silkscreen_indicate_1)
                {
                        write_element_arc
                        (
                                fp,
                                multiplier * (((-pitch_x - pad_length) / 2) - pad_solder_mask_clearance - 4 * silkscreen_line_width) ,
                                0.0,
                                multiplier * 2 * silkscreen_line_width,
                                multiplier * 2 * silkscreen_line_width,
                                0.0,
                                360.0,
                                multiplier * silkscreen_line_width
                        );
                }
                /* Write a courtyard */
                if (courtyard)
                {
                }
                /* Write attributes */
                write_attributes (fp);
                fclose (fp);
        }
        else
        {
                fprintf (stderr, "Error: could not open file for SMT footprint: %s.\n", footprint_filename);
                return (EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a TO92 footprint for a transistor package.
 */
int
write_footprint_to92 ()
{
        FILE *fp;
        gdouble xmax;
        gdouble xmin;
        gdouble ymax;
        gdouble ymin;
        gdouble x_text;
        gdouble y_text;

        if (fp = g_fopen (footprint_filename, "w"))
        {
                /* Determine (extreme) courtyard dimensions */
                xmax = multiplier * (package_body_length / 2);
                xmin = multiplier * (-package_body_length / 2);
                ymax = multiplier * (package_body_width / 2);
                ymin = multiplier * (-package_body_width / 2);
                /* If the user input is using more real-estate then use it */
                if (multiplier * (-courtyard_length / 2) < xmin)
                {
                        xmin = multiplier * (-courtyard_length / 2);
                }
                if (multiplier * (courtyard_length / 2) > xmax)
                {
                        xmax = multiplier * (courtyard_length / 2);
                }
                if (multiplier * (-courtyard_width / 2) < ymin)
                {
                        ymin = multiplier * (-courtyard_width / 2);
                }
                if (multiplier * (courtyard_width / 2) > ymax)
                {
                        ymax = multiplier * (courtyard_width / 2);
                }
                /* Write element header */
                x_text = 0.0 ;
                y_text = (ymin / 2) - 150.0 ;
                write_element_header (fp, x_text, y_text);
                /* Write encapsulated element entities */
                write_pin
                (
                        fp,
                        1, /* pin number */
                        "", /* pin name */
                        -5000.0, /* x0 coordinate */
                        0.0, /* y0-coordinate */
                        multiplier * pad_diameter, /* width of the annulus ring (pad) */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * pad_solder_mask_clearance, /* solder mask clearance */
                        multiplier * pin_drill_diameter, /* pin drill diameter */
                        /* Write pin #1 with a square pad */
                        (pin1_square) ? "square" : pin_pad_flags /* flags */
                );
                write_pin
                (
                        fp,
                        2, /* pin number */
                        "", /* pin name */
                        0.0, /* x0 coordinate */
                        0.0, /* y0-coordinate */
                        multiplier * pad_diameter, /* width of the annulus ring (pad) */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * pad_solder_mask_clearance, /* solder mask clearance */
                        multiplier * pin_drill_diameter, /* pin drill diameter */
                        pin_pad_flags /* flags */
                );
                write_pin
                (
                        fp,
                        3, /* pin number */
                        "", /* pin name */
                        5000.0, /* x0 coordinate */
                        0.0, /* y0-coordinate */
                        multiplier * pad_diameter, /* width of the annulus ring (pad) */
                        multiplier * pad_clearance, /* clearance */
                        multiplier * pad_solder_mask_clearance, /* solder mask clearance */
                        multiplier * pin_drill_diameter, /* pin drill diameter */
                        pin_pad_flags /* flags */
                );
                /* Write a pin #1 marker */
                if (silkscreen_indicate_1)
                {
                        /*! \todo Write a pin #1 marker ! */
                }
                /* Write package body on silkscreen */
                if (silkscreen_package_outline)
                {
                        fprintf (fp, "\tElementLine[-8600 -6000 8600 -6000 1000]");
                        fprintf (fp, "\tElementArc[0 0 10500 10500 -35 250 1000]");
                }
                /* Write a courtyard */
                if (courtyard)
                {
                }
                /* Write attributes */
                write_attributes (fp);
                fclose (fp);
        }
        else
        {
                fprintf (stderr, "Error: could not open file for TO92 footprint: %s.\n", footprint_filename);
                return (EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a footprintwizard file based on the current global variables.
 *
 */
int
write_footprintwizard_file()
{
        FILE *fp;

        if (fp = g_fopen (fpw_filename, "w"))
        {
        fprintf (fp, "%s\n", footprint_filename);
        fprintf (fp, "%s\n", footprint_units);
        fprintf (fp, "%s\n", footprint_author);
        fprintf (fp, "%s\n", footprint_dist_license);
        fprintf (fp, "%s\n", footprint_units);
        fprintf (fp, "%s\n", footprint_status);
        fprintf (fp, "%s\n", footprint_name);
        fprintf (fp, "%s\n", footprint_type);
        fprintf (fp, "%d\n", number_of_pins);
        fprintf (fp, "%d\n", number_of_columns);
        fprintf (fp, "%d\n", number_of_rows);
        fprintf (fp, "%s\n", pad_shape);
        fprintf (fp, "%s\n", pin_1_position);
        fprintf (fp, "%f\n", pitch_x);
        fprintf (fp, "%f\n", pitch_y);
        fprintf (fp, "%f\n", pad_length);
        fprintf (fp, "%f\n", pad_width);
        fprintf (fp, "%f\n", pad_diameter);
        fprintf (fp, "%f\n", pin_drill_diameter);
        fprintf (fp, "%f\n", pad_clearance);
        fprintf (fp, "%f\n", pad_solder_mask_clearance);
        fprintf (fp, "%f\n", silkscreen_line_width);
        fprintf (fp, "%f\n", courtyard_length);
        fprintf (fp, "%f\n", courtyard_width);
        fprintf (fp, "%f\n", courtyard_line_width);
        fprintf (fp, "%d\n", thermal);
        fprintf (fp, "%f\n", thermal_length);
        fprintf (fp, "%f\n", thermal_width);
        fprintf (fp, "%f\n", thermal_solder_mask_clearance);
        fprintf (fp, "%f\n", c1);
        fprintf (fp, "%f\n", g1);
        fprintf (fp, "%f\n", z1);
        fprintf (fp, "%f\n", c2);
        fprintf (fp, "%f\n", g2);
        fprintf (fp, "%f\n", z2);
        }
        else
        {
                fprintf (stderr, "Error: could not open footprintwizard file %s.\n", fpw_filename);
        }
        fclose (fp);
}


/*!
 * \brief Write a footprint based on the global variables.
 *
 * This function does not write the footprints.\n
 * It is a dispatcher for helper functions who <b>actually</b> do write the
 * footprint to file.
 */
int
write_footprint()
{
        /* Determine the pad shape type, default is a circular pad */
        if (strcmp (pad_shape, ""))
        {
                /* No pad shape given */
                fprintf (stderr, "Warning: could not determine pad shape.\n");
                fprintf (stderr, "Please try again.\n");
                return (EXIT_FAILURE);
        }
        if (strcmp (pad_shape, "rectangular pad"))
        {
                g_strconcat (pin_pad_flags, "square", NULL);
        }
        if (strcmp (pad_shape, "octagonal pad"))
        {
                g_strconcat (pin_pad_flags, "octagon", NULL);
        }
        if (strcmp (pad_shape, "rounded pad, elongated"))
        {
                g_strconcat (pin_pad_flags, "", NULL);
        }
        /* Determine the units type */
        if (strcmp (footprint_units, "mil")) multiplier = 100.0;
        if (strcmp (footprint_units, "mil/100")) multiplier = 1.0;
        if (strcmp (footprint_units, "mm")) multiplier = (1000 / 25.4) * 100;
        /* Determine the package type */
        if (strcmp (footprint_type, "BGA")) package_type = BGA;
        if (strcmp (footprint_type, "CAPC")) package_type = CAPC;
        if (strcmp (footprint_type, "DIP")) package_type = DIP;
        if (strcmp (footprint_type, "INDC")) package_type = INDC;
        if (strcmp (footprint_type, "PGA")) package_type = PGA;
        if (strcmp (footprint_type, "QFN")) package_type = QFN;
        if (strcmp (footprint_type, "QFP")) package_type = QFP;
        if (strcmp (footprint_type, "RESC")) package_type = RESC;
        if (strcmp (footprint_type, "SIP")) package_type = SIP;
        if (strcmp (footprint_type, "SO")) package_type = SO;
        if (strcmp (footprint_type, "TO92")) package_type = TO92;
        /* Depending on the package type write that type of footprint file */
        switch (package_type)
        {
                case BGA:
                case CAPC:
                {
                        write_footprint_smt ();
                }
                case DIP:
                {
                        write_footprint_dip ();
                }
                case DO:
                case INDC:
                {
                        write_footprint_smt ();
                }
                case PGA:
                case PLCC:
                case QFN:
                case QFP:
                case RESC:
                {
                        write_footprint_smt ();
                }
                case SIP:
                case SO:
                case TO92:
                {
                        write_footprint_to92 ();
                }
                default:
                {
                        fprintf (stdout, "Error: wrong or non-existent footprint type entered.\n");
                }
        }
}

/* EOF */
