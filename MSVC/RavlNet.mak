


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlNet
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlNet
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/Socket.obj $(OPTOBJDIR)/NetStream.obj $(OPTOBJDIR)/SocketStrm.obj $(OPTOBJDIR)/Packet.obj $(OPTOBJDIR)/NetMessage.obj $(OPTOBJDIR)/NetEndPoint.obj $(OPTOBJDIR)/NetMsgCall.obj $(OPTOBJDIR)/NetIPort.obj $(OPTOBJDIR)/NetIPortServer.obj $(OPTOBJDIR)/NetPortManager.obj $(OPTOBJDIR)/NetPortClient.obj $(OPTOBJDIR)/NetPortFormat.obj $(OPTOBJDIR)/NetOPort.obj $(OPTOBJDIR)/NetOPortServer.obj $(OPTOBJDIR)/NetPort.obj $(OPTOBJDIR)/NetAttributeCtrl.obj $(OPTOBJDIR)/NetRequestManager.obj $(OPTOBJDIR)/NetAttributeCtrlServer.obj $(OPTOBJDIR)/NetByteStream.obj $(OPTOBJDIR)/NetMsgOPortData.obj $(OPTOBJDIR)/WinSocket.obj $(OPTOBJDIR)/RavlSysNetworkML.obj
	@echo -- making $(OPTLIBDIR)/RavlNet.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlNet.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/Socket.obj $(DEBUGOBJDIR)/NetStream.obj $(DEBUGOBJDIR)/SocketStrm.obj $(DEBUGOBJDIR)/Packet.obj $(DEBUGOBJDIR)/NetMessage.obj $(DEBUGOBJDIR)/NetEndPoint.obj $(DEBUGOBJDIR)/NetMsgCall.obj $(DEBUGOBJDIR)/NetIPort.obj $(DEBUGOBJDIR)/NetIPortServer.obj $(DEBUGOBJDIR)/NetPortManager.obj $(DEBUGOBJDIR)/NetPortClient.obj $(DEBUGOBJDIR)/NetPortFormat.obj $(DEBUGOBJDIR)/NetOPort.obj $(DEBUGOBJDIR)/NetOPortServer.obj $(DEBUGOBJDIR)/NetPort.obj $(DEBUGOBJDIR)/NetAttributeCtrl.obj $(DEBUGOBJDIR)/NetRequestManager.obj $(DEBUGOBJDIR)/NetAttributeCtrlServer.obj $(DEBUGOBJDIR)/NetByteStream.obj $(DEBUGOBJDIR)/NetMsgOPortData.obj $(DEBUGOBJDIR)/WinSocket.obj $(DEBUGOBJDIR)/RavlSysNetworkML.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlNet.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlNet.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlNet
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/Socket.obj: .././OS/Network/Socket.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Socket.obj .././OS/Network/Socket.cc

$(DEBUGOBJDIR)/Socket.obj: .././OS/Network/Socket.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Socket.obj .././OS/Network/Socket.cc

$(OPTOBJDIR)/NetStream.obj: .././OS/Network/NetStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetStream.obj .././OS/Network/NetStream.cc

$(DEBUGOBJDIR)/NetStream.obj: .././OS/Network/NetStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetStream.obj .././OS/Network/NetStream.cc

$(OPTOBJDIR)/SocketStrm.obj: .././OS/Network/SocketStrm.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SocketStrm.obj .././OS/Network/SocketStrm.cc

$(DEBUGOBJDIR)/SocketStrm.obj: .././OS/Network/SocketStrm.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SocketStrm.obj .././OS/Network/SocketStrm.cc

$(OPTOBJDIR)/Packet.obj: .././OS/Network/Packet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Packet.obj .././OS/Network/Packet.cc

$(DEBUGOBJDIR)/Packet.obj: .././OS/Network/Packet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Packet.obj .././OS/Network/Packet.cc

$(OPTOBJDIR)/NetMessage.obj: .././OS/Network/NetMessage.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetMessage.obj .././OS/Network/NetMessage.cc

$(DEBUGOBJDIR)/NetMessage.obj: .././OS/Network/NetMessage.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetMessage.obj .././OS/Network/NetMessage.cc

$(OPTOBJDIR)/NetEndPoint.obj: .././OS/Network/NetEndPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetEndPoint.obj .././OS/Network/NetEndPoint.cc

$(DEBUGOBJDIR)/NetEndPoint.obj: .././OS/Network/NetEndPoint.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetEndPoint.obj .././OS/Network/NetEndPoint.cc

$(OPTOBJDIR)/NetMsgCall.obj: .././OS/Network/NetMsgCall.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetMsgCall.obj .././OS/Network/NetMsgCall.cc

$(DEBUGOBJDIR)/NetMsgCall.obj: .././OS/Network/NetMsgCall.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetMsgCall.obj .././OS/Network/NetMsgCall.cc

$(OPTOBJDIR)/NetIPort.obj: .././OS/Network/NetIPort.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetIPort.obj .././OS/Network/NetIPort.cc

