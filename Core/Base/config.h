/* This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here*/
#ifndef RAVL_CONFIG_HEADER
#define RAVL_CONFIG_HEADER 1
/*! rcsid="$Id$" */
/*! file="Ravl/Core/Base/config.h" */
/*! lib=RavlCore */

/********************************************************************************/
/******* AMMA / QMAKE COMPATIBILITY *******/
#if !defined(RAVL_CHECK)
#if defined(AMMA_CHECK) || defined(QMAKE_CHECK)
#define RAVL_CHECK 1
#else
#define RAVL_CHECK 0
#endif
#endif
/****************************************/
/******** RAVL Paranoid checking. ********
 * These checks may significantly slow code,
 * but are helpful when looking for more 
 * obscure bugs.
 */
#ifdef QMAKE_PARANOID
#define RAVL_PARANOID(x) x
#else
#define RAVL_PARANOID(x)
#endif

/********************************************************************************/
/***** Detect the OS, compiler and processor type being used. *******************/

#define RAVL_COMPILER_GCC defined(__GNUC__)                        /* GNU compiler ? */
#define RAVL_COMPILER_GCC2 (defined(__GNUC__) && (__GNUC__ < 3))   /* gcc 2.x */
#define RAVL_COMPILER_GCC3 (defined(__GNUC__) && (__GNUC__ >= 3))  /* gcc 3.x */
#define RAVL_COMPILER_MIPSPRO (!defined(__GNUC__) && defined(__sgi))   /* MIPS Pro compiler */
#define RAVL_COMPILER_VISUALCPP (!defined(__GNUC__) && defined(WIN32)) /* Visual C++ */

#define RAVL_CPU_IX86  defined(__i386__)  /* 386 base varient. */
#define RAVL_CPU_SPARC defined(__sparc)   /* sun sparc based system. */
#define RAVL_CPU_MIPS  defined(__mips)    /* mips */
#define RAVL_CPU_ALPHA defined(__alpha)   /* alpha based system */

#define RAVL_OS_LINUX   defined(__linux__) /* Linux based OS. */
#define RAVL_OS_WIN32   defined(WIN32)     /* Windows platform. */
#define RAVL_OS_IRIX    defined(__sgi__)   /* IRIX.      */
#define RAVL_OS_SOLARIS defined(__sun)     /* Solaris.   */
#define RAVL_OS_OSF     defined(__osf)     /* OSF.       */

#define RAVL_OS_UNIX !RAVL_OS_WIN32       /* a unix style system */
#define RAVL_OS_POSIX !RAVL_OS_WIN32      /* POSIX complient OS. */

/********************************************************************************/
/****** RAVL behavour ***********************************************************/

/* Set the following define to 1 to have the Ravl IO system
 * to automatically use the type conversion mechanism when doing IO.
 * This is add alot of flexibity to IO operations but comes at the
 * price of larger executables and a slighty longer load times.
 */
#define RAVL_USE_IO_AUTO_TYPECONVERTER 1

/* Setting the following define to 1 will switch various routines to
 * use multi-thread implementations. Unfortunately this may mean changing
 * the USESLIBS to include the RavlThreads library for the directories
 * concerned. This is off by default as it generates slower code for single 
 * processor systems.
 */
#define RAVL_USE_PARALLEL 0


/********************************************************************************/
/****** OS Configuration/System includes ****************************************/

#define RAVL_USE_LARGEFILESUPPORT defined(__linux__)     /* Special 64 bit stat functions */
#define RAVL_LIMITED_FILENAMES 0                         /* have 8.3 filenames. */
#define RAVL_HAVE_UNIXDIRFUNCS RAVL_OS_POSIX             /* POSIX directory access ? */
#define RAVL_HAVE_REENTRANT_UNIXDIRFUNCS !defined(__cygwin__) /* Re-entrant directory functions. */
#define RAVL_HAVE_POSIX_THREADS_RWLOCK RAVL_OS_LINUX
#define RAVL_HAVE_PTHREAD_COND RAVL_OS_POSIX
#define RAVL_HAVE_BYTESWAP RAVL_OS_LINUX
#define RAVL_HAVE_NETDB_H  RAVL_OS_UNIX
#define RAVL_HAVE_UNISTD_H RAVL_OS_UNIX
#define RAVL_HAVE_SYS_SOCKET_H RAVL_OS_UNIX
#define RAVL_USE_TIMEB_H   RAVL_OS_WIN32
#define RAVL_USE_WINSOCK   RAVL_OS_WIN32
#define RAVL_HAVE_IO_H     RAVL_OS_WIN32

