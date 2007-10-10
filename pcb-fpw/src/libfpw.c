/*!
 * \file libfpw.c
 * \author Copyright (C) 2007 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief libfpw contains functions for fpw (FootPrintWizard) which is a
 * program for the creation of footprint files used by the pcb layout
 * application (see http://pcb.sourgeforge.net) for the placement of parts in
 * a pcb layout.
 */


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>

#define VERSION "0.0.1"

/* Some package types */
#define DIP_TYPE 10
#define SIP_TYPE 11
#define PGA_TYPE 12
#define BGA_TYPE 20
#define SMT_TYPE 21
#define SO_TYPE 22
#define PLCC_TYPE 23
#define QFN_TYPE 24
#define QFP_TYPE 25

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

/* Thin lines on silkscreen are not printed in the real world */
#define THIN_DRAW 1

gchar *footprint_filename = NULL; /*!< filename of footprint file */
gchar *footprint_name = NULL; /*!< name of footprint */
gchar *footprint_type = NULL; /*!< type of footprint */
gchar *footprint_units = NULL; /*!< units for footprint dimensions */
gchar *n1_pos = NULL; /*!< position of number 1 pin. */
gchar *pad_shape = NULL; /*!< shape of pads/pins. */
gchar *suffix = ".fp";
gint n; /*!< number of pads/pins. */
gint n_col; /*!< number of columns. */
gint n_row; /*!< number of rows. */
gboolean thermal; /*!< has thermal pad */
gint type; /*!< type of footprint */
gdouble c1; /*!< top to bottom pads/pins center-center distance. */
gdouble c2; /*!< left to right pads/pins center-center distance. */
gdouble courtyard_line_width; /*!< courtyard line width */
gdouble e1; /*!< vertical spacing of pads/pins (pitch). */
gdouble e2; /*!< horizontal spacing of pads/pins (pitch). */
gdouble g1; /*!< top to bottom pads/pins inner-inner distance. */
gdouble g2; /*!< left to right pads/pins inner-inner distance. */
gdouble multiplier; /*!< multiplier to convert to mils/100. */
gdouble r1; /*!< vertical silkscreen dimension */
gdouble r2; /*!< horizontal silkscreen dimension */
gdouble silkscreen_line_width; /*!< silkscreen line width */
gdouble solder_mask_clearance; /*!< solder mask clearance of pad. */
gdouble thermal_solder_mask_clearance; /*!< solder mask clearance of thermal pad. */
gdouble v1; /*!< vertical courtyard dimension */
gdouble v2; /*!< horizontal courtyard dimension */
gdouble x; /*!< length of pad. */
gdouble y; /*!< width of pad. */
gdouble thermal_x; /*!< length of thermal pad. */
gdouble thermal_y; /*!< width of thermal pad. */
gdouble z1; /*!< top to bottom pads/pins outer-outer distance. */
gdouble z2; /*!< left to right pads/pins outer-outer distance. */
gdouble d_hole; /*!< diameter of pin hole. */
gdouble d_pad; /*!< diameter of pin pad. */


/*!
 * \brief Write a rectangular courtyard for any given footprint.
 *
 * Function description:
 * Write a rectangular courtyard for any given footprint.
 * If courtyard_line_width is 0.0 no courtyard is drawn.
 * If courtyard_line_width is < 0.0 a courtyard with a linewidth of 1/100 of
 * a mil is drawn (#define THIN_DRAW 1).
 */
int
write_rectangular_pad
(
        FILE *fp, /*!< file pointer */
        gint pad_number, /*!< pad number */
        gdouble x0,
        gdouble y0,
        gdouble x1,
        gdouble y1,
        gdouble width,
        gdouble clearance,
        gdouble solder_mask_clearance,
        gint flags
)
{
                        fprintf (fp,
                                "\tPad[%d %d %d %d %d %d %d \"\" \"1\" 0x00000100]\n",
                                (int) x0, /* x0 coordinate */
                                (int) y0, /* y0-coordinate */
                                (int) x1, /* x1 coordinate */
                                (int) y1, /* y1-coordinate */
                                (int) width, /* width of the pad */
                                (int) clearance, /* clearance */
                                (int) solder_mask_clearance /* solder mask clearance */
                                );
}


