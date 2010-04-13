/*!
 * \file pcb-lfpw.c
 * \author Copyright 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
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

#include <X11/StringDefs.h>
#include <Xm/Xm.h>
#include <Xm/DialogS.h>
#include <Xm/MwmUtil.h>
#include <X11/Xmu/Editres.h>
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
#include "pcb-lfpw.h"
#include "toplevel.c"


#define LUI 1
/*!< Define whether this is a Lesstif User Interface (LUI) or not. */
#define GUI 0
/*!< Define whether this is a GTK User Interface (GUI) or not. */
#define CLI 0
/*!< Define whether this is a Command Line Interface (CLI) or not. */


XtAppContext appcontext;
Widget top_level_window = NULL;
        /*!< global main pcb-lfpw window */
Widget about_dialog = NULL;   
        /*!< about_dialog window */
char *fpw_filename = NULL;
char *program_name = NULL;
Boolean debug = 0;
        /*!< Global for being verbose on debugging information. */
Boolean silent = 0;
        /*!< Global for suppressing the logging of critical messages. */
Boolean verbose = 0;
        /*!< Global for being verbose on logging of information. */


/*!
 * \brief Print the version of the Lesstif footprintwizard to stderr.
 *
 * \return \c EXIT_SUCCESS.
 */
int
print_version ()
{
        fprintf (stderr, "\npcb-lfpw version %s\n", VERSION);
        fprintf (stderr, "(C) 2010 by Bert Timmerman.\n");
        fprintf (stderr, "This is free software; see the source for copying conditions.\n");
        fprintf (stderr, "There is NO warranty; not even for MERCHANTABILITY\n");
        fprintf (stderr, "or FITNESS FOR A PARTICULAR PURPOSE.\n\n");
        return (EXIT_SUCCESS);
}


/*!
 * \brief Print the usage message for the Lesstif footprintwizard to stderr.
 *
 * \return \c EXIT_SUCCESS.
 */
int
print_usage ()
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
 * \brief Parse the command line options.
 *
 * \return \c .
 */
static
int cmdline_options (int argc, char *argv[])
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
                        case '?':
                                print_usage ();
                                exit (EXIT_FAILURE);
                        default:
                                fprintf (stderr, "unknown command line option encountered.\n");
                                print_usage ();
                                exit (EXIT_FAILURE);
                }
        }
        if (optind < argc)
        {
                print_usage ();
                exit (EXIT_FAILURE);
        }
}


/*!
 * \brief Parse the command line options.
 *
 * \return \c .
 */
int 
main (int argc, char **argv)
{
        Arg args[5];
        char title[124];
        int n;
        int status;

        /* get command line options */
        status = cmdline_options (argc, argv);
        if (status == 0)
        {
                /* Initialize toolkit and parse command line options. */
                top_level_window = XtVaAppInitialize (&appcontext,
                        "pcb-lfpw",
                        NULL,
                        0,
                        &argc,
                        argv,
                        NULL);
                /* to debug with editres */
//                XtAddEventHandler (top_level_window, (EventMask) 0, True, _XEditResCheckMessages, NULL);
                /* simplify later name changes by always using malloc */
                program_name = XtNewString ("pcb-lfpw");
                fpw_filename = XtNewString ("no_name.fpw");
                /* title in main window bar */
                strcpy (title, "pcb-lfpw FootPrint Wizard");
                n = 0;
                XtSetArg (args[n], XmNtitle, title);
                n++;
                XtSetArg (args[n], XmNiconName, "gFootprintWizard.xpm");
                n++;
                XtSetValues (top_level_window, args, n);
                build_gui (top_level_window);
                XtRealizeWidget (top_level_window);
                XtAppMainLoop (appcontext);
        };
}


/* EOF */
