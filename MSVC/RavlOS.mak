


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlOS
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlOS
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/Date.obj $(OPTOBJDIR)/DateIO.obj $(OPTOBJDIR)/DeadLineTimer.obj $(OPTOBJDIR)/FilePermission.obj $(OPTOBJDIR)/Filename.obj $(OPTOBJDIR)/Directory.obj $(OPTOBJDIR)/FileSearch.obj $(OPTOBJDIR)/UserInfo.obj $(OPTOBJDIR)/FileOwner.obj $(OPTOBJDIR)/FileStream.obj $(OPTOBJDIR)/SerialIO.obj $(OPTOBJDIR)/SysLog.obj $(OPTOBJDIR)/OSProcess.obj $(OPTOBJDIR)/ChildOSProcess.obj $(OPTOBJDIR)/ChildOSProcessWait.obj $(OPTOBJDIR)/ChildOSProcessStream.obj $(OPTOBJDIR)/MailUser.obj $(OPTOBJDIR)/FileUser.obj $(OPTOBJDIR)/TextFileLine.obj $(OPTOBJDIR)/TextBuffer.obj $(OPTOBJDIR)/TextFile.obj $(OPTOBJDIR)/TextCursor.obj $(OPTOBJDIR)/TemplateFile.obj $(OPTOBJDIR)/TextFragment.obj $(OPTOBJDIR)/ConfigFile.obj $(OPTOBJDIR)/TemplateComplex.obj
	@echo -- making $(OPTLIBDIR)/RavlOS.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlOS.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/Date.obj $(DEBUGOBJDIR)/DateIO.obj $(DEBUGOBJDIR)/DeadLineTimer.obj $(DEBUGOBJDIR)/FilePermission.obj $(DEBUGOBJDIR)/Filename.obj $(DEBUGOBJDIR)/Directory.obj $(DEBUGOBJDIR)/FileSearch.obj $(DEBUGOBJDIR)/UserInfo.obj $(DEBUGOBJDIR)/FileOwner.obj $(DEBUGOBJDIR)/FileStream.obj $(DEBUGOBJDIR)/SerialIO.obj $(DEBUGOBJDIR)/SysLog.obj $(DEBUGOBJDIR)/OSProcess.obj $(DEBUGOBJDIR)/ChildOSProcess.obj $(DEBUGOBJDIR)/ChildOSProcessWait.obj $(DEBUGOBJDIR)/ChildOSProcessStream.obj $(DEBUGOBJDIR)/MailUser.obj $(DEBUGOBJDIR)/FileUser.obj $(DEBUGOBJDIR)/TextFileLine.obj $(DEBUGOBJDIR)/TextBuffer.obj $(DEBUGOBJDIR)/TextFile.obj $(DEBUGOBJDIR)/TextCursor.obj $(DEBUGOBJDIR)/TemplateFile.obj $(DEBUGOBJDIR)/TextFragment.obj $(DEBUGOBJDIR)/ConfigFile.obj $(DEBUGOBJDIR)/TemplateComplex.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlOS.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlOS.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlOS
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/Date.obj: .././OS/Time/Date.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Date.obj .././OS/Time/Date.cc

$(DEBUGOBJDIR)/Date.obj: .././OS/Time/Date.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Date.obj .././OS/Time/Date.cc

$(OPTOBJDIR)/DateIO.obj: .././OS/Time/DateIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DateIO.obj .././OS/Time/DateIO.cc

$(DEBUGOBJDIR)/DateIO.obj: .././OS/Time/DateIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DateIO.obj .././OS/Time/DateIO.cc

$(OPTOBJDIR)/DeadLineTimer.obj: .././OS/Time/DeadLineTimer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DeadLineTimer.obj .././OS/Time/DeadLineTimer.cc

$(DEBUGOBJDIR)/DeadLineTimer.obj: .././OS/Time/DeadLineTimer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DeadLineTimer.obj .././OS/Time/DeadLineTimer.cc

