# Microsoft Developer Studio Project File - Name="RavlImageProc" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlImageProc - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlImageProc.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlImageProc.mak" CFG="RavlImageProc - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlImageProc - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlImageProc - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlImageProc"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlImageProc"
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

# Name "RavlImageProc - Win32 Release"
# Name "RavlImageProc - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Image\Processing\Tools\Rectangle2dIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\SobolImage.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\PyramidScan.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\ImagePointFeatureSet.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\ImagePointFeature.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\HomomorphicFilter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\Correlate2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\Matching.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\WarpThinPlateSpline.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\GaborFilter2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\DCT2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\DeinterlaceStream.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\WarpMesh2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\EdgeSobel.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\EdgeDeriche.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\SqrComposition.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\EdgeNonMaxSuppression.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\Edgel.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\EdgeLink.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\EdgeDetector.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\EdgeIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\ChromaThreshold.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\Segmentation.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\ConnectedComponents.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\BlueScreen.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\SegmentExtrema.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\PixelSelectStack.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\PixelMap.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\PixelMapSearch.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\PCPixel.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\PCPixelList.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\PCMapping.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\PPHT.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\ArcDetector.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Corners\Corner.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Corners\CornerDetector.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Corners\CornerDetectorHarris.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Corners\CornerDetectorSusan.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Motion\LMSGradient\LMSOpticFlow.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Motion\LMSGradient\LMSMultiScaleMotion.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Motion\LMSGradient\LMSRegionMotion.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\PointTrack.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\PointTrackModel.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\PointTracker.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\MosaicBuilder.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\ImageTracker.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\ImageMatcher.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\MatchNormalisedCorrelation.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\ForegroundSep.cc
# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\TrackingHomog.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Image\Processing\Tools\Rectangle2dIter.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header Rectangle2dIter.hh

"C:\Build\inc\Ravl\Image\Rectangle2dIter.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\Rectangle2dIter.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header Rectangle2dIter.hh

"C:\Build\inc\Ravl\Image\Rectangle2dIter.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\Rectangle2dIter.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\SobolImage.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header SobolImage.hh

"C:\Build\inc\Ravl\Image\SobolImage.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\SobolImage.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header SobolImage.hh

"C:\Build\inc\Ravl\Image\SobolImage.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\SobolImage.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\SubSample.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header SubSample.hh

"C:\Build\inc\Ravl\Image\SubSample.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\SubSample.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header SubSample.hh

"C:\Build\inc\Ravl\Image\SubSample.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\SubSample.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\SummedAreaTable.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header SummedAreaTable.hh

"C:\Build\inc\Ravl\Image\SummedAreaTable.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\SummedAreaTable.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header SummedAreaTable.hh

"C:\Build\inc\Ravl\Image\SummedAreaTable.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\SummedAreaTable.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\SummedAreaTable2.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header SummedAreaTable2.hh

"C:\Build\inc\Ravl\Image\SummedAreaTable2.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\SummedAreaTable2.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header SummedAreaTable2.hh

"C:\Build\inc\Ravl\Image\SummedAreaTable2.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\SummedAreaTable2.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\PyramidScan.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PyramidScan.hh

"C:\Build\inc\Ravl\Image\PyramidScan.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\PyramidScan.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PyramidScan.hh

"C:\Build\inc\Ravl\Image\PyramidScan.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\PyramidScan.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\PeakDetector.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PeakDetector.hh

"C:\Build\inc\Ravl\Image\PeakDetector.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\PeakDetector.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PeakDetector.hh

"C:\Build\inc\Ravl\Image\PeakDetector.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\PeakDetector.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\ImagePointFeatureSet.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ImagePointFeatureSet.hh

"C:\Build\inc\Ravl\Image\ImagePointFeatureSet.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\ImagePointFeatureSet.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ImagePointFeatureSet.hh

"C:\Build\inc\Ravl\Image\ImagePointFeatureSet.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\ImagePointFeatureSet.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\ImagePointFeature.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ImagePointFeature.hh

