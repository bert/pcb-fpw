/*!
 * \file pcb_globals.h
 * \author See the copyright notices in the pcb package, for more
 * information see http://pcb.gpleda.org .
 *
 * \brief This file contains global definitions, typedefs, structs and
 * variables extracted from the pcb source files const.h, globals.h and
 * macro.h .
 *
 * \warning Do not change the following definitions even if they're not
 * very nice.\n
 * It allows us to have functions act on these "base types" and not need
 * to know what kind of actual object they're working on.\n
 * In the future this may simplify the conversion of pcb-gfpw from a
 * stand-alone application to a pcb plug-in.
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
 * \n
 * Now follows some definitions, structs and typedefs copied from pcb.\n
 */


#ifndef __PCB_GLOBALS_INCLUDED__
#define __PCB_GLOBALS_INCLUDED__


#define MAX_LAYER 16
        /*!< Maximum number of layers, check the pcb source code for more changes,
         * a *lot* more changes.
         */
#define MAX_ELEMENTNAMES 3
        /*!< Maximum number of supported names of an element. */
#define EMARK_SIZE 1000
        /*!< Size of diamond element mark. */
#define MIN_TEXTSCALE 10
        /*!< Scaling of text objects in percent. */
#define MAX_TEXTSCALE 10000
        /*!< Scaling of text objects in percent. */

#define THIN_DRAW 1
        /*!< Draw objects with thin lines.\n
         * Thin lines are not printed on silkscreen (in the real world). */

#define MIL_TO_MM 0.025400000
        /*!< Convert mil to mm. */
#define MM_TO_MIL 39.37007874
        /*!< Convert mm to mil. */
#define TAN_22_5_DEGREE_2 0.207106781
        /*!< For convenience: 0.5 * tan (22.5) */

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

/* Object types. */
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

/* Object flag values. */
#define NOFLAG 0x0000
#define PINFLAG 0x0001
        /*!< is a pin. */
#define VIAFLAG 0x0002
        /*!< is a via. */
#define FOUNDFLAG 0x0004
        /*!< used by 'FindConnection()'. */
#define HOLEFLAG 0x0008
        /*!< pin or via is only a hole. */
#define NOPASTEFLAG 0x0008
        /*!< pad should not receive solderpaste.\n
         * This is to support fiducials. */
#define RATFLAG 0x0010
        /*!< indicates line is a rat line. */
#define PININPOLYFLAG 0x0010
        /*!< pin found inside poly - same as rat line since not used on
         * lines. */
#define CLEARPOLYFLAG 0x0010
        /*!< pins/vias clear these polygons. */
#define HIDENAMEFLAG 0x0010
        /*!< hide the element name. */
#define DISPLAYNAMEFLAG 0x0020
        /*!< display the names of pins/pads of an element. */
#define CLEARLINEFLAG 0x0020
        /*!< line doesn't touch polygons. */
#define FULLPOLYFLAG 0x0020
        /*!< full polygon is drawn (i.e. all parts instead of only the
         * biggest one). */
#define SELECTEDFLAG 0x0040
        /*!< object has been selected. */
#define ONSOLDERFLAG 0x0080
        /*!< element is on bottom side. */
#define AUTOFLAG 0x0080
        /*!< line/via created by auto-router. */
#define SQUAREFLAG 0x0100
        /*!< pin is square, not round. */
#define RUBBERENDFLAG 0x0200
        /*!< indicates one end already rubber banding same as warn flag
         * since pins/pads won't use it. */
#define WARNFLAG 0x0200
        /*!< Warning for pin/via/pad. */
#define USETHERMALFLAG 0x0400
        /*!< draw pin, via with thermal fingers. */
#define ONSILKFLAG 0x0400
        /*!< old files use this to indicate silk. */
#define OCTAGONFLAG 0x0800
        /*!< draw pin/via as octagon instead of round. */
#define DRCFLAG 0x1000
        /*!< flag like FOUND flag for DRC checking. */
#define LOCKFLAG 0x2000
        /*!< object locked in place. */
