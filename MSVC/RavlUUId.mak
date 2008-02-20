


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlUUId
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlUUId
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlUUId  $(OPTOBJDIR)/UUId.obj
	@echo -- making $(OPTLIBDIR)/RavlUUId.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlUUId.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlUUId  $(DEBUGOBJDIR)/UUId.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlUUId.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlUUId.lib $(DEBUGOBJDIR)/*.obj

setupRavlUUId::
        echo --- creating dir for RavlUUId
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/UUId.obj: .././Contrib/UUId/UUId.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/UUId.obj .././Contrib/UUId/UUId.cc

$(DEBUGOBJDIR)/UUId.obj: .././Contrib/UUId/UUId.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/UUId.obj .././Contrib/UUId/UUId.cc


