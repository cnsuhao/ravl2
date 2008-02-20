


#--------------------------
# Compiler and flags etc
#--------------------------
CC = cl.exe

LD = lib.exe

INCLUDES =  /I "include\Win32" /I "include" /I "c:/Program Files/Microsoft Visual Studio 8/VC/ATLMFC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/INCLUDE" /I "c:/Program Files/Microsoft Visual Studio 8/VC/PlatformSDK/include" /I "c:/Program Files/Microsoft Visual Studio 8/SDK/v2.0/include" 

DEFINES = /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2=1" /D "_CRT_SECURE_NO_DEPRECATE" /D "_SCL_SECURE_NO_DEPRECATE" /D "_SCL_SECURE=0" /D "_UNICODE" /D "UNICODE"


OPTFLAGS = /nologo /c /O2 /Ob1 /EHsc /MD /TP

DEBUGFLAGS = /nologo /c /Ob1 /EHsc /MD /TP

#-----------------------------------------------------------------------------
# OK lets define some of our output directories and define script to make them
#-----------------------------------------------------------------------------
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlCore
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlCore
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/Assert.obj $(OPTOBJDIR)/Exception.obj $(OPTOBJDIR)/EntryPnt.obj $(OPTOBJDIR)/Index.obj $(OPTOBJDIR)/String.obj $(OPTOBJDIR)/RefCounter.obj $(OPTOBJDIR)/HandleRefCounter.obj $(OPTOBJDIR)/Trigger.obj $(OPTOBJDIR)/Calls.obj $(OPTOBJDIR)/MTLocks.obj $(OPTOBJDIR)/StreamType.obj $(OPTOBJDIR)/Stream.obj $(OPTOBJDIR)/StrStream.obj $(OPTOBJDIR)/BinStream.obj $(OPTOBJDIR)/BitStream.obj $(OPTOBJDIR)/IndexRange1d.obj $(OPTOBJDIR)/IndexRange2d.obj $(OPTOBJDIR)/Index2d.obj $(OPTOBJDIR)/Index3d.obj $(OPTOBJDIR)/IntC.obj $(OPTOBJDIR)/StdConst.obj $(OPTOBJDIR)/RCAbstract.obj $(OPTOBJDIR)/BinString.obj $(OPTOBJDIR)/RCWrap.obj $(OPTOBJDIR)/IndexRange3d.obj $(OPTOBJDIR)/Math.obj $(OPTOBJDIR)/RealC.obj $(OPTOBJDIR)/RealRange1d.obj $(OPTOBJDIR)/RealRange2d.obj $(OPTOBJDIR)/RealRange3d.obj $(OPTOBJDIR)/RCBodyV.obj $(OPTOBJDIR)/URLMapper.obj $(OPTOBJDIR)/GenBinStream.obj $(OPTOBJDIR)/Resource.obj $(OPTOBJDIR)/AMutex.obj $(OPTOBJDIR)/RCLayer.obj $(OPTOBJDIR)/CPUID.obj $(OPTOBJDIR)/RBfAcc2d.obj $(OPTOBJDIR)/SBfAcc2d.obj $(OPTOBJDIR)/RBfAcc.obj $(OPTOBJDIR)/SBfAcc.obj $(OPTOBJDIR)/Stack.obj $(OPTOBJDIR)/DLink.obj $(OPTOBJDIR)/DList.obj $(OPTOBJDIR)/Hash.obj $(OPTOBJDIR)/GraphBase.obj $(OPTOBJDIR)/Graph.obj $(OPTOBJDIR)/GraphBaseLinearIter.obj $(OPTOBJDIR)/GraphBConIt.obj $(OPTOBJDIR)/HEMeshBaseVertex.obj $(OPTOBJDIR)/HEMeshBaseEdge.obj $(OPTOBJDIR)/HEMeshBaseFace.obj $(OPTOBJDIR)/HEMeshBase.obj $(OPTOBJDIR)/HEMeshBaseFaceIter.obj $(OPTOBJDIR)/BGraphBase.obj $(OPTOBJDIR)/BGraphBaseIter.obj $(OPTOBJDIR)/BGraphLinearIter.obj $(OPTOBJDIR)/StdMath.obj $(OPTOBJDIR)/Random.obj $(OPTOBJDIR)/RandomGauss.obj $(OPTOBJDIR)/Angle.obj $(OPTOBJDIR)/ScalMath.obj $(OPTOBJDIR)/RandomMersenneTwister.obj $(OPTOBJDIR)/Erf.obj $(OPTOBJDIR)/LogValue.obj $(OPTOBJDIR)/StringList.obj $(OPTOBJDIR)/Option.obj $(OPTOBJDIR)/TypeName.obj $(OPTOBJDIR)/BufStream.obj $(OPTOBJDIR)/SubStringList.obj $(OPTOBJDIR)/XMLStream.obj $(OPTOBJDIR)/XMLTree.obj $(OPTOBJDIR)/StreamParse.obj $(OPTOBJDIR)/VirtualConstructor.obj $(OPTOBJDIR)/FunctionRegister.obj $(OPTOBJDIR)/IndexNd.obj $(OPTOBJDIR)/VariableLengthCode.obj $(OPTOBJDIR)/IndexRange2dSet.obj $(OPTOBJDIR)/Base64.obj $(OPTOBJDIR)/PointerManager.obj $(OPTOBJDIR)/RealRange2dSet.obj $(OPTOBJDIR)/TimeCode.obj $(OPTOBJDIR)/STL.obj
	@echo -- making $(OPTLIBDIR)/RavlCore.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlCore.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/Assert.obj $(DEBUGOBJDIR)/Exception.obj $(DEBUGOBJDIR)/EntryPnt.obj $(DEBUGOBJDIR)/Index.obj $(DEBUGOBJDIR)/String.obj $(DEBUGOBJDIR)/RefCounter.obj $(DEBUGOBJDIR)/HandleRefCounter.obj $(DEBUGOBJDIR)/Trigger.obj $(DEBUGOBJDIR)/Calls.obj $(DEBUGOBJDIR)/MTLocks.obj $(DEBUGOBJDIR)/StreamType.obj $(DEBUGOBJDIR)/Stream.obj $(DEBUGOBJDIR)/StrStream.obj $(DEBUGOBJDIR)/BinStream.obj $(DEBUGOBJDIR)/BitStream.obj $(DEBUGOBJDIR)/IndexRange1d.obj $(DEBUGOBJDIR)/IndexRange2d.obj $(DEBUGOBJDIR)/Index2d.obj $(DEBUGOBJDIR)/Index3d.obj $(DEBUGOBJDIR)/IntC.obj $(DEBUGOBJDIR)/StdConst.obj $(DEBUGOBJDIR)/RCAbstract.obj $(DEBUGOBJDIR)/BinString.obj $(DEBUGOBJDIR)/RCWrap.obj $(DEBUGOBJDIR)/IndexRange3d.obj $(DEBUGOBJDIR)/Math.obj $(DEBUGOBJDIR)/RealC.obj $(DEBUGOBJDIR)/RealRange1d.obj $(DEBUGOBJDIR)/RealRange2d.obj $(DEBUGOBJDIR)/RealRange3d.obj $(DEBUGOBJDIR)/RCBodyV.obj $(DEBUGOBJDIR)/URLMapper.obj $(DEBUGOBJDIR)/GenBinStream.obj $(DEBUGOBJDIR)/Resource.obj $(DEBUGOBJDIR)/AMutex.obj $(DEBUGOBJDIR)/RCLayer.obj $(DEBUGOBJDIR)/CPUID.obj $(DEBUGOBJDIR)/RBfAcc2d.obj $(DEBUGOBJDIR)/SBfAcc2d.obj $(DEBUGOBJDIR)/RBfAcc.obj $(DEBUGOBJDIR)/SBfAcc.obj $(DEBUGOBJDIR)/Stack.obj $(DEBUGOBJDIR)/DLink.obj $(DEBUGOBJDIR)/DList.obj $(DEBUGOBJDIR)/Hash.obj $(DEBUGOBJDIR)/GraphBase.obj $(DEBUGOBJDIR)/Graph.obj $(DEBUGOBJDIR)/GraphBaseLinearIter.obj $(DEBUGOBJDIR)/GraphBConIt.obj $(DEBUGOBJDIR)/HEMeshBaseVertex.obj $(DEBUGOBJDIR)/HEMeshBaseEdge.obj $(DEBUGOBJDIR)/HEMeshBaseFace.obj $(DEBUGOBJDIR)/HEMeshBase.obj $(DEBUGOBJDIR)/HEMeshBaseFaceIter.obj $(DEBUGOBJDIR)/BGraphBase.obj $(DEBUGOBJDIR)/BGraphBaseIter.obj $(DEBUGOBJDIR)/BGraphLinearIter.obj $(DEBUGOBJDIR)/StdMath.obj $(DEBUGOBJDIR)/Random.obj $(DEBUGOBJDIR)/RandomGauss.obj $(DEBUGOBJDIR)/Angle.obj $(DEBUGOBJDIR)/ScalMath.obj $(DEBUGOBJDIR)/RandomMersenneTwister.obj $(DEBUGOBJDIR)/Erf.obj $(DEBUGOBJDIR)/LogValue.obj $(DEBUGOBJDIR)/StringList.obj $(DEBUGOBJDIR)/Option.obj $(DEBUGOBJDIR)/TypeName.obj $(DEBUGOBJDIR)/BufStream.obj $(DEBUGOBJDIR)/SubStringList.obj $(DEBUGOBJDIR)/XMLStream.obj $(DEBUGOBJDIR)/XMLTree.obj $(DEBUGOBJDIR)/StreamParse.obj $(DEBUGOBJDIR)/VirtualConstructor.obj $(DEBUGOBJDIR)/FunctionRegister.obj $(DEBUGOBJDIR)/IndexNd.obj $(DEBUGOBJDIR)/VariableLengthCode.obj $(DEBUGOBJDIR)/IndexRange2dSet.obj $(DEBUGOBJDIR)/Base64.obj $(DEBUGOBJDIR)/PointerManager.obj $(DEBUGOBJDIR)/RealRange2dSet.obj $(DEBUGOBJDIR)/TimeCode.obj $(DEBUGOBJDIR)/STL.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlCore.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlCore.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlCore
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/Assert.obj: .././Core/Base/Assert.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Assert.obj .././Core/Base/Assert.cc

