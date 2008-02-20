


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlLogic
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlLogic
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/Literal.obj $(OPTOBJDIR)/Var.obj $(OPTOBJDIR)/Unify.obj $(OPTOBJDIR)/BindSet.obj $(OPTOBJDIR)/Tuple.obj $(OPTOBJDIR)/LList.obj $(OPTOBJDIR)/Condition.obj $(OPTOBJDIR)/MinTerm.obj $(OPTOBJDIR)/Or.obj $(OPTOBJDIR)/And.obj $(OPTOBJDIR)/Not.obj $(OPTOBJDIR)/LiteralIter.obj $(OPTOBJDIR)/State.obj $(OPTOBJDIR)/LiteralIter1.obj $(OPTOBJDIR)/StateOrIter.obj $(OPTOBJDIR)/StateSet.obj $(OPTOBJDIR)/LiteralFilterIter.obj $(OPTOBJDIR)/StateAndIter.obj $(OPTOBJDIR)/NamedLiteral.obj $(OPTOBJDIR)/NamedVar.obj $(OPTOBJDIR)/LiteralIO.obj $(OPTOBJDIR)/MinTermIter.obj $(OPTOBJDIR)/Value.obj $(OPTOBJDIR)/Context.obj $(OPTOBJDIR)/LiteralIndexBase.obj $(OPTOBJDIR)/LiteralIndexElement.obj $(OPTOBJDIR)/LiteralIndexLeaf.obj $(OPTOBJDIR)/LiteralIndexNode.obj $(OPTOBJDIR)/LiteralIndexIter.obj $(OPTOBJDIR)/LiteralIndexFilterBase.obj $(OPTOBJDIR)/LiteralIndexLeafIter.obj $(OPTOBJDIR)/LiteralIndexLeafVarIter.obj $(OPTOBJDIR)/StateIndexed.obj $(OPTOBJDIR)/LiteralIndexFilterRaw.obj $(OPTOBJDIR)/DecisionTreeElement.obj $(OPTOBJDIR)/DecisionTreeLeaf.obj $(OPTOBJDIR)/DecisionTreeBase.obj $(OPTOBJDIR)/DecisionTreeBranch.obj $(OPTOBJDIR)/DecisionTreeBranchBinary.obj $(OPTOBJDIR)/DecisionExamples.obj $(OPTOBJDIR)/Discriminator.obj $(OPTOBJDIR)/SampleLiteral.obj $(OPTOBJDIR)/SampleState.obj
	@echo -- making $(OPTLIBDIR)/RavlLogic.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlLogic.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/Literal.obj $(DEBUGOBJDIR)/Var.obj $(DEBUGOBJDIR)/Unify.obj $(DEBUGOBJDIR)/BindSet.obj $(DEBUGOBJDIR)/Tuple.obj $(DEBUGOBJDIR)/LList.obj $(DEBUGOBJDIR)/Condition.obj $(DEBUGOBJDIR)/MinTerm.obj $(DEBUGOBJDIR)/Or.obj $(DEBUGOBJDIR)/And.obj $(DEBUGOBJDIR)/Not.obj $(DEBUGOBJDIR)/LiteralIter.obj $(DEBUGOBJDIR)/State.obj $(DEBUGOBJDIR)/LiteralIter1.obj $(DEBUGOBJDIR)/StateOrIter.obj $(DEBUGOBJDIR)/StateSet.obj $(DEBUGOBJDIR)/LiteralFilterIter.obj $(DEBUGOBJDIR)/StateAndIter.obj $(DEBUGOBJDIR)/NamedLiteral.obj $(DEBUGOBJDIR)/NamedVar.obj $(DEBUGOBJDIR)/LiteralIO.obj $(DEBUGOBJDIR)/MinTermIter.obj $(DEBUGOBJDIR)/Value.obj $(DEBUGOBJDIR)/Context.obj $(DEBUGOBJDIR)/LiteralIndexBase.obj $(DEBUGOBJDIR)/LiteralIndexElement.obj $(DEBUGOBJDIR)/LiteralIndexLeaf.obj $(DEBUGOBJDIR)/LiteralIndexNode.obj $(DEBUGOBJDIR)/LiteralIndexIter.obj $(DEBUGOBJDIR)/LiteralIndexFilterBase.obj $(DEBUGOBJDIR)/LiteralIndexLeafIter.obj $(DEBUGOBJDIR)/LiteralIndexLeafVarIter.obj $(DEBUGOBJDIR)/StateIndexed.obj $(DEBUGOBJDIR)/LiteralIndexFilterRaw.obj $(DEBUGOBJDIR)/DecisionTreeElement.obj $(DEBUGOBJDIR)/DecisionTreeLeaf.obj $(DEBUGOBJDIR)/DecisionTreeBase.obj $(DEBUGOBJDIR)/DecisionTreeBranch.obj $(DEBUGOBJDIR)/DecisionTreeBranchBinary.obj $(DEBUGOBJDIR)/DecisionExamples.obj $(DEBUGOBJDIR)/Discriminator.obj $(DEBUGOBJDIR)/SampleLiteral.obj $(DEBUGOBJDIR)/SampleState.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlLogic.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlLogic.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlLogic
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/Literal.obj: .././Logic/Base/Literal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Literal.obj .././Logic/Base/Literal.cc

