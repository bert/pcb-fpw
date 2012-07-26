/*!
 * \file src/gtk3/pcb-gfpw.c
 *
 * \author Copyright 2007 ... 2012 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Functions for pcb-gfpw (GTK3 UI).
 *
 * \todo
 * First run the glade files through gtk-builder-convert with this command:\n
 *   gtk-builder-convert pcb-gfpw.glade pcb-gfpw.xml \n
 *   gtk-builder-convert about_dialog.glade about_dialog.xml \n
 * \n
 *
 * Compile by using this command (those are backticks, not single
 * quotes):\n
 * \code
 *   gcc -Wall -g -o pcb-gfpw pcb-gfpw.c `pkg-config --cflags --libs gtk+-2.0` -export-dynamic
 * \endcode
 * Then execute the program using:\n
 * \code
 *   ./pcb-gfpw
 * \endcode
 *
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


#include "pcb-gfpw.h"
#include "about_dialog.h"


int
main (int argc, char *argv[])
{
    GtkWidget *about_dialog;

    gtk_init (&argc, &argv);
    about_dialog = create_about_dialog ();
    gtk_main ();
    return 0;
}


/* EOF */

