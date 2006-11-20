# Microsoft Developer Studio Project File - Name="RavlIO" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlIO - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlIO.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlIO.mak" CFG="RavlIO - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlIO - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlIO - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlIO"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlIO"
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

# Name "RavlIO - Win32 Release"
# Name "RavlIO - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Core\IO\Entity.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Process.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Port.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\SPort.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\SPortAttach.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\ProcInfo.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Converter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\TypeInfo.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Pipes.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatDesc.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatBinStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatGen.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\TypeConverter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatRegistry.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\IndexIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Event.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\EventSet.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Plug.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\StreamOp.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\StreamProcess.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\IOConnect.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatXMLStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\DataConv.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeCtrl.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeType.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeValueTypes.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeCtrlXML.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeSet.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\ByteFileIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\ByteStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\SByteStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeCtrlInternal.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeCtrlUpdateSignal.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\PrintIOInfo.cc
# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\CoreIO.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Core\IO\Entity.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Entity.hh

"C:\Build\inc\Ravl\DP\Entity.hh" :  "" ""
	copy ..\.\Core\IO\Entity.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Entity.hh

"C:\Build\inc\Ravl\DP\Entity.hh" :  "" ""
	copy ..\.\Core\IO\Entity.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Process.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Process.hh

"C:\Build\inc\Ravl\DP\Process.hh" :  "" ""
	copy ..\.\Core\IO\Process.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Process.hh

"C:\Build\inc\Ravl\DP\Process.hh" :  "" ""
	copy ..\.\Core\IO\Process.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Port.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Port.hh

"C:\Build\inc\Ravl\DP\Port.hh" :  "" ""
	copy ..\.\Core\IO\Port.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Port.hh

"C:\Build\inc\Ravl\DP\Port.hh" :  "" ""
	copy ..\.\Core\IO\Port.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\SPort.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header SPort.hh

"C:\Build\inc\Ravl\DP\SPort.hh" :  "" ""
	copy ..\.\Core\IO\SPort.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header SPort.hh

"C:\Build\inc\Ravl\DP\SPort.hh" :  "" ""
	copy ..\.\Core\IO\SPort.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\SPortAttach.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header SPortAttach.hh

"C:\Build\inc\Ravl\DP\SPortAttach.hh" :  "" ""
	copy ..\.\Core\IO\SPortAttach.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header SPortAttach.hh

"C:\Build\inc\Ravl\DP\SPortAttach.hh" :  "" ""
	copy ..\.\Core\IO\SPortAttach.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\StreamOp.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header StreamOp.hh

"C:\Build\inc\Ravl\DP\StreamOp.hh" :  "" ""
	copy ..\.\Core\IO\StreamOp.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header StreamOp.hh

"C:\Build\inc\Ravl\DP\StreamOp.hh" :  "" ""
	copy ..\.\Core\IO\StreamOp.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\IOJoin.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header IOJoin.hh

"C:\Build\inc\Ravl\DP\IOJoin.hh" :  "" ""
	copy ..\.\Core\IO\IOJoin.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header IOJoin.hh

"C:\Build\inc\Ravl\DP\IOJoin.hh" :  "" ""
	copy ..\.\Core\IO\IOJoin.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\ProcOStream.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header ProcOStream.hh

"C:\Build\inc\Ravl\DP\ProcOStream.hh" :  "" ""
	copy ..\.\Core\IO\ProcOStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header ProcOStream.hh

"C:\Build\inc\Ravl\DP\ProcOStream.hh" :  "" ""
	copy ..\.\Core\IO\ProcOStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\ProcIStream.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header ProcIStream.hh

"C:\Build\inc\Ravl\DP\ProcIStream.hh" :  "" ""
	copy ..\.\Core\IO\ProcIStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header ProcIStream.hh

"C:\Build\inc\Ravl\DP\ProcIStream.hh" :  "" ""
	copy ..\.\Core\IO\ProcIStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Func2Proc.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Func2Proc.hh

"C:\Build\inc\Ravl\DP\Func2Proc.hh" :  "" ""
	copy ..\.\Core\IO\Func2Proc.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Func2Proc.hh

"C:\Build\inc\Ravl\DP\Func2Proc.hh" :  "" ""
	copy ..\.\Core\IO\Func2Proc.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileIO.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header FileIO.hh

