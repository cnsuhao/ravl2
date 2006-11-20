# Microsoft Developer Studio Project File - Name="RavlCore" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlCore - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlCore.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlCore.mak" CFG="RavlCore - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlCore - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlCore - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlCore"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlCore"
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

# Name "RavlCore - Win32 Release"
# Name "RavlCore - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Core\Base\Assert.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Exception.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\EntryPnt.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Index.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\String.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RefCounter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\HandleRefCounter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Trigger.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Calls.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\MTLocks.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\StreamType.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Stream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\StrStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\BinStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\BitStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\IndexRange1d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\IndexRange2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Index2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Index3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\IntC.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\StdConst.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RCAbstract.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\BinString.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RCWrap.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\IndexRange3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Math.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RealC.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RealRange1d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RealRange2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RealRange3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RCBodyV.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\URLMapper.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\GenBinStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Resource.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\AMutex.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RCLayer.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Misc\Stack.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\DList\DLink.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\DList\DList.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Hash\Hash.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\GraphBase.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\Graph.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\GraphBaseLinearIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\GraphBConIt.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\HEMeshBaseVertex.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\HEMeshBaseEdge.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\HEMeshBaseFace.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\HEMeshBase.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\HEMeshBaseFaceIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BGraphBase.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BGraphBaseIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BGraphLinearIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\StdMath.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\Random.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\RandomGauss.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\Angle.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\ScalMath.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\RandomMersenneTwister.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\Erf.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\StringList.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\Option.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\TypeName.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\BufStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\SubStringList.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\XMLStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\XMLTree.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\StreamParse.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\VirtualConstructor.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\FunctionRegister.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\IndexNd.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\VariableLengthCode.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\IndexRange2dSet.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\Base64.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\PointerManager.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\RealRange2dSet.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\System\TimeCode.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Core\Machine\i386-win32-vc\Atomic.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Atomic.hh

"C:\Build\inc\Win32\Ravl\Atomic.hh" :  "" ""
	copy ..\.\Core\Machine\i386-win32-vc\Atomic.hh C:\Build\inc\Win32\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Atomic.hh

"C:\Build\inc\Win32\Ravl\Atomic.hh" :  "" ""
	copy ..\.\Core\Machine\i386-win32-vc\Atomic.hh C:\Build\inc\Win32\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Types.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Types.hh

"C:\Build\inc\Ravl\Types.hh" :  "" ""
	copy ..\.\Core\Base\Types.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Types.hh

"C:\Build\inc\Ravl\Types.hh" :  "" ""
	copy ..\.\Core\Base\Types.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\config.h

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header config.h

"C:\Build\inc\Ravl\config.h" :  "" ""
	copy ..\.\Core\Base\config.h C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header config.h

"C:\Build\inc\Ravl\config.h" :  "" ""
	copy ..\.\Core\Base\config.h C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Pair.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Pair.hh

"C:\Build\inc\Ravl\Pair.hh" :  "" ""
	copy ..\.\Core\Base\Pair.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Pair.hh

"C:\Build\inc\Ravl\Pair.hh" :  "" ""
	copy ..\.\Core\Base\Pair.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Resource.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Resource.hh

"C:\Build\inc\Ravl\Resource.hh" :  "" ""
	copy ..\.\Core\Base\Resource.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Resource.hh

"C:\Build\inc\Ravl\Resource.hh" :  "" ""
	copy ..\.\Core\Base\Resource.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Assert.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Assert.hh

"C:\Build\inc\Ravl\Assert.hh" :  "" ""
	copy ..\.\Core\Base\Assert.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Assert.hh

"C:\Build\inc\Ravl\Assert.hh" :  "" ""
	copy ..\.\Core\Base\Assert.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Exception.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Exception.hh

"C:\Build\inc\Ravl\Exception.hh" :  "" ""
	copy ..\.\Core\Base\Exception.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Exception.hh

"C:\Build\inc\Ravl\Exception.hh" :  "" ""
	copy ..\.\Core\Base\Exception.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\EntryPnt.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header EntryPnt.hh

"C:\Build\inc\Ravl\EntryPnt.hh" :  "" ""
	copy ..\.\Core\Base\EntryPnt.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header EntryPnt.hh

"C:\Build\inc\Ravl\EntryPnt.hh" :  "" ""
	copy ..\.\Core\Base\EntryPnt.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Index.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Index.hh

"C:\Build\inc\Ravl\Index.hh" :  "" ""
	copy ..\.\Core\Base\Index.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Index.hh

"C:\Build\inc\Ravl\Index.hh" :  "" ""
	copy ..\.\Core\Base\Index.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\String.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header String.hh

"C:\Build\inc\Ravl\String.hh" :  "" ""
	copy ..\.\Core\Base\String.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header String.hh

"C:\Build\inc\Ravl\String.hh" :  "" ""
	copy ..\.\Core\Base\String.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RefCounter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RefCounter.hh

"C:\Build\inc\Ravl\RefCounter.hh" :  "" ""
	copy ..\.\Core\Base\RefCounter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RefCounter.hh

"C:\Build\inc\Ravl\RefCounter.hh" :  "" ""
	copy ..\.\Core\Base\RefCounter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\HandleRefCounter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header HandleRefCounter.hh

"C:\Build\inc\Ravl\HandleRefCounter.hh" :  "" ""
	copy ..\.\Core\Base\HandleRefCounter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header HandleRefCounter.hh

"C:\Build\inc\Ravl\HandleRefCounter.hh" :  "" ""
	copy ..\.\Core\Base\HandleRefCounter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Trigger.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Trigger.hh

"C:\Build\inc\Ravl\Trigger.hh" :  "" ""
	copy ..\.\Core\Base\Trigger.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Trigger.hh

"C:\Build\inc\Ravl\Trigger.hh" :  "" ""
	copy ..\.\Core\Base\Trigger.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Calls.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Calls.hh

"C:\Build\inc\Ravl\Calls.hh" :  "" ""
	copy ..\.\Core\Base\Calls.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Calls.hh

"C:\Build\inc\Ravl\Calls.hh" :  "" ""
	copy ..\.\Core\Base\Calls.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\MTLocks.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header MTLocks.hh

"C:\Build\inc\Ravl\MTLocks.hh" :  "" ""
	copy ..\.\Core\Base\MTLocks.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header MTLocks.hh

"C:\Build\inc\Ravl\MTLocks.hh" :  "" ""
	copy ..\.\Core\Base\MTLocks.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\StreamType.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header StreamType.hh

"C:\Build\inc\Ravl\StreamType.hh" :  "" ""
	copy ..\.\Core\Base\StreamType.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header StreamType.hh

"C:\Build\inc\Ravl\StreamType.hh" :  "" ""
	copy ..\.\Core\Base\StreamType.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Stream.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Stream.hh

"C:\Build\inc\Ravl\Stream.hh" :  "" ""
	copy ..\.\Core\Base\Stream.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Stream.hh

"C:\Build\inc\Ravl\Stream.hh" :  "" ""
	copy ..\.\Core\Base\Stream.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\StrStream.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header StrStream.hh

"C:\Build\inc\Ravl\StrStream.hh" :  "" ""
	copy ..\.\Core\Base\StrStream.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header StrStream.hh

"C:\Build\inc\Ravl\StrStream.hh" :  "" ""
	copy ..\.\Core\Base\StrStream.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\BinStream.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BinStream.hh

"C:\Build\inc\Ravl\BinStream.hh" :  "" ""
	copy ..\.\Core\Base\BinStream.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BinStream.hh

"C:\Build\inc\Ravl\BinStream.hh" :  "" ""
	copy ..\.\Core\Base\BinStream.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\BitStream.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BitStream.hh

"C:\Build\inc\Ravl\BitStream.hh" :  "" ""
	copy ..\.\Core\Base\BitStream.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BitStream.hh

"C:\Build\inc\Ravl\BitStream.hh" :  "" ""
	copy ..\.\Core\Base\BitStream.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\IndexRange1d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header IndexRange1d.hh

"C:\Build\inc\Ravl\IndexRange1d.hh" :  "" ""
	copy ..\.\Core\Base\IndexRange1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header IndexRange1d.hh

"C:\Build\inc\Ravl\IndexRange1d.hh" :  "" ""
	copy ..\.\Core\Base\IndexRange1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Index2d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Index2d.hh

"C:\Build\inc\Ravl\Index2d.hh" :  "" ""
	copy ..\.\Core\Base\Index2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Index2d.hh

"C:\Build\inc\Ravl\Index2d.hh" :  "" ""
	copy ..\.\Core\Base\Index2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\IndexRange2d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header IndexRange2d.hh

"C:\Build\inc\Ravl\IndexRange2d.hh" :  "" ""
	copy ..\.\Core\Base\IndexRange2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header IndexRange2d.hh

"C:\Build\inc\Ravl\IndexRange2d.hh" :  "" ""
	copy ..\.\Core\Base\IndexRange2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Index3d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Index3d.hh

