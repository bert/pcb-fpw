/*!
 * \file src/pcb_globals.h
 *
 * \author PCB, interactive printed circuit board design \n
 * Copyright (C) 1994, 1995, 1996 Thomas Nau \n
 * Contact addresses for paper mail and Email: \n
 * Thomas Nau, Schlehenweg 15, 88471 Baustetten, Germany \n
 * Thomas.Nau@rz.uni-ulm.de
 *
 * \brief Contains typedefs, global variables and structs copied from pcb.
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


#ifndef __PCB_GLOBALS_INCLUDED__
#define __PCB_GLOBALS_INCLUDED__


/*!
 * \warning Now follows some definitions and typedefs copied from pcb. \n
 * Do not change the following definitions even if they're not very nice. \n
 * It allows us to have functions act on these "base types" and not need to
 * know what kind of actual object they're working on. \n
 * In the future this may simplify the conversion of pcb-gfpw from a
 * stand-alone application to a pcb plug-in.
 */

#ifndef MIN
#define MIN(a,b) ((a) < (b) ? (a) : (b))
#define MAX(a,b) ((a) > (b) ? (a) : (b))
#endif

#define LN_2_OVER_2 0.346573590

#define MAX_LAYER 16
        /*!< Maximum number of layers, check the pcb source code for
         * more changes, a *lot* more changes. */
#define MAX_ELEMENTNAMES 3
        /*!< Maximum number of supported names of an element. */
#define DESCRIPTION_INDEX 0
#define NAMEONPCB_INDEX 1
#define VALUE_INDEX 2
#define MARK_SIZE 5000 /* in mils/100 ? */
        /*!< Relative marker size */
#define MIN_TEXTSCALE 10
        /*!< Scaling of text objects in percent */
#define MAX_TEXTSCALE 10000 /* in mils/100 ? */
        /*!< Scaling of text objects in percent */

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
         * Example: fiducial pads. */

/*!
 * PCB flags.
 */
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
        /*!< pad should not receive solderpaste. \n
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
        /*!< indicates one end already rubber banding same as warn
         * flag since pins/pads won't use it. */
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
        /*!< Padr.Point2 is closer to outside edge. \n
        * Also pinout text for pins is vertical. */
#define VISITFLAG 0x8000
        /*!< marker to avoid re-visiting an object. */

/*!
 * macros to transform coord systems
 * draw.c uses a different definition of TO_SCREEN
 */
#ifndef	SWAP_IDENT
#define	SWAP_IDENT Settings.ShowSolderSide
#endif

#define	SWAP_SIGN_X(x) (x)
#define	SWAP_SIGN_Y(y) (-(y))
#define	SWAP_ANGLE(a) (-(a))
#define	SWAP_DELTA(d) (-(d))
#define	SWAP_X(x) (SWAP_SIGN_X(x))
#define	SWAP_Y(y) (PCB->MaxHeight +SWAP_SIGN_Y(y))

#define	TO_SCREEN_SIGN_X(x) (SWAP_IDENT ? SWAP_SIGN_X(x) : (x))
#define	TO_SCREEN_SIGN_Y(y) (SWAP_IDENT ? SWAP_SIGN_Y(y) : (y))

/*!
 * The layer-numbers of the two additional special layers 'component'
 * and 'solder'. \n
 * The offset of \c MAX_LAYER is not added
 */
#define SOLDER_LAYER 0
#define COMPONENT_LAYER 1

#define TEST_FLAG(F,P) ((P)->Flags.f & (F) ? 1 : 0)

/*!
 * Determines if an object is on the given \c side. \n
 * \c side is either \c SOLDER_LAYER or \c COMPONENT_LAYER.
 */
#define ON_SIDE(element, side) \
        (TEST_FLAG (ONSOLDERFLAG, element) == (side == SOLDER_LAYER))

/*!
 *  Determines if object is on front or back.
 */
#define FRONT(o) \
        ((TEST_FLAG(ONSOLDERFLAG, (o)) != 0) == SWAP_IDENT)



static int ID = 1;
        /*!< Current object ID; \n
         * Incremented after each creation of an object. */

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

/*! End cap styles.
 * The cap *always* extends beyond the coordinates given, by half the
 * width of the line.
 * Beveled ends can be used to make octagonal pads by giving the same
 * x,y coordinate twice.
 */
