/*!
 * \file fpw.c
 * \author Copyright (C) 2007, 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief fpw (FootPrintWizard) is a CLI program for the creation of
 * footprints.
 *
 * fpw (FootPrintWizard) is a program run from the Command Line Interface
 * (CLI) for the creation of footprints files.\n
 * These footprint files can be used by the pcb layout application
 * (see http://pcb.sourgeforge.net) to allow for the placement of parts on a
 * pcb layout.\n
 *
 * This program is free software; you can redistribute it and/or modify\n
 * it under the terms of the GNU General Public License as published by\n
 * the Free Software Foundation; either version 2 of the License, or\n
 * (at your option) any later version.\n
 * \n
 * This program is distributed in the hope that it will be useful,\n
 * but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.\n
 * \n
 * You should have received a copy of the GNU General Public License\n
 * along with this program; if not, write to:\n
 * the Free Software Foundation, Inc.,\n
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\n
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

/*
 * Standard gettext macros.
 */
#ifdef ENABLE_NLS
#  include <libintl.h>
#  undef _
#  define _(String) dgettext (PACKAGE, String)
#  define Q_(String) g_strip_context ((String), gettext (String))
#  ifdef gettext_noop
#    define N_(String) gettext_noop (String)
#  else
#    define N_(String) (String)
#  endif
#else
#  define textdomain(String) (String)
#  define gettext(String) (String)
#  define dgettext(Domain,Message) (Message)
#  define dcgettext(Domain,Message,Type) (Message)
#  define bindtextdomain(Domain,Directory) (Domain)
#  define _(String) (String)
#  define Q_(String) g_strip_context ((String), (String))
#  define N_(String) (String)
        bindtextdomain (GETTEXT_PACKAGE, PACKAGE_LOCALE_DIR);
        bind_textdomain_codeset (GETTEXT_PACKAGE, "UTF-8");
        textdomain (GETTEXT_PACKAGE);
#endif

#include "libfpw.c"

gchar *program_name = NULL;

/*!
 * \brief Print the version of the footprintwizard to stderr.
 */
static void
print_version ()
{
        fprintf (stderr, (_("\n%s version %s\n")), program_name, FPW_VERSION);
        fprintf (stderr, (_("(C) 2007, 2008 by Bert Timmerman.\n")));
        fprintf (stderr, (_("This is free software; see the source for copying conditions.\n")));
        fprintf (stderr, (_("There is NO warranty; not even for MERCHANTABILITY\n")));
        fprintf (stderr, (_("or FITNESS FOR A PARTICULAR PURPOSE.\n\n")));
        exit (EXIT_SUCCESS);
}


/*!
 * \brief Print the usage message for the footprintwizard to stderr.
 */
static void
print_usage ()
{
        fprintf (stderr, (_("\n%s usage:\n")), program_name);
        fprintf (stderr, (_("%s -h   : print this help message and exit.\n\n")), program_name);
        fprintf (stderr, (_("%s -V   : print the version information and exit.\n\n")), program_name);
        fprintf (stderr, (_("To write a footprint file use:\n\n")));
        fprintf (stderr, (_("\t%s -f fpw_filename -o footprint_name\n\n")), program_name);
        exit (EXIT_SUCCESS);
}


/*!
 * \brief The CLI for the footprintwizard.
 */
