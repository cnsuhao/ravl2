// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here

#define _XOPEN_SOURCE 600

//#include <stdlib.h>
//#include <emmintrin.h>

#include "Ravl/PatternRec/SvmQuadraticClassifier.hh"
#include "Ravl/PatternRec/SvmClassifier.hh"
#include "Ravl/PatternRec/CommonKernels.hh"
#include "Ravl/PatternRec/AuxVector.hh"

namespace RavlN
{
using namespace RavlN;


//---------------------------------------------------------------------------
//! Default constructor
//! Creates empty classifier
SvmQuadraticClassifierBodyC::SvmQuadraticClassifierBodyC()
{
  InitMembers();
}

//---------------------------------------------------------------------------
//! Load from stream.
SvmQuadraticClassifierBodyC::SvmQuadraticClassifierBodyC(istream &Strm)
                           : Classifier2BodyC(Strm)
{
  InitMembers();

  IntT version;
  Strm >> version;
  if(version != 0)
    throw ExceptionOperationFailedC("SvmQuadraticClassifierBodyC::Load:"
                                    "Unrecognised version number in stream.");

  int numWeights;
  Strm >> numWeights;
  RavlAssert((numWeights & 1) == 0); // Should always be even!

  CreateBuffers(numWeights / 2);

  // read weights
  for(int i = 0; i < m_halfWeights; i++)
  {
    Strm >> m_weights1[i];
  }

  for(int i = 0; i < m_halfWeights; i++)
  {
    Strm >> m_weights2[i];
  }

  Strm >> m_threshold;
}
//---------------------------------------------------------------------------
//! Load from binary stream.
SvmQuadraticClassifierBodyC::SvmQuadraticClassifierBodyC(BinIStreamC &Strm)
                           :Classifier2BodyC(Strm)
{
  InitMembers();

  IntT version;
  Strm >> version;
  if(version != 0)
    throw ExceptionOperationFailedC("SvmQuadraticClassifierBodyC::Load:"
                                    "Unrecognised version number in stream.");

  int numWeights;
  Strm >> numWeights;
  RavlAssert((numWeights & 1) == 0); // Should always be even!

  CreateBuffers(numWeights / 2);

  // read weights
  for(int i = 0; i < m_halfWeights; i++)
    Strm >> m_weights1[i];

  for(int i = 0; i < m_halfWeights; i++)
    Strm >> m_weights2[i];

  Strm >> m_threshold;
}
//---------------------------------------------------------------------------
//! Destructor.
SvmQuadraticClassifierBodyC::~SvmQuadraticClassifierBodyC()
{
  DestroyBuffers();
  AuxVectorC::DestroyAuxVector(auxVec);
  auxVec = NULL;
}
//---------------------------------------------------------------------------
//! free allocated memory
void SvmQuadraticClassifierBodyC::DestroyBuffers()
{
  if(m_weights1 != NULL)
    auxVec->FreeVector(m_weights1);

  if(m_weights1 != NULL)
    auxVec->FreeVector(m_weights2);

  m_weights1 = NULL;
  m_weights2 = NULL;
  m_halfWeights = 0;
}
//---------------------------------------------------------------------------
//! allocate memory for weights
void SvmQuadraticClassifierBodyC::CreateBuffers(int HalfWeights)
{
  m_weights1 = auxVec->AllocateVector(HalfWeights);
  m_weights2 = auxVec->AllocateVector(HalfWeights);

  if(m_weights1 == NULL || m_weights2 == NULL)
  {
    DestroyBuffers();
    throw ExceptionOperationFailedC("SvmQuadraticClassifierBodyC::CreateBuffers:"
                                    "Can't allocate memory for weights");
  }
  m_halfWeights = HalfWeights;
}
//---------------------------------------------------------------------------
//! initialise member variables
void SvmQuadraticClassifierBodyC::InitMembers()
{
  m_weights1 = NULL;
  m_weights2 = NULL;
  m_halfWeights = 0;
  m_threshold = 0.;
  auxVec = GetAuxVector();
}
//---------------------------------------------------------------------------
//! Writes object to stream
bool SvmQuadraticClassifierBodyC::Save(ostream &Out) const
{
  if(!ClassifierBodyC::Save(Out))
    throw ExceptionOperationFailedC("SvmQuadraticClassifierBodyC::Save:"
                                    "error in ClassifierBodyC::Save call.");
  const IntT version = 0;
  Out << ' ' << version << ' ' << m_halfWeights * 2;
  for(int i = 0; i < m_halfWeights; i++)
  {
    Out << '\n' << m_weights1[i];
  }
  for(int i = 0; i < m_halfWeights; i++)
  {
    Out << '\n' << m_weights2[i];
  }
  Out << '\n' << m_threshold;
  return true;
}
//---------------------------------------------------------------------------
//! Writes object to stream, can be loaded using constructor
bool SvmQuadraticClassifierBodyC::Save(BinOStreamC &Out) const
{
  if(!ClassifierBodyC::Save(Out))
    throw ExceptionOperationFailedC("SvmQuadraticClassifierBodyC::Save:"
                                    "error in ClassifierBodyC::Save call.");
  const IntT version = 0;
  Out << version << m_halfWeights * 2;
  for(int i = 0; i < m_halfWeights; i++)
  {
    Out << m_weights1[i];
  }
  for(int i = 0; i < m_halfWeights; i++)
  {
    Out << m_weights2[i];
  }
  Out << m_threshold;
  return true;
}
//---------------------------------------------------------------------------
//! Classifier vector 'Data' return value of descriminant function
RealT SvmQuadraticClassifierBodyC::Classify2(const RealT* Data) const
{
  RealT retVal = m_threshold + auxVec->DotProduct2(Data, m_weights1, m_weights2,
                                                   m_halfWeights);
  return retVal;
}
//---------------------------------------------------------------------------
//! Get vector length of classifier
IntT SvmQuadraticClassifierBodyC::GetDataSize() const
{
  return m_halfWeights;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//! Create classifier
/**
@param Sv support vectors
@param Lambdas lagrangian multipliers
@param Scale global scale from kernel function
@param Threshold threshold
 */
void SvmQuadraticClassifierBodyC::Create(const SampleC<VectorC>& Sv,
                                         const RealT* Lambdas,
                                         RealT Scale, RealT Threshold)
{
  const int numSv = Sv.Size();
  if(numSv <= 0)
    throw ExceptionOperationFailedC("SvmQuadraticClassifierBodyC::Create:"
                                    "No support vectors!");
  CreateBuffers(Sv[0].Size());

  for(int i = 0; i < m_halfWeights;i++ )
  {
    m_weights1[i] = 0.;
    m_weights2[i] = 0.;
  }

  for(int i = 0; i < numSv; i++)
  {
    RealT lambda = Lambdas[i];
    const RealT* imPtr = Sv[i].DataStart();
    RealT* wPtr = m_weights1;
    RealT* w2Ptr = m_weights2;
    const RealT* const wePtr = m_weights1 + m_halfWeights;
    while(wPtr < wePtr)
    {
      RealT val = *imPtr++;
      *wPtr++ += lambda * val;
      *w2Ptr++ += lambda * val * val;
    }
  }

  for(int i = 0; i < m_halfWeights;i++)
  {
    m_weights1[i] *= Scale;
    m_weights2[i] *= Scale;
  }

  m_threshold = Threshold;
}

//---------------------------------------------------------------------------
//! Create classifier
/**
@param Sv support vectors
@param Lambdas lagrangian multipliers
@param Weights weights for features
@param Scale global scale from kernel function
@param Threshold threshold
 */
void SvmQuadraticClassifierBodyC::Create(const SampleC<VectorC>& Sv,
                                         const RealT* Lambdas,
                                         const RealT* Weights,
                                         RealT Scale, RealT Threshold)
{
  Create(Sv, Lambdas, Scale, Threshold);
  for(int j = 0; j < m_halfWeights; j++)
  {
    const RealT w = Weights[j];
    m_weights1[j] *= w;
    m_weights2[j] *= w * w;
  }
}

//---------------------------------------------------------------------------
}
