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
 * These checks may significantly slow code, but are helpful when looking for more 
 * obscure bugs.
 */
#ifdef QMAKE_PARANOID
#define RAVL_PARANOID(x) x
#else
#define RAVL_PARANOID(x)
#endif

/********************************************************************************/
/***** Detect the OS, compiler and processor type being used. *******************/

#if !defined(WIN32)
#define RAVL_COMPILER_GCC defined(__GNUC__)                        /* GNU compiler ? */
#define RAVL_COMPILER_GCC2 (defined(__GNUC__) && (__GNUC__ < 3))   /* gcc 2.x */
#define RAVL_COMPILER_GCC3 (defined(__GNUC__) && (__GNUC__ >= 3))  /* gcc 3.x */
#define RAVL_COMPILER_MIPSPRO (!defined(__GNUC__) && defined(__sgi))   /* MIPS Pro compiler */
#define RAVL_COMPILER_VISUALCPP (!defined(__GNUC__) && defined(WIN32)) /* Visual C++ */
#define RAVL_COMPILER_VISUALCPPNET (!defined(__GNUC__) && defined(WIN32) && (_MSC_VER >= 1300)) /* Visual C++ .NET*/

#define RAVL_CPU_IX86  defined(__i386__)  /* 386 base varient. */
#define RAVL_CPU_SPARC defined(__sparc)   /* sun sparc based system. */
#define RAVL_CPU_MIPS  defined(__mips)    /* mips */
#define RAVL_CPU_ALPHA defined(__alpha)   /* alpha based system */

#define RAVL_OS_LINUX   defined(__linux__) /* Linux based OS. */
#define RAVL_OS_WIN32   defined(WIN32)     /* Windows platform. */
#define RAVL_OS_IRIX    defined(__sgi__)   /* IRIX.      */
#define RAVL_OS_SOLARIS defined(__sun)     /* Solaris.   */
#define RAVL_OS_OSF     defined(__osf__)   /* OSF.       */
#define RAVL_OS_CYGWIN  defined(__CYGWIN__) /* Cygwin is a windows/unix hybrid */
#else
/* Unfortunatly the Visual C++ preprocessor doesn't accept defined() as anything but part 
   of an #if or #elif so the compiler selection breaks. Here are the settings for a windows box.
*/
#define RAVL_COMPILER_GCC       0
#define RAVL_COMPILER_GCC2      0
#define RAVL_COMPILER_GCC3      0
#define RAVL_COMPILER_MIPSPRO   0
#define RAVL_COMPILER_VISUALCPP 1
#define RAVL_COMPILER_VISUALCPPNET (_MSC_VER >= 1300)

#define RAVL_CPU_IX86  1
#define RAVL_CPU_SPARC 0
#define RAVL_CPU_MIPS  0
#define RAVL_CPU_ALPHA 0

#define RAVL_OS_LINUX   0
#define RAVL_OS_WIN32   1
#define RAVL_OS_IRIX    0
#define RAVL_OS_SOLARIS 0
#define RAVL_OS_OSF     0
#define RAVL_OS_CYGWIN  0
#endif

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

