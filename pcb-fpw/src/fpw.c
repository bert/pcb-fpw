/*!
 * \file fpw.c
 * \brief fpw (FootPrintWizard) is a program for the creation of footprints.
 *
 * fpw (FootPrintWizard) is a program run from the Command Line Interface
 * (CLI) for the creation of footprints files.\n
 * These footprint files can be used by the pcb layout application
 * (see http://pcb.sourgeforge.net) to allow for the placement of parts on a
 * pcb layout.\n
 *
 * \author Copyright (C) 2007 by Bert Timmerman <bert.timmerman@xs4all.nl>
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
#include <stdlib.h>

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
        fprintf (stderr, "\n%s version %s\n", program_name, FPW_VERSION);
        fprintf (stderr, "(C) 2007 by Bert Timmerman.\n\n");
        fprintf (stderr, "This is free software; see the source for copying conditions.\n");
        fprintf (stderr, "There is NO warranty; not even for MERCHANTABILITY\n");
        fprintf (stderr, "or FITNESS FOR A PARTICULAR PURPOSE.\n\n");
        exit (EXIT_SUCCESS);
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
        fprintf (stderr, "\n%s usage:\n", program_name);
        fprintf (stderr, "%s -h   : prints this help message and exits.\n\n", program_name);
        fprintf (stderr, "%s -V   : prints the version information and exits.\n\n", program_name);
        fprintf (stderr, "%s -f fpw_filename -o footprint_name   : reads the template file specified after -f and\n", program_name);
        fprintf (stderr, "                                          writes a footprint to the file specified after -o.\n\n");
        exit (EXIT_SUCCESS);
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
                exit (EXIT_FAILURE);
        }
        /* Read variables from the fpw file */
        read_footprintwizard_file();
        if (strcmp (footprint_units, "mils")) multiplier = 100.0;
        if (strcmp (footprint_units, "mils/100")) multiplier = 1.0;
        if (strcmp (footprint_units, "mm")) multiplier = (1000 / 25.4) * 100;
        /* If the footprint_filename contains a valid name that exists, use it */
        if (g_str_has_suffix (footprint_name, suffix))
        {
                /* Footprintname has a .fp suffix, do nothing */
                footprint_filename = g_strdup (footprint_name);
        }
        else
        {
                /* Footprintname has no .fp suffix, add a .fp suffix */
                footprint_filename = g_strconcat (footprint_name, ".fp", NULL);
        }
        write_footprint ();
        fprintf (stderr, "Footprint %s is written successful.", footprint_name);
        exit (EXIT_SUCCESS);
}

/* EOF */
