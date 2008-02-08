


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
DEBUGOBJDIR = c:\Build/win32/debug/obj/RavlImageProc
DEBUGLIBDIR = c:\Build/win32/debug/lib

OPTOBJDIR = c:\Build/win32/opt/obj/RavlImageProc
OPTLIBDIR = c:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/Rectangle2dIter.obj $(OPTOBJDIR)/SobolImage.obj $(OPTOBJDIR)/PyramidScan.obj $(OPTOBJDIR)/ImagePointFeatureSet.obj $(OPTOBJDIR)/ImagePointFeature.obj $(OPTOBJDIR)/HomomorphicFilter.obj $(OPTOBJDIR)/DCT2d.obj $(OPTOBJDIR)/DeinterlaceStream.obj $(OPTOBJDIR)/GaborComplex.obj $(OPTOBJDIR)/GaborFilter2d.obj $(OPTOBJDIR)/Correlate2d.obj $(OPTOBJDIR)/Matching.obj $(OPTOBJDIR)/WarpThinPlateSpline.obj $(OPTOBJDIR)/WarpMesh2d.obj $(OPTOBJDIR)/EdgeSobel.obj $(OPTOBJDIR)/EdgeDeriche.obj $(OPTOBJDIR)/SqrComposition.obj $(OPTOBJDIR)/EdgeNonMaxSuppression.obj $(OPTOBJDIR)/Edgel.obj $(OPTOBJDIR)/EdgeLink.obj $(OPTOBJDIR)/EdgeDetector.obj $(OPTOBJDIR)/EdgeIO.obj $(OPTOBJDIR)/ChromaThreshold.obj $(OPTOBJDIR)/Segmentation.obj $(OPTOBJDIR)/ConnectedComponents.obj $(OPTOBJDIR)/BlueScreen.obj $(OPTOBJDIR)/SegmentExtrema.obj $(OPTOBJDIR)/PixelSelectStack.obj $(OPTOBJDIR)/PixelMap.obj $(OPTOBJDIR)/PixelMapSearch.obj $(OPTOBJDIR)/PCPixel.obj $(OPTOBJDIR)/PCPixelList.obj $(OPTOBJDIR)/PCMapping.obj $(OPTOBJDIR)/PPHT.obj $(OPTOBJDIR)/ArcDetector.obj $(OPTOBJDIR)/Corner.obj $(OPTOBJDIR)/CornerDetector.obj $(OPTOBJDIR)/CornerDetectorHarris.obj $(OPTOBJDIR)/CornerDetectorSusan.obj $(OPTOBJDIR)/LMSOpticFlow.obj $(OPTOBJDIR)/LMSMultiScaleMotion.obj $(OPTOBJDIR)/LMSRegionMotion.obj $(OPTOBJDIR)/PointTrack.obj $(OPTOBJDIR)/PointTrackModel.obj $(OPTOBJDIR)/PointTracker.obj $(OPTOBJDIR)/MosaicBuilder.obj $(OPTOBJDIR)/ImageTracker.obj $(OPTOBJDIR)/ImageMatcher.obj $(OPTOBJDIR)/MatchNormalisedCorrelation.obj $(OPTOBJDIR)/ForegroundSep.obj $(OPTOBJDIR)/TrackingHomog.obj
	@echo -- making $(OPTLIBDIR)/RavlImageProc.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlImageProc.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/Rectangle2dIter.obj $(DEBUGOBJDIR)/SobolImage.obj $(DEBUGOBJDIR)/PyramidScan.obj $(DEBUGOBJDIR)/ImagePointFeatureSet.obj $(DEBUGOBJDIR)/ImagePointFeature.obj $(DEBUGOBJDIR)/HomomorphicFilter.obj $(DEBUGOBJDIR)/DCT2d.obj $(DEBUGOBJDIR)/DeinterlaceStream.obj $(DEBUGOBJDIR)/GaborComplex.obj $(DEBUGOBJDIR)/GaborFilter2d.obj $(DEBUGOBJDIR)/Correlate2d.obj $(DEBUGOBJDIR)/Matching.obj $(DEBUGOBJDIR)/WarpThinPlateSpline.obj $(DEBUGOBJDIR)/WarpMesh2d.obj $(DEBUGOBJDIR)/EdgeSobel.obj $(DEBUGOBJDIR)/EdgeDeriche.obj $(DEBUGOBJDIR)/SqrComposition.obj $(DEBUGOBJDIR)/EdgeNonMaxSuppression.obj $(DEBUGOBJDIR)/Edgel.obj $(DEBUGOBJDIR)/EdgeLink.obj $(DEBUGOBJDIR)/EdgeDetector.obj $(DEBUGOBJDIR)/EdgeIO.obj $(DEBUGOBJDIR)/ChromaThreshold.obj $(DEBUGOBJDIR)/Segmentation.obj $(DEBUGOBJDIR)/ConnectedComponents.obj $(DEBUGOBJDIR)/BlueScreen.obj $(DEBUGOBJDIR)/SegmentExtrema.obj $(DEBUGOBJDIR)/PixelSelectStack.obj $(DEBUGOBJDIR)/PixelMap.obj $(DEBUGOBJDIR)/PixelMapSearch.obj $(DEBUGOBJDIR)/PCPixel.obj $(DEBUGOBJDIR)/PCPixelList.obj $(DEBUGOBJDIR)/PCMapping.obj $(DEBUGOBJDIR)/PPHT.obj $(DEBUGOBJDIR)/ArcDetector.obj $(DEBUGOBJDIR)/Corner.obj $(DEBUGOBJDIR)/CornerDetector.obj $(DEBUGOBJDIR)/CornerDetectorHarris.obj $(DEBUGOBJDIR)/CornerDetectorSusan.obj $(DEBUGOBJDIR)/LMSOpticFlow.obj $(DEBUGOBJDIR)/LMSMultiScaleMotion.obj $(DEBUGOBJDIR)/LMSRegionMotion.obj $(DEBUGOBJDIR)/PointTrack.obj $(DEBUGOBJDIR)/PointTrackModel.obj $(DEBUGOBJDIR)/PointTracker.obj $(DEBUGOBJDIR)/MosaicBuilder.obj $(DEBUGOBJDIR)/ImageTracker.obj $(DEBUGOBJDIR)/ImageMatcher.obj $(DEBUGOBJDIR)/MatchNormalisedCorrelation.obj $(DEBUGOBJDIR)/ForegroundSep.obj $(DEBUGOBJDIR)/TrackingHomog.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlImageProc.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlImageProc.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlImageProc
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/Rectangle2dIter.obj: .././Image/Processing/Tools/Rectangle2dIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Rectangle2dIter.obj .././Image/Processing/Tools/Rectangle2dIter.cc

