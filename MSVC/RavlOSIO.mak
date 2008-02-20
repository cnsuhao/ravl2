


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlOSIO
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlOSIO
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlOSIO  $(OPTOBJDIR)/FileSequence.obj $(OPTOBJDIR)/SequenceIO.obj $(OPTOBJDIR)/FileListIO.obj $(OPTOBJDIR)/CompositeStream.obj $(OPTOBJDIR)/FileFormatComposite.obj $(OPTOBJDIR)/PlayList.obj $(OPTOBJDIR)/SubSequenceSpec.obj $(OPTOBJDIR)/EditSpec.obj $(OPTOBJDIR)/FileFormatDynamic.obj $(OPTOBJDIR)/DynamicLink.obj $(OPTOBJDIR)/RavlOSIOMustLink.obj
	@echo -- making $(OPTLIBDIR)/RavlOSIO.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlOSIO.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlOSIO  $(DEBUGOBJDIR)/FileSequence.obj $(DEBUGOBJDIR)/SequenceIO.obj $(DEBUGOBJDIR)/FileListIO.obj $(DEBUGOBJDIR)/CompositeStream.obj $(DEBUGOBJDIR)/FileFormatComposite.obj $(DEBUGOBJDIR)/PlayList.obj $(DEBUGOBJDIR)/SubSequenceSpec.obj $(DEBUGOBJDIR)/EditSpec.obj $(DEBUGOBJDIR)/FileFormatDynamic.obj $(DEBUGOBJDIR)/DynamicLink.obj $(DEBUGOBJDIR)/RavlOSIOMustLink.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlOSIO.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlOSIO.lib $(DEBUGOBJDIR)/*.obj

setupRavlOSIO::
        echo --- creating dir for RavlOSIO
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/FileSequence.obj: .././OS/IO/FileSequence.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileSequence.obj .././OS/IO/FileSequence.cc

$(DEBUGOBJDIR)/FileSequence.obj: .././OS/IO/FileSequence.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileSequence.obj .././OS/IO/FileSequence.cc

$(OPTOBJDIR)/SequenceIO.obj: .././OS/IO/SequenceIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SequenceIO.obj .././OS/IO/SequenceIO.cc

$(DEBUGOBJDIR)/SequenceIO.obj: .././OS/IO/SequenceIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SequenceIO.obj .././OS/IO/SequenceIO.cc

$(OPTOBJDIR)/FileListIO.obj: .././OS/IO/FileListIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileListIO.obj .././OS/IO/FileListIO.cc

$(DEBUGOBJDIR)/FileListIO.obj: .././OS/IO/FileListIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileListIO.obj .././OS/IO/FileListIO.cc

$(OPTOBJDIR)/CompositeStream.obj: .././OS/IO/CompositeStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CompositeStream.obj .././OS/IO/CompositeStream.cc

$(DEBUGOBJDIR)/CompositeStream.obj: .././OS/IO/CompositeStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CompositeStream.obj .././OS/IO/CompositeStream.cc

$(OPTOBJDIR)/FileFormatComposite.obj: .././OS/IO/FileFormatComposite.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileFormatComposite.obj .././OS/IO/FileFormatComposite.cc

$(DEBUGOBJDIR)/FileFormatComposite.obj: .././OS/IO/FileFormatComposite.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileFormatComposite.obj .././OS/IO/FileFormatComposite.cc

$(OPTOBJDIR)/PlayList.obj: .././OS/IO/PlayList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PlayList.obj .././OS/IO/PlayList.cc

$(DEBUGOBJDIR)/PlayList.obj: .././OS/IO/PlayList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PlayList.obj .././OS/IO/PlayList.cc

$(OPTOBJDIR)/SubSequenceSpec.obj: .././OS/IO/SubSequenceSpec.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SubSequenceSpec.obj .././OS/IO/SubSequenceSpec.cc

$(DEBUGOBJDIR)/SubSequenceSpec.obj: .././OS/IO/SubSequenceSpec.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SubSequenceSpec.obj .././OS/IO/SubSequenceSpec.cc

$(OPTOBJDIR)/EditSpec.obj: .././OS/IO/EditSpec.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EditSpec.obj .././OS/IO/EditSpec.cc

$(DEBUGOBJDIR)/EditSpec.obj: .././OS/IO/EditSpec.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EditSpec.obj .././OS/IO/EditSpec.cc

$(OPTOBJDIR)/FileFormatDynamic.obj: .././OS/IO/FileFormatDynamic.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileFormatDynamic.obj .././OS/IO/FileFormatDynamic.cc

$(DEBUGOBJDIR)/FileFormatDynamic.obj: .././OS/IO/FileFormatDynamic.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileFormatDynamic.obj .././OS/IO/FileFormatDynamic.cc

$(OPTOBJDIR)/DynamicLink.obj: .././OS/IO/DynamicLink.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DynamicLink.obj .././OS/IO/DynamicLink.cc

$(DEBUGOBJDIR)/DynamicLink.obj: .././OS/IO/DynamicLink.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DynamicLink.obj .././OS/IO/DynamicLink.cc

$(OPTOBJDIR)/RavlOSIOMustLink.obj: .././OS/IO/RavlOSIOMustLink.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RavlOSIOMustLink.obj .././OS/IO/RavlOSIOMustLink.cc

$(DEBUGOBJDIR)/RavlOSIOMustLink.obj: .././OS/IO/RavlOSIOMustLink.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RavlOSIOMustLink.obj .././OS/IO/RavlOSIOMustLink.cc