"C:\Build\inc\Ravl\Index3d.hh" :  "" ""
	copy ..\.\Core\Base\Index3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Index3d.hh

"C:\Build\inc\Ravl\Index3d.hh" :  "" ""
	copy ..\.\Core\Base\Index3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RCWrap.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RCWrap.hh

"C:\Build\inc\Ravl\RCWrap.hh" :  "" ""
	copy ..\.\Core\Base\RCWrap.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RCWrap.hh

"C:\Build\inc\Ravl\RCWrap.hh" :  "" ""
	copy ..\.\Core\Base\RCWrap.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Empty.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Empty.hh

"C:\Build\inc\Ravl\Empty.hh" :  "" ""
	copy ..\.\Core\Base\Empty.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Empty.hh

"C:\Build\inc\Ravl\Empty.hh" :  "" ""
	copy ..\.\Core\Base\Empty.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\IntC.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header IntC.hh

"C:\Build\inc\Ravl\IntC.hh" :  "" ""
	copy ..\.\Core\Base\IntC.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header IntC.hh

"C:\Build\inc\Ravl\IntC.hh" :  "" ""
	copy ..\.\Core\Base\IntC.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\TFVector.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header TFVector.hh

"C:\Build\inc\Ravl\TFVector.hh" :  "" ""
	copy ..\.\Core\Base\TFVector.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header TFVector.hh

"C:\Build\inc\Ravl\TFVector.hh" :  "" ""
	copy ..\.\Core\Base\TFVector.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\FIndex.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header FIndex.hh

"C:\Build\inc\Ravl\FIndex.hh" :  "" ""
	copy ..\.\Core\Base\FIndex.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header FIndex.hh

"C:\Build\inc\Ravl\FIndex.hh" :  "" ""
	copy ..\.\Core\Base\FIndex.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\StdConst.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header StdConst.hh

"C:\Build\inc\Ravl\StdConst.hh" :  "" ""
	copy ..\.\Core\Base\StdConst.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header StdConst.hh

"C:\Build\inc\Ravl\StdConst.hh" :  "" ""
	copy ..\.\Core\Base\StdConst.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RCAbstract.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RCAbstract.hh

"C:\Build\inc\Ravl\RCAbstract.hh" :  "" ""
	copy ..\.\Core\Base\RCAbstract.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RCAbstract.hh

"C:\Build\inc\Ravl\RCAbstract.hh" :  "" ""
	copy ..\.\Core\Base\RCAbstract.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Math.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Math.hh

"C:\Build\inc\Ravl\Math.hh" :  "" ""
	copy ..\.\Core\Base\Math.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Math.hh

"C:\Build\inc\Ravl\Math.hh" :  "" ""
	copy ..\.\Core\Base\Math.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\CallMethods.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header CallMethods.hh

"C:\Build\inc\Ravl\CallMethods.hh" :  "" ""
	copy ..\.\Core\Base\CallMethods.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header CallMethods.hh

"C:\Build\inc\Ravl\CallMethods.hh" :  "" ""
	copy ..\.\Core\Base\CallMethods.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\CallMethodRefs.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header CallMethodRefs.hh

"C:\Build\inc\Ravl\CallMethodRefs.hh" :  "" ""
	copy ..\.\Core\Base\CallMethodRefs.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header CallMethodRefs.hh

"C:\Build\inc\Ravl\CallMethodRefs.hh" :  "" ""
	copy ..\.\Core\Base\CallMethodRefs.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\DeepCopy.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header DeepCopy.hh

"C:\Build\inc\Ravl\DeepCopy.hh" :  "" ""
	copy ..\.\Core\Base\DeepCopy.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header DeepCopy.hh

"C:\Build\inc\Ravl\DeepCopy.hh" :  "" ""
	copy ..\.\Core\Base\DeepCopy.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\StdHash.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header StdHash.hh

"C:\Build\inc\Ravl\StdHash.hh" :  "" ""
	copy ..\.\Core\Base\StdHash.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header StdHash.hh

"C:\Build\inc\Ravl\StdHash.hh" :  "" ""
	copy ..\.\Core\Base\StdHash.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Const.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Const.hh

"C:\Build\inc\Ravl\Const.hh" :  "" ""
	copy ..\.\Core\Base\Const.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Const.hh

"C:\Build\inc\Ravl\Const.hh" :  "" ""
	copy ..\.\Core\Base\Const.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\IndexRange3d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header IndexRange3d.hh

"C:\Build\inc\Ravl\IndexRange3d.hh" :  "" ""
	copy ..\.\Core\Base\IndexRange3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header IndexRange3d.hh

"C:\Build\inc\Ravl\IndexRange3d.hh" :  "" ""
	copy ..\.\Core\Base\IndexRange3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Average.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Average.hh

"C:\Build\inc\Ravl\Average.hh" :  "" ""
	copy ..\.\Core\Base\Average.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Average.hh

"C:\Build\inc\Ravl\Average.hh" :  "" ""
	copy ..\.\Core\Base\Average.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RealC.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RealC.hh

"C:\Build\inc\Ravl\RealC.hh" :  "" ""
	copy ..\.\Core\Base\RealC.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RealC.hh

"C:\Build\inc\Ravl\RealC.hh" :  "" ""
	copy ..\.\Core\Base\RealC.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\SmartPtr.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SmartPtr.hh

"C:\Build\inc\Ravl\SmartPtr.hh" :  "" ""
	copy ..\.\Core\Base\SmartPtr.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SmartPtr.hh

"C:\Build\inc\Ravl\SmartPtr.hh" :  "" ""
	copy ..\.\Core\Base\SmartPtr.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\SubIndexRange2dIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SubIndexRange2dIter.hh

"C:\Build\inc\Ravl\SubIndexRange2dIter.hh" :  "" ""
	copy ..\.\Core\Base\SubIndexRange2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SubIndexRange2dIter.hh

"C:\Build\inc\Ravl\SubIndexRange2dIter.hh" :  "" ""
	copy ..\.\Core\Base\SubIndexRange2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\SubIndexRange3dIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SubIndexRange3dIter.hh

"C:\Build\inc\Ravl\SubIndexRange3dIter.hh" :  "" ""
	copy ..\.\Core\Base\SubIndexRange3dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SubIndexRange3dIter.hh

"C:\Build\inc\Ravl\SubIndexRange3dIter.hh" :  "" ""
	copy ..\.\Core\Base\SubIndexRange3dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RealRange1d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RealRange1d.hh

"C:\Build\inc\Ravl\RealRange1d.hh" :  "" ""
	copy ..\.\Core\Base\RealRange1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RealRange1d.hh

"C:\Build\inc\Ravl\RealRange1d.hh" :  "" ""
	copy ..\.\Core\Base\RealRange1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RealRange2d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RealRange2d.hh

"C:\Build\inc\Ravl\RealRange2d.hh" :  "" ""
	copy ..\.\Core\Base\RealRange2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RealRange2d.hh

"C:\Build\inc\Ravl\RealRange2d.hh" :  "" ""
	copy ..\.\Core\Base\RealRange2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RealRange3d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RealRange3d.hh

"C:\Build\inc\Ravl\RealRange3d.hh" :  "" ""
	copy ..\.\Core\Base\RealRange3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RealRange3d.hh

"C:\Build\inc\Ravl\RealRange3d.hh" :  "" ""
	copy ..\.\Core\Base\RealRange3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RCBodyV.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RCBodyV.hh

"C:\Build\inc\Ravl\RCBodyV.hh" :  "" ""
	copy ..\.\Core\Base\RCBodyV.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RCBodyV.hh

"C:\Build\inc\Ravl\RCBodyV.hh" :  "" ""
	copy ..\.\Core\Base\RCBodyV.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RCHandleV.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RCHandleV.hh

"C:\Build\inc\Ravl\RCHandleV.hh" :  "" ""
	copy ..\.\Core\Base\RCHandleV.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RCHandleV.hh

"C:\Build\inc\Ravl\RCHandleV.hh" :  "" ""
	copy ..\.\Core\Base\RCHandleV.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\IndexRange2dIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header IndexRange2dIter.hh

"C:\Build\inc\Ravl\IndexRange2dIter.hh" :  "" ""
	copy ..\.\Core\Base\IndexRange2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header IndexRange2dIter.hh

"C:\Build\inc\Ravl\IndexRange2dIter.hh" :  "" ""
	copy ..\.\Core\Base\IndexRange2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\IndexRange3dIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header IndexRange3dIter.hh

"C:\Build\inc\Ravl\IndexRange3dIter.hh" :  "" ""
	copy ..\.\Core\Base\IndexRange3dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header IndexRange3dIter.hh

"C:\Build\inc\Ravl\IndexRange3dIter.hh" :  "" ""
	copy ..\.\Core\Base\IndexRange3dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\fdstreambuf.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header fdstreambuf.hh

"C:\Build\inc\Ravl\fdstreambuf.hh" :  "" ""
	copy ..\.\Core\Base\fdstreambuf.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header fdstreambuf.hh

