


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
DEBUGOBJDIR = c:\Build/win32/debug/obj/RavlDPMT
DEBUGLIBDIR = c:\Build/win32/debug/lib

OPTOBJDIR = c:\Build/win32/opt/obj/RavlDPMT
OPTLIBDIR = c:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/MTIOConnect.obj $(OPTOBJDIR)/PlayControl.obj $(OPTOBJDIR)/Governor.obj $(OPTOBJDIR)/Blackboard.obj
	@echo -- making $(OPTLIBDIR)/RavlDPMT.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlDPMT.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/MTIOConnect.obj $(DEBUGOBJDIR)/PlayControl.obj $(DEBUGOBJDIR)/Governor.obj $(DEBUGOBJDIR)/Blackboard.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlDPMT.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlDPMT.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlDPMT
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/MTIOConnect.obj: .././OS/DataProc/MTIOConnect.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MTIOConnect.obj .././OS/DataProc/MTIOConnect.cc

$(DEBUGOBJDIR)/MTIOConnect.obj: .././OS/DataProc/MTIOConnect.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MTIOConnect.obj .././OS/DataProc/MTIOConnect.cc

$(OPTOBJDIR)/PlayControl.obj: .././OS/DataProc/PlayControl.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PlayControl.obj .././OS/DataProc/PlayControl.cc

$(DEBUGOBJDIR)/PlayControl.obj: .././OS/DataProc/PlayControl.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PlayControl.obj .././OS/DataProc/PlayControl.cc

$(OPTOBJDIR)/Governor.obj: .././OS/DataProc/Governor.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Governor.obj .././OS/DataProc/Governor.cc

$(DEBUGOBJDIR)/Governor.obj: .././OS/DataProc/Governor.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Governor.obj .././OS/DataProc/Governor.cc

$(OPTOBJDIR)/Blackboard.obj: .././OS/DataProc/Blackboard.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Blackboard.obj .././OS/DataProc/Blackboard.cc

$(DEBUGOBJDIR)/Blackboard.obj: .././OS/DataProc/Blackboard.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Blackboard.obj .././OS/DataProc/Blackboard.cc