#define RAVL_USE_LARGEFILESUPPORT RAVL_OS_LINUX    /* Special 64 bit filehandling functions like stat64. */
#define RAVL_LIMITED_FILENAMES 0                   /* have 8.3 filenames. */
#define RAVL_HAVE_UNIXDIRFUNCS RAVL_OS_POSIX       /* Unix style directory access ? */
#define RAVL_HAVE_REENTRANT_UNIXDIRFUNCS !RAVL_OS_CYGWIN /* Re-entrant directory functions. */
#define RAVL_HAVE_POSIX_THREADS_RWLOCK RAVL_OS_LINUX
#define RAVL_HAVE_PTHREAD_COND RAVL_OS_POSIX
#define RAVL_HAVE_BYTESWAP     RAVL_OS_LINUX
#define RAVL_HAVE_NETDB_H      RAVL_OS_UNIX
#define RAVL_HAVE_UNISTD_H     RAVL_OS_UNIX       /* have unistd.h */
#define RAVL_HAVE_SYS_SOCKET_H RAVL_OS_UNIX       /* have sys/socket.h  */
#define RAVL_HAVE_TERMIOS      RAVL_OS_UNIX       /* have termios for controlling serial ports. */
#define RAVL_USE_TIMEB_H       RAVL_OS_WIN32
#define RAVL_HAVE_PROCESS_H    RAVL_OS_WIN32      /* have process.h */
#define RAVL_USE_WINSOCK       RAVL_OS_WIN32
#define RAVL_HAVE_IO_H         RAVL_OS_WIN32
#define RAVL_HAVE_SYS_TIME_H   (!RAVL_OS_SOLARIS && !RAVL_OS_WIN32) /* Have <sys/time.h> */
#define RAVL_HAVE_YIELD        (RAVL_OS_WIN32 || RAVL_OS_SOLARIS)   /* have yield() */
#define RAVL_HAVE_SCHED_YIELD  (!RAVL_OS_WIN32 && !RAVL_OS_SOLARIS) /* have sched_yield() */
#define RAVL_HAVE_SCHED_H      !RAVL_OS_WIN32     /* have <sched.h> */
#define RAVL_HAVE_THREAD_H     RAVL_OS_SOLARIS    /* have <thread.h> (solaris threads.) */
#define RAVL_HAVE_THR_YIELD    RAVL_OS_SOLARIS    /* have thr_yield() (solaris threads.)  */
#define RAVL_READDIR_R_NOBUFF  RAVL_OS_OSF        /* readdir_r has no buffer argument. */
#define RAVL_TIMET_IS_INT      !RAVL_OS_IRIX      /* time_t is an int or long. IRIX uses a struct, effects stat() results. */
#define RAVL_HAVE_PWD_H        (RAVL_OS_UNIX || RAVL_OS_CYGWIN)       /* have <pwd.h> */
#define RAVL_ERRNO_IS_FUNC     0                  /* errno should be used as function. i.e. errno() for use with threaded code. */
#define RAVL_HAVE_GETPWNAM_R   (!RAVL_OS_LINUX && !RAVL_OS_CYGWIN)  /* have reentrant getpwnam_r */
#define RAVL_HAVE_GETPWUID_R   (!RAVL_OS_LINUX && !RAVL_OS_CYGWIN)  /* have reentrant getpwnam_r */
#define RAVL_HAVE_GETPW_RET_PW !RAVL_OS_OSF     /* Pass pointer to result ptr as last argument for  getpwuid_r, getpwnam_r */
#define RAVL_HAVE_GETPW_WITH_RESULT  RAVL_OS_IRIX  || RAVL_OS_SOLARIS /* Pass pointer to result ptr as last argument for  getpwuid_r, getpwnam_r */
#define RAVL_HAVE_HSTRERROR    (RAVL_OS_IRIX || RAVL_OS_LINUX)  /* have hstrerror, otherwise use strerror. */
#define RAVL_HAVE_SOCKLEN_T    (RAVL_OS_LINUX || RAVL_OS_SOLARIS)  /* Have socklen_t */

/********************************************************************************/
/****** Processor properties ****************************************************/

#define RAVL_LITTLEENDIAN RAVL_CPU_IX86    /* Little endian machine. */
#define RAVL_BIGENDIAN    !RAVL_CPU_IX86   /* Big endian machine. */
/* Yes there are other endian machines, but I've never actually met one. */

/* Setting the follow define to 1 will enable the use of MMX code. */
#define RAVL_USE_MMX (RAVL_CPU_IX86 && RAVL_COMPILER_GCC)

/********************************************************************************/
/****** Numerical functions and headers *****************************************/

#define RAVL_HAVE_VALUES_H (!RAVL_OS_WIN32 && !RAVL_OS_CYGWIN)   /* have values.h        */
#define RAVL_HAVE_FLOAT_H  (RAVL_OS_WIN32  || RAVL_OS_CYGWIN) /* have float.h         */
#define RAVL_HAVE_NAN_H    (RAVL_OS_SOLARIS || RAVL_OS_IRIX) /* have nan.h           */
#define RAVL_HAVE_IEEEFP_H (RAVL_OS_SOLARIS || RAVL_OS_IRIX) /* have ieeefp.h        */
#define RAVL_HAVE_HYPOT    !RAVL_OS_WIN32   /* have hypot() in libm */
#define RAVL_HAVE_CBRT     0                /* have cbrt() in libm  */
#define RAVL_HAVE_ERF      (!RAVL_OS_WIN32 && !RAVL_OS_CYGWIN)   /* have erf() and erfc() in libm  */