$(DEBUGOBJDIR)/Rectangle2dIter.obj: .././Image/Processing/Tools/Rectangle2dIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Rectangle2dIter.obj .././Image/Processing/Tools/Rectangle2dIter.cc

$(OPTOBJDIR)/SobolImage.obj: .././Image/Processing/Tools/SobolImage.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SobolImage.obj .././Image/Processing/Tools/SobolImage.cc

$(DEBUGOBJDIR)/SobolImage.obj: .././Image/Processing/Tools/SobolImage.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SobolImage.obj .././Image/Processing/Tools/SobolImage.cc

$(OPTOBJDIR)/PyramidScan.obj: .././Image/Processing/Tools/PyramidScan.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PyramidScan.obj .././Image/Processing/Tools/PyramidScan.cc

$(DEBUGOBJDIR)/PyramidScan.obj: .././Image/Processing/Tools/PyramidScan.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PyramidScan.obj .././Image/Processing/Tools/PyramidScan.cc

$(OPTOBJDIR)/ImagePointFeatureSet.obj: .././Image/Processing/Tools/ImagePointFeatureSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImagePointFeatureSet.obj .././Image/Processing/Tools/ImagePointFeatureSet.cc

$(DEBUGOBJDIR)/ImagePointFeatureSet.obj: .././Image/Processing/Tools/ImagePointFeatureSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImagePointFeatureSet.obj .././Image/Processing/Tools/ImagePointFeatureSet.cc

