/*!
 * \file libfpw.c
 * \brief libfpw contains helper functions for both fpw (CLI) and
 * pcb-gfpw (GUI) versions of the pcb FootPrintWizard.
 *
 * fpw (FootPrintWizard) is a program for the creation of footprint files
 * to be used by the pcb layout application (see http://pcb.sourgeforge.net)
 * for the placement of parts in a pcb layout.\n\n
 * The functions in libfpw are called by the CLI version of the
 * FootPrintWizard (fpw) as well as the GUI version (pcb-gfpw).\n
 *
 * \author Copyright (C) 2007 by Bert Timmerman <bert.timmerman@xs4all.nl>
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
        DIOM, /*! Diode, Molded package. */
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
#define PIN 0x0001 /*!< If set, this object is a pin.\n */
                   /*!< This flag is for internal use only. */
#define VIA 0x0002 /*!< Likewise, for vias. */
#define HOLE 0x0008 /*!< For pins and vias, this flag means that the pin or via is a hole without a copper annulus. */
#define PININPOLY 0x0010 /*!< For pins and pads, this flag is used internally to indicate that the pin or pad overlaps a polygon on some layer. */
#define SHOWNAME 0x0020 /*!< For elements, when set the names of pins are shown. */
#define ONSOLDER 0x0080 /*!< For elements and pads, indicates that they are on the solder side. */
#define SQUARE 0x0100 /*!< For pins and pads, indicates a square (vs round) pin/pad. */
#define WARN 0x0200 /*!< For pins, vias, and pads, set to indicate a warning. */
#define OCTAGON 0x0800 /*!< Draw pins and vias as octagons. */
#define LOCK 0x2000 /*!< Set for locked objects. */
#define EDGE2 0x4000 /*!< For pads, indicates that the second point is closer to the edge.\n */
                     /*!< For pins, indicates that the pin is closer to a horizontal edge and thus pinout text should be vertical. */
#define MARKER 0x8000 /*!< Marker used internally to avoid revisiting an object. */
#define NOPASTE 0x10000 /*!< For pads, set to prevent a solderpaste stencil opening for the pad.\n */
                        /*!< Primarily used for pads used as fiducials. */

gchar *fpw_filename; /*!< Filename of footprintwizard file. */
gchar *fpw_suffix = "fpw"; /*!< Suffix of footprintwizard file. */
gchar *footprint_filename = NULL; /*!< Filename of footprint file. */
gchar *fp_suffix = "fp"; /*!< Suffix of footprint file. */
gchar *footprint_name = NULL; /*!< Name of the footprint. */
gchar *footprint_type = NULL; /*!< Type of the footprint. */
package_t package_type; /*!< Type of the package. */
gchar *footprint_units = NULL; /*!< Units for the footprint dimensions. */
gdouble multiplier; /*!< Multiplier to convert to mils/100. */
gchar *footprint_value; /*!< Value of the package. */

gdouble package_body_length; /*!< Length dimension of the package body. */
gdouble package_body_width; /*!< Width dimension of the package body. */
gdouble package_body_height; /*!< Height dimension of the package body. */
gboolean package_is_radial; /*!< Package has a radial body. */

gchar *footprint_author; /*!< Author of the footprint. */
gchar *footprint_dist_license; /*!< Distribution license of the footprint. */
gchar *footprint_use_license; /*!< Usage license of the footprint. */
gchar *footprint_status; /*!< Status of the footprint. */

gint n; /*!< Number of pads/pins. */
gint n_col; /*!< Number of columns. */
gint n_row; /*!< Number of rows. */
gchar *n1_pos = NULL; /*!< Position of number 1 pin. */
location_t pin1_location; /*!< Location of number 1 pin. */
gdouble pitch_x; /*!< Pitch in X-direction. */
gdouble pitch_y; /*!< Pitch in Y-direction. */
gdouble x; /*!< Length of pad. */
gdouble y; /*!< Width of pad. */
gdouble pin_hole_diameter; /*!< Diameter of pin hole. */
gdouble pad_diameter; /*!< Diameter of pin pad (annulus). */
gchar *pad_shape = NULL; /*!< Shape of pads/pins. */
gint pin_pad_type; /*!< Type of pads/pins. */
gchar *pin_pad_flags = NULL; /*!< Flags of pads/pins. */
gdouble solder_mask_clearance; /*!< Solder mask clearance of a pin/pad. */
gdouble pad_clearance; /*!< Clearance of a pin/pad. */