"C:\Build\inc\Ravl\Image\ImagePointFeature.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\ImagePointFeature.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ImagePointFeature.hh

"C:\Build\inc\Ravl\Image\ImagePointFeature.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\ImagePointFeature.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tools\TakeSubImage.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header TakeSubImage.hh

"C:\Build\inc\Ravl\Image\TakeSubImage.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\TakeSubImage.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header TakeSubImage.hh

"C:\Build\inc\Ravl\Image\TakeSubImage.hh" :  "" ""
	copy ..\.\Image\Processing\Tools\TakeSubImage.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\Convolve2d.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header Convolve2d.hh

"C:\Build\inc\Ravl\Image\Convolve2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\Convolve2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header Convolve2d.hh

"C:\Build\inc\Ravl\Image\Convolve2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\Convolve2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\ConvolveSeparable2d.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ConvolveSeparable2d.hh

"C:\Build\inc\Ravl\Image\ConvolveSeparable2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\ConvolveSeparable2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ConvolveSeparable2d.hh

"C:\Build\inc\Ravl\Image\ConvolveSeparable2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\ConvolveSeparable2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\ConvolveHorz2d.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ConvolveHorz2d.hh

"C:\Build\inc\Ravl\Image\ConvolveHorz2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\ConvolveHorz2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ConvolveHorz2d.hh

"C:\Build\inc\Ravl\Image\ConvolveHorz2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\ConvolveHorz2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\ConvolveVert2d.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ConvolveVert2d.hh

"C:\Build\inc\Ravl\Image\ConvolveVert2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\ConvolveVert2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ConvolveVert2d.hh

"C:\Build\inc\Ravl\Image\ConvolveVert2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\ConvolveVert2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\GaussConvolve2d.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header GaussConvolve2d.hh

"C:\Build\inc\Ravl\Image\GaussConvolve2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\GaussConvolve2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header GaussConvolve2d.hh

"C:\Build\inc\Ravl\Image\GaussConvolve2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\GaussConvolve2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\GaussConvolve.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header GaussConvolve.hh

"C:\Build\inc\Ravl\Image\GaussConvolve.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\GaussConvolve.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header GaussConvolve.hh

"C:\Build\inc\Ravl\Image\GaussConvolve.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\GaussConvolve.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\Averaging2d.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header Averaging2d.hh

"C:\Build\inc\Ravl\Image\Averaging2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\Averaging2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header Averaging2d.hh

"C:\Build\inc\Ravl\Image\Averaging2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\Averaging2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\Correlate2d.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header Correlate2d.hh

"C:\Build\inc\Ravl\Image\Correlate2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\Correlate2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header Correlate2d.hh

"C:\Build\inc\Ravl\Image\Correlate2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\Correlate2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\NormalisedCorrelation.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header NormalisedCorrelation.hh

"C:\Build\inc\Ravl\Image\NormalisedCorrelation.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\NormalisedCorrelation.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header NormalisedCorrelation.hh

"C:\Build\inc\Ravl\Image\NormalisedCorrelation.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\NormalisedCorrelation.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\GaborFilter2d.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header GaborFilter2d.hh

"C:\Build\inc\Ravl\Image\GaborFilter2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\GaborFilter2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header GaborFilter2d.hh

"C:\Build\inc\Ravl\Image\GaborFilter2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\GaborFilter2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\GabourFilter2d.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header GabourFilter2d.hh

"C:\Build\inc\Ravl\Image\GabourFilter2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\GabourFilter2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header GabourFilter2d.hh

"C:\Build\inc\Ravl\Image\GabourFilter2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\GabourFilter2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\HomomorphicFilter.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header HomomorphicFilter.hh

"C:\Build\inc\Ravl\Image\HomomorphicFilter.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\HomomorphicFilter.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header HomomorphicFilter.hh

"C:\Build\inc\Ravl\Image\HomomorphicFilter.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\HomomorphicFilter.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\HistogramEqualise.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header HistogramEqualise.hh

"C:\Build\inc\Ravl\Image\HistogramEqualise.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\HistogramEqualise.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header HistogramEqualise.hh

