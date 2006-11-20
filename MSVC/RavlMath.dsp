# Microsoft Developer Studio Project File - Name="RavlMath" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=RavlMath - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "RavlMath.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "RavlMath.mak" CFG="RavlMath - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "RavlMath - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "RavlMath - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "C:\Build\win32\opt\lib"
# PROP Intermediate_Dir "C:\Build\win32\opt\obj\RavlMath"
# PROP Target_Dir ""
# ADD CPP /nologo /W3 /GR /GX /MD /O2  /I "C:\Build\inc\Win32\" /I "C:\Build\inc\" /D "NDEBUG" /D "_LIB" /D "VISUAL_CPP" /D "WIN32" /D "RAVL_USE_GTK2" /D "_MBCS" /YX /FD /TP /c
# ADD BASE RSC /l 0x809
# ADD RSC /l 0x809 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "C:\Build\win32\debug\lib"
# PROP Intermediate_Dir "C:\Build\win32\debug\obj\RavlMath"
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

# Name "RavlMath - Win32 Release"
# Name "RavlMath - Win32 Debug"

# Begin Group "Source Files"
# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"


# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TMatrix.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\Matrix.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixInverse.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixSVD.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixEigen.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixSolve.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixRUT.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixRS.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\Vector.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixNearSingular.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\LeastSquares.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\VectorMatrix.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixRandom.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixDeterminant.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixLUDecomposition.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TSMatrixSparse.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\SMatrix.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\RawMatrix.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\Vector2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\Matrix3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\VectorMatrix2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\VectorMatrix3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\VectorMatrix4d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\Matrix2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\LineABC2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Curve2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Curve2dLine.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Curve2dLineFit.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Curve2dLineSegment.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Line2dIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Affine2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Moments2d2.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\LinePP2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Projection2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Point2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\PointSet2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Polygon2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Circle2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\FitCircle2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Arc2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Curve2dCircle.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Curve2dArc.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\FitLineABC2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\ConvexHullOfPointSet.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\HEMesh2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\DelaunayTriangulation2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\TriMesh2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\AffineTransformPolygon2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\ProjectiveTransformPolygon2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Conic2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Ellipse2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\ScanPolygon2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\PolyLine2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Poly2dApprox.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\LinePP3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\LinePV3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\PlaneABCD3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\PlanePVV3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\Quatern3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\RigidTransform3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\EulerAngle.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\AxisAngle.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\PointSet3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\HEMesh3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\Boundary\CrackCode.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\Boundary\BVertex.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\Boundary\Crack.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\Boundary\Boundary.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\Boundary\ConvexHull.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\Boundary\Edge.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\1D\PPoint1d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\1D\PProjection1d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\PPointLine2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\PPoint2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\PLine2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\PLinePP2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\PProjection2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\PPerspective2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\FundamentalMatrix2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\FitPProjection2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\3D\PPointPlane3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\3D\PPoint3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\3D\PPlane3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\3D\PProjection3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\3D\PPerspective3d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\MeanVariance.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\MeanNd.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\MeanCovariance.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\Statistics.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\Mean.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\Normal.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\Sums1d2.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\SumsNd2.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\Histogram\RealHistogram1d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\Histogram\RealHistogram2d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\Histogram\RealHist1dBinaryIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\Histogram\RealHist2dBinaryIO.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\PrimitiveBinaryPolynomial.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\SobolSequence.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\CircleIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\SquareIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\ZigZagIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\Polygon2dIter.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Complex\Complex.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\1D\FFT1d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\1D\PowerSpectrum1d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\1D\Correlation1d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\1D\RealCepstral.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\1D\GenerateSignal1d.cc
# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\2D\FFT2d.cc
# End Source File


# End Group

# Begin Group "Header Files"
# PROP Default_Filter "h;hpp;hxx;hm;inl"


# Begin Source File
SOURCE=..\.\Math\CCMath\CCMath.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header CCMath.hh

"C:\Build\inc\Ravl\CCMath.hh" :  "" ""
	copy ..\.\Math\CCMath\CCMath.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header CCMath.hh

"C:\Build\inc\Ravl\CCMath.hh" :  "" ""
	copy ..\.\Math\CCMath\CCMath.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TVector.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TVector.hh

"C:\Build\inc\Ravl\TVector.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TVector.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TVector.hh

"C:\Build\inc\Ravl\TVector.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TVector.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TMatrix.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TMatrix.hh

"C:\Build\inc\Ravl\TMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TMatrix.hh

"C:\Build\inc\Ravl\TMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\Matrix.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Matrix.hh

"C:\Build\inc\Ravl\Matrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\Matrix.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Matrix.hh

"C:\Build\inc\Ravl\Matrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\Matrix.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\Vector.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Vector.hh