$(DEBUGOBJDIR)/Literal.obj: .././Logic/Base/Literal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Literal.obj .././Logic/Base/Literal.cc

$(OPTOBJDIR)/Var.obj: .././Logic/Base/Var.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Var.obj .././Logic/Base/Var.cc

$(DEBUGOBJDIR)/Var.obj: .././Logic/Base/Var.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Var.obj .././Logic/Base/Var.cc

$(OPTOBJDIR)/Unify.obj: .././Logic/Base/Unify.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Unify.obj .././Logic/Base/Unify.cc

$(DEBUGOBJDIR)/Unify.obj: .././Logic/Base/Unify.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Unify.obj .././Logic/Base/Unify.cc

$(OPTOBJDIR)/BindSet.obj: .././Logic/Base/BindSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BindSet.obj .././Logic/Base/BindSet.cc

$(DEBUGOBJDIR)/BindSet.obj: .././Logic/Base/BindSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BindSet.obj .././Logic/Base/BindSet.cc

$(OPTOBJDIR)/Tuple.obj: .././Logic/Base/Tuple.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Tuple.obj .././Logic/Base/Tuple.cc

$(DEBUGOBJDIR)/Tuple.obj: .././Logic/Base/Tuple.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Tuple.obj .././Logic/Base/Tuple.cc

$(OPTOBJDIR)/LList.obj: .././Logic/Base/LList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LList.obj .././Logic/Base/LList.cc

$(DEBUGOBJDIR)/LList.obj: .././Logic/Base/LList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LList.obj .././Logic/Base/LList.cc

$(OPTOBJDIR)/Condition.obj: .././Logic/Base/Condition.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Condition.obj .././Logic/Base/Condition.cc

$(DEBUGOBJDIR)/Condition.obj: .././Logic/Base/Condition.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Condition.obj .././Logic/Base/Condition.cc

$(OPTOBJDIR)/MinTerm.obj: .././Logic/Base/MinTerm.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MinTerm.obj .././Logic/Base/MinTerm.cc

$(DEBUGOBJDIR)/MinTerm.obj: .././Logic/Base/MinTerm.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MinTerm.obj .././Logic/Base/MinTerm.cc

$(OPTOBJDIR)/Or.obj: .././Logic/Base/Or.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Or.obj .././Logic/Base/Or.cc

$(DEBUGOBJDIR)/Or.obj: .././Logic/Base/Or.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Or.obj .././Logic/Base/Or.cc

$(OPTOBJDIR)/And.obj: .././Logic/Base/And.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/And.obj .././Logic/Base/And.cc

$(DEBUGOBJDIR)/And.obj: .././Logic/Base/And.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/And.obj .././Logic/Base/And.cc

$(OPTOBJDIR)/Not.obj: .././Logic/Base/Not.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Not.obj .././Logic/Base/Not.cc

$(DEBUGOBJDIR)/Not.obj: .././Logic/Base/Not.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Not.obj .././Logic/Base/Not.cc