$(OPTOBJDIR)/FilePermission.obj: .././OS/FileSystem/FilePermission.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FilePermission.obj .././OS/FileSystem/FilePermission.cc

$(DEBUGOBJDIR)/FilePermission.obj: .././OS/FileSystem/FilePermission.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FilePermission.obj .././OS/FileSystem/FilePermission.cc

$(OPTOBJDIR)/Filename.obj: .././OS/FileSystem/Filename.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Filename.obj .././OS/FileSystem/Filename.cc

$(DEBUGOBJDIR)/Filename.obj: .././OS/FileSystem/Filename.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Filename.obj .././OS/FileSystem/Filename.cc

$(OPTOBJDIR)/Directory.obj: .././OS/FileSystem/Directory.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Directory.obj .././OS/FileSystem/Directory.cc

$(DEBUGOBJDIR)/Directory.obj: .././OS/FileSystem/Directory.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Directory.obj .././OS/FileSystem/Directory.cc

$(OPTOBJDIR)/FileSearch.obj: .././OS/FileSystem/FileSearch.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileSearch.obj .././OS/FileSystem/FileSearch.cc

$(DEBUGOBJDIR)/FileSearch.obj: .././OS/FileSystem/FileSearch.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileSearch.obj .././OS/FileSystem/FileSearch.cc

$(OPTOBJDIR)/UserInfo.obj: .././OS/FileSystem/UserInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/UserInfo.obj .././OS/FileSystem/UserInfo.cc

$(DEBUGOBJDIR)/UserInfo.obj: .././OS/FileSystem/UserInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/UserInfo.obj .././OS/FileSystem/UserInfo.cc

$(OPTOBJDIR)/FileOwner.obj: .././OS/FileSystem/FileOwner.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileOwner.obj .././OS/FileSystem/FileOwner.cc

$(DEBUGOBJDIR)/FileOwner.obj: .././OS/FileSystem/FileOwner.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileOwner.obj .././OS/FileSystem/FileOwner.cc

$(OPTOBJDIR)/FileStream.obj: .././OS/FileSystem/FileStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileStream.obj .././OS/FileSystem/FileStream.cc

$(DEBUGOBJDIR)/FileStream.obj: .././OS/FileSystem/FileStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileStream.obj .././OS/FileSystem/FileStream.cc

$(OPTOBJDIR)/SerialIO.obj: .././OS/Misc/SerialIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SerialIO.obj .././OS/Misc/SerialIO.cc

$(DEBUGOBJDIR)/SerialIO.obj: .././OS/Misc/SerialIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SerialIO.obj .././OS/Misc/SerialIO.cc

$(OPTOBJDIR)/SysLog.obj: .././OS/Misc/SysLog.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SysLog.obj .././OS/Misc/SysLog.cc

$(DEBUGOBJDIR)/SysLog.obj: .././OS/Misc/SysLog.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SysLog.obj .././OS/Misc/SysLog.cc

$(OPTOBJDIR)/OSProcess.obj: .././OS/Exec/OSProcess.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/OSProcess.obj .././OS/Exec/OSProcess.cc

$(DEBUGOBJDIR)/OSProcess.obj: .././OS/Exec/OSProcess.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/OSProcess.obj .././OS/Exec/OSProcess.cc

$(OPTOBJDIR)/ChildOSProcess.obj: .././OS/Exec/ChildOSProcess.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ChildOSProcess.obj .././OS/Exec/ChildOSProcess.cc

$(DEBUGOBJDIR)/ChildOSProcess.obj: .././OS/Exec/ChildOSProcess.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ChildOSProcess.obj .././OS/Exec/ChildOSProcess.cc

$(OPTOBJDIR)/ChildOSProcessWait.obj: .././OS/Exec/ChildOSProcessWait.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ChildOSProcessWait.obj .././OS/Exec/ChildOSProcessWait.cc

