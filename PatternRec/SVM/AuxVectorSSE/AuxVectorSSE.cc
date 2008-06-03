// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here

#include <stdlib.h>
#include <emmintrin.h>

#include "Ravl/PatternRec/AuxVectorSSE.hh"

namespace RavlN
{

//---------------------------------------------------------------------------
double *AuxVectorSSEC::AllocateVector(int Size) const
{
  double *retVal;
#ifdef VISUAL_CPP
  retVal = (double*)_aligned_malloc(Size * sizeof(double), 16);
#else
  posix_memalign((void **)&retVal, 16, Size * sizeof(double));
#endif
  return retVal;
}

//---------------------------------------------------------------------------
void AuxVectorSSEC::FreeVector(double *Ptr) const
{
#ifdef VISUAL_CPP
  _aligned_free(Ptr);
#else
  free(Ptr);
#endif
}

//---------------------------------------------------------------------------
double AuxVectorSSEC::DotProduct(const double *Data, const double *Weights,
                                 int Size) const
{
  const double* wPtr = Weights;
  const double* const ewPtr = Weights + (Size & ~0x1);
  const double* dPtr = Data;
  __m128d sum = _mm_setzero_pd();
  if((((unsigned long int) dPtr) & 0xf) == 0) // Data 16-byte aligned ?
  {
    while(wPtr != ewPtr)
    {
      const __m128d val = _mm_load_pd(dPtr);
      sum = _mm_add_pd(sum, _mm_mul_pd(val, _mm_load_pd(wPtr)));
      dPtr += 2;
      wPtr += 2;
    }
  } else
  {
    while(wPtr != ewPtr)
    {
      const __m128d val = _mm_loadu_pd(dPtr);
      sum = _mm_add_pd(sum, _mm_mul_pd(val, _mm_load_pd(wPtr)));
      dPtr += 2;
      wPtr += 2;
    }
  }
  if(Size & 1) // Odd length ?
  {
    const __m128d val = _mm_load_sd(dPtr++);
    sum = _mm_add_pd(sum, _mm_mul_sd(val, _mm_load_sd(wPtr++)));
  }
  double tmp[2];
  _mm_storeu_pd(tmp, sum);
  return tmp[0] + tmp[1];
}

//---------------------------------------------------------------------------
double AuxVectorSSEC::DotProduct2(const double *Data, const double *Weights1,
                                  const double *Weights2, int Size) const
{
  const double* wPtr = Weights1;
  const double* w2Ptr = Weights2;
  const double* const ewPtr = Weights1 + (Size & ~0x1);
  const double* dPtr = Data;
  __m128d sum = _mm_setzero_pd();
  if((((unsigned long int) dPtr) & 0xf) == 0) // Data 16-byte aligned ?
  {
    while(wPtr != ewPtr)
    {
      const __m128d val = _mm_load_pd(dPtr);
      sum = _mm_add_pd(sum,
                       _mm_mul_pd(val,
                                  _mm_add_pd(_mm_mul_pd(val,
                                                        _mm_load_pd(w2Ptr)),
                                             _mm_load_pd(wPtr))));
      dPtr += 2;
      wPtr += 2;
      w2Ptr += 2;
    }
  } else
  {
    while(wPtr != ewPtr)
    {
      const __m128d val = _mm_loadu_pd(dPtr);
      sum = _mm_add_pd(sum,
                       _mm_mul_pd(val,
                                  _mm_add_pd(_mm_mul_pd(val,
                                                        _mm_load_pd(w2Ptr)),
                                             _mm_load_pd(wPtr))));
      dPtr += 2;
      wPtr += 2;
      w2Ptr += 2;
    }
  }
  if(Size & 1) // Odd length ?
  {
    const __m128d val = _mm_load_sd(dPtr++);
    sum = _mm_add_pd(sum,
                     _mm_mul_sd(val,
                                _mm_add_sd(_mm_mul_sd(val,
                                                      _mm_load_sd(w2Ptr++)),
                                           _mm_load_sd(wPtr++))));
  }
  double tmp[2];
  _mm_storeu_pd(tmp, sum);
  return tmp[0] + tmp[1];
}
//---------------------------------------------------------------------------

} //end of namespace RavlN
