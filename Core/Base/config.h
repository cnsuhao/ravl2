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

#define USE_GCC30 0

/******* AMMA/QMAKE COMPATIBILITY *******/
#if !defined(RAVL_CHECK)
#ifdef AMMA_CHECK
#define RAVL_CHECK 1
#else
#define RAVL_CHECK 0
#endif
#endif
/****************************************/

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


#if !defined(__sgi__)
#define _GNU_SOURCE 1
#define _POSIX_SOURCE 1
#endif
#if defined(__linux__)
#define _ISOC9X_SOURCE 1
#endif
#if !defined(__sgi__)
#define RAVL_HAVE_IOS_BINARY 1
#else
#define RAVL_HAVE_IOS_BINARY 0
#endif

#if !defined(__sol2__)
#define RAVL_HAVE_POSIX_THREADS_RWLOCK 1
#else
#define RAVL_HAVE_POSIX_THREADS_RWLOCK 0
#endif

#if !defined(__linux__)
#define RAVL_LITTLEENDIAN 0
#define RAVL_BIGENDIAN 1
#define RAVL_HAVE_STD_NAMESPACE 0
#define RAVL_HAVE_BYTESWAP 0 
#else
#define RAVL_LITTLEENDIAN 1
#define RAVL_BIGENDIAN 0
#define RAVL_HAVE_STD_NAMESPACE 1
#define RAVL_HAVE_BYTESWAP 1
#define RAVL_HAVE_IEEEFP_H 0
#endif

#define RAVL_HAVE_EXCEPTIONS 1
#define RAVL_HAVE_RTTI 1

#if defined(__sgi__)
#define RAVL_HAVE_ANSICPPHEADERS 0
#define RAVL_HAVE_IOS_SEEKDIR 0 /* else assume ios::seek_dir exists. */
#define RAVL_HAVE_STREAMSIZE 0
#else
#define RAVL_HAVE_ANSICPPHEADERS 1
#if !defined(VISUAL_CPP)
#define RAVL_HAVE_STREAMSIZE 1
#if USE_GCC30
#define RAVL_HAVE_IOS_SEEKDIR 1 /* use ios::seekdir */
#else
#define RAVL_HAVE_IOS_SEEKDIR 0 /* use ios::seekdir */
#endif
#else
#define RAVL_HAVE_STREAMSIZE 0
#define RAVL_HAVE_IOS_SEEKDIR 0 /* use ios::seekdir */
#endif
#endif

#if defined(VISUAL_CPP) || defined(__cygwin__)
#define RAVL_HAVE_VALUES_H 0
#define RAVL_HAVE_FLOAT_H 1
#define RAVL_HAVE_PTHREAD_COND 0
#define RAVL_HAVE_HYPOT 0
#define RAVL_HAVE_NAN_H 0
#define RAVL_HAVE_IEEEFP_H 0
#define RAVL_HAVE_UNISTD_H 0
#define RAVL_HAVE_IO_H 1
#define RAVL_HAVE_NETDB_H 0
#define RAVL_HAVE_EXCEPTION_SPECS 0
#define RAVL_HAVE_SYS_SOCKET_H 0
#define RAVL_USE_WINSOCK 1
#define RAVL_HAVE_UNIXDIRFUNCS 0
#else
#define RAVL_HAVE_VALUES_H 1
#define RAVL_HAVE_FLOAT_H 1
#define RAVL_HAVE_PTHREAD_COND 1
#define RAVL_HAVE_HYPOT 1  /* Have the maths hypot(x,y) function ? */
#define RAVL_HAVE_UNISTD_H 1
#define RAVL_HAVE_IO_H 0
#define RAVL_HAVE_NETDB_H 1
#define RAVL_HAVE_EXCEPTION_SPECS 1
#define RAVL_HAVE_SYS_SOCKET_H 1
#define RAVL_USE_WINSOCK 0
#define RAVL_HAVE_UNIXDIRFUNCS 1
#if !defined(__linux__)
#define RAVL_HAVE_IEEEFP_H 1
#define RAVL_HAVE_NAN_H 1
#else
#define RAVL_HAVE_IEEEFP_H 0
#define RAVL_HAVE_NAN_H 0
#endif
#endif

#if defined(VISUAL_CPP) 
#define RAVL_VISUALCPP_NAMESPACE_BUG 1
#define RAVL_ISTREAM_UNGET_BUG 1
#define RAVL_NEW_ANSI_CXX_DRAFT 0
#define RAVL_STRICT_NAMESPACES 1
#define RAVL_USE_TIMEB_H 1
#else
#define RAVL_VISUALCPP_NAMESPACE_BUG 0
#define RAVL_ISTREAM_UNGET_BUG 0
#define RAVL_NEW_ANSI_CXX_DRAFT 1
#define RAVL_STRICT_NAMESPACES 0
#define RAVL_USE_TIMEB_H 0
#endif

#define RAVL_HAVE_REENTRANT_UNIXDIRFUNCS 1
#define RAVL_LIMITED_FILENAMES 0

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


#endif