"C:\Build\inc\Ravl\fdstreambuf.hh" :  "" ""
	copy ..\.\Core\Base\fdstreambuf.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\fdstream.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header fdstream.hh

"C:\Build\inc\Ravl\fdstream.hh" :  "" ""
	copy ..\.\Core\Base\fdstream.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header fdstream.hh

"C:\Build\inc\Ravl\fdstream.hh" :  "" ""
	copy ..\.\Core\Base\fdstream.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\GenBinStream.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header GenBinStream.hh

"C:\Build\inc\Ravl\GenBinStream.hh" :  "" ""
	copy ..\.\Core\Base\GenBinStream.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header GenBinStream.hh

"C:\Build\inc\Ravl\GenBinStream.hh" :  "" ""
	copy ..\.\Core\Base\GenBinStream.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\Traits.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Traits.hh

"C:\Build\inc\Ravl\Traits.hh" :  "" ""
	copy ..\.\Core\Base\Traits.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Traits.hh

"C:\Build\inc\Ravl\Traits.hh" :  "" ""
	copy ..\.\Core\Base\Traits.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\FPNumber.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header FPNumber.hh

"C:\Build\inc\Ravl\FPNumber.hh" :  "" ""
	copy ..\.\Core\Base\FPNumber.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header FPNumber.hh

"C:\Build\inc\Ravl\FPNumber.hh" :  "" ""
	copy ..\.\Core\Base\FPNumber.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\QInt.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header QInt.hh

"C:\Build\inc\Ravl\QInt.hh" :  "" ""
	copy ..\.\Core\Base\QInt.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header QInt.hh

"C:\Build\inc\Ravl\QInt.hh" :  "" ""
	copy ..\.\Core\Base\QInt.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\CompilerHints.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header CompilerHints.hh

"C:\Build\inc\Ravl\CompilerHints.hh" :  "" ""
	copy ..\.\Core\Base\CompilerHints.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header CompilerHints.hh

"C:\Build\inc\Ravl\CompilerHints.hh" :  "" ""
	copy ..\.\Core\Base\CompilerHints.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\stdio_fdstream.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header stdio_fdstream.hh

"C:\Build\inc\Ravl\stdio_fdstream.hh" :  "" ""
	copy ..\.\Core\Base\stdio_fdstream.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header stdio_fdstream.hh

"C:\Build\inc\Ravl\stdio_fdstream.hh" :  "" ""
	copy ..\.\Core\Base\stdio_fdstream.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\AMutex.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header AMutex.hh

"C:\Build\inc\Ravl\AMutex.hh" :  "" ""
	copy ..\.\Core\Base\AMutex.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header AMutex.hh

"C:\Build\inc\Ravl\AMutex.hh" :  "" ""
	copy ..\.\Core\Base\AMutex.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Base\RCLayer.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RCLayer.hh

"C:\Build\inc\Ravl\RCLayer.hh" :  "" ""
	copy ..\.\Core\Base\RCLayer.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RCLayer.hh

"C:\Build\inc\Ravl\RCLayer.hh" :  "" ""
	copy ..\.\Core\Base\RCLayer.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\Buffer.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Buffer.hh

"C:\Build\inc\Ravl\Buffer.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Buffer.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Buffer.hh

"C:\Build\inc\Ravl\Buffer.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Buffer.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\CompositeBuffer.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header CompositeBuffer.hh

"C:\Build\inc\Ravl\CompositeBuffer.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\CompositeBuffer.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header CompositeBuffer.hh

"C:\Build\inc\Ravl\CompositeBuffer.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\CompositeBuffer.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\RBfAcc.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RBfAcc.hh

"C:\Build\inc\Ravl\RBfAcc.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\RBfAcc.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RBfAcc.hh

"C:\Build\inc\Ravl\RBfAcc.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\RBfAcc.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\SBfAcc.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SBfAcc.hh

"C:\Build\inc\Ravl\SBfAcc.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\SBfAcc.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SBfAcc.hh

"C:\Build\inc\Ravl\SBfAcc.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\SBfAcc.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BufferAccess.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BufferAccess.hh

"C:\Build\inc\Ravl\BufferAccess.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BufferAccess.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BufferAccess.hh

"C:\Build\inc\Ravl\BufferAccess.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BufferAccess.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAccIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAccIter.hh

"C:\Build\inc\Ravl\BfAccIter.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAccIter.hh

"C:\Build\inc\Ravl\BfAccIter.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAccIter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAccIter2.hh

"C:\Build\inc\Ravl\BfAccIter2.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAccIter2.hh

"C:\Build\inc\Ravl\BfAccIter2.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAccIter3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAccIter3.hh

"C:\Build\inc\Ravl\BfAccIter3.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAccIter3.hh

"C:\Build\inc\Ravl\BfAccIter3.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAccIter4.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAccIter4.hh

"C:\Build\inc\Ravl\BfAccIter4.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter4.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAccIter4.hh

"C:\Build\inc\Ravl\BfAccIter4.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter4.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAccIter5.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAccIter5.hh

"C:\Build\inc\Ravl\BfAccIter5.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter5.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAccIter5.hh

"C:\Build\inc\Ravl\BfAccIter5.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter5.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAccIter6.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAccIter6.hh

"C:\Build\inc\Ravl\BfAccIter6.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter6.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAccIter6.hh

"C:\Build\inc\Ravl\BfAccIter6.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter6.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAccIter7.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAccIter7.hh

"C:\Build\inc\Ravl\BfAccIter7.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter7.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAccIter7.hh

"C:\Build\inc\Ravl\BfAccIter7.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAccIter7.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAcc2Iter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAcc2Iter.hh

"C:\Build\inc\Ravl\BfAcc2Iter.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAcc2Iter.hh

"C:\Build\inc\Ravl\BfAcc2Iter.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAcc2Iter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAcc2Iter2.hh

"C:\Build\inc\Ravl\BfAcc2Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAcc2Iter2.hh

"C:\Build\inc\Ravl\BfAcc2Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAcc2Iter3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAcc2Iter3.hh

"C:\Build\inc\Ravl\BfAcc2Iter3.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAcc2Iter3.hh

"C:\Build\inc\Ravl\BfAcc2Iter3.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAcc2Iter4.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAcc2Iter4.hh

"C:\Build\inc\Ravl\BfAcc2Iter4.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter4.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAcc2Iter4.hh

"C:\Build\inc\Ravl\BfAcc2Iter4.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter4.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAcc2Iter5.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAcc2Iter5.hh

"C:\Build\inc\Ravl\BfAcc2Iter5.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter5.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAcc2Iter5.hh

"C:\Build\inc\Ravl\BfAcc2Iter5.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter5.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAcc2Iter6.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAcc2Iter6.hh

"C:\Build\inc\Ravl\BfAcc2Iter6.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter6.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAcc2Iter6.hh

"C:\Build\inc\Ravl\BfAcc2Iter6.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter6.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAcc2Iter7.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAcc2Iter7.hh

"C:\Build\inc\Ravl\BfAcc2Iter7.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter7.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAcc2Iter7.hh

"C:\Build\inc\Ravl\BfAcc2Iter7.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc2Iter7.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\Buffer2d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Buffer2d.hh

"C:\Build\inc\Ravl\Buffer2d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Buffer2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Buffer2d.hh

"C:\Build\inc\Ravl\Buffer2d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Buffer2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\SBfAcc2d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SBfAcc2d.hh

"C:\Build\inc\Ravl\SBfAcc2d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\SBfAcc2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SBfAcc2d.hh

"C:\Build\inc\Ravl\SBfAcc2d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\SBfAcc2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\RBfAcc2d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RBfAcc2d.hh

"C:\Build\inc\Ravl\RBfAcc2d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\RBfAcc2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RBfAcc2d.hh

"C:\Build\inc\Ravl\RBfAcc2d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\RBfAcc2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\Slice1d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Slice1d.hh

"C:\Build\inc\Ravl\Slice1d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Slice1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Slice1d.hh

"C:\Build\inc\Ravl\Slice1d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Slice1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\Slice1dIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Slice1dIter.hh

"C:\Build\inc\Ravl\Slice1dIter.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Slice1dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Slice1dIter.hh

"C:\Build\inc\Ravl\Slice1dIter.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Slice1dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\Slice1dIter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Slice1dIter2.hh

"C:\Build\inc\Ravl\Slice1dIter2.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Slice1dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Slice1dIter2.hh

"C:\Build\inc\Ravl\Slice1dIter2.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Slice1dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\Slice1dIter3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Slice1dIter3.hh

"C:\Build\inc\Ravl\Slice1dIter3.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Slice1dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Slice1dIter3.hh

"C:\Build\inc\Ravl\Slice1dIter3.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Slice1dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\Buffer3d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Buffer3d.hh

"C:\Build\inc\Ravl\Buffer3d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Buffer3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Buffer3d.hh