$(OPTOBJDIR)/ImagePointFeature.obj: .././Image/Processing/Tools/ImagePointFeature.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImagePointFeature.obj .././Image/Processing/Tools/ImagePointFeature.cc

$(DEBUGOBJDIR)/ImagePointFeature.obj: .././Image/Processing/Tools/ImagePointFeature.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImagePointFeature.obj .././Image/Processing/Tools/ImagePointFeature.cc

$(OPTOBJDIR)/HomomorphicFilter.obj: .././Image/Processing/Filters/Misc/HomomorphicFilter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HomomorphicFilter.obj .././Image/Processing/Filters/Misc/HomomorphicFilter.cc

$(DEBUGOBJDIR)/HomomorphicFilter.obj: .././Image/Processing/Filters/Misc/HomomorphicFilter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HomomorphicFilter.obj .././Image/Processing/Filters/Misc/HomomorphicFilter.cc

$(OPTOBJDIR)/DCT2d.obj: .././Image/Processing/Filters/Misc/DCT2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DCT2d.obj .././Image/Processing/Filters/Misc/DCT2d.cc

$(DEBUGOBJDIR)/DCT2d.obj: .././Image/Processing/Filters/Misc/DCT2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DCT2d.obj .././Image/Processing/Filters/Misc/DCT2d.cc

$(OPTOBJDIR)/DeinterlaceStream.obj: .././Image/Processing/Filters/Misc/DeinterlaceStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DeinterlaceStream.obj .././Image/Processing/Filters/Misc/DeinterlaceStream.cc

$(DEBUGOBJDIR)/DeinterlaceStream.obj: .././Image/Processing/Filters/Misc/DeinterlaceStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DeinterlaceStream.obj .././Image/Processing/Filters/Misc/DeinterlaceStream.cc

$(OPTOBJDIR)/GaborComplex.obj: .././Image/Processing/Filters/Gabor/GaborComplex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GaborComplex.obj .././Image/Processing/Filters/Gabor/GaborComplex.cc

$(DEBUGOBJDIR)/GaborComplex.obj: .././Image/Processing/Filters/Gabor/GaborComplex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GaborComplex.obj .././Image/Processing/Filters/Gabor/GaborComplex.cc

$(OPTOBJDIR)/GaborFilter2d.obj: .././Image/Processing/Filters/Gabor/GaborFilter2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GaborFilter2d.obj .././Image/Processing/Filters/Gabor/GaborFilter2d.cc

$(DEBUGOBJDIR)/GaborFilter2d.obj: .././Image/Processing/Filters/Gabor/GaborFilter2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GaborFilter2d.obj .././Image/Processing/Filters/Gabor/GaborFilter2d.cc

$(OPTOBJDIR)/Correlate2d.obj: .././Image/Processing/Filters/Matching/Correlate2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Correlate2d.obj .././Image/Processing/Filters/Matching/Correlate2d.cc

$(DEBUGOBJDIR)/Correlate2d.obj: .././Image/Processing/Filters/Matching/Correlate2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Correlate2d.obj .././Image/Processing/Filters/Matching/Correlate2d.cc

$(OPTOBJDIR)/Matching.obj: .././Image/Processing/Filters/Matching/Matching.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Matching.obj .././Image/Processing/Filters/Matching/Matching.cc

$(DEBUGOBJDIR)/Matching.obj: .././Image/Processing/Filters/Matching/Matching.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Matching.obj .././Image/Processing/Filters/Matching/Matching.cc

$(OPTOBJDIR)/WarpThinPlateSpline.obj: .././Image/Processing/Filters/Warp/WarpThinPlateSpline.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/WarpThinPlateSpline.obj .././Image/Processing/Filters/Warp/WarpThinPlateSpline.cc

