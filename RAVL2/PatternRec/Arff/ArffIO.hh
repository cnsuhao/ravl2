#ifndef ARFFIO_HH
#define ARFFIO_HH

#include "Ravl/String.hh"
#include "Ravl/PatternRec/Sample.hh"
#include "Ravl/Vector.hh"

namespace RavlN
{
using namespace RavlN;

void SaveArff(const StringC& FileName, const SampleC<VectorC> &TrVec,
              const SampleC<SByteT> &TrLab);

void LoadArff(const StringC& FileName, SampleC<VectorC> &TrVec,
              SampleC<SByteT> &TrLab);

void TrimFeatures(SampleC<VectorC> &TrVec, const char *Mask);
};
#endif
