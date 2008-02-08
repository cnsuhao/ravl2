


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
DEBUGOBJDIR = c:\Build/win32/debug/obj/RavlLogicAgent
DEBUGLIBDIR = c:\Build/win32/debug/lib

OPTOBJDIR = c:\Build/win32/opt/obj/RavlLogicAgent
OPTLIBDIR = c:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/ActiveBlackboard.obj $(OPTOBJDIR)/Agent.obj $(OPTOBJDIR)/AgentPlan.obj
	@echo -- making $(OPTLIBDIR)/RavlLogicAgent.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlLogicAgent.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/ActiveBlackboard.obj $(DEBUGOBJDIR)/Agent.obj $(DEBUGOBJDIR)/AgentPlan.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlLogicAgent.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlLogicAgent.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlLogicAgent
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/ActiveBlackboard.obj: .././Logic/Agent/ActiveBlackboard.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ActiveBlackboard.obj .././Logic/Agent/ActiveBlackboard.cc

$(DEBUGOBJDIR)/ActiveBlackboard.obj: .././Logic/Agent/ActiveBlackboard.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ActiveBlackboard.obj .././Logic/Agent/ActiveBlackboard.cc

$(OPTOBJDIR)/Agent.obj: .././Logic/Agent/Agent.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Agent.obj .././Logic/Agent/Agent.cc

$(DEBUGOBJDIR)/Agent.obj: .././Logic/Agent/Agent.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Agent.obj .././Logic/Agent/Agent.cc

$(OPTOBJDIR)/AgentPlan.obj: .././Logic/Agent/AgentPlan.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AgentPlan.obj .././Logic/Agent/AgentPlan.cc

$(DEBUGOBJDIR)/AgentPlan.obj: .././Logic/Agent/AgentPlan.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AgentPlan.obj .././Logic/Agent/AgentPlan.cc


