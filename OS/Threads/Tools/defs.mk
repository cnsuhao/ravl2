# This file is part of RAVL, Recognition And Vision Library 
# Copyright (C) 2001, University of Surrey
# This code may be redistributed under the terms of the GNU Lesser
# General Public License (LGPL). See the lgpl.licence file for details or
# see http://www.gnu.org/copyleft/lesser.html
# file-header-ends-here
##########################################################
#! rcsid="$Id$"
#! file="Ravl/OS/Threads/Tools/defs.mk"

DESCRIPTION=Threading tools

PACKAGE=Ravl/Threads

HEADERS=MessageQueue.hh LaunchThread.hh TickerTrigger.hh \
 TimedTriggerQueue.hh Signal.hh Signal1.hh Signal2.hh Signal3.hh \
 SignalConnectionSet.hh MTPriQueueL.hh
#  EventHandler.hh  TimedEventQueue.hh \
# EventHandlerRef.hh

SOURCES=MessageQueue.cc LaunchThread.cc TickerTrigger.cc \
 TimedTriggerQueue.cc Signal.cc  SignalConnectionSet.cc

# EventHandler.cc  TimedEventQueue.cc

EHT=Ravl.API.OS.Signals.html

PLIB=RavlThreads

LIBDEPS=RavlThreadTools.def

USESLIBS = RavlThreads RavlOS

EXAMPLES= exSignal.cc exSignal1.cc exSignal2.cc exLaunchThread.cc testAtomicSpeed.cc

TESTEXES = testLaunchThread.cc testTickerTrigger.cc testTimedTriggerQueue.cc testSignal.cc testAtomic.cc

