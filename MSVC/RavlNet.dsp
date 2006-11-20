# Microsoft Developer Studio Project File - Name="RavlNet" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlNet - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlNet.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlNet.mak" CFG="RavlNet - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlNet - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlNet - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlNet"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlNet"
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

# Name "RavlNet - Win32 Release"
# Name "RavlNet - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\OS\Network\Socket.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\SocketStrm.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\Packet.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetMessage.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetEndPoint.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetMsgCall.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetIPort.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetIPortServer.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetPortManager.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetPortClient.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetPortFormat.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetOPort.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetOPortServer.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetPort.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetAttributeCtrl.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetRequestManager.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetAttributeCtrlServer.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetByteStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetMsgOPortData.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\WinSocket.cc
# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\RavlSysNetworkML.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\OS\Network\SktError.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header SktError.hh

"C:\Build\inc\Ravl\OS\SktError.hh" :  "" ""
	copy ..\.\OS\Network\SktError.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header SktError.hh

"C:\Build\inc\Ravl\OS\SktError.hh" :  "" ""
	copy ..\.\OS\Network\SktError.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\Socket.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header Socket.hh

"C:\Build\inc\Ravl\OS\Socket.hh" :  "" ""
	copy ..\.\OS\Network\Socket.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header Socket.hh

"C:\Build\inc\Ravl\OS\Socket.hh" :  "" ""
	copy ..\.\OS\Network\Socket.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetStream.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetStream.hh

"C:\Build\inc\Ravl\OS\NetStream.hh" :  "" ""
	copy ..\.\OS\Network\NetStream.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetStream.hh

"C:\Build\inc\Ravl\OS\NetStream.hh" :  "" ""
	copy ..\.\OS\Network\NetStream.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\Packet.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header Packet.hh

"C:\Build\inc\Ravl\OS\Packet.hh" :  "" ""
	copy ..\.\OS\Network\Packet.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header Packet.hh

"C:\Build\inc\Ravl\OS\Packet.hh" :  "" ""
	copy ..\.\OS\Network\Packet.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetMessage.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetMessage.hh

"C:\Build\inc\Ravl\OS\NetMessage.hh" :  "" ""
	copy ..\.\OS\Network\NetMessage.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetMessage.hh

"C:\Build\inc\Ravl\OS\NetMessage.hh" :  "" ""
	copy ..\.\OS\Network\NetMessage.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetEndPoint.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetEndPoint.hh

"C:\Build\inc\Ravl\OS\NetEndPoint.hh" :  "" ""
	copy ..\.\OS\Network\NetEndPoint.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetEndPoint.hh

"C:\Build\inc\Ravl\OS\NetEndPoint.hh" :  "" ""
	copy ..\.\OS\Network\NetEndPoint.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetMsgCall.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetMsgCall.hh

"C:\Build\inc\Ravl\OS\NetMsgCall.hh" :  "" ""
	copy ..\.\OS\Network\NetMsgCall.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetMsgCall.hh

"C:\Build\inc\Ravl\OS\NetMsgCall.hh" :  "" ""
	copy ..\.\OS\Network\NetMsgCall.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetIPort.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetIPort.hh

"C:\Build\inc\Ravl\OS\NetIPort.hh" :  "" ""
	copy ..\.\OS\Network\NetIPort.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetIPort.hh

"C:\Build\inc\Ravl\OS\NetIPort.hh" :  "" ""
	copy ..\.\OS\Network\NetIPort.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetIPortServer.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetIPortServer.hh

"C:\Build\inc\Ravl\OS\NetIPortServer.hh" :  "" ""
	copy ..\.\OS\Network\NetIPortServer.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetIPortServer.hh

"C:\Build\inc\Ravl\OS\NetIPortServer.hh" :  "" ""
	copy ..\.\OS\Network\NetIPortServer.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetPortManager.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetPortManager.hh

"C:\Build\inc\Ravl\OS\NetPortManager.hh" :  "" ""
	copy ..\.\OS\Network\NetPortManager.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetPortManager.hh

"C:\Build\inc\Ravl\OS\NetPortManager.hh" :  "" ""
	copy ..\.\OS\Network\NetPortManager.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetPortClient.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetPortClient.hh