$(DEBUGOBJDIR)/Assert.obj: .././Core/Base/Assert.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Assert.obj .././Core/Base/Assert.cc

$(OPTOBJDIR)/Exception.obj: .././Core/Base/Exception.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Exception.obj .././Core/Base/Exception.cc

$(DEBUGOBJDIR)/Exception.obj: .././Core/Base/Exception.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Exception.obj .././Core/Base/Exception.cc

$(OPTOBJDIR)/EntryPnt.obj: .././Core/Base/EntryPnt.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EntryPnt.obj .././Core/Base/EntryPnt.cc

$(DEBUGOBJDIR)/EntryPnt.obj: .././Core/Base/EntryPnt.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EntryPnt.obj .././Core/Base/EntryPnt.cc

$(OPTOBJDIR)/Index.obj: .././Core/Base/Index.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Index.obj .././Core/Base/Index.cc

$(DEBUGOBJDIR)/Index.obj: .././Core/Base/Index.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Index.obj .././Core/Base/Index.cc

$(OPTOBJDIR)/String.obj: .././Core/Base/String.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/String.obj .././Core/Base/String.cc

$(DEBUGOBJDIR)/String.obj: .././Core/Base/String.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/String.obj .././Core/Base/String.cc

$(OPTOBJDIR)/RefCounter.obj: .././Core/Base/RefCounter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RefCounter.obj .././Core/Base/RefCounter.cc