"C:\Build\inc\Ravl\Vector.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\Vector.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Vector.hh

"C:\Build\inc\Ravl\Vector.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\Vector.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixRUT.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header MatrixRUT.hh

"C:\Build\inc\Ravl\MatrixRUT.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\MatrixRUT.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header MatrixRUT.hh

"C:\Build\inc\Ravl\MatrixRUT.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\MatrixRUT.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixRS.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header MatrixRS.hh

"C:\Build\inc\Ravl\MatrixRS.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\MatrixRS.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header MatrixRS.hh

"C:\Build\inc\Ravl\MatrixRS.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\MatrixRS.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\LeastSquares.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header LeastSquares.hh

"C:\Build\inc\Ravl\LeastSquares.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\LeastSquares.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header LeastSquares.hh

"C:\Build\inc\Ravl\LeastSquares.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\LeastSquares.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\VectorMatrix.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header VectorMatrix.hh

"C:\Build\inc\Ravl\VectorMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\VectorMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header VectorMatrix.hh

"C:\Build\inc\Ravl\VectorMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\VectorMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\MatrixDecomposition.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header MatrixDecomposition.hh

"C:\Build\inc\Ravl\MatrixDecomposition.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\MatrixDecomposition.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header MatrixDecomposition.hh

"C:\Build\inc\Ravl\MatrixDecomposition.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\MatrixDecomposition.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TSMatrix.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TSMatrix.hh

"C:\Build\inc\Ravl\TSMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TSMatrix.hh

"C:\Build\inc\Ravl\TSMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TSMatrixFull.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TSMatrixFull.hh

"C:\Build\inc\Ravl\TSMatrixFull.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixFull.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TSMatrixFull.hh

"C:\Build\inc\Ravl\TSMatrixFull.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixFull.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TSMatrixPartial.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TSMatrixPartial.hh

"C:\Build\inc\Ravl\TSMatrixPartial.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixPartial.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TSMatrixPartial.hh

"C:\Build\inc\Ravl\TSMatrixPartial.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixPartial.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TSMatrixDiagonal.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TSMatrixDiagonal.hh

"C:\Build\inc\Ravl\TSMatrixDiagonal.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixDiagonal.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TSMatrixDiagonal.hh

"C:\Build\inc\Ravl\TSMatrixDiagonal.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixDiagonal.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TSMatrixRightUpper.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TSMatrixRightUpper.hh

"C:\Build\inc\Ravl\TSMatrixRightUpper.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixRightUpper.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TSMatrixRightUpper.hh

"C:\Build\inc\Ravl\TSMatrixRightUpper.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixRightUpper.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TSMatrixLeftLower.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TSMatrixLeftLower.hh

"C:\Build\inc\Ravl\TSMatrixLeftLower.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixLeftLower.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TSMatrixLeftLower.hh

"C:\Build\inc\Ravl\TSMatrixLeftLower.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixLeftLower.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TSMatrixSparse.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TSMatrixSparse.hh

"C:\Build\inc\Ravl\TSMatrixSparse.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixSparse.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TSMatrixSparse.hh

"C:\Build\inc\Ravl\TSMatrixSparse.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixSparse.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TSMatrixScaledIdentity.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TSMatrixScaledIdentity.hh

"C:\Build\inc\Ravl\TSMatrixScaledIdentity.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixScaledIdentity.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TSMatrixScaledIdentity.hh

"C:\Build\inc\Ravl\TSMatrixScaledIdentity.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixScaledIdentity.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TSMatrixSymmetric.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TSMatrixSymmetric.hh

"C:\Build\inc\Ravl\TSMatrixSymmetric.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixSymmetric.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TSMatrixSymmetric.hh

"C:\Build\inc\Ravl\TSMatrixSymmetric.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixSymmetric.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TSMatrixTranspose.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TSMatrixTranspose.hh

"C:\Build\inc\Ravl\TSMatrixTranspose.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixTranspose.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TSMatrixTranspose.hh

"C:\Build\inc\Ravl\TSMatrixTranspose.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixTranspose.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\SMatrix.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header SMatrix.hh

"C:\Build\inc\Ravl\SMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header SMatrix.hh

"C:\Build\inc\Ravl\SMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\SMatrixSparse.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header SMatrixSparse.hh

"C:\Build\inc\Ravl\SMatrixSparse.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrixSparse.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header SMatrixSparse.hh

"C:\Build\inc\Ravl\SMatrixSparse.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrixSparse.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\SMatrixSymmetric.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header SMatrixSymmetric.hh

"C:\Build\inc\Ravl\SMatrixSymmetric.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrixSymmetric.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header SMatrixSymmetric.hh

"C:\Build\inc\Ravl\SMatrixSymmetric.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrixSymmetric.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\SMatrixDiagonal.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header SMatrixDiagonal.hh

