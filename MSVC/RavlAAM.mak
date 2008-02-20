


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlAAM
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlAAM
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/AAMAppearance.obj $(OPTOBJDIR)/AAMShapeModel.obj $(OPTOBJDIR)/AAMAffineShapeModel.obj $(OPTOBJDIR)/AAMScaleRotationShapeModel.obj $(OPTOBJDIR)/AAMAppearanceModel.obj $(OPTOBJDIR)/AAMAppearanceUtil.obj $(OPTOBJDIR)/AAMActiveAppearanceModel.obj $(OPTOBJDIR)/AAMSampleStream.obj $(OPTOBJDIR)/AAMMultiResActiveAppearanceModel.obj $(OPTOBJDIR)/AAMFaceLocalisation.obj $(OPTOBJDIR)/AAMPoseEstimateCostFunction.obj $(OPTOBJDIR)/AAMPoseEstimate.obj $(OPTOBJDIR)/AAMFaceCorrection.obj $(OPTOBJDIR)/AAMActiveAppearanceModelsIO.obj $(OPTOBJDIR)/AAMActiveAppearanceModelMustLink.obj
	@echo -- making $(OPTLIBDIR)/RavlAAM.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlAAM.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/AAMAppearance.obj $(DEBUGOBJDIR)/AAMShapeModel.obj $(DEBUGOBJDIR)/AAMAffineShapeModel.obj $(DEBUGOBJDIR)/AAMScaleRotationShapeModel.obj $(DEBUGOBJDIR)/AAMAppearanceModel.obj $(DEBUGOBJDIR)/AAMAppearanceUtil.obj $(DEBUGOBJDIR)/AAMActiveAppearanceModel.obj $(DEBUGOBJDIR)/AAMSampleStream.obj $(DEBUGOBJDIR)/AAMMultiResActiveAppearanceModel.obj $(DEBUGOBJDIR)/AAMFaceLocalisation.obj $(DEBUGOBJDIR)/AAMPoseEstimateCostFunction.obj $(DEBUGOBJDIR)/AAMPoseEstimate.obj $(DEBUGOBJDIR)/AAMFaceCorrection.obj $(DEBUGOBJDIR)/AAMActiveAppearanceModelsIO.obj $(DEBUGOBJDIR)/AAMActiveAppearanceModelMustLink.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlAAM.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlAAM.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlAAM
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/AAMAppearance.obj: .././CompVision/ActiveAppearanceModels/AAMAppearance.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMAppearance.obj .././CompVision/ActiveAppearanceModels/AAMAppearance.cc

$(DEBUGOBJDIR)/AAMAppearance.obj: .././CompVision/ActiveAppearanceModels/AAMAppearance.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMAppearance.obj .././CompVision/ActiveAppearanceModels/AAMAppearance.cc

$(OPTOBJDIR)/AAMShapeModel.obj: .././CompVision/ActiveAppearanceModels/AAMShapeModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMShapeModel.obj .././CompVision/ActiveAppearanceModels/AAMShapeModel.cc

$(DEBUGOBJDIR)/AAMShapeModel.obj: .././CompVision/ActiveAppearanceModels/AAMShapeModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMShapeModel.obj .././CompVision/ActiveAppearanceModels/AAMShapeModel.cc

$(OPTOBJDIR)/AAMAffineShapeModel.obj: .././CompVision/ActiveAppearanceModels/AAMAffineShapeModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMAffineShapeModel.obj .././CompVision/ActiveAppearanceModels/AAMAffineShapeModel.cc

$(DEBUGOBJDIR)/AAMAffineShapeModel.obj: .././CompVision/ActiveAppearanceModels/AAMAffineShapeModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMAffineShapeModel.obj .././CompVision/ActiveAppearanceModels/AAMAffineShapeModel.cc

$(OPTOBJDIR)/AAMScaleRotationShapeModel.obj: .././CompVision/ActiveAppearanceModels/AAMScaleRotationShapeModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMScaleRotationShapeModel.obj .././CompVision/ActiveAppearanceModels/AAMScaleRotationShapeModel.cc

$(DEBUGOBJDIR)/AAMScaleRotationShapeModel.obj: .././CompVision/ActiveAppearanceModels/AAMScaleRotationShapeModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMScaleRotationShapeModel.obj .././CompVision/ActiveAppearanceModels/AAMScaleRotationShapeModel.cc

$(OPTOBJDIR)/AAMAppearanceModel.obj: .././CompVision/ActiveAppearanceModels/AAMAppearanceModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMAppearanceModel.obj .././CompVision/ActiveAppearanceModels/AAMAppearanceModel.cc

$(DEBUGOBJDIR)/AAMAppearanceModel.obj: .././CompVision/ActiveAppearanceModels/AAMAppearanceModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMAppearanceModel.obj .././CompVision/ActiveAppearanceModels/AAMAppearanceModel.cc

$(OPTOBJDIR)/AAMAppearanceUtil.obj: .././CompVision/ActiveAppearanceModels/AAMAppearanceUtil.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMAppearanceUtil.obj .././CompVision/ActiveAppearanceModels/AAMAppearanceUtil.cc

$(DEBUGOBJDIR)/AAMAppearanceUtil.obj: .././CompVision/ActiveAppearanceModels/AAMAppearanceUtil.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMAppearanceUtil.obj .././CompVision/ActiveAppearanceModels/AAMAppearanceUtil.cc