$(DEBUGOBJDIR)/NetIPort.obj: .././OS/Network/NetIPort.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetIPort.obj .././OS/Network/NetIPort.cc

$(OPTOBJDIR)/NetIPortServer.obj: .././OS/Network/NetIPortServer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetIPortServer.obj .././OS/Network/NetIPortServer.cc

$(DEBUGOBJDIR)/NetIPortServer.obj: .././OS/Network/NetIPortServer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetIPortServer.obj .././OS/Network/NetIPortServer.cc

$(OPTOBJDIR)/NetPortManager.obj: .././OS/Network/NetPortManager.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetPortManager.obj .././OS/Network/NetPortManager.cc

$(DEBUGOBJDIR)/NetPortManager.obj: .././OS/Network/NetPortManager.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetPortManager.obj .././OS/Network/NetPortManager.cc

$(OPTOBJDIR)/NetPortClient.obj: .././OS/Network/NetPortClient.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetPortClient.obj .././OS/Network/NetPortClient.cc

$(DEBUGOBJDIR)/NetPortClient.obj: .././OS/Network/NetPortClient.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetPortClient.obj .././OS/Network/NetPortClient.cc

$(OPTOBJDIR)/NetPortFormat.obj: .././OS/Network/NetPortFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetPortFormat.obj .././OS/Network/NetPortFormat.cc

$(DEBUGOBJDIR)/NetPortFormat.obj: .././OS/Network/NetPortFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetPortFormat.obj .././OS/Network/NetPortFormat.cc

$(OPTOBJDIR)/NetOPort.obj: .././OS/Network/NetOPort.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetOPort.obj .././OS/Network/NetOPort.cc

$(DEBUGOBJDIR)/NetOPort.obj: .././OS/Network/NetOPort.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetOPort.obj .././OS/Network/NetOPort.cc

$(OPTOBJDIR)/NetOPortServer.obj: .././OS/Network/NetOPortServer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetOPortServer.obj .././OS/Network/NetOPortServer.cc

$(DEBUGOBJDIR)/NetOPortServer.obj: .././OS/Network/NetOPortServer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetOPortServer.obj .././OS/Network/NetOPortServer.cc

$(OPTOBJDIR)/NetPort.obj: .././OS/Network/NetPort.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetPort.obj .././OS/Network/NetPort.cc

$(DEBUGOBJDIR)/NetPort.obj: .././OS/Network/NetPort.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetPort.obj .././OS/Network/NetPort.cc

$(OPTOBJDIR)/NetAttributeCtrl.obj: .././OS/Network/NetAttributeCtrl.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetAttributeCtrl.obj .././OS/Network/NetAttributeCtrl.cc

$(DEBUGOBJDIR)/NetAttributeCtrl.obj: .././OS/Network/NetAttributeCtrl.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetAttributeCtrl.obj .././OS/Network/NetAttributeCtrl.cc

$(OPTOBJDIR)/NetRequestManager.obj: .././OS/Network/NetRequestManager.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetRequestManager.obj .././OS/Network/NetRequestManager.cc

$(DEBUGOBJDIR)/NetRequestManager.obj: .././OS/Network/NetRequestManager.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetRequestManager.obj .././OS/Network/NetRequestManager.cc

$(OPTOBJDIR)/NetAttributeCtrlServer.obj: .././OS/Network/NetAttributeCtrlServer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetAttributeCtrlServer.obj .././OS/Network/NetAttributeCtrlServer.cc

$(DEBUGOBJDIR)/NetAttributeCtrlServer.obj: .././OS/Network/NetAttributeCtrlServer.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetAttributeCtrlServer.obj .././OS/Network/NetAttributeCtrlServer.cc

$(OPTOBJDIR)/NetByteStream.obj: .././OS/Network/NetByteStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetByteStream.obj .././OS/Network/NetByteStream.cc

$(DEBUGOBJDIR)/NetByteStream.obj: .././OS/Network/NetByteStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetByteStream.obj .././OS/Network/NetByteStream.cc

$(OPTOBJDIR)/NetMsgOPortData.obj: .././OS/Network/NetMsgOPortData.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/NetMsgOPortData.obj .././OS/Network/NetMsgOPortData.cc

$(DEBUGOBJDIR)/NetMsgOPortData.obj: .././OS/Network/NetMsgOPortData.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/NetMsgOPortData.obj .././OS/Network/NetMsgOPortData.cc

$(OPTOBJDIR)/WinSocket.obj: .././OS/Network/WinSocket.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/WinSocket.obj .././OS/Network/WinSocket.cc

$(DEBUGOBJDIR)/WinSocket.obj: .././OS/Network/WinSocket.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/WinSocket.obj .././OS/Network/WinSocket.cc

$(OPTOBJDIR)/RavlSysNetworkML.obj: .././OS/Network/RavlSysNetworkML.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RavlSysNetworkML.obj .././OS/Network/RavlSysNetworkML.cc

$(DEBUGOBJDIR)/RavlSysNetworkML.obj: .././OS/Network/RavlSysNetworkML.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RavlSysNetworkML.obj .././OS/Network/RavlSysNetworkML.cc