"C:\Build\inc\Ravl\SMatrixDiagonal.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrixDiagonal.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header SMatrixDiagonal.hh

"C:\Build\inc\Ravl\SMatrixDiagonal.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrixDiagonal.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\SMatrixLeftLower.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header SMatrixLeftLower.hh

"C:\Build\inc\Ravl\SMatrixLeftLower.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrixLeftLower.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header SMatrixLeftLower.hh

"C:\Build\inc\Ravl\SMatrixLeftLower.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrixLeftLower.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\SMatrixRightUpper.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header SMatrixRightUpper.hh

"C:\Build\inc\Ravl\SMatrixRightUpper.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrixRightUpper.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header SMatrixRightUpper.hh

"C:\Build\inc\Ravl\SMatrixRightUpper.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrixRightUpper.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\SMatrixScaledIdentity.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header SMatrixScaledIdentity.hh

"C:\Build\inc\Ravl\SMatrixScaledIdentity.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrixScaledIdentity.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header SMatrixScaledIdentity.hh

"C:\Build\inc\Ravl\SMatrixScaledIdentity.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SMatrixScaledIdentity.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\SVD.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header SVD.hh

"C:\Build\inc\Ravl\SVD.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SVD.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header SVD.hh

"C:\Build\inc\Ravl\SVD.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\SVD.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\RawMatrix.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header RawMatrix.hh

"C:\Build\inc\Ravl\RawMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\RawMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header RawMatrix.hh

"C:\Build\inc\Ravl\RawMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\RawMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\Eigen.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Eigen.hh

"C:\Build\inc\Ravl\Eigen.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\Eigen.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Eigen.hh

"C:\Build\inc\Ravl\Eigen.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\Eigen.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\General\TSMatrixSparseIter.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TSMatrixSparseIter.hh

"C:\Build\inc\Ravl\TSMatrixSparseIter.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixSparseIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TSMatrixSparseIter.hh

"C:\Build\inc\Ravl\TSMatrixSparseIter.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\General\TSMatrixSparseIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\FVector.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header FVector.hh

"C:\Build\inc\Ravl\FVector.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\FVector.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header FVector.hh

"C:\Build\inc\Ravl\FVector.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\FVector.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\Vector2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Vector2d.hh

"C:\Build\inc\Ravl\Vector2d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\Vector2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Vector2d.hh

"C:\Build\inc\Ravl\Vector2d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\Vector2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\Vector3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Vector3d.hh

"C:\Build\inc\Ravl\Vector3d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\Vector3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Vector3d.hh

"C:\Build\inc\Ravl\Vector3d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\Vector3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\Vector4d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Vector4d.hh

"C:\Build\inc\Ravl\Vector4d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\Vector4d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Vector4d.hh

"C:\Build\inc\Ravl\Vector4d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\Vector4d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\FMatrix.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header FMatrix.hh

"C:\Build\inc\Ravl\FMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\FMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header FMatrix.hh

"C:\Build\inc\Ravl\FMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\FMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\Matrix2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Matrix2d.hh

"C:\Build\inc\Ravl\Matrix2d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\Matrix2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Matrix2d.hh

"C:\Build\inc\Ravl\Matrix2d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\Matrix2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\Matrix3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Matrix3d.hh

"C:\Build\inc\Ravl\Matrix3d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\Matrix3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Matrix3d.hh

"C:\Build\inc\Ravl\Matrix3d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\Matrix3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\Matrix4d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Matrix4d.hh

"C:\Build\inc\Ravl\Matrix4d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\Matrix4d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Matrix4d.hh

"C:\Build\inc\Ravl\Matrix4d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\Matrix4d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\FVectorMatrix.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header FVectorMatrix.hh

"C:\Build\inc\Ravl\FVectorMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\FVectorMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header FVectorMatrix.hh

"C:\Build\inc\Ravl\FVectorMatrix.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\FVectorMatrix.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\VectorMatrix2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header VectorMatrix2d.hh

"C:\Build\inc\Ravl\VectorMatrix2d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\VectorMatrix2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header VectorMatrix2d.hh

"C:\Build\inc\Ravl\VectorMatrix2d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\VectorMatrix2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\VectorMatrix3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header VectorMatrix3d.hh

"C:\Build\inc\Ravl\VectorMatrix3d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\VectorMatrix3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header VectorMatrix3d.hh

"C:\Build\inc\Ravl\VectorMatrix3d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\VectorMatrix3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\LinearAlgebra\FixedSize\VectorMatrix4d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header VectorMatrix4d.hh

"C:\Build\inc\Ravl\VectorMatrix4d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\VectorMatrix4d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header VectorMatrix4d.hh