$(DEBUGOBJDIR)/RefCounter.obj: .././Core/Base/RefCounter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RefCounter.obj .././Core/Base/RefCounter.cc

$(OPTOBJDIR)/HandleRefCounter.obj: .././Core/Base/HandleRefCounter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HandleRefCounter.obj .././Core/Base/HandleRefCounter.cc

$(DEBUGOBJDIR)/HandleRefCounter.obj: .././Core/Base/HandleRefCounter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HandleRefCounter.obj .././Core/Base/HandleRefCounter.cc

$(OPTOBJDIR)/Trigger.obj: .././Core/Base/Trigger.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Trigger.obj .././Core/Base/Trigger.cc

$(DEBUGOBJDIR)/Trigger.obj: .././Core/Base/Trigger.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Trigger.obj .././Core/Base/Trigger.cc

$(OPTOBJDIR)/Calls.obj: .././Core/Base/Calls.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Calls.obj .././Core/Base/Calls.cc

$(DEBUGOBJDIR)/Calls.obj: .././Core/Base/Calls.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Calls.obj .././Core/Base/Calls.cc

$(OPTOBJDIR)/MTLocks.obj: .././Core/Base/MTLocks.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MTLocks.obj .././Core/Base/MTLocks.cc

$(DEBUGOBJDIR)/MTLocks.obj: .././Core/Base/MTLocks.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MTLocks.obj .././Core/Base/MTLocks.cc

$(OPTOBJDIR)/StreamType.obj: .././Core/Base/StreamType.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StreamType.obj .././Core/Base/StreamType.cc

$(DEBUGOBJDIR)/StreamType.obj: .././Core/Base/StreamType.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StreamType.obj .././Core/Base/StreamType.cc

$(OPTOBJDIR)/Stream.obj: .././Core/Base/Stream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Stream.obj .././Core/Base/Stream.cc

$(DEBUGOBJDIR)/Stream.obj: .././Core/Base/Stream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Stream.obj .././Core/Base/Stream.cc

$(OPTOBJDIR)/StrStream.obj: .././Core/Base/StrStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StrStream.obj .././Core/Base/StrStream.cc