"C:\Build\inc\Ravl\Image\HistogramEqualise.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\HistogramEqualise.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\Matching.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header Matching.hh

"C:\Build\inc\Ravl\Image\Matching.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\Matching.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header Matching.hh

"C:\Build\inc\Ravl\Image\Matching.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\Matching.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\WarpScale.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header WarpScale.hh

"C:\Build\inc\Ravl\Image\WarpScale.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\WarpScale.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header WarpScale.hh

"C:\Build\inc\Ravl\Image\WarpScale.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\WarpScale.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\WarpAffine.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header WarpAffine.hh

"C:\Build\inc\Ravl\Image\WarpAffine.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\WarpAffine.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header WarpAffine.hh

"C:\Build\inc\Ravl\Image\WarpAffine.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\WarpAffine.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\WarpProjective.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header WarpProjective.hh

"C:\Build\inc\Ravl\Image\WarpProjective.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\WarpProjective.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header WarpProjective.hh

"C:\Build\inc\Ravl\Image\WarpProjective.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\WarpProjective.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\PixelMixer.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PixelMixer.hh

"C:\Build\inc\Ravl\Image\PixelMixer.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\PixelMixer.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PixelMixer.hh

"C:\Build\inc\Ravl\Image\PixelMixer.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\PixelMixer.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\RemoveDistortion.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header RemoveDistortion.hh

"C:\Build\inc\Ravl\Image\RemoveDistortion.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\RemoveDistortion.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header RemoveDistortion.hh

"C:\Build\inc\Ravl\Image\RemoveDistortion.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\RemoveDistortion.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\WarpThinPlateSpline.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header WarpThinPlateSpline.hh

"C:\Build\inc\Ravl\Image\WarpThinPlateSpline.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\WarpThinPlateSpline.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header WarpThinPlateSpline.hh

"C:\Build\inc\Ravl\Image\WarpThinPlateSpline.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\WarpThinPlateSpline.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\SpatialDifference.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header SpatialDifference.hh

"C:\Build\inc\Ravl\Image\SpatialDifference.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\SpatialDifference.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header SpatialDifference.hh

"C:\Build\inc\Ravl\Image\SpatialDifference.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\SpatialDifference.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\SumRectangles.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header SumRectangles.hh

"C:\Build\inc\Ravl\Image\SumRectangles.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\SumRectangles.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header SumRectangles.hh

"C:\Build\inc\Ravl\Image\SumRectangles.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\SumRectangles.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\DeinterlaceStream.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header DeinterlaceStream.hh

"C:\Build\inc\Ravl\Image\DeinterlaceStream.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\DeinterlaceStream.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header DeinterlaceStream.hh

"C:\Build\inc\Ravl\Image\DeinterlaceStream.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\DeinterlaceStream.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\DCT2d.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header DCT2d.hh

"C:\Build\inc\Ravl\Image\DCT2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\DCT2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header DCT2d.hh

"C:\Build\inc\Ravl\Image\DCT2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\DCT2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\ImageExtend.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ImageExtend.hh

"C:\Build\inc\Ravl\Image\ImageExtend.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\ImageExtend.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ImageExtend.hh

"C:\Build\inc\Ravl\Image\ImageExtend.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\ImageExtend.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\ImagePyramid.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ImagePyramid.hh

"C:\Build\inc\Ravl\Image\ImagePyramid.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\ImagePyramid.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ImagePyramid.hh

"C:\Build\inc\Ravl\Image\ImagePyramid.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\ImagePyramid.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Filters\WarpMesh2d.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header WarpMesh2d.hh

"C:\Build\inc\Ravl\Image\WarpMesh2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\WarpMesh2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header WarpMesh2d.hh

"C:\Build\inc\Ravl\Image\WarpMesh2d.hh" :  "" ""
	copy ..\.\Image\Processing\Filters\WarpMesh2d.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\EdgeSobel.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header EdgeSobel.hh

"C:\Build\inc\Ravl\Image\EdgeSobel.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\EdgeSobel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header EdgeSobel.hh