"C:\Build\inc\Ravl\VectorMatrix4d.hh" :  "" ""
	copy ..\.\Math\LinearAlgebra\FixedSize\VectorMatrix4d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\FPoint.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header FPoint.hh

"C:\Build\inc\Ravl\FPoint.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\FPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header FPoint.hh

"C:\Build\inc\Ravl\FPoint.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\FPoint.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\FLinePP.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header FLinePP.hh

"C:\Build\inc\Ravl\FLinePP.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\FLinePP.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header FLinePP.hh

"C:\Build\inc\Ravl\FLinePP.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\FLinePP.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\Point4d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Point4d.hh

"C:\Build\inc\Ravl\Point4d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\Point4d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Point4d.hh

"C:\Build\inc\Ravl\Point4d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\Point4d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\FAffine.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header FAffine.hh

"C:\Build\inc\Ravl\FAffine.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\FAffine.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header FAffine.hh

"C:\Build\inc\Ravl\FAffine.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\FAffine.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\LineABC2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header LineABC2d.hh

"C:\Build\inc\Ravl\LineABC2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\LineABC2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header LineABC2d.hh

"C:\Build\inc\Ravl\LineABC2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\LineABC2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Curve2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Curve2d.hh

"C:\Build\inc\Ravl\Curve2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Curve2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Curve2d.hh

"C:\Build\inc\Ravl\Curve2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Curve2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Curve2dLine.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Curve2dLine.hh

"C:\Build\inc\Ravl\Curve2dLine.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Curve2dLine.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Curve2dLine.hh

"C:\Build\inc\Ravl\Curve2dLine.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Curve2dLine.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Curve2dLineSegment.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Curve2dLineSegment.hh

"C:\Build\inc\Ravl\Curve2dLineSegment.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Curve2dLineSegment.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Curve2dLineSegment.hh

"C:\Build\inc\Ravl\Curve2dLineSegment.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Curve2dLineSegment.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Line2dIter.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Line2dIter.hh

"C:\Build\inc\Ravl\Line2dIter.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Line2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Line2dIter.hh

"C:\Build\inc\Ravl\Line2dIter.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Line2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Affine2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Affine2d.hh

"C:\Build\inc\Ravl\Affine2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Affine2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Affine2d.hh

"C:\Build\inc\Ravl\Affine2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Affine2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Moments2d2.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Moments2d2.hh

"C:\Build\inc\Ravl\Moments2d2.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Moments2d2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Moments2d2.hh

"C:\Build\inc\Ravl\Moments2d2.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Moments2d2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\LinePP2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header LinePP2d.hh

"C:\Build\inc\Ravl\LinePP2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\LinePP2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header LinePP2d.hh

"C:\Build\inc\Ravl\LinePP2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\LinePP2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Projection2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Projection2d.hh

"C:\Build\inc\Ravl\Projection2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Projection2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Projection2d.hh

"C:\Build\inc\Ravl\Projection2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Projection2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Point2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Point2d.hh

"C:\Build\inc\Ravl\Point2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Point2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Point2d.hh

"C:\Build\inc\Ravl\Point2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Point2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\PointSet2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PointSet2d.hh

"C:\Build\inc\Ravl\PointSet2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\PointSet2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PointSet2d.hh

"C:\Build\inc\Ravl\PointSet2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\PointSet2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Polygon2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Polygon2d.hh

"C:\Build\inc\Ravl\Polygon2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Polygon2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Polygon2d.hh

"C:\Build\inc\Ravl\Polygon2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Polygon2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Circle2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Circle2d.hh

"C:\Build\inc\Ravl\Circle2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Circle2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Circle2d.hh

"C:\Build\inc\Ravl\Circle2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Circle2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Arc2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Arc2d.hh

"C:\Build\inc\Ravl\Arc2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Arc2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Arc2d.hh

"C:\Build\inc\Ravl\Arc2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Arc2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Curve2dCircle.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Curve2dCircle.hh

"C:\Build\inc\Ravl\Curve2dCircle.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Curve2dCircle.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Curve2dCircle.hh

"C:\Build\inc\Ravl\Curve2dCircle.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Curve2dCircle.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Curve2dArc.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Curve2dArc.hh

"C:\Build\inc\Ravl\Curve2dArc.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Curve2dArc.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Curve2dArc.hh

"C:\Build\inc\Ravl\Curve2dArc.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Curve2dArc.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\HEMesh2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header HEMesh2d.hh

"C:\Build\inc\Ravl\HEMesh2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\HEMesh2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header HEMesh2d.hh

"C:\Build\inc\Ravl\HEMesh2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\HEMesh2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\DelaunayTriangulation2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header DelaunayTriangulation2d.hh

"C:\Build\inc\Ravl\DelaunayTriangulation2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\DelaunayTriangulation2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header DelaunayTriangulation2d.hh