$(DEBUGOBJDIR)/StrStream.obj: .././Core/Base/StrStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StrStream.obj .././Core/Base/StrStream.cc

$(OPTOBJDIR)/BinStream.obj: .././Core/Base/BinStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BinStream.obj .././Core/Base/BinStream.cc

$(DEBUGOBJDIR)/BinStream.obj: .././Core/Base/BinStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BinStream.obj .././Core/Base/BinStream.cc

$(OPTOBJDIR)/BitStream.obj: .././Core/Base/BitStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BitStream.obj .././Core/Base/BitStream.cc

$(DEBUGOBJDIR)/BitStream.obj: .././Core/Base/BitStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BitStream.obj .././Core/Base/BitStream.cc

$(OPTOBJDIR)/IndexRange1d.obj: .././Core/Base/IndexRange1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/IndexRange1d.obj .././Core/Base/IndexRange1d.cc

$(DEBUGOBJDIR)/IndexRange1d.obj: .././Core/Base/IndexRange1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/IndexRange1d.obj .././Core/Base/IndexRange1d.cc

$(OPTOBJDIR)/IndexRange2d.obj: .././Core/Base/IndexRange2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/IndexRange2d.obj .././Core/Base/IndexRange2d.cc

$(DEBUGOBJDIR)/IndexRange2d.obj: .././Core/Base/IndexRange2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/IndexRange2d.obj .././Core/Base/IndexRange2d.cc

$(OPTOBJDIR)/Index2d.obj: .././Core/Base/Index2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Index2d.obj .././Core/Base/Index2d.cc

$(DEBUGOBJDIR)/Index2d.obj: .././Core/Base/Index2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Index2d.obj .././Core/Base/Index2d.cc

$(OPTOBJDIR)/Index3d.obj: .././Core/Base/Index3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Index3d.obj .././Core/Base/Index3d.cc

$(DEBUGOBJDIR)/Index3d.obj: .././Core/Base/Index3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Index3d.obj .././Core/Base/Index3d.cc

$(OPTOBJDIR)/IntC.obj: .././Core/Base/IntC.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/IntC.obj .././Core/Base/IntC.cc

$(DEBUGOBJDIR)/IntC.obj: .././Core/Base/IntC.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/IntC.obj .././Core/Base/IntC.cc

$(OPTOBJDIR)/StdConst.obj: .././Core/Base/StdConst.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StdConst.obj .././Core/Base/StdConst.cc

$(DEBUGOBJDIR)/StdConst.obj: .././Core/Base/StdConst.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StdConst.obj .././Core/Base/StdConst.cc

$(OPTOBJDIR)/RCAbstract.obj: .././Core/Base/RCAbstract.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RCAbstract.obj .././Core/Base/RCAbstract.cc

$(DEBUGOBJDIR)/RCAbstract.obj: .././Core/Base/RCAbstract.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RCAbstract.obj .././Core/Base/RCAbstract.cc

$(OPTOBJDIR)/BinString.obj: .././Core/Base/BinString.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BinString.obj .././Core/Base/BinString.cc

$(DEBUGOBJDIR)/BinString.obj: .././Core/Base/BinString.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BinString.obj .././Core/Base/BinString.cc

$(OPTOBJDIR)/RCWrap.obj: .././Core/Base/RCWrap.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RCWrap.obj .././Core/Base/RCWrap.cc

$(DEBUGOBJDIR)/RCWrap.obj: .././Core/Base/RCWrap.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RCWrap.obj .././Core/Base/RCWrap.cc

$(OPTOBJDIR)/IndexRange3d.obj: .././Core/Base/IndexRange3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/IndexRange3d.obj .././Core/Base/IndexRange3d.cc

$(DEBUGOBJDIR)/IndexRange3d.obj: .././Core/Base/IndexRange3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/IndexRange3d.obj .././Core/Base/IndexRange3d.cc

$(OPTOBJDIR)/Math.obj: .././Core/Base/Math.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Math.obj .././Core/Base/Math.cc

$(DEBUGOBJDIR)/Math.obj: .././Core/Base/Math.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Math.obj .././Core/Base/Math.cc

$(OPTOBJDIR)/RealC.obj: .././Core/Base/RealC.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealC.obj .././Core/Base/RealC.cc

$(DEBUGOBJDIR)/RealC.obj: .././Core/Base/RealC.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealC.obj .././Core/Base/RealC.cc

$(OPTOBJDIR)/RealRange1d.obj: .././Core/Base/RealRange1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealRange1d.obj .././Core/Base/RealRange1d.cc

$(DEBUGOBJDIR)/RealRange1d.obj: .././Core/Base/RealRange1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealRange1d.obj .././Core/Base/RealRange1d.cc