"C:\Build\inc\Ravl\Buffer3d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\Buffer3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAcc3Iter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAcc3Iter.hh

"C:\Build\inc\Ravl\BfAcc3Iter.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc3Iter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAcc3Iter.hh

"C:\Build\inc\Ravl\BfAcc3Iter.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc3Iter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAcc3Iter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAcc3Iter2.hh

"C:\Build\inc\Ravl\BfAcc3Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc3Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAcc3Iter2.hh

"C:\Build\inc\Ravl\BfAcc3Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc3Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BfAcc3Iter3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BfAcc3Iter3.hh

"C:\Build\inc\Ravl\BfAcc3Iter3.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc3Iter3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BfAcc3Iter3.hh

"C:\Build\inc\Ravl\BfAcc3Iter3.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BfAcc3Iter3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\SBfAcc3d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SBfAcc3d.hh

"C:\Build\inc\Ravl\SBfAcc3d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\SBfAcc3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SBfAcc3d.hh

"C:\Build\inc\Ravl\SBfAcc3d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\SBfAcc3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\RBfAcc3d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RBfAcc3d.hh

"C:\Build\inc\Ravl\RBfAcc3d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\RBfAcc3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RBfAcc3d.hh

"C:\Build\inc\Ravl\RBfAcc3d.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\RBfAcc3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\BufferAccessIterR.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BufferAccessIterR.hh

"C:\Build\inc\Ravl\BufferAccessIterR.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BufferAccessIterR.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BufferAccessIterR.hh

"C:\Build\inc\Ravl\BufferAccessIterR.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\BufferAccessIterR.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Buffer\SingleBuffer.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SingleBuffer.hh

"C:\Build\inc\Ravl\SingleBuffer.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\SingleBuffer.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SingleBuffer.hh

"C:\Build\inc\Ravl\SingleBuffer.hh" :  "" ""
	copy ..\.\Core\Container\Buffer\SingleBuffer.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SDArray1d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SDArray1d.hh

"C:\Build\inc\Ravl\SDArray1d.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SDArray1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SDArray1d.hh

"C:\Build\inc\Ravl\SDArray1d.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SDArray1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray1d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray1d.hh

"C:\Build\inc\Ravl\SArray1d.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray1d.hh

"C:\Build\inc\Ravl\SArray1d.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray1dIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray1dIter.hh

"C:\Build\inc\Ravl\SArray1dIter.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray1dIter.hh

"C:\Build\inc\Ravl\SArray1dIter.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray1dIter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray1dIter2.hh

"C:\Build\inc\Ravl\SArray1dIter2.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray1dIter2.hh

"C:\Build\inc\Ravl\SArray1dIter2.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray1dIter3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray1dIter3.hh

"C:\Build\inc\Ravl\SArray1dIter3.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray1dIter3.hh

"C:\Build\inc\Ravl\SArray1dIter3.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray1dIter4.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray1dIter4.hh

"C:\Build\inc\Ravl\SArray1dIter4.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1dIter4.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray1dIter4.hh

"C:\Build\inc\Ravl\SArray1dIter4.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1dIter4.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray1dIter5.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray1dIter5.hh

"C:\Build\inc\Ravl\SArray1dIter5.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1dIter5.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray1dIter5.hh

"C:\Build\inc\Ravl\SArray1dIter5.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1dIter5.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray2d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray2d.hh

"C:\Build\inc\Ravl\SArray2d.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray2d.hh

"C:\Build\inc\Ravl\SArray2d.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray2dIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray2dIter.hh

"C:\Build\inc\Ravl\SArray2dIter.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray2dIter.hh

"C:\Build\inc\Ravl\SArray2dIter.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray2dIter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray2dIter2.hh

"C:\Build\inc\Ravl\SArray2dIter2.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray2dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray2dIter2.hh

"C:\Build\inc\Ravl\SArray2dIter2.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray2dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray2dIter3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray2dIter3.hh

"C:\Build\inc\Ravl\SArray2dIter3.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray2dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray2dIter3.hh

"C:\Build\inc\Ravl\SArray2dIter3.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray2dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray3d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray3d.hh

"C:\Build\inc\Ravl\SArray3d.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray3d.hh

"C:\Build\inc\Ravl\SArray3d.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray3dIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray3dIter.hh

"C:\Build\inc\Ravl\SArray3dIter.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray3dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray3dIter.hh

"C:\Build\inc\Ravl\SArray3dIter.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray3dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray3dIter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray3dIter2.hh

"C:\Build\inc\Ravl\SArray3dIter2.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray3dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray3dIter2.hh

"C:\Build\inc\Ravl\SArray3dIter2.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray3dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray3dIter3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray3dIter3.hh

"C:\Build\inc\Ravl\SArray3dIter3.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray3dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray3dIter3.hh

"C:\Build\inc\Ravl\SArray3dIter3.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray3dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\SArray\SArray1dIterR.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SArray1dIterR.hh

"C:\Build\inc\Ravl\SArray1dIterR.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1dIterR.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SArray1dIterR.hh

"C:\Build\inc\Ravl\SArray1dIterR.hh" :  "" ""
	copy ..\.\Core\Container\SArray\SArray1dIterR.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array1d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array1d.hh

"C:\Build\inc\Ravl\Array1d.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array1d.hh

"C:\Build\inc\Ravl\Array1d.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array1dIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array1dIter.hh

"C:\Build\inc\Ravl\Array1dIter.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array1dIter.hh

"C:\Build\inc\Ravl\Array1dIter.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array1dIter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array1dIter2.hh

"C:\Build\inc\Ravl\Array1dIter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array1dIter2.hh

"C:\Build\inc\Ravl\Array1dIter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array1dIter3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array1dIter3.hh

"C:\Build\inc\Ravl\Array1dIter3.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array1dIter3.hh

"C:\Build\inc\Ravl\Array1dIter3.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array1dIter4.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array1dIter4.hh

"C:\Build\inc\Ravl\Array1dIter4.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter4.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array1dIter4.hh

"C:\Build\inc\Ravl\Array1dIter4.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter4.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array1dIter5.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array1dIter5.hh

"C:\Build\inc\Ravl\Array1dIter5.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter5.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array1dIter5.hh

"C:\Build\inc\Ravl\Array1dIter5.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter5.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array1dIter6.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array1dIter6.hh

"C:\Build\inc\Ravl\Array1dIter6.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter6.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array1dIter6.hh

"C:\Build\inc\Ravl\Array1dIter6.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter6.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array1dIter7.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array1dIter7.hh

"C:\Build\inc\Ravl\Array1dIter7.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter7.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array1dIter7.hh

"C:\Build\inc\Ravl\Array1dIter7.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIter7.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2d.hh

"C:\Build\inc\Ravl\Array2d.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2d.hh

"C:\Build\inc\Ravl\Array2d.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dIter.hh

"C:\Build\inc\Ravl\Array2dIter.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dIter.hh

"C:\Build\inc\Ravl\Array2dIter.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dIter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dIter2.hh

"C:\Build\inc\Ravl\Array2dIter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dIter2.hh

"C:\Build\inc\Ravl\Array2dIter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dIter3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dIter3.hh

"C:\Build\inc\Ravl\Array2dIter3.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dIter3.hh

"C:\Build\inc\Ravl\Array2dIter3.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dIter4.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dIter4.hh

"C:\Build\inc\Ravl\Array2dIter4.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter4.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dIter4.hh

"C:\Build\inc\Ravl\Array2dIter4.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter4.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dIter5.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dIter5.hh

"C:\Build\inc\Ravl\Array2dIter5.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter5.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dIter5.hh

"C:\Build\inc\Ravl\Array2dIter5.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter5.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dIter6.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dIter6.hh

"C:\Build\inc\Ravl\Array2dIter6.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter6.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dIter6.hh

"C:\Build\inc\Ravl\Array2dIter6.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter6.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dIter7.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dIter7.hh

"C:\Build\inc\Ravl\Array2dIter7.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter7.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dIter7.hh

"C:\Build\inc\Ravl\Array2dIter7.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dIter7.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array3d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array3d.hh

"C:\Build\inc\Ravl\Array3d.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array3d.hh

"C:\Build\inc\Ravl\Array3d.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array3dIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array3dIter.hh

"C:\Build\inc\Ravl\Array3dIter.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array3dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array3dIter.hh

"C:\Build\inc\Ravl\Array3dIter.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array3dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array3dIter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array3dIter2.hh

"C:\Build\inc\Ravl\Array3dIter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array3dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array3dIter2.hh

"C:\Build\inc\Ravl\Array3dIter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array3dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array3dIter3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array3dIter3.hh

"C:\Build\inc\Ravl\Array3dIter3.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array3dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array3dIter3.hh

"C:\Build\inc\Ravl\Array3dIter3.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array3dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dSqr2Iter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dSqr2Iter.hh