$(DEBUGOBJDIR)/WarpThinPlateSpline.obj: .././Image/Processing/Filters/Warp/WarpThinPlateSpline.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/WarpThinPlateSpline.obj .././Image/Processing/Filters/Warp/WarpThinPlateSpline.cc

$(OPTOBJDIR)/WarpMesh2d.obj: .././Image/Processing/Filters/Warp/WarpMesh2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/WarpMesh2d.obj .././Image/Processing/Filters/Warp/WarpMesh2d.cc

$(DEBUGOBJDIR)/WarpMesh2d.obj: .././Image/Processing/Filters/Warp/WarpMesh2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/WarpMesh2d.obj .././Image/Processing/Filters/Warp/WarpMesh2d.cc

$(OPTOBJDIR)/EdgeSobel.obj: .././Image/Processing/Edges/EdgeSobel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EdgeSobel.obj .././Image/Processing/Edges/EdgeSobel.cc

$(DEBUGOBJDIR)/EdgeSobel.obj: .././Image/Processing/Edges/EdgeSobel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EdgeSobel.obj .././Image/Processing/Edges/EdgeSobel.cc

$(OPTOBJDIR)/EdgeDeriche.obj: .././Image/Processing/Edges/EdgeDeriche.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EdgeDeriche.obj .././Image/Processing/Edges/EdgeDeriche.cc

$(DEBUGOBJDIR)/EdgeDeriche.obj: .././Image/Processing/Edges/EdgeDeriche.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EdgeDeriche.obj .././Image/Processing/Edges/EdgeDeriche.cc

$(OPTOBJDIR)/SqrComposition.obj: .././Image/Processing/Edges/SqrComposition.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SqrComposition.obj .././Image/Processing/Edges/SqrComposition.cc

$(DEBUGOBJDIR)/SqrComposition.obj: .././Image/Processing/Edges/SqrComposition.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SqrComposition.obj .././Image/Processing/Edges/SqrComposition.cc

$(OPTOBJDIR)/EdgeNonMaxSuppression.obj: .././Image/Processing/Edges/EdgeNonMaxSuppression.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EdgeNonMaxSuppression.obj .././Image/Processing/Edges/EdgeNonMaxSuppression.cc

$(DEBUGOBJDIR)/EdgeNonMaxSuppression.obj: .././Image/Processing/Edges/EdgeNonMaxSuppression.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EdgeNonMaxSuppression.obj .././Image/Processing/Edges/EdgeNonMaxSuppression.cc

$(OPTOBJDIR)/Edgel.obj: .././Image/Processing/Edges/Edgel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Edgel.obj .././Image/Processing/Edges/Edgel.cc

$(DEBUGOBJDIR)/Edgel.obj: .././Image/Processing/Edges/Edgel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Edgel.obj .././Image/Processing/Edges/Edgel.cc

$(OPTOBJDIR)/EdgeLink.obj: .././Image/Processing/Edges/EdgeLink.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EdgeLink.obj .././Image/Processing/Edges/EdgeLink.cc

$(DEBUGOBJDIR)/EdgeLink.obj: .././Image/Processing/Edges/EdgeLink.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EdgeLink.obj .././Image/Processing/Edges/EdgeLink.cc

$(OPTOBJDIR)/EdgeDetector.obj: .././Image/Processing/Edges/EdgeDetector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EdgeDetector.obj .././Image/Processing/Edges/EdgeDetector.cc

$(DEBUGOBJDIR)/EdgeDetector.obj: .././Image/Processing/Edges/EdgeDetector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EdgeDetector.obj .././Image/Processing/Edges/EdgeDetector.cc

$(OPTOBJDIR)/EdgeIO.obj: .././Image/Processing/Edges/EdgeIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EdgeIO.obj .././Image/Processing/Edges/EdgeIO.cc

$(DEBUGOBJDIR)/EdgeIO.obj: .././Image/Processing/Edges/EdgeIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EdgeIO.obj .././Image/Processing/Edges/EdgeIO.cc

$(OPTOBJDIR)/ChromaThreshold.obj: .././Image/Processing/Segmentation/ChromaThreshold.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ChromaThreshold.obj .././Image/Processing/Segmentation/ChromaThreshold.cc