"C:\Build\inc\Ravl\OS\NetPortClient.hh" :  "" ""
	copy ..\.\OS\Network\NetPortClient.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetPortClient.hh

"C:\Build\inc\Ravl\OS\NetPortClient.hh" :  "" ""
	copy ..\.\OS\Network\NetPortClient.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetPortFormat.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetPortFormat.hh

"C:\Build\inc\Ravl\OS\NetPortFormat.hh" :  "" ""
	copy ..\.\OS\Network\NetPortFormat.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetPortFormat.hh

"C:\Build\inc\Ravl\OS\NetPortFormat.hh" :  "" ""
	copy ..\.\OS\Network\NetPortFormat.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetOPort.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetOPort.hh

"C:\Build\inc\Ravl\OS\NetOPort.hh" :  "" ""
	copy ..\.\OS\Network\NetOPort.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetOPort.hh

"C:\Build\inc\Ravl\OS\NetOPort.hh" :  "" ""
	copy ..\.\OS\Network\NetOPort.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetOPortServer.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetOPortServer.hh

"C:\Build\inc\Ravl\OS\NetOPortServer.hh" :  "" ""
	copy ..\.\OS\Network\NetOPortServer.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetOPortServer.hh

"C:\Build\inc\Ravl\OS\NetOPortServer.hh" :  "" ""
	copy ..\.\OS\Network\NetOPortServer.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetPort.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetPort.hh

"C:\Build\inc\Ravl\OS\NetPort.hh" :  "" ""
	copy ..\.\OS\Network\NetPort.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetPort.hh

"C:\Build\inc\Ravl\OS\NetPort.hh" :  "" ""
	copy ..\.\OS\Network\NetPort.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetAttributeCtrl.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetAttributeCtrl.hh

"C:\Build\inc\Ravl\OS\NetAttributeCtrl.hh" :  "" ""
	copy ..\.\OS\Network\NetAttributeCtrl.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetAttributeCtrl.hh

"C:\Build\inc\Ravl\OS\NetAttributeCtrl.hh" :  "" ""
	copy ..\.\OS\Network\NetAttributeCtrl.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetRequestManager.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetRequestManager.hh

"C:\Build\inc\Ravl\OS\NetRequestManager.hh" :  "" ""
	copy ..\.\OS\Network\NetRequestManager.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetRequestManager.hh

"C:\Build\inc\Ravl\OS\NetRequestManager.hh" :  "" ""
	copy ..\.\OS\Network\NetRequestManager.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetAttributeCtrlServer.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetAttributeCtrlServer.hh

"C:\Build\inc\Ravl\OS\NetAttributeCtrlServer.hh" :  "" ""
	copy ..\.\OS\Network\NetAttributeCtrlServer.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetAttributeCtrlServer.hh

"C:\Build\inc\Ravl\OS\NetAttributeCtrlServer.hh" :  "" ""
	copy ..\.\OS\Network\NetAttributeCtrlServer.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetByteStream.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetByteStream.hh

"C:\Build\inc\Ravl\OS\NetByteStream.hh" :  "" ""
	copy ..\.\OS\Network\NetByteStream.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetByteStream.hh

"C:\Build\inc\Ravl\OS\NetByteStream.hh" :  "" ""
	copy ..\.\OS\Network\NetByteStream.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\NetMsgOPortData.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header NetMsgOPortData.hh

"C:\Build\inc\Ravl\OS\NetMsgOPortData.hh" :  "" ""
	copy ..\.\OS\Network\NetMsgOPortData.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header NetMsgOPortData.hh

"C:\Build\inc\Ravl\OS\NetMsgOPortData.hh" :  "" ""
	copy ..\.\OS\Network\NetMsgOPortData.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\OS\Network\WinSocket.hh

!IF  "$(CFG)" == "RavlNet - Win32 Release"

# Begin Custom Build - Install Header WinSocket.hh

"C:\Build\inc\Ravl\OS\WinSocket.hh" :  "" ""
	copy ..\.\OS\Network\WinSocket.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlNet - Win32 Debug"

# Begin Custom Build - Install Header WinSocket.hh

"C:\Build\inc\Ravl\OS\WinSocket.hh" :  "" ""
	copy ..\.\OS\Network\WinSocket.hh C:\Build\inc\Ravl\OS

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