$(OPTOBJDIR)/RealRange2d.obj: .././Core/Base/RealRange2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealRange2d.obj .././Core/Base/RealRange2d.cc

$(DEBUGOBJDIR)/RealRange2d.obj: .././Core/Base/RealRange2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealRange2d.obj .././Core/Base/RealRange2d.cc

$(OPTOBJDIR)/RealRange3d.obj: .././Core/Base/RealRange3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealRange3d.obj .././Core/Base/RealRange3d.cc

$(DEBUGOBJDIR)/RealRange3d.obj: .././Core/Base/RealRange3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealRange3d.obj .././Core/Base/RealRange3d.cc

$(OPTOBJDIR)/RCBodyV.obj: .././Core/Base/RCBodyV.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RCBodyV.obj .././Core/Base/RCBodyV.cc

$(DEBUGOBJDIR)/RCBodyV.obj: .././Core/Base/RCBodyV.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RCBodyV.obj .././Core/Base/RCBodyV.cc

$(OPTOBJDIR)/URLMapper.obj: .././Core/Base/URLMapper.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/URLMapper.obj .././Core/Base/URLMapper.cc

$(DEBUGOBJDIR)/URLMapper.obj: .././Core/Base/URLMapper.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/URLMapper.obj .././Core/Base/URLMapper.cc

$(OPTOBJDIR)/GenBinStream.obj: .././Core/Base/GenBinStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GenBinStream.obj .././Core/Base/GenBinStream.cc

$(DEBUGOBJDIR)/GenBinStream.obj: .././Core/Base/GenBinStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GenBinStream.obj .././Core/Base/GenBinStream.cc

$(OPTOBJDIR)/Resource.obj: .././Core/Base/Resource.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Resource.obj .././Core/Base/Resource.cc

$(DEBUGOBJDIR)/Resource.obj: .././Core/Base/Resource.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Resource.obj .././Core/Base/Resource.cc

$(OPTOBJDIR)/AMutex.obj: .././Core/Base/AMutex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AMutex.obj .././Core/Base/AMutex.cc

$(DEBUGOBJDIR)/AMutex.obj: .././Core/Base/AMutex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AMutex.obj .././Core/Base/AMutex.cc

$(OPTOBJDIR)/RCLayer.obj: .././Core/Base/RCLayer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RCLayer.obj .././Core/Base/RCLayer.cc

$(DEBUGOBJDIR)/RCLayer.obj: .././Core/Base/RCLayer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RCLayer.obj .././Core/Base/RCLayer.cc

$(OPTOBJDIR)/CPUID.obj: .././Core/Base/CPUID.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CPUID.obj .././Core/Base/CPUID.cc

$(DEBUGOBJDIR)/CPUID.obj: .././Core/Base/CPUID.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CPUID.obj .././Core/Base/CPUID.cc

$(OPTOBJDIR)/RBfAcc2d.obj: .././Core/Container/Buffer/RBfAcc2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RBfAcc2d.obj .././Core/Container/Buffer/RBfAcc2d.cc

$(DEBUGOBJDIR)/RBfAcc2d.obj: .././Core/Container/Buffer/RBfAcc2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RBfAcc2d.obj .././Core/Container/Buffer/RBfAcc2d.cc

$(OPTOBJDIR)/SBfAcc2d.obj: .././Core/Container/Buffer/SBfAcc2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SBfAcc2d.obj .././Core/Container/Buffer/SBfAcc2d.cc

$(DEBUGOBJDIR)/SBfAcc2d.obj: .././Core/Container/Buffer/SBfAcc2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SBfAcc2d.obj .././Core/Container/Buffer/SBfAcc2d.cc

$(OPTOBJDIR)/RBfAcc.obj: .././Core/Container/Buffer/RBfAcc.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RBfAcc.obj .././Core/Container/Buffer/RBfAcc.cc

$(DEBUGOBJDIR)/RBfAcc.obj: .././Core/Container/Buffer/RBfAcc.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RBfAcc.obj .././Core/Container/Buffer/RBfAcc.cc

$(OPTOBJDIR)/SBfAcc.obj: .././Core/Container/Buffer/SBfAcc.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SBfAcc.obj .././Core/Container/Buffer/SBfAcc.cc

$(DEBUGOBJDIR)/SBfAcc.obj: .././Core/Container/Buffer/SBfAcc.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SBfAcc.obj .././Core/Container/Buffer/SBfAcc.cc

$(OPTOBJDIR)/Stack.obj: .././Core/Container/Misc/Stack.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Stack.obj .././Core/Container/Misc/Stack.cc

$(DEBUGOBJDIR)/Stack.obj: .././Core/Container/Misc/Stack.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Stack.obj .././Core/Container/Misc/Stack.cc