/* Sort out some flags to ensure we get the right functions from 
 * system headers. 
 */
#if !defined(__sgi__)
#define _GNU_SOURCE 1
#define _POSIX_SOURCE 1
#endif
#if defined(__linux__)
#define _ISOC9X_SOURCE 1
#endif

/********************************************************************************/
/****** Numerical functions and headers *****************************************/

#define RAVL_HAVE_VALUES_H !RAVL_OS_WIN32   /* have values.h        */
#define RAVL_HAVE_FLOAT_H  RAVL_OS_WIN32    /* have float.h         */
#define RAVL_HAVE_NAN_H    RAVL_OS_WIN32    /* have nan.h           */
#define RAVL_HAVE_IEEEFP_H !RAVL_OS_LINUX   /* have ieeefp.h        */
#define RAVL_HAVE_HYPOT    !RAVL_OS_WIN32   /* have hypot() in libm */
#define RAVL_HAVE_CBRT     0                /* have cbrt() in libm  */
#define RAVL_HAVE_ERF      !RAVL_OS_WIN32   /* have erf() and erfc() in libm  */

#define RAVL_HAVE_ISINF    RAVL_OS_LINUX    /* have isinf() in libm  */
#define RAVL_HAVE__FINITE  RAVL_OS_WIN32    /* have _finite() in libm  */
#define RAVL_HAVE_FINITE   (!RAVL_OS_LINUX && !RAVL_OS_WIN32)  /* have finite() in libm  */

#define RAVL_HAVE_ISNAN    RAVL_OS_LINUX    /* have isnan() in libm  */
#define RAVL_HAVE__ISNAN   RAVL_OS_WIN32    /* have _isnan() in libm  */
#define RAVL_HAVE_ISNAND   (!RAVL_OS_LINUX && !RAVL_OS_WIN32) /* have isnand() in libm  */

/********************************************************************************/
/****** Compiler/ C++ Library ***************************************************/

#define RAVL_HAVE_STD_NAMESPACE   RAVL_USE_GCC3           /* Use the 'std' namespace. */
#define RAVL_HAVE_ANSICPPHEADERS  !RAVL_COMPILER_MIPSPRO  /* Use ansi complient c++ headers, i.e without the .h */
#define RAVL_HAVE_EXCEPTIONS      1                       /* are exceptions enabled ? */
#define RAVL_HAVE_EXCEPTION_SPECS !RAVL_COMPILER_VISUALCPP /* throw(..) exceptions specs accepted ? */
#define RAVL_HAVE_RTTI            1                      /* is C++ Real Time Type Information available ? */
#define RAVL_HAVE_IOS_BINARY      !RAVL_COMPILER_MIPSPRO /* do we have ios::binary.  */
#define RAVL_HAVE_IOS_SEEKDIR     !RAVL_COMPILER_MIPSPRO /* else assume ios::seek_dir exists. */
#define RAVL_HAVE_STREAMSIZE      !RAVL_COMPILER_MIPSPRO
#define RAVL_HAVE_STDNAMESPACE    RAVL_COMPILER_GCC3    /* Use std namespace. */
#define RAVL_HAVE_STREAMASCLASS   !RAVL_COMPILER_GCC3   /* istream and ostream are classes not typedefs. */
#define RAVL_VISUALCPP_NAMESPACE_BUG RAVL_COMPILER_VISUALCPP
#define RAVL_ISTREAM_UNGET_BUG       RAVL_COMPILER_VISUALCPP
#define RAVL_NEW_ANSI_CXX_DRAFT   !defined(VISUAL_CPP) 

/* Define a macro so we can easily switch in and out exception specs
// for functions.
*/
#if RAVL_HAVE_EXCEPTION_SPECS
#define RAVL_THROW(x) throw(x)
#define RAVL_THROW2(x,y) throw(x,y)
#define RAVL_THROW3(x,y,z) throw(x,y,z)
#else
#define RAVL_THROW(x)
#define RAVL_THROW2(x,y)
#define RAVL_THROW3(x,y,z)
#endif

/********************************************************************************/
/****** Processor properties ****************************************************/

#define RAVL_LITTLEENDIAN RAVL_CPU_IX86    /* Little endian machine. */
#define RAVL_BIGENDIAN    !RAVL_CPU_IX86   /* Big endian machine. */
/* Yes there are other endian machines, but I've never actually met one. */

/* Setting the follow define to 1 will enable the use of MMX code. */
#define RAVL_USE_MMX (RAVL_CPU_IX86 && RAVL_COMPILER_GCC)

#endif