$(OPTOBJDIR)/LiteralIter.obj: .././Logic/Base/LiteralIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralIter.obj .././Logic/Base/LiteralIter.cc

$(DEBUGOBJDIR)/LiteralIter.obj: .././Logic/Base/LiteralIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralIter.obj .././Logic/Base/LiteralIter.cc

$(OPTOBJDIR)/State.obj: .././Logic/Base/State.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/State.obj .././Logic/Base/State.cc

$(DEBUGOBJDIR)/State.obj: .././Logic/Base/State.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/State.obj .././Logic/Base/State.cc

$(OPTOBJDIR)/LiteralIter1.obj: .././Logic/Base/LiteralIter1.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralIter1.obj .././Logic/Base/LiteralIter1.cc

$(DEBUGOBJDIR)/LiteralIter1.obj: .././Logic/Base/LiteralIter1.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralIter1.obj .././Logic/Base/LiteralIter1.cc

$(OPTOBJDIR)/StateOrIter.obj: .././Logic/Base/StateOrIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StateOrIter.obj .././Logic/Base/StateOrIter.cc

$(DEBUGOBJDIR)/StateOrIter.obj: .././Logic/Base/StateOrIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StateOrIter.obj .././Logic/Base/StateOrIter.cc

$(OPTOBJDIR)/StateSet.obj: .././Logic/Base/StateSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StateSet.obj .././Logic/Base/StateSet.cc

$(DEBUGOBJDIR)/StateSet.obj: .././Logic/Base/StateSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StateSet.obj .././Logic/Base/StateSet.cc

$(OPTOBJDIR)/LiteralFilterIter.obj: .././Logic/Base/LiteralFilterIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralFilterIter.obj .././Logic/Base/LiteralFilterIter.cc

$(DEBUGOBJDIR)/LiteralFilterIter.obj: .././Logic/Base/LiteralFilterIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralFilterIter.obj .././Logic/Base/LiteralFilterIter.cc

$(OPTOBJDIR)/StateAndIter.obj: .././Logic/Base/StateAndIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StateAndIter.obj .././Logic/Base/StateAndIter.cc

$(DEBUGOBJDIR)/StateAndIter.obj: .././Logic/Base/StateAndIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StateAndIter.obj .././Logic/Base/StateAndIter.cc

$(OPTOBJDIR)/NamedLiteral.obj: .././Logic/Base/NamedLiteral.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NamedLiteral.obj .././Logic/Base/NamedLiteral.cc

$(DEBUGOBJDIR)/NamedLiteral.obj: .././Logic/Base/NamedLiteral.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NamedLiteral.obj .././Logic/Base/NamedLiteral.cc

$(OPTOBJDIR)/NamedVar.obj: .././Logic/Base/NamedVar.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NamedVar.obj .././Logic/Base/NamedVar.cc

$(DEBUGOBJDIR)/NamedVar.obj: .././Logic/Base/NamedVar.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NamedVar.obj .././Logic/Base/NamedVar.cc

$(OPTOBJDIR)/LiteralIO.obj: .././Logic/Base/LiteralIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralIO.obj .././Logic/Base/LiteralIO.cc

$(DEBUGOBJDIR)/LiteralIO.obj: .././Logic/Base/LiteralIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralIO.obj .././Logic/Base/LiteralIO.cc

$(OPTOBJDIR)/MinTermIter.obj: .././Logic/Base/MinTermIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MinTermIter.obj .././Logic/Base/MinTermIter.cc

$(DEBUGOBJDIR)/MinTermIter.obj: .././Logic/Base/MinTermIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MinTermIter.obj .././Logic/Base/MinTermIter.cc

$(OPTOBJDIR)/Value.obj: .././Logic/Base/Value.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Value.obj .././Logic/Base/Value.cc

$(DEBUGOBJDIR)/Value.obj: .././Logic/Base/Value.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Value.obj .././Logic/Base/Value.cc

$(OPTOBJDIR)/Context.obj: .././Logic/Base/Context.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Context.obj .././Logic/Base/Context.cc