/*!
 * \brief Write a rectangular courtyard for any given footprint.
 *
 * Function description:
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
        /* If courtyard_line_width is 0.0 no courtyard is drawn */
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
 * Function description:
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
                if (x > y) /* write pads parallel to x-axis */
                {
                        fprintf (stdout, "Pads are drawn parallel on X-axis.\n");
                        /* Pad #1 */
                        fprintf (fp, "\tPad[%d %d %d %d %d %d %d \"\" \"1\" 0x00000100]\n",
                                (int) (multiplier * -1 * (e2 + x - y) / 2), /* x0 coordinate */
                                (int) (multiplier * (0)), /* y0-coordinate */
                                (int) (multiplier * (-e2 + x - y) / 2), /* x1 coordinate */
                                (int) (multiplier * (0)), /* y1-coordinate */
                                (int) (multiplier * y), /* width of the pad */
                                (int) (multiplier * solder_mask_clearance), /* clearance */
                                (int) (multiplier * (y + (2 * solder_mask_clearance))) /* solder mask clearance */
                                );
                        /* Pad #2 */
                        fprintf (fp, "\tPad[%d %d %d %d %d %d %d \"\" \"2\" 0x00000100]\n",
                                (int) (multiplier * -1 * (-e2 + x - y) / 2), /* x0 coordinate */
                                (int) (multiplier * (0)), /* y0-coordinate */
                                (int) (multiplier * (e2 + x - y) / 2), /* x1 coordinate */
                                (int) (multiplier * (0)), /* y1-coordinate */
                                (int) (multiplier * y), /* width of the pad */
                                (int) (multiplier * solder_mask_clearance), /* clearance */
                                (int) (multiplier * (y + (2 * solder_mask_clearance))) /* solder mask clearance */
                                );
                }
                else /* write pads perpendiclar to x-axis */
                {
                        fprintf (stdout, "Pads are drawn perpendicular to X-axis.\n");
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
                fprintf (fp, "\n");
                fprintf (fp, ")\n");
        }
        close (fp);
}


/*!
 * \brief Write a footprint based on the global variables.
 *
 * Function description:
 *
 */
int
write_footprint()
{
        /* Determine the units type */
        if (strcmp (footprint_units, "mils")) multiplier = 100.0;
        if (strcmp (footprint_units, "mils/100")) multiplier = 1.0;
        if (strcmp (footprint_units, "mm")) multiplier = (1000 / 25.4) * 100;
        /* Determine the footprint type */
        if (strcmp (footprint_type, "DIP")) type = DIP_TYPE;
        if (strcmp (footprint_type, "SIP")) type = SIP_TYPE;
        if (strcmp (footprint_type, "PGA")) type = PGA_TYPE;
        if (strcmp (footprint_type, "BGA")) type = BGA_TYPE;
        if (strcmp (footprint_type, "QFN")) type = QFN_TYPE;
        if (strcmp (footprint_type, "QFP")) type = QFP_TYPE;
        if (strcmp (footprint_type, "SO")) type = SO_TYPE;
        if (strcmp (footprint_type, "SMT")) type = SMT_TYPE;
        /* Depending on the footprint type write that type of footprint file
         */
        switch (type)
        {
                case SIP_TYPE:
                case DIP_TYPE:
                case PGA_TYPE:
                case BGA_TYPE:
                case QFN_TYPE:
                case QFP_TYPE:
                case SO_TYPE:
                case SMT_TYPE:
                {
                        write_smt_footprint();
                }
                default:
                {
                        fprintf (stdout, "Warning: wrong or non-existent footprint type entered.\n");
                }
        }
}

/* EOF */
