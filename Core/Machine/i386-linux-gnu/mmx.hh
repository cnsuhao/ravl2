// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_MMX_HEADER
#define RAVL_MMX_HEADER 1
///////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! author="Ramesh Krishna"
//! lib=RavlCore
//! file="Ravl/Core/Machine/i386-linux-gnu/mmx.hh"

// These are some macro's used for accelerating some processing operatations
// on processors x86 processors that support MMX instructions.

#include "Ravl/config.h"

#define MMX8 0 
#define MMX7 16
#define MMX6 32
#define MMX5 48
#define MMX4 0
#define MMX3 16
#define MMX2 32
#define MMX1 48

#define MMXADDMASK 0x1000100010001

#define MMXLEN2 2
#define MMXLEN4 4


// Use this before any MMX operations, and after floating point ops between
// mmx calls.

#if RAVL_COMPILER_GCC3 || RAVL_COMPILER_GCC4
#define INITMMX __asm__( "pxor %%mm0, %%mm0" : : ); // Init the mask register
#else
#define INITMMX __asm__( "pxor %mm0, %mm0" : : ); // Init the mask register
#endif

// Use this after any MMX operations if thay are followed by floating point ops.

#define CLOSEMMX __asm__ ( "emms" : : );

////////////////////////////////////////////////////////////////////////////////
// Add the two arrays of 4 shorts put the result in a third.
// Array3[0..3] = Array1[0..3] + Array2[0..3] 

#define MMXADDARRAYS3_SHORT4( Array1, Array2, Array3 )  __asm__ volatile      \
(                                                                      \
  "\n\t movq %1, %%mm1 \t         # Load Array1 elements"              \
  "\n\t paddsw %2, %%mm1 \t       # Add vals"                          \
  "\n\t movq %%mm1, %0 \t         # copy to output"                    \
  : "=m"(Array3) : "m"(Array1), "m"(Array2)                            \
);

////////////////////////////////////////////////////////////////////////////////
// Add one array of 4 shorts into another..
// Array1[0..3] += Array2[0..3]

#define MMXADDARRAYS2_SHORT4( Array1, Array2 )  __asm__ volatile              \
(                                                                      \
  "\n\t movq %1, %%mm1 \t         # Load Array1 elements"              \
  "\n\t paddsw %0, %%mm1 \t       # Add vals with Array0"              \
  "\n\t movq %%mm1, %0 \t         # Load result into Array0"           \
  : "=m"(Array1) : "m"(Array2)                                         \
);

////////////////////////////////////////////////////////////////////////////////
// Subtract the two arrays of 4 shorts put the result in a third.
// Array3[0..3] = Array1[0..3] - Array2[0..3] 

#define MMXSUBTARRAYS3_SHORT4( Array1, Array2, Array3 )  __asm__ volatile      \
(                                                                      \
  "\n\t movq %1, %%mm1 \t         # Load Array1 elements"              \
  "\n\t psubsw %2, %%mm1 \t       # Array1 - Array2"                   \
  "\n\t movq %%mm1, %0 \t         # copy to Array3"                    \
  : "=m"(Array3) : "m"(Array1), "m"(Array2)                            \
);

////////////////////////////////////////////////////////////////////////////////
// Subtract one array of 4 shorts from another.
// Array1[0..3] -= Array2[0..3]

#define MMXSUBTARRAYS2_SHORT4( Array1, Array2)  __asm__ volatile       \
(                                                                      \
  "\n\t movq %1, %%mm1 \t         # Load Array1 elements"              \
  "\n\t psubsw %0, %%mm1 \t       # Array1 - Array2"                   \
  "\n\t movq %%mm1, %0 \t         # copy to Array1"                    \
  : "=m"(Array3) : "m"(Array1)                                         \
);

///////////////////////////////////////////////////////////////////////////////////
// Multiply by a constant.
// Array1 * Array2. 4 * 16 bit input, 2 * 2 * 32 bit output.  
// Array3 = 2 * 32 bit (1st part), Array4 = 2 * 32 bit (2nd part) 