"C:\Build\inc\Ravl\DelaunayTriangulation2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\DelaunayTriangulation2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\TriMesh2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header TriMesh2d.hh

"C:\Build\inc\Ravl\TriMesh2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\TriMesh2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header TriMesh2d.hh

"C:\Build\inc\Ravl\TriMesh2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\TriMesh2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Conic2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Conic2d.hh

"C:\Build\inc\Ravl\Conic2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Conic2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Conic2d.hh

"C:\Build\inc\Ravl\Conic2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Conic2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\Ellipse2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Ellipse2d.hh

"C:\Build\inc\Ravl\Ellipse2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Ellipse2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Ellipse2d.hh

"C:\Build\inc\Ravl\Ellipse2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\Ellipse2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\ScanPolygon2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header ScanPolygon2d.hh

"C:\Build\inc\Ravl\ScanPolygon2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\ScanPolygon2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header ScanPolygon2d.hh

"C:\Build\inc\Ravl\ScanPolygon2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\ScanPolygon2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\2D\PolyLine2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PolyLine2d.hh

"C:\Build\inc\Ravl\PolyLine2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\PolyLine2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PolyLine2d.hh

"C:\Build\inc\Ravl\PolyLine2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\2D\PolyLine2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\LinePP3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header LinePP3d.hh

"C:\Build\inc\Ravl\LinePP3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\LinePP3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header LinePP3d.hh

"C:\Build\inc\Ravl\LinePP3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\LinePP3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\LinePV3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header LinePV3d.hh

"C:\Build\inc\Ravl\LinePV3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\LinePV3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header LinePV3d.hh

"C:\Build\inc\Ravl\LinePV3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\LinePV3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\PlaneABCD3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PlaneABCD3d.hh

"C:\Build\inc\Ravl\PlaneABCD3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\PlaneABCD3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PlaneABCD3d.hh

"C:\Build\inc\Ravl\PlaneABCD3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\PlaneABCD3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\PlanePVV3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PlanePVV3d.hh

"C:\Build\inc\Ravl\PlanePVV3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\PlanePVV3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PlanePVV3d.hh

"C:\Build\inc\Ravl\PlanePVV3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\PlanePVV3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\Point3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Point3d.hh

"C:\Build\inc\Ravl\Point3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\Point3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Point3d.hh

"C:\Build\inc\Ravl\Point3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\Point3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\Quatern3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Quatern3d.hh

"C:\Build\inc\Ravl\Quatern3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\Quatern3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Quatern3d.hh

"C:\Build\inc\Ravl\Quatern3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\Quatern3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\RigidTransform3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header RigidTransform3d.hh

"C:\Build\inc\Ravl\RigidTransform3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\RigidTransform3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header RigidTransform3d.hh

"C:\Build\inc\Ravl\RigidTransform3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\RigidTransform3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\EulerAngle.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header EulerAngle.hh

"C:\Build\inc\Ravl\EulerAngle.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\EulerAngle.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header EulerAngle.hh

"C:\Build\inc\Ravl\EulerAngle.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\EulerAngle.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\AxisAngle.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header AxisAngle.hh

"C:\Build\inc\Ravl\AxisAngle.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\AxisAngle.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header AxisAngle.hh

"C:\Build\inc\Ravl\AxisAngle.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\AxisAngle.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\PointSet3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PointSet3d.hh

"C:\Build\inc\Ravl\PointSet3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\PointSet3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PointSet3d.hh

"C:\Build\inc\Ravl\PointSet3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\PointSet3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\3D\HEMesh3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header HEMesh3d.hh

"C:\Build\inc\Ravl\HEMesh3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\HEMesh3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header HEMesh3d.hh

"C:\Build\inc\Ravl\HEMesh3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\3D\HEMesh3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\Boundary\CrackCode.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header CrackCode.hh

"C:\Build\inc\Ravl\CrackCode.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\Boundary\CrackCode.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header CrackCode.hh

"C:\Build\inc\Ravl\CrackCode.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\Boundary\CrackCode.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\Boundary\BVertex.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header BVertex.hh

"C:\Build\inc\Ravl\BVertex.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\Boundary\BVertex.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header BVertex.hh

"C:\Build\inc\Ravl\BVertex.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\Boundary\BVertex.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\Boundary\Crack.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Crack.hh

"C:\Build\inc\Ravl\Crack.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\Boundary\Crack.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Crack.hh

"C:\Build\inc\Ravl\Crack.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\Boundary\Crack.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\Boundary\Boundary.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Boundary.hh

"C:\Build\inc\Ravl\Boundary.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\Boundary\Boundary.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Boundary.hh

"C:\Build\inc\Ravl\Boundary.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\Boundary\Boundary.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Euclidean\Boundary\Edge.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Edge.hh

"C:\Build\inc\Ravl\Edge.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\Boundary\Edge.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Edge.hh