gboolean package_outline; /*!< Draw the package body outline on the silkscreen. */
gboolean silkscreen_indicate_1; /*!< Indicate the position of number 1 */
        /*!< pin/pad on the silkscreen. */
gdouble silkscreen_length; /*!< Silkscreen length (X-direction). */
gdouble silkscreen_width; /*!< Silkscreen width (Y-direction). */
gdouble r1; /*!< Silkscreen width (Y-direction). */
gdouble r2; /*!< Silkscreen length (X-direction). */
gdouble silkscreen_line_width; /*!< Silkscreen line width. */

gboolean courtyard; /*!< Draw courtyard. */
gdouble courtyard_length; /*!< Courtyard length (X-direction). */
gdouble courtyard_width; /*!< Courtyard width (Y-direction). */
gdouble v1; /*!< Courtyard width (Y-direction). */
gdouble v2; /*!< Courtyard length (X-direction). */
gdouble courtyard_line_width; /*!< Courtyard line width. */

gboolean thermal; /*!< Draw thermal pad. */
gboolean thermal_nopaste; /*!< Thermal pad has no paste. */
gdouble thermal_x; /*!< Length of thermal pad. */
gdouble thermal_y; /*!< Width of thermal pad. */
gdouble thermal_solder_mask_clearance; /*!< Solder mask clearance of thermal pad. */

gchar *dummy = NULL; /*!< Every now and then the village-idot is needed ;-) */

/*!
 * \attention Now follow some obsolete variables for goals input (heel and
 * toe) of pads.\n
 * These variables maybe added when and if another tab is added for the
 * creation of footprints based on heel and toe information for pads.\n
 * This can be considered being an expert-mode. */
gdouble c1; /*!< Top to bottom pads center-center distance. */
gdouble e1; /*!< Pitch in Y-direction. */
gdouble g1; /*!< Top to bottom pads inner-inner distance. */
gdouble z1; /*!< Top to bottom pads outer-outer distance. */
gdouble c2; /*!< Left to right pads center-center distance. */
gdouble e2; /*!< Pitch in X-direction. */
gdouble g2; /*!< Left to right pads inner-inner distance. */
gdouble z2; /*!< Left to right pads outer-outer distance. */



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
}


/*!
 * \brief Write an element arc.
 *
 */
int
write_element_arc
(
        FILE *fp, /*!< file pointer */
        gdouble x,
        gdouble y,
        gdouble width,
        gdouble height,
        gdouble start_angle,
        gdouble delta_angle,
        gdouble line_width
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
        fprintf (fp, "Element[\"\" \"%s\" \"?\" \"%s\" 0 0 %d %d 0 100 \"\"]\n",
                footprint_name,
                footprint_value,
                (int) (x_text * multiplier),
                (int) (y_text * multiplier)
                );
}


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
                fscanf (fp, "%s\n", n1_pos);
                fscanf (fp, "%s\n", pad_shape);
                fscanf (fp, "%d\n", n);
                fscanf (fp, "%d\n", n_col);
                fscanf (fp, "%d\n", n_row);
                fscanf (fp, "%f\n", x);
                fscanf (fp, "%f\n", y);
                fscanf (fp, "%f\n", pad_diameter);
                fscanf (fp, "%f\n", pin_hole_diameter);
                fscanf (fp, "%f\n", c1);
                fscanf (fp, "%f\n", g1);
                fscanf (fp, "%f\n", z1);
                fscanf (fp, "%f\n", c2);
                fscanf (fp, "%f\n", g2);
                fscanf (fp, "%f\n", z2);
                fscanf (fp, "%f\n", e1);
                fscanf (fp, "%f\n", e2);
                fscanf (fp, "%f\n", solder_mask_clearance);
                fscanf (fp, "%f\n", r1);
                fscanf (fp, "%f\n", r2);
                fscanf (fp, "%f\n", silkscreen_line_width);
                fscanf (fp, "%f\n", v1);
                fscanf (fp, "%f\n", v2);
                fscanf (fp, "%f\n", courtyard_line_width);
                fscanf (fp, "%d\n", thermal);
                fscanf (fp, "%f\n", thermal_x);
                fscanf (fp, "%f\n", thermal_y);
                fscanf (fp, "%f\n", thermal_solder_mask_clearance);
                close (fp);
        }
}


