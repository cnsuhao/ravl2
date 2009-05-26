// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
// $Id: AuxVector.hh 10404 2007-03-29 14:07:26Z alex $

#ifndef RAVL_AUX_VECTOR_HEADER
#define RAVL_AUX_VECTOR_HEADER


namespace RavlN
{

//! Auxilary vector functions (base class for AuxVectorSSEC)
class AuxVectorC
{
public:
  //! Default constructor
  AuxVectorC();

  //! Destructor
  virtual ~AuxVectorC();

  virtual double *AllocateVector(int Size) const;

  virtual void FreeVector(double *Ptr) const;

  virtual double DotProduct(const double *Data, const double *Weights,
                            int Size) const;

  virtual double DotProduct2(const double *Data, const double *Weights1,
                             const double *Weights2, int Size) const;

  static void DestroyAuxVector(AuxVectorC* AuxVec);
};

typedef AuxVectorC* GetAuxVectorF_T();
extern GetAuxVectorF_T *GetAuxVector;

} //end of namespace RavlN
#endif