$(DEBUGOBJDIR)/ChildOSProcessWait.obj: .././OS/Exec/ChildOSProcessWait.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ChildOSProcessWait.obj .././OS/Exec/ChildOSProcessWait.cc

$(OPTOBJDIR)/ChildOSProcessStream.obj: .././OS/Exec/ChildOSProcessStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ChildOSProcessStream.obj .././OS/Exec/ChildOSProcessStream.cc

$(DEBUGOBJDIR)/ChildOSProcessStream.obj: .././OS/Exec/ChildOSProcessStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ChildOSProcessStream.obj .././OS/Exec/ChildOSProcessStream.cc

$(OPTOBJDIR)/MailUser.obj: .././OS/Exec/MailUser.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MailUser.obj .././OS/Exec/MailUser.cc

$(DEBUGOBJDIR)/MailUser.obj: .././OS/Exec/MailUser.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MailUser.obj .././OS/Exec/MailUser.cc

$(OPTOBJDIR)/FileUser.obj: .././OS/Exec/FileUser.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileUser.obj .././OS/Exec/FileUser.cc

$(DEBUGOBJDIR)/FileUser.obj: .././OS/Exec/FileUser.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileUser.obj .././OS/Exec/FileUser.cc

$(OPTOBJDIR)/TextFileLine.obj: .././OS/Text/TextFileLine.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TextFileLine.obj .././OS/Text/TextFileLine.cc

$(DEBUGOBJDIR)/TextFileLine.obj: .././OS/Text/TextFileLine.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TextFileLine.obj .././OS/Text/TextFileLine.cc

$(OPTOBJDIR)/TextBuffer.obj: .././OS/Text/TextBuffer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TextBuffer.obj .././OS/Text/TextBuffer.cc

$(DEBUGOBJDIR)/TextBuffer.obj: .././OS/Text/TextBuffer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TextBuffer.obj .././OS/Text/TextBuffer.cc

$(OPTOBJDIR)/TextFile.obj: .././OS/Text/TextFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TextFile.obj .././OS/Text/TextFile.cc

$(DEBUGOBJDIR)/TextFile.obj: .././OS/Text/TextFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TextFile.obj .././OS/Text/TextFile.cc

$(OPTOBJDIR)/TextCursor.obj: .././OS/Text/TextCursor.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TextCursor.obj .././OS/Text/TextCursor.cc

$(DEBUGOBJDIR)/TextCursor.obj: .././OS/Text/TextCursor.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TextCursor.obj .././OS/Text/TextCursor.cc

$(OPTOBJDIR)/TemplateFile.obj: .././OS/Text/TemplateFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TemplateFile.obj .././OS/Text/TemplateFile.cc

$(DEBUGOBJDIR)/TemplateFile.obj: .././OS/Text/TemplateFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TemplateFile.obj .././OS/Text/TemplateFile.cc

$(OPTOBJDIR)/TextFragment.obj: .././OS/Text/TextFragment.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TextFragment.obj .././OS/Text/TextFragment.cc

$(DEBUGOBJDIR)/TextFragment.obj: .././OS/Text/TextFragment.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TextFragment.obj .././OS/Text/TextFragment.cc

$(OPTOBJDIR)/ConfigFile.obj: .././OS/Text/ConfigFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ConfigFile.obj .././OS/Text/ConfigFile.cc

$(DEBUGOBJDIR)/ConfigFile.obj: .././OS/Text/ConfigFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ConfigFile.obj .././OS/Text/ConfigFile.cc

$(OPTOBJDIR)/TemplateComplex.obj: .././OS/Text/TemplateComplex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TemplateComplex.obj .././OS/Text/TemplateComplex.cc

$(DEBUGOBJDIR)/TemplateComplex.obj: .././OS/Text/TemplateComplex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TemplateComplex.obj .././OS/Text/TemplateComplex.cc


