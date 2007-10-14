/*!
 * \file libfpw.c
 * \author Copyright (C) 2007 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief libfpw contains functions for fpw (FootPrintWizard).
 *
 * fpw (FootPrintWizard) is a program for the creation of footprint files
 * used by the pcb layout application (see http://pcb.sourgeforge.net) for
 * the placement of parts in a pcb layout.
 */


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#define VERSION "0.0.1"

/* Some through hole package types */
#define TH 100 /*!< Generic technology description. */
#define SIP 101 /*!< Single Inline Package. */
#define DIP 102 /*!< Dual Inline Package. */
#define PGA 103 /*!< Pin Gate Array package. */
#define DO 104 /*!< Diode Outline package. */
#define TO 105 /*!< Transistor Outline package. */

/* Some surface mounted package types */
#define SMT 200 /*!< Generic technology description. */
#define BGA 201 /*!< Ball Gate Array package. */
#define SO 202 /*!< Small Outline package. */
#define PLCC 203 /*!< Plastic Leadless Chip Carrier package. */
#define QFN 204 /*!< Quad Flat No-leads package. */
#define QFP 205 /*!< Quad Flat Package. */

/* Locations for pin #1 orientation */
/*   2 -- 5 -- 8  */
/*   |    |    |  */
/*   1 -- 4 -- 7  */
/*   |    |    |  */
/*   0 -- 3 -- 6  */
#define LOWER_LEFT 0
#define MIDDLE_LEFT 1
#define UPPER_LEFT 2
#define LOWER_MIDDLE 3
#define MIDDLE_MIDDLE 4
#define UPPER_MIDDLE 5
#define LOWER_RIGHT 6
#define MIDDLE_RIGHT 7
#define UPPER_RIGHT 8

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

gchar *footprint_filename = NULL; /*!< filename of footprint file */
gchar *suffix = ".fp";
gchar *footprint_name = NULL; /*!< name of footprint */
gchar *footprint_type = NULL; /*!< type of footprint */
gint package_type; /*!< type of package */
gchar *footprint_units = NULL; /*!< units for footprint dimensions */
gdouble multiplier; /*!< multiplier to convert to mils/100. */
gchar *n1_pos = NULL; /*!< position of number 1 pin. */
gint n; /*!< number of pads/pins. */
gint n_col; /*!< number of columns. */
gint n_row; /*!< number of rows. */
gdouble c1; /*!< top to bottom pads/pins center-center distance. */
gdouble e1; /*!< vertical spacing of pads/pins (pitch). */
gdouble g1; /*!< top to bottom pads/pins inner-inner distance. */
gdouble z1; /*!< top to bottom pads/pins outer-outer distance. */
gdouble c2; /*!< left to right pads/pins center-center distance. */
gdouble e2; /*!< horizontal spacing of pads/pins (pitch). */
gdouble g2; /*!< left to right pads/pins inner-inner distance. */
gdouble z2; /*!< left to right pads/pins outer-outer distance. */
gdouble x; /*!< length of pad. */
gdouble y; /*!< width of pad. */
gdouble d_hole; /*!< diameter of pin hole. */
gdouble d_pad; /*!< diameter of pin pad. */
gchar *pad_shape = NULL; /*!< shape of pads/pins. */
gint pin_pad_type; /*!< type of pads/pins. */
gchar *pin_pad_flags = NULL; /*!< flags of pads/pins. */
gdouble solder_mask_clearance; /*!< solder mask clearance of pin/pad. */
gdouble silkscreen_line_width; /*!< silkscreen line width */
gdouble r1; /*!< vertical silkscreen dimension */
gdouble r2; /*!< horizontal silkscreen dimension */
gdouble v1; /*!< vertical courtyard dimension */
gdouble v2; /*!< horizontal courtyard dimension */
gdouble courtyard_line_width; /*!< courtyard line width */
gboolean thermal; /*!< has thermal pad */
gboolean thermal_nopaste; /*!< thermal pad has no paste */
gdouble thermal_x; /*!< length of thermal pad. */
gdouble thermal_y; /*!< width of thermal pad. */
gdouble thermal_solder_mask_clearance; /*!< solder mask clearance of thermal pad. */


/*!
 * \brief Write a rectangular pad for any given footprint.
 *
 * Write a rectangular pad for any given footprint.
 */