"C:\Build\inc\Ravl\Image\EdgeSobel.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\EdgeSobel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\EdgeDeriche.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header EdgeDeriche.hh

"C:\Build\inc\Ravl\Image\EdgeDeriche.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\EdgeDeriche.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header EdgeDeriche.hh

"C:\Build\inc\Ravl\Image\EdgeDeriche.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\EdgeDeriche.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\SqrComposition.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header SqrComposition.hh

"C:\Build\inc\Ravl\Image\SqrComposition.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\SqrComposition.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header SqrComposition.hh

"C:\Build\inc\Ravl\Image\SqrComposition.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\SqrComposition.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\EdgeNonMaxSuppression.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header EdgeNonMaxSuppression.hh

"C:\Build\inc\Ravl\Image\EdgeNonMaxSuppression.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\EdgeNonMaxSuppression.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header EdgeNonMaxSuppression.hh

"C:\Build\inc\Ravl\Image\EdgeNonMaxSuppression.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\EdgeNonMaxSuppression.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\Edgel.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header Edgel.hh

"C:\Build\inc\Ravl\Image\Edgel.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\Edgel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header Edgel.hh

"C:\Build\inc\Ravl\Image\Edgel.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\Edgel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\EdgeLink.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header EdgeLink.hh

"C:\Build\inc\Ravl\Image\EdgeLink.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\EdgeLink.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header EdgeLink.hh

"C:\Build\inc\Ravl\Image\EdgeLink.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\EdgeLink.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\EdgeDetector.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header EdgeDetector.hh

"C:\Build\inc\Ravl\Image\EdgeDetector.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\EdgeDetector.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header EdgeDetector.hh

"C:\Build\inc\Ravl\Image\EdgeDetector.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\EdgeDetector.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Edges\Gradient.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header Gradient.hh

"C:\Build\inc\Ravl\Image\Gradient.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\Gradient.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header Gradient.hh

"C:\Build\inc\Ravl\Image\Gradient.hh" :  "" ""
	copy ..\.\Image\Processing\Edges\Gradient.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\Segmentation.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header Segmentation.hh

"C:\Build\inc\Ravl\Image\Segmentation.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\Segmentation.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header Segmentation.hh

"C:\Build\inc\Ravl\Image\Segmentation.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\Segmentation.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\RegionSet.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header RegionSet.hh

"C:\Build\inc\Ravl\Image\RegionSet.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\RegionSet.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header RegionSet.hh

"C:\Build\inc\Ravl\Image\RegionSet.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\RegionSet.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\ConnectedComponents.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ConnectedComponents.hh

"C:\Build\inc\Ravl\Image\ConnectedComponents.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\ConnectedComponents.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ConnectedComponents.hh

"C:\Build\inc\Ravl\Image\ConnectedComponents.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\ConnectedComponents.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\ChromaThreshold.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ChromaThreshold.hh

"C:\Build\inc\Ravl\Image\ChromaThreshold.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\ChromaThreshold.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ChromaThreshold.hh

"C:\Build\inc\Ravl\Image\ChromaThreshold.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\ChromaThreshold.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\BlueScreen.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header BlueScreen.hh

"C:\Build\inc\Ravl\Image\BlueScreen.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\BlueScreen.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header BlueScreen.hh

"C:\Build\inc\Ravl\Image\BlueScreen.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\BlueScreen.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\SegmentExtrema.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header SegmentExtrema.hh

"C:\Build\inc\Ravl\Image\SegmentExtrema.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\SegmentExtrema.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header SegmentExtrema.hh

"C:\Build\inc\Ravl\Image\SegmentExtrema.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\SegmentExtrema.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\FloodRegion.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header FloodRegion.hh

"C:\Build\inc\Ravl\Image\FloodRegion.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\FloodRegion.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header FloodRegion.hh

"C:\Build\inc\Ravl\Image\FloodRegion.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\FloodRegion.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\SegmentRegion.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header SegmentRegion.hh