$(OPTOBJDIR)/DLink.obj: .././Core/Container/DList/DLink.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DLink.obj .././Core/Container/DList/DLink.cc

$(DEBUGOBJDIR)/DLink.obj: .././Core/Container/DList/DLink.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DLink.obj .././Core/Container/DList/DLink.cc

$(OPTOBJDIR)/DList.obj: .././Core/Container/DList/DList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DList.obj .././Core/Container/DList/DList.cc

$(DEBUGOBJDIR)/DList.obj: .././Core/Container/DList/DList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DList.obj .././Core/Container/DList/DList.cc

$(OPTOBJDIR)/Hash.obj: .././Core/Container/Hash/Hash.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Hash.obj .././Core/Container/Hash/Hash.cc

$(DEBUGOBJDIR)/Hash.obj: .././Core/Container/Hash/Hash.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Hash.obj .././Core/Container/Hash/Hash.cc

$(OPTOBJDIR)/GraphBase.obj: .././Core/Container/Graph/GraphBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GraphBase.obj .././Core/Container/Graph/GraphBase.cc

$(DEBUGOBJDIR)/GraphBase.obj: .././Core/Container/Graph/GraphBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GraphBase.obj .././Core/Container/Graph/GraphBase.cc

$(OPTOBJDIR)/Graph.obj: .././Core/Container/Graph/Graph.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Graph.obj .././Core/Container/Graph/Graph.cc

$(DEBUGOBJDIR)/Graph.obj: .././Core/Container/Graph/Graph.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Graph.obj .././Core/Container/Graph/Graph.cc

$(OPTOBJDIR)/GraphBaseLinearIter.obj: .././Core/Container/Graph/GraphBaseLinearIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GraphBaseLinearIter.obj .././Core/Container/Graph/GraphBaseLinearIter.cc

$(DEBUGOBJDIR)/GraphBaseLinearIter.obj: .././Core/Container/Graph/GraphBaseLinearIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GraphBaseLinearIter.obj .././Core/Container/Graph/GraphBaseLinearIter.cc

$(OPTOBJDIR)/GraphBConIt.obj: .././Core/Container/Graph/GraphBConIt.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GraphBConIt.obj .././Core/Container/Graph/GraphBConIt.cc

$(DEBUGOBJDIR)/GraphBConIt.obj: .././Core/Container/Graph/GraphBConIt.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GraphBConIt.obj .././Core/Container/Graph/GraphBConIt.cc

$(OPTOBJDIR)/HEMeshBaseVertex.obj: .././Core/Container/Graph/HEMeshBaseVertex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HEMeshBaseVertex.obj .././Core/Container/Graph/HEMeshBaseVertex.cc

$(DEBUGOBJDIR)/HEMeshBaseVertex.obj: .././Core/Container/Graph/HEMeshBaseVertex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HEMeshBaseVertex.obj .././Core/Container/Graph/HEMeshBaseVertex.cc

$(OPTOBJDIR)/HEMeshBaseEdge.obj: .././Core/Container/Graph/HEMeshBaseEdge.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HEMeshBaseEdge.obj .././Core/Container/Graph/HEMeshBaseEdge.cc

$(DEBUGOBJDIR)/HEMeshBaseEdge.obj: .././Core/Container/Graph/HEMeshBaseEdge.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HEMeshBaseEdge.obj .././Core/Container/Graph/HEMeshBaseEdge.cc

$(OPTOBJDIR)/HEMeshBaseFace.obj: .././Core/Container/Graph/HEMeshBaseFace.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HEMeshBaseFace.obj .././Core/Container/Graph/HEMeshBaseFace.cc

$(DEBUGOBJDIR)/HEMeshBaseFace.obj: .././Core/Container/Graph/HEMeshBaseFace.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HEMeshBaseFace.obj .././Core/Container/Graph/HEMeshBaseFace.cc

$(OPTOBJDIR)/HEMeshBase.obj: .././Core/Container/Graph/HEMeshBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HEMeshBase.obj .././Core/Container/Graph/HEMeshBase.cc

$(DEBUGOBJDIR)/HEMeshBase.obj: .././Core/Container/Graph/HEMeshBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HEMeshBase.obj .././Core/Container/Graph/HEMeshBase.cc

$(OPTOBJDIR)/HEMeshBaseFaceIter.obj: .././Core/Container/Graph/HEMeshBaseFaceIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HEMeshBaseFaceIter.obj .././Core/Container/Graph/HEMeshBaseFaceIter.cc

$(DEBUGOBJDIR)/HEMeshBaseFaceIter.obj: .././Core/Container/Graph/HEMeshBaseFaceIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HEMeshBaseFaceIter.obj .././Core/Container/Graph/HEMeshBaseFaceIter.cc