#define EDGE2FLAG 0x4000
        /*!< Padr.Point2 is closer to outside edge also pinout text for
         * pins is vertical. */
#define VISITFLAG 0x8000
        /*!< marker to avoid re-visiting an object. */

/* Elements name index within the structure. */
#define DESCRIPTION_INDEX 0
#define NAMEONPCB_INDEX 1
#define VALUE_INDEX 2

/* Access macros for elements name structure. */
#define NAME_INDEX(p)           (TEST_FLAG(NAMEONPCBFLAG,(p)) ? NAMEONPCB_INDEX :\
                                (TEST_FLAG(DESCRIPTIONFLAG, (p)) ? \
                                DESCRIPTION_INDEX : VALUE_INDEX))
#define ELEMENT_NAME(p,e)       ((e)->Name[NAME_INDEX((p))].TextString)
#define DESCRIPTION_NAME(e)     ((e)->Name[DESCRIPTION_INDEX].TextString)
#define NAMEONPCB_NAME(e)       ((e)->Name[NAMEONPCB_INDEX].TextString)
#define VALUE_NAME(e)           ((e)->Name[VALUE_INDEX].TextString)
#define ELEMENT_TEXT(p,e)       ((e)->Name[NAME_INDEX((p))])
#define DESCRIPTION_TEXT(e)     ((e)->Name[DESCRIPTION_INDEX])
#define NAMEONPCB_TEXT(e)       ((e)->Name[NAMEONPCB_INDEX])
#define VALUE_TEXT(e)           ((e)->Name[VALUE_INDEX])

/*!
 * \brief Routine for testing flags.
 */
#define TEST_FLAG(F,P) ((P)->Flags.f & (F) ? 1 : 0)

/*!
 * \brief Pin loop shortcut.
 *
 * All object loops run backwards to prevent from errors when deleting
 * objects.\n
 * A pointer is created from index addressing because the base pointer
 * may change when new memory is allocated.\n
 * All data is relative to an objects name 'top' which can be either
 * PCB or PasteBuffer
 */