"C:\Build\inc\Ravl\Image\SegmentRegion.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\SegmentRegion.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header SegmentRegion.hh

"C:\Build\inc\Ravl\Image\SegmentRegion.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\SegmentRegion.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\RegionGrow.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header RegionGrow.hh

"C:\Build\inc\Ravl\Image\RegionGrow.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\RegionGrow.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header RegionGrow.hh

"C:\Build\inc\Ravl\Image\RegionGrow.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\RegionGrow.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\RegionGrowSteal.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header RegionGrowSteal.hh

"C:\Build\inc\Ravl\Image\RegionGrowSteal.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\RegionGrowSteal.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header RegionGrowSteal.hh

"C:\Build\inc\Ravl\Image\RegionGrowSteal.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\RegionGrowSteal.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\PixelSelectStack.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PixelSelectStack.hh

"C:\Build\inc\Ravl\Image\PixelSelectStack.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\PixelSelectStack.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PixelSelectStack.hh

"C:\Build\inc\Ravl\Image\PixelSelectStack.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\PixelSelectStack.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\PixelClassifyGrey.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PixelClassifyGrey.hh

"C:\Build\inc\Ravl\Image\PixelClassifyGrey.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\PixelClassifyGrey.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PixelClassifyGrey.hh

"C:\Build\inc\Ravl\Image\PixelClassifyGrey.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\PixelClassifyGrey.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\PixelClassifyColour.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PixelClassifyColour.hh

"C:\Build\inc\Ravl\Image\PixelClassifyColour.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\PixelClassifyColour.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PixelClassifyColour.hh

"C:\Build\inc\Ravl\Image\PixelClassifyColour.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\PixelClassifyColour.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Segmentation\PixelClassifyMotion.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PixelClassifyMotion.hh

"C:\Build\inc\Ravl\Image\PixelClassifyMotion.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\PixelClassifyMotion.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PixelClassifyMotion.hh

"C:\Build\inc\Ravl\Image\PixelClassifyMotion.hh" :  "" ""
	copy ..\.\Image\Processing\Segmentation\PixelClassifyMotion.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Morphology\Erode.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header Erode.hh

"C:\Build\inc\Ravl\Image\Erode.hh" :  "" ""
	copy ..\.\Image\Processing\Morphology\Erode.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header Erode.hh

"C:\Build\inc\Ravl\Image\Erode.hh" :  "" ""
	copy ..\.\Image\Processing\Morphology\Erode.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Morphology\Dilate.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header Dilate.hh

"C:\Build\inc\Ravl\Image\Dilate.hh" :  "" ""
	copy ..\.\Image\Processing\Morphology\Dilate.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header Dilate.hh

"C:\Build\inc\Ravl\Image\Dilate.hh" :  "" ""
	copy ..\.\Image\Processing\Morphology\Dilate.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Morphology\DilateSubSample2X.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header DilateSubSample2X.hh

"C:\Build\inc\Ravl\Image\DilateSubSample2X.hh" :  "" ""
	copy ..\.\Image\Processing\Morphology\DilateSubSample2X.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header DilateSubSample2X.hh

"C:\Build\inc\Ravl\Image\DilateSubSample2X.hh" :  "" ""
	copy ..\.\Image\Processing\Morphology\DilateSubSample2X.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Morphology\MorphOpen.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header MorphOpen.hh

"C:\Build\inc\Ravl\Image\MorphOpen.hh" :  "" ""
	copy ..\.\Image\Processing\Morphology\MorphOpen.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header MorphOpen.hh

"C:\Build\inc\Ravl\Image\MorphOpen.hh" :  "" ""
	copy ..\.\Image\Processing\Morphology\MorphOpen.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Morphology\MorphClose.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header MorphClose.hh

"C:\Build\inc\Ravl\Image\MorphClose.hh" :  "" ""
	copy ..\.\Image\Processing\Morphology\MorphClose.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header MorphClose.hh

"C:\Build\inc\Ravl\Image\MorphClose.hh" :  "" ""
	copy ..\.\Image\Processing\Morphology\MorphClose.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\PixelMap.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PixelMap.hh

