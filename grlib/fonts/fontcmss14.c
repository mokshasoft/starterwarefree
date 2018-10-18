//*****************************************************************************
//
// fontcmss14.c - Font definition for the 14 point Cmss font.
//
// Copyright (c) 2008-2010 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
// This is part of revision 6288 of the Stellaris Graphics Library.
//
//*****************************************************************************

//*****************************************************************************
//
// This file is generated by ftrasterize; DO NOT EDIT BY HAND!
//
//*****************************************************************************

#include "grlib.h"

//*****************************************************************************
//
// Details of this font:
//     Style: cmss
//     Size: 14 point
//     Bold: no
//     Italic: no
//     Memory usage: 1748 bytes
//
//*****************************************************************************

//*****************************************************************************
//
// The compressed data for the 14 point Cmss font.
//
//*****************************************************************************
static const unsigned char g_pucCmss14Data[1545] =
{
      5,   6,   0,  11,  32,  11,   2,  33,  17,  17,  17,  17,
     17,  17,  81, 144,   9,   5,  81,  33,  17,  33,   0,   7,
     80,  27,  10, 225,  33,  81,  33,  97,  33,  97,  33,  57,
     49,  33,  97,  33,  73,  49,  33,  97,  17,  97,  33,  97,
     33,  97,  33, 240,  24,   6,  33,  68,  17,  17,  17,  17,
     17,  49,  17,  67,  67,  49,  17,  49,  17,  17,  17,  17,
     35,  65, 240,  96,  36,  10,  17, 129,  17,  49,  49,  17,
     33,  65,  17,  33,  65,  17,  17,  97,  33, 129,  34,  81,
     17,  33,  49,  33,  33,  49,  33,  33,  33,  49,  33,  33,
     66, 240, 240,  32,  24,   9, 178,  97,  33,  81,  33,  81,
     17,  99,  98,  65,  17,  18,  33,  33,  36,  33,  50,  67,
     19, 240, 240, 112,   6,   2,  33,  17, 240, 160,  17,   4,
     33,  33,  49,  33,  49,  49,  49,  49,  49,  49,  49,  65,
     49,  65,  80,  17,   4,   1,  65,  49,  65,  49,  49,  49,
     49,  49,  49,  49,  33,  49,  33, 112,  11,   6,  33,  81,
     53,  49,  53,  49,   0,   7,  16,  16,  10, 240, 145, 145,
    145, 145, 145,  89,  81, 145, 145, 145, 240, 240,  80,   6,
      2, 240,  81,  17, 112,   6,   4, 240, 211, 240, 224,   5,
      2, 240,  81, 144,  17,   6,  65,  81,  65,  81,  81,  65,
     81,  81,  65,  81,  81,  65,  81,  81, 176,  20,   6, 211,
     34,  18,  17,  49,  17,  49,  17,  49,  17,  49,  17,  49,
     18,  18,  35, 240, 176,  13,   6, 195,  81,  81,  81,  81,
     81,  81,  81,  53, 240, 160,  14,   6, 211,  33,  34,  81,
     81,  65,  65,  65,  65,  85, 240, 160,  15,   6, 211,  33,
     49,  81,  50,  97,  81,  81,  17,  49,  35, 240, 176,  17,
      6, 241,  66,  49,  17,  49,  17,  33,  33,  33,  33,  37,
     65,  81, 240, 176,  15,   7, 245,  33,  97, 100,  49,  49,
     97,  97,  18,  34,  36, 240, 240,  18,   6, 227,  33,  65,
     81,  18,  34,  33,  17,  49,  17,  49,  17,  49,  35, 240,
    176,  13,   6, 197,  65,  81,  65,  81,  65,  81,  81,  81,
    240, 208,  19,   6, 211,  33,  49,  17,  49,  17,  49,  35,
     34,  18,  17,  49,  17,  49,  35, 240, 176,  17,   6, 211,
     33,  49,  17,  49,  17,  49,  17,  49,  36,  81,  65,  35,
    240, 192,   5,   2, 161, 145, 144,   7,   2, 161, 145,  17,
     17,  80,  12,   2, 129,  49,  17,  17,  17,  17,  17,  17,
     17,  48,  10,  10,   0,   6,  41, 240, 105,   0,   7,  80,
     14,   5, 240,  97, 145,  65,  65,  65,  49,  65,  65,  33,
     19, 112,  12,   5,  83,  81,  65,  50,  34,  49,  65, 225,
    240, 128,  27,   8, 164,  50,  33,  49,  20,  17,  18,  18,
     17,  17,  49,  17,  17,  49,  17,  18,  18,  33,  19,  50,
     49,  52, 240, 240,  64,  22,   8, 177,  98,  97,  17,  65,
     33,  65,  33,  65,  49,  53,  33,  65,  33,  81,  17,  81,
    240, 240,  48,  22,   8, 134,  33,  66,  17,  81,  17,  66,
     21,  49,  65,  33,  81,  17,  81,  17,  66,  21, 240, 240,
     80,  16,   8, 164,  50,  97,  97, 113, 113, 113, 129, 114,
     49,  52, 240, 240,  64,  23,   8, 133,  49,  50,  33,  65,
     33,  81,  17,  81,  17,  81,  17,  81,  17,  66,  17,  65,
     37, 240, 240,  80,  14,   7, 118,  17,  97,  97, 101,  33,
     97,  97,  97, 102, 240, 224,  14,   6, 101,  17,  81,  81,
     81,  85,  17,  81,  81,  81, 240, 224,  19,   8, 165,  34,
     49,  33,  97, 113, 113, 113,  51,  33,  65,  34,  49,  52,
    240, 240,  64,  24,   8, 129,  81,  17,  81,  17,  81,  17,
     81,  23,  17,  81,  17,  81,  17,  81,  17,  81,  17,  81,
    240, 240,  48,  13,   2,  33,  17,  17,  17,  17,  17,  17,
     17,  17,  17, 144,  14,   5, 129,  65,  65,  65,  65,  65,
     65,  65,  65,  19, 240, 112,  25,   8, 129,  65,  33,  50,
     33,  34,  49,  33,  65,  18,  66,  17,  65,  49,  49,  50,
     33,  65,  33,  66, 240, 240,  48,  14,   6,  97,  81,  81,
     81,  81,  81,  81,  81,  81,  85, 240, 160,  38,  10, 162,
     82,  18,  82,  18,  82,  17,  17,  49,  17,  17,  17,  49,
     17,  17,  17,  49,  17,  17,  33,  17,  33,  17,  33,  17,
     33,  17,  33,  17,  33,  17,  49,  49, 240, 240, 176,  31,
      8, 130,  65,  18,  65,  17,  17,  49,  17,  17,  49,  17,
     33,  33,  17,  33,  33,  17,  49,  17,  17,  49,  17,  17,
     66,  17,  66, 240, 240,  48,  23,   9, 180,  65,  65,  49,
     65,  33,  97,  17,  97,  17,  97,  17,  97,  33,  65,  50,
     34,  68, 240, 240, 144,  19,   7, 117,  33,  50,  17,  65,
     17,  65,  17,  50,  21,  33,  97,  97,  97, 240, 240,  64,
     25,   9, 180,  66,  34,  49,  65,  33,  97,  17,  97,  17,
     97,  17,  97,  33,  33,  17,  50,  19,  68, 145, 129, 240,
     80,  23,   8, 133,  49,  66,  17,  81,  17,  81,  17,  65,
     37,  49,  49,  49,  50,  33,  66,  17,  81, 240, 240,  48,
     15,   6, 115,  33,  81,  81,  98,  98,  81,  81,  17,  49,
     35, 240, 176,  15,   8, 135,  65, 113, 113, 113, 113, 113,
    113, 113, 113, 240, 240,  96,  24,   8, 129,  81,  17,  81,
     17,  81,  17,  81,  17,  81,  17,  81,  17,  81,  17,  81,
     33,  49,  67, 240, 240,  80,  23,   9, 146,  81,  33,  81,
     33,  66,  34,  49,  65,  49,  65,  33,  82,  17,  97,  17,
     98, 114, 240, 240, 160,  36,  13, 209,  66,  65,  33,  50,
     65,  33,  50,  49,  49,  49,  17,  33,  50,  17,  33,  33,
     65,  17,  33,  33,  65,  17,  33,  17,  81,  17,  50,  82,
     66,  97,  65,   0,   7,  22,   9, 161,  66,  34,  49,  65,
     33,  99,  98, 114,  98,  17,  81,  34,  49,  65,  34,  81,
    240, 240, 112,  20,   8, 129,  81,  18,  65,  33,  49,  50,
     18,  65,  17,  97, 113, 113, 113, 113, 240, 240,  96,  14,
      7, 118,  82,  81,  81,  97,  81,  82,  81,  81, 102, 240,
    224,  17,   3,   2,  17,  33,  33,  33,  33,  33,  33,  33,
     33,  33,  33,  33,  33,  34,  10,   5,  81,  33,  17,  33,
     17,  33,   0,   7,  17,   3,   2,  33,  33,  33,  33,  33,
     33,  33,  33,  33,  33,  33,  33,  33,  18,   9,   5, 113,
     49,  17,  17,  33,   0,   7,   5,   2,  65, 240, 160,   7,
      2,  33,  17,  17, 240, 128,  13,   5, 240, 178,  81,  35,
     17,  33,  17,  33,  20, 240,  96,  18,   6,  97,  81,  81,
     81,  84,  33,  49,  17,  49,  17,  49,  17,  34,  20, 240,
    176,  12,   6, 240, 240,  20,  18,  65,  81,  82,  84, 240,
    160,  18,   7, 193,  97,  97,  97,  37,  18,  49,  17,  65,
     17,  65,  18,  49,  37, 240, 224,  13,   6, 240, 240,  19,
     33,  49,  21,  17,  82,  84, 240, 160,  14,   5, 114,  33,
     65,  65,  51,  49,  65,  65,  65,  65, 240, 128,  18,   7,
    240, 240, 116,  33,  33,  49,  33,  51,  65, 100,  33,  65,
     33,  49,  51, 144,  20,   6,  97,  81,  81,  81,  81,  19,
     18,  33,  17,  49,  17,  49,  17,  49,  17,  49, 240, 160,
     10,   2,  65,  81,  17,  17,  17,  17,  17, 144,  13,   4,
    161, 177,  49,  49,  49,  49,  49,  49,  49,  19,  80,  18,
      6,  97,  81,  81,  81,  81,  33,  33,  17,  51,  51,  49,
     33,  33,  49, 240, 160,  13,   2,  33,  17,  17,  17,  17,
     17,  17,  17,  17,  17, 144,  25,   9, 240, 240, 241,  18,
     19,  18,  33,  33,  17,  49,  33,  17,  49,  33,  17,  49,
     33,  17,  49,  33, 240, 240, 112,  17,   6, 240, 241,  19,
     18,  33,  17,  49,  17,  49,  17,  49,  17,  49, 240, 160,
     16,   7, 240, 240, 100,  34,  34,  17,  65,  17,  65,  18,
     34,  36, 240, 240,  17,   6, 240, 244,  33,  34,  17,  49,
     17,  49,  17,  34,  20,  33,  81,  81, 176,  19,   7, 240,
    240,  99,  17,  18,  34,  17,  65,  17,  65,  18,  49,  37,
     97,  97,  97, 128,  12,   4, 240,  81,  17,  18,  33,  49,
     49,  49, 240,  64,  12,   6, 240, 240,  20,  17,  83,  98,
     81,  20, 240, 176,  13,   5, 177,  65,  65,  52,  33,  65,
     65,  65,  67, 240,  96,  16,   6, 240, 241,  49,  17,  49,
     17,  49,  17,  49,  17,  49,  21, 240, 160,  16,   7, 240,
    240,  81,  50,  33,  33,  49,  33,  51,  82,  82, 240, 240,
     16,  25,   9, 240, 240, 241,  49,  33,  33,  18,  33,  33,
     17,  17,  17,  33,  17,  17,  17,  34,  34,  65,  34, 240,
    240, 128,  16,   7, 240, 240,  82,  33,  49,  18,  66,  82,
     65,  33,  34,  34, 240, 224,  17,   7, 240, 240,  81,  50,
     33,  33,  49,  33,  66,  82,  82,  81,  97,  81, 192,  11,
      6, 240, 245,  65,  65,  66,  65,  69, 240, 160,   8,   7,
      0,   6,  22,   0,   6,  32,   8,  14,   0,  12,  45,   0,
     12,  48,  11,   5,  97,  17,  17,  17,  33,  17,   0,   7,
     16,   8,   5, 162,  17,  17,  18,   0,   7,
};