"C:\Build\inc\Ravl\Edge.hh" :  "" ""
	copy ..\.\Math\Geometry\Euclidean\Boundary\Edge.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\1D\PPoint1d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PPoint1d.hh

"C:\Build\inc\Ravl\PPoint1d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\1D\PPoint1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PPoint1d.hh

"C:\Build\inc\Ravl\PPoint1d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\1D\PPoint1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\1D\PProjection1d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PProjection1d.hh

"C:\Build\inc\Ravl\PProjection1d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\1D\PProjection1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PProjection1d.hh

"C:\Build\inc\Ravl\PProjection1d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\1D\PProjection1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\PPointLine2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PPointLine2d.hh

"C:\Build\inc\Ravl\PPointLine2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\2D\PPointLine2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PPointLine2d.hh

"C:\Build\inc\Ravl\PPointLine2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\2D\PPointLine2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\PPoint2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PPoint2d.hh

"C:\Build\inc\Ravl\PPoint2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\2D\PPoint2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PPoint2d.hh

"C:\Build\inc\Ravl\PPoint2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\2D\PPoint2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\PLine2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PLine2d.hh

"C:\Build\inc\Ravl\PLine2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\2D\PLine2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PLine2d.hh

"C:\Build\inc\Ravl\PLine2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\2D\PLine2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\PProjection2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PProjection2d.hh

"C:\Build\inc\Ravl\PProjection2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\2D\PProjection2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PProjection2d.hh

"C:\Build\inc\Ravl\PProjection2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\2D\PProjection2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\PPerspective2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PPerspective2d.hh

"C:\Build\inc\Ravl\PPerspective2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\2D\PPerspective2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PPerspective2d.hh

"C:\Build\inc\Ravl\PPerspective2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\2D\PPerspective2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\2D\FundamentalMatrix2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header FundamentalMatrix2d.hh

"C:\Build\inc\Ravl\FundamentalMatrix2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\2D\FundamentalMatrix2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header FundamentalMatrix2d.hh

"C:\Build\inc\Ravl\FundamentalMatrix2d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\2D\FundamentalMatrix2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\3D\PPointPlane3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PPointPlane3d.hh

"C:\Build\inc\Ravl\PPointPlane3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\3D\PPointPlane3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PPointPlane3d.hh

"C:\Build\inc\Ravl\PPointPlane3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\3D\PPointPlane3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\3D\PPoint3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PPoint3d.hh

"C:\Build\inc\Ravl\PPoint3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\3D\PPoint3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PPoint3d.hh

"C:\Build\inc\Ravl\PPoint3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\3D\PPoint3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\3D\PPlane3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PPlane3d.hh

"C:\Build\inc\Ravl\PPlane3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\3D\PPlane3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PPlane3d.hh

"C:\Build\inc\Ravl\PPlane3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\3D\PPlane3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\3D\PProjection3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PProjection3d.hh

"C:\Build\inc\Ravl\PProjection3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\3D\PProjection3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PProjection3d.hh

"C:\Build\inc\Ravl\PProjection3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\3D\PProjection3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Geometry\Projective\3D\PPerspective3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PPerspective3d.hh

"C:\Build\inc\Ravl\PPerspective3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\3D\PPerspective3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PPerspective3d.hh

"C:\Build\inc\Ravl\PPerspective3d.hh" :  "" ""
	copy ..\.\Math\Geometry\Projective\3D\PPerspective3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\MeanVariance.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header MeanVariance.hh

"C:\Build\inc\Ravl\MeanVariance.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\MeanVariance.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header MeanVariance.hh

"C:\Build\inc\Ravl\MeanVariance.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\MeanVariance.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\MeanNd.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header MeanNd.hh

"C:\Build\inc\Ravl\MeanNd.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\MeanNd.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header MeanNd.hh

"C:\Build\inc\Ravl\MeanNd.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\MeanNd.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\MeanCovariance.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header MeanCovariance.hh

"C:\Build\inc\Ravl\MeanCovariance.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\MeanCovariance.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header MeanCovariance.hh

"C:\Build\inc\Ravl\MeanCovariance.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\MeanCovariance.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\Statistics.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Statistics.hh

"C:\Build\inc\Ravl\Statistics.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\Statistics.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Statistics.hh

"C:\Build\inc\Ravl\Statistics.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\Statistics.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\Mean.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Mean.hh

"C:\Build\inc\Ravl\Mean.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\Mean.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Mean.hh

"C:\Build\inc\Ravl\Mean.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\Mean.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\FMean.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header FMean.hh

"C:\Build\inc\Ravl\FMean.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\FMean.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header FMean.hh

"C:\Build\inc\Ravl\FMean.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\FMean.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\FMeanCovariance.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header FMeanCovariance.hh