int
write_rectangular_pad
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
 * \brief Write a rectangular courtyard for any given footprint.
 *
 * Write a rectangular courtyard for any given footprint.
 * If courtyard_line_width is 0.0 no courtyard is drawn.
 * If courtyard_line_width is < 0.0 a courtyard with a linewidth of 1/100 of
 * a mil is drawn (#define THIN_DRAW 1).
 */
int
write_rectangular_courtyard
(
        FILE *fp, /*!< file pointer */
        gdouble xmin, /*!< minimum x-coordinate of courtyard */
        gdouble ymin, /*!< minimum y-coordinate of courtyard */
        gdouble xmax, /*!< maximum x-coordinate of courtyard */
        gdouble ymax, /*!< maximum y-coordinate of courtyard */
        gdouble courtyard_line_width /*!< courtyard line width */
)
{
        /* If courtyard_line_width is 0.0 do not draw a courtyard */
        if (courtyard_line_width == 0.0)
        {
                return;
        }
        /* If courtyard_line_width is < 0.0 a courtyard with a linewidth of
         * 1/100 of a mil is drawn (#define THIN_DRAW 1)
         */
        if (courtyard_line_width < 0.0)
        {
                courtyard_line_width = THIN_DRAW;
        }
        /* Print courtyard ends (perpendicular to x-axis) */
        fprintf (fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) xmin,
                (int) ymin,
                (int) xmin,
                (int) ymax,
                (int) courtyard_line_width
                );
        fprintf (fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) xmax,
                (int) ymin,
                (int) xmax,
                (int) ymax,
                (int) courtyard_line_width
                );
        /* Print courtyard sides (parallel with x-axis) */
        fprintf (fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) xmin,
                (int) ymin,
                (int) xmax,
                (int) ymin,
                (int) courtyard_line_width
                );
        fprintf (fp,
                "\tElementLine[%d %d %d %d %d]\n",
                (int) xmax,
                (int) ymax,
                (int) xmin,
                (int) ymax,
                (int) courtyard_line_width
                );
}


/*!
 * \brief Write a basic SMT footprint with two pads for a resistor or
 * capacitor.
 *
 */