$(DEBUGOBJDIR)/Context.obj: .././Logic/Base/Context.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Context.obj .././Logic/Base/Context.cc

$(OPTOBJDIR)/LiteralIndexBase.obj: .././Logic/Index/LiteralIndexBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralIndexBase.obj .././Logic/Index/LiteralIndexBase.cc

$(DEBUGOBJDIR)/LiteralIndexBase.obj: .././Logic/Index/LiteralIndexBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralIndexBase.obj .././Logic/Index/LiteralIndexBase.cc

$(OPTOBJDIR)/LiteralIndexElement.obj: .././Logic/Index/LiteralIndexElement.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralIndexElement.obj .././Logic/Index/LiteralIndexElement.cc

$(DEBUGOBJDIR)/LiteralIndexElement.obj: .././Logic/Index/LiteralIndexElement.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralIndexElement.obj .././Logic/Index/LiteralIndexElement.cc

$(OPTOBJDIR)/LiteralIndexLeaf.obj: .././Logic/Index/LiteralIndexLeaf.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralIndexLeaf.obj .././Logic/Index/LiteralIndexLeaf.cc

$(DEBUGOBJDIR)/LiteralIndexLeaf.obj: .././Logic/Index/LiteralIndexLeaf.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralIndexLeaf.obj .././Logic/Index/LiteralIndexLeaf.cc

$(OPTOBJDIR)/LiteralIndexNode.obj: .././Logic/Index/LiteralIndexNode.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralIndexNode.obj .././Logic/Index/LiteralIndexNode.cc

$(DEBUGOBJDIR)/LiteralIndexNode.obj: .././Logic/Index/LiteralIndexNode.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralIndexNode.obj .././Logic/Index/LiteralIndexNode.cc

$(OPTOBJDIR)/LiteralIndexIter.obj: .././Logic/Index/LiteralIndexIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralIndexIter.obj .././Logic/Index/LiteralIndexIter.cc

$(DEBUGOBJDIR)/LiteralIndexIter.obj: .././Logic/Index/LiteralIndexIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralIndexIter.obj .././Logic/Index/LiteralIndexIter.cc

$(OPTOBJDIR)/LiteralIndexFilterBase.obj: .././Logic/Index/LiteralIndexFilterBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralIndexFilterBase.obj .././Logic/Index/LiteralIndexFilterBase.cc

$(DEBUGOBJDIR)/LiteralIndexFilterBase.obj: .././Logic/Index/LiteralIndexFilterBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralIndexFilterBase.obj .././Logic/Index/LiteralIndexFilterBase.cc

$(OPTOBJDIR)/LiteralIndexLeafIter.obj: .././Logic/Index/LiteralIndexLeafIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralIndexLeafIter.obj .././Logic/Index/LiteralIndexLeafIter.cc

$(DEBUGOBJDIR)/LiteralIndexLeafIter.obj: .././Logic/Index/LiteralIndexLeafIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralIndexLeafIter.obj .././Logic/Index/LiteralIndexLeafIter.cc

$(OPTOBJDIR)/LiteralIndexLeafVarIter.obj: .././Logic/Index/LiteralIndexLeafVarIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralIndexLeafVarIter.obj .././Logic/Index/LiteralIndexLeafVarIter.cc

$(DEBUGOBJDIR)/LiteralIndexLeafVarIter.obj: .././Logic/Index/LiteralIndexLeafVarIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralIndexLeafVarIter.obj .././Logic/Index/LiteralIndexLeafVarIter.cc

$(OPTOBJDIR)/StateIndexed.obj: .././Logic/Index/StateIndexed.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StateIndexed.obj .././Logic/Index/StateIndexed.cc

$(DEBUGOBJDIR)/StateIndexed.obj: .././Logic/Index/StateIndexed.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StateIndexed.obj .././Logic/Index/StateIndexed.cc

$(OPTOBJDIR)/LiteralIndexFilterRaw.obj: .././Logic/Index/LiteralIndexFilterRaw.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LiteralIndexFilterRaw.obj .././Logic/Index/LiteralIndexFilterRaw.cc