"C:\Build\inc\Ravl\DP\FileIO.hh" :  "" ""
	copy ..\.\Core\IO\FileIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header FileIO.hh

"C:\Build\inc\Ravl\DP\FileIO.hh" :  "" ""
	copy ..\.\Core\IO\FileIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\BinFileIO.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header BinFileIO.hh

"C:\Build\inc\Ravl\DP\BinFileIO.hh" :  "" ""
	copy ..\.\Core\IO\BinFileIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header BinFileIO.hh

"C:\Build\inc\Ravl\DP\BinFileIO.hh" :  "" ""
	copy ..\.\Core\IO\BinFileIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FuncP2Proc.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header FuncP2Proc.hh

"C:\Build\inc\Ravl\DP\FuncP2Proc.hh" :  "" ""
	copy ..\.\Core\IO\FuncP2Proc.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header FuncP2Proc.hh

"C:\Build\inc\Ravl\DP\FuncP2Proc.hh" :  "" ""
	copy ..\.\Core\IO\FuncP2Proc.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\ProcCompose.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header ProcCompose.hh

"C:\Build\inc\Ravl\DP\ProcCompose.hh" :  "" ""
	copy ..\.\Core\IO\ProcCompose.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header ProcCompose.hh

"C:\Build\inc\Ravl\DP\ProcCompose.hh" :  "" ""
	copy ..\.\Core\IO\ProcCompose.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\ProcInfo.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header ProcInfo.hh

"C:\Build\inc\Ravl\DP\ProcInfo.hh" :  "" ""
	copy ..\.\Core\IO\ProcInfo.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header ProcInfo.hh

"C:\Build\inc\Ravl\DP\ProcInfo.hh" :  "" ""
	copy ..\.\Core\IO\ProcInfo.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Converter.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Converter.hh

"C:\Build\inc\Ravl\DP\Converter.hh" :  "" ""
	copy ..\.\Core\IO\Converter.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Converter.hh

"C:\Build\inc\Ravl\DP\Converter.hh" :  "" ""
	copy ..\.\Core\IO\Converter.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\DataConv.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header DataConv.hh

"C:\Build\inc\Ravl\DP\DataConv.hh" :  "" ""
	copy ..\.\Core\IO\DataConv.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header DataConv.hh

"C:\Build\inc\Ravl\DP\DataConv.hh" :  "" ""
	copy ..\.\Core\IO\DataConv.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\TypeInfo.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header TypeInfo.hh

"C:\Build\inc\Ravl\DP\TypeInfo.hh" :  "" ""
	copy ..\.\Core\IO\TypeInfo.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header TypeInfo.hh

"C:\Build\inc\Ravl\DP\TypeInfo.hh" :  "" ""
	copy ..\.\Core\IO\TypeInfo.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Pipes.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Pipes.hh

"C:\Build\inc\Ravl\DP\Pipes.hh" :  "" ""
	copy ..\.\Core\IO\Pipes.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Pipes.hh

"C:\Build\inc\Ravl\DP\Pipes.hh" :  "" ""
	copy ..\.\Core\IO\Pipes.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormat.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header FileFormat.hh

"C:\Build\inc\Ravl\DP\FileFormat.hh" :  "" ""
	copy ..\.\Core\IO\FileFormat.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header FileFormat.hh

"C:\Build\inc\Ravl\DP\FileFormat.hh" :  "" ""
	copy ..\.\Core\IO\FileFormat.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatDesc.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header FileFormatDesc.hh

"C:\Build\inc\Ravl\DP\FileFormatDesc.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatDesc.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header FileFormatDesc.hh

"C:\Build\inc\Ravl\DP\FileFormatDesc.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatDesc.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatStream.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header FileFormatStream.hh

"C:\Build\inc\Ravl\DP\FileFormatStream.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header FileFormatStream.hh

"C:\Build\inc\Ravl\DP\FileFormatStream.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatBinStream.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header FileFormatBinStream.hh

"C:\Build\inc\Ravl\DP\FileFormatBinStream.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatBinStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header FileFormatBinStream.hh

"C:\Build\inc\Ravl\DP\FileFormatBinStream.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatBinStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatGen.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header FileFormatGen.hh