"C:\Build\inc\Ravl\Array2dSqr2Iter.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr2Iter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dSqr2Iter.hh

"C:\Build\inc\Ravl\Array2dSqr2Iter.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr2Iter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dSqr2Iter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dSqr2Iter2.hh

"C:\Build\inc\Ravl\Array2dSqr2Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr2Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dSqr2Iter2.hh

"C:\Build\inc\Ravl\Array2dSqr2Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr2Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dSqr3Iter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dSqr3Iter.hh

"C:\Build\inc\Ravl\Array2dSqr3Iter.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr3Iter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dSqr3Iter.hh

"C:\Build\inc\Ravl\Array2dSqr3Iter.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr3Iter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dSqr31Iter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dSqr31Iter2.hh

"C:\Build\inc\Ravl\Array2dSqr31Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr31Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dSqr31Iter2.hh

"C:\Build\inc\Ravl\Array2dSqr31Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr31Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dSqr33Iter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dSqr33Iter2.hh

"C:\Build\inc\Ravl\Array2dSqr33Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr33Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dSqr33Iter2.hh

"C:\Build\inc\Ravl\Array2dSqr33Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr33Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dSqr311Iter3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dSqr311Iter3.hh

"C:\Build\inc\Ravl\Array2dSqr311Iter3.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr311Iter3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dSqr311Iter3.hh

"C:\Build\inc\Ravl\Array2dSqr311Iter3.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr311Iter3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dSqr3111Iter4.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dSqr3111Iter4.hh

"C:\Build\inc\Ravl\Array2dSqr3111Iter4.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr3111Iter4.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dSqr3111Iter4.hh

"C:\Build\inc\Ravl\Array2dSqr3111Iter4.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr3111Iter4.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dSqr3311Iter4.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dSqr3311Iter4.hh

"C:\Build\inc\Ravl\Array2dSqr3311Iter4.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr3311Iter4.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dSqr3311Iter4.hh

"C:\Build\inc\Ravl\Array2dSqr3311Iter4.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr3311Iter4.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array1dIterR.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array1dIterR.hh

"C:\Build\inc\Ravl\Array1dIterR.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIterR.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array1dIterR.hh

"C:\Build\inc\Ravl\Array1dIterR.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array1dIterR.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dSqr51Iter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dSqr51Iter2.hh

"C:\Build\inc\Ravl\Array2dSqr51Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr51Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dSqr51Iter2.hh

"C:\Build\inc\Ravl\Array2dSqr51Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr51Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Array\Array2dSqr71Iter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Array2dSqr71Iter2.hh

"C:\Build\inc\Ravl\Array2dSqr71Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr71Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Array2dSqr71Iter2.hh

"C:\Build\inc\Ravl\Array2dSqr71Iter2.hh" :  "" ""
	copy ..\.\Core\Container\Array\Array2dSqr71Iter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Misc\Stack.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Stack.hh

"C:\Build\inc\Ravl\Stack.hh" :  "" ""
	copy ..\.\Core\Container\Misc\Stack.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Stack.hh

"C:\Build\inc\Ravl\Stack.hh" :  "" ""
	copy ..\.\Core\Container\Misc\Stack.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Misc\StackIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header StackIter.hh

"C:\Build\inc\Ravl\StackIter.hh" :  "" ""
	copy ..\.\Core\Container\Misc\StackIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header StackIter.hh

"C:\Build\inc\Ravl\StackIter.hh" :  "" ""
	copy ..\.\Core\Container\Misc\StackIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Misc\Tuple2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Tuple2.hh

"C:\Build\inc\Ravl\Tuple2.hh" :  "" ""
	copy ..\.\Core\Container\Misc\Tuple2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Tuple2.hh

"C:\Build\inc\Ravl\Tuple2.hh" :  "" ""
	copy ..\.\Core\Container\Misc\Tuple2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Misc\Tuple3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Tuple3.hh

"C:\Build\inc\Ravl\Tuple3.hh" :  "" ""
	copy ..\.\Core\Container\Misc\Tuple3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Tuple3.hh

"C:\Build\inc\Ravl\Tuple3.hh" :  "" ""
	copy ..\.\Core\Container\Misc\Tuple3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Misc\Tuple4.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Tuple4.hh

"C:\Build\inc\Ravl\Tuple4.hh" :  "" ""
	copy ..\.\Core\Container\Misc\Tuple4.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Tuple4.hh

"C:\Build\inc\Ravl\Tuple4.hh" :  "" ""
	copy ..\.\Core\Container\Misc\Tuple4.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Misc\BlkStack.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BlkStack.hh

"C:\Build\inc\Ravl\BlkStack.hh" :  "" ""
	copy ..\.\Core\Container\Misc\BlkStack.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BlkStack.hh

"C:\Build\inc\Ravl\BlkStack.hh" :  "" ""
	copy ..\.\Core\Container\Misc\BlkStack.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Misc\BlkStackIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BlkStackIter.hh

"C:\Build\inc\Ravl\BlkStackIter.hh" :  "" ""
	copy ..\.\Core\Container\Misc\BlkStackIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BlkStackIter.hh

"C:\Build\inc\Ravl\BlkStackIter.hh" :  "" ""
	copy ..\.\Core\Container\Misc\BlkStackIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Misc\BinTable.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BinTable.hh

"C:\Build\inc\Ravl\BinTable.hh" :  "" ""
	copy ..\.\Core\Container\Misc\BinTable.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BinTable.hh

"C:\Build\inc\Ravl\BinTable.hh" :  "" ""
	copy ..\.\Core\Container\Misc\BinTable.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Misc\BinIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BinIter.hh

"C:\Build\inc\Ravl\BinIter.hh" :  "" ""
	copy ..\.\Core\Container\Misc\BinIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BinIter.hh

"C:\Build\inc\Ravl\BinIter.hh" :  "" ""
	copy ..\.\Core\Container\Misc\BinIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Misc\BinList.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BinList.hh

"C:\Build\inc\Ravl\BinList.hh" :  "" ""
	copy ..\.\Core\Container\Misc\BinList.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BinList.hh

"C:\Build\inc\Ravl\BinList.hh" :  "" ""
	copy ..\.\Core\Container\Misc\BinList.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Queue\PriQueue.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header PriQueue.hh

"C:\Build\inc\Ravl\PriQueue.hh" :  "" ""
	copy ..\.\Core\Container\Queue\PriQueue.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header PriQueue.hh

"C:\Build\inc\Ravl\PriQueue.hh" :  "" ""
	copy ..\.\Core\Container\Queue\PriQueue.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Queue\PriQueueL.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header PriQueueL.hh

"C:\Build\inc\Ravl\PriQueueL.hh" :  "" ""
	copy ..\.\Core\Container\Queue\PriQueueL.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header PriQueueL.hh

"C:\Build\inc\Ravl\PriQueueL.hh" :  "" ""
	copy ..\.\Core\Container\Queue\PriQueueL.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Queue\HeapNode.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header HeapNode.hh

"C:\Build\inc\Ravl\HeapNode.hh" :  "" ""
	copy ..\.\Core\Container\Queue\HeapNode.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header HeapNode.hh

"C:\Build\inc\Ravl\HeapNode.hh" :  "" ""
	copy ..\.\Core\Container\Queue\HeapNode.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Queue\BlkQueue.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BlkQueue.hh

"C:\Build\inc\Ravl\BlkQueue.hh" :  "" ""
	copy ..\.\Core\Container\Queue\BlkQueue.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BlkQueue.hh

"C:\Build\inc\Ravl\BlkQueue.hh" :  "" ""
	copy ..\.\Core\Container\Queue\BlkQueue.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Queue\FixedQueue.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header FixedQueue.hh

"C:\Build\inc\Ravl\FixedQueue.hh" :  "" ""
	copy ..\.\Core\Container\Queue\FixedQueue.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header FixedQueue.hh

"C:\Build\inc\Ravl\FixedQueue.hh" :  "" ""
	copy ..\.\Core\Container\Queue\FixedQueue.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Trees\BinaryTree.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BinaryTree.hh

"C:\Build\inc\Ravl\BinaryTree.hh" :  "" ""
	copy ..\.\Core\Container\Trees\BinaryTree.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BinaryTree.hh

"C:\Build\inc\Ravl\BinaryTree.hh" :  "" ""
	copy ..\.\Core\Container\Trees\BinaryTree.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Trees\AVLTree.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header AVLTree.hh

"C:\Build\inc\Ravl\AVLTree.hh" :  "" ""
	copy ..\.\Core\Container\Trees\AVLTree.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header AVLTree.hh

"C:\Build\inc\Ravl\AVLTree.hh" :  "" ""
	copy ..\.\Core\Container\Trees\AVLTree.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Trees\BinaryTreeUpIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BinaryTreeUpIter.hh

"C:\Build\inc\Ravl\BinaryTreeUpIter.hh" :  "" ""
	copy ..\.\Core\Container\Trees\BinaryTreeUpIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BinaryTreeUpIter.hh

