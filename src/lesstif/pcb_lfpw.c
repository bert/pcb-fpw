/*!
 * \file src/lesstif/pcb_lfpw.c
 *
 * \author Copyright 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Lesstif program for the pcb footprintwizard (pcb-lfpw).
 *
 * pcb-lfpw (LesstifFootPrintWizard) is a program for the creation of footprint
 * files to be used by with the pcb layout application
 * (see http://pcb.sourgeforge.net) for the placement of parts in a pcb
 * layout.\n
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


#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include "xincludes.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <strings.h>    
#include <time.h>
#include <dirent.h>
#include <errno.h>

#include "../../config.h"
#include "main_window.h"
#include "about_dialog.h"
#include "pcb_lfpw.h"


#define LUI 1
/*!< Define whether this is a Lesstif User Interface (LUI) or not. */
#define GUI 0
/*!< Define whether this is a GTK User Interface (GUI) or not. */
#define CLI 0
/*!< Define whether this is a Command Line Interface (CLI) or not. */


/*!
 * \brief Parse the command line options.
 *
 * \return \c .
 */
int
lfpw_cmdline_options (int argc, char *argv[])
{
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
        while ((optc = getopt_long (argc, argv, "dhVvqq", opts, NULL)) != -1)
        {
                switch (optc)
                {
                        case 'd':
                                debug = TRUE;
                                break;
                        case 'h':
                                lfpw_print_usage ();
                                exit (EXIT_SUCCESS);
                        case 'V':
                                lfpw_print_version ();
                                exit (EXIT_SUCCESS);
                        case 'v':
                                verbose = TRUE;
                                break;
                        case 'q':
                                silent = TRUE;
                                verbose = FALSE; /* Just to be sure. */
                                break;
                        case '?':
                                lfpw_print_usage ();
                                exit (EXIT_FAILURE);
                        default:
                                fprintf (stderr, "unknown command line option encountered.\n");
                                lfpw_print_usage ();
                                exit (EXIT_FAILURE);
                }
        }
        if (optind < argc)
        {
                lfpw_print_usage ();
                exit (EXIT_FAILURE);
        }
        return (EXIT_SUCCESS);
}


/*!
 * \brief Print the usage message for the Lesstif footprintwizard to stderr.
 *
 * \return \c EXIT_SUCCESS.
 */
int
lfpw_print_usage (void)
{
        fprintf (stderr, "\npcb-lfpw usage and options:\n");
        fprintf (stderr, "\t --help \n");
        fprintf (stderr, "\t -? \n");
        fprintf (stderr, "\t -h        : print this help message and exit.\n\n");
        fprintf (stderr, "\t --verbose \n");
        fprintf (stderr, "\t -v        : log messages, be verbose.\n\n");
        fprintf (stderr, "\t --silent \n");
        fprintf (stderr, "\t --quiet \n");
        fprintf (stderr, "\t -q        : do not log messages, overrides --verbose.\n\n");
        fprintf (stderr, "\t --version \n");
        fprintf (stderr, "\t -V        : print the version information and exit.\n\n");
        fprintf (stderr, "\t --debug \n");
        fprintf (stderr, "\t -d        : turn on debugging output messages.\n\n");
        return (EXIT_SUCCESS);
}


/*!
 * \brief Print the version of the Lesstif footprintwizard to stderr.
 *
 * \return \c EXIT_SUCCESS.
 */
int
lfpw_print_version (void)
{
        fprintf (stderr, "\npcb-lfpw version %s\n", VERSION);
        fprintf (stderr, "(C) 2010 by Bert Timmerman.\n");
        fprintf (stderr, "This is free software; see the source for copying conditions.\n");
        fprintf (stderr, "There is NO warranty; not even for MERCHANTABILITY\n");
        fprintf (stderr, "or FITNESS FOR A PARTICULAR PURPOSE.\n\n");
        return (EXIT_SUCCESS);
}


/*!
 * \brief The Lesstif GUI for the footprintwizard.
 *
 * \return \c EXIT_SUCCESS if successfull.
 */
int 
main (int argc, char **argv)
{
        int status;
        Display *display;
        
        /* get command line options */
        status = lfpw_cmdline_options (argc, argv);
        if (status == 0)
        {
                /* Initialize toolkit and parse command line options. */
                XtToolkitInitialize ();
                XtSetLanguageProc (NULL, NULL, NULL);
                pcb_lfpw_app_context = XtCreateApplicationContext ();
                display = XtOpenDisplay
                (
                        pcb_lfpw_app_context,
                        NULL,
                        "pcb-lfpw",
                        "pcb-fpw",
                        NULL,
                        0,
                        &argc,
                        argv
                );
                create_main_window (argc, argv);
                /*! \todo debug with editres */
/*                XtAddEventHandler
                (
                        main_window,
                        (EventMask) 0,
                        True,
                        _XEditResCheckMessages,
                        NULL
                );
 */
                /* Create windows. */
                create_main_window (argc, argv);
                create_about_dialog (argc, argv);
                /* Enter the main loop. */
                XtAppMainLoop (pcb_lfpw_app_context);
        };
        return (EXIT_SUCCESS);
}


/* EOF */