$(DEBUGOBJDIR)/ChromaThreshold.obj: .././Image/Processing/Segmentation/ChromaThreshold.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ChromaThreshold.obj .././Image/Processing/Segmentation/ChromaThreshold.cc

$(OPTOBJDIR)/Segmentation.obj: .././Image/Processing/Segmentation/Segmentation.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Segmentation.obj .././Image/Processing/Segmentation/Segmentation.cc

$(DEBUGOBJDIR)/Segmentation.obj: .././Image/Processing/Segmentation/Segmentation.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Segmentation.obj .././Image/Processing/Segmentation/Segmentation.cc

$(OPTOBJDIR)/ConnectedComponents.obj: .././Image/Processing/Segmentation/ConnectedComponents.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ConnectedComponents.obj .././Image/Processing/Segmentation/ConnectedComponents.cc

$(DEBUGOBJDIR)/ConnectedComponents.obj: .././Image/Processing/Segmentation/ConnectedComponents.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ConnectedComponents.obj .././Image/Processing/Segmentation/ConnectedComponents.cc

$(OPTOBJDIR)/BlueScreen.obj: .././Image/Processing/Segmentation/BlueScreen.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BlueScreen.obj .././Image/Processing/Segmentation/BlueScreen.cc

$(DEBUGOBJDIR)/BlueScreen.obj: .././Image/Processing/Segmentation/BlueScreen.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BlueScreen.obj .././Image/Processing/Segmentation/BlueScreen.cc

$(OPTOBJDIR)/SegmentExtrema.obj: .././Image/Processing/Segmentation/SegmentExtrema.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SegmentExtrema.obj .././Image/Processing/Segmentation/SegmentExtrema.cc

$(DEBUGOBJDIR)/SegmentExtrema.obj: .././Image/Processing/Segmentation/SegmentExtrema.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SegmentExtrema.obj .././Image/Processing/Segmentation/SegmentExtrema.cc

$(OPTOBJDIR)/PixelSelectStack.obj: .././Image/Processing/Segmentation/PixelSelectStack.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PixelSelectStack.obj .././Image/Processing/Segmentation/PixelSelectStack.cc

$(DEBUGOBJDIR)/PixelSelectStack.obj: .././Image/Processing/Segmentation/PixelSelectStack.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PixelSelectStack.obj .././Image/Processing/Segmentation/PixelSelectStack.cc

$(OPTOBJDIR)/PixelMap.obj: .././Image/Processing/Lines/PixelMap.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PixelMap.obj .././Image/Processing/Lines/PixelMap.cc

$(DEBUGOBJDIR)/PixelMap.obj: .././Image/Processing/Lines/PixelMap.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PixelMap.obj .././Image/Processing/Lines/PixelMap.cc

$(OPTOBJDIR)/PixelMapSearch.obj: .././Image/Processing/Lines/PixelMapSearch.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PixelMapSearch.obj .././Image/Processing/Lines/PixelMapSearch.cc

$(DEBUGOBJDIR)/PixelMapSearch.obj: .././Image/Processing/Lines/PixelMapSearch.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PixelMapSearch.obj .././Image/Processing/Lines/PixelMapSearch.cc

$(OPTOBJDIR)/PCPixel.obj: .././Image/Processing/Lines/PCPixel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PCPixel.obj .././Image/Processing/Lines/PCPixel.cc

$(DEBUGOBJDIR)/PCPixel.obj: .././Image/Processing/Lines/PCPixel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PCPixel.obj .././Image/Processing/Lines/PCPixel.cc

$(OPTOBJDIR)/PCPixelList.obj: .././Image/Processing/Lines/PCPixelList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PCPixelList.obj .././Image/Processing/Lines/PCPixelList.cc

$(DEBUGOBJDIR)/PCPixelList.obj: .././Image/Processing/Lines/PCPixelList.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PCPixelList.obj .././Image/Processing/Lines/PCPixelList.cc