"C:\Build\inc\Ravl\BinaryTreeUpIter.hh" :  "" ""
	copy ..\.\Core\Container\Trees\BinaryTreeUpIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Trees\BinaryTreeDownIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BinaryTreeDownIter.hh

"C:\Build\inc\Ravl\BinaryTreeDownIter.hh" :  "" ""
	copy ..\.\Core\Container\Trees\BinaryTreeDownIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BinaryTreeDownIter.hh

"C:\Build\inc\Ravl\BinaryTreeDownIter.hh" :  "" ""
	copy ..\.\Core\Container\Trees\BinaryTreeDownIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Trees\HashTree.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header HashTree.hh

"C:\Build\inc\Ravl\HashTree.hh" :  "" ""
	copy ..\.\Core\Container\Trees\HashTree.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header HashTree.hh

"C:\Build\inc\Ravl\HashTree.hh" :  "" ""
	copy ..\.\Core\Container\Trees\HashTree.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\DList\DLink.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header DLink.hh

"C:\Build\inc\Ravl\DLink.hh" :  "" ""
	copy ..\.\Core\Container\DList\DLink.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header DLink.hh

"C:\Build\inc\Ravl\DLink.hh" :  "" ""
	copy ..\.\Core\Container\DList\DLink.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\DList\DList.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header DList.hh

"C:\Build\inc\Ravl\DList.hh" :  "" ""
	copy ..\.\Core\Container\DList\DList.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header DList.hh

"C:\Build\inc\Ravl\DList.hh" :  "" ""
	copy ..\.\Core\Container\DList\DList.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\DList\DLIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header DLIter.hh

"C:\Build\inc\Ravl\DLIter.hh" :  "" ""
	copy ..\.\Core\Container\DList\DLIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header DLIter.hh

"C:\Build\inc\Ravl\DLIter.hh" :  "" ""
	copy ..\.\Core\Container\DList\DLIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\DList\CDLIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header CDLIter.hh

"C:\Build\inc\Ravl\CDLIter.hh" :  "" ""
	copy ..\.\Core\Container\DList\CDLIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header CDLIter.hh

"C:\Build\inc\Ravl\CDLIter.hh" :  "" ""
	copy ..\.\Core\Container\DList\CDLIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\DList\IntrDList.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header IntrDList.hh

"C:\Build\inc\Ravl\IntrDList.hh" :  "" ""
	copy ..\.\Core\Container\DList\IntrDList.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header IntrDList.hh

"C:\Build\inc\Ravl\IntrDList.hh" :  "" ""
	copy ..\.\Core\Container\DList\IntrDList.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\DList\IntrDLIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header IntrDLIter.hh

"C:\Build\inc\Ravl\IntrDLIter.hh" :  "" ""
	copy ..\.\Core\Container\DList\IntrDLIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header IntrDLIter.hh

"C:\Build\inc\Ravl\IntrDLIter.hh" :  "" ""
	copy ..\.\Core\Container\DList\IntrDLIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Hash\Hash.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Hash.hh

"C:\Build\inc\Ravl\Hash.hh" :  "" ""
	copy ..\.\Core\Container\Hash\Hash.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Hash.hh

"C:\Build\inc\Ravl\Hash.hh" :  "" ""
	copy ..\.\Core\Container\Hash\Hash.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Hash\HashIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header HashIter.hh

"C:\Build\inc\Ravl\HashIter.hh" :  "" ""
	copy ..\.\Core\Container\Hash\HashIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header HashIter.hh

"C:\Build\inc\Ravl\HashIter.hh" :  "" ""
	copy ..\.\Core\Container\Hash\HashIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Hash\BiHash.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BiHash.hh

"C:\Build\inc\Ravl\BiHash.hh" :  "" ""
	copy ..\.\Core\Container\Hash\BiHash.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BiHash.hh

"C:\Build\inc\Ravl\BiHash.hh" :  "" ""
	copy ..\.\Core\Container\Hash\BiHash.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Hash\RCHash.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RCHash.hh

"C:\Build\inc\Ravl\RCHash.hh" :  "" ""
	copy ..\.\Core\Container\Hash\RCHash.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RCHash.hh

"C:\Build\inc\Ravl\RCHash.hh" :  "" ""
	copy ..\.\Core\Container\Hash\RCHash.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Hash\HSet.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header HSet.hh

"C:\Build\inc\Ravl\HSet.hh" :  "" ""
	copy ..\.\Core\Container\Hash\HSet.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header HSet.hh

"C:\Build\inc\Ravl\HSet.hh" :  "" ""
	copy ..\.\Core\Container\Hash\HSet.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Hash\HSetExtra.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header HSetExtra.hh

"C:\Build\inc\Ravl\HSetExtra.hh" :  "" ""
	copy ..\.\Core\Container\Hash\HSetExtra.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header HSetExtra.hh

"C:\Build\inc\Ravl\HSetExtra.hh" :  "" ""
	copy ..\.\Core\Container\Hash\HSetExtra.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\GraphBase.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header GraphBase.hh

"C:\Build\inc\Ravl\GraphBase.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphBase.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header GraphBase.hh

"C:\Build\inc\Ravl\GraphBase.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphBase.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\Graph.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Graph.hh

"C:\Build\inc\Ravl\Graph.hh" :  "" ""
	copy ..\.\Core\Container\Graph\Graph.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Graph.hh

"C:\Build\inc\Ravl\Graph.hh" :  "" ""
	copy ..\.\Core\Container\Graph\Graph.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\GraphNode.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header GraphNode.hh

"C:\Build\inc\Ravl\GraphNode.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphNode.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header GraphNode.hh

"C:\Build\inc\Ravl\GraphNode.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphNode.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\GraphEdge.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header GraphEdge.hh

"C:\Build\inc\Ravl\GraphEdge.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphEdge.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header GraphEdge.hh

"C:\Build\inc\Ravl\GraphEdge.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphEdge.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\GraphAdj.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header GraphAdj.hh

"C:\Build\inc\Ravl\GraphAdj.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphAdj.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header GraphAdj.hh

"C:\Build\inc\Ravl\GraphAdj.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphAdj.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\GraphBaseLinearIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header GraphBaseLinearIter.hh

"C:\Build\inc\Ravl\GraphBaseLinearIter.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphBaseLinearIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header GraphBaseLinearIter.hh

"C:\Build\inc\Ravl\GraphBaseLinearIter.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphBaseLinearIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\GraphLinearIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header GraphLinearIter.hh

"C:\Build\inc\Ravl\GraphLinearIter.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphLinearIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header GraphLinearIter.hh

"C:\Build\inc\Ravl\GraphLinearIter.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphLinearIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\GraphBestRoute.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header GraphBestRoute.hh

"C:\Build\inc\Ravl\GraphBestRoute.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphBestRoute.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header GraphBestRoute.hh

"C:\Build\inc\Ravl\GraphBestRoute.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphBestRoute.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\GraphConnIt.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header GraphConnIt.hh

"C:\Build\inc\Ravl\GraphConnIt.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphConnIt.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header GraphConnIt.hh

"C:\Build\inc\Ravl\GraphConnIt.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphConnIt.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\GraphBConIt.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header GraphBConIt.hh

"C:\Build\inc\Ravl\GraphBConIt.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphBConIt.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header GraphBConIt.hh

"C:\Build\inc\Ravl\GraphBConIt.hh" :  "" ""
	copy ..\.\Core\Container\Graph\GraphBConIt.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\HEMeshBaseVertex.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header HEMeshBaseVertex.hh

"C:\Build\inc\Ravl\HEMeshBaseVertex.hh" :  "" ""
	copy ..\.\Core\Container\Graph\HEMeshBaseVertex.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header HEMeshBaseVertex.hh

"C:\Build\inc\Ravl\HEMeshBaseVertex.hh" :  "" ""
	copy ..\.\Core\Container\Graph\HEMeshBaseVertex.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\HEMeshBaseEdge.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header HEMeshBaseEdge.hh

"C:\Build\inc\Ravl\HEMeshBaseEdge.hh" :  "" ""
	copy ..\.\Core\Container\Graph\HEMeshBaseEdge.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header HEMeshBaseEdge.hh

"C:\Build\inc\Ravl\HEMeshBaseEdge.hh" :  "" ""
	copy ..\.\Core\Container\Graph\HEMeshBaseEdge.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\HEMeshBaseFace.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header HEMeshBaseFace.hh

"C:\Build\inc\Ravl\HEMeshBaseFace.hh" :  "" ""
	copy ..\.\Core\Container\Graph\HEMeshBaseFace.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header HEMeshBaseFace.hh

"C:\Build\inc\Ravl\HEMeshBaseFace.hh" :  "" ""
	copy ..\.\Core\Container\Graph\HEMeshBaseFace.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\HEMeshBase.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header HEMeshBase.hh

"C:\Build\inc\Ravl\HEMeshBase.hh" :  "" ""
	copy ..\.\Core\Container\Graph\HEMeshBase.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header HEMeshBase.hh

