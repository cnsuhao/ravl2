# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
#############################################
#! rcsid="$Id$"
#! file="Ravl/OS/Threads/Posix/defs.mk"

DESCRIPTION = Posix thread interface.

#ANSIFLAG= 

PACKAGE = Ravl/Threads

HEADERS = Thread.hh Mutex.hh ConditionalMutex.hh Semaphore.hh RWLock.hh \
 SemaphoreRC.hh ThreadEvent.hh

SOURCES = Thread.cc Mutex.cc ConditionalMutex.cc Semaphore.cc RWLock.cc \
 SemaphoreRC.cc MTLockImpl.cc ThreadEvent.cc AMutexImpl.cc

PLIB = RavlThreads

USESLIBS = RavlCore posixThreads RavlOS

TESTEXES = testRWLock.cc

EXAMPLES = exThread.cc
