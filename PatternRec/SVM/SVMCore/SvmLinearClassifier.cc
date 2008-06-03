// This file is used in conjunction with RAVL, Recognition And Vision Library
// Copyright (C) 2004, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here

#include "Ravl/PatternRec/SvmLinearClassifier.hh"
#include "Ravl/PatternRec/SvmClassifier.hh"
#include "Ravl/PatternRec/CommonKernels.hh"
#include "Ravl/PatternRec/AuxVector.hh"

namespace RavlN
{
using namespace RavlN;

//---------------------------------------------------------------------------
//! Default constructor.
//! Creates empty classifier
SvmLinearClassifierBodyC::SvmLinearClassifierBodyC()
{
  InitMembers();
}
//---------------------------------------------------------------------------
//! Load from stream.
SvmLinearClassifierBodyC::SvmLinearClassifierBodyC(istream &Strm)
                         :Classifier2BodyC(Strm)
{
  InitMembers();

  IntT version;
  Strm >> version;
  if(version != 0)
    throw ExceptionOperationFailedC("SvmLinearClassifierBodyC::Load:"
                                    "Unrecognised version number in stream.");

  int numWeights;
  Strm >> numWeights;

  CreateBuffers(numWeights);

  // read weights
  for(int i = 0; i < m_numWeights; i++)
  {
    Strm >> m_weights[i];
  }

  Strm >> m_threshold;
}
//---------------------------------------------------------------------------
//! Load from binary stream.
SvmLinearClassifierBodyC::SvmLinearClassifierBodyC(BinIStreamC &Strm)
                         :Classifier2BodyC(Strm)
{
  InitMembers();

  IntT version;
  Strm >> version;
  if(version != 0)
    throw ExceptionOperationFailedC("SvmLinearClassifierBodyC::Load:"
                                    "Unrecognised version number in stream.");

  int numWeights;
  Strm >> numWeights;

  CreateBuffers(numWeights);

  // read weights
  for(int i = 0; i < m_numWeights; i++)
  {
    Strm >> m_weights[i];
  }

  Strm >> m_threshold;
}
//---------------------------------------------------------------------------
// Destructor.
SvmLinearClassifierBodyC::~SvmLinearClassifierBodyC()
{
  DestroyBuffers();
  AuxVectorC::DestroyAuxVector(auxVec);
  auxVec = NULL;
}
//---------------------------------------------------------------------------
void SvmLinearClassifierBodyC::DestroyBuffers()
{
  if(m_weights != NULL)
    auxVec->FreeVector(m_weights);
  m_weights = NULL;
  m_numWeights = 0;
}
//---------------------------------------------------------------------------
//! allocate memory for weights
void SvmLinearClassifierBodyC::CreateBuffers(int NumWeights)
{
  if(m_numWeights != NumWeights)
  {
    DestroyBuffers();
    m_weights = auxVec->AllocateVector(NumWeights);
    if(m_weights == NULL)
      throw ExceptionOperationFailedC("SvmLinearClassifierBodyC::CreateBuffers:"
                                      "Can't allocate memory for weights");
    m_numWeights = NumWeights;
  }
}
//---------------------------------------------------------------------------
//! initialise member variables
void SvmLinearClassifierBodyC::InitMembers()
{
  m_threshold = 0.;
  m_weights = NULL;
  m_numWeights = 0;
  auxVec = GetAuxVector();
}
//---------------------------------------------------------------------------
// Writes object to stream
bool SvmLinearClassifierBodyC::Save(ostream &Out) const
{
  if(!ClassifierBodyC::Save(Out))
    throw ExceptionOperationFailedC("SvmLinearClassifierBodyC::Save:"
                                    "error in ClassifierBodyC::Save call.");
  const IntT version = 0;
  Out << ' ' << version << ' ' << m_numWeights;
  for(int i = 0; i < m_numWeights; i++)
  {
    Out << '\n' << m_weights[i];
  }
  Out << '\n' << m_threshold;
  return true;
}
//---------------------------------------------------------------------------
// Writes object to stream, can be loaded using constructor
bool SvmLinearClassifierBodyC::Save(BinOStreamC &Out) const
{
  if(!ClassifierBodyC::Save(Out))
    throw ExceptionOperationFailedC("SvmLinearClassifierBodyC::Save:"
                                    "error in ClassifierBodyC::Save call.");
  const IntT version = 0;
  Out << version << m_numWeights;
  for(int i = 0; i < m_numWeights; i++)
  {
    Out << m_weights[i];
  }
  Out << m_threshold;
  return true;
}
//---------------------------------------------------------------------------
// Classifier vector 'Data' return value of descriminant function
RealT SvmLinearClassifierBodyC::Classify2(const RealT* Data) const
{
  RealT retVal = m_threshold + auxVec->DotProduct(Data, m_weights, m_numWeights);
  return retVal;
}
//---------------------------------------------------------------------------
// Get vector length of classifier
IntT SvmLinearClassifierBodyC::GetDataSize() const
{
  return m_numWeights;
}
//---------------------------------------------------------------------------
//! Create classifier
/**
@param Sv support vectors
@param Lambdas lagrangian multipliers
@param Scale global scale from kernel function
@param Threshold threshold
  */
void SvmLinearClassifierBodyC::Create(const SampleC<VectorC>& Sv,
                                      const RealT* Lambdas,
                                      RealT Scale, RealT Threshold)
{
  const int numSv = Sv.Size();

  if(numSv <= 0)
    throw ExceptionOperationFailedC("SvmLinearClassifierBodyC::Create:"
                                    "No support vectors!");

  CreateBuffers(Sv[0].Size());

  for(int i = 0; i < m_numWeights; m_weights[i++] = 0.);

  for(int i = 0; i < numSv; i++)
  {
    RealT lambda = Lambdas[i];
    const RealT* imPtr = Sv[i].DataStart();
    RealT* wPtr = m_weights;
    const RealT* const ewPtr = m_weights + m_numWeights;
    while(wPtr < ewPtr)
    {
      *wPtr++ += lambda * *imPtr++;
    }
  }

  for(int i = 0; i < m_numWeights; m_weights[i++] *= Scale);

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
void SvmLinearClassifierBodyC::Create(const SampleC<VectorC>& Sv,
                                      const RealT* Lambdas,
                                      const RealT* Weights,
                                      RealT Scale, RealT Threshold)
{
  Create(Sv, Lambdas, Scale, Threshold);
  for(int j = 0; j < m_numWeights; j++)
  {
    m_weights[j] *= Weights[j];
  }
}
//---------------------------------------------------------------------------
}
