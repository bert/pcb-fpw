/*!
 * \file register_functions.c
 * \author Copyright (C) 2007, 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Contains helper functions to register package dependant functions
 * for both fpw (CLI) and pcb-gfpw (GUI) versions of the pcb FootPrintWizard.
 *
 * This mechanism is copied from the pcb plug-in/HID mechanism. \n
 * The usual copyright disclaimer applies here and my thanks go to
 * DJ Delorie for creating this functionality in pcb. \n
 * The implementation is modified for the specific needs of pcb-gfpw/fpw. \n
 * fpw (FootPrintWizard) is a program for the creation of footprint files
 * to be used by the pcb layout application
 * (see http://pcb.sourgeforge.net) for the placement of parts in a pcb layout.\n\n
 *
 * This program is free software; you can redistribute it and/or modify\n
 * it under the terms of the GNU General Public License as published by\n
 * the Free Software Foundation; either version 2 of the License, or\n
 * (at your option) any later version.\n
 * \n
 * This program is distributed in the hope that it will be useful,\n
 * but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.\n
 * See the GNU General Public License for more details.\n
 * \n
 * You should have received a copy of the GNU General Public License\n
 * along with this program; if not, write to:\n
 * the Free Software Foundation, Inc.,\n
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.\n
 */


#ifndef _REGISTER_FUNCTIONS_
#define _REGISTER_FUNCTIONS_


/*!
 * \brief .
 */
typedef struct
{
        char *name;
                /*!< This is matched against fuction names. */
        int (*trigger_cb) (int argc, char **argv, int x, int y);
                /*!< Called when the function is called.  If this function returns
                 * non-zero, no further actions will be invoked for this event.
                 */
        const char *description;
                /*!< Short description that sometimes accompanies the name. */
        const char *syntax;
                /*!< Full allowed syntax; use \n to separate lines. */
} fpw_function_t;


/*!
 * \brief .
 */
typedef struct fpw_function_node_t
{
        struct fpw_function_node_t *next;
        fpw_function_t *functions;
        int n;
} fpw_function_node_t;

fpw_function_node_t *fpw_function_nodes = 0;

static int n_functions = 0;

static fpw_function_t *all_functions = 0;


static int
fpw_function_sort (const void *va, const void *vb)
{
        fpw_function_t *a = (fpw_function_t *) va;
        fpw_function_t *b = (fpw_function_t *) vb;
        return strcmp (a->name, b->name);
}


/*!
 * \brief Find the function as described in \c name in the register.
 * \return 0 if a NULL pointer is passed.
 */
fpw_function_t *
fpw_find_function (const char *name)
{
        fpw_function_node_t *gf;
        int i, n, lower, upper;

        if (name == NULL)
                return 0;
        if (all_functions == 0)
        {
                n = 0;
                all_functions = malloc (n_functions * sizeof (fpw_function_t));
                for (gf = fpw_function_nodes; gf; gf = gf->next)
                        for (i = 0; i < gf->n; i++)
                                all_functions[n++] = gf->functions[i];
                qsort (all_functions, n_functions, sizeof (fpw_function_t), fpw_function_sort);
        }
        lower = -1;
        upper = n_functions;
        /* printf("search function %s\n", name); */
        while (lower < upper - 1)
        {
                i = (lower + upper) / 2;
                n = strcmp (all_functions[i].name, name);
                /* printf("try [%d].%s, cmp %d\n", i, all_functions[i].name, n); */
                if (n == 0)
                        return all_functions + i;
                if (n > 0)
                        upper = i;
                else
                        lower = i;
        }
        for (i = 0; i < n_functions; i++)
                if (strcasecmp (all_functions[i].name, name) == 0)
                        return all_functions + i;
        g_log ("", G_LOG_LEVEL_WARNING,
                _("unknown function `%s'\n"), name);
        return 0;
}


/*!
 * \brief .
 */
int
fpw_functionv (const char *name, int argc, char **argv)
{
        int x = 0;
        int y = 0;
        int i;
        fpw_function_t *a;

        if (verbose && name)
        {
                fprintf (stderr, "Function: \033[34m%s(", name);
                for (i = 0; i < argc; i++)
                        fprintf (stderr, "%s%s", i ? "," : "", argv[i]);
                fprintf (stderr, ")\033[0m\n");
        }
        a = fpw_find_function (name);
        if (!a)
                return 1;
        return a->trigger_cb (argc, argv, x, y);
}


/*!
 * \brief .
 */
int
fpw_function (const char *name)
{
        return fpw_functionv (name, 0, 0);
}


#define FPW_CONCAT(a,b) a##b


/*!
 * \brief .
 */
void
fpw_register_functions (fpw_function_t * a, int n)
{
        fpw_function_node_t *gf;

        /* printf("%d functions registered\n", n); */
        gf = (fpw_function_node_t *) malloc (sizeof (fpw_function_node_t));
        gf->next = fpw_function_nodes;
        fpw_function_nodes = gf;
        gf->functions = a;
        gf->n = n;
        n_functions += n;
        if (all_functions)
        {
                free (all_functions);
                all_functions = 0;
        }
}


#define REGISTER_FUNCTIONS(a) FPW_CONCAT(void register_,a) ()\
{ fpw_register_functions(a, sizeof(a)/sizeof(a[0])); }


#endif /* _REGISTER_FUNCTIONS_ guard. */


/* EOF */
