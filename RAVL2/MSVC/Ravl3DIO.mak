


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/Ravl3DIO
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/Ravl3DIO
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setupRavl3DIO  $(OPTOBJDIR)/VRMLFileIO.obj $(OPTOBJDIR)/FormatVRMLFile.obj $(OPTOBJDIR)/CTriFileIO.obj $(OPTOBJDIR)/FormatCTriFile.obj $(OPTOBJDIR)/TriFileIO.obj $(OPTOBJDIR)/FormatTriFile.obj $(OPTOBJDIR)/MeshIOObj.obj $(OPTOBJDIR)/FormatMeshObj.obj $(OPTOBJDIR)/TriMeshIO.obj $(OPTOBJDIR)/TexTriMeshIO.obj $(OPTOBJDIR)/POVRayFileIO.obj $(OPTOBJDIR)/FormatPOVRayFile.obj $(OPTOBJDIR)/MeshConv.obj $(OPTOBJDIR)/RavlMeshIO.obj
	@echo -- making $(OPTLIBDIR)/Ravl3DIO.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/Ravl3DIO.lib $(OPTOBJDIR)/*.obj


debug:: setupRavl3DIO  $(DEBUGOBJDIR)/VRMLFileIO.obj $(DEBUGOBJDIR)/FormatVRMLFile.obj $(DEBUGOBJDIR)/CTriFileIO.obj $(DEBUGOBJDIR)/FormatCTriFile.obj $(DEBUGOBJDIR)/TriFileIO.obj $(DEBUGOBJDIR)/FormatTriFile.obj $(DEBUGOBJDIR)/MeshIOObj.obj $(DEBUGOBJDIR)/FormatMeshObj.obj $(DEBUGOBJDIR)/TriMeshIO.obj $(DEBUGOBJDIR)/TexTriMeshIO.obj $(DEBUGOBJDIR)/POVRayFileIO.obj $(DEBUGOBJDIR)/FormatPOVRayFile.obj $(DEBUGOBJDIR)/MeshConv.obj $(DEBUGOBJDIR)/RavlMeshIO.obj 
	@echo -- making $(DEBUGLIBDIR)/Ravl3DIO.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/Ravl3DIO.lib $(DEBUGOBJDIR)/*.obj

setupRavl3DIO::
        echo --- creating dir for Ravl3DIO
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/VRMLFileIO.obj: .././3D/MeshIO/VRMLFileIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/VRMLFileIO.obj .././3D/MeshIO/VRMLFileIO.cc

$(DEBUGOBJDIR)/VRMLFileIO.obj: .././3D/MeshIO/VRMLFileIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/VRMLFileIO.obj .././3D/MeshIO/VRMLFileIO.cc

$(OPTOBJDIR)/FormatVRMLFile.obj: .././3D/MeshIO/FormatVRMLFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FormatVRMLFile.obj .././3D/MeshIO/FormatVRMLFile.cc

$(DEBUGOBJDIR)/FormatVRMLFile.obj: .././3D/MeshIO/FormatVRMLFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FormatVRMLFile.obj .././3D/MeshIO/FormatVRMLFile.cc

$(OPTOBJDIR)/CTriFileIO.obj: .././3D/MeshIO/CTriFileIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CTriFileIO.obj .././3D/MeshIO/CTriFileIO.cc

$(DEBUGOBJDIR)/CTriFileIO.obj: .././3D/MeshIO/CTriFileIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CTriFileIO.obj .././3D/MeshIO/CTriFileIO.cc

$(OPTOBJDIR)/FormatCTriFile.obj: .././3D/MeshIO/FormatCTriFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FormatCTriFile.obj .././3D/MeshIO/FormatCTriFile.cc

$(DEBUGOBJDIR)/FormatCTriFile.obj: .././3D/MeshIO/FormatCTriFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FormatCTriFile.obj .././3D/MeshIO/FormatCTriFile.cc

$(OPTOBJDIR)/TriFileIO.obj: .././3D/MeshIO/TriFileIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TriFileIO.obj .././3D/MeshIO/TriFileIO.cc

$(DEBUGOBJDIR)/TriFileIO.obj: .././3D/MeshIO/TriFileIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TriFileIO.obj .././3D/MeshIO/TriFileIO.cc

$(OPTOBJDIR)/FormatTriFile.obj: .././3D/MeshIO/FormatTriFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FormatTriFile.obj .././3D/MeshIO/FormatTriFile.cc

$(DEBUGOBJDIR)/FormatTriFile.obj: .././3D/MeshIO/FormatTriFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FormatTriFile.obj .././3D/MeshIO/FormatTriFile.cc

$(OPTOBJDIR)/MeshIOObj.obj: .././3D/MeshIO/MeshIOObj.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MeshIOObj.obj .././3D/MeshIO/MeshIOObj.cc

$(DEBUGOBJDIR)/MeshIOObj.obj: .././3D/MeshIO/MeshIOObj.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MeshIOObj.obj .././3D/MeshIO/MeshIOObj.cc

$(OPTOBJDIR)/FormatMeshObj.obj: .././3D/MeshIO/FormatMeshObj.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FormatMeshObj.obj .././3D/MeshIO/FormatMeshObj.cc

$(DEBUGOBJDIR)/FormatMeshObj.obj: .././3D/MeshIO/FormatMeshObj.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FormatMeshObj.obj .././3D/MeshIO/FormatMeshObj.cc

$(OPTOBJDIR)/TriMeshIO.obj: .././3D/MeshIO/TriMeshIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TriMeshIO.obj .././3D/MeshIO/TriMeshIO.cc

$(DEBUGOBJDIR)/TriMeshIO.obj: .././3D/MeshIO/TriMeshIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TriMeshIO.obj .././3D/MeshIO/TriMeshIO.cc

$(OPTOBJDIR)/TexTriMeshIO.obj: .././3D/MeshIO/TexTriMeshIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TexTriMeshIO.obj .././3D/MeshIO/TexTriMeshIO.cc

$(DEBUGOBJDIR)/TexTriMeshIO.obj: .././3D/MeshIO/TexTriMeshIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TexTriMeshIO.obj .././3D/MeshIO/TexTriMeshIO.cc

$(OPTOBJDIR)/POVRayFileIO.obj: .././3D/MeshIO/POVRayFileIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/POVRayFileIO.obj .././3D/MeshIO/POVRayFileIO.cc

$(DEBUGOBJDIR)/POVRayFileIO.obj: .././3D/MeshIO/POVRayFileIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/POVRayFileIO.obj .././3D/MeshIO/POVRayFileIO.cc

$(OPTOBJDIR)/FormatPOVRayFile.obj: .././3D/MeshIO/FormatPOVRayFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FormatPOVRayFile.obj .././3D/MeshIO/FormatPOVRayFile.cc

$(DEBUGOBJDIR)/FormatPOVRayFile.obj: .././3D/MeshIO/FormatPOVRayFile.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FormatPOVRayFile.obj .././3D/MeshIO/FormatPOVRayFile.cc

$(OPTOBJDIR)/MeshConv.obj: .././3D/MeshIO/MeshConv.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MeshConv.obj .././3D/MeshIO/MeshConv.cc

$(DEBUGOBJDIR)/MeshConv.obj: .././3D/MeshIO/MeshConv.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MeshConv.obj .././3D/MeshIO/MeshConv.cc

$(OPTOBJDIR)/RavlMeshIO.obj: .././3D/MeshIO/RavlMeshIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RavlMeshIO.obj .././3D/MeshIO/RavlMeshIO.cc

$(DEBUGOBJDIR)/RavlMeshIO.obj: .././3D/MeshIO/RavlMeshIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RavlMeshIO.obj .././3D/MeshIO/RavlMeshIO.cc


