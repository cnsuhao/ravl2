
#ifndef _RAVL_3D_EULER_ANGLE_HH_
#define _RAVL_3D_EULER_ANGLE_HH_ 1

#include "Ravl/Vector3d.hh"
#include "Ravl/Matrix3d.hh"

namespace RavlN
{
  //! userlevel=Develop

  // C-style euler angle -> matrix conversions
  void EulerXYXToMatrix(const RealT* a, RealT* R);
  void EulerXYZToMatrix(const RealT* a, RealT* R);
  void EulerXZXToMatrix(const RealT* a, RealT* R);
  void EulerXZYToMatrix(const RealT* a, RealT* R);
  void EulerYXYToMatrix(const RealT* a, RealT* R);
  void EulerYXZToMatrix(const RealT* a, RealT* R);
  void EulerYZXToMatrix(const RealT* a, RealT* R);
  void EulerYZYToMatrix(const RealT* a, RealT* R);
  void EulerZXYToMatrix(const RealT* a, RealT* R);
  void EulerZXZToMatrix(const RealT* a, RealT* R);
  void EulerZYXToMatrix(const RealT* a, RealT* R);
  void EulerZYZToMatrix(const RealT* a, RealT* R);

  // C-style matrix -> euler angle conversions
  void MatrixToEulerXYX(const RealT* R, RealT* a, const RealT a0_default = 0.0);
  void MatrixToEulerXYZ(const RealT* R, RealT* a, const RealT a0_default = 0.0);
  void MatrixToEulerXZX(const RealT* R, RealT* a, const RealT a0_default = 0.0);
  void MatrixToEulerXZY(const RealT* R, RealT* a, const RealT a0_default = 0.0);
  void MatrixToEulerYXY(const RealT* R, RealT* a, const RealT a0_default = 0.0);
  void MatrixToEulerYXZ(const RealT* R, RealT* a, const RealT a0_default = 0.0);
  void MatrixToEulerYZX(const RealT* R, RealT* a, const RealT a0_default = 0.0);
  void MatrixToEulerYZY(const RealT* R, RealT* a, const RealT a0_default = 0.0);
  void MatrixToEulerZXY(const RealT* R, RealT* a, const RealT a0_default = 0.0);
  void MatrixToEulerZXZ(const RealT* R, RealT* a, const RealT a0_default = 0.0);
  void MatrixToEulerZYX(const RealT* R, RealT* a, const RealT a0_default = 0.0);
  void MatrixToEulerZYZ(const RealT* R, RealT* a, const RealT a0_default = 0.0);
  
  //! userlevel=Normal

  // Euler angle -> matrix conversions


  inline void EulerXYXToMatrix(const Vector3dC& a, Matrix3dC& R)
  { EulerXYXToMatrix(&a[0],&R[0][0]); }
  inline void EulerXYZToMatrix(const Vector3dC& a, Matrix3dC& R)
  { EulerXYZToMatrix(&a[0],&R[0][0]); }
  inline void EulerXZXToMatrix(const Vector3dC& a, Matrix3dC& R)
  { EulerXZXToMatrix(&a[0],&R[0][0]); }
#if 0
  void EulerXZYToMatrix(const Vector3dC& a, Matrix3dC& R)
  { EulerXZYToMatrix(&a[0],&R[0][0]); }
  void EulerYXYToMatrix(const Vector3dC& a, Matrix3dC& R)
  { EulerYXYToMatrix(&a[0],&R[0][0]); }
  void EulerYXZToMatrix(const Vector3dC& a, Matrix3dC& R)
  { EulerYXZToMatrix(&a[0],&R[0][0]); }
  void EulerYZXToMatrix(const Vector3dC& a, Matrix3dC& R)
  { EulerYZXToMatrix(&a[0],&R[0][0]); }
  void EulerYZYToMatrix(const Vector3dC& a, Matrix3dC& R)
  { EulerYZYToMatrix(&a[0],&R[0][0]); }
  void EulerZXYToMatrix(const Vector3dC& a, Matrix3dC& R)
  { EulerZXYToMatrix(&a[0],&R[0][0]); }
  void EulerZXZToMatrix(const Vector3dC& a, Matrix3dC& R)
  { EulerZXZToMatrix(&a[0],&R[0][0]); }
  void EulerZYXToMatrix(const Vector3dC& a, Matrix3dC& R)
  { EulerZYXToMatrix(&a[0],&R[0][0]); }
  void EulerZYZToMatrix(const Vector3dC& a, Matrix3dC& R)
  { EulerZYZToMatrix(&a[0],&R[0][0]); }
#endif

