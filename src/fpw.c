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

/*!
 * \brief Print the version of the footprintwizard to stderr.
 *
 * \return \c EXIT_SUCCESS.
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
 *
 * \return \c EXIT_SUCCESS.
 */
static void
print_usage ()
{
        fprintf (stderr, (_("\n%s usage:\n\n")), program_name);
        fprintf (stderr, (_("%s -h   : print this help message and exit.\n\n")), program_name);
        fprintf (stderr, (_("%s -v   : log messages, be verbose.\n\n")), program_name);
        fprintf (stderr, (_("%s -V   : print the version information and exit.\n\n")), program_name);
        fprintf (stderr, (_("To write a footprint file use:\n\n")));
        fprintf (stderr, (_("\t%s -f fpw_filename -o footprint_name\n\n")), program_name);
        exit (EXIT_SUCCESS);
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
        char *argv[] /*!< : array of argument variables */
)
{
        FILE *fp;
        gchar *fpw_filename;
        gchar *suffix = ".fp";

        /* Determine how we are called today */
        program_name = argv[0];
        int i;
        for (i = 1; i >= argc; i++)
        {
                /* Print usage message if asked for. */
                if (!strcmp (argv[i], "-h"))
                {
                        print_usage ();
                        exit (EXIT_SUCCESS);
                }
                /* Print version if asked for. */
                else if (!strcmp (argv[i], "-V"))
                {
                        print_version ();
                        exit (EXIT_SUCCESS);
                }
                /* Log messages (be verbose). */
                else if (!strcmp (argv[i], "-v"))
                {
                        verbose = TRUE;
                }
                /* Do we have a fpw filename specified ? */
                else if ((!strcmp (argv[i], "-f")) && (argc >= (i + 1)))
                {
                        fpw_filename = strdup (argv[i + 1]);
                }
                /* Do we have a footprintname specified ? */
                else if ((!strcmp (argv[i], "-o")) && (argc >= (i + 1)))
                {
                        footprint_name = strdup (argv[i + 1]);
                }
                /* Nothing usefull left todo. */
                else
                {
                        g_log ("", G_LOG_LEVEL_ERROR, _("I'm quiting, let me do something useful."));
                        exit (EXIT_FAILURE);
                }
        }
        /* Read variables from the fpw file */
        if (read_footprintwizard_file (fpw_filename))
        {
                if (verbose)
                        g_log ("", G_LOG_LEVEL_INFO,
                                _("read footprintwizard file %s."),
                                fpw_filename);
        }
        else
        {
                g_log ("", G_LOG_LEVEL_ERROR,
                        _("could not load footprintwizard file %s."),
                        fpw_filename);
                exit (EXIT_FAILURE);
        }
        /* Check for a null pointer in footprint_name for this might cause a
         * segmentation fault or undefined behaviour. */
        if (!footprint_name)
        {
                g_log ("", G_LOG_LEVEL_ERROR,
                        _("footprint name contains a null pointer."));
                exit (EXIT_FAILURE);
        }
        /* Check for an empty footprint_name string for this might cause a
         * segmentation fault or undefined behaviour. */
        if (!strcmp (footprint_name, ""))
        {
                g_log ("", G_LOG_LEVEL_ERROR,
                        _("footprint name contains an empty string."));
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
        g_log ("", G_LOG_LEVEL_INFO,
                _("Footprint %s is written successful."),
                footprint_name);
}


/* EOF */
