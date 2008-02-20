


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" /I "C:\Program Files\Microsoft Platform SDK for Windows Server 2003 R2\Include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlThreads
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlThreads
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlThreads  $(OPTOBJDIR)/Thread.obj $(OPTOBJDIR)/Mutex.obj $(OPTOBJDIR)/ConditionalMutex.obj $(OPTOBJDIR)/Semaphore.obj $(OPTOBJDIR)/RWLock.obj $(OPTOBJDIR)/SemaphoreRC.obj $(OPTOBJDIR)/MTLockImpl.obj $(OPTOBJDIR)/ThreadEvent.obj $(OPTOBJDIR)/AMutexImpl.obj $(OPTOBJDIR)/RCRWLock.obj $(OPTOBJDIR)/MessageQueue.obj $(OPTOBJDIR)/LaunchThread.obj $(OPTOBJDIR)/TickerTrigger.obj $(OPTOBJDIR)/TimedTriggerQueue.obj $(OPTOBJDIR)/Signal.obj $(OPTOBJDIR)/SignalConnectionSet.obj
	@echo -- making $(OPTLIBDIR)/RavlThreads.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlThreads.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlThreads  $(DEBUGOBJDIR)/Thread.obj $(DEBUGOBJDIR)/Mutex.obj $(DEBUGOBJDIR)/ConditionalMutex.obj $(DEBUGOBJDIR)/Semaphore.obj $(DEBUGOBJDIR)/RWLock.obj $(DEBUGOBJDIR)/SemaphoreRC.obj $(DEBUGOBJDIR)/MTLockImpl.obj $(DEBUGOBJDIR)/ThreadEvent.obj $(DEBUGOBJDIR)/AMutexImpl.obj $(DEBUGOBJDIR)/RCRWLock.obj $(DEBUGOBJDIR)/MessageQueue.obj $(DEBUGOBJDIR)/LaunchThread.obj $(DEBUGOBJDIR)/TickerTrigger.obj $(DEBUGOBJDIR)/TimedTriggerQueue.obj $(DEBUGOBJDIR)/Signal.obj $(DEBUGOBJDIR)/SignalConnectionSet.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlThreads.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlThreads.lib $(DEBUGOBJDIR)/*.obj

setupRavlThreads::
        echo --- creating dir for RavlThreads
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/Thread.obj: .././OS/Threads/Posix/Thread.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Thread.obj .././OS/Threads/Posix/Thread.cc

$(DEBUGOBJDIR)/Thread.obj: .././OS/Threads/Posix/Thread.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Thread.obj .././OS/Threads/Posix/Thread.cc

$(OPTOBJDIR)/Mutex.obj: .././OS/Threads/Posix/Mutex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Mutex.obj .././OS/Threads/Posix/Mutex.cc

$(DEBUGOBJDIR)/Mutex.obj: .././OS/Threads/Posix/Mutex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Mutex.obj .././OS/Threads/Posix/Mutex.cc

$(OPTOBJDIR)/ConditionalMutex.obj: .././OS/Threads/Posix/ConditionalMutex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ConditionalMutex.obj .././OS/Threads/Posix/ConditionalMutex.cc

$(DEBUGOBJDIR)/ConditionalMutex.obj: .././OS/Threads/Posix/ConditionalMutex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ConditionalMutex.obj .././OS/Threads/Posix/ConditionalMutex.cc

$(OPTOBJDIR)/Semaphore.obj: .././OS/Threads/Posix/Semaphore.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Semaphore.obj .././OS/Threads/Posix/Semaphore.cc

$(DEBUGOBJDIR)/Semaphore.obj: .././OS/Threads/Posix/Semaphore.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Semaphore.obj .././OS/Threads/Posix/Semaphore.cc

$(OPTOBJDIR)/RWLock.obj: .././OS/Threads/Posix/RWLock.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RWLock.obj .././OS/Threads/Posix/RWLock.cc

$(DEBUGOBJDIR)/RWLock.obj: .././OS/Threads/Posix/RWLock.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RWLock.obj .././OS/Threads/Posix/RWLock.cc

$(OPTOBJDIR)/SemaphoreRC.obj: .././OS/Threads/Posix/SemaphoreRC.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SemaphoreRC.obj .././OS/Threads/Posix/SemaphoreRC.cc

$(DEBUGOBJDIR)/SemaphoreRC.obj: .././OS/Threads/Posix/SemaphoreRC.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SemaphoreRC.obj .././OS/Threads/Posix/SemaphoreRC.cc

$(OPTOBJDIR)/MTLockImpl.obj: .././OS/Threads/Posix/MTLockImpl.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MTLockImpl.obj .././OS/Threads/Posix/MTLockImpl.cc

$(DEBUGOBJDIR)/MTLockImpl.obj: .././OS/Threads/Posix/MTLockImpl.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MTLockImpl.obj .././OS/Threads/Posix/MTLockImpl.cc

$(OPTOBJDIR)/ThreadEvent.obj: .././OS/Threads/Posix/ThreadEvent.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ThreadEvent.obj .././OS/Threads/Posix/ThreadEvent.cc

$(DEBUGOBJDIR)/ThreadEvent.obj: .././OS/Threads/Posix/ThreadEvent.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ThreadEvent.obj .././OS/Threads/Posix/ThreadEvent.cc

$(OPTOBJDIR)/AMutexImpl.obj: .././OS/Threads/Posix/AMutexImpl.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AMutexImpl.obj .././OS/Threads/Posix/AMutexImpl.cc

$(DEBUGOBJDIR)/AMutexImpl.obj: .././OS/Threads/Posix/AMutexImpl.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AMutexImpl.obj .././OS/Threads/Posix/AMutexImpl.cc

$(OPTOBJDIR)/RCRWLock.obj: .././OS/Threads/Posix/RCRWLock.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RCRWLock.obj .././OS/Threads/Posix/RCRWLock.cc

$(DEBUGOBJDIR)/RCRWLock.obj: .././OS/Threads/Posix/RCRWLock.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RCRWLock.obj .././OS/Threads/Posix/RCRWLock.cc

$(OPTOBJDIR)/MessageQueue.obj: .././OS/Threads/Tools/MessageQueue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MessageQueue.obj .././OS/Threads/Tools/MessageQueue.cc

$(DEBUGOBJDIR)/MessageQueue.obj: .././OS/Threads/Tools/MessageQueue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MessageQueue.obj .././OS/Threads/Tools/MessageQueue.cc

$(OPTOBJDIR)/LaunchThread.obj: .././OS/Threads/Tools/LaunchThread.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LaunchThread.obj .././OS/Threads/Tools/LaunchThread.cc

$(DEBUGOBJDIR)/LaunchThread.obj: .././OS/Threads/Tools/LaunchThread.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LaunchThread.obj .././OS/Threads/Tools/LaunchThread.cc

$(OPTOBJDIR)/TickerTrigger.obj: .././OS/Threads/Tools/TickerTrigger.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TickerTrigger.obj .././OS/Threads/Tools/TickerTrigger.cc

$(DEBUGOBJDIR)/TickerTrigger.obj: .././OS/Threads/Tools/TickerTrigger.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TickerTrigger.obj .././OS/Threads/Tools/TickerTrigger.cc

$(OPTOBJDIR)/TimedTriggerQueue.obj: .././OS/Threads/Tools/TimedTriggerQueue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TimedTriggerQueue.obj .././OS/Threads/Tools/TimedTriggerQueue.cc

$(DEBUGOBJDIR)/TimedTriggerQueue.obj: .././OS/Threads/Tools/TimedTriggerQueue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TimedTriggerQueue.obj .././OS/Threads/Tools/TimedTriggerQueue.cc

$(OPTOBJDIR)/Signal.obj: .././OS/Threads/Tools/Signal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Signal.obj .././OS/Threads/Tools/Signal.cc

$(DEBUGOBJDIR)/Signal.obj: .././OS/Threads/Tools/Signal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Signal.obj .././OS/Threads/Tools/Signal.cc

$(OPTOBJDIR)/SignalConnectionSet.obj: .././OS/Threads/Tools/SignalConnectionSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SignalConnectionSet.obj .././OS/Threads/Tools/SignalConnectionSet.cc

$(DEBUGOBJDIR)/SignalConnectionSet.obj: .././OS/Threads/Tools/SignalConnectionSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SignalConnectionSet.obj .././OS/Threads/Tools/SignalConnectionSet.cc