#define	PIN_LOOP(element) do { \
    Cardinal n, sn; \
    PinTypePtr pin; \
    for (sn = (element)->PinN, n = 0; (element)->PinN > 0 && n < (element)->PinN ; \
        n += 1 + (element)->PinN - sn, sn = (element)->PinN) \
    { \
        pin = &(element)->Pin[n]

#define	PAD_LOOP(element) do { \
    Cardinal n, sn; \
    PadTypePtr pad; \
    for (sn = (element)->PadN, n = 0; (element)->PadN > 0 && n < (element)->PadN ; \
        sn == (element)->PadN ? n++ : 0) \
    { \
        pad = &(element)->Pad[n]

#define ELEMENTARC_LOOP(element) do { \
    Cardinal n; \
    ArcTypePtr arc; \
    for (n = (element)->ArcN-1; n != -1; n--) \
    { \
        arc = &(element)->Arc[n]


#define ELEMENTLINE_LOOP(element) do { \
    Cardinal n; \
    LineTypePtr line; \
    for (n = (element)->LineN-1; n != -1; n--) \
    { \
        line = &(element)->Line[n]


#define END_LOOP }} while (0)


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
typedef int BDimension;
        /*!< big dimension */
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
        LocationType X1;
                /*!< X-value of the upper left corner coordinate. */
        LocationType Y1;
                /*!< Y-value of the upper left corner coordinate. */
        LocationType X2;
                /*!< X-value of the lower right corner coordinate. */
        LocationType Y2;
                /*!< Y-value of the lower right corner coordinate. */
} BoxType, *BoxTypePtr;

/*!
 * \brief A Flag type.
 *
 * This structure must be simple-assignable for now.
 */
typedef struct
{
        unsigned long f;
                /*!< Generic flags */
        unsigned char t[(MAX_LAYER + 1) / 2];
                /*!< Thermals */
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
 * \brief Polygon float type.
 */
typedef struct
{
        double X;
        double Y;
}
FloatPolyType, *FloatPolyTypePtr;

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
 * \brief Holds information about one line entity.
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
        long int X;
                /*!< X-value of origin point.*/
        long int Y;
                /*!< Y-value of origin point.*/
} MarkType, *MarkTypePtr;

/*!
 * \brief Holds information about one text entity.
 */
typedef struct
{
        ANYOBJECTFIELDS;
        BDimension Scale;
                /*!< text scaling in percent. */
        LocationType X;
                /*!< X-value of origin (insertion point). */
        LocationType Y;
                /*!< Y-value of origin (insertion point). */
        BYTE Direction;
                /*!< Text direction. */
        char *TextString;
                /*!< String value. */
        void *Element;
} TextType, *TextTypePtr;

/*!
 * \brief Holds information about one arc entity.
 */
typedef struct
{
        ANYOBJECTFIELDS;
        BDimension Thickness;
                /*!< Trace width. */
        BDimension Clearance;
                /*!< Clearance with polygons. */
        LocationType Width;
                /*!< Length of axis. */
        LocationType Height;
                /*!< Heigth of axis. */
        LocationType X;
                /*!< X-value of center coordinate. */
        LocationType Y;
                /*!< Y-value of center coordinate. */
        long int StartAngle;
                /*!< limiting angle in degrees */
        long int Delta;
                /*!< limiting angle in degrees */
} ArcType, *ArcTypePtr;

/*!
 * \brief Holds information about one SMD pad entity.
 */
typedef struct
{
        ANYLINEFIELDS;
        BDimension Mask;
        char *Name;
                /*!< Pad name. */
        char *Number;
                /*!< 'Line' */
        void *Element;
        void *Spare;
} PadType, *PadTypePtr;

/*!
 * \brief Holds information about one through hole pin entity.
 */
typedef struct
{
        ANYOBJECTFIELDS;
        BDimension Thickness;
                /*!< Diameter of annulus.*/
        BDimension Clearance;
                /*!< Clearance with polygons.*/
        BDimension Mask;
        BDimension DrillingHole;
                /*!< Diameter of drill hole.*/
        LocationType X;
                /*!< X-value of center point.*/
        LocationType Y;
                /*!< Y-value of center point.*/
        char *Name;
                /*!< Pin name. */
        char *Number;
                /*!< Pin number. */
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
                /*!< the elements names:\n
                 * - description text,\n
                 * - name on PCB second,\n
                 * - value third\n
                 * see pcb/src/macro.h
                 */
        LocationType MarkX;
                /*!< X-value of position mark.*/
        LocationType MarkY;
                /*!< Y-value of position mark.*/
        Cardinal PinN;
                /*!< Pin Number.*/
        Cardinal PinMax;
                /*!< Maximum number of pins.*/
        Cardinal PadN;
                /*!< Pad Number.*/
        Cardinal PadMax;
                /*!< Maximum number of pads.*/
        Cardinal LineN;
                /*!< Line Number.*/
        Cardinal LineMax;
                /*!< Maximum number of lines. */
        Cardinal ArcN;
                /*!< Arc Number.*/
        Cardinal ArcMax;
                /*!< Maximum number of arcs.*/
        PinTypePtr Pin;
                /*!< Pins contained by the element.*/
        PadTypePtr Pad;
                /*!< Pads contained by the element.*/
        LineTypePtr Line;
                /*!< Lines contained by the element.*/
        ArcTypePtr Arc;
                /*!< Arcs contained by the element.*/
        BoxType VBox;
                /*!< Bounding box.*/
        AttributeListType Attributes;
                /*!< List of attributes. */
} ElementType, *ElementTypePtr, **ElementTypeHandle;


/*!
 * \brief The element we are currently working on.
 *
 * This element contains data based upon the values in the GUI entries,
 * comboboxes and checkbuttons.
 */
ElementTypePtr current_element;


/*!
 * \brief The element we were previously working on.
 *
 * After switching to a new element, for instance after loading a fpw
 * file, we want to keep the former element around for a while.
 *
 * \todo Maybe this will evolve in a full undo/redo mechanisme (feature).
 */
ElementTypePtr previous_element = NULL;


#endif /* __PCB_GLOBALS_INCLUDED__ */

/* EOF */