"C:\Build\inc\Ravl\FMeanCovariance.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\FMeanCovariance.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header FMeanCovariance.hh

"C:\Build\inc\Ravl\FMeanCovariance.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\FMeanCovariance.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\MeanCovariance2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header MeanCovariance2d.hh

"C:\Build\inc\Ravl\MeanCovariance2d.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\MeanCovariance2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header MeanCovariance2d.hh

"C:\Build\inc\Ravl\MeanCovariance2d.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\MeanCovariance2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\MeanCovariance3d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header MeanCovariance3d.hh

"C:\Build\inc\Ravl\MeanCovariance3d.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\MeanCovariance3d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header MeanCovariance3d.hh

"C:\Build\inc\Ravl\MeanCovariance3d.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\MeanCovariance3d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\Normal.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Normal.hh

"C:\Build\inc\Ravl\Normal.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\Normal.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Normal.hh

"C:\Build\inc\Ravl\Normal.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\Normal.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\Sums1d2.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Sums1d2.hh

"C:\Build\inc\Ravl\Sums1d2.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\Sums1d2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Sums1d2.hh

"C:\Build\inc\Ravl\Sums1d2.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\Sums1d2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\MeanCovariance\SumsNd2.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header SumsNd2.hh

"C:\Build\inc\Ravl\SumsNd2.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\SumsNd2.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header SumsNd2.hh

"C:\Build\inc\Ravl\SumsNd2.hh" :  "" ""
	copy ..\.\Math\Statistics\MeanCovariance\SumsNd2.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\Histogram\Histogram.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Histogram.hh

"C:\Build\inc\Ravl\Histogram.hh" :  "" ""
	copy ..\.\Math\Statistics\Histogram\Histogram.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Histogram.hh

"C:\Build\inc\Ravl\Histogram.hh" :  "" ""
	copy ..\.\Math\Statistics\Histogram\Histogram.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\Histogram\RealHistogram1d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header RealHistogram1d.hh

"C:\Build\inc\Ravl\RealHistogram1d.hh" :  "" ""
	copy ..\.\Math\Statistics\Histogram\RealHistogram1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header RealHistogram1d.hh

"C:\Build\inc\Ravl\RealHistogram1d.hh" :  "" ""
	copy ..\.\Math\Statistics\Histogram\RealHistogram1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Statistics\Histogram\RealHistogram2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header RealHistogram2d.hh

"C:\Build\inc\Ravl\RealHistogram2d.hh" :  "" ""
	copy ..\.\Math\Statistics\Histogram\RealHistogram2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header RealHistogram2d.hh

"C:\Build\inc\Ravl\RealHistogram2d.hh" :  "" ""
	copy ..\.\Math\Statistics\Histogram\RealHistogram2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\PrimitiveBinaryPolynomial.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PrimitiveBinaryPolynomial.hh

"C:\Build\inc\Ravl\PrimitiveBinaryPolynomial.hh" :  "" ""
	copy ..\.\Math\Sequence\PrimitiveBinaryPolynomial.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PrimitiveBinaryPolynomial.hh

"C:\Build\inc\Ravl\PrimitiveBinaryPolynomial.hh" :  "" ""
	copy ..\.\Math\Sequence\PrimitiveBinaryPolynomial.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\SobolSequence.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header SobolSequence.hh

"C:\Build\inc\Ravl\SobolSequence.hh" :  "" ""
	copy ..\.\Math\Sequence\SobolSequence.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header SobolSequence.hh

"C:\Build\inc\Ravl\SobolSequence.hh" :  "" ""
	copy ..\.\Math\Sequence\SobolSequence.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\CircleIter.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header CircleIter.hh

"C:\Build\inc\Ravl\CircleIter.hh" :  "" ""
	copy ..\.\Math\Sequence\CircleIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header CircleIter.hh

"C:\Build\inc\Ravl\CircleIter.hh" :  "" ""
	copy ..\.\Math\Sequence\CircleIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\PermutationIter.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PermutationIter.hh

"C:\Build\inc\Ravl\PermutationIter.hh" :  "" ""
	copy ..\.\Math\Sequence\PermutationIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PermutationIter.hh

"C:\Build\inc\Ravl\PermutationIter.hh" :  "" ""
	copy ..\.\Math\Sequence\PermutationIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\CombinationIter.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header CombinationIter.hh

"C:\Build\inc\Ravl\CombinationIter.hh" :  "" ""
	copy ..\.\Math\Sequence\CombinationIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header CombinationIter.hh

"C:\Build\inc\Ravl\CombinationIter.hh" :  "" ""
	copy ..\.\Math\Sequence\CombinationIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\SquareIter.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header SquareIter.hh

"C:\Build\inc\Ravl\SquareIter.hh" :  "" ""
	copy ..\.\Math\Sequence\SquareIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header SquareIter.hh