//*****************************************************************************
//
// The font definition for the 14 point Cmss font.
//
//*****************************************************************************
const tFont g_sFontCmss14 =
{
    //
    // The format of the font.
    //
    FONT_FMT_PIXEL_RLE,

    //
    // The maximum width of the font.
    //
    12,

    //
    // The height of the font.
    //
    15,

    //
    // The baseline of the font.
    //
    11,

    //
    // The offset to each character in the font.
    //
    {
           0,    5,   16,   25,   52,   76,  112,  136,
         142,  159,  176,  187,  203,  209,  215,  220,
         237,  257,  270,  284,  299,  316,  331,  349,
         362,  381,  398,  403,  410,  422,  432,  446,
         458,  485,  507,  529,  545,  568,  582,  596,
         615,  639,  652,  666,  691,  705,  743,  774,
         797,  816,  841,  864,  879,  894,  918,  941,
         977,  999, 1019, 1033, 1050, 1060, 1077, 1086,
        1091, 1098, 1111, 1129, 1141, 1159, 1172, 1186,
        1204, 1224, 1234, 1247, 1265, 1278, 1303, 1320,
        1336, 1353, 1372, 1384, 1396, 1409, 1425, 1441,
        1466, 1482, 1499, 1510, 1518, 1526, 1537,
    },

    //
    // A pointer to the actual font data
    //
    g_pucCmss14Data
};