#define RAVL_HAVE_ISINF    (RAVL_OS_LINUX || RAVL_OS_CYGWIN)    /* have isinf() in libm  */
#define RAVL_HAVE__FINITE  RAVL_OS_WIN32    /* have _finite() in libm  */
#define RAVL_HAVE_FINITE   (RAVL_OS_SOLARIS || RAVL_OS_IRIX || RAVL_OS_OSF)  /* have finite() in libm  */

#define RAVL_HAVE_ISNAN    (RAVL_OS_LINUX || RAVL_OS_OSF || RAVL_OS_CYGWIN)   /* have isnan() in libm  */
#define RAVL_HAVE__ISNAN   RAVL_OS_WIN32    /* have _isnan() in libm  */
#define RAVL_HAVE_ISNAND   (RAVL_OS_SOLARIS || RAVL_OS_IRIX) /* have isnand() in libm  */

/********************************************************************************/
/****** Compiler/ C++ Library ***************************************************/

#define RAVL_HAVE_STDNAMESPACE    (RAVL_COMPILER_GCC3 || RAVL_COMPILER_VISUALCPPNET) /* Use std namespace. */
#define RAVL_HAVE_ANSICPPHEADERS  (RAVL_COMPILER_GCC || RAVL_COMPILER_VISUALCPPNET) /* Use ansi complient c++ headers, i.e without the .h */
#define RAVL_HAVE_EXCEPTIONS      1                        /* are exceptions enabled ? */
#define RAVL_HAVE_EXCEPTION_H     !RAVL_COMPILER_VISUALCPP /* Have exception.h ? */
#define RAVL_HAVE_EXCEPTION_SPECS !RAVL_COMPILER_VISUALCPP /* throw(..) exceptions specs accepted ? */
#define RAVL_HAVE_RTTI            1                        /* is C++ Real Time Type Information available ? */
#define RAVL_HAVE_IOS_BINARY      !RAVL_COMPILER_MIPSPRO   /* do we have ios::binary.  */
#define RAVL_HAVE_IOS_SEEKDIR     (RAVL_HAVE_STDNAMESPACE || RAVL_COMPILER_GCC)  /* else assume ios::seek_dir exists. */
#define RAVL_HAVE_STREAMSIZE      (RAVL_HAVE_STDNAMESPACE || RAVL_COMPILER_GCC)  /* have streamsize type. */
#define RAVL_HAVE_STREAMASCLASS   !RAVL_HAVE_STDNAMESPACE    /* istream and ostream are classes not typedefs. */
#define RAVL_VISUALCPP_NAMESPACE_BUG RAVL_COMPILER_VISUALCPP /* Bug in namespace handling under Visual C++ 6.x */
#define RAVL_VISUALCPP_TYPENAME_BUG RAVL_COMPILER_VISUALCPP  /* Restrictions in using keyword 'typename' in Visual C++ 6.x */
#define RAVL_ISTREAM_UNGET_BUG    RAVL_COMPILER_VISUALCPP    /* Bug in stream unget under Visual C++ 6.x */
#define RAVL_NEW_ANSI_CXX_DRAFT   RAVL_COMPILER_GCC          /* The mainly effects the use of <> in templated friend declarations */
#define RAVL_HAVE_STRINGSTREAM    RAVL_COMPILER_GCC3         /* Use stringstream instead of strstream */

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
/* Sort out some flags to ensure we get the right functions from the system 
 * headers. 
 */

#if !RAVL_OS_IRIX
#ifndef _GNU_SOURCE
#define _GNU_SOURCE 1
#endif
#ifndef _POSIX_SOURCE
#define _POSIX_SOURCE 1
#endif
#endif

#if RAVL_OS_LINUX || RAVL_OS_CYGWIN
#ifndef _ISOC9X_SOURCE
#define _ISOC9X_SOURCE 1
#endif
#endif

#if RAVL_OS_OSF
#ifndef _OSF_SOURCE
#define _OSF_SOURCE 1
#endif
#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE 1
#endif
#ifndef _REENTRANT
#define _REENTRANT 1
#endif
#endif

#endif