$(OPTOBJDIR)/AAMActiveAppearanceModel.obj: .././CompVision/ActiveAppearanceModels/AAMActiveAppearanceModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMActiveAppearanceModel.obj .././CompVision/ActiveAppearanceModels/AAMActiveAppearanceModel.cc

$(DEBUGOBJDIR)/AAMActiveAppearanceModel.obj: .././CompVision/ActiveAppearanceModels/AAMActiveAppearanceModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMActiveAppearanceModel.obj .././CompVision/ActiveAppearanceModels/AAMActiveAppearanceModel.cc

$(OPTOBJDIR)/AAMSampleStream.obj: .././CompVision/ActiveAppearanceModels/AAMSampleStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMSampleStream.obj .././CompVision/ActiveAppearanceModels/AAMSampleStream.cc

$(DEBUGOBJDIR)/AAMSampleStream.obj: .././CompVision/ActiveAppearanceModels/AAMSampleStream.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMSampleStream.obj .././CompVision/ActiveAppearanceModels/AAMSampleStream.cc

$(OPTOBJDIR)/AAMMultiResActiveAppearanceModel.obj: .././CompVision/ActiveAppearanceModels/AAMMultiResActiveAppearanceModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMMultiResActiveAppearanceModel.obj .././CompVision/ActiveAppearanceModels/AAMMultiResActiveAppearanceModel.cc

$(DEBUGOBJDIR)/AAMMultiResActiveAppearanceModel.obj: .././CompVision/ActiveAppearanceModels/AAMMultiResActiveAppearanceModel.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMMultiResActiveAppearanceModel.obj .././CompVision/ActiveAppearanceModels/AAMMultiResActiveAppearanceModel.cc

$(OPTOBJDIR)/AAMFaceLocalisation.obj: .././CompVision/ActiveAppearanceModels/AAMFaceLocalisation.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMFaceLocalisation.obj .././CompVision/ActiveAppearanceModels/AAMFaceLocalisation.cc

$(DEBUGOBJDIR)/AAMFaceLocalisation.obj: .././CompVision/ActiveAppearanceModels/AAMFaceLocalisation.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMFaceLocalisation.obj .././CompVision/ActiveAppearanceModels/AAMFaceLocalisation.cc

$(OPTOBJDIR)/AAMPoseEstimateCostFunction.obj: .././CompVision/ActiveAppearanceModels/AAMPoseEstimateCostFunction.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMPoseEstimateCostFunction.obj .././CompVision/ActiveAppearanceModels/AAMPoseEstimateCostFunction.cc

$(DEBUGOBJDIR)/AAMPoseEstimateCostFunction.obj: .././CompVision/ActiveAppearanceModels/AAMPoseEstimateCostFunction.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMPoseEstimateCostFunction.obj .././CompVision/ActiveAppearanceModels/AAMPoseEstimateCostFunction.cc

$(OPTOBJDIR)/AAMPoseEstimate.obj: .././CompVision/ActiveAppearanceModels/AAMPoseEstimate.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMPoseEstimate.obj .././CompVision/ActiveAppearanceModels/AAMPoseEstimate.cc

$(DEBUGOBJDIR)/AAMPoseEstimate.obj: .././CompVision/ActiveAppearanceModels/AAMPoseEstimate.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMPoseEstimate.obj .././CompVision/ActiveAppearanceModels/AAMPoseEstimate.cc

$(OPTOBJDIR)/AAMFaceCorrection.obj: .././CompVision/ActiveAppearanceModels/AAMFaceCorrection.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMFaceCorrection.obj .././CompVision/ActiveAppearanceModels/AAMFaceCorrection.cc

$(DEBUGOBJDIR)/AAMFaceCorrection.obj: .././CompVision/ActiveAppearanceModels/AAMFaceCorrection.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMFaceCorrection.obj .././CompVision/ActiveAppearanceModels/AAMFaceCorrection.cc

$(OPTOBJDIR)/AAMActiveAppearanceModelsIO.obj: .././CompVision/ActiveAppearanceModels/AAMActiveAppearanceModelsIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMActiveAppearanceModelsIO.obj .././CompVision/ActiveAppearanceModels/AAMActiveAppearanceModelsIO.cc

$(DEBUGOBJDIR)/AAMActiveAppearanceModelsIO.obj: .././CompVision/ActiveAppearanceModels/AAMActiveAppearanceModelsIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMActiveAppearanceModelsIO.obj .././CompVision/ActiveAppearanceModels/AAMActiveAppearanceModelsIO.cc

$(OPTOBJDIR)/AAMActiveAppearanceModelMustLink.obj: .././CompVision/ActiveAppearanceModels/AAMActiveAppearanceModelMustLink.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AAMActiveAppearanceModelMustLink.obj .././CompVision/ActiveAppearanceModels/AAMActiveAppearanceModelMustLink.cc

$(DEBUGOBJDIR)/AAMActiveAppearanceModelMustLink.obj: .././CompVision/ActiveAppearanceModels/AAMActiveAppearanceModelMustLink.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AAMActiveAppearanceModelMustLink.obj .././CompVision/ActiveAppearanceModels/AAMActiveAppearanceModelMustLink.cc


