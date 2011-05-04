/*!
 * \file src/globals.h
 *
 * \author Copyright (C) 2007, 2008, 2009, 2010, 2011 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Contains global variables and structs for both fpw (CLI) and
 * pcb-gfpw (GUI) versions of the pcb FootPrintWizard.
 *
 * fpw (FootPrintWizard) is a program for the creation of footprint files
 * to be used by the pcb layout application
 * (see http://pcb.gpleda.org) for the placement of parts in a pcb
 * layout.\n
 * \n
 * The functions in libfpw are called by both the CLI version of the
 * FootPrintWizard (fpw) as well as the GUI version (pcb-gfpw).\n
 *
 * \todo Collect all global variables for the footprint into a single struct.\n
 * Switching to another preview will be easier by just switching pointers.
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


#ifndef __GLOBALS_INCLUDED__
#define __GLOBALS_INCLUDED__


/*!
 * \brief Some package types conforming to standard name space definitions.
 */
typedef enum packages
{
        NO_PACKAGE, /*!< For those living in the void. */
        BGA, /*!< Ball gate array package. */
        CAPA, /*!< Capacitor, Through Hole Non-Polarized Axial package. */
        CAPAD, /*!< Capacitor, Through Hole Non-Polarized,
                Axial Diameter, Horizontal Mounted package. */
        CAPAE, /*!< Capacitor, aluminium electrolytic package. */
        CAPC, /*!< Capacitor, chip package. */
        CAPM, /*!< Capacitor, molded, non-polarized package. */
        CAPMP, /*!< Capacitor, molded, polarized package. */
        CAPPR, /*!< Capacitor, through hole, polarized radial package. */
        CON_DIL, /*!< Connector package dual inline package numbering scheme. */
        CON_DIP, /*!< Connector package with dual inline numbering scheme. */
        CON_HDR, /*!< Connector package with header numbering scheme. */
        CON_SIL, /*! Single In Line connector package. */
        DIL, /*!< Dual inline package. */
        DIOAD, /*!< Through Hole Diode, Axial Diameter, Horizontal
                Mounted package. */
        DIOM, /*!< Diode, molded package. */
        DIOMELF, /*!< Diode, MELF package. */
        DIP, /*!< Dual Inline Package package. */
        DIPS, /*!< Dual Inline Package Socket package. */
        DO, /*!< Diode outline package. */
        HDRV, /*!< Pin Through Hole Vertical Header Connector package. */
        INDAD, /*!< Inductor, Through Hole Axial Diameter, Horizontal
                Mounted package. */
        INDC, /*!< Inductor, chip package. */
        INDM, /*!< Inductor, molded package. */
        INDP, /*!< Inductor, precision wire wound package. */
        MTGNP, /*!< Mounting Hole, Non Plated. */
        MTGP, /*!< Mounting Hole, Plated. */
        PGA, /*!< Pin gate array package. */
        PLCC, /*!< Plastic leadless chip carrier package. */
        QFN, /*!< Quad flat no-leads package. */
        QFP, /*!< Quad flat package. */
        RES, /*!< Resistor TH technology package. */
        RESAD, /*!< Resistor, Axial Diameter Horizontal Mounting. */
        RESAR, /*!< Resistor, Axial Rectangular, Horizontal Mounting. */
        RESC, /*!< Resistor, chip package. */
        RESM, /*!< Resistor, molded package. */
        RESMELF, /*!< Resistor, MELF package. */
        SIL, /*!< Single inline package. */
        SIP, /*!< Single inline package. */
        SO, /*!< Small outline package. */
        SOT, /*!< Small outline transistor package. */
        TO, /*!< Transistor outline package. */
        TO92, /*!< Transistor outline package. */
        TO220, /*!< Transistor outline package. */
        TO220S, /*!< Transistor outline package (with staggered pins). */
        TO220SW, /*!< Transistor outline package (standing with staggered pins). */
        TO220W /*!< Transistor outline package (standing). */
} package_t;

/*!
 * \brief Some units types.
 */
typedef enum units
{
        NO_UNITS, /*!< For those living in the void. */
        MIL, /*!< Imperial units type (Imperial standard "inch" divided by 1,000). */
        MIL_100, /*!< Imperial units type (Imperial standard "inch" divided by 100,000). */
        MM /*!< Metric units type (Metric standard "meter" divided by 1,000). */
} units_t;

/*!
 * \brief Some status types.
 */
typedef enum status
{
        NO_STATUS, /*!< For those living in the void. */
        EXPERIMENTAL, /*!< Experimental. */
        PRIVATE, /*!< Private (not published). */
        PUBLIC, /*!< Public (released). */
        STABLE /*! Stable (confirmed by peers or by usage in an actual pcb).*/
} status_t;

/*!
 * \brief Set of valid letter combinations for row identifiers for BGA and
 * PGA packages.
 */