"C:\Build\inc\Ravl\Image\PixelMap.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\PixelMap.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PixelMap.hh

"C:\Build\inc\Ravl\Image\PixelMap.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\PixelMap.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\PixelMapSearch.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PixelMapSearch.hh

"C:\Build\inc\Ravl\Image\PixelMapSearch.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\PixelMapSearch.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PixelMapSearch.hh

"C:\Build\inc\Ravl\Image\PixelMapSearch.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\PixelMapSearch.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\PCPixel.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PCPixel.hh

"C:\Build\inc\Ravl\Image\PCPixel.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\PCPixel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PCPixel.hh

"C:\Build\inc\Ravl\Image\PCPixel.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\PCPixel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\PCPixelList.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PCPixelList.hh

"C:\Build\inc\Ravl\Image\PCPixelList.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\PCPixelList.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PCPixelList.hh

"C:\Build\inc\Ravl\Image\PCPixelList.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\PCPixelList.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\PCMapping.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PCMapping.hh

"C:\Build\inc\Ravl\Image\PCMapping.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\PCMapping.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PCMapping.hh

"C:\Build\inc\Ravl\Image\PCMapping.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\PCMapping.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\PPHT.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PPHT.hh

"C:\Build\inc\Ravl\Image\PPHT.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\PPHT.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PPHT.hh

"C:\Build\inc\Ravl\Image\PPHT.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\PPHT.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Lines\ArcDetector.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ArcDetector.hh

"C:\Build\inc\Ravl\Image\ArcDetector.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\ArcDetector.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ArcDetector.hh

"C:\Build\inc\Ravl\Image\ArcDetector.hh" :  "" ""
	copy ..\.\Image\Processing\Lines\ArcDetector.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Corners\Corner.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header Corner.hh

"C:\Build\inc\Ravl\Image\Corner.hh" :  "" ""
	copy ..\.\Image\Processing\Corners\Corner.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header Corner.hh

"C:\Build\inc\Ravl\Image\Corner.hh" :  "" ""
	copy ..\.\Image\Processing\Corners\Corner.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Corners\CornerDetector.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header CornerDetector.hh

"C:\Build\inc\Ravl\Image\CornerDetector.hh" :  "" ""
	copy ..\.\Image\Processing\Corners\CornerDetector.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header CornerDetector.hh

"C:\Build\inc\Ravl\Image\CornerDetector.hh" :  "" ""
	copy ..\.\Image\Processing\Corners\CornerDetector.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Corners\CornerDetectorHarris.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header CornerDetectorHarris.hh

"C:\Build\inc\Ravl\Image\CornerDetectorHarris.hh" :  "" ""
	copy ..\.\Image\Processing\Corners\CornerDetectorHarris.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header CornerDetectorHarris.hh

"C:\Build\inc\Ravl\Image\CornerDetectorHarris.hh" :  "" ""
	copy ..\.\Image\Processing\Corners\CornerDetectorHarris.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Corners\CornerDetectorSusan.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header CornerDetectorSusan.hh

"C:\Build\inc\Ravl\Image\CornerDetectorSusan.hh" :  "" ""
	copy ..\.\Image\Processing\Corners\CornerDetectorSusan.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header CornerDetectorSusan.hh

"C:\Build\inc\Ravl\Image\CornerDetectorSusan.hh" :  "" ""
	copy ..\.\Image\Processing\Corners\CornerDetectorSusan.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Motion\LMSGradient\LMSOpticFlow.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header LMSOpticFlow.hh

"C:\Build\inc\Ravl\Image\LMSOpticFlow.hh" :  "" ""
	copy ..\.\Image\Processing\Motion\LMSGradient\LMSOpticFlow.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header LMSOpticFlow.hh

"C:\Build\inc\Ravl\Image\LMSOpticFlow.hh" :  "" ""
	copy ..\.\Image\Processing\Motion\LMSGradient\LMSOpticFlow.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Motion\LMSGradient\LMSMultiScaleMotion.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header LMSMultiScaleMotion.hh