$(OPTOBJDIR)/PCMapping.obj: .././Image/Processing/Lines/PCMapping.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PCMapping.obj .././Image/Processing/Lines/PCMapping.cc

$(DEBUGOBJDIR)/PCMapping.obj: .././Image/Processing/Lines/PCMapping.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PCMapping.obj .././Image/Processing/Lines/PCMapping.cc

$(OPTOBJDIR)/PPHT.obj: .././Image/Processing/Lines/PPHT.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PPHT.obj .././Image/Processing/Lines/PPHT.cc

$(DEBUGOBJDIR)/PPHT.obj: .././Image/Processing/Lines/PPHT.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PPHT.obj .././Image/Processing/Lines/PPHT.cc

$(OPTOBJDIR)/ArcDetector.obj: .././Image/Processing/Lines/ArcDetector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ArcDetector.obj .././Image/Processing/Lines/ArcDetector.cc

$(DEBUGOBJDIR)/ArcDetector.obj: .././Image/Processing/Lines/ArcDetector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ArcDetector.obj .././Image/Processing/Lines/ArcDetector.cc

$(OPTOBJDIR)/Corner.obj: .././Image/Processing/Corners/Corner.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Corner.obj .././Image/Processing/Corners/Corner.cc

$(DEBUGOBJDIR)/Corner.obj: .././Image/Processing/Corners/Corner.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Corner.obj .././Image/Processing/Corners/Corner.cc

$(OPTOBJDIR)/CornerDetector.obj: .././Image/Processing/Corners/CornerDetector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CornerDetector.obj .././Image/Processing/Corners/CornerDetector.cc

$(DEBUGOBJDIR)/CornerDetector.obj: .././Image/Processing/Corners/CornerDetector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CornerDetector.obj .././Image/Processing/Corners/CornerDetector.cc

$(OPTOBJDIR)/CornerDetectorHarris.obj: .././Image/Processing/Corners/CornerDetectorHarris.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CornerDetectorHarris.obj .././Image/Processing/Corners/CornerDetectorHarris.cc

$(DEBUGOBJDIR)/CornerDetectorHarris.obj: .././Image/Processing/Corners/CornerDetectorHarris.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CornerDetectorHarris.obj .././Image/Processing/Corners/CornerDetectorHarris.cc

$(OPTOBJDIR)/CornerDetectorSusan.obj: .././Image/Processing/Corners/CornerDetectorSusan.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CornerDetectorSusan.obj .././Image/Processing/Corners/CornerDetectorSusan.cc

$(DEBUGOBJDIR)/CornerDetectorSusan.obj: .././Image/Processing/Corners/CornerDetectorSusan.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CornerDetectorSusan.obj .././Image/Processing/Corners/CornerDetectorSusan.cc

$(OPTOBJDIR)/LMSOpticFlow.obj: .././Image/Processing/Motion/LMSGradient/LMSOpticFlow.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LMSOpticFlow.obj .././Image/Processing/Motion/LMSGradient/LMSOpticFlow.cc

$(DEBUGOBJDIR)/LMSOpticFlow.obj: .././Image/Processing/Motion/LMSGradient/LMSOpticFlow.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LMSOpticFlow.obj .././Image/Processing/Motion/LMSGradient/LMSOpticFlow.cc

$(OPTOBJDIR)/LMSMultiScaleMotion.obj: .././Image/Processing/Motion/LMSGradient/LMSMultiScaleMotion.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LMSMultiScaleMotion.obj .././Image/Processing/Motion/LMSGradient/LMSMultiScaleMotion.cc

$(DEBUGOBJDIR)/LMSMultiScaleMotion.obj: .././Image/Processing/Motion/LMSGradient/LMSMultiScaleMotion.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LMSMultiScaleMotion.obj .././Image/Processing/Motion/LMSGradient/LMSMultiScaleMotion.cc

$(OPTOBJDIR)/LMSRegionMotion.obj: .././Image/Processing/Motion/LMSGradient/LMSRegionMotion.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LMSRegionMotion.obj .././Image/Processing/Motion/LMSGradient/LMSRegionMotion.cc

