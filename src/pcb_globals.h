/*!
 * \file src/pcb_globals.h
 *
 * \author Copyright (C) 2010 by Bert Timmerman <bert.timmerman@xs4all.nl>
 *
 * \brief Contains typedefs, global variables and structs from pcb.
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


#endif /* __PCB_GLOBALS_INCLUDED__ */


/* EOF */