"C:\Build\inc\Ravl\Image\LMSMultiScaleMotion.hh" :  "" ""
	copy ..\.\Image\Processing\Motion\LMSGradient\LMSMultiScaleMotion.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header LMSMultiScaleMotion.hh

"C:\Build\inc\Ravl\Image\LMSMultiScaleMotion.hh" :  "" ""
	copy ..\.\Image\Processing\Motion\LMSGradient\LMSMultiScaleMotion.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Motion\LMSGradient\LMSRegionMotion.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header LMSRegionMotion.hh

"C:\Build\inc\Ravl\Image\LMSRegionMotion.hh" :  "" ""
	copy ..\.\Image\Processing\Motion\LMSGradient\LMSRegionMotion.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header LMSRegionMotion.hh

"C:\Build\inc\Ravl\Image\LMSRegionMotion.hh" :  "" ""
	copy ..\.\Image\Processing\Motion\LMSGradient\LMSRegionMotion.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\PointTrack.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PointTrack.hh

"C:\Build\inc\Ravl\Image\PointTrack.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\PointTrack.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PointTrack.hh

"C:\Build\inc\Ravl\Image\PointTrack.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\PointTrack.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\PointTrackModel.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PointTrackModel.hh

"C:\Build\inc\Ravl\Image\PointTrackModel.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\PointTrackModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PointTrackModel.hh

"C:\Build\inc\Ravl\Image\PointTrackModel.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\PointTrackModel.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\PointTracker.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header PointTracker.hh

"C:\Build\inc\Ravl\Image\PointTracker.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\PointTracker.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header PointTracker.hh

"C:\Build\inc\Ravl\Image\PointTracker.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\PointTracker.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\MosaicBuilder.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header MosaicBuilder.hh

"C:\Build\inc\Ravl\Image\MosaicBuilder.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\MosaicBuilder.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header MosaicBuilder.hh

"C:\Build\inc\Ravl\Image\MosaicBuilder.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\MosaicBuilder.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\MatchPatch.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header MatchPatch.hh

"C:\Build\inc\Ravl\Image\MatchPatch.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\MatchPatch.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header MatchPatch.hh

"C:\Build\inc\Ravl\Image\MatchPatch.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\MatchPatch.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\ImageTracker.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ImageTracker.hh

"C:\Build\inc\Ravl\Image\ImageTracker.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\ImageTracker.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ImageTracker.hh

"C:\Build\inc\Ravl\Image\ImageTracker.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\ImageTracker.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\ImageMatcher.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ImageMatcher.hh

"C:\Build\inc\Ravl\Image\ImageMatcher.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\ImageMatcher.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ImageMatcher.hh

"C:\Build\inc\Ravl\Image\ImageMatcher.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\ImageMatcher.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\MatchNormalisedCorrelation.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header MatchNormalisedCorrelation.hh

"C:\Build\inc\Ravl\Image\MatchNormalisedCorrelation.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\MatchNormalisedCorrelation.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header MatchNormalisedCorrelation.hh

"C:\Build\inc\Ravl\Image\MatchNormalisedCorrelation.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\MatchNormalisedCorrelation.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\ForegroundSep.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header ForegroundSep.hh

"C:\Build\inc\Ravl\Image\ForegroundSep.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\ForegroundSep.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header ForegroundSep.hh

"C:\Build\inc\Ravl\Image\ForegroundSep.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\ForegroundSep.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Image\Processing\Tracking\TrackingHomog.hh

!IF  "$(CFG)" == "RavlImageProc - Win32 Release"

# Begin Custom Build - Install Header TrackingHomog.hh

"C:\Build\inc\Ravl\Image\TrackingHomog.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\TrackingHomog.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlImageProc - Win32 Debug"

# Begin Custom Build - Install Header TrackingHomog.hh

"C:\Build\inc\Ravl\Image\TrackingHomog.hh" :  "" ""
	copy ..\.\Image\Processing\Tracking\TrackingHomog.hh C:\Build\inc\Ravl\Image

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
