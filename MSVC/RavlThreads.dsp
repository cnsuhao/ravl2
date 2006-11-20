# Microsoft Developer Studio Project File - Name="RavlThreads" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlThreads - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlThreads.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlThreads.mak" CFG="RavlThreads - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlThreads - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlThreads - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlThreads"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlThreads"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /Gm /GR /GX /ZI /Od /MDd  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "_DEBUG" /D "VISUAL_CPP" /D "_LIB" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /GZ /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ENDIF 

# Begin Target

# Name "RavlThreads - Win32 Release"
# Name "RavlThreads - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\OS\Threads\Posix\Thread.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\Mutex.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\ConditionalMutex.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\Semaphore.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\RWLock.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\SemaphoreRC.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\MTLockImpl.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\ThreadEvent.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\AMutexImpl.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\RCRWLock.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\MessageQueue.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\LaunchThread.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\TickerTrigger.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\TimedTriggerQueue.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\Signal.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\SignalConnectionSet.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\OS\Threads\Posix\Thread.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header Thread.hh

"C:\Build\inc\Ravl\Threads\Thread.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\Thread.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header Thread.hh

"C:\Build\inc\Ravl\Threads\Thread.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\Thread.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\Mutex.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header Mutex.hh

"C:\Build\inc\Ravl\Threads\Mutex.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\Mutex.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header Mutex.hh

"C:\Build\inc\Ravl\Threads\Mutex.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\Mutex.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\ConditionalMutex.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header ConditionalMutex.hh

"C:\Build\inc\Ravl\Threads\ConditionalMutex.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\ConditionalMutex.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header ConditionalMutex.hh

"C:\Build\inc\Ravl\Threads\ConditionalMutex.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\ConditionalMutex.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\Semaphore.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header Semaphore.hh

"C:\Build\inc\Ravl\Threads\Semaphore.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\Semaphore.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header Semaphore.hh

"C:\Build\inc\Ravl\Threads\Semaphore.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\Semaphore.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\RWLock.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header RWLock.hh

"C:\Build\inc\Ravl\Threads\RWLock.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\RWLock.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header RWLock.hh

"C:\Build\inc\Ravl\Threads\RWLock.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\RWLock.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\SemaphoreRC.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header SemaphoreRC.hh

"C:\Build\inc\Ravl\Threads\SemaphoreRC.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\SemaphoreRC.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header SemaphoreRC.hh

"C:\Build\inc\Ravl\Threads\SemaphoreRC.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\SemaphoreRC.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\ThreadEvent.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header ThreadEvent.hh

"C:\Build\inc\Ravl\Threads\ThreadEvent.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\ThreadEvent.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header ThreadEvent.hh

"C:\Build\inc\Ravl\Threads\ThreadEvent.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\ThreadEvent.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Posix\RCRWLock.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header RCRWLock.hh

"C:\Build\inc\Ravl\Threads\RCRWLock.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\RCRWLock.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header RCRWLock.hh

"C:\Build\inc\Ravl\Threads\RCRWLock.hh" :  "" ""
	copy ..\.\OS\Threads\Posix\RCRWLock.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\MessageQueue.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header MessageQueue.hh

"C:\Build\inc\Ravl\Threads\MessageQueue.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\MessageQueue.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header MessageQueue.hh

"C:\Build\inc\Ravl\Threads\MessageQueue.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\MessageQueue.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\LaunchThread.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header LaunchThread.hh

"C:\Build\inc\Ravl\Threads\LaunchThread.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\LaunchThread.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header LaunchThread.hh

"C:\Build\inc\Ravl\Threads\LaunchThread.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\LaunchThread.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\TickerTrigger.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header TickerTrigger.hh

"C:\Build\inc\Ravl\Threads\TickerTrigger.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\TickerTrigger.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header TickerTrigger.hh

"C:\Build\inc\Ravl\Threads\TickerTrigger.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\TickerTrigger.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\TimedTriggerQueue.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header TimedTriggerQueue.hh

"C:\Build\inc\Ravl\Threads\TimedTriggerQueue.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\TimedTriggerQueue.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header TimedTriggerQueue.hh

"C:\Build\inc\Ravl\Threads\TimedTriggerQueue.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\TimedTriggerQueue.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\Signal.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header Signal.hh

"C:\Build\inc\Ravl\Threads\Signal.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\Signal.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header Signal.hh

"C:\Build\inc\Ravl\Threads\Signal.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\Signal.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\Signal1.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header Signal1.hh

"C:\Build\inc\Ravl\Threads\Signal1.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\Signal1.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header Signal1.hh

"C:\Build\inc\Ravl\Threads\Signal1.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\Signal1.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\Signal2.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header Signal2.hh

"C:\Build\inc\Ravl\Threads\Signal2.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\Signal2.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header Signal2.hh

"C:\Build\inc\Ravl\Threads\Signal2.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\Signal2.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\Signal3.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header Signal3.hh

"C:\Build\inc\Ravl\Threads\Signal3.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\Signal3.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header Signal3.hh

"C:\Build\inc\Ravl\Threads\Signal3.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\Signal3.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\SignalConnectionSet.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header SignalConnectionSet.hh

"C:\Build\inc\Ravl\Threads\SignalConnectionSet.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\SignalConnectionSet.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header SignalConnectionSet.hh

"C:\Build\inc\Ravl\Threads\SignalConnectionSet.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\SignalConnectionSet.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Threads\Tools\MTPriQueueL.hh

!IF  "$(CFG)" == "RavlThreads - Win32 Release"

# Begin Custom Build - Install Header MTPriQueueL.hh

"C:\Build\inc\Ravl\Threads\MTPriQueueL.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\MTPriQueueL.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlThreads - Win32 Debug"

# Begin Custom Build - Install Header MTPriQueueL.hh

"C:\Build\inc\Ravl\Threads\MTPriQueueL.hh" :  "" ""
	copy ..\.\OS\Threads\Tools\MTPriQueueL.hh C:\Build\inc\Ravl\Threads

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
