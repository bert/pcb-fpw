/*!
 * \file src/register_functions.h
 *
 * \author Copyright (C) 2007, 2008, 2009, 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Header file for helper functions to register package dependant functions
 * for both fpw (CLI) and pcb-gfpw (GUI) versions of the pcb FootPrintWizard.
 *
 * This mechanism is copied from the pcb plug-in/HID mechanism.\n
 * The usual copyright disclaimer applies here and my thanks go to
 * DJ Delorie for creating this functionality in pcb.\n
 * The implementation is modified for the specific needs of pcb-gfpw/fpw.\n
 * fpw (FootPrintWizard) is a program for the creation of footprint files
 * to be used by the pcb layout application
 * (see http://pcb.sourgeforge.net) for the placement of parts in a pcb layout.\n
 * \n
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


#ifndef __REGISTER_FUNCTIONS__
#define __REGISTER_FUNCTIONS__


/*!
 * \brief .
 */
typedef struct
{
        char *name;
                /*!< This name is matched against fuction names.*/
        int (*trigger_cb) (int argc, char **argv, int x, int y);
                /*!< Is called when the function is called.\n
                 * If this function returns non-zero, no further actions
                 * will be invoked for this event.
                 */
        const char *description;
                /*!< This is a short description that sometimes
                 * accompanies the name.*/
        const char *syntax;
                /*!< Full allowed syntax; use \\n to separate lines.*/
} fpw_function_t;


/*!
 * \brief .
 */
typedef struct fpw_function_node_t
{
        struct fpw_function_node_t *next;
                /*!< The next function node.*/
        fpw_function_t *functions;
                /*!< The next function.*/
        int n;
                /*!< The number of function nodes ?.*/
} fpw_function_node_t;


fpw_function_node_t *fpw_function_nodes = 0;


static int n_functions = 0;


static fpw_function_t *all_functions = 0;


static int fpw_function_sort (const void *va, const void *vb);
fpw_function_t * fpw_find_function (const char *name);
int fpw_functionv (const char *name, int argc, char **argv);
int fpw_function (const char *name);

#define FPW_CONCAT(a,b) a##b

void fpw_register_functions (fpw_function_t * a, int n);

#define REGISTER_FUNCTIONS(a) FPW_CONCAT(void register_,a) ()\
{ fpw_register_functions(a, sizeof(a)/sizeof(a[0])); }


#endif /* __REGISTER_FUNCTIONS__ */


/* EOF */
