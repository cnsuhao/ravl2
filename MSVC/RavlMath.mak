


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
DEBUGOBJDIR = C:\Build/win32/debug/obj/RavlMath
DEBUGLIBDIR = C:\Build/win32/debug/lib

OPTOBJDIR = C:\Build/win32/opt/obj/RavlMath
OPTLIBDIR = C:\Build/win32/opt/lib


opt:: setup  $(OPTOBJDIR)/TMatrix.obj $(OPTOBJDIR)/Matrix.obj $(OPTOBJDIR)/MatrixInverse.obj $(OPTOBJDIR)/MatrixSVD.obj $(OPTOBJDIR)/MatrixEigen.obj $(OPTOBJDIR)/MatrixSolve.obj $(OPTOBJDIR)/MatrixRUT.obj $(OPTOBJDIR)/MatrixRS.obj $(OPTOBJDIR)/Vector.obj $(OPTOBJDIR)/MatrixNearSingular.obj $(OPTOBJDIR)/LeastSquares.obj $(OPTOBJDIR)/VectorMatrix.obj $(OPTOBJDIR)/MatrixRandom.obj $(OPTOBJDIR)/MatrixDeterminant.obj $(OPTOBJDIR)/MatrixLUDecomposition.obj $(OPTOBJDIR)/TSMatrixSparse.obj $(OPTOBJDIR)/SMatrix.obj $(OPTOBJDIR)/RawMatrix.obj $(OPTOBJDIR)/FastMatrixEigen.obj $(OPTOBJDIR)/Vector2d.obj $(OPTOBJDIR)/Matrix3d.obj $(OPTOBJDIR)/VectorMatrix2d.obj $(OPTOBJDIR)/VectorMatrix3d.obj $(OPTOBJDIR)/VectorMatrix4d.obj $(OPTOBJDIR)/Matrix2d.obj $(OPTOBJDIR)/LineABC2d.obj $(OPTOBJDIR)/Curve2d.obj $(OPTOBJDIR)/Curve2dLine.obj $(OPTOBJDIR)/Curve2dLineFit.obj $(OPTOBJDIR)/Curve2dLineSegment.obj $(OPTOBJDIR)/Line2dIter.obj $(OPTOBJDIR)/Affine2d.obj $(OPTOBJDIR)/Moments2d2.obj $(OPTOBJDIR)/LinePP2d.obj $(OPTOBJDIR)/Projection2d.obj $(OPTOBJDIR)/Point2d.obj $(OPTOBJDIR)/PointSet2d.obj $(OPTOBJDIR)/Polygon2d.obj $(OPTOBJDIR)/Circle2d.obj $(OPTOBJDIR)/FitCircle2d.obj $(OPTOBJDIR)/Arc2d.obj $(OPTOBJDIR)/Curve2dCircle.obj $(OPTOBJDIR)/Curve2dArc.obj $(OPTOBJDIR)/FitLineABC2d.obj $(OPTOBJDIR)/ConvexHullOfPointSet.obj $(OPTOBJDIR)/HEMesh2d.obj $(OPTOBJDIR)/DelaunayTriangulation2d.obj $(OPTOBJDIR)/TriMesh2d.obj $(OPTOBJDIR)/AffineTransformPolygon2d.obj $(OPTOBJDIR)/ProjectiveTransformPolygon2d.obj $(OPTOBJDIR)/Conic2d.obj $(OPTOBJDIR)/Ellipse2d.obj $(OPTOBJDIR)/ScanPolygon2d.obj $(OPTOBJDIR)/PolyLine2d.obj $(OPTOBJDIR)/Poly2dApprox.obj $(OPTOBJDIR)/LinePP3d.obj $(OPTOBJDIR)/LinePV3d.obj $(OPTOBJDIR)/PlaneABCD3d.obj $(OPTOBJDIR)/PlanePVV3d.obj $(OPTOBJDIR)/Quatern3d.obj $(OPTOBJDIR)/RigidTransform3d.obj $(OPTOBJDIR)/EulerAngle.obj $(OPTOBJDIR)/AxisAngle.obj $(OPTOBJDIR)/PointSet3d.obj $(OPTOBJDIR)/HEMesh3d.obj $(OPTOBJDIR)/Affine3d.obj $(OPTOBJDIR)/FitPlaneABCD3d.obj $(OPTOBJDIR)/FitPlanePVV3d.obj $(OPTOBJDIR)/CrackCode.obj $(OPTOBJDIR)/BVertex.obj $(OPTOBJDIR)/Crack.obj $(OPTOBJDIR)/Boundary.obj $(OPTOBJDIR)/ConvexHull.obj $(OPTOBJDIR)/Edge.obj $(OPTOBJDIR)/PPoint1d.obj $(OPTOBJDIR)/PProjection1d.obj $(OPTOBJDIR)/PPointLine2d.obj $(OPTOBJDIR)/PPoint2d.obj $(OPTOBJDIR)/PLine2d.obj $(OPTOBJDIR)/PLinePP2d.obj $(OPTOBJDIR)/PProjection2d.obj $(OPTOBJDIR)/PPerspective2d.obj $(OPTOBJDIR)/FundamentalMatrix2d.obj $(OPTOBJDIR)/FitPProjection2d.obj $(OPTOBJDIR)/PPointPlane3d.obj $(OPTOBJDIR)/PPoint3d.obj $(OPTOBJDIR)/PPlane3d.obj $(OPTOBJDIR)/PProjection3d.obj $(OPTOBJDIR)/PPerspective3d.obj $(OPTOBJDIR)/PLinePV3d.obj $(OPTOBJDIR)/FitPPlane3d.obj $(OPTOBJDIR)/MeanVariance.obj $(OPTOBJDIR)/MeanNd.obj $(OPTOBJDIR)/MeanCovariance.obj $(OPTOBJDIR)/Statistics.obj $(OPTOBJDIR)/Mean.obj $(OPTOBJDIR)/Normal.obj $(OPTOBJDIR)/Sums1d2.obj $(OPTOBJDIR)/SumsNd2.obj $(OPTOBJDIR)/RealHistogram1d.obj $(OPTOBJDIR)/RealHistogram2d.obj $(OPTOBJDIR)/RealHistogram3d.obj $(OPTOBJDIR)/RealHist1dBinaryIO.obj $(OPTOBJDIR)/RealHist2dBinaryIO.obj $(OPTOBJDIR)/RealHist3dBinaryIO.obj $(OPTOBJDIR)/Parzen.obj $(OPTOBJDIR)/PrimitiveBinaryPolynomial.obj $(OPTOBJDIR)/SobolSequence.obj $(OPTOBJDIR)/CircleIter.obj $(OPTOBJDIR)/SquareIter.obj $(OPTOBJDIR)/ZigZagIter.obj $(OPTOBJDIR)/Polygon2dIter.obj $(OPTOBJDIR)/ThinPlateSpline1d.obj $(OPTOBJDIR)/Complex.obj $(OPTOBJDIR)/FFT1d.obj $(OPTOBJDIR)/PowerSpectrum1d.obj $(OPTOBJDIR)/Correlation1d.obj $(OPTOBJDIR)/RealCepstral.obj $(OPTOBJDIR)/GenerateSignal1d.obj $(OPTOBJDIR)/FFT2d.obj
	@echo -- making $(OPTLIBDIR)/RavlMath.lib
	$(LD) /NOLOGO /out:$(OPTLIBDIR)/RavlMath.lib $(OPTOBJDIR)/*.obj


debug:: setup  $(DEBUGOBJDIR)/TMatrix.obj $(DEBUGOBJDIR)/Matrix.obj $(DEBUGOBJDIR)/MatrixInverse.obj $(DEBUGOBJDIR)/MatrixSVD.obj $(DEBUGOBJDIR)/MatrixEigen.obj $(DEBUGOBJDIR)/MatrixSolve.obj $(DEBUGOBJDIR)/MatrixRUT.obj $(DEBUGOBJDIR)/MatrixRS.obj $(DEBUGOBJDIR)/Vector.obj $(DEBUGOBJDIR)/MatrixNearSingular.obj $(DEBUGOBJDIR)/LeastSquares.obj $(DEBUGOBJDIR)/VectorMatrix.obj $(DEBUGOBJDIR)/MatrixRandom.obj $(DEBUGOBJDIR)/MatrixDeterminant.obj $(DEBUGOBJDIR)/MatrixLUDecomposition.obj $(DEBUGOBJDIR)/TSMatrixSparse.obj $(DEBUGOBJDIR)/SMatrix.obj $(DEBUGOBJDIR)/RawMatrix.obj $(DEBUGOBJDIR)/FastMatrixEigen.obj $(DEBUGOBJDIR)/Vector2d.obj $(DEBUGOBJDIR)/Matrix3d.obj $(DEBUGOBJDIR)/VectorMatrix2d.obj $(DEBUGOBJDIR)/VectorMatrix3d.obj $(DEBUGOBJDIR)/VectorMatrix4d.obj $(DEBUGOBJDIR)/Matrix2d.obj $(DEBUGOBJDIR)/LineABC2d.obj $(DEBUGOBJDIR)/Curve2d.obj $(DEBUGOBJDIR)/Curve2dLine.obj $(DEBUGOBJDIR)/Curve2dLineFit.obj $(DEBUGOBJDIR)/Curve2dLineSegment.obj $(DEBUGOBJDIR)/Line2dIter.obj $(DEBUGOBJDIR)/Affine2d.obj $(DEBUGOBJDIR)/Moments2d2.obj $(DEBUGOBJDIR)/LinePP2d.obj $(DEBUGOBJDIR)/Projection2d.obj $(DEBUGOBJDIR)/Point2d.obj $(DEBUGOBJDIR)/PointSet2d.obj $(DEBUGOBJDIR)/Polygon2d.obj $(DEBUGOBJDIR)/Circle2d.obj $(DEBUGOBJDIR)/FitCircle2d.obj $(DEBUGOBJDIR)/Arc2d.obj $(DEBUGOBJDIR)/Curve2dCircle.obj $(DEBUGOBJDIR)/Curve2dArc.obj $(DEBUGOBJDIR)/FitLineABC2d.obj $(DEBUGOBJDIR)/ConvexHullOfPointSet.obj $(DEBUGOBJDIR)/HEMesh2d.obj $(DEBUGOBJDIR)/DelaunayTriangulation2d.obj $(DEBUGOBJDIR)/TriMesh2d.obj $(DEBUGOBJDIR)/AffineTransformPolygon2d.obj $(DEBUGOBJDIR)/ProjectiveTransformPolygon2d.obj $(DEBUGOBJDIR)/Conic2d.obj $(DEBUGOBJDIR)/Ellipse2d.obj $(DEBUGOBJDIR)/ScanPolygon2d.obj $(DEBUGOBJDIR)/PolyLine2d.obj $(DEBUGOBJDIR)/Poly2dApprox.obj $(DEBUGOBJDIR)/LinePP3d.obj $(DEBUGOBJDIR)/LinePV3d.obj $(DEBUGOBJDIR)/PlaneABCD3d.obj $(DEBUGOBJDIR)/PlanePVV3d.obj $(DEBUGOBJDIR)/Quatern3d.obj $(DEBUGOBJDIR)/RigidTransform3d.obj $(DEBUGOBJDIR)/EulerAngle.obj $(DEBUGOBJDIR)/AxisAngle.obj $(DEBUGOBJDIR)/PointSet3d.obj $(DEBUGOBJDIR)/HEMesh3d.obj $(DEBUGOBJDIR)/Affine3d.obj $(DEBUGOBJDIR)/FitPlaneABCD3d.obj $(DEBUGOBJDIR)/FitPlanePVV3d.obj $(DEBUGOBJDIR)/CrackCode.obj $(DEBUGOBJDIR)/BVertex.obj $(DEBUGOBJDIR)/Crack.obj $(DEBUGOBJDIR)/Boundary.obj $(DEBUGOBJDIR)/ConvexHull.obj $(DEBUGOBJDIR)/Edge.obj $(DEBUGOBJDIR)/PPoint1d.obj $(DEBUGOBJDIR)/PProjection1d.obj $(DEBUGOBJDIR)/PPointLine2d.obj $(DEBUGOBJDIR)/PPoint2d.obj $(DEBUGOBJDIR)/PLine2d.obj $(DEBUGOBJDIR)/PLinePP2d.obj $(DEBUGOBJDIR)/PProjection2d.obj $(DEBUGOBJDIR)/PPerspective2d.obj $(DEBUGOBJDIR)/FundamentalMatrix2d.obj $(DEBUGOBJDIR)/FitPProjection2d.obj $(DEBUGOBJDIR)/PPointPlane3d.obj $(DEBUGOBJDIR)/PPoint3d.obj $(DEBUGOBJDIR)/PPlane3d.obj $(DEBUGOBJDIR)/PProjection3d.obj $(DEBUGOBJDIR)/PPerspective3d.obj $(DEBUGOBJDIR)/PLinePV3d.obj $(DEBUGOBJDIR)/FitPPlane3d.obj $(DEBUGOBJDIR)/MeanVariance.obj $(DEBUGOBJDIR)/MeanNd.obj $(DEBUGOBJDIR)/MeanCovariance.obj $(DEBUGOBJDIR)/Statistics.obj $(DEBUGOBJDIR)/Mean.obj $(DEBUGOBJDIR)/Normal.obj $(DEBUGOBJDIR)/Sums1d2.obj $(DEBUGOBJDIR)/SumsNd2.obj $(DEBUGOBJDIR)/RealHistogram1d.obj $(DEBUGOBJDIR)/RealHistogram2d.obj $(DEBUGOBJDIR)/RealHistogram3d.obj $(DEBUGOBJDIR)/RealHist1dBinaryIO.obj $(DEBUGOBJDIR)/RealHist2dBinaryIO.obj $(DEBUGOBJDIR)/RealHist3dBinaryIO.obj $(DEBUGOBJDIR)/Parzen.obj $(DEBUGOBJDIR)/PrimitiveBinaryPolynomial.obj $(DEBUGOBJDIR)/SobolSequence.obj $(DEBUGOBJDIR)/CircleIter.obj $(DEBUGOBJDIR)/SquareIter.obj $(DEBUGOBJDIR)/ZigZagIter.obj $(DEBUGOBJDIR)/Polygon2dIter.obj $(DEBUGOBJDIR)/ThinPlateSpline1d.obj $(DEBUGOBJDIR)/Complex.obj $(DEBUGOBJDIR)/FFT1d.obj $(DEBUGOBJDIR)/PowerSpectrum1d.obj $(DEBUGOBJDIR)/Correlation1d.obj $(DEBUGOBJDIR)/RealCepstral.obj $(DEBUGOBJDIR)/GenerateSignal1d.obj $(DEBUGOBJDIR)/FFT2d.obj 
	@echo -- making $(DEBUGLIBDIR)/RavlMath.lib
	$(LD) /NOLOGO /out:$(DEBUGLIBDIR)/RavlMath.lib $(DEBUGOBJDIR)/*.obj

setup::
        echo --- creating dir for RavlMath
        @if not exist "$(DEBUGOBJDIR)" mkdir "$(DEBUGOBJDIR)"
        @if not exist "$(DEBUGLIBDIR)" mkdir "$(DEBUGLIBDIR)"
        @if not exist "$(OPTOBJDIR)" mkdir "$(OPTOBJDIR)"
        @if not exist "$(OPTLIBDIR)" mkdir "$(OPTLIBDIR)"



$(OPTOBJDIR)/TMatrix.obj: .././Math/LinearAlgebra/General/TMatrix.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TMatrix.obj .././Math/LinearAlgebra/General/TMatrix.cc

$(DEBUGOBJDIR)/TMatrix.obj: .././Math/LinearAlgebra/General/TMatrix.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TMatrix.obj .././Math/LinearAlgebra/General/TMatrix.cc

$(OPTOBJDIR)/Matrix.obj: .././Math/LinearAlgebra/General/Matrix.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Matrix.obj .././Math/LinearAlgebra/General/Matrix.cc

$(DEBUGOBJDIR)/Matrix.obj: .././Math/LinearAlgebra/General/Matrix.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Matrix.obj .././Math/LinearAlgebra/General/Matrix.cc

$(OPTOBJDIR)/MatrixInverse.obj: .././Math/LinearAlgebra/General/MatrixInverse.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MatrixInverse.obj .././Math/LinearAlgebra/General/MatrixInverse.cc

$(DEBUGOBJDIR)/MatrixInverse.obj: .././Math/LinearAlgebra/General/MatrixInverse.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MatrixInverse.obj .././Math/LinearAlgebra/General/MatrixInverse.cc

$(OPTOBJDIR)/MatrixSVD.obj: .././Math/LinearAlgebra/General/MatrixSVD.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MatrixSVD.obj .././Math/LinearAlgebra/General/MatrixSVD.cc

$(DEBUGOBJDIR)/MatrixSVD.obj: .././Math/LinearAlgebra/General/MatrixSVD.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MatrixSVD.obj .././Math/LinearAlgebra/General/MatrixSVD.cc

$(OPTOBJDIR)/MatrixEigen.obj: .././Math/LinearAlgebra/General/MatrixEigen.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MatrixEigen.obj .././Math/LinearAlgebra/General/MatrixEigen.cc

$(DEBUGOBJDIR)/MatrixEigen.obj: .././Math/LinearAlgebra/General/MatrixEigen.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MatrixEigen.obj .././Math/LinearAlgebra/General/MatrixEigen.cc

$(OPTOBJDIR)/MatrixSolve.obj: .././Math/LinearAlgebra/General/MatrixSolve.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MatrixSolve.obj .././Math/LinearAlgebra/General/MatrixSolve.cc

$(DEBUGOBJDIR)/MatrixSolve.obj: .././Math/LinearAlgebra/General/MatrixSolve.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MatrixSolve.obj .././Math/LinearAlgebra/General/MatrixSolve.cc

$(OPTOBJDIR)/MatrixRUT.obj: .././Math/LinearAlgebra/General/MatrixRUT.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MatrixRUT.obj .././Math/LinearAlgebra/General/MatrixRUT.cc

$(DEBUGOBJDIR)/MatrixRUT.obj: .././Math/LinearAlgebra/General/MatrixRUT.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MatrixRUT.obj .././Math/LinearAlgebra/General/MatrixRUT.cc

$(OPTOBJDIR)/MatrixRS.obj: .././Math/LinearAlgebra/General/MatrixRS.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MatrixRS.obj .././Math/LinearAlgebra/General/MatrixRS.cc

$(DEBUGOBJDIR)/MatrixRS.obj: .././Math/LinearAlgebra/General/MatrixRS.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MatrixRS.obj .././Math/LinearAlgebra/General/MatrixRS.cc

$(OPTOBJDIR)/Vector.obj: .././Math/LinearAlgebra/General/Vector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Vector.obj .././Math/LinearAlgebra/General/Vector.cc

$(DEBUGOBJDIR)/Vector.obj: .././Math/LinearAlgebra/General/Vector.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Vector.obj .././Math/LinearAlgebra/General/Vector.cc

$(OPTOBJDIR)/MatrixNearSingular.obj: .././Math/LinearAlgebra/General/MatrixNearSingular.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MatrixNearSingular.obj .././Math/LinearAlgebra/General/MatrixNearSingular.cc

$(DEBUGOBJDIR)/MatrixNearSingular.obj: .././Math/LinearAlgebra/General/MatrixNearSingular.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MatrixNearSingular.obj .././Math/LinearAlgebra/General/MatrixNearSingular.cc

$(OPTOBJDIR)/LeastSquares.obj: .././Math/LinearAlgebra/General/LeastSquares.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LeastSquares.obj .././Math/LinearAlgebra/General/LeastSquares.cc

$(DEBUGOBJDIR)/LeastSquares.obj: .././Math/LinearAlgebra/General/LeastSquares.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LeastSquares.obj .././Math/LinearAlgebra/General/LeastSquares.cc

$(OPTOBJDIR)/VectorMatrix.obj: .././Math/LinearAlgebra/General/VectorMatrix.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/VectorMatrix.obj .././Math/LinearAlgebra/General/VectorMatrix.cc

$(DEBUGOBJDIR)/VectorMatrix.obj: .././Math/LinearAlgebra/General/VectorMatrix.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/VectorMatrix.obj .././Math/LinearAlgebra/General/VectorMatrix.cc

$(OPTOBJDIR)/MatrixRandom.obj: .././Math/LinearAlgebra/General/MatrixRandom.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MatrixRandom.obj .././Math/LinearAlgebra/General/MatrixRandom.cc

$(DEBUGOBJDIR)/MatrixRandom.obj: .././Math/LinearAlgebra/General/MatrixRandom.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MatrixRandom.obj .././Math/LinearAlgebra/General/MatrixRandom.cc

$(OPTOBJDIR)/MatrixDeterminant.obj: .././Math/LinearAlgebra/General/MatrixDeterminant.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MatrixDeterminant.obj .././Math/LinearAlgebra/General/MatrixDeterminant.cc

$(DEBUGOBJDIR)/MatrixDeterminant.obj: .././Math/LinearAlgebra/General/MatrixDeterminant.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MatrixDeterminant.obj .././Math/LinearAlgebra/General/MatrixDeterminant.cc

$(OPTOBJDIR)/MatrixLUDecomposition.obj: .././Math/LinearAlgebra/General/MatrixLUDecomposition.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MatrixLUDecomposition.obj .././Math/LinearAlgebra/General/MatrixLUDecomposition.cc

$(DEBUGOBJDIR)/MatrixLUDecomposition.obj: .././Math/LinearAlgebra/General/MatrixLUDecomposition.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MatrixLUDecomposition.obj .././Math/LinearAlgebra/General/MatrixLUDecomposition.cc

$(OPTOBJDIR)/TSMatrixSparse.obj: .././Math/LinearAlgebra/General/TSMatrixSparse.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TSMatrixSparse.obj .././Math/LinearAlgebra/General/TSMatrixSparse.cc

$(DEBUGOBJDIR)/TSMatrixSparse.obj: .././Math/LinearAlgebra/General/TSMatrixSparse.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TSMatrixSparse.obj .././Math/LinearAlgebra/General/TSMatrixSparse.cc

$(OPTOBJDIR)/SMatrix.obj: .././Math/LinearAlgebra/General/SMatrix.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SMatrix.obj .././Math/LinearAlgebra/General/SMatrix.cc

$(DEBUGOBJDIR)/SMatrix.obj: .././Math/LinearAlgebra/General/SMatrix.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SMatrix.obj .././Math/LinearAlgebra/General/SMatrix.cc

$(OPTOBJDIR)/RawMatrix.obj: .././Math/LinearAlgebra/General/RawMatrix.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RawMatrix.obj .././Math/LinearAlgebra/General/RawMatrix.cc

$(DEBUGOBJDIR)/RawMatrix.obj: .././Math/LinearAlgebra/General/RawMatrix.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RawMatrix.obj .././Math/LinearAlgebra/General/RawMatrix.cc

$(OPTOBJDIR)/FastMatrixEigen.obj: .././Math/LinearAlgebra/General/FastMatrixEigen.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FastMatrixEigen.obj .././Math/LinearAlgebra/General/FastMatrixEigen.cc

$(DEBUGOBJDIR)/FastMatrixEigen.obj: .././Math/LinearAlgebra/General/FastMatrixEigen.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FastMatrixEigen.obj .././Math/LinearAlgebra/General/FastMatrixEigen.cc

$(OPTOBJDIR)/Vector2d.obj: .././Math/LinearAlgebra/FixedSize/Vector2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Vector2d.obj .././Math/LinearAlgebra/FixedSize/Vector2d.cc

$(DEBUGOBJDIR)/Vector2d.obj: .././Math/LinearAlgebra/FixedSize/Vector2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Vector2d.obj .././Math/LinearAlgebra/FixedSize/Vector2d.cc

$(OPTOBJDIR)/Matrix3d.obj: .././Math/LinearAlgebra/FixedSize/Matrix3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Matrix3d.obj .././Math/LinearAlgebra/FixedSize/Matrix3d.cc

$(DEBUGOBJDIR)/Matrix3d.obj: .././Math/LinearAlgebra/FixedSize/Matrix3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Matrix3d.obj .././Math/LinearAlgebra/FixedSize/Matrix3d.cc

$(OPTOBJDIR)/VectorMatrix2d.obj: .././Math/LinearAlgebra/FixedSize/VectorMatrix2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/VectorMatrix2d.obj .././Math/LinearAlgebra/FixedSize/VectorMatrix2d.cc

$(DEBUGOBJDIR)/VectorMatrix2d.obj: .././Math/LinearAlgebra/FixedSize/VectorMatrix2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/VectorMatrix2d.obj .././Math/LinearAlgebra/FixedSize/VectorMatrix2d.cc

$(OPTOBJDIR)/VectorMatrix3d.obj: .././Math/LinearAlgebra/FixedSize/VectorMatrix3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/VectorMatrix3d.obj .././Math/LinearAlgebra/FixedSize/VectorMatrix3d.cc

$(DEBUGOBJDIR)/VectorMatrix3d.obj: .././Math/LinearAlgebra/FixedSize/VectorMatrix3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/VectorMatrix3d.obj .././Math/LinearAlgebra/FixedSize/VectorMatrix3d.cc

$(OPTOBJDIR)/VectorMatrix4d.obj: .././Math/LinearAlgebra/FixedSize/VectorMatrix4d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/VectorMatrix4d.obj .././Math/LinearAlgebra/FixedSize/VectorMatrix4d.cc

$(DEBUGOBJDIR)/VectorMatrix4d.obj: .././Math/LinearAlgebra/FixedSize/VectorMatrix4d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/VectorMatrix4d.obj .././Math/LinearAlgebra/FixedSize/VectorMatrix4d.cc

$(OPTOBJDIR)/Matrix2d.obj: .././Math/LinearAlgebra/FixedSize/Matrix2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Matrix2d.obj .././Math/LinearAlgebra/FixedSize/Matrix2d.cc

$(DEBUGOBJDIR)/Matrix2d.obj: .././Math/LinearAlgebra/FixedSize/Matrix2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Matrix2d.obj .././Math/LinearAlgebra/FixedSize/Matrix2d.cc

$(OPTOBJDIR)/LineABC2d.obj: .././Math/Geometry/Euclidean/2D/LineABC2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LineABC2d.obj .././Math/Geometry/Euclidean/2D/LineABC2d.cc

$(DEBUGOBJDIR)/LineABC2d.obj: .././Math/Geometry/Euclidean/2D/LineABC2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LineABC2d.obj .././Math/Geometry/Euclidean/2D/LineABC2d.cc

$(OPTOBJDIR)/Curve2d.obj: .././Math/Geometry/Euclidean/2D/Curve2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Curve2d.obj .././Math/Geometry/Euclidean/2D/Curve2d.cc

$(DEBUGOBJDIR)/Curve2d.obj: .././Math/Geometry/Euclidean/2D/Curve2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Curve2d.obj .././Math/Geometry/Euclidean/2D/Curve2d.cc

$(OPTOBJDIR)/Curve2dLine.obj: .././Math/Geometry/Euclidean/2D/Curve2dLine.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Curve2dLine.obj .././Math/Geometry/Euclidean/2D/Curve2dLine.cc

$(DEBUGOBJDIR)/Curve2dLine.obj: .././Math/Geometry/Euclidean/2D/Curve2dLine.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Curve2dLine.obj .././Math/Geometry/Euclidean/2D/Curve2dLine.cc

$(OPTOBJDIR)/Curve2dLineFit.obj: .././Math/Geometry/Euclidean/2D/Curve2dLineFit.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Curve2dLineFit.obj .././Math/Geometry/Euclidean/2D/Curve2dLineFit.cc

$(DEBUGOBJDIR)/Curve2dLineFit.obj: .././Math/Geometry/Euclidean/2D/Curve2dLineFit.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Curve2dLineFit.obj .././Math/Geometry/Euclidean/2D/Curve2dLineFit.cc

$(OPTOBJDIR)/Curve2dLineSegment.obj: .././Math/Geometry/Euclidean/2D/Curve2dLineSegment.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Curve2dLineSegment.obj .././Math/Geometry/Euclidean/2D/Curve2dLineSegment.cc

$(DEBUGOBJDIR)/Curve2dLineSegment.obj: .././Math/Geometry/Euclidean/2D/Curve2dLineSegment.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Curve2dLineSegment.obj .././Math/Geometry/Euclidean/2D/Curve2dLineSegment.cc

$(OPTOBJDIR)/Line2dIter.obj: .././Math/Geometry/Euclidean/2D/Line2dIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Line2dIter.obj .././Math/Geometry/Euclidean/2D/Line2dIter.cc

$(DEBUGOBJDIR)/Line2dIter.obj: .././Math/Geometry/Euclidean/2D/Line2dIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Line2dIter.obj .././Math/Geometry/Euclidean/2D/Line2dIter.cc

$(OPTOBJDIR)/Affine2d.obj: .././Math/Geometry/Euclidean/2D/Affine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Affine2d.obj .././Math/Geometry/Euclidean/2D/Affine2d.cc

$(DEBUGOBJDIR)/Affine2d.obj: .././Math/Geometry/Euclidean/2D/Affine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Affine2d.obj .././Math/Geometry/Euclidean/2D/Affine2d.cc

$(OPTOBJDIR)/Moments2d2.obj: .././Math/Geometry/Euclidean/2D/Moments2d2.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Moments2d2.obj .././Math/Geometry/Euclidean/2D/Moments2d2.cc

$(DEBUGOBJDIR)/Moments2d2.obj: .././Math/Geometry/Euclidean/2D/Moments2d2.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Moments2d2.obj .././Math/Geometry/Euclidean/2D/Moments2d2.cc

$(OPTOBJDIR)/LinePP2d.obj: .././Math/Geometry/Euclidean/2D/LinePP2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LinePP2d.obj .././Math/Geometry/Euclidean/2D/LinePP2d.cc

$(DEBUGOBJDIR)/LinePP2d.obj: .././Math/Geometry/Euclidean/2D/LinePP2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LinePP2d.obj .././Math/Geometry/Euclidean/2D/LinePP2d.cc

$(OPTOBJDIR)/Projection2d.obj: .././Math/Geometry/Euclidean/2D/Projection2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Projection2d.obj .././Math/Geometry/Euclidean/2D/Projection2d.cc

$(DEBUGOBJDIR)/Projection2d.obj: .././Math/Geometry/Euclidean/2D/Projection2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Projection2d.obj .././Math/Geometry/Euclidean/2D/Projection2d.cc

$(OPTOBJDIR)/Point2d.obj: .././Math/Geometry/Euclidean/2D/Point2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Point2d.obj .././Math/Geometry/Euclidean/2D/Point2d.cc

$(DEBUGOBJDIR)/Point2d.obj: .././Math/Geometry/Euclidean/2D/Point2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Point2d.obj .././Math/Geometry/Euclidean/2D/Point2d.cc

$(OPTOBJDIR)/PointSet2d.obj: .././Math/Geometry/Euclidean/2D/PointSet2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PointSet2d.obj .././Math/Geometry/Euclidean/2D/PointSet2d.cc

$(DEBUGOBJDIR)/PointSet2d.obj: .././Math/Geometry/Euclidean/2D/PointSet2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PointSet2d.obj .././Math/Geometry/Euclidean/2D/PointSet2d.cc

$(OPTOBJDIR)/Polygon2d.obj: .././Math/Geometry/Euclidean/2D/Polygon2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Polygon2d.obj .././Math/Geometry/Euclidean/2D/Polygon2d.cc

$(DEBUGOBJDIR)/Polygon2d.obj: .././Math/Geometry/Euclidean/2D/Polygon2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Polygon2d.obj .././Math/Geometry/Euclidean/2D/Polygon2d.cc

$(OPTOBJDIR)/Circle2d.obj: .././Math/Geometry/Euclidean/2D/Circle2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Circle2d.obj .././Math/Geometry/Euclidean/2D/Circle2d.cc

$(DEBUGOBJDIR)/Circle2d.obj: .././Math/Geometry/Euclidean/2D/Circle2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Circle2d.obj .././Math/Geometry/Euclidean/2D/Circle2d.cc

$(OPTOBJDIR)/FitCircle2d.obj: .././Math/Geometry/Euclidean/2D/FitCircle2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FitCircle2d.obj .././Math/Geometry/Euclidean/2D/FitCircle2d.cc

$(DEBUGOBJDIR)/FitCircle2d.obj: .././Math/Geometry/Euclidean/2D/FitCircle2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FitCircle2d.obj .././Math/Geometry/Euclidean/2D/FitCircle2d.cc

$(OPTOBJDIR)/Arc2d.obj: .././Math/Geometry/Euclidean/2D/Arc2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Arc2d.obj .././Math/Geometry/Euclidean/2D/Arc2d.cc

$(DEBUGOBJDIR)/Arc2d.obj: .././Math/Geometry/Euclidean/2D/Arc2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Arc2d.obj .././Math/Geometry/Euclidean/2D/Arc2d.cc

$(OPTOBJDIR)/Curve2dCircle.obj: .././Math/Geometry/Euclidean/2D/Curve2dCircle.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Curve2dCircle.obj .././Math/Geometry/Euclidean/2D/Curve2dCircle.cc

$(DEBUGOBJDIR)/Curve2dCircle.obj: .././Math/Geometry/Euclidean/2D/Curve2dCircle.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Curve2dCircle.obj .././Math/Geometry/Euclidean/2D/Curve2dCircle.cc

$(OPTOBJDIR)/Curve2dArc.obj: .././Math/Geometry/Euclidean/2D/Curve2dArc.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Curve2dArc.obj .././Math/Geometry/Euclidean/2D/Curve2dArc.cc

$(DEBUGOBJDIR)/Curve2dArc.obj: .././Math/Geometry/Euclidean/2D/Curve2dArc.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Curve2dArc.obj .././Math/Geometry/Euclidean/2D/Curve2dArc.cc

$(OPTOBJDIR)/FitLineABC2d.obj: .././Math/Geometry/Euclidean/2D/FitLineABC2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FitLineABC2d.obj .././Math/Geometry/Euclidean/2D/FitLineABC2d.cc

$(DEBUGOBJDIR)/FitLineABC2d.obj: .././Math/Geometry/Euclidean/2D/FitLineABC2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FitLineABC2d.obj .././Math/Geometry/Euclidean/2D/FitLineABC2d.cc

$(OPTOBJDIR)/ConvexHullOfPointSet.obj: .././Math/Geometry/Euclidean/2D/ConvexHullOfPointSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ConvexHullOfPointSet.obj .././Math/Geometry/Euclidean/2D/ConvexHullOfPointSet.cc

$(DEBUGOBJDIR)/ConvexHullOfPointSet.obj: .././Math/Geometry/Euclidean/2D/ConvexHullOfPointSet.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ConvexHullOfPointSet.obj .././Math/Geometry/Euclidean/2D/ConvexHullOfPointSet.cc

$(OPTOBJDIR)/HEMesh2d.obj: .././Math/Geometry/Euclidean/2D/HEMesh2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HEMesh2d.obj .././Math/Geometry/Euclidean/2D/HEMesh2d.cc

$(DEBUGOBJDIR)/HEMesh2d.obj: .././Math/Geometry/Euclidean/2D/HEMesh2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HEMesh2d.obj .././Math/Geometry/Euclidean/2D/HEMesh2d.cc

$(OPTOBJDIR)/DelaunayTriangulation2d.obj: .././Math/Geometry/Euclidean/2D/DelaunayTriangulation2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/DelaunayTriangulation2d.obj .././Math/Geometry/Euclidean/2D/DelaunayTriangulation2d.cc

$(DEBUGOBJDIR)/DelaunayTriangulation2d.obj: .././Math/Geometry/Euclidean/2D/DelaunayTriangulation2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/DelaunayTriangulation2d.obj .././Math/Geometry/Euclidean/2D/DelaunayTriangulation2d.cc

$(OPTOBJDIR)/TriMesh2d.obj: .././Math/Geometry/Euclidean/2D/TriMesh2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/TriMesh2d.obj .././Math/Geometry/Euclidean/2D/TriMesh2d.cc

$(DEBUGOBJDIR)/TriMesh2d.obj: .././Math/Geometry/Euclidean/2D/TriMesh2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/TriMesh2d.obj .././Math/Geometry/Euclidean/2D/TriMesh2d.cc

$(OPTOBJDIR)/AffineTransformPolygon2d.obj: .././Math/Geometry/Euclidean/2D/AffineTransformPolygon2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AffineTransformPolygon2d.obj .././Math/Geometry/Euclidean/2D/AffineTransformPolygon2d.cc

$(DEBUGOBJDIR)/AffineTransformPolygon2d.obj: .././Math/Geometry/Euclidean/2D/AffineTransformPolygon2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AffineTransformPolygon2d.obj .././Math/Geometry/Euclidean/2D/AffineTransformPolygon2d.cc

$(OPTOBJDIR)/ProjectiveTransformPolygon2d.obj: .././Math/Geometry/Euclidean/2D/ProjectiveTransformPolygon2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ProjectiveTransformPolygon2d.obj .././Math/Geometry/Euclidean/2D/ProjectiveTransformPolygon2d.cc

$(DEBUGOBJDIR)/ProjectiveTransformPolygon2d.obj: .././Math/Geometry/Euclidean/2D/ProjectiveTransformPolygon2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ProjectiveTransformPolygon2d.obj .././Math/Geometry/Euclidean/2D/ProjectiveTransformPolygon2d.cc

$(OPTOBJDIR)/Conic2d.obj: .././Math/Geometry/Euclidean/2D/Conic2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Conic2d.obj .././Math/Geometry/Euclidean/2D/Conic2d.cc

$(DEBUGOBJDIR)/Conic2d.obj: .././Math/Geometry/Euclidean/2D/Conic2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Conic2d.obj .././Math/Geometry/Euclidean/2D/Conic2d.cc

$(OPTOBJDIR)/Ellipse2d.obj: .././Math/Geometry/Euclidean/2D/Ellipse2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Ellipse2d.obj .././Math/Geometry/Euclidean/2D/Ellipse2d.cc

$(DEBUGOBJDIR)/Ellipse2d.obj: .././Math/Geometry/Euclidean/2D/Ellipse2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Ellipse2d.obj .././Math/Geometry/Euclidean/2D/Ellipse2d.cc

$(OPTOBJDIR)/ScanPolygon2d.obj: .././Math/Geometry/Euclidean/2D/ScanPolygon2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ScanPolygon2d.obj .././Math/Geometry/Euclidean/2D/ScanPolygon2d.cc

$(DEBUGOBJDIR)/ScanPolygon2d.obj: .././Math/Geometry/Euclidean/2D/ScanPolygon2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ScanPolygon2d.obj .././Math/Geometry/Euclidean/2D/ScanPolygon2d.cc

$(OPTOBJDIR)/PolyLine2d.obj: .././Math/Geometry/Euclidean/2D/PolyLine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PolyLine2d.obj .././Math/Geometry/Euclidean/2D/PolyLine2d.cc

$(DEBUGOBJDIR)/PolyLine2d.obj: .././Math/Geometry/Euclidean/2D/PolyLine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PolyLine2d.obj .././Math/Geometry/Euclidean/2D/PolyLine2d.cc

$(OPTOBJDIR)/Poly2dApprox.obj: .././Math/Geometry/Euclidean/2D/Poly2dApprox.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Poly2dApprox.obj .././Math/Geometry/Euclidean/2D/Poly2dApprox.cc

$(DEBUGOBJDIR)/Poly2dApprox.obj: .././Math/Geometry/Euclidean/2D/Poly2dApprox.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Poly2dApprox.obj .././Math/Geometry/Euclidean/2D/Poly2dApprox.cc

$(OPTOBJDIR)/LinePP3d.obj: .././Math/Geometry/Euclidean/3D/LinePP3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LinePP3d.obj .././Math/Geometry/Euclidean/3D/LinePP3d.cc

$(DEBUGOBJDIR)/LinePP3d.obj: .././Math/Geometry/Euclidean/3D/LinePP3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LinePP3d.obj .././Math/Geometry/Euclidean/3D/LinePP3d.cc

$(OPTOBJDIR)/LinePV3d.obj: .././Math/Geometry/Euclidean/3D/LinePV3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/LinePV3d.obj .././Math/Geometry/Euclidean/3D/LinePV3d.cc

$(DEBUGOBJDIR)/LinePV3d.obj: .././Math/Geometry/Euclidean/3D/LinePV3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/LinePV3d.obj .././Math/Geometry/Euclidean/3D/LinePV3d.cc

$(OPTOBJDIR)/PlaneABCD3d.obj: .././Math/Geometry/Euclidean/3D/PlaneABCD3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PlaneABCD3d.obj .././Math/Geometry/Euclidean/3D/PlaneABCD3d.cc

$(DEBUGOBJDIR)/PlaneABCD3d.obj: .././Math/Geometry/Euclidean/3D/PlaneABCD3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PlaneABCD3d.obj .././Math/Geometry/Euclidean/3D/PlaneABCD3d.cc

$(OPTOBJDIR)/PlanePVV3d.obj: .././Math/Geometry/Euclidean/3D/PlanePVV3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PlanePVV3d.obj .././Math/Geometry/Euclidean/3D/PlanePVV3d.cc

$(DEBUGOBJDIR)/PlanePVV3d.obj: .././Math/Geometry/Euclidean/3D/PlanePVV3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PlanePVV3d.obj .././Math/Geometry/Euclidean/3D/PlanePVV3d.cc

$(OPTOBJDIR)/Quatern3d.obj: .././Math/Geometry/Euclidean/3D/Quatern3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Quatern3d.obj .././Math/Geometry/Euclidean/3D/Quatern3d.cc

$(DEBUGOBJDIR)/Quatern3d.obj: .././Math/Geometry/Euclidean/3D/Quatern3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Quatern3d.obj .././Math/Geometry/Euclidean/3D/Quatern3d.cc

$(OPTOBJDIR)/RigidTransform3d.obj: .././Math/Geometry/Euclidean/3D/RigidTransform3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RigidTransform3d.obj .././Math/Geometry/Euclidean/3D/RigidTransform3d.cc

$(DEBUGOBJDIR)/RigidTransform3d.obj: .././Math/Geometry/Euclidean/3D/RigidTransform3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RigidTransform3d.obj .././Math/Geometry/Euclidean/3D/RigidTransform3d.cc

$(OPTOBJDIR)/EulerAngle.obj: .././Math/Geometry/Euclidean/3D/EulerAngle.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/EulerAngle.obj .././Math/Geometry/Euclidean/3D/EulerAngle.cc

$(DEBUGOBJDIR)/EulerAngle.obj: .././Math/Geometry/Euclidean/3D/EulerAngle.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/EulerAngle.obj .././Math/Geometry/Euclidean/3D/EulerAngle.cc

$(OPTOBJDIR)/AxisAngle.obj: .././Math/Geometry/Euclidean/3D/AxisAngle.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/AxisAngle.obj .././Math/Geometry/Euclidean/3D/AxisAngle.cc

$(DEBUGOBJDIR)/AxisAngle.obj: .././Math/Geometry/Euclidean/3D/AxisAngle.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/AxisAngle.obj .././Math/Geometry/Euclidean/3D/AxisAngle.cc

$(OPTOBJDIR)/PointSet3d.obj: .././Math/Geometry/Euclidean/3D/PointSet3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PointSet3d.obj .././Math/Geometry/Euclidean/3D/PointSet3d.cc

$(DEBUGOBJDIR)/PointSet3d.obj: .././Math/Geometry/Euclidean/3D/PointSet3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PointSet3d.obj .././Math/Geometry/Euclidean/3D/PointSet3d.cc

$(OPTOBJDIR)/HEMesh3d.obj: .././Math/Geometry/Euclidean/3D/HEMesh3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/HEMesh3d.obj .././Math/Geometry/Euclidean/3D/HEMesh3d.cc

$(DEBUGOBJDIR)/HEMesh3d.obj: .././Math/Geometry/Euclidean/3D/HEMesh3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/HEMesh3d.obj .././Math/Geometry/Euclidean/3D/HEMesh3d.cc

$(OPTOBJDIR)/Affine3d.obj: .././Math/Geometry/Euclidean/3D/Affine3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Affine3d.obj .././Math/Geometry/Euclidean/3D/Affine3d.cc

$(DEBUGOBJDIR)/Affine3d.obj: .././Math/Geometry/Euclidean/3D/Affine3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Affine3d.obj .././Math/Geometry/Euclidean/3D/Affine3d.cc

$(OPTOBJDIR)/FitPlaneABCD3d.obj: .././Math/Geometry/Euclidean/3D/FitPlaneABCD3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FitPlaneABCD3d.obj .././Math/Geometry/Euclidean/3D/FitPlaneABCD3d.cc

$(DEBUGOBJDIR)/FitPlaneABCD3d.obj: .././Math/Geometry/Euclidean/3D/FitPlaneABCD3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FitPlaneABCD3d.obj .././Math/Geometry/Euclidean/3D/FitPlaneABCD3d.cc

$(OPTOBJDIR)/FitPlanePVV3d.obj: .././Math/Geometry/Euclidean/3D/FitPlanePVV3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FitPlanePVV3d.obj .././Math/Geometry/Euclidean/3D/FitPlanePVV3d.cc

$(DEBUGOBJDIR)/FitPlanePVV3d.obj: .././Math/Geometry/Euclidean/3D/FitPlanePVV3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FitPlanePVV3d.obj .././Math/Geometry/Euclidean/3D/FitPlanePVV3d.cc

$(OPTOBJDIR)/CrackCode.obj: .././Math/Geometry/Euclidean/Boundary/CrackCode.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CrackCode.obj .././Math/Geometry/Euclidean/Boundary/CrackCode.cc

$(DEBUGOBJDIR)/CrackCode.obj: .././Math/Geometry/Euclidean/Boundary/CrackCode.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CrackCode.obj .././Math/Geometry/Euclidean/Boundary/CrackCode.cc

$(OPTOBJDIR)/BVertex.obj: .././Math/Geometry/Euclidean/Boundary/BVertex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/BVertex.obj .././Math/Geometry/Euclidean/Boundary/BVertex.cc

$(DEBUGOBJDIR)/BVertex.obj: .././Math/Geometry/Euclidean/Boundary/BVertex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/BVertex.obj .././Math/Geometry/Euclidean/Boundary/BVertex.cc

$(OPTOBJDIR)/Crack.obj: .././Math/Geometry/Euclidean/Boundary/Crack.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Crack.obj .././Math/Geometry/Euclidean/Boundary/Crack.cc

$(DEBUGOBJDIR)/Crack.obj: .././Math/Geometry/Euclidean/Boundary/Crack.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Crack.obj .././Math/Geometry/Euclidean/Boundary/Crack.cc

$(OPTOBJDIR)/Boundary.obj: .././Math/Geometry/Euclidean/Boundary/Boundary.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Boundary.obj .././Math/Geometry/Euclidean/Boundary/Boundary.cc

$(DEBUGOBJDIR)/Boundary.obj: .././Math/Geometry/Euclidean/Boundary/Boundary.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Boundary.obj .././Math/Geometry/Euclidean/Boundary/Boundary.cc

$(OPTOBJDIR)/ConvexHull.obj: .././Math/Geometry/Euclidean/Boundary/ConvexHull.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ConvexHull.obj .././Math/Geometry/Euclidean/Boundary/ConvexHull.cc

$(DEBUGOBJDIR)/ConvexHull.obj: .././Math/Geometry/Euclidean/Boundary/ConvexHull.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ConvexHull.obj .././Math/Geometry/Euclidean/Boundary/ConvexHull.cc

$(OPTOBJDIR)/Edge.obj: .././Math/Geometry/Euclidean/Boundary/Edge.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Edge.obj .././Math/Geometry/Euclidean/Boundary/Edge.cc

$(DEBUGOBJDIR)/Edge.obj: .././Math/Geometry/Euclidean/Boundary/Edge.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Edge.obj .././Math/Geometry/Euclidean/Boundary/Edge.cc

$(OPTOBJDIR)/PPoint1d.obj: .././Math/Geometry/Projective/1D/PPoint1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PPoint1d.obj .././Math/Geometry/Projective/1D/PPoint1d.cc

$(DEBUGOBJDIR)/PPoint1d.obj: .././Math/Geometry/Projective/1D/PPoint1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PPoint1d.obj .././Math/Geometry/Projective/1D/PPoint1d.cc

$(OPTOBJDIR)/PProjection1d.obj: .././Math/Geometry/Projective/1D/PProjection1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PProjection1d.obj .././Math/Geometry/Projective/1D/PProjection1d.cc

$(DEBUGOBJDIR)/PProjection1d.obj: .././Math/Geometry/Projective/1D/PProjection1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PProjection1d.obj .././Math/Geometry/Projective/1D/PProjection1d.cc

$(OPTOBJDIR)/PPointLine2d.obj: .././Math/Geometry/Projective/2D/PPointLine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PPointLine2d.obj .././Math/Geometry/Projective/2D/PPointLine2d.cc

$(DEBUGOBJDIR)/PPointLine2d.obj: .././Math/Geometry/Projective/2D/PPointLine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PPointLine2d.obj .././Math/Geometry/Projective/2D/PPointLine2d.cc

$(OPTOBJDIR)/PPoint2d.obj: .././Math/Geometry/Projective/2D/PPoint2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PPoint2d.obj .././Math/Geometry/Projective/2D/PPoint2d.cc

$(DEBUGOBJDIR)/PPoint2d.obj: .././Math/Geometry/Projective/2D/PPoint2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PPoint2d.obj .././Math/Geometry/Projective/2D/PPoint2d.cc

$(OPTOBJDIR)/PLine2d.obj: .././Math/Geometry/Projective/2D/PLine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PLine2d.obj .././Math/Geometry/Projective/2D/PLine2d.cc

$(DEBUGOBJDIR)/PLine2d.obj: .././Math/Geometry/Projective/2D/PLine2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PLine2d.obj .././Math/Geometry/Projective/2D/PLine2d.cc

$(OPTOBJDIR)/PLinePP2d.obj: .././Math/Geometry/Projective/2D/PLinePP2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PLinePP2d.obj .././Math/Geometry/Projective/2D/PLinePP2d.cc

$(DEBUGOBJDIR)/PLinePP2d.obj: .././Math/Geometry/Projective/2D/PLinePP2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PLinePP2d.obj .././Math/Geometry/Projective/2D/PLinePP2d.cc

$(OPTOBJDIR)/PProjection2d.obj: .././Math/Geometry/Projective/2D/PProjection2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PProjection2d.obj .././Math/Geometry/Projective/2D/PProjection2d.cc

$(DEBUGOBJDIR)/PProjection2d.obj: .././Math/Geometry/Projective/2D/PProjection2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PProjection2d.obj .././Math/Geometry/Projective/2D/PProjection2d.cc

$(OPTOBJDIR)/PPerspective2d.obj: .././Math/Geometry/Projective/2D/PPerspective2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PPerspective2d.obj .././Math/Geometry/Projective/2D/PPerspective2d.cc

$(DEBUGOBJDIR)/PPerspective2d.obj: .././Math/Geometry/Projective/2D/PPerspective2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PPerspective2d.obj .././Math/Geometry/Projective/2D/PPerspective2d.cc

$(OPTOBJDIR)/FundamentalMatrix2d.obj: .././Math/Geometry/Projective/2D/FundamentalMatrix2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FundamentalMatrix2d.obj .././Math/Geometry/Projective/2D/FundamentalMatrix2d.cc

$(DEBUGOBJDIR)/FundamentalMatrix2d.obj: .././Math/Geometry/Projective/2D/FundamentalMatrix2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FundamentalMatrix2d.obj .././Math/Geometry/Projective/2D/FundamentalMatrix2d.cc

$(OPTOBJDIR)/FitPProjection2d.obj: .././Math/Geometry/Projective/2D/FitPProjection2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FitPProjection2d.obj .././Math/Geometry/Projective/2D/FitPProjection2d.cc

$(DEBUGOBJDIR)/FitPProjection2d.obj: .././Math/Geometry/Projective/2D/FitPProjection2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FitPProjection2d.obj .././Math/Geometry/Projective/2D/FitPProjection2d.cc

$(OPTOBJDIR)/PPointPlane3d.obj: .././Math/Geometry/Projective/3D/PPointPlane3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PPointPlane3d.obj .././Math/Geometry/Projective/3D/PPointPlane3d.cc

$(DEBUGOBJDIR)/PPointPlane3d.obj: .././Math/Geometry/Projective/3D/PPointPlane3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PPointPlane3d.obj .././Math/Geometry/Projective/3D/PPointPlane3d.cc

$(OPTOBJDIR)/PPoint3d.obj: .././Math/Geometry/Projective/3D/PPoint3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PPoint3d.obj .././Math/Geometry/Projective/3D/PPoint3d.cc

$(DEBUGOBJDIR)/PPoint3d.obj: .././Math/Geometry/Projective/3D/PPoint3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PPoint3d.obj .././Math/Geometry/Projective/3D/PPoint3d.cc

$(OPTOBJDIR)/PPlane3d.obj: .././Math/Geometry/Projective/3D/PPlane3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PPlane3d.obj .././Math/Geometry/Projective/3D/PPlane3d.cc

$(DEBUGOBJDIR)/PPlane3d.obj: .././Math/Geometry/Projective/3D/PPlane3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PPlane3d.obj .././Math/Geometry/Projective/3D/PPlane3d.cc

$(OPTOBJDIR)/PProjection3d.obj: .././Math/Geometry/Projective/3D/PProjection3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PProjection3d.obj .././Math/Geometry/Projective/3D/PProjection3d.cc

$(DEBUGOBJDIR)/PProjection3d.obj: .././Math/Geometry/Projective/3D/PProjection3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PProjection3d.obj .././Math/Geometry/Projective/3D/PProjection3d.cc

$(OPTOBJDIR)/PPerspective3d.obj: .././Math/Geometry/Projective/3D/PPerspective3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PPerspective3d.obj .././Math/Geometry/Projective/3D/PPerspective3d.cc

$(DEBUGOBJDIR)/PPerspective3d.obj: .././Math/Geometry/Projective/3D/PPerspective3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PPerspective3d.obj .././Math/Geometry/Projective/3D/PPerspective3d.cc

$(OPTOBJDIR)/PLinePV3d.obj: .././Math/Geometry/Projective/3D/PLinePV3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PLinePV3d.obj .././Math/Geometry/Projective/3D/PLinePV3d.cc

$(DEBUGOBJDIR)/PLinePV3d.obj: .././Math/Geometry/Projective/3D/PLinePV3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PLinePV3d.obj .././Math/Geometry/Projective/3D/PLinePV3d.cc

$(OPTOBJDIR)/FitPPlane3d.obj: .././Math/Geometry/Projective/3D/FitPPlane3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FitPPlane3d.obj .././Math/Geometry/Projective/3D/FitPPlane3d.cc

$(DEBUGOBJDIR)/FitPPlane3d.obj: .././Math/Geometry/Projective/3D/FitPPlane3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FitPPlane3d.obj .././Math/Geometry/Projective/3D/FitPPlane3d.cc

$(OPTOBJDIR)/MeanVariance.obj: .././Math/Statistics/MeanCovariance/MeanVariance.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MeanVariance.obj .././Math/Statistics/MeanCovariance/MeanVariance.cc

$(DEBUGOBJDIR)/MeanVariance.obj: .././Math/Statistics/MeanCovariance/MeanVariance.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MeanVariance.obj .././Math/Statistics/MeanCovariance/MeanVariance.cc

$(OPTOBJDIR)/MeanNd.obj: .././Math/Statistics/MeanCovariance/MeanNd.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MeanNd.obj .././Math/Statistics/MeanCovariance/MeanNd.cc

$(DEBUGOBJDIR)/MeanNd.obj: .././Math/Statistics/MeanCovariance/MeanNd.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MeanNd.obj .././Math/Statistics/MeanCovariance/MeanNd.cc

$(OPTOBJDIR)/MeanCovariance.obj: .././Math/Statistics/MeanCovariance/MeanCovariance.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/MeanCovariance.obj .././Math/Statistics/MeanCovariance/MeanCovariance.cc

$(DEBUGOBJDIR)/MeanCovariance.obj: .././Math/Statistics/MeanCovariance/MeanCovariance.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/MeanCovariance.obj .././Math/Statistics/MeanCovariance/MeanCovariance.cc

$(OPTOBJDIR)/Statistics.obj: .././Math/Statistics/MeanCovariance/Statistics.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Statistics.obj .././Math/Statistics/MeanCovariance/Statistics.cc

$(DEBUGOBJDIR)/Statistics.obj: .././Math/Statistics/MeanCovariance/Statistics.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Statistics.obj .././Math/Statistics/MeanCovariance/Statistics.cc

$(OPTOBJDIR)/Mean.obj: .././Math/Statistics/MeanCovariance/Mean.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Mean.obj .././Math/Statistics/MeanCovariance/Mean.cc

$(DEBUGOBJDIR)/Mean.obj: .././Math/Statistics/MeanCovariance/Mean.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Mean.obj .././Math/Statistics/MeanCovariance/Mean.cc

$(OPTOBJDIR)/Normal.obj: .././Math/Statistics/MeanCovariance/Normal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Normal.obj .././Math/Statistics/MeanCovariance/Normal.cc

$(DEBUGOBJDIR)/Normal.obj: .././Math/Statistics/MeanCovariance/Normal.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Normal.obj .././Math/Statistics/MeanCovariance/Normal.cc

$(OPTOBJDIR)/Sums1d2.obj: .././Math/Statistics/MeanCovariance/Sums1d2.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Sums1d2.obj .././Math/Statistics/MeanCovariance/Sums1d2.cc

$(DEBUGOBJDIR)/Sums1d2.obj: .././Math/Statistics/MeanCovariance/Sums1d2.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Sums1d2.obj .././Math/Statistics/MeanCovariance/Sums1d2.cc

$(OPTOBJDIR)/SumsNd2.obj: .././Math/Statistics/MeanCovariance/SumsNd2.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SumsNd2.obj .././Math/Statistics/MeanCovariance/SumsNd2.cc

$(DEBUGOBJDIR)/SumsNd2.obj: .././Math/Statistics/MeanCovariance/SumsNd2.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SumsNd2.obj .././Math/Statistics/MeanCovariance/SumsNd2.cc

$(OPTOBJDIR)/RealHistogram1d.obj: .././Math/Statistics/Histogram/RealHistogram1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealHistogram1d.obj .././Math/Statistics/Histogram/RealHistogram1d.cc

$(DEBUGOBJDIR)/RealHistogram1d.obj: .././Math/Statistics/Histogram/RealHistogram1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealHistogram1d.obj .././Math/Statistics/Histogram/RealHistogram1d.cc

$(OPTOBJDIR)/RealHistogram2d.obj: .././Math/Statistics/Histogram/RealHistogram2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealHistogram2d.obj .././Math/Statistics/Histogram/RealHistogram2d.cc

$(DEBUGOBJDIR)/RealHistogram2d.obj: .././Math/Statistics/Histogram/RealHistogram2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealHistogram2d.obj .././Math/Statistics/Histogram/RealHistogram2d.cc

$(OPTOBJDIR)/RealHistogram3d.obj: .././Math/Statistics/Histogram/RealHistogram3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealHistogram3d.obj .././Math/Statistics/Histogram/RealHistogram3d.cc

$(DEBUGOBJDIR)/RealHistogram3d.obj: .././Math/Statistics/Histogram/RealHistogram3d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealHistogram3d.obj .././Math/Statistics/Histogram/RealHistogram3d.cc

$(OPTOBJDIR)/RealHist1dBinaryIO.obj: .././Math/Statistics/Histogram/RealHist1dBinaryIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealHist1dBinaryIO.obj .././Math/Statistics/Histogram/RealHist1dBinaryIO.cc

$(DEBUGOBJDIR)/RealHist1dBinaryIO.obj: .././Math/Statistics/Histogram/RealHist1dBinaryIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealHist1dBinaryIO.obj .././Math/Statistics/Histogram/RealHist1dBinaryIO.cc

$(OPTOBJDIR)/RealHist2dBinaryIO.obj: .././Math/Statistics/Histogram/RealHist2dBinaryIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealHist2dBinaryIO.obj .././Math/Statistics/Histogram/RealHist2dBinaryIO.cc

$(DEBUGOBJDIR)/RealHist2dBinaryIO.obj: .././Math/Statistics/Histogram/RealHist2dBinaryIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealHist2dBinaryIO.obj .././Math/Statistics/Histogram/RealHist2dBinaryIO.cc

$(OPTOBJDIR)/RealHist3dBinaryIO.obj: .././Math/Statistics/Histogram/RealHist3dBinaryIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealHist3dBinaryIO.obj .././Math/Statistics/Histogram/RealHist3dBinaryIO.cc

$(DEBUGOBJDIR)/RealHist3dBinaryIO.obj: .././Math/Statistics/Histogram/RealHist3dBinaryIO.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealHist3dBinaryIO.obj .././Math/Statistics/Histogram/RealHist3dBinaryIO.cc

$(OPTOBJDIR)/Parzen.obj: .././Math/Statistics/Histogram/Parzen.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Parzen.obj .././Math/Statistics/Histogram/Parzen.cc

$(DEBUGOBJDIR)/Parzen.obj: .././Math/Statistics/Histogram/Parzen.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Parzen.obj .././Math/Statistics/Histogram/Parzen.cc

$(OPTOBJDIR)/PrimitiveBinaryPolynomial.obj: .././Math/Sequence/PrimitiveBinaryPolynomial.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PrimitiveBinaryPolynomial.obj .././Math/Sequence/PrimitiveBinaryPolynomial.cc

$(DEBUGOBJDIR)/PrimitiveBinaryPolynomial.obj: .././Math/Sequence/PrimitiveBinaryPolynomial.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PrimitiveBinaryPolynomial.obj .././Math/Sequence/PrimitiveBinaryPolynomial.cc

$(OPTOBJDIR)/SobolSequence.obj: .././Math/Sequence/SobolSequence.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SobolSequence.obj .././Math/Sequence/SobolSequence.cc

$(DEBUGOBJDIR)/SobolSequence.obj: .././Math/Sequence/SobolSequence.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SobolSequence.obj .././Math/Sequence/SobolSequence.cc

$(OPTOBJDIR)/CircleIter.obj: .././Math/Sequence/CircleIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/CircleIter.obj .././Math/Sequence/CircleIter.cc

$(DEBUGOBJDIR)/CircleIter.obj: .././Math/Sequence/CircleIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/CircleIter.obj .././Math/Sequence/CircleIter.cc

$(OPTOBJDIR)/SquareIter.obj: .././Math/Sequence/SquareIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/SquareIter.obj .././Math/Sequence/SquareIter.cc

$(DEBUGOBJDIR)/SquareIter.obj: .././Math/Sequence/SquareIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/SquareIter.obj .././Math/Sequence/SquareIter.cc

$(OPTOBJDIR)/ZigZagIter.obj: .././Math/Sequence/ZigZagIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ZigZagIter.obj .././Math/Sequence/ZigZagIter.cc

$(DEBUGOBJDIR)/ZigZagIter.obj: .././Math/Sequence/ZigZagIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ZigZagIter.obj .././Math/Sequence/ZigZagIter.cc

$(OPTOBJDIR)/Polygon2dIter.obj: .././Math/Sequence/Polygon2dIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Polygon2dIter.obj .././Math/Sequence/Polygon2dIter.cc

$(DEBUGOBJDIR)/Polygon2dIter.obj: .././Math/Sequence/Polygon2dIter.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Polygon2dIter.obj .././Math/Sequence/Polygon2dIter.cc

$(OPTOBJDIR)/ThinPlateSpline1d.obj: .././Math/Sequence/ThinPlateSpline1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/ThinPlateSpline1d.obj .././Math/Sequence/ThinPlateSpline1d.cc

$(DEBUGOBJDIR)/ThinPlateSpline1d.obj: .././Math/Sequence/ThinPlateSpline1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/ThinPlateSpline1d.obj .././Math/Sequence/ThinPlateSpline1d.cc

$(OPTOBJDIR)/Complex.obj: .././Math/Complex/Complex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Complex.obj .././Math/Complex/Complex.cc

$(DEBUGOBJDIR)/Complex.obj: .././Math/Complex/Complex.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Complex.obj .././Math/Complex/Complex.cc

$(OPTOBJDIR)/FFT1d.obj: .././Math/Signals/1D/FFT1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FFT1d.obj .././Math/Signals/1D/FFT1d.cc

$(DEBUGOBJDIR)/FFT1d.obj: .././Math/Signals/1D/FFT1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FFT1d.obj .././Math/Signals/1D/FFT1d.cc

$(OPTOBJDIR)/PowerSpectrum1d.obj: .././Math/Signals/1D/PowerSpectrum1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/PowerSpectrum1d.obj .././Math/Signals/1D/PowerSpectrum1d.cc

$(DEBUGOBJDIR)/PowerSpectrum1d.obj: .././Math/Signals/1D/PowerSpectrum1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/PowerSpectrum1d.obj .././Math/Signals/1D/PowerSpectrum1d.cc

$(OPTOBJDIR)/Correlation1d.obj: .././Math/Signals/1D/Correlation1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/Correlation1d.obj .././Math/Signals/1D/Correlation1d.cc

$(DEBUGOBJDIR)/Correlation1d.obj: .././Math/Signals/1D/Correlation1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/Correlation1d.obj .././Math/Signals/1D/Correlation1d.cc

$(OPTOBJDIR)/RealCepstral.obj: .././Math/Signals/1D/RealCepstral.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/RealCepstral.obj .././Math/Signals/1D/RealCepstral.cc

$(DEBUGOBJDIR)/RealCepstral.obj: .././Math/Signals/1D/RealCepstral.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/RealCepstral.obj .././Math/Signals/1D/RealCepstral.cc

$(OPTOBJDIR)/GenerateSignal1d.obj: .././Math/Signals/1D/GenerateSignal1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/GenerateSignal1d.obj .././Math/Signals/1D/GenerateSignal1d.cc

$(DEBUGOBJDIR)/GenerateSignal1d.obj: .././Math/Signals/1D/GenerateSignal1d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/GenerateSignal1d.obj .././Math/Signals/1D/GenerateSignal1d.cc

$(OPTOBJDIR)/FFT2d.obj: .././Math/Signals/2D/FFT2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(OPTOBJDIR)/FFT2d.obj .././Math/Signals/2D/FFT2d.cc

$(DEBUGOBJDIR)/FFT2d.obj: .././Math/Signals/2D/FFT2d.cc 
        $(CC) $(INCLUDES) $(DEFINES) $(OPTFLAGS) /Fo$(DEBUGOBJDIR)/FFT2d.obj .././Math/Signals/2D/FFT2d.cc


