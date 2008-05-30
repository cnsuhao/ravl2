// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here

#include "Ravl/PatternRec/AuxVector.hh"

#include <stdio.h>

namespace RavlN
{

//---------------------------------------------------------------------------
AuxVectorC* GetAuxVectorSimple()
{
  //printf("GetAuxVectorSimple\n");
  return new AuxVectorC();
}

GetAuxVectorF_T *GetAuxVector = &GetAuxVectorSimple;

//---------------------------------------------------------------------------
//! Default constructor
AuxVectorC::AuxVectorC()
{
}

//---------------------------------------------------------------------------
//! Destructor
AuxVectorC::~AuxVectorC()
{
}

//---------------------------------------------------------------------------
double *AuxVectorC::AllocateVector(int Size) const
{
  return new double[Size];
}

//---------------------------------------------------------------------------
void AuxVectorC::FreeVector(double *Ptr) const
{
  delete[] Ptr;
}

//---------------------------------------------------------------------------
double AuxVectorC::DotProduct(const double *Data, const double *Weights,
                              int Size) const
{
  double retVal = 0.;
  const double* wPtr = Weights;
  const double* const ewPtr = wPtr + Size;
  const double* dPtr = Data;
  while(wPtr != ewPtr)
  {
    const double val = *dPtr++;
    retVal += val * *wPtr++;
  }
  return retVal;
}

//---------------------------------------------------------------------------
double AuxVectorC::DotProduct2(const double *Data, const double *Weights1,
                               const double *Weights2, int Size) const
{
  double retVal = 0.;
  const double* wPtr = Weights1;
  const double* w2Ptr = Weights2;
  const double* const ewPtr = wPtr + Size;
  const double* dPtr = Data;
  while(wPtr != ewPtr)
  {
    const double val = *dPtr++;
    retVal += val * (*wPtr++ + *w2Ptr++ * val);
  }
  return retVal;
}

//---------------------------------------------------------------------------
void AuxVectorC::DestroyAuxVector(AuxVectorC* AuxVec)
{
  delete AuxVec;
}

//---------------------------------------------------------------------------

} //end of namespace RavlN
