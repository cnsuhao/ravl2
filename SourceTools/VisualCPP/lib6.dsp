# Microsoft Developer Studio Project File - Name="$(PROJECT_NAME)" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=$(PROJECT_NAME) - Win32 Release
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "$(PROJECT_NAME).mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "$(PROJECT_NAME).mak" CFG="$(PROJECT_NAME) - Win32 Release"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "$(PROJECT_NAME) - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "$(PROJECT_NAME) - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$$(CFG)" == "$(PROJECT_NAME) - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "d:/temp/Release"
# PROP BASE Intermediate_Dir "d:/temp/Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "$(TEMP_DIR)/Release"
# PROP Intermediate_Dir "$(TEMP_DIR)/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "$(VCPP_SRC_ROOT)/inc" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "VISUAL_CPP" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"$(VCPP_SRC_ROOT)/lib/opt/$(PROJECT_NAME).lib"

!ELSEIF  "$$(CFG)" == "$(PROJECT_NAME) - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "$(TEMP_DIR)/Debug"
# PROP BASE Intermediate_Dir "$(TEMP_DIR)/Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "$(TEMP_DIR)/Debug"
# PROP Intermediate_Dir "$(TEMP_DIR)/Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GR /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /GR /GX /Z7 /Od /I "$(VCPP_SRC_ROOT)/inc" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "VISUAL_CPP" /D "AMMA_CHECK" /YX /FD /c
# ADD BASE RSC /l 0x409
# ADD RSC /l 0x409
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"$(VCPP_SRC_ROOT)/lib/debug/$(PROJECT_NAME).lib"

!ENDIF 

# Begin Target

# Name "$(PROJECT_NAME) - Win32 Release"
# Name "$(PROJECT_NAME) - Win32 Debug"
$(ALL_THE_SRC_FILES)
# End Target
# End Project