"C:\Build\inc\Ravl\DP\FileFormatGen.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatGen.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header FileFormatGen.hh

"C:\Build\inc\Ravl\DP\FileFormatGen.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatGen.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatIO.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header FileFormatIO.hh

"C:\Build\inc\Ravl\DP\FileFormatIO.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header FileFormatIO.hh

"C:\Build\inc\Ravl\DP\FileFormatIO.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\TypeConverter.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header TypeConverter.hh

"C:\Build\inc\Ravl\DP\TypeConverter.hh" :  "" ""
	copy ..\.\Core\IO\TypeConverter.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header TypeConverter.hh

"C:\Build\inc\Ravl\DP\TypeConverter.hh" :  "" ""
	copy ..\.\Core\IO\TypeConverter.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatRegistry.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header FileFormatRegistry.hh

"C:\Build\inc\Ravl\DP\FileFormatRegistry.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatRegistry.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header FileFormatRegistry.hh

"C:\Build\inc\Ravl\DP\FileFormatRegistry.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatRegistry.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\CoreIO.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header CoreIO.hh

"C:\Build\inc\Ravl\DP\CoreIO.hh" :  "" ""
	copy ..\.\Core\IO\CoreIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header CoreIO.hh

"C:\Build\inc\Ravl\DP\CoreIO.hh" :  "" ""
	copy ..\.\Core\IO\CoreIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\ComposeSingle.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header ComposeSingle.hh

"C:\Build\inc\Ravl\DP\ComposeSingle.hh" :  "" ""
	copy ..\.\Core\IO\ComposeSingle.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header ComposeSingle.hh

"C:\Build\inc\Ravl\DP\ComposeSingle.hh" :  "" ""
	copy ..\.\Core\IO\ComposeSingle.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Compose.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Compose.hh

"C:\Build\inc\Ravl\DP\Compose.hh" :  "" ""
	copy ..\.\Core\IO\Compose.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Compose.hh

"C:\Build\inc\Ravl\DP\Compose.hh" :  "" ""
	copy ..\.\Core\IO\Compose.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Func2Stream.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Func2Stream.hh

"C:\Build\inc\Ravl\DP\Func2Stream.hh" :  "" ""
	copy ..\.\Core\IO\Func2Stream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Func2Stream.hh

"C:\Build\inc\Ravl\DP\Func2Stream.hh" :  "" ""
	copy ..\.\Core\IO\Func2Stream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\IOConnect.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header IOConnect.hh

"C:\Build\inc\Ravl\DP\IOConnect.hh" :  "" ""
	copy ..\.\Core\IO\IOConnect.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header IOConnect.hh

"C:\Build\inc\Ravl\DP\IOConnect.hh" :  "" ""
	copy ..\.\Core\IO\IOConnect.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\IFailOver.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header IFailOver.hh

"C:\Build\inc\Ravl\DP\IFailOver.hh" :  "" ""
	copy ..\.\Core\IO\IFailOver.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header IFailOver.hh

"C:\Build\inc\Ravl\DP\IFailOver.hh" :  "" ""
	copy ..\.\Core\IO\IFailOver.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\IOTap.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header IOTap.hh

"C:\Build\inc\Ravl\DP\IOTap.hh" :  "" ""
	copy ..\.\Core\IO\IOTap.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header IOTap.hh

"C:\Build\inc\Ravl\DP\IOTap.hh" :  "" ""
	copy ..\.\Core\IO\IOTap.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Multiplex.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Multiplex.hh

"C:\Build\inc\Ravl\DP\Multiplex.hh" :  "" ""
	copy ..\.\Core\IO\Multiplex.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Multiplex.hh

"C:\Build\inc\Ravl\DP\Multiplex.hh" :  "" ""
	copy ..\.\Core\IO\Multiplex.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\SplitO.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header SplitO.hh

"C:\Build\inc\Ravl\DP\SplitO.hh" :  "" ""
	copy ..\.\Core\IO\SplitO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header SplitO.hh

"C:\Build\inc\Ravl\DP\SplitO.hh" :  "" ""
	copy ..\.\Core\IO\SplitO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Event.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Event.hh

