/*!
 * \file globals.h
 * \author Copyright (C) 2008 by Bert Timmerman <bert.timmerman@xs4all.nl>
 * \brief Contains global variables and structs for both fpw (CLI) and
 * pcb-gfpw (GUI) versions of the pcb FootPrintWizard.
 *
 * fpw (FootPrintWizard) is a program for the creation of footprint files
 * to be used by the pcb layout application
 * (see http://pcb.sourgeforge.net) for the placement of parts in a pcb layout.\n\n
 * The functions in libfpw are called by both the CLI version of the
 * FootPrintWizard (fpw) as well as the GUI version (pcb-gfpw).\n
 *
 * \todo Collect all global variables for the footprint into a single struct.\n
 * Switching to another preview will be easier by just switching pointers.
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


/*!
 * \brief Some package types conforming to IPC name space definitions.
 */
typedef enum packages
{
        NO_PACKAGE, /*!< For those living in the void. */
        BGA, /*!< Ball gate array package. */
        CAPAE, /*!< Capacitor, aluminium electrolytic package. */
        CAPC, /*!< Capacitor, chip package. */
        CAPM, /*!< Capacitor, molded, non-polarized package. */
        CAPMP, /*!< Capacitor, molded, polarized package. */
        CON_DIL, /*!< Connector package dual inline package numbering scheme. */
        CON_DIP, /*!< Connector package with dual inline numbering scheme. */
        CON_HDR, /*!< Connector package with header numbering scheme. */
        DIL, /*!< Dual inline package. */
        DIOM, /*!< Diode, molded package. */
        DIOMELF, /*!< Diode, MELF package. */
        DIP, /*!< Dual inline package. */
        DO, /*!< Diode outline package. */
        INDC, /*!< Inductor, chip package. */
        INDM, /*!< Inductor, molded package. */
        INDP, /*!< Inductor, precision wire wound package. */
        PGA, /*!< Pin gate array package. */
        PLCC, /*!< Plastic leadless chip carrier package. */
        QFN, /*!< Quad flat no-leads package. */
        QFP, /*!< Quad flat package. */
        RES, /*!< Resistor TH technology package. */
        RESC, /*!< Resistor, chip package. */
        RESM, /*!< Resistor, molded package. */
        RESMELF, /*!< Resistor, MELF package. */
        SIL, /*!< Single inline package. */
        SIP, /*!< Single inline package. */
        SO, /*!< Small outline package. */
        SOT, /*!< Small outline transistor package. */
        TO, /*!< Transistor outline package. */
        TO92, /*!< Transistor outline package. */
        TO220 /*!< Transistor outline package. */
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
 * \brief Some units types.
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
        NO_LOCATION, /*!< For those living in the void. */
        UPPER_LEFT, /*!< Package has the upper left pin as pin #1. */
        MIDDLE_LEFT, /*!< Package has the middle left pin as pin #1. */
        LOWER_LEFT, /*!< Package has the lower left pin as pin #1. */
        UPPER_MIDDLE, /*!< Package has the upper middle pin as pin #1. */
        MIDDLE_MIDDLE, /*!< Package has the middle middle pin as pin #1. */
        LOWER_MIDDLE, /*!< Package has the lower middle pin as pin #1. */
        UPPER_RIGHT, /*!< Package has the upper right pin as pin #1. */
        MIDDLE_RIGHT, /*!< Package has the middle right pin as pin #1. */
        LOWER_RIGHT, /*!< Package has the lower right pin as pin #1. */
        LEFT_TOP, /*!< Package has the left topside pin as pin #1. */
        RIGHT_TOP, /*!< Package has the right topside pin as pin #1. */
        LEFT_BOTTOM, /*!< Package has the left bottomside pin as pin #1. */
        RIGHT_BOTTOM /*!< Package has the right bottomside pin as pin #1. */
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


gboolean verbose = TRUE;
        /*!< Global file pointer for being verbose or not. */

FILE *fp;
        /*!< Global file pointer for the footprint file. */
gchar *fpw_pathname = NULL;
        /*!< Path to the footprintwizard file */
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
gboolean license_in_footprint;
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
gchar *pin_pad_exceptions_string;
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
gchar *pin_pad_flags = NULL;
        /*!< Flags of pins/pads. */
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

gchar *dummy = NULL;
        /*!< Every now and then the village-idot is needed ;-) */


/*
 * Now follows some definitions and typedefs copied from pcb.
 *
 * Do not change the following definitions even if they're not very nice.
 * It allows us to have functions act on these "base types" and not need to
 * know what kind of actual object they're working on.
 * In the future this may simplify the conversion of pcb-gfpw from a
 * stand-alone application to a pcb plug-in.
 */

#define MAX_LAYER 16
/*!< Maximum number of layers, check the pcb source code for more changes,
 * a *lot* more changes.
 */
#define MAX_ELEMENTNAMES 3
/*!< Maximum number of supported names of an element. */
#define EMARK_SIZE 1000
/*!< Size of diamond element mark. */
#define MIN_TEXTSCALE 10
/*!< Scaling of text objects in percent */
#define MAX_TEXTSCALE 10000
/*!< Scaling of text objects in percent */

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

/* Pin or pad types / Object flag values */
#define CLEAR 0x0000
        /*!< Default (round) pad. */
#define PIN 0x0001
        /*!< If set, this object is a pin.\n
         * This flag is for internal use only. */
#define VIA 0x0002
        /*!< Likewise, for vias. */
#define HOLE 0x0008
        /*!< For pins and vias, this flag means that the pin or via is a hole
         * without a copper annulus. */
#define PININPOLY 0x0010
        /*!< For pins and pads, this flag is used internally to indicate that
         * the pin or pad overlaps a polygon on some layer. */
#define SHOWNAME 0x0020
        /*!< For elements, when set the names of pins are shown. */
#define ONSOLDER 0x0080
        /*!< For elements and pads, indicates that they are on the solder
         * side. */
#define SQUARE 0x0100
        /*!< For pins and pads, indicates a square (vs round) pin/pad. */
#define WARN 0x0200
        /*!< For pins, vias, and pads, set to indicate a warning. */
#define OCTAGON 0x0800
        /*!< Draw pins and vias as octagons. */
#define LOCK 0x2000
        /*!< Set for locked objects. */
#define EDGE2 0x4000
        /*!< For pads, indicates that the second point is closer to the
         * edge.\n
         * For pins, indicates that the pin is closer to a horizontal edge
         * and thus pinout text should be vertical. */
#define MARKER 0x8000
        /*!< Marker used internally to avoid revisiting an object. */
#define NOPASTE 0x10000
        /*!< For pads, set to prevent a solderpaste stencil opening for the
         * pad.\n
         * Primarily used for pads used as fiducials. */
static int ID = 1;
        /*!< Current object ID;\n
         * incremented after each creation of an object. */

/*!
 * \brief Some directions.
 */
typedef enum
{
        NORTH,
        EAST,
        SOUTH,
        WEST
} direction_t;

typedef int LocationType;
typedef int BDimension; /*!< big dimension */
typedef unsigned int Cardinal;
typedef char Boolean;
typedef char *String;
typedef short Position;
typedef short Dimension;
typedef unsigned char BYTE;

/*!
 * \brief A bounding box. */
typedef struct
{
        LocationType X1; /*!< X-value of the upper left corner coordinate. */
        LocationType Y1; /*!< Y-value of the upper left corner coordinate. */
        LocationType X2; /*!< X-value of the lower right corner coordinate. */
        LocationType Y2; /*!< Y-value of the lower right corner coordinate. */
} BoxType, *BoxTypePtr;

/*!
 * \brief A Flag type.
 *
 * This structure must be simple-assignable for now.
 */
typedef struct
{
  unsigned long f; /*!< Generic flags */
  unsigned char t[(MAX_LAYER + 1) / 2]; /*!< Thermals */
} FlagType, *FlagTypePtr;

/*!
 * \brief An Attribute type.
 */
typedef struct
{
        char *name;
        char *value;
} AttributeType, *AttributeTypePtr;

/*!
 * \brief An Attribute list.
 */
typedef struct
{
        int Number;
        int Max;
        AttributeType *List;
} AttributeListType, *AttributeListTypePtr;

/*!
 * \brief A line or polygon point.
 *
 * Point type can be cast as BoxType
 */
typedef struct
{
  LocationType X;
  LocationType Y;
  LocationType X2;
  LocationType Y2;
  long int ID;
} PointType, *PointTypePtr;

/*!
 * Any object that uses the "object flags" defined in pcb/src/const.h,
 * or exists as an object on the pcb, MUST be defined using this as the first
 * fields, either directly or through ANYLINEFIELDS.
 */
#define ANYOBJECTFIELDS \
        BoxType BoundingBox; \
        long int ID; \
        FlagType Flags; \
        struct LibraryEntryType *net

/*!
 * Lines, pads, and rats all use this so they can be cross-cast.
 */
#define ANYLINEFIELDS \
        ANYOBJECTFIELDS; \
        BDimension Thickness; \
        BDimension Clearance; \
        PointType Point1; \
        PointType Point2

/*!
 * \brief Holds information of any line object type.
 */
typedef struct
{
        ANYLINEFIELDS;
} AnyLineObjectType, *AnyLineObjectTypePtr;

/*!
 * ]\brief Holds information about one line entity.
 */
typedef struct
{
        ANYLINEFIELDS;
        char *Number;
} LineType, *LineTypePtr;

/*!
 * \brief Holds information about one mark entity.
 */
typedef struct
{
        Boolean status;
        long int X; /*!< X-value of origin. */
        long int Y; /*!< Y-value of origin. */
} MarkType, *MarkTypePtr;

/*!
 * \brief Holds information about one text entity.
 */
typedef struct
{
        ANYOBJECTFIELDS;
        BDimension Scale; /*!< text scaling in percent. */
        LocationType X; /*!< X-value of origin (insertion point). */
        LocationType Y; /*!< Y-value of origin (insertion point). */
        BYTE Direction; /*!< Text direction. */
        char *TextString; /*!< String value. */
        void *Element;
} TextType, *TextTypePtr;

/*!
 * \brief Holds information about one arc entity.
 */
typedef struct
{
        ANYOBJECTFIELDS;
        BDimension Thickness; /*!< Trace width. */
        BDimension Clearance; /*!< Clearance with polygons. */
        LocationType Width; /*!< Length of axis. */
        LocationType Height; /*!< Heigth of axis. */
        LocationType X; /*!< X-value of center coordinate. */
        LocationType Y; /*!< Y-value of center coordinate. */
        long int StartAngle; /*!< limiting angle in degrees */
        long int Delta; /*!< limiting angle in degrees */
} ArcType, *ArcTypePtr;

/*!
 * \brief Holds information about one SMD pad entity.
 */
typedef struct
{
        ANYLINEFIELDS;
        BDimension Mask;
        char *Name; /*!< Pad name. */
        char *Number; /*!< 'Line' */
        void *Element;
        void *Spare;
} PadType, *PadTypePtr;

/*!
 * \brief Holds information about one through hole pin entity.
 */
typedef struct
{
        ANYOBJECTFIELDS;
        BDimension Thickness; /*!< Diameter of annulus. */
        BDimension Clearance; /*!< Clearance with polygons. */
        BDimension Mask;
        BDimension DrillingHole; /*!< Diameter of drill hole. */
        LocationType X; /*!< X-value of center. */
        LocationType Y; /*!< Y-value of center. */
        char *Name; /*!< Pin name. */
        char *Number; /*!< Pin number. */
        void *Element;
        void *Spare;
} PinType, *PinTypePtr, **PinTypeHandle;

/*!
 * \brief Holds information about one element entity.
 */
typedef struct
{
        ANYOBJECTFIELDS;
        TextType Name[MAX_ELEMENTNAMES];
                /*!< the elements names: \n
                 * - description text, \n
                 * - name on PCB second, \n
                 * - value third \n
                 * see pcb/src/macro.h
                 */
        LocationType MarkX; /*!< X-value of position mark. */
        LocationType MarkY; /*!< Y-value of position mark. */
        Cardinal PinN; /*!< Number of pins. */
        Cardinal PinMax; /*!< Maximum number of pins. */
        Cardinal PadN; /*!< Number of pads. */
        Cardinal PadMax; /*!< Maximum number of pads. */
        Cardinal LineN; /*!< Number of lines. */
        Cardinal LineMax; /*!< Maximum number of lines. */
        Cardinal ArcN; /*!< Number of arcs. */
        Cardinal ArcMax; /*!< Maximum number of arcs. */
        PinTypePtr Pin; /*!< Pins contained by the element. */
        PadTypePtr Pad; /*!< Pads contained by the element. */
        LineTypePtr Line; /*!< Lines contained by the element. */
        ArcTypePtr Arc; /*!< Arcs contained by the element. */
        BoxType VBox;
        AttributeListType Attributes; /*!< List of attributes. */
} ElementType, *ElementTypePtr, **ElementTypeHandle;

/* EOF */