"C:\Build\inc\Ravl\HEMeshBase.hh" :  "" ""
	copy ..\.\Core\Container\Graph\HEMeshBase.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\HEMeshBaseFaceIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header HEMeshBaseFaceIter.hh

"C:\Build\inc\Ravl\HEMeshBaseFaceIter.hh" :  "" ""
	copy ..\.\Core\Container\Graph\HEMeshBaseFaceIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header HEMeshBaseFaceIter.hh

"C:\Build\inc\Ravl\HEMeshBaseFaceIter.hh" :  "" ""
	copy ..\.\Core\Container\Graph\HEMeshBaseFaceIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\HEMeshBaseVertexIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header HEMeshBaseVertexIter.hh

"C:\Build\inc\Ravl\HEMeshBaseVertexIter.hh" :  "" ""
	copy ..\.\Core\Container\Graph\HEMeshBaseVertexIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header HEMeshBaseVertexIter.hh

"C:\Build\inc\Ravl\HEMeshBaseVertexIter.hh" :  "" ""
	copy ..\.\Core\Container\Graph\HEMeshBaseVertexIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\THEMeshVertex.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header THEMeshVertex.hh

"C:\Build\inc\Ravl\THEMeshVertex.hh" :  "" ""
	copy ..\.\Core\Container\Graph\THEMeshVertex.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header THEMeshVertex.hh

"C:\Build\inc\Ravl\THEMeshVertex.hh" :  "" ""
	copy ..\.\Core\Container\Graph\THEMeshVertex.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\THEMeshEdge.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header THEMeshEdge.hh

"C:\Build\inc\Ravl\THEMeshEdge.hh" :  "" ""
	copy ..\.\Core\Container\Graph\THEMeshEdge.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header THEMeshEdge.hh

"C:\Build\inc\Ravl\THEMeshEdge.hh" :  "" ""
	copy ..\.\Core\Container\Graph\THEMeshEdge.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\THEMeshFace.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header THEMeshFace.hh

"C:\Build\inc\Ravl\THEMeshFace.hh" :  "" ""
	copy ..\.\Core\Container\Graph\THEMeshFace.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header THEMeshFace.hh

"C:\Build\inc\Ravl\THEMeshFace.hh" :  "" ""
	copy ..\.\Core\Container\Graph\THEMeshFace.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\THEMesh.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header THEMesh.hh

"C:\Build\inc\Ravl\THEMesh.hh" :  "" ""
	copy ..\.\Core\Container\Graph\THEMesh.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header THEMesh.hh

"C:\Build\inc\Ravl\THEMesh.hh" :  "" ""
	copy ..\.\Core\Container\Graph\THEMesh.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\THEMeshFaceIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header THEMeshFaceIter.hh

"C:\Build\inc\Ravl\THEMeshFaceIter.hh" :  "" ""
	copy ..\.\Core\Container\Graph\THEMeshFaceIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header THEMeshFaceIter.hh

"C:\Build\inc\Ravl\THEMeshFaceIter.hh" :  "" ""
	copy ..\.\Core\Container\Graph\THEMeshFaceIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Graph\THEMeshVertexIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header THEMeshVertexIter.hh

"C:\Build\inc\Ravl\THEMeshVertexIter.hh" :  "" ""
	copy ..\.\Core\Container\Graph\THEMeshVertexIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header THEMeshVertexIter.hh

"C:\Build\inc\Ravl\THEMeshVertexIter.hh" :  "" ""
	copy ..\.\Core\Container\Graph\THEMeshVertexIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BLink.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BLink.hh

"C:\Build\inc\Ravl\BLink.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BLink.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BLink.hh

"C:\Build\inc\Ravl\BLink.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BLink.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BList.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BList.hh

"C:\Build\inc\Ravl\BList.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BList.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BList.hh

"C:\Build\inc\Ravl\BList.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BList.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BListIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BListIter.hh

"C:\Build\inc\Ravl\BListIter.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BListIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BListIter.hh

"C:\Build\inc\Ravl\BListIter.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BListIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BHash.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BHash.hh

"C:\Build\inc\Ravl\BHash.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BHash.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BHash.hh

"C:\Build\inc\Ravl\BHash.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BHash.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BHashIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BHashIter.hh

"C:\Build\inc\Ravl\BHashIter.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BHashIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BHashIter.hh

"C:\Build\inc\Ravl\BHashIter.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BHashIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BStack.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BStack.hh

"C:\Build\inc\Ravl\BStack.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BStack.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BStack.hh

"C:\Build\inc\Ravl\BStack.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BStack.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BDAGraph.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BDAGraph.hh

"C:\Build\inc\Ravl\BDAGraph.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BDAGraph.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BDAGraph.hh

"C:\Build\inc\Ravl\BDAGraph.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BDAGraph.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BGraphEdgeIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BGraphEdgeIter.hh

"C:\Build\inc\Ravl\BGraphEdgeIter.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphEdgeIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BGraphEdgeIter.hh

"C:\Build\inc\Ravl\BGraphEdgeIter.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphEdgeIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BGraphBase.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BGraphBase.hh

"C:\Build\inc\Ravl\BGraphBase.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphBase.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BGraphBase.hh

"C:\Build\inc\Ravl\BGraphBase.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphBase.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BGraph.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BGraph.hh

"C:\Build\inc\Ravl\BGraph.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraph.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BGraph.hh

"C:\Build\inc\Ravl\BGraph.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraph.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BGraphLinearIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BGraphLinearIter.hh

"C:\Build\inc\Ravl\BGraphLinearIter.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphLinearIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BGraphLinearIter.hh

"C:\Build\inc\Ravl\BGraphLinearIter.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphLinearIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BGraphBaseIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BGraphBaseIter.hh

"C:\Build\inc\Ravl\BGraphBaseIter.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphBaseIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BGraphBaseIter.hh

"C:\Build\inc\Ravl\BGraphBaseIter.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphBaseIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BGraphNodeIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BGraphNodeIter.hh

"C:\Build\inc\Ravl\BGraphNodeIter.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphNodeIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BGraphNodeIter.hh

"C:\Build\inc\Ravl\BGraphNodeIter.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphNodeIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BGraphEdge.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BGraphEdge.hh

"C:\Build\inc\Ravl\BGraphEdge.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphEdge.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BGraphEdge.hh

"C:\Build\inc\Ravl\BGraphEdge.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphEdge.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Container\Branch\BGraphNode.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BGraphNode.hh

"C:\Build\inc\Ravl\BGraphNode.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphNode.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BGraphNode.hh

"C:\Build\inc\Ravl\BGraphNode.hh" :  "" ""
	copy ..\.\Core\Container\Branch\BGraphNode.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\StdMath.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header StdMath.hh

"C:\Build\inc\Ravl\StdMath.hh" :  "" ""
	copy ..\.\Core\Math\StdMath.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header StdMath.hh

"C:\Build\inc\Ravl\StdMath.hh" :  "" ""
	copy ..\.\Core\Math\StdMath.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\Random.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Random.hh

"C:\Build\inc\Ravl\Random.hh" :  "" ""
	copy ..\.\Core\Math\Random.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Random.hh

"C:\Build\inc\Ravl\Random.hh" :  "" ""
	copy ..\.\Core\Math\Random.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\RandomGauss.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RandomGauss.hh

"C:\Build\inc\Ravl\RandomGauss.hh" :  "" ""
	copy ..\.\Core\Math\RandomGauss.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RandomGauss.hh

"C:\Build\inc\Ravl\RandomGauss.hh" :  "" ""
	copy ..\.\Core\Math\RandomGauss.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\Angle.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Angle.hh

"C:\Build\inc\Ravl\Angle.hh" :  "" ""
	copy ..\.\Core\Math\Angle.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Angle.hh

"C:\Build\inc\Ravl\Angle.hh" :  "" ""
	copy ..\.\Core\Math\Angle.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\ScalMath.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header ScalMath.hh

"C:\Build\inc\Ravl\ScalMath.hh" :  "" ""
	copy ..\.\Core\Math\ScalMath.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header ScalMath.hh

"C:\Build\inc\Ravl\ScalMath.hh" :  "" ""
	copy ..\.\Core\Math\ScalMath.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\TFMatrix.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header TFMatrix.hh

"C:\Build\inc\Ravl\TFMatrix.hh" :  "" ""
	copy ..\.\Core\Math\TFMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header TFMatrix.hh

"C:\Build\inc\Ravl\TFMatrix.hh" :  "" ""
	copy ..\.\Core\Math\TFMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\Math\RandomMersenneTwister.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RandomMersenneTwister.hh

"C:\Build\inc\Ravl\RandomMersenneTwister.hh" :  "" ""
	copy ..\.\Core\Math\RandomMersenneTwister.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RandomMersenneTwister.hh

"C:\Build\inc\Ravl\RandomMersenneTwister.hh" :  "" ""
	copy ..\.\Core\Math\RandomMersenneTwister.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\StringList.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header StringList.hh

