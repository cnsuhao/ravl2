# Microsoft Developer Studio Project File - Name="$(PROJECT_NAME)" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 5.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Console Application" 0x0103

CFG=kieron - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "$(PROJECT_NAME).mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "$(PROJECT_NAME).mak" CFG="$(PROJECT_NAME) - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "$(PROJECT_NAME) - Win32 Release" (based on "Win32 (x86) Console Application")
!MESSAGE "$(PROJECT_NAME) - Win32 Debug" (based on "Win32 (x86) Console Application")
!MESSAGE 
# Begin Project
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe

RSC=rc.exe

!IF  "$$(CFG)" == "$(PROJECT_NAME) - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "$(TEMP_DIR)/Release"
# PROP BASE Intermediate_Dir "$(TEMP_DIR)/Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "$(TEMP_DIR)/Release"
# PROP Intermediate_Dir "$(TEMP_DIR)/Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GR /GX /O2 /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "$(VCPP_SRC_ROOT)/inc" /D "WIN32" /D "NDEBUG" /D "_CONSOLE" /D "_MBCS" /D "VISUAL_CPP" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE RSC /l 0x409 /d "NDEBUG"
# ADD RSC /l 0x409 /d "NDEBUG"
LIB32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /machine:I386

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
# ADD BASE CPP /nologo /W3 /GR /GX /Z7 /Od /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /GR /GX /Z7 /Od  /I "$(VCPP_SRC_ROOT)/inc" /D "WIN32" /D "_DEBUG" /D "_CONSOLE" /D "_MBCS" /D "VISUAL_CPP" /YX /FD /c
BSC32=bscmake.exe
# ADD BASE RSC /l 0x409 /d "_DEBUG"
# ADD RSC /l 0x409 /d "_DEBUG"
LIB32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:console /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "$(PROJECT_NAME) - Win32 Release"
# Name "$(PROJECT_NAME) - Win32 Debug"
$(ALL_THE_SRC_FILES)
# End Target
# End Project