char *row_letters[] =
{
        "A", "B", "C", "D", "E", "F", "G", "H", "J", "K",
        "L", "M", "N", "P", "R", "T", "U", "V", "W", "Y",
        "AA", "AB", "AC", "AD", "AE", "AF", "AG", "AH", "AJ", "AK",
        "AL", "AM", "AN", "AP", "AR", "AT", "AU", "AV", "AW", "AY",
        "BA", "BB", "BC", "BD", "BE", "BF", "BG", "BH", "BJ", "BK",
        "BL", "BM", "BN", "BP", "BR", "BT", "BU", "BV", "BW", "BY",
        "CA", "CB", "CC", "CD", "CE", "CF", "CG", "CH", "CJ", "CK",
        "CL", "CM", "CN", "CP", "CR", "CT", "CU", "CV", "CW", "CY"
};

/*!
 * \brief Some locations for pin #1 orientation.
 *
 * <pre>
 *   10    4   11
 *   +-----------+
 *  1|     |     |7
 *   |     |     |
 *  2+ --- 5 --- +8
 *   |     |     |
 *  3|     |     |9
 *   +-----------+
 *    12   6   13
 * </pre>
 */
typedef enum locations
{
        NO_LOCATION, /*!< For those living in the void.*/
        UPPER_LEFT, /*!< 1: Package has the upper left pin as pin #1.*/
        MIDDLE_LEFT, /*!< 2: Package has the middle left pin as pin #1.*/
        LOWER_LEFT, /*!< 3: Package has the lower left pin as pin #1.*/
        UPPER_MIDDLE, /*!< 4: Package has the upper middle pin as pin #1.*/
        MIDDLE_MIDDLE, /*!< 5: Package has the middle middle pin as pin #1.*/
        LOWER_MIDDLE, /*!< 6: Package has the lower middle pin as pin #1.*/
        UPPER_RIGHT, /*!< 7: Package has the upper right pin as pin #1.*/
        MIDDLE_RIGHT, /*!< 8: Package has the middle right pin as pin #1.*/
        LOWER_RIGHT, /*!< 9: Package has the lower right pin as pin #1.*/
        LEFT_TOP, /*!< 10: Package has the left topside pin as pin #1.*/
        RIGHT_TOP, /*!< 11: Package has the right topside pin as pin #1.*/
        LEFT_BOTTOM, /*!< 12: Package has the left bottomside pin as pin #1.*/
        RIGHT_BOTTOM /*!< 13: Package has the right bottomside pin as pin #1.*/
} location_t;

/*!
 * \brief Some pad shapes types.
 */
typedef enum pad_shapes
{
        NO_SHAPE,
        ROUND,
        SQUARE,
        OCTAGONAL,
        ROUND_ELONGATED
} pad_shapes_t;

/* Thin lines are not printed on silkscreen (in the real world) */
#define THIN_DRAW 1 /*!< Draw with thin lines. */

#define MIL_TO_MM 0.025400000 /*!< Convert mil to mm. */
#define MM_TO_MIL 39.37007874 /*!< Convert mm to mil. */


gboolean debug = FALSE;
        /*!< Global for being verbose on debugging information. */
gboolean silent = FALSE;
        /*!< Global for suppressing the logging of critical messages. */
gboolean verbose = FALSE;
        /*!< Global for being verbose on logging of information. */

FILE *fp;
        /*!< Global file pointer for the footprint file. */
gchar *fpw_pathname = NULL;
        /*!< Path to the footprintwizard file.*/
gchar *fpw_suffix = "fpw";
        /*!< Suffix of footprintwizard file. */
gchar *footprint_filename = NULL;
        /*!< Filename of footprint file. */
gchar *fp_suffix = "fp";
        /*!< Suffix of footprint file. */
gchar *footprint_name = NULL;
        /*!< Name of the footprint. */
gchar *footprint_type = NULL;
        /*!< Type of the footprint. */
package_t package_type = NO_PACKAGE;
        /*!< Type of the package. */
gchar *footprint_units = NULL;
        /*!< Units for the footprint dimensions. */
units_t units_type = NO_UNITS;
        /*!< Units (enumerated) for the footprint dimensions.\n
         * Initial value is \c NO_UNITS. */
gdouble multiplier;
        /*!< Multiplier to convert to mils/100. */
gchar *footprint_refdes = NULL;
        /*!< Default value of the refdes prefix. */
gchar *footprint_value = NULL;
        /*!< Default value of the package. */

gdouble package_body_length;
        /*!< Length dimension of the package body. */
gdouble package_body_width;
        /*!< Width dimension of the package body. */
gdouble package_body_height;
        /*!< Height dimension of the package body. */
gboolean package_is_radial = FALSE;
        /*!< Package has a radial body. */

gchar *footprint_author = NULL;
        /*!< Author of the footprint. */
gchar *footprint_dist_license = "GPL";
        /*!< Distribution license of the footprint. */
gchar *footprint_use_license = "unlimited";
        /*!< Usage license of the footprint. */
gchar *footprint_status = "Experimental";
        /*!< Status of the footprint. */
status_t status_type = NO_STATUS;
        /*!< Status (enumerated) for the footprint status.\n
         * Initial value is \c NO_STATUS. */
