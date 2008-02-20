


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlIO
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlIO
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavlIO  $(OPTOBJDIR)/Entity.obj $(OPTOBJDIR)/Process.obj $(OPTOBJDIR)/Port.obj $(OPTOBJDIR)/SPort.obj $(OPTOBJDIR)/SPortAttach.obj $(OPTOBJDIR)/ProcInfo.obj $(OPTOBJDIR)/Converter.obj $(OPTOBJDIR)/TypeInfo.obj $(OPTOBJDIR)/Pipes.obj $(OPTOBJDIR)/FileFormat.obj $(OPTOBJDIR)/FileFormatDesc.obj $(OPTOBJDIR)/FileFormatStream.obj $(OPTOBJDIR)/FileFormatBinStream.obj $(OPTOBJDIR)/FileFormatGen.obj $(OPTOBJDIR)/FileFormatIO.obj $(OPTOBJDIR)/TypeConverter.obj $(OPTOBJDIR)/FileFormatRegistry.obj $(OPTOBJDIR)/IndexIO.obj $(OPTOBJDIR)/Event.obj $(OPTOBJDIR)/EventSet.obj $(OPTOBJDIR)/Plug.obj $(OPTOBJDIR)/StreamOp.obj $(OPTOBJDIR)/StreamProcess.obj $(OPTOBJDIR)/IOConnect.obj $(OPTOBJDIR)/FileFormatXMLStream.obj $(OPTOBJDIR)/DataConv.obj $(OPTOBJDIR)/AttributeCtrl.obj $(OPTOBJDIR)/AttributeType.obj $(OPTOBJDIR)/AttributeValueTypes.obj $(OPTOBJDIR)/AttributeCtrlXML.obj $(OPTOBJDIR)/AttributeSet.obj $(OPTOBJDIR)/ByteFileIO.obj $(OPTOBJDIR)/ByteStream.obj $(OPTOBJDIR)/SByteStream.obj $(OPTOBJDIR)/AttributeCtrlInternal.obj $(OPTOBJDIR)/AttributeCtrlUpdateSignal.obj $(OPTOBJDIR)/PrintIOInfo.obj $(OPTOBJDIR)/CoreIO.obj
	@echo -- making $(OPTLIBDIR)/RavlIO.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlIO.lib $(OPTOBJDIR)/*.obj


debug:: setupRavlIO  $(DEBUGOBJDIR)/Entity.obj $(DEBUGOBJDIR)/Process.obj $(DEBUGOBJDIR)/Port.obj $(DEBUGOBJDIR)/SPort.obj $(DEBUGOBJDIR)/SPortAttach.obj $(DEBUGOBJDIR)/ProcInfo.obj $(DEBUGOBJDIR)/Converter.obj $(DEBUGOBJDIR)/TypeInfo.obj $(DEBUGOBJDIR)/Pipes.obj $(DEBUGOBJDIR)/FileFormat.obj $(DEBUGOBJDIR)/FileFormatDesc.obj $(DEBUGOBJDIR)/FileFormatStream.obj $(DEBUGOBJDIR)/FileFormatBinStream.obj $(DEBUGOBJDIR)/FileFormatGen.obj $(DEBUGOBJDIR)/FileFormatIO.obj $(DEBUGOBJDIR)/TypeConverter.obj $(DEBUGOBJDIR)/FileFormatRegistry.obj $(DEBUGOBJDIR)/IndexIO.obj $(DEBUGOBJDIR)/Event.obj $(DEBUGOBJDIR)/EventSet.obj $(DEBUGOBJDIR)/Plug.obj $(DEBUGOBJDIR)/StreamOp.obj $(DEBUGOBJDIR)/StreamProcess.obj $(DEBUGOBJDIR)/IOConnect.obj $(DEBUGOBJDIR)/FileFormatXMLStream.obj $(DEBUGOBJDIR)/DataConv.obj $(DEBUGOBJDIR)/AttributeCtrl.obj $(DEBUGOBJDIR)/AttributeType.obj $(DEBUGOBJDIR)/AttributeValueTypes.obj $(DEBUGOBJDIR)/AttributeCtrlXML.obj $(DEBUGOBJDIR)/AttributeSet.obj $(DEBUGOBJDIR)/ByteFileIO.obj $(DEBUGOBJDIR)/ByteStream.obj $(DEBUGOBJDIR)/SByteStream.obj $(DEBUGOBJDIR)/AttributeCtrlInternal.obj $(DEBUGOBJDIR)/AttributeCtrlUpdateSignal.obj $(DEBUGOBJDIR)/PrintIOInfo.obj $(DEBUGOBJDIR)/CoreIO.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlIO.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlIO.lib $(DEBUGOBJDIR)/*.obj

setupRavlIO::
        echo --- creating dir for RavlIO
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/Entity.obj: .././Core/IO/Entity.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Entity.obj .././Core/IO/Entity.cc

$(DEBUGOBJDIR)/Entity.obj: .././Core/IO/Entity.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Entity.obj .././Core/IO/Entity.cc

$(OPTOBJDIR)/Process.obj: .././Core/IO/Process.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Process.obj .././Core/IO/Process.cc

$(DEBUGOBJDIR)/Process.obj: .././Core/IO/Process.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Process.obj .././Core/IO/Process.cc

$(OPTOBJDIR)/Port.obj: .././Core/IO/Port.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Port.obj .././Core/IO/Port.cc

$(DEBUGOBJDIR)/Port.obj: .././Core/IO/Port.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Port.obj .././Core/IO/Port.cc

$(OPTOBJDIR)/SPort.obj: .././Core/IO/SPort.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SPort.obj .././Core/IO/SPort.cc

$(DEBUGOBJDIR)/SPort.obj: .././Core/IO/SPort.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SPort.obj .././Core/IO/SPort.cc

$(OPTOBJDIR)/SPortAttach.obj: .././Core/IO/SPortAttach.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SPortAttach.obj .././Core/IO/SPortAttach.cc

$(DEBUGOBJDIR)/SPortAttach.obj: .././Core/IO/SPortAttach.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SPortAttach.obj .././Core/IO/SPortAttach.cc

$(OPTOBJDIR)/ProcInfo.obj: .././Core/IO/ProcInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ProcInfo.obj .././Core/IO/ProcInfo.cc

$(DEBUGOBJDIR)/ProcInfo.obj: .././Core/IO/ProcInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ProcInfo.obj .././Core/IO/ProcInfo.cc

$(OPTOBJDIR)/Converter.obj: .././Core/IO/Converter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Converter.obj .././Core/IO/Converter.cc

$(DEBUGOBJDIR)/Converter.obj: .././Core/IO/Converter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Converter.obj .././Core/IO/Converter.cc

$(OPTOBJDIR)/TypeInfo.obj: .././Core/IO/TypeInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TypeInfo.obj .././Core/IO/TypeInfo.cc

$(DEBUGOBJDIR)/TypeInfo.obj: .././Core/IO/TypeInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TypeInfo.obj .././Core/IO/TypeInfo.cc

$(OPTOBJDIR)/Pipes.obj: .././Core/IO/Pipes.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Pipes.obj .././Core/IO/Pipes.cc

$(DEBUGOBJDIR)/Pipes.obj: .././Core/IO/Pipes.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Pipes.obj .././Core/IO/Pipes.cc

$(OPTOBJDIR)/FileFormat.obj: .././Core/IO/FileFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileFormat.obj .././Core/IO/FileFormat.cc

$(DEBUGOBJDIR)/FileFormat.obj: .././Core/IO/FileFormat.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileFormat.obj .././Core/IO/FileFormat.cc

$(OPTOBJDIR)/FileFormatDesc.obj: .././Core/IO/FileFormatDesc.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileFormatDesc.obj .././Core/IO/FileFormatDesc.cc

$(DEBUGOBJDIR)/FileFormatDesc.obj: .././Core/IO/FileFormatDesc.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileFormatDesc.obj .././Core/IO/FileFormatDesc.cc

$(OPTOBJDIR)/FileFormatStream.obj: .././Core/IO/FileFormatStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileFormatStream.obj .././Core/IO/FileFormatStream.cc

$(DEBUGOBJDIR)/FileFormatStream.obj: .././Core/IO/FileFormatStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileFormatStream.obj .././Core/IO/FileFormatStream.cc

$(OPTOBJDIR)/FileFormatBinStream.obj: .././Core/IO/FileFormatBinStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileFormatBinStream.obj .././Core/IO/FileFormatBinStream.cc

$(DEBUGOBJDIR)/FileFormatBinStream.obj: .././Core/IO/FileFormatBinStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileFormatBinStream.obj .././Core/IO/FileFormatBinStream.cc

$(OPTOBJDIR)/FileFormatGen.obj: .././Core/IO/FileFormatGen.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileFormatGen.obj .././Core/IO/FileFormatGen.cc

$(DEBUGOBJDIR)/FileFormatGen.obj: .././Core/IO/FileFormatGen.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileFormatGen.obj .././Core/IO/FileFormatGen.cc

$(OPTOBJDIR)/FileFormatIO.obj: .././Core/IO/FileFormatIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileFormatIO.obj .././Core/IO/FileFormatIO.cc

$(DEBUGOBJDIR)/FileFormatIO.obj: .././Core/IO/FileFormatIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileFormatIO.obj .././Core/IO/FileFormatIO.cc

$(OPTOBJDIR)/TypeConverter.obj: .././Core/IO/TypeConverter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TypeConverter.obj .././Core/IO/TypeConverter.cc

$(DEBUGOBJDIR)/TypeConverter.obj: .././Core/IO/TypeConverter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TypeConverter.obj .././Core/IO/TypeConverter.cc

$(OPTOBJDIR)/FileFormatRegistry.obj: .././Core/IO/FileFormatRegistry.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileFormatRegistry.obj .././Core/IO/FileFormatRegistry.cc

$(DEBUGOBJDIR)/FileFormatRegistry.obj: .././Core/IO/FileFormatRegistry.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileFormatRegistry.obj .././Core/IO/FileFormatRegistry.cc

$(OPTOBJDIR)/IndexIO.obj: .././Core/IO/IndexIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/IndexIO.obj .././Core/IO/IndexIO.cc

$(DEBUGOBJDIR)/IndexIO.obj: .././Core/IO/IndexIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/IndexIO.obj .././Core/IO/IndexIO.cc

$(OPTOBJDIR)/Event.obj: .././Core/IO/Event.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Event.obj .././Core/IO/Event.cc

$(DEBUGOBJDIR)/Event.obj: .././Core/IO/Event.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Event.obj .././Core/IO/Event.cc

$(OPTOBJDIR)/EventSet.obj: .././Core/IO/EventSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EventSet.obj .././Core/IO/EventSet.cc

$(DEBUGOBJDIR)/EventSet.obj: .././Core/IO/EventSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EventSet.obj .././Core/IO/EventSet.cc

$(OPTOBJDIR)/Plug.obj: .././Core/IO/Plug.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Plug.obj .././Core/IO/Plug.cc

$(DEBUGOBJDIR)/Plug.obj: .././Core/IO/Plug.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Plug.obj .././Core/IO/Plug.cc

$(OPTOBJDIR)/StreamOp.obj: .././Core/IO/StreamOp.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StreamOp.obj .././Core/IO/StreamOp.cc

$(DEBUGOBJDIR)/StreamOp.obj: .././Core/IO/StreamOp.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StreamOp.obj .././Core/IO/StreamOp.cc

$(OPTOBJDIR)/StreamProcess.obj: .././Core/IO/StreamProcess.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/StreamProcess.obj .././Core/IO/StreamProcess.cc

$(DEBUGOBJDIR)/StreamProcess.obj: .././Core/IO/StreamProcess.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/StreamProcess.obj .././Core/IO/StreamProcess.cc

$(OPTOBJDIR)/IOConnect.obj: .././Core/IO/IOConnect.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/IOConnect.obj .././Core/IO/IOConnect.cc

$(DEBUGOBJDIR)/IOConnect.obj: .././Core/IO/IOConnect.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/IOConnect.obj .././Core/IO/IOConnect.cc

$(OPTOBJDIR)/FileFormatXMLStream.obj: .././Core/IO/FileFormatXMLStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FileFormatXMLStream.obj .././Core/IO/FileFormatXMLStream.cc

$(DEBUGOBJDIR)/FileFormatXMLStream.obj: .././Core/IO/FileFormatXMLStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FileFormatXMLStream.obj .././Core/IO/FileFormatXMLStream.cc

$(OPTOBJDIR)/DataConv.obj: .././Core/IO/DataConv.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DataConv.obj .././Core/IO/DataConv.cc

$(DEBUGOBJDIR)/DataConv.obj: .././Core/IO/DataConv.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DataConv.obj .././Core/IO/DataConv.cc

$(OPTOBJDIR)/AttributeCtrl.obj: .././Core/IO/AttributeCtrl.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AttributeCtrl.obj .././Core/IO/AttributeCtrl.cc

$(DEBUGOBJDIR)/AttributeCtrl.obj: .././Core/IO/AttributeCtrl.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AttributeCtrl.obj .././Core/IO/AttributeCtrl.cc

$(OPTOBJDIR)/AttributeType.obj: .././Core/IO/AttributeType.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AttributeType.obj .././Core/IO/AttributeType.cc

$(DEBUGOBJDIR)/AttributeType.obj: .././Core/IO/AttributeType.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AttributeType.obj .././Core/IO/AttributeType.cc

$(OPTOBJDIR)/AttributeValueTypes.obj: .././Core/IO/AttributeValueTypes.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AttributeValueTypes.obj .././Core/IO/AttributeValueTypes.cc

$(DEBUGOBJDIR)/AttributeValueTypes.obj: .././Core/IO/AttributeValueTypes.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AttributeValueTypes.obj .././Core/IO/AttributeValueTypes.cc

$(OPTOBJDIR)/AttributeCtrlXML.obj: .././Core/IO/AttributeCtrlXML.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AttributeCtrlXML.obj .././Core/IO/AttributeCtrlXML.cc

$(DEBUGOBJDIR)/AttributeCtrlXML.obj: .././Core/IO/AttributeCtrlXML.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AttributeCtrlXML.obj .././Core/IO/AttributeCtrlXML.cc

$(OPTOBJDIR)/AttributeSet.obj: .././Core/IO/AttributeSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AttributeSet.obj .././Core/IO/AttributeSet.cc

$(DEBUGOBJDIR)/AttributeSet.obj: .././Core/IO/AttributeSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AttributeSet.obj .././Core/IO/AttributeSet.cc

$(OPTOBJDIR)/ByteFileIO.obj: .././Core/IO/ByteFileIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ByteFileIO.obj .././Core/IO/ByteFileIO.cc

$(DEBUGOBJDIR)/ByteFileIO.obj: .././Core/IO/ByteFileIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ByteFileIO.obj .././Core/IO/ByteFileIO.cc

$(OPTOBJDIR)/ByteStream.obj: .././Core/IO/ByteStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ByteStream.obj .././Core/IO/ByteStream.cc

$(DEBUGOBJDIR)/ByteStream.obj: .././Core/IO/ByteStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ByteStream.obj .././Core/IO/ByteStream.cc

$(OPTOBJDIR)/SByteStream.obj: .././Core/IO/SByteStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SByteStream.obj .././Core/IO/SByteStream.cc

$(DEBUGOBJDIR)/SByteStream.obj: .././Core/IO/SByteStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SByteStream.obj .././Core/IO/SByteStream.cc

$(OPTOBJDIR)/AttributeCtrlInternal.obj: .././Core/IO/AttributeCtrlInternal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AttributeCtrlInternal.obj .././Core/IO/AttributeCtrlInternal.cc

$(DEBUGOBJDIR)/AttributeCtrlInternal.obj: .././Core/IO/AttributeCtrlInternal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AttributeCtrlInternal.obj .././Core/IO/AttributeCtrlInternal.cc

$(OPTOBJDIR)/AttributeCtrlUpdateSignal.obj: .././Core/IO/AttributeCtrlUpdateSignal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AttributeCtrlUpdateSignal.obj .././Core/IO/AttributeCtrlUpdateSignal.cc

$(DEBUGOBJDIR)/AttributeCtrlUpdateSignal.obj: .././Core/IO/AttributeCtrlUpdateSignal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AttributeCtrlUpdateSignal.obj .././Core/IO/AttributeCtrlUpdateSignal.cc

$(OPTOBJDIR)/PrintIOInfo.obj: .././Core/IO/PrintIOInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PrintIOInfo.obj .././Core/IO/PrintIOInfo.cc

$(DEBUGOBJDIR)/PrintIOInfo.obj: .././Core/IO/PrintIOInfo.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PrintIOInfo.obj .././Core/IO/PrintIOInfo.cc

$(OPTOBJDIR)/CoreIO.obj: .././Core/IO/CoreIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CoreIO.obj .././Core/IO/CoreIO.cc

$(DEBUGOBJDIR)/CoreIO.obj: .././Core/IO/CoreIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CoreIO.obj .././Core/IO/CoreIO.cc


