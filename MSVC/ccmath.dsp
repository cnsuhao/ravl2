# Microsoft Developer Studio Project File - Name="ccmath" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ccmath - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ccmath.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ccmath.mak" CFG="ccmath - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ccmath - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ccmath - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ccmath - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\ccmath"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ccmath - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\ccmath"
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

# Name "ccmath - Win32 Release"
# Name "ccmath - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\CCMath\matrix\atou1.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\atovm.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\chouse.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\chousv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\cmattr.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\cmcpy.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\cminv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\cmmul.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\cmmult.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\cmprt.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\csolv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\cvmul.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\eigen.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\eigval.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\evmax.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\hconj.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\heigval.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\heigvec.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\hevmax.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\hmgen.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\house.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\housev.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\ldumat.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\ldvmat.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\matprt.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\mattr.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\mcopy.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\minv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\mmul.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\ortho.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\otrma.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\otrsm.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\psinv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\qrbdi.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\qrbdu1.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\qrbdv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\qrecvc.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\qreval.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\qrevec.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\rmmult.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\ruinv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\smgen.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\solvps.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\solvru.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\solvtd.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\sv2u1v.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\sv2uv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\sv2val.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\svdu1v.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\svduv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\svdval.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\trncm.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\trnm.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\unitary.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\utrncm.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\utrnhm.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\vmul.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\unfl.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\lrand.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\lrana.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\matrix\solv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\fft\fft2.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\fft\fft2_d.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\fft\fftgc.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\fft\fftgr.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\fft\ftuns.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\fft\pfac.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\fft\pshuf.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\fft\pwspec.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\fft\smoo.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\chcof.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\csfit.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\csplp.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\evpsq.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\fitval.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\gnlsq.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\plsq.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\psqcf.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\qrbdbv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\qrvar.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\sv2lsq.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\tnsfit.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\chpade.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\cspl.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\dcspl.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\evpsqv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\ftch.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\lsqsv.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\pplsq.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\psqvar.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\qrlsq.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\seqlsq.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\svdlsq.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\statf\gaml.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\statf\pctb.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\statf\pctbn.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\statf\pctg.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\statf\pctgn.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\statf\pctn.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\statf\qbeta.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\statf\qbnc.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\statf\qgama.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\statf\qgnc.c
# End Source File

# Begin Source File
SOURCE=..\.\CCMath\statf\qnorm.c
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\CCMath\ccmath.h

!IF  "$(CFG)" == "ccmath - Win32 Release"

# Begin Custom Build - Install Header ccmath.h

"C:\Build\inc\ccmath\ccmath.h" :  "" ""
	copy ..\.\CCMath\ccmath.h C:\Build\inc\ccmath

# End Custom Build

!ELSEIF  "$(CFG)" == "ccmath - Win32 Debug"

# Begin Custom Build - Install Header ccmath.h

"C:\Build\inc\ccmath\ccmath.h" :  "" ""
	copy ..\.\CCMath\ccmath.h C:\Build\inc\ccmath

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\CCMath\cfit\orpol.h

!IF  "$(CFG)" == "ccmath - Win32 Release"

# Begin Custom Build - Install Header orpol.h

"C:\Build\inc\ccmath\orpol.h" :  "" ""
	copy ..\.\CCMath\cfit\orpol.h C:\Build\inc\ccmath

# End Custom Build

!ELSEIF  "$(CFG)" == "ccmath - Win32 Debug"

# Begin Custom Build - Install Header orpol.h

"C:\Build\inc\ccmath\orpol.h" :  "" ""
	copy ..\.\CCMath\cfit\orpol.h C:\Build\inc\ccmath

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
