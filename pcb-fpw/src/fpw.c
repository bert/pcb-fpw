/*!
 * \file fpw.c
 * \author Copyright (C) 2007 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief fpw (FootPrintWizard) is a program for the creation of footprint
 * files used by the pcb layout application (see http://pcb.sourgeforge.net)
 * for the placement of parts in a pcb layout.
 */


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

#include <gtk/gtk.h>

#include "libfpw.c"


gchar *program_name = NULL;

/*!
 * \brief Print the version of the footprintwizard to stderr.
 *
 * Function description:
 *
 */
static void
print_version ()
{
        fprintf (stderr, "\nfpw version %s\n", VERSION);
        fprintf (stderr, "(C) 2007 by Bert Timmerman.\n\n");
        exit (0);
}


/*!
 * \brief Print the usage message for the footprintwizard to stderr.
 *
 * Function description:
 *
 */
static void
print_usage ()
{
        fprintf (stderr, "\nfpw usage:\n");
        fprintf (stderr, "fpw -h                             : prints this help message and exits.\n");
        fprintf (stderr, "fpw -V                             : prints the version and exits.\n");
        fprintf (stderr, "fpw -f fpw_filename -o footprint_name  : prints the version and exits.\n\n");
        exit (0);
}


/*!
 * \brief The CLI for the footprintwizard.
 *
 * Function description:
 *
 */
int
main
(
        int argc, /*!< number of arguments on CLI */
        char *argv[] /*!< array of argument variables */
)
{
        FILE *fp;
        gchar *fpw_filename = NULL;
        gchar *dummy_footprint_name = NULL;
        gchar *suffix = ".fp";

        /* Determine how we are called today */
        program_name = argv[0];
        /* Print usage message if asked for */
        if (argc > 1 && strcmp (argv[1], "-h") == 0)
                print_usage ();
        /* Print version if asked for */
        if (argc > 1 && strcmp (argv[1], "-V") == 0)
                print_version ();
        if (argc > 3 &&
                strcmp (argv[1], "-f") == 0 &&
                strcmp (argv[3], "-o") == 0)
        {
                fpw_filename = strdup (argv[2]);
                footprint_name = strdup (argv[4]);
        }
        else
        {
                fprintf (stderr, "I'm quiting, let me do something useful.\n");
                exit (0);
        }
        /* If the footprint_filename contains a valid
         * name that exists, read variables from the fpw file */
        if (g_str_has_suffix (footprint_name, suffix))
        {
                /* Footprintname has a .fp suffix, do nothing */
                footprint_filename = g_strdup (footprint_name);
        }
        else
        {
                /* Footprintname has no .fp suffix, add a .fpw suffix */
                footprint_filename = g_strconcat (footprint_name, ".fp", NULL);
        }
        /* Get global variables from footprintwizard file with .fpw suffix */
        if (fp = g_fopen (fpw_filename, "r"))
        {
                fscanf (fp, "%s\n", footprint_filename);
                fscanf (fp, "%s\n", dummy_footprint_name); /* do not (re)use this value ! */
                fscanf (fp, "%s\n", footprint_type);
                fscanf (fp, "%s\n", footprint_units);
                fscanf (fp, "%s\n", n1_pos);
                fscanf (fp, "%s\n", pad_shape);
                fscanf (fp, "%d\n", n);
                fscanf (fp, "%d\n", n_col);
                fscanf (fp, "%d\n", n_row);
                fscanf (fp, "%f\n", x);
                fscanf (fp, "%f\n", y);
                fscanf (fp, "%f\n", d_pad);
                fscanf (fp, "%f\n", d_hole);
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
        }
        close (fp);
        if (strcmp (footprint_units, "mils")) multiplier = 100.0;
        if (strcmp (footprint_units, "mils/100")) multiplier = 1.0;
        if (strcmp (footprint_units, "mm")) multiplier = (1000 / 25.4) * 100;
        /* Pass control to libfpw */
        write_footprint ();
        /* If we get here, control is passed back from libfpw */
        fprintf (stderr, "Footprint %s is written successful.", footprint_name);
}

/* EOF */