$(OPTOBJDIR)/BGraphBase.obj: .././Core/Container/Branch/BGraphBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BGraphBase.obj .././Core/Container/Branch/BGraphBase.cc

$(DEBUGOBJDIR)/BGraphBase.obj: .././Core/Container/Branch/BGraphBase.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BGraphBase.obj .././Core/Container/Branch/BGraphBase.cc

$(OPTOBJDIR)/BGraphBaseIter.obj: .././Core/Container/Branch/BGraphBaseIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BGraphBaseIter.obj .././Core/Container/Branch/BGraphBaseIter.cc

$(DEBUGOBJDIR)/BGraphBaseIter.obj: .././Core/Container/Branch/BGraphBaseIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BGraphBaseIter.obj .././Core/Container/Branch/BGraphBaseIter.cc

$(OPTOBJDIR)/BGraphLinearIter.obj: .././Core/Container/Branch/BGraphLinearIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BGraphLinearIter.obj .././Core/Container/Branch/BGraphLinearIter.cc

$(DEBUGOBJDIR)/BGraphLinearIter.obj: .././Core/Container/Branch/BGraphLinearIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BGraphLinearIter.obj .././Core/Container/Branch/BGraphLinearIter.cc

$(OPTOBJDIR)/StdMath.obj: .././Core/Math/StdMath.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StdMath.obj .././Core/Math/StdMath.cc

$(DEBUGOBJDIR)/StdMath.obj: .././Core/Math/StdMath.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StdMath.obj .././Core/Math/StdMath.cc

$(OPTOBJDIR)/Random.obj: .././Core/Math/Random.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Random.obj .././Core/Math/Random.cc

$(DEBUGOBJDIR)/Random.obj: .././Core/Math/Random.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Random.obj .././Core/Math/Random.cc

$(OPTOBJDIR)/RandomGauss.obj: .././Core/Math/RandomGauss.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RandomGauss.obj .././Core/Math/RandomGauss.cc

$(DEBUGOBJDIR)/RandomGauss.obj: .././Core/Math/RandomGauss.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RandomGauss.obj .././Core/Math/RandomGauss.cc

$(OPTOBJDIR)/Angle.obj: .././Core/Math/Angle.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Angle.obj .././Core/Math/Angle.cc

$(DEBUGOBJDIR)/Angle.obj: .././Core/Math/Angle.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Angle.obj .././Core/Math/Angle.cc

$(OPTOBJDIR)/ScalMath.obj: .././Core/Math/ScalMath.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ScalMath.obj .././Core/Math/ScalMath.cc

$(DEBUGOBJDIR)/ScalMath.obj: .././Core/Math/ScalMath.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ScalMath.obj .././Core/Math/ScalMath.cc

$(OPTOBJDIR)/RandomMersenneTwister.obj: .././Core/Math/RandomMersenneTwister.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RandomMersenneTwister.obj .././Core/Math/RandomMersenneTwister.cc

$(DEBUGOBJDIR)/RandomMersenneTwister.obj: .././Core/Math/RandomMersenneTwister.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RandomMersenneTwister.obj .././Core/Math/RandomMersenneTwister.cc

$(OPTOBJDIR)/Erf.obj: .././Core/Math/Erf.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Erf.obj .././Core/Math/Erf.cc

$(DEBUGOBJDIR)/Erf.obj: .././Core/Math/Erf.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Erf.obj .././Core/Math/Erf.cc

$(OPTOBJDIR)/LogValue.obj: .././Core/Math/LogValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LogValue.obj .././Core/Math/LogValue.cc

$(DEBUGOBJDIR)/LogValue.obj: .././Core/Math/LogValue.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LogValue.obj .././Core/Math/LogValue.cc

$(OPTOBJDIR)/StringList.obj: .././Core/System/StringList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StringList.obj .././Core/System/StringList.cc

$(DEBUGOBJDIR)/StringList.obj: .././Core/System/StringList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StringList.obj .././Core/System/StringList.cc

$(OPTOBJDIR)/Option.obj: .././Core/System/Option.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Option.obj .././Core/System/Option.cc

$(DEBUGOBJDIR)/Option.obj: .././Core/System/Option.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Option.obj .././Core/System/Option.cc

$(OPTOBJDIR)/TypeName.obj: .././Core/System/TypeName.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TypeName.obj .././Core/System/TypeName.cc

$(DEBUGOBJDIR)/TypeName.obj: .././Core/System/TypeName.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TypeName.obj .././Core/System/TypeName.cc

$(OPTOBJDIR)/BufStream.obj: .././Core/System/BufStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BufStream.obj .././Core/System/BufStream.cc