$(DEBUGOBJDIR)/LMSRegionMotion.obj: .././Image/Processing/Motion/LMSGradient/LMSRegionMotion.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LMSRegionMotion.obj .././Image/Processing/Motion/LMSGradient/LMSRegionMotion.cc

$(OPTOBJDIR)/PointTrack.obj: .././Image/Processing/Tracking/PointTrack.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PointTrack.obj .././Image/Processing/Tracking/PointTrack.cc

$(DEBUGOBJDIR)/PointTrack.obj: .././Image/Processing/Tracking/PointTrack.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PointTrack.obj .././Image/Processing/Tracking/PointTrack.cc

$(OPTOBJDIR)/PointTrackModel.obj: .././Image/Processing/Tracking/PointTrackModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PointTrackModel.obj .././Image/Processing/Tracking/PointTrackModel.cc

$(DEBUGOBJDIR)/PointTrackModel.obj: .././Image/Processing/Tracking/PointTrackModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PointTrackModel.obj .././Image/Processing/Tracking/PointTrackModel.cc

$(OPTOBJDIR)/PointTracker.obj: .././Image/Processing/Tracking/PointTracker.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PointTracker.obj .././Image/Processing/Tracking/PointTracker.cc

$(DEBUGOBJDIR)/PointTracker.obj: .././Image/Processing/Tracking/PointTracker.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PointTracker.obj .././Image/Processing/Tracking/PointTracker.cc

$(OPTOBJDIR)/MosaicBuilder.obj: .././Image/Processing/Tracking/MosaicBuilder.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MosaicBuilder.obj .././Image/Processing/Tracking/MosaicBuilder.cc

$(DEBUGOBJDIR)/MosaicBuilder.obj: .././Image/Processing/Tracking/MosaicBuilder.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MosaicBuilder.obj .././Image/Processing/Tracking/MosaicBuilder.cc

$(OPTOBJDIR)/ImageTracker.obj: .././Image/Processing/Tracking/ImageTracker.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImageTracker.obj .././Image/Processing/Tracking/ImageTracker.cc

$(DEBUGOBJDIR)/ImageTracker.obj: .././Image/Processing/Tracking/ImageTracker.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImageTracker.obj .././Image/Processing/Tracking/ImageTracker.cc

$(OPTOBJDIR)/ImageMatcher.obj: .././Image/Processing/Tracking/ImageMatcher.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ImageMatcher.obj .././Image/Processing/Tracking/ImageMatcher.cc

$(DEBUGOBJDIR)/ImageMatcher.obj: .././Image/Processing/Tracking/ImageMatcher.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ImageMatcher.obj .././Image/Processing/Tracking/ImageMatcher.cc

$(OPTOBJDIR)/MatchNormalisedCorrelation.obj: .././Image/Processing/Tracking/MatchNormalisedCorrelation.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MatchNormalisedCorrelation.obj .././Image/Processing/Tracking/MatchNormalisedCorrelation.cc

$(DEBUGOBJDIR)/MatchNormalisedCorrelation.obj: .././Image/Processing/Tracking/MatchNormalisedCorrelation.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MatchNormalisedCorrelation.obj .././Image/Processing/Tracking/MatchNormalisedCorrelation.cc

$(OPTOBJDIR)/ForegroundSep.obj: .././Image/Processing/Tracking/ForegroundSep.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ForegroundSep.obj .././Image/Processing/Tracking/ForegroundSep.cc

$(DEBUGOBJDIR)/ForegroundSep.obj: .././Image/Processing/Tracking/ForegroundSep.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ForegroundSep.obj .././Image/Processing/Tracking/ForegroundSep.cc

$(OPTOBJDIR)/TrackingHomog.obj: .././Image/Processing/Tracking/TrackingHomog.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TrackingHomog.obj .././Image/Processing/Tracking/TrackingHomog.cc

$(DEBUGOBJDIR)/TrackingHomog.obj: .././Image/Processing/Tracking/TrackingHomog.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TrackingHomog.obj .././Image/Processing/Tracking/TrackingHomog.cc