int
write_smt_footprint ()
{
        FILE *fp = NULL;
        double xmax;
        double xmin;
        double ymax;
        double ymin;

        /* Determine filename for the actual footprint file */
        if (g_str_has_suffix (footprint_name, suffix))
        {
                /* Footprintname has the .fp suffix, do nothing here */
        }
        else
        {
                footprint_filename = g_strconcat (footprint_name, ".fp", NULL);
        }
        if (fp = g_fopen (footprint_filename, "w"))
        {
                /* Determine extreme (courtyard) dimensions */
                xmax = multiplier * (e2 / 2 + x / 2 + solder_mask_clearance);
                if (multiplier * (v1 / 2) > xmax) xmax = multiplier * (v1 / 2);
                xmin = multiplier * ((-e2 / 2) - (x / 2) - solder_mask_clearance);
                if (multiplier * (-v1 / 2) < xmin) xmin = multiplier * (-v1 / 2);
                ymax = multiplier * (y / 2 + solder_mask_clearance);
                if (multiplier * (v2 / 2) > ymax) ymax = multiplier * (v2 / 2);
                ymin = multiplier * ((-y / 2) - solder_mask_clearance);
                if (multiplier * (-v2 / 2) < ymin) ymin = multiplier * (-v2 / 2);
                /* Write header to file */
                fprintf (fp, "Element[0x00000000 \"%s\" \"?\" \"\" %d %d 0 0 0 100 0x00000000]\n",
                        footprint_name,
                        (int) (xmin + multiplier * 20),
                        (int) (ymax + multiplier * 20)
                        );
                /* Write encapsulated element entities */
                fprintf (fp, "(\n");
                if (x > y) /* Write pads parallel to x-axis */
                {
                        fprintf (stderr, "Pads are drawn parallel on X-axis.\n");
                        /* Pad #1 */
                        write_rectangular_pad
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
                                "square" /* flags */
                        );
                        /* Pad #2 */
                        write_rectangular_pad
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
                                "square" /* flags */
                        );
                }
                else /* write pads perpendiclar to x-axis */
                {
                        fprintf (stderr, "Pads are drawn perpendicular to X-axis.\n");
                        /* Pad #1 */
                        fprintf (fp, "\tPad[%d %d %d %d %d %d %d \"\" \"1\" 0x00000100]\n",
                                (int) (-multiplier * (e2 / 2)), /* x0-coordinate */
                                (int) (multiplier * (y - x) / 2), /* y0-coordinate */
                                (int) (-multiplier * (e2 / 2)), /* x0-coordinate */
                                (int) (multiplier * (-y + x) / 2), /* y1-coordinate */
                                (int) (multiplier * x), /* width of the pad */
                                (int) (multiplier * solder_mask_clearance), /* clearance */
                                (int) (multiplier * (x + (2 * solder_mask_clearance))) /* solder mask clearance */
                                );
                        /* Pad #2 */
                        fprintf (fp, "\tPad[%d %d %d %d %d %d %d \"\" \"2\" 0x00000100]\n",
                                (int) (multiplier * (e2 / 2)), /* x1-coordinate */
                                (int) (multiplier * (y - x) / 2), /* y0-coordinate */
                                (int) (multiplier * (e2 / 2)), /* x1-coordinate */
                                (int) (multiplier * (-y + x) /2), /* y1-coordinate */
                                (int) (multiplier * x), /* width of the pad */
                                (int) (multiplier * solder_mask_clearance), /* clearance */
                                (int) (multiplier * (x + (2 * solder_mask_clearance))) /* solder mask clearance */
                                );
                }
                courtyard_line_width = multiplier * courtyard_line_width;
                write_rectangular_courtyard (fp, xmin, ymin, xmax, ymax, courtyard_line_width);
                /* Attributes in the form "Attribute("name" "value")" */
                fprintf (fp, "\tAttribute(\"author\" \"Bert Timmerman\")\n");
                fprintf (fp, "\tAttribute(\"dist-license\" \"GPL\")\n");
                fprintf (fp, "\tAttribute(\"use-license\" \"unlimited\")\n");
                fprintf (fp, "\tAttribute(\"xxx\" \"yyy\")\n");
                fprintf (fp, "\n");
                fprintf (fp, ")\n");
        }
        close (fp);
}


/*!
 * \brief Write a footprint based on the global variables.
 *
 */
int
write_footprintwizard_file()
{
        FILE *fp;
        gchar *suffix = ".fp";

        /* Write global variables to footprintwizard file with .fpw suffix */
        if (g_str_has_suffix (footprint_name, suffix))
        {
                /* Footprintname has a .fp suffix, add a w */
                footprint_filename = g_strconcat (footprint_name, "w", NULL);
        }
        else
        {
                /* Footprintname has no .fp suffix, add a .fpw suffix */
                footprint_filename = g_strconcat (footprint_name, ".fpw", NULL);
        }
        if (fp = g_fopen (footprint_filename, "w"))
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
                fprintf (fp, "%f\n", d_pad);
                fprintf (fp, "%f\n", d_hole);
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
        if (strcmp (footprint_units, "mils")) multiplier = 100.0;
        if (strcmp (footprint_units, "mils/100")) multiplier = 1.0;
        if (strcmp (footprint_units, "mm")) multiplier = (1000 / 25.4) * 100;
        /* Determine the footprint type */
        if (strcmp (footprint_type, "DIP")) package_type = DIP;
        if (strcmp (footprint_type, "SIP")) package_type = SIP;
        if (strcmp (footprint_type, "PGA")) package_type = PGA;
        if (strcmp (footprint_type, "BGA")) package_type = BGA;
        if (strcmp (footprint_type, "QFN")) package_type = QFN;
        if (strcmp (footprint_type, "QFP")) package_type = QFP;
        if (strcmp (footprint_type, "SO")) package_type = SO;
        if (strcmp (footprint_type, "SMT")) package_type = SMT;
        /* Depending on the footprint type write that type of footprint file
         */
        switch (package_type)
        {
                case TH:
                case SIP:
                case DIP:
                case PGA:
                case DO:
                case TO:
                case SMT:
                {
                        write_smt_footprint();
                }
                case BGA:
                case SO:
                case PLCC:
                case QFN:
                case QFP:
                default:
                {
                        fprintf (stdout, "Warning: wrong or non-existent footprint type entered.\n");
                }
        }
}

/* EOF */