"C:\Build\inc\Ravl\DP\Event.hh" :  "" ""
	copy ..\.\Core\IO\Event.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Event.hh

"C:\Build\inc\Ravl\DP\Event.hh" :  "" ""
	copy ..\.\Core\IO\Event.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\EventSet.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header EventSet.hh

"C:\Build\inc\Ravl\DP\EventSet.hh" :  "" ""
	copy ..\.\Core\IO\EventSet.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header EventSet.hh

"C:\Build\inc\Ravl\DP\EventSet.hh" :  "" ""
	copy ..\.\Core\IO\EventSet.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Method2Proc.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Method2Proc.hh

"C:\Build\inc\Ravl\DP\Method2Proc.hh" :  "" ""
	copy ..\.\Core\IO\Method2Proc.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Method2Proc.hh

"C:\Build\inc\Ravl\DP\Method2Proc.hh" :  "" ""
	copy ..\.\Core\IO\Method2Proc.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\MethodIO.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header MethodIO.hh

"C:\Build\inc\Ravl\DP\MethodIO.hh" :  "" ""
	copy ..\.\Core\IO\MethodIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header MethodIO.hh

"C:\Build\inc\Ravl\DP\MethodIO.hh" :  "" ""
	copy ..\.\Core\IO\MethodIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\ContainerIO.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header ContainerIO.hh

"C:\Build\inc\Ravl\DP\ContainerIO.hh" :  "" ""
	copy ..\.\Core\IO\ContainerIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header ContainerIO.hh

"C:\Build\inc\Ravl\DP\ContainerIO.hh" :  "" ""
	copy ..\.\Core\IO\ContainerIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Plug.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Plug.hh

"C:\Build\inc\Ravl\DP\Plug.hh" :  "" ""
	copy ..\.\Core\IO\Plug.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Plug.hh

"C:\Build\inc\Ravl\DP\Plug.hh" :  "" ""
	copy ..\.\Core\IO\Plug.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Tap.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Tap.hh

"C:\Build\inc\Ravl\DP\Tap.hh" :  "" ""
	copy ..\.\Core\IO\Tap.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Tap.hh

"C:\Build\inc\Ravl\DP\Tap.hh" :  "" ""
	copy ..\.\Core\IO\Tap.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\StreamProcess.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header StreamProcess.hh

"C:\Build\inc\Ravl\DP\StreamProcess.hh" :  "" ""
	copy ..\.\Core\IO\StreamProcess.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header StreamProcess.hh

"C:\Build\inc\Ravl\DP\StreamProcess.hh" :  "" ""
	copy ..\.\Core\IO\StreamProcess.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Process21.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Process21.hh

"C:\Build\inc\Ravl\DP\Process21.hh" :  "" ""
	copy ..\.\Core\IO\Process21.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Process21.hh

"C:\Build\inc\Ravl\DP\Process21.hh" :  "" ""
	copy ..\.\Core\IO\Process21.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Process31.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Process31.hh

"C:\Build\inc\Ravl\DP\Process31.hh" :  "" ""
	copy ..\.\Core\IO\Process31.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Process31.hh

"C:\Build\inc\Ravl\DP\Process31.hh" :  "" ""
	copy ..\.\Core\IO\Process31.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Method2Proc21.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Method2Proc21.hh

"C:\Build\inc\Ravl\DP\Method2Proc21.hh" :  "" ""
	copy ..\.\Core\IO\Method2Proc21.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Method2Proc21.hh

"C:\Build\inc\Ravl\DP\Method2Proc21.hh" :  "" ""
	copy ..\.\Core\IO\Method2Proc21.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Method2Proc31.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Method2Proc31.hh

"C:\Build\inc\Ravl\DP\Method2Proc31.hh" :  "" ""
	copy ..\.\Core\IO\Method2Proc31.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Method2Proc31.hh

"C:\Build\inc\Ravl\DP\Method2Proc31.hh" :  "" ""
	copy ..\.\Core\IO\Method2Proc31.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\StreamOp21.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header StreamOp21.hh

"C:\Build\inc\Ravl\DP\StreamOp21.hh" :  "" ""
	copy ..\.\Core\IO\StreamOp21.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header StreamOp21.hh

