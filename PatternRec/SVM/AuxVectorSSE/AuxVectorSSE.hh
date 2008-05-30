// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
// $Id: AuxVectorSSE.hh 10404 2007-03-29 14:07:26Z alex $

#ifndef RAVL_AUX_VECTOR_SSE_HEADER
#define RAVL_AUX_VECTOR_SSE_HEADER

#include "Ravl/PatternRec/AuxVector.hh"

namespace RavlN
{

//! Auxilary vector functions optimized for SSE
class AuxVectorSSEC : public AuxVectorC
{
public:
  //! Default constructor
  AuxVectorSSEC()
    {}

  //! Destructor
  virtual ~AuxVectorSSEC()
    {}

  virtual double *AllocateVector(int Size) const;

  virtual void FreeVector(double *Ptr) const;

  virtual double DotProduct(const double *Data, const double *Weights,
                            int Size) const;

  virtual double DotProduct2(const double *Data, const double *Weights1,
                             const double *Weights2, int Size) const;
};

} //end of namespace RavlN
#endif
