/*!
 * \file fpw.c
 * \author Copyright (C) 2007, 2008, 2009 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief fpw (FootPrintWizard) is a CLI program for the creation of
 * footprints.
 *
 * fpw (FootPrintWizard) is a program run from the Command Line Interface
 * (CLI) for the creation of footprints files.\n
 * These footprint files can be used by the pcb layout application
 * (see http://pcb.gpleda.org) to allow for the placement of parts on a
 * pcb layout.\n
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


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
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

#define GUI 0

#include "libfpw.c"
#include "packages.h"

gchar *program_name = NULL;
gchar *fpw_filename;


/*!
 * \brief Print the version of the footprintwizard to stderr.
 *
 * \return \c EXIT_SUCCESS.
 */
int
print_version ()
{
        fprintf (stderr, (_("\nfpw version %s\n")), FPW_VERSION);
        fprintf (stderr, (_("(C) 2007, 2008, 2009 by Bert Timmerman.\n")));
        fprintf (stderr, (_("This is free software; see the source for copying conditions.\n")));
        fprintf (stderr, (_("There is NO warranty; not even for MERCHANTABILITY\n")));
        fprintf (stderr, (_("or FITNESS FOR A PARTICULAR PURPOSE.\n\n")));
        return (EXIT_SUCCESS);
}


/*!
 * \brief Print the usage message for the footprintwizard to stderr.
 *
 * \return \c EXIT_SUCCESS.
 */
int
print_usage ()
{
        fprintf (stderr, (_("\nfpw usage and options:\n")));
        fprintf (stderr, (_("\t --help \n")));
        fprintf (stderr, (_("\t -? \n")));
        fprintf (stderr, (_("\t -h        : print this help message and exit.\n\n")));
        fprintf (stderr, (_("\t --verbose \n")));
        fprintf (stderr, (_("\t -v        : log messages, be verbose.\n\n")));
        fprintf (stderr, (_("\t --silent \n")));
        fprintf (stderr, (_("\t --quiet \n")));
        fprintf (stderr, (_("\t -q        : do not log messages, overrides --verbose.\n\n")));
        fprintf (stderr, (_("\t --version \n")));
        fprintf (stderr, (_("\t -V        : print the version information and exit.\n\n")));
        fprintf (stderr, (_("\t --format <fpw_footprintwizard filename> \n")));
        fprintf (stderr, (_("\t -f <fpw_footprintwizard filename>\n\n")));
        fprintf (stderr, (_("\t --output <footprint name> \n")));
        fprintf (stderr, (_("\t -o <footprint name>\n\n")));
        fprintf (stderr, (_("\t --debug \n")));
        fprintf (stderr, (_("\t -d        : turn on debugging output messages.\n\n")));
        return (EXIT_SUCCESS);
}


/*!
 * \brief The CLI for the footprintwizard.
 *
 * \return \c EXIT_SUCCESS.
 */
int
main
(
        int argc, /*!< : number of arguments on CLI */
        char **argv /*!< : array of argument variables */
)
{
        FILE *fp;
        gchar *suffix = ".fp";
        int debug = 0;

        /* Determine how we are called today */
        program_name = argv[0];
        static const struct option opts[] =
        {
                {"debug", no_argument, NULL, 'd'},
                {"help", no_argument, NULL, 'h'},
                {"version", no_argument, NULL, 'V'},
                {"verbose", no_argument, NULL, 'v'},
                {"quiet", no_argument, NULL, 'q'},
                {"silent", no_argument, NULL, 'q'},
                {"format", required_argument, NULL, 'f'},
                {"output", required_argument, NULL, 'o'},
                {0, 0, 0, 0}
        };
        int optc;
        while ((optc = getopt_long (argc, argv, "dVvqqf:o:", opts, NULL)) != -1)
        {
                switch (optc)
                {
                        case 'd':
                                debug = TRUE;
                                break;
                        case 'h':
                                print_usage ();
                                exit (EXIT_SUCCESS);
                        case 'V':
                                print_version ();
                                exit (EXIT_SUCCESS);
                        case 'v':
                                verbose = TRUE;
                                break;
                        case 'q':
                                silent = TRUE;
                                verbose = FALSE; /* Just to be sure. */
                                break;
                        case 'f':
                                fpw_filename = strdup (optarg);
                                if (debug)
                                        fprintf (stderr, "fpw filename = %s\n", fpw_filename);
                                break;
                        case 'o':
                                footprint_name = strdup (optarg);
                                if (debug)
                                        fprintf (stderr, "footprint name = %s\n", footprint_name);
                                break;
                        case '?':
                                print_usage ();
                                exit (EXIT_FAILURE);
                        default:
                                g_log ("", G_LOG_LEVEL_WARNING,
                                        _("unknown command line option encountered.\n"));
                                print_usage ();
                                exit (EXIT_FAILURE);
                }
        }
        if (optind < argc)
        {
                print_usage ();
                exit (EXIT_FAILURE);
        }
        /* Read variables from the fpw file */
        if (read_footprintwizard_file (fpw_filename))
        {
                if (verbose)
                {
                        g_log ("", G_LOG_LEVEL_INFO,
                                _("read footprintwizard file %s."),
                                fpw_filename);
                }
        }
        else
        {
                if ((verbose) && (!silent))
                {
                        g_log ("", G_LOG_LEVEL_ERROR,
                                _("could not load footprintwizard file %s."),
                                fpw_filename);
                }
                        exit (EXIT_FAILURE);
        }
        /* Check for a null pointer in footprint_name for this might cause a
         * segmentation fault or undefined behaviour. */
        if (!footprint_name)
        {
                if ((verbose) && (!silent))
                {
                        g_log ("", G_LOG_LEVEL_ERROR,
                                _("footprint name contains a null pointer."));
                }
                        exit (EXIT_FAILURE);
        }
        /* Check for an empty footprint_name string for this might cause a
         * segmentation fault or undefined behaviour. */
        if (!strcmp (footprint_name, ""))
        {
                if ((verbose) && (!silent))
                {
                        g_log ("", G_LOG_LEVEL_ERROR,
                                _("footprint name contains an empty string."));
                }
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
        write_footprint ();
        if (verbose)
        {
                g_log ("", G_LOG_LEVEL_INFO,
                _("Footprint %s is written successful."),
                footprint_name);
        }
}


/* EOF */