"C:\Build\inc\Ravl\DP\StreamOp21.hh" :  "" ""
	copy ..\.\Core\IO\StreamOp21.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\StreamOp31.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header StreamOp31.hh

"C:\Build\inc\Ravl\DP\StreamOp31.hh" :  "" ""
	copy ..\.\Core\IO\StreamOp31.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header StreamOp31.hh

"C:\Build\inc\Ravl\DP\StreamOp31.hh" :  "" ""
	copy ..\.\Core\IO\StreamOp31.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Func2Proc21.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Func2Proc21.hh

"C:\Build\inc\Ravl\DP\Func2Proc21.hh" :  "" ""
	copy ..\.\Core\IO\Func2Proc21.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Func2Proc21.hh

"C:\Build\inc\Ravl\DP\Func2Proc21.hh" :  "" ""
	copy ..\.\Core\IO\Func2Proc21.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\Func2Proc31.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header Func2Proc31.hh

"C:\Build\inc\Ravl\DP\Func2Proc31.hh" :  "" ""
	copy ..\.\Core\IO\Func2Proc31.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header Func2Proc31.hh

"C:\Build\inc\Ravl\DP\Func2Proc31.hh" :  "" ""
	copy ..\.\Core\IO\Func2Proc31.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\OffsetScale.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header OffsetScale.hh

"C:\Build\inc\Ravl\DP\OffsetScale.hh" :  "" ""
	copy ..\.\Core\IO\OffsetScale.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header OffsetScale.hh

"C:\Build\inc\Ravl\DP\OffsetScale.hh" :  "" ""
	copy ..\.\Core\IO\OffsetScale.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\RunningAverage.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header RunningAverage.hh

"C:\Build\inc\Ravl\DP\RunningAverage.hh" :  "" ""
	copy ..\.\Core\IO\RunningAverage.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header RunningAverage.hh

"C:\Build\inc\Ravl\DP\RunningAverage.hh" :  "" ""
	copy ..\.\Core\IO\RunningAverage.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\IOPort.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header IOPort.hh

"C:\Build\inc\Ravl\DP\IOPort.hh" :  "" ""
	copy ..\.\Core\IO\IOPort.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header IOPort.hh

"C:\Build\inc\Ravl\DP\IOPort.hh" :  "" ""
	copy ..\.\Core\IO\IOPort.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\XMLFileIO.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header XMLFileIO.hh

"C:\Build\inc\Ravl\DP\XMLFileIO.hh" :  "" ""
	copy ..\.\Core\IO\XMLFileIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header XMLFileIO.hh

"C:\Build\inc\Ravl\DP\XMLFileIO.hh" :  "" ""
	copy ..\.\Core\IO\XMLFileIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\FileFormatXMLStream.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header FileFormatXMLStream.hh

"C:\Build\inc\Ravl\DP\FileFormatXMLStream.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatXMLStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header FileFormatXMLStream.hh

"C:\Build\inc\Ravl\DP\FileFormatXMLStream.hh" :  "" ""
	copy ..\.\Core\IO\FileFormatXMLStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\ListIO.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header ListIO.hh

"C:\Build\inc\Ravl\DP\ListIO.hh" :  "" ""
	copy ..\.\Core\IO\ListIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header ListIO.hh

"C:\Build\inc\Ravl\DP\ListIO.hh" :  "" ""
	copy ..\.\Core\IO\ListIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeType.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header AttributeType.hh

"C:\Build\inc\Ravl\DP\AttributeType.hh" :  "" ""
	copy ..\.\Core\IO\AttributeType.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header AttributeType.hh

"C:\Build\inc\Ravl\DP\AttributeType.hh" :  "" ""
	copy ..\.\Core\IO\AttributeType.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeCtrl.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header AttributeCtrl.hh

"C:\Build\inc\Ravl\DP\AttributeCtrl.hh" :  "" ""
	copy ..\.\Core\IO\AttributeCtrl.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header AttributeCtrl.hh

"C:\Build\inc\Ravl\DP\AttributeCtrl.hh" :  "" ""
	copy ..\.\Core\IO\AttributeCtrl.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeValueTypes.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header AttributeValueTypes.hh

"C:\Build\inc\Ravl\DP\AttributeValueTypes.hh" :  "" ""
	copy ..\.\Core\IO\AttributeValueTypes.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header AttributeValueTypes.hh