gboolean license_in_footprint = TRUE;
        /*!< Include a license text into the footprint file. */
gboolean attributes_in_footprint;
        /*!< Include the global values based on the entry values of the GUI
         * into the footprint file. */

gint number_of_pins;
        /*!< Number of pads/pins. */
gint number_of_columns;
        /*!< Number of columns. */
gint number_of_rows;
        /*!< Number of rows. */
gchar *pin_1_position = NULL;
        /*!< Position of number 1 pin. */
location_t pin1_location;
        /*!< Location of number 1 pin. */
gdouble pitch_x;
        /*!< Pitch in the X-direction. */
gdouble pitch_y;
        /*!< Pitch in the Y-direction. */
gint count_x;
        /*!< Number of pin/pads in the X-direction. */
gint count_y;
        /*!< Number of pin/pads in the Y-direction. */
gchar *pin_pad_exceptions_string = "";
        /*!< String with exceptions of existing pins or pads. */
gint number_of_exceptions = 0;
        /*!< Number of exceptions of existing pins or pads. */
gdouble pin_drill_diameter;
        /*!< Diameter of pin hole. */
gdouble pad_diameter;
        /*!< Outer diameter of pin pad (annulus). */
gdouble pad_length;
        /*!< Length of pad (parallel to Element X-axis). */
gdouble pad_width;
        /*!< Width of pad (perpendicular to Element X-axis). */
gchar *pad_shape;
        /*!< Shape of pads/pins. */
pad_shapes_t pad_shapes_type = NO_SHAPE;
        /*!< Shape of pads/pins (enumerated).\n
         * Initial value is \c NO_SHAPE. */
gint pin_pad_type;
        /*!< Type of pads/pins. */
gboolean pin1_square;
        /*!< Pin #1 is square. */
gdouble pad_solder_mask_clearance;
        /*!< Solder mask clearance of a pin/pad. */
gdouble pad_clearance;
        /*!< Clearance of a pin/pad. */

gboolean silkscreen_package_outline;
        /*!< Draw the package body outline on the silkscreen. */
gboolean silkscreen_indicate_1;
        /*!< Indicate the position of number 1 */
gdouble silkscreen_length;
        /*!< Silkscreen length (X-direction). */
gdouble silkscreen_width;
        /*!< Silkscreen width (Y-direction). */
gdouble silkscreen_line_width;
        /*!< Silkscreen line width. */

gboolean courtyard;
        /*!< Draw courtyard. */
gdouble courtyard_length;
        /*!< Courtyard length (X-direction). */
gdouble courtyard_width;
        /*!< Courtyard width (Y-direction). */
gdouble courtyard_line_width;
        /*!< Courtyard line width. */
gdouble courtyard_clearance_with_package;
        /*!< Courtyard clearance with package outline */

gboolean thermal;
        /*!< Draw thermal pad(s). */
gboolean thermal_nopaste;
        /*!< Thermal pad has no paste. */
gdouble thermal_length;
        /*!< Length of thermal pad. */
gdouble thermal_width;
        /*!< Width of thermal pad. */
gdouble thermal_solder_mask_clearance;
        /*!< Solder mask clearance of thermal pad. */
gdouble thermal_clearance;
        /*!< Clearance of a thermal pad. */

gboolean fiducial;
        /*!< Draw fiducials. */
gdouble fiducial_pad_diameter;
        /*!< Outer diameter of the fiducial pad. */
gdouble fiducial_pad_clearance;
        /*!< Clearance of a fiducial pad. */
gdouble fiducial_pad_solder_mask_clearance;
        /*!< Solder mask clearance of a fiducial pad. */

gboolean c1_state = TRUE;
        /*!< State of the top to bottom center-center distance radiobutton. */
gdouble c1;
        /*!< Top to bottom pads center-center distance. */
gboolean g1_state = FALSE;
        /*!< State of the top to bottom inner-inner distance radiobutton. */
gdouble g1;
        /*!< Top to bottom pads inner-inner distance. */
gboolean z1_state = FALSE;
        /*!< State of the top to bottom outer-outer distance radiobutton. */
gdouble z1;
        /*!< Top to bottom pads outer-outer distance. */

gboolean c2_state = TRUE;
        /*!< State of the left to right center-center distance radiobutton. */
gdouble c2;
        /*!< Left to right pads center-center distance. */
gboolean g2_state = FALSE;
        /*!< State of the left to right inner-inner distance radiobutton. */
gdouble g2;
        /*!< Left to right pads inner-inner distance. */
gboolean z2_state = FALSE;
        /*!< State of the left to right outer-outer distance radiobutton. */
gdouble z2;
        /*!< Left to right pads outer-outer distance. */
gchar *temp_dir;
        /*!< Temporary directory. */
gchar *work_dir;
        /*!< Current working directory. */
gchar *dummy = NULL;
        /*!< Every now and then the village-idot is needed ;-) */

#if GUI
        GtkWidget *widget;
                /*!< : the last used widget.*/
#endif


#endif /* __GLOBALS_INCLUDED__ */


/* EOF */