int
main
(
        int argc, /*!< number of arguments on CLI */
        char *argv[] /*!< array of argument variables */
)
{
        FILE *fp;
        gchar *fpw_filename;
        gchar *suffix = ".fp";

        /* Today we feel like a CLI application ! */
        gui = FALSE;
        /* Determine how we are called today */
        program_name = argv[0];
        /* Print usage message if asked for */
        if (argc > 1 && strcmp (argv[1], "-h") == 0)
        {
                print_usage ();
        }
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
                fprintf (stderr, (_("I'm quiting, let me do something useful.\n")));
                exit (EXIT_FAILURE);
        }
        /* Read variables from the fpw file */
        if (read_footprintwizard_file (fpw_filename))
        {
                fprintf (stderr, (_("SUCCESS: reading footprintwizard file %s.\n")),
                        fpw_filename);
        }
        else
        {
                fprintf (stderr, (_("ERROR: reading footprintwizard file %s.\n")),
                        fpw_filename);
                exit (EXIT_FAILURE);
              }
        /* Check for a null pointer in footprint_units for this might cause a
         * segmentation fault or undefined behaviour. */
        if (!footprint_units)
        {
                fprintf (stderr, (_("ERROR: footprint units contains a null pointer.\n")));
                exit (EXIT_FAILURE);
        }
        /* Check for an empty footprint_units string for this might cause a
         * segmentation fault or undefined behaviour. */
        if (!strcmp (footprint_units, ""))
        {
                fprintf (stderr, (_("ERROR: footprint units contains an empty string.\n")));
                exit (EXIT_FAILURE);
        }
        /* Check for a null pointer in pad_shape for this might cause a
         * segmentation fault or undefined behaviour. */
        if (!pad_shape)
        {
                fprintf (stderr, (_("ERROR: pad shape contains a null pointer.\n")));
                exit (EXIT_FAILURE);
        }
        /* Check for an empty pad_shape string for this might cause a
         * segmentation fault or undefined behaviour. */
        if (!strcmp (pad_shape, ""))
        {
                fprintf (stderr, (_("ERROR: pad shape contains an empty string.\n")));
                exit (EXIT_FAILURE);
        }
        /* Check for a null pointer in footprint_name for this might cause a
         * segmentation fault or undefined behaviour. */
        if (!footprint_name)
        {
                fprintf (stderr, (_("ERROR: footprint name contains a null pointer.\n")));
                exit (EXIT_FAILURE);
        }
        /* Check for an empty footprint_name string for this might cause a
         * segmentation fault or undefined behaviour. */
        if (!strcmp (footprint_name, ""))
        {
                fprintf (stderr, (_("ERROR: footprint name contains an empty string.\n")));
                exit (EXIT_FAILURE);
        }
        /* If the footprint_filename contains a valid footprintname, use it. */
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
        /* Determine the multiplier based upon the units type */
        if (strcmp (footprint_units, "mils"))
                multiplier = 100.0;
        else if (strcmp (footprint_units, "mils/100"))
                multiplier = 1.0;
        else if (strcmp (footprint_units, "mm"))
                multiplier = (1000 / 25.4) * 100;
        else
        {
                fprintf (stderr, (_("ERROR: footprint units contains an unknown units type.\n")));
                exit (EXIT_FAILURE);
        }
        /* Determine the pad shape type, default is a circular pad */
        if (!strcmp (pad_shape, "circular pad"))
                g_strconcat (pin_pad_flags, "", NULL);
        else if (!strcmp (pad_shape, "rectangular pad"))
                g_strconcat (pin_pad_flags, "square", NULL);
        else if (!strcmp (pad_shape, "octagonal pad"))
                g_strconcat (pin_pad_flags, "octagon", NULL);
        else if (!strcmp (pad_shape, "rounded pad, elongated"))
                g_strconcat (pin_pad_flags, "", NULL);
        else
        {
                fprintf (stderr, (_("ERROR: pad shape contains an unknown pad shape type.\n")));
                exit (EXIT_FAILURE);
        }
        /* Determine the package type */
        if (!strcmp (footprint_type, "BGA"))
        {
                package_type = BGA;
        }
        else if (!strcmp (footprint_type, "CAPC"))
        {
                package_type = CAPC;
        }
        else if (!strcmp (footprint_type, "DIL"))
        {
                package_type = DIL;
        }
        else if (!strcmp (footprint_type, "DIP"))
        {
                package_type = DIP;
        }
        else if (!strcmp (footprint_type, "INDC"))
        {
                package_type = INDC;
        }
        else if (!strcmp (footprint_type, "PGA"))
        {
                package_type = PGA;
        }
        else if (!strcmp (footprint_type, "QFN"))
        {
                package_type = QFN;
                fprintf (stderr, (_("ERROR: footprint type %s not yet implemented.\n")),
                        footprint_type);
                exit (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "QFP"))
        {
                package_type = QFP;
                fprintf (stderr, (_("ERROR: footprint type %s not yet implemented.\n")),
                        footprint_type);
                exit (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "RESC"))
        {
                package_type = RESC;
        }
        else if (!strcmp (footprint_type, "SIL"))
        {
                package_type = SIP;
                fprintf (stderr, (_("ERROR: footprint type %s not yet implemented.\n")),
                        footprint_type);
                exit (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "SIP"))
        {
                package_type = SIP;
                fprintf (stderr, (_("ERROR: footprint type %s not yet implemented.\n")),
                        footprint_type);
                exit (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "SO"))
        {
                package_type = SO;
                fprintf (stderr, (_("ERROR: footprint type %s not yet implemented.\n")),
                        footprint_type);
                exit (EXIT_FAILURE);
        }
        else if (!strcmp (footprint_type, "TO92"))
        {
                package_type = TO92;
        }
        else
        {
                fprintf (stderr, (_("ERROR: unknown or not yet implemented footprint type entered.\n")));
                exit (EXIT_FAILURE);
        }
        write_footprint ();
        fprintf (stderr, (_("Footprint %s is written successful.")),
                footprint_name);
}

/* EOF */