"C:\Build\inc\Ravl\DP\AttributeValueTypes.hh" :  "" ""
	copy ..\.\Core\IO\AttributeValueTypes.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeSet.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header AttributeSet.hh

"C:\Build\inc\Ravl\DP\AttributeSet.hh" :  "" ""
	copy ..\.\Core\IO\AttributeSet.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header AttributeSet.hh

"C:\Build\inc\Ravl\DP\AttributeSet.hh" :  "" ""
	copy ..\.\Core\IO\AttributeSet.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeCtrlInternal.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header AttributeCtrlInternal.hh

"C:\Build\inc\Ravl\DP\AttributeCtrlInternal.hh" :  "" ""
	copy ..\.\Core\IO\AttributeCtrlInternal.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header AttributeCtrlInternal.hh

"C:\Build\inc\Ravl\DP\AttributeCtrlInternal.hh" :  "" ""
	copy ..\.\Core\IO\AttributeCtrlInternal.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\ByteFileIO.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header ByteFileIO.hh

"C:\Build\inc\Ravl\DP\ByteFileIO.hh" :  "" ""
	copy ..\.\Core\IO\ByteFileIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header ByteFileIO.hh

"C:\Build\inc\Ravl\DP\ByteFileIO.hh" :  "" ""
	copy ..\.\Core\IO\ByteFileIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\SampleStream.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header SampleStream.hh

"C:\Build\inc\Ravl\DP\SampleStream.hh" :  "" ""
	copy ..\.\Core\IO\SampleStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header SampleStream.hh

"C:\Build\inc\Ravl\DP\SampleStream.hh" :  "" ""
	copy ..\.\Core\IO\SampleStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\CacheIStream.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header CacheIStream.hh

"C:\Build\inc\Ravl\DP\CacheIStream.hh" :  "" ""
	copy ..\.\Core\IO\CacheIStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header CacheIStream.hh

"C:\Build\inc\Ravl\DP\CacheIStream.hh" :  "" ""
	copy ..\.\Core\IO\CacheIStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\ByteStream.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header ByteStream.hh

"C:\Build\inc\Ravl\DP\ByteStream.hh" :  "" ""
	copy ..\.\Core\IO\ByteStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header ByteStream.hh

"C:\Build\inc\Ravl\DP\ByteStream.hh" :  "" ""
	copy ..\.\Core\IO\ByteStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\SByteStream.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header SByteStream.hh

"C:\Build\inc\Ravl\DP\SByteStream.hh" :  "" ""
	copy ..\.\Core\IO\SByteStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header SByteStream.hh

"C:\Build\inc\Ravl\DP\SByteStream.hh" :  "" ""
	copy ..\.\Core\IO\SByteStream.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\MemIO.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header MemIO.hh

"C:\Build\inc\Ravl\DP\MemIO.hh" :  "" ""
	copy ..\.\Core\IO\MemIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header MemIO.hh

"C:\Build\inc\Ravl\DP\MemIO.hh" :  "" ""
	copy ..\.\Core\IO\MemIO.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\AttributeCtrlUpdateSignal.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header AttributeCtrlUpdateSignal.hh

"C:\Build\inc\Ravl\DP\AttributeCtrlUpdateSignal.hh" :  "" ""
	copy ..\.\Core\IO\AttributeCtrlUpdateSignal.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header AttributeCtrlUpdateSignal.hh

"C:\Build\inc\Ravl\DP\AttributeCtrlUpdateSignal.hh" :  "" ""
	copy ..\.\Core\IO\AttributeCtrlUpdateSignal.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Core\IO\PrintIOInfo.hh

!IF  "$(CFG)" == "RavlIO - Win32 Release"

# Begin Custom Build - Install Header PrintIOInfo.hh

"C:\Build\inc\Ravl\DP\PrintIOInfo.hh" :  "" ""
	copy ..\.\Core\IO\PrintIOInfo.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlIO - Win32 Debug"

# Begin Custom Build - Install Header PrintIOInfo.hh

"C:\Build\inc\Ravl\DP\PrintIOInfo.hh" :  "" ""
	copy ..\.\Core\IO\PrintIOInfo.hh C:\Build\inc\Ravl\DP

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