$(DEBUGOBJDIR)/LiteralIndexFilterRaw.obj: .././Logic/Index/LiteralIndexFilterRaw.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LiteralIndexFilterRaw.obj .././Logic/Index/LiteralIndexFilterRaw.cc

$(OPTOBJDIR)/DecisionTreeElement.obj: .././Logic/DecisionTree/DecisionTreeElement.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DecisionTreeElement.obj .././Logic/DecisionTree/DecisionTreeElement.cc

$(DEBUGOBJDIR)/DecisionTreeElement.obj: .././Logic/DecisionTree/DecisionTreeElement.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DecisionTreeElement.obj .././Logic/DecisionTree/DecisionTreeElement.cc

$(OPTOBJDIR)/DecisionTreeLeaf.obj: .././Logic/DecisionTree/DecisionTreeLeaf.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DecisionTreeLeaf.obj .././Logic/DecisionTree/DecisionTreeLeaf.cc

$(DEBUGOBJDIR)/DecisionTreeLeaf.obj: .././Logic/DecisionTree/DecisionTreeLeaf.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DecisionTreeLeaf.obj .././Logic/DecisionTree/DecisionTreeLeaf.cc

$(OPTOBJDIR)/DecisionTreeBase.obj: .././Logic/DecisionTree/DecisionTreeBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DecisionTreeBase.obj .././Logic/DecisionTree/DecisionTreeBase.cc

$(DEBUGOBJDIR)/DecisionTreeBase.obj: .././Logic/DecisionTree/DecisionTreeBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DecisionTreeBase.obj .././Logic/DecisionTree/DecisionTreeBase.cc

$(OPTOBJDIR)/DecisionTreeBranch.obj: .././Logic/DecisionTree/DecisionTreeBranch.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DecisionTreeBranch.obj .././Logic/DecisionTree/DecisionTreeBranch.cc

$(DEBUGOBJDIR)/DecisionTreeBranch.obj: .././Logic/DecisionTree/DecisionTreeBranch.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DecisionTreeBranch.obj .././Logic/DecisionTree/DecisionTreeBranch.cc

$(OPTOBJDIR)/DecisionTreeBranchBinary.obj: .././Logic/DecisionTree/DecisionTreeBranchBinary.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DecisionTreeBranchBinary.obj .././Logic/DecisionTree/DecisionTreeBranchBinary.cc

$(DEBUGOBJDIR)/DecisionTreeBranchBinary.obj: .././Logic/DecisionTree/DecisionTreeBranchBinary.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DecisionTreeBranchBinary.obj .././Logic/DecisionTree/DecisionTreeBranchBinary.cc

$(OPTOBJDIR)/DecisionExamples.obj: .././Logic/DecisionTree/DecisionExamples.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DecisionExamples.obj .././Logic/DecisionTree/DecisionExamples.cc

$(DEBUGOBJDIR)/DecisionExamples.obj: .././Logic/DecisionTree/DecisionExamples.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DecisionExamples.obj .././Logic/DecisionTree/DecisionExamples.cc

$(OPTOBJDIR)/Discriminator.obj: .././Logic/DecisionTree/Discriminator.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Discriminator.obj .././Logic/DecisionTree/Discriminator.cc

$(DEBUGOBJDIR)/Discriminator.obj: .././Logic/DecisionTree/Discriminator.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Discriminator.obj .././Logic/DecisionTree/Discriminator.cc

$(OPTOBJDIR)/SampleLiteral.obj: .././Logic/DecisionTree/SampleLiteral.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SampleLiteral.obj .././Logic/DecisionTree/SampleLiteral.cc

$(DEBUGOBJDIR)/SampleLiteral.obj: .././Logic/DecisionTree/SampleLiteral.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SampleLiteral.obj .././Logic/DecisionTree/SampleLiteral.cc

$(OPTOBJDIR)/SampleState.obj: .././Logic/DecisionTree/SampleState.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SampleState.obj .././Logic/DecisionTree/SampleState.cc

$(DEBUGOBJDIR)/SampleState.obj: .././Logic/DecisionTree/SampleState.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SampleState.obj .././Logic/DecisionTree/SampleState.cc