typedef enum
{
        Trace_Cap, /*!< This means we're drawing a trace, which has round caps. */
        Square_Cap, /*!< Square pins or pads. */
        Round_Cap, /*!< Round pins or round-ended pads, thermals. */
        Beveled_Cap /*!< Octagon pins or bevel-cornered pads. */
} EndCapStyle;

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
                /*!< : X-value of the upper left corner coordinate. */
        LocationType Y1;
                /*!< : Y-value of the upper left corner coordinate. */
        LocationType X2;
                /*!< : X-value of the lower right corner coordinate. */
        LocationType Y2;
                /*!< : Y-value of the lower right corner coordinate. */
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
 * \brief Holds information about one (SMD) pad entity.
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
        GList *Pin;
                /*!< Pins contained by the element.*/
        GList *Pad;
                /*!< Pads contained by the element.*/
        GList *Line;
                /*!< Lines contained by the element.*/
        GList *Arc;
                /*!< Arcs contained by the element.*/
        BoxType VBox;
                /*!< Virtual (bounding) Box.*/
        AttributeListType Attributes;
                /*!< List of attributes. */
} ElementType, *ElementTypePtr, **ElementTypeHandle;

/* holds information about a polygon */
typedef struct 
{
        ANYOBJECTFIELDS;
        Cardinal PointN; /* number of points in polygon */
        Cardinal  PointMax; /* max number from malloc() */
//        POLYAREA *Clipped; /* the clipped region of this polygon */
//        PLINE *NoHoles; /* the polygon broken into hole-less regions */
        int NoHolesValid; /* Is the NoHoles polygon up to date? */
        PointTypePtr Points; /* data */
        Cardinal *HoleIndex; /* Index of hole data within the Points array */
        Cardinal HoleIndexN; /* number of holes in polygon */
        Cardinal HoleIndexMax; /* max number from malloc() */
} PolygonType, *PolygonTypePtr, **PolygonTypeHandle;

#define ELEMENTLINE_LOOP(element) do \
        { \
                GList *__iter; \
                GList *__copy = g_list_reverse (g_list_copy ((element)->Line)); \
                Cardinal n; \
                for (__iter = __copy, n = (element)->LineN - 1; \
                        __iter != NULL; \
                        __iter = g_list_next (__iter), n--) \
                        { \
                                LineType *line = __iter->data;

#define ELEMENTARC_LOOP(element) do \
        { \
                GList *__iter; \
                GList *__copy = g_list_reverse (g_list_copy ((element)->Arc)); \
                Cardinal n; \
                for (__iter = __copy, n = (element)->ArcN - 1; \
                        __iter != NULL; \
                        __iter = g_list_next (__iter), n--) \
                        { \
                                ArcType *arc = __iter->data;

#define ELEMENTTEXT_LOOP(element) do \
        { \
                Cardinal n; \
                GList *__copy = NULL; /* DUMMY */ \
                TextTypePtr text; \
                for (n = MAX_ELEMENTNAMES-1; n != -1; n--) \
                { \
                        text = &(element)->Name[n]

#define PIN_LOOP(element) do \
        { \
                GList *__iter; \
                GList *__copy = g_list_copy ((element)->Pin); \
                Cardinal n; \
                for (__iter = __copy, n = 0; \
                        __iter != NULL; \
                        __iter = g_list_next (__iter), n++) \
                        { \
                                PinType *pin = __iter->data;

#define PAD_LOOP(element) do \
        { \
                GList *__iter; \
                GList *__copy = g_list_copy ((element)->Pad); \
                Cardinal n; \
                for (__iter = __copy, n = 0; \
                        __iter != NULL; \
                        __iter = g_list_next (__iter), n++) \
                        { \
                                PadType *pad = __iter->data;

#define ARC_LOOP(element) do \
        { \
                GList *__iter; \
                GList *__copy = g_list_reverse (g_list_copy ((element)->Arc)); \
                Cardinal n; \
                for (__iter = __copy, n = (element)->ArcN - 1; \
                        __iter != NULL; \
                        __iter = g_list_next (__iter), n--) \
                        { \
                                ArcType *arc = __iter->data;

#define END_LOOP } \
                g_list_free (__iter); \
                g_list_free (__copy); \
        } while (0)


#endif /* __PCB_GLOBALS_INCLUDED__ */


/* EOF */