"C:\Build\inc\Ravl\SquareIter.hh" :  "" ""
	copy ..\.\Math\Sequence\SquareIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\ZigZagIter.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header ZigZagIter.hh

"C:\Build\inc\Ravl\ZigZagIter.hh" :  "" ""
	copy ..\.\Math\Sequence\ZigZagIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header ZigZagIter.hh

"C:\Build\inc\Ravl\ZigZagIter.hh" :  "" ""
	copy ..\.\Math\Sequence\ZigZagIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\Polygon2dIter.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Polygon2dIter.hh

"C:\Build\inc\Ravl\Polygon2dIter.hh" :  "" ""
	copy ..\.\Math\Sequence\Polygon2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Polygon2dIter.hh

"C:\Build\inc\Ravl\Polygon2dIter.hh" :  "" ""
	copy ..\.\Math\Sequence\Polygon2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Sequence\Array2dPolygon2dIter.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Array2dPolygon2dIter.hh

"C:\Build\inc\Ravl\Array2dPolygon2dIter.hh" :  "" ""
	copy ..\.\Math\Sequence\Array2dPolygon2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Array2dPolygon2dIter.hh

"C:\Build\inc\Ravl\Array2dPolygon2dIter.hh" :  "" ""
	copy ..\.\Math\Sequence\Array2dPolygon2dIter.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Complex\Complex.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Complex.hh

"C:\Build\inc\Ravl\Complex.hh" :  "" ""
	copy ..\.\Math\Complex\Complex.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Complex.hh

"C:\Build\inc\Ravl\Complex.hh" :  "" ""
	copy ..\.\Math\Complex\Complex.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\1D\FFT1d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header FFT1d.hh

"C:\Build\inc\Ravl\FFT1d.hh" :  "" ""
	copy ..\.\Math\Signals\1D\FFT1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header FFT1d.hh

"C:\Build\inc\Ravl\FFT1d.hh" :  "" ""
	copy ..\.\Math\Signals\1D\FFT1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\1D\PowerSpectrum1d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header PowerSpectrum1d.hh

"C:\Build\inc\Ravl\PowerSpectrum1d.hh" :  "" ""
	copy ..\.\Math\Signals\1D\PowerSpectrum1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header PowerSpectrum1d.hh

"C:\Build\inc\Ravl\PowerSpectrum1d.hh" :  "" ""
	copy ..\.\Math\Signals\1D\PowerSpectrum1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\1D\Correlation1d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Correlation1d.hh

"C:\Build\inc\Ravl\Correlation1d.hh" :  "" ""
	copy ..\.\Math\Signals\1D\Correlation1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Correlation1d.hh

"C:\Build\inc\Ravl\Correlation1d.hh" :  "" ""
	copy ..\.\Math\Signals\1D\Correlation1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\1D\RealCepstral.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header RealCepstral.hh

"C:\Build\inc\Ravl\RealCepstral.hh" :  "" ""
	copy ..\.\Math\Signals\1D\RealCepstral.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header RealCepstral.hh

"C:\Build\inc\Ravl\RealCepstral.hh" :  "" ""
	copy ..\.\Math\Signals\1D\RealCepstral.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\1D\Convolution1d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header Convolution1d.hh

"C:\Build\inc\Ravl\Convolution1d.hh" :  "" ""
	copy ..\.\Math\Signals\1D\Convolution1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header Convolution1d.hh

"C:\Build\inc\Ravl\Convolution1d.hh" :  "" ""
	copy ..\.\Math\Signals\1D\Convolution1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\1D\GenerateSignal1d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header GenerateSignal1d.hh

"C:\Build\inc\Ravl\GenerateSignal1d.hh" :  "" ""
	copy ..\.\Math\Signals\1D\GenerateSignal1d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header GenerateSignal1d.hh

"C:\Build\inc\Ravl\GenerateSignal1d.hh" :  "" ""
	copy ..\.\Math\Signals\1D\GenerateSignal1d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File

# Begin Source File
SOURCE=..\.\Math\Signals\2D\FFT2d.hh

!IF  "$(CFG)" == "RavlMath - Win32 Release"

# Begin Custom Build - Install Header FFT2d.hh

"C:\Build\inc\Ravl\FFT2d.hh" :  "" ""
	copy ..\.\Math\Signals\2D\FFT2d.hh C:\Build\inc\Ravl

# End Custom Build

!ELSEIF  "$(CFG)" == "RavlMath - Win32 Debug"

# Begin Custom Build - Install Header FFT2d.hh

"C:\Build\inc\Ravl\FFT2d.hh" :  "" ""
	copy ..\.\Math\Signals\2D\FFT2d.hh C:\Build\inc\Ravl

# End Custom Build

!ENDIF 

# End Source File


# End Group

# End Target
# End Project
