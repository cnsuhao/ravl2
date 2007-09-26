#!/bin/sh
# This file is based on the GNU config.guess script

# This script attempts to guess a canonical system name.
#   Copyright (C) 1992, 1993 Free Software Foundation, Inc.
#
# This file is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.  */

#
# This script attempts to guess a canonical system name similar to
# config.sub.  If it succeeds, it prints the system name on stdout, and
# exits with 0.  Otherwise, it exits with 1.

UNAME_MACHINE=`(uname -m) 2>/dev/null` || UNAME_MACHINE=unknown
UNAME_SYSTEM=`(uname -s) 2>/dev/null` || UNAME_SYSTEM=unknown
UNAME_RELEASE=`(uname -r) 2>/dev/null` || UNAME_RELEASE=unknown

# Note: order is significant - the case branches are not exclusive.
ID="${UNAME_MACHINE}:${UNAME_SYSTEM}:${UNAME_RELEASE}"
case $ID in
    *:IRIX64:*)
	echo "sgi" ;
	exit 0 ;;
    sun4*:SunOS:5.9)
	echo "sol2_9"
	exit 0 ;;
    i*86:Linux:*)
	echo "linux"
	exit 0 ;;
    x86_64:Linux:*)
	echo "linux64"
	exit 0 ;;
    i*86:CYGWIN*:*)
	echo "cygwin"
	exit 0 ;;
    alpha:OSF1:*)
	echo "alpha"
	exit 0 ;;
    alpha:Linux:*)
	echo "linux_alpha"
	exit 0 ;;
    'Power Macintosh':Darwin:*)
	echo "macosx"
	exit 0 ;;
    i386:Darwin:*)
        echo "macosx386"
        exit 0 ;;
    *:*:*)
	echo "unknown"
	echo "Unknown machine $ID " >&2
	exit 0 ;;
esac

# /IRIX64/        {print "sgi"; exit;}\
# /SunOS [^ ]* 4/ {print "sun4"; exit;}\
# /SunOS [^ ]* 5/ {print "sol2"; exit;}\
# /OSF.*alpha/    {print "alpha"; exit;}\
# /Linux/ {print "linux"; exit}\
# /ULTRIX.*RISC/  {print "mips"; exit;}'