"C:\Build\inc\Ravl\StringList.hh" :  "" ""
	copy ..\.\Core\System\StringList.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header StringList.hh

"C:\Build\inc\Ravl\StringList.hh" :  "" ""
	copy ..\.\Core\System\StringList.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\Option.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Option.hh

"C:\Build\inc\Ravl\Option.hh" :  "" ""
	copy ..\.\Core\System\Option.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Option.hh

"C:\Build\inc\Ravl\Option.hh" :  "" ""
	copy ..\.\Core\System\Option.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\TypeName.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header TypeName.hh

"C:\Build\inc\Ravl\TypeName.hh" :  "" ""
	copy ..\.\Core\System\TypeName.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header TypeName.hh

"C:\Build\inc\Ravl\TypeName.hh" :  "" ""
	copy ..\.\Core\System\TypeName.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\BufStream.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header BufStream.hh

"C:\Build\inc\Ravl\BufStream.hh" :  "" ""
	copy ..\.\Core\System\BufStream.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header BufStream.hh

"C:\Build\inc\Ravl\BufStream.hh" :  "" ""
	copy ..\.\Core\System\BufStream.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\SubStringList.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header SubStringList.hh

"C:\Build\inc\Ravl\SubStringList.hh" :  "" ""
	copy ..\.\Core\System\SubStringList.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header SubStringList.hh

"C:\Build\inc\Ravl\SubStringList.hh" :  "" ""
	copy ..\.\Core\System\SubStringList.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\XMLStream.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header XMLStream.hh

"C:\Build\inc\Ravl\XMLStream.hh" :  "" ""
	copy ..\.\Core\System\XMLStream.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header XMLStream.hh

"C:\Build\inc\Ravl\XMLStream.hh" :  "" ""
	copy ..\.\Core\System\XMLStream.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\XMLTree.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header XMLTree.hh

"C:\Build\inc\Ravl\XMLTree.hh" :  "" ""
	copy ..\.\Core\System\XMLTree.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header XMLTree.hh

"C:\Build\inc\Ravl\XMLTree.hh" :  "" ""
	copy ..\.\Core\System\XMLTree.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\Collection.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Collection.hh

"C:\Build\inc\Ravl\Collection.hh" :  "" ""
	copy ..\.\Core\System\Collection.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Collection.hh

"C:\Build\inc\Ravl\Collection.hh" :  "" ""
	copy ..\.\Core\System\Collection.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\CollectionIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header CollectionIter.hh

"C:\Build\inc\Ravl\CollectionIter.hh" :  "" ""
	copy ..\.\Core\System\CollectionIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header CollectionIter.hh

"C:\Build\inc\Ravl\CollectionIter.hh" :  "" ""
	copy ..\.\Core\System\CollectionIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\IO.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header IO.hh

"C:\Build\inc\Ravl\IO.hh" :  "" ""
	copy ..\.\Core\System\IO.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header IO.hh

"C:\Build\inc\Ravl\IO.hh" :  "" ""
	copy ..\.\Core\System\IO.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\DArray1d.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header DArray1d.hh

"C:\Build\inc\Ravl\DArray1d.hh" :  "" ""
	copy ..\.\Core\System\DArray1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header DArray1d.hh

"C:\Build\inc\Ravl\DArray1d.hh" :  "" ""
	copy ..\.\Core\System\DArray1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\DArray1dIter.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header DArray1dIter.hh

"C:\Build\inc\Ravl\DArray1dIter.hh" :  "" ""
	copy ..\.\Core\System\DArray1dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header DArray1dIter.hh

"C:\Build\inc\Ravl\DArray1dIter.hh" :  "" ""
	copy ..\.\Core\System\DArray1dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\DArray1dIter2.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header DArray1dIter2.hh

"C:\Build\inc\Ravl\DArray1dIter2.hh" :  "" ""
	copy ..\.\Core\System\DArray1dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header DArray1dIter2.hh

"C:\Build\inc\Ravl\DArray1dIter2.hh" :  "" ""
	copy ..\.\Core\System\DArray1dIter2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\DArray1dIter3.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header DArray1dIter3.hh

"C:\Build\inc\Ravl\DArray1dIter3.hh" :  "" ""
	copy ..\.\Core\System\DArray1dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header DArray1dIter3.hh

"C:\Build\inc\Ravl\DArray1dIter3.hh" :  "" ""
	copy ..\.\Core\System\DArray1dIter3.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\DArray1dIter4.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header DArray1dIter4.hh

"C:\Build\inc\Ravl\DArray1dIter4.hh" :  "" ""
	copy ..\.\Core\System\DArray1dIter4.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header DArray1dIter4.hh

"C:\Build\inc\Ravl\DArray1dIter4.hh" :  "" ""
	copy ..\.\Core\System\DArray1dIter4.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\DArray1dIter5.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header DArray1dIter5.hh

"C:\Build\inc\Ravl\DArray1dIter5.hh" :  "" ""
	copy ..\.\Core\System\DArray1dIter5.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header DArray1dIter5.hh

"C:\Build\inc\Ravl\DArray1dIter5.hh" :  "" ""
	copy ..\.\Core\System\DArray1dIter5.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\VirtualConstructor.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header VirtualConstructor.hh

"C:\Build\inc\Ravl\VirtualConstructor.hh" :  "" ""
	copy ..\.\Core\System\VirtualConstructor.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header VirtualConstructor.hh

"C:\Build\inc\Ravl\VirtualConstructor.hh" :  "" ""
	copy ..\.\Core\System\VirtualConstructor.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\FunctionRegister.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header FunctionRegister.hh

"C:\Build\inc\Ravl\FunctionRegister.hh" :  "" ""
	copy ..\.\Core\System\FunctionRegister.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header FunctionRegister.hh

"C:\Build\inc\Ravl\FunctionRegister.hh" :  "" ""
	copy ..\.\Core\System\FunctionRegister.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\IndexNd.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header IndexNd.hh

"C:\Build\inc\Ravl\IndexNd.hh" :  "" ""
	copy ..\.\Core\System\IndexNd.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header IndexNd.hh

"C:\Build\inc\Ravl\IndexNd.hh" :  "" ""
	copy ..\.\Core\System\IndexNd.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\Cache.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Cache.hh

"C:\Build\inc\Ravl\Cache.hh" :  "" ""
	copy ..\.\Core\System\Cache.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Cache.hh

"C:\Build\inc\Ravl\Cache.hh" :  "" ""
	copy ..\.\Core\System\Cache.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\DListExtra.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header DListExtra.hh

"C:\Build\inc\Ravl\DListExtra.hh" :  "" ""
	copy ..\.\Core\System\DListExtra.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header DListExtra.hh

"C:\Build\inc\Ravl\DListExtra.hh" :  "" ""
	copy ..\.\Core\System\DListExtra.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\VariableLengthCode.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header VariableLengthCode.hh

"C:\Build\inc\Ravl\VariableLengthCode.hh" :  "" ""
	copy ..\.\Core\System\VariableLengthCode.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header VariableLengthCode.hh

"C:\Build\inc\Ravl\VariableLengthCode.hh" :  "" ""
	copy ..\.\Core\System\VariableLengthCode.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\IndexRange2dSet.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header IndexRange2dSet.hh

"C:\Build\inc\Ravl\IndexRange2dSet.hh" :  "" ""
	copy ..\.\Core\System\IndexRange2dSet.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header IndexRange2dSet.hh

"C:\Build\inc\Ravl\IndexRange2dSet.hh" :  "" ""
	copy ..\.\Core\System\IndexRange2dSet.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\Base64.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header Base64.hh

"C:\Build\inc\Ravl\Base64.hh" :  "" ""
	copy ..\.\Core\System\Base64.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header Base64.hh

"C:\Build\inc\Ravl\Base64.hh" :  "" ""
	copy ..\.\Core\System\Base64.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\PointerManager.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header PointerManager.hh

"C:\Build\inc\Ravl\PointerManager.hh" :  "" ""
	copy ..\.\Core\System\PointerManager.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header PointerManager.hh

"C:\Build\inc\Ravl\PointerManager.hh" :  "" ""
	copy ..\.\Core\System\PointerManager.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\RealRange2dSet.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header RealRange2dSet.hh

"C:\Build\inc\Ravl\RealRange2dSet.hh" :  "" ""
	copy ..\.\Core\System\RealRange2dSet.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header RealRange2dSet.hh

"C:\Build\inc\Ravl\RealRange2dSet.hh" :  "" ""
	copy ..\.\Core\System\RealRange2dSet.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\System\TimeCode.hh

!IF  "$(CFG)" == "RavlCore - Win32 Release"

# Begin Custom Build - Install Header TimeCode.hh

"C:\Build\inc\Ravl\TimeCode.hh" :  "" ""
	copy ..\.\Core\System\TimeCode.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlCore - Win32 Debug"

# Begin Custom Build - Install Header TimeCode.hh

"C:\Build\inc\Ravl\TimeCode.hh" :  "" ""
	copy ..\.\Core\System\TimeCode.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