$(DEBUGOBJDIR)/BufStream.obj: .././Core/System/BufStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BufStream.obj .././Core/System/BufStream.cc

$(OPTOBJDIR)/SubStringList.obj: .././Core/System/SubStringList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SubStringList.obj .././Core/System/SubStringList.cc

$(DEBUGOBJDIR)/SubStringList.obj: .././Core/System/SubStringList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SubStringList.obj .././Core/System/SubStringList.cc

$(OPTOBJDIR)/XMLStream.obj: .././Core/System/XMLStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/XMLStream.obj .././Core/System/XMLStream.cc

$(DEBUGOBJDIR)/XMLStream.obj: .././Core/System/XMLStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/XMLStream.obj .././Core/System/XMLStream.cc

$(OPTOBJDIR)/XMLTree.obj: .././Core/System/XMLTree.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/XMLTree.obj .././Core/System/XMLTree.cc

$(DEBUGOBJDIR)/XMLTree.obj: .././Core/System/XMLTree.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/XMLTree.obj .././Core/System/XMLTree.cc

$(OPTOBJDIR)/StreamParse.obj: .././Core/System/StreamParse.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StreamParse.obj .././Core/System/StreamParse.cc

$(DEBUGOBJDIR)/StreamParse.obj: .././Core/System/StreamParse.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StreamParse.obj .././Core/System/StreamParse.cc

$(OPTOBJDIR)/VirtualConstructor.obj: .././Core/System/VirtualConstructor.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/VirtualConstructor.obj .././Core/System/VirtualConstructor.cc

$(DEBUGOBJDIR)/VirtualConstructor.obj: .././Core/System/VirtualConstructor.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/VirtualConstructor.obj .././Core/System/VirtualConstructor.cc

$(OPTOBJDIR)/FunctionRegister.obj: .././Core/System/FunctionRegister.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FunctionRegister.obj .././Core/System/FunctionRegister.cc

$(DEBUGOBJDIR)/FunctionRegister.obj: .././Core/System/FunctionRegister.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FunctionRegister.obj .././Core/System/FunctionRegister.cc

$(OPTOBJDIR)/IndexNd.obj: .././Core/System/IndexNd.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/IndexNd.obj .././Core/System/IndexNd.cc

$(DEBUGOBJDIR)/IndexNd.obj: .././Core/System/IndexNd.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/IndexNd.obj .././Core/System/IndexNd.cc

$(OPTOBJDIR)/VariableLengthCode.obj: .././Core/System/VariableLengthCode.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/VariableLengthCode.obj .././Core/System/VariableLengthCode.cc

$(DEBUGOBJDIR)/VariableLengthCode.obj: .././Core/System/VariableLengthCode.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/VariableLengthCode.obj .././Core/System/VariableLengthCode.cc

$(OPTOBJDIR)/IndexRange2dSet.obj: .././Core/System/IndexRange2dSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/IndexRange2dSet.obj .././Core/System/IndexRange2dSet.cc

$(DEBUGOBJDIR)/IndexRange2dSet.obj: .././Core/System/IndexRange2dSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/IndexRange2dSet.obj .././Core/System/IndexRange2dSet.cc

$(OPTOBJDIR)/Base64.obj: .././Core/System/Base64.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Base64.obj .././Core/System/Base64.cc

$(DEBUGOBJDIR)/Base64.obj: .././Core/System/Base64.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Base64.obj .././Core/System/Base64.cc

$(OPTOBJDIR)/PointerManager.obj: .././Core/System/PointerManager.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PointerManager.obj .././Core/System/PointerManager.cc

$(DEBUGOBJDIR)/PointerManager.obj: .././Core/System/PointerManager.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PointerManager.obj .././Core/System/PointerManager.cc

$(OPTOBJDIR)/RealRange2dSet.obj: .././Core/System/RealRange2dSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealRange2dSet.obj .././Core/System/RealRange2dSet.cc

$(DEBUGOBJDIR)/RealRange2dSet.obj: .././Core/System/RealRange2dSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealRange2dSet.obj .././Core/System/RealRange2dSet.cc

$(OPTOBJDIR)/TimeCode.obj: .././Core/System/TimeCode.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TimeCode.obj .././Core/System/TimeCode.cc

$(DEBUGOBJDIR)/TimeCode.obj: .././Core/System/TimeCode.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TimeCode.obj .././Core/System/TimeCode.cc

$(OPTOBJDIR)/STL.obj: .././Core/System/STL.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/STL.obj .././Core/System/STL.cc

$(DEBUGOBJDIR)/STL.obj: .././Core/System/STL.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/STL.obj .././Core/System/STL.cc