/*!
 * \brief Write a pad for any given footprint.
 *
 * Write a pad for any given footprint.
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
        gdouble solder_mask_clearance, /*!< solder mask clearance */
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
                (int) solder_mask_clearance,
                pad_name,
                pad_number,
                flags
                );
}


/*!
 * \brief Write a pin for any given footprint.
 *
 * Write a pin for any given footprint.
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
        gdouble solder_mask_clearance, /*!< solder mask clearance */
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
                (int) solder_mask_clearance,
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
 * If line_width is 0.0 no courtyard is drawn.
 * If line_width is < 0.0 a courtyard with a linewidth of 1/100 of
 * a mil is drawn (#define THIN_DRAW 1).
 */
int
write_rectangle
(
        FILE *fp, /*!< file pointer */
        gdouble xmin, /*!< minimum x-coordinate of courtyard */
        gdouble ymin, /*!< minimum y-coordinate of courtyard */
        gdouble xmax, /*!< maximum x-coordinate of courtyard */
        gdouble ymax, /*!< maximum y-coordinate of courtyard */
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
        /* Print courtyard ends (perpendicular to x-axis) */
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
        /* Print courtyard sides (parallel with x-axis) */
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
                xmax = multiplier * (e2 / 2 + pad_diameter / 2 + solder_mask_clearance);
                if (multiplier * (v1 / 2) > xmax) xmax = multiplier * (v1 / 2);
                xmin = multiplier * ((-e2 / 2) - (pad_diameter / 2) - solder_mask_clearance);
                if (multiplier * (-v1 / 2) < xmin) xmin = multiplier * (-v1 / 2);
                ymax = multiplier * ((n / 4) * e1 + (pad_diameter / 2) + solder_mask_clearance);
                if (multiplier * (v2 / 2) > ymax) ymax = multiplier * (v2 / 2);
                ymin = multiplier * ((-n / 4) * e1 - (pad_diameter / 2) - solder_mask_clearance);
                if (multiplier * (-v2 / 2) < ymin) ymin = multiplier * (-v2 / 2);
                /* Write element header to file */
                x_text = 0.0 ;
                y_text = (ymin / 2) - 150.0;
                write_element_header (fp, x_text, y_text);
                /* Write encapsulated element entities */
                fprintf (fp, "(\n");
                pin_number = 1;
                for (i = 0; i > (n_row - 1); i++)
                {
                        pin_number = 1 + i;
                        write_pin
                        (
                                fp,
                                pin_number, /* pin number */
                                "", /* pin name */
                                multiplier * - e2 / 2, /* x0 coordinate */
                                multiplier * ((-n_row / 2 + i) * e1), /* y0-coordinate */
                                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * solder_mask_clearance, /* solder mask clearance */
                                multiplier * pin_hole_diameter, /* pin drill diameter */
                                pin_pad_flags /* flags */
                        );
                        pin_number = (n_row * n_col) - i;
                        write_pin
                        (
                                fp,
                                pin_number, /* pin number */
                                "", /* pin name */
                                multiplier * e2 / 2, /* x0 coordinate */
                                multiplier * ((-n_row / 2 + i) * e1), /* y0-coordinate */
                                multiplier * pad_diameter, /* width of the annulus ring (pad) */
                                multiplier * pad_clearance, /* clearance */
                                multiplier * solder_mask_clearance, /* solder mask clearance */
                                multiplier * pin_hole_diameter, /* pin drill diameter */
                                pin_pad_flags /* flags */
                        );
                        pin_number++;
                }
                /* Write a package body on the silkscreen */
                if (package_outline)
                {
                        write_rectangle
                        (
                                fp,
                                multiplier * (((-e2 + pad_diameter + silkscreen_line_width) / 2) + solder_mask_clearance) ,
                                multiplier * ymin,
                                multiplier * (((e2 - pad_diameter - silkscreen_line_width) / 2) - solder_mask_clearance) ,
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
                write_attributes(fp);
                fprintf (fp, "\n");
                fprintf (fp, ")\n");
        }
        else
        {
                fprintf (stderr, "Error: could not open file for DIP footprint: %s.\n", footprint_filename);
                return (EXIT_FAILURE);
        }
        close (fp);
        return (EXIT_SUCCESS);
}


/*!
 * \brief Write a SMT footprint with two pads for a chip resistor package.
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
                xmax = multiplier * (e2 / 2 + x / 2 + solder_mask_clearance);
                if (multiplier * (v1 / 2) > xmax) xmax = multiplier * (v1 / 2);
                xmin = multiplier * ((-e2 / 2) - (x / 2) - solder_mask_clearance);
                if (multiplier * (-v1 / 2) < xmin) xmin = multiplier * (-v1 / 2);
                ymax = multiplier * (y / 2 + solder_mask_clearance);
                if (multiplier * (v2 / 2) > ymax) ymax = multiplier * (v2 / 2);
                ymin = multiplier * ((-y / 2) - solder_mask_clearance);
                if (multiplier * (-v2 / 2) < ymin) ymin = multiplier * (-v2 / 2);
                /* Write element header to file */
                x_text = 0.0 ;
                y_text = (ymin / 2) - 150.0;
                write_element_header (fp, x_text, y_text);
                /* Write encapsulated element entities */
                fprintf (fp, "(\n");
                if (x > y) /* Write pads parallel to x-axis */
                {
                        fprintf (stderr, "Pads are drawn parallel on X-axis.\n");
                        /* Pad #1 */
                        write_pad
                        (
                                fp, /* file pointer */
                                1, /* pad number */
                                "", /* pad name */
                                multiplier * -1 * (e2 + x - y) / 2, /* x0 coordinate */
                                0, /* y0-coordinate */
                                multiplier * (-e2 + x - y) / 2, /* x1 coordinate */
                                0, /* y1-coordinate */
                                multiplier * y, /* width of the pad */
                                multiplier * solder_mask_clearance, /* clearance */
                                multiplier * (y + (2 * solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                        /* Pad #2 */
                        write_pad
                        (
                                fp, /* file pointer */
                                2, /* pad number */
                                "", /* pad name */
                                multiplier * -1 * (-e2 + x - y) / 2, /* x0 coordinate */
                                0, /* y0-coordinate */
                                multiplier * (e2 + x - y) / 2, /* x1 coordinate */
                                0, /* y1-coordinate */
                                multiplier * y, /* width of the pad */
                                multiplier * solder_mask_clearance, /* clearance */
                                multiplier * (y + (2 * solder_mask_clearance)), /* solder mask clearance */
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
                                multiplier * (-e2 / 2), /* x0-coordinate */
                                multiplier * (y - x) / 2, /* y0-coordinate */
                                multiplier * (-e2 / 2), /* x0-coordinate */
                                multiplier * (-y + x) / 2, /* y1-coordinate */
                                multiplier * x, /* width of the pad */
                                multiplier * solder_mask_clearance, /* clearance */
                                multiplier * (x + (2 * solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                        /* Pad #2 */
                        write_pad
                        (
                                fp, /* file pointer */
                                1, /* pad number */
                                "", /* pad name */
                                multiplier * (e2 / 2), /* x1-coordinate */
                                multiplier * (y - x) / 2, /* y0-coordinate */
                                multiplier * (e2 / 2), /* x1-coordinate */
                                multiplier * (-y + x) / 2, /* y1-coordinate */
                                multiplier * x, /* width of the pad */
                                multiplier * solder_mask_clearance, /* clearance */
                                multiplier * (x + (2 * solder_mask_clearance)), /* solder mask clearance */
                                pin_pad_flags /* flags */
                        );
                }
                /* Write a package body on the silkscreen */
                fprintf
                (
                        fp,
                        "\tElementLine[%d %d %d %d %d]\n",
                        (int) (((-e2 + x + silkscreen_line_width) / 2) + solder_mask_clearance),
                        (int) y,
                        (int) (((e2 - x - silkscreen_line_width) / 2) - solder_mask_clearance),
                        (int) y,
                        (int) silkscreen_line_width
                );
                fprintf
                (
                        fp,
                        "\tElementLine[%d %d %d %d %d]\n",
                        (int) (((-e2 + x + silkscreen_line_width) / 2) + solder_mask_clearance),
                        (int) -y,
                        (int) (((e2 - x - silkscreen_line_width) / 2) - solder_mask_clearance),
                        (int) -y,
                        (int) silkscreen_line_width
                );
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
                write_attributes(fp);
                fprintf (fp, "\n");
                fprintf (fp, ")\n");
        }
        else
        {
                fprintf (stderr, "Error: could not open file for SMT footprint: %s.\n", footprint_filename);
                return (EXIT_FAILURE);
        }
        close (fp);
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
                xmax = multiplier * (package_body_length);
                if (multiplier * (v1 / 2) > xmax) xmax = multiplier * (v1 / 2);
                xmin = multiplier * (-package_body_length);
                if (multiplier * (-v1 / 2) < xmin) xmin = multiplier * (-v1 / 2);
                ymax = multiplier * (package_body_width);
                if (multiplier * (v2 / 2) > ymax) ymax = multiplier * (v2 / 2);
                ymin = multiplier * (-package_body_width);
                if (multiplier * (-v2 / 2) < ymin) ymin = multiplier * (-v2 / 2);
                /* Write element header to file */
                x_text = 0.0 ;
                y_text = (ymin / 2) - 150.0 ;
                write_element_header (fp, x_text, y_text);
                /* Write encapsulated element entities */
                fprintf (fp, "(\n");
                /* Write package body on silkscreen */
                if (courtyard)
                {
                }
                /* Write attributes */
                write_attributes (fp);
                fprintf (fp, "\n");
                fprintf (fp, ")\n");
        }
        else
        {
                fprintf (stderr, "Error: could not open file for TO92 footprint: %s.\n", footprint_filename);
                return (EXIT_FAILURE);
        }
        close (fp);
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
        fprintf (fp, "%s\n", footprint_name);
        fprintf (fp, "%s\n", footprint_type);
        fprintf (fp, "%s\n", footprint_units);
        fprintf (fp, "%s\n", n1_pos);
        fprintf (fp, "%s\n", pad_shape);
        fprintf (fp, "%d\n", n);
        fprintf (fp, "%d\n", n_col);
        fprintf (fp, "%d\n", n_row);
        fprintf (fp, "%f\n", x);
        fprintf (fp, "%f\n", y);
        fprintf (fp, "%f\n", pad_diameter);
        fprintf (fp, "%f\n", pin_hole_diameter);
        fprintf (fp, "%f\n", c1);
        fprintf (fp, "%f\n", g1);
        fprintf (fp, "%f\n", z1);
        fprintf (fp, "%f\n", c2);
        fprintf (fp, "%f\n", g2);
        fprintf (fp, "%f\n", z2);
        fprintf (fp, "%f\n", e1);
        fprintf (fp, "%f\n", e2);
        fprintf (fp, "%f\n", solder_mask_clearance);
        fprintf (fp, "%f\n", r1);
        fprintf (fp, "%f\n", r2);
        fprintf (fp, "%f\n", silkscreen_line_width);
        fprintf (fp, "%f\n", v1);
        fprintf (fp, "%f\n", v2);
        fprintf (fp, "%f\n", courtyard_line_width);
        fprintf (fp, "%d\n", thermal);
        fprintf (fp, "%f\n", thermal_x);
        fprintf (fp, "%f\n", thermal_y);
        fprintf (fp, "%f\n", thermal_solder_mask_clearance);
        }
        else
        {
                fprintf (stderr, "Error: could not open footprintwizard file %s.\n", fpw_filename);
        }
        close (fp);
}


/*!
 * \brief Write a footprint based on the global variables.
 *
 */
int
write_footprint()
{
        /* Determine the pad shape type */
        if (strcmp (pad_shape, "rectangular pad"))
        {
                g_strconcat (pin_pad_flags, "square", NULL);
        }
        if (strcmp (pad_shape, "rectangular pin"))
        {
                g_strconcat (pin_pad_flags, "square", NULL);
        }
        if (strcmp (pad_shape, "octagonal pad"))
        {
                g_strconcat (pin_pad_flags, "octagon", NULL);
        }
        if (strcmp (pad_shape, "octagonal pin"))
        {
                g_strconcat (pin_pad_flags, "octagon", NULL);
        }
        if (strcmp (pad_shape, "round pin, elongated"))
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
        if (strcmp (footprint_type, "TO92")) package_type = SO;
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
                case TO:
                default:
                {
                        fprintf (stdout, "Error: wrong or non-existent footprint type entered.\n");
                }
        }
}

/* EOF */