  // Matrix -> euler angle conversions
  inline void MatrixToEulerXYX(const Matrix3dC& R, Vector3dC& a, const RealT a0_default = 0.0)
  { MatrixToEulerXYX(&R[0][0], &a[0], a0_default); }
  inline void MatrixToEulerXYZ(const Matrix3dC& R, Vector3dC& a, const RealT a0_default = 0.0)
  { MatrixToEulerXYZ(&R[0][0], &a[0], a0_default); }
  inline void MatrixToEulerXZX(const Matrix3dC& R, Vector3dC& a, const RealT a0_default = 0.0)
  { MatrixToEulerXZX(&R[0][0], &a[0], a0_default); }
#if 0
  void MatrixToEulerXZY(const Matrix3dC& R, Vector3dC& a, const RealT a0_default = 0.0)
  { MatrixToEulerXZY(&R[0][0], &a[0], a0_default);} 
  void MatrixToEulerYXY(const Matrix3dC& R, Vector3dC& a, const RealT a0_default = 0.0)
  { MatrixToEulerYXY(&R[0][0], &a[0], a0_default); }
  void MatrixToEulerYXZ(const Matrix3dC& R, Vector3dC& a, const RealT a0_default = 0.0)
  { MatrixToEulerYXZ(&R[0][0], &a[0], a0_default); }
  void MatrixToEulerYZX(const Matrix3dC& R, Vector3dC& a, const RealT a0_default = 0.0)
  { MatrixToEulerYZX(&R[0][0], &a[0], a0_default); }
  void MatrixToEulerYZY(const Matrix3dC& R, Vector3dC& a, const RealT a0_default = 0.0)
  { MatrixToEulerYXY(&R[0][0], &a[0], a0_default); }
  void MatrixToEulerZXY(const Matrix3dC& R, Vector3dC& a, const RealT a0_default = 0.0)
  { MatrixToEulerZXY(&R[0][0], &a[0], a0_default); }
  void MatrixToEulerZXZ(const Matrix3dC& R, Vector3dC& a, const RealT a0_default = 0.0)
  { MatrixToEulerZXZ(&R[0][0], &a[0], a0_default); }
  void MatrixToEulerZYX(const Matrix3dC& R, Vector3dC& a, const RealT a0_default = 0.0)
  { MatrixToEulerZYX(&R[0][0], &a[0], a0_default); }
  void MatrixToEulerZYZ(const Matrix3dC& R, Vector3dC& a, const RealT a0_default = 0.0)
  { MatrixToEulerZYZ(&R[0][0], &a[0], a0_default); }
#endif

  //! userlevel=Normal

  //: Euler angle sequence definition.
  // Doesn't yet support all sequences...will add more soon
  class EulerSequenceC
  {
  public:
    enum SequenceT
    {
      XYX,
      XYZ,
      XZX,

      NumSequences
    };

  public:
    EulerSequenceC()
    {
    }
    //: Default constructor - construct invalid sequence.

    EulerSequenceC(int sequence) : 
      s(sequence)
    {
      RavlAssert(s >= 0);
      RavlAssert(s < NumSequences);
    }
    //: Construct sequence from integer identifier

    EulerSequenceC(const char* str);
    //: Construct sequence from string, eg. "XYZ"

  public:
    operator int() const
    { return s; }

  protected:
    int s;
  };
  

  //: Convert Euler angles to rotation matrix according to sequence
  //  Not all sequences yet supported.
  void EulerToMatrix(const Vector3dC& a, 
		     Matrix3dC& R, 
		     const EulerSequenceC sequence);

  //: Convert rotation matrix to Euler angles according to sequence
  //  Not all sequences yet supported.
  void MatrixToEuler(const Matrix3dC& R, 
		     Vector3dC& a, 
		     const EulerSequenceC sequence,
		     const RealT a0_default = 0.0);

  //: Class for all Euler angle info
  class EulerAngleC : public Vector3dC
  {
  public:
    EulerAngleC()
    {
    }
    //: Default constructor (uninitialised angles and sequence).

    EulerAngleC(RealT a, RealT b, RealT c, EulerSequenceC sequence) :
      Vector3dC(a,b,c),
      s(sequence)
    {
    }
    //: Construct from angle parameters and sequence.

    EulerAngleC(const Vector3dC& a, EulerSequenceC sequence) :
      Vector3dC(a),
      s(sequence)
    {
    }
    //: Construct from angle vector and sequence.
    
    EulerAngleC(const Matrix3dC& R, EulerSequenceC sequence, RealT a0_default = 0.0) :
      s(sequence)
    {
      MatrixToEuler(R, *static_cast<Vector3dC*>(this), sequence, a0_default);
    }
    //: Construct from rotation matrix and sequence.
   

  public:

    const EulerSequenceC& Sequence() const
    { return s; };
    //: Euler sequence (read-only)

    EulerSequenceC& Sequence()
    { return s; };
    //: Euler sequence.

  public:

    void Matrix(Matrix3dC& R) const
    { EulerToMatrix(*static_cast<const Vector3dC*>(this), R, s); }
    //: Convert to rotation matrix.

    Matrix3dC Matrix() const
    {
      Matrix3dC R;
      Matrix(R);
      return R;
    }
    //: Convert to rotation matrix (as return value).

  protected:
    EulerSequenceC s;
    
  };
}




#endif