#define MMXMULTA4S( Array1, Array2, Array3, Array4 )  __asm__ volatile      \
(                                                        \
  "\n\t movq %2, %%mm1 \t          # load a1"            \
  "\n\t movq %%mm1, %%mm2 \t       # copy a1"            \
  "\n\t pmullw %3, %%mm1  \t       # a2 * a1 = low"      \
  "\n\t movq %%mm1, %%mm3 \t       # copy low bits"      \
  "\n\t pmulhw %3, %%mm2  \t       # a2 * a1 = high"     \
  "\n\t movq %%mm1, %%mm4 \t       # copy high bits"     \
  "\n\t punpcklwd %%mm2, %%mm1 \t  # 2 lo nums"          \
  "\n\t punpckhwd %%mm2, %%mm3 \t  # 2 hi nums"          \
  "\n\t movq %%mm1, %0 \t          # cp out"             \
  "\n\t movq %%mm3, %1 \t          # cp out"             \
  : "=m"(*Array3), "=m"(*Array4) : "m"(*Array1), "m"(*Array2)         \
);



//////////////////////////////////////////////////////////////////////////////////
// Image - 8 bit image data (single row)
// Filter - signed 16 bit filter data (up to four vals). 
// Sresult - unsigned int sum of products of Image and Filter values.
// Shift - MMX1, MMX2, MMX3, MMX4 for 1, 2, 3 and 4 data values resp.

#define MMXMULT4B( Image, Filter, Sresult, Shift )  __asm__ volatile  \
(                                                                     \
  "\n\t movq %1, %%mm1 \t         # Load the 8 bit image data"        \
  "\n\t punpcklbw %%mm0, %%mm1 \t # Unpack into 16-bit data"          \
  "\n\t psllq %4, %%mm1 \t        # Shift out unwanted vals"          \
  "\n\t psrlq %4, %%mm1 \t        # Shift out unwanted vals"          \
  "\n\t pmaddwd %2, %%mm1 \t      # Multiply with filter data"        \
  "\n\t movq  %%mm1, %%mm2 \t     # Copy the two values"              \
  "\n\t psrlq %3, %%mm1 \t        # Shift to line up vals"            \
  "\n\t paddd %%mm2, %%mm1 \t     # Add lower 32 bits"                \
  "\n\t movd %0, %%mm2 \t         # Read in original val"             \
  "\n\t paddd %%mm2, %%mm1 \t     # Add lower 32 bits"                \
  "\n\t movd %%mm1, %0 \t         # load data into result"            \
  : "=m"(Sresult) : "m"(*Image), "m"(*Filter), "i"(32), "i"(Shift)    \
);


// As above but image is short int

#define MMXMULT4S( Image, Filter, Sresult, Shift )  __asm__ volatile  \
(                                                                     \
  "\n\t movq %1, %%mm1 \t         # Load the 8 bit image data"        \
  "\n\t psllq %4, %%mm1 \t        # Shift out unwanted vals"          \
  "\n\t psrlq %4, %%mm1 \t        # Shift out unwanted vals"          \
  "\n\t pmaddwd %2, %%mm1 \t      # Multiply with filter data"        \
  "\n\t movq  %%mm1, %%mm2 \t     # Copy the two values"              \
  "\n\t psrlq %3, %%mm1 \t        # Shift to line up vals"            \
  "\n\t paddd %%mm2, %%mm1 \t     # Add lower 32 bits"                \
  "\n\t movd %0, %%mm2 \t         # Read in original val"             \
  "\n\t paddd %%mm2, %%mm1 \t     # Add lower 32 bits"                \
  "\n\t movd %%mm1, %0 \t         # load data into result"            \
  : "=m"(Sresult) : "m"(*Image), "m"(*Filter), "i"(32), "i"(Shift)    \
);

