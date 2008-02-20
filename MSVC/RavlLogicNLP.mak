


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlLogicNLP
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlLogicNLP
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/NLPCausalLink.obj $(OPTOBJDIR)/NLPStep.obj $(OPTOBJDIR)/NLPAgendaItem.obj $(OPTOBJDIR)/NLPAction.obj $(OPTOBJDIR)/NLPAgenda.obj $(OPTOBJDIR)/NonLinearPlan.obj $(OPTOBJDIR)/NLPlanner.obj
	@echo -- making $(OPTLIBDIR)/RavlLogicNLP.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlLogicNLP.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/NLPCausalLink.obj $(DEBUGOBJDIR)/NLPStep.obj $(DEBUGOBJDIR)/NLPAgendaItem.obj $(DEBUGOBJDIR)/NLPAction.obj $(DEBUGOBJDIR)/NLPAgenda.obj $(DEBUGOBJDIR)/NonLinearPlan.obj $(DEBUGOBJDIR)/NLPlanner.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlLogicNLP.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlLogicNLP.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlLogicNLP
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/NLPCausalLink.obj: .././Logic/NonLinearPlanner/NLPCausalLink.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NLPCausalLink.obj .././Logic/NonLinearPlanner/NLPCausalLink.cc

$(DEBUGOBJDIR)/NLPCausalLink.obj: .././Logic/NonLinearPlanner/NLPCausalLink.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NLPCausalLink.obj .././Logic/NonLinearPlanner/NLPCausalLink.cc

$(OPTOBJDIR)/NLPStep.obj: .././Logic/NonLinearPlanner/NLPStep.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NLPStep.obj .././Logic/NonLinearPlanner/NLPStep.cc

$(DEBUGOBJDIR)/NLPStep.obj: .././Logic/NonLinearPlanner/NLPStep.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NLPStep.obj .././Logic/NonLinearPlanner/NLPStep.cc

$(OPTOBJDIR)/NLPAgendaItem.obj: .././Logic/NonLinearPlanner/NLPAgendaItem.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NLPAgendaItem.obj .././Logic/NonLinearPlanner/NLPAgendaItem.cc

$(DEBUGOBJDIR)/NLPAgendaItem.obj: .././Logic/NonLinearPlanner/NLPAgendaItem.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NLPAgendaItem.obj .././Logic/NonLinearPlanner/NLPAgendaItem.cc

$(OPTOBJDIR)/NLPAction.obj: .././Logic/NonLinearPlanner/NLPAction.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NLPAction.obj .././Logic/NonLinearPlanner/NLPAction.cc

$(DEBUGOBJDIR)/NLPAction.obj: .././Logic/NonLinearPlanner/NLPAction.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NLPAction.obj .././Logic/NonLinearPlanner/NLPAction.cc

$(OPTOBJDIR)/NLPAgenda.obj: .././Logic/NonLinearPlanner/NLPAgenda.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NLPAgenda.obj .././Logic/NonLinearPlanner/NLPAgenda.cc

$(DEBUGOBJDIR)/NLPAgenda.obj: .././Logic/NonLinearPlanner/NLPAgenda.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NLPAgenda.obj .././Logic/NonLinearPlanner/NLPAgenda.cc

$(OPTOBJDIR)/NonLinearPlan.obj: .././Logic/NonLinearPlanner/NonLinearPlan.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NonLinearPlan.obj .././Logic/NonLinearPlanner/NonLinearPlan.cc

$(DEBUGOBJDIR)/NonLinearPlan.obj: .././Logic/NonLinearPlanner/NonLinearPlan.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NonLinearPlan.obj .././Logic/NonLinearPlanner/NonLinearPlan.cc

$(OPTOBJDIR)/NLPlanner.obj: .././Logic/NonLinearPlanner/NLPlanner.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NLPlanner.obj .././Logic/NonLinearPlanner/NLPlanner.cc

$(DEBUGOBJDIR)/NLPlanner.obj: .././Logic/NonLinearPlanner/NLPlanner.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NLPlanner.obj .././Logic/NonLinearPlanner/NLPlanner.cc