///////////////////////////////////////////////////////////////////////////////
// Image - 8 bit image data (single row)
// Filter1 - signed 16 bit filter data (first four vals). 
// Filter2 - remaining signed 16 bit filter data (up to four vals). 
// Sresult - unsigned int sum of products of Image and Filter values.
// Shift - MMX5, MMX6, MMX7, MMX8 for 5, 6, 7 and 8 data values resp.

#define MMXMULT8B( Image, Filter1, Filter2, Sresult, Shift )  __asm__ volatile   \
(                                                                      \
  "\n\t movq %2, %%mm5 \t         # Load the filter (1st half)"        \
  "\n\t movq %5, %%mm6 \t         # Load the filter (2nd half)"        \
  "\n\t movq %1, %%mm1 \t         # Load the 8 bit image data"         \
  "\n\t movq %%mm1, %%mm2 \t      # Make a copy"                       \
  "\n\t punpcklbw %%mm0, %%mm1 \t # Unpack into 16-bit data"           \
  "\n\t punpckhbw %%mm0, %%mm2 \t # Unpack into 16-bit data"           \
  "\n\t psllq %4, %%mm2 \t        # Shift out unwanted vals, 2nd reg"  \
  "\n\t psrlq %4, %%mm2 \t        # Shift back into correct posns"     \
  "\n\t pmaddwd %%mm5, %%mm1 \t   # Multiply with filter data"         \
  "\n\t pmaddwd %%mm6, %%mm2 \t   # Multiply with filter data"         \
  "\n\t paddd %%mm1, %%mm2 \t     # Add both vals"                     \
  "\n\t movq  %%mm2, %%mm1 \t     # Make a copy"                       \
  "\n\t psrlq %3, %%mm1 \t        # Shift to line up vals"             \
  "\n\t paddd %%mm1, %%mm2 \t     # Add lower 32 bits"                 \
  "\n\t movd %0, %%mm1 \t         # Read in original val"              \
  "\n\t paddd %%mm2, %%mm1 \t     # Add lower 32 bits"                 \
  "\n\t movd %%mm1, %0 \t         # load data into result"             \
  : "=m"(Sresult) : "m"(*Image), "m"(*Filter1), "i"(32), "i"(Shift), "m"(*Filter2) \
);


// As above but image is short int

#define MMXMULT8S( Image1, Image2, Filter1, Filter2, Sresult, Shift )  __asm__ volatile   \
(                                                                      \
  "\n\t movq %2, %%mm5 \t         # Load the filter (1st half)"        \
  "\n\t movq %6, %%mm6 \t         # Load the filter (2nd half)"        \
  "\n\t movq %1, %%mm1 \t         # Load the 16 bit image data"        \
  "\n\t movq %5, %%mm2 \t         # Load the 16 bit image data"        \
  "\n\t psllq %4, %%mm2 \t        # Shift out unwanted vals, 2nd reg"  \
  "\n\t psrlq %4, %%mm2 \t        # Shift back into correct posns"     \
  "\n\t pmaddwd %%mm5, %%mm1 \t   # Multiply with filter data"         \
  "\n\t pmaddwd %%mm6, %%mm2 \t   # Multiply with filter data"         \
  "\n\t paddd %%mm1, %%mm2 \t     # Add both vals"                     \
  "\n\t movq  %%mm2, %%mm1 \t     # Make a copy"                       \
  "\n\t psrlq %3, %%mm1 \t        # Shift to line up vals"             \
  "\n\t paddd %%mm1, %%mm2 \t     # Add lower 32 bits"                 \
  "\n\t movd %0, %%mm1 \t         # Read in original val"              \
  "\n\t paddd %%mm2, %%mm1 \t     # Add lower 32 bits"                 \
  "\n\t movd %%mm1, %0 \t         # load data into result"             \
  : "=m"(Sresult) : "m"(*Image1), "m"(*Filter1), "i"(32), "i"(Shift), "m"(*Image2), "m"(*Filter2) \
);

#endif
