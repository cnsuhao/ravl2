#include "Ravl/Parzen.hh"
#include "Ravl/MeanVariance.hh"

using namespace RavlN;

// Constructor
ParzenWindowC::ParzenWindowC (const Array1dC<RealT>& samples, RealT h_1)
  : Array1dC<RealT>(samples)
{
  MeanVarianceC stats(this->SArray1d(true));
  bandwidth = h_1*Sqrt(2.0*stats.Variance()/(this->Size()));
}
    
// Estimate the pdf at the value "arg"
RealT ParzenWindowC::PdfEstimate(RealT arg) {
  RealT estimate(0.0);
  for (Array1dIterC<RealT> i(*this); i; ++i) 
    estimate += exp(-Sqr((arg-(*i))/bandwidth));
  return estimate/(this->Size()*bandwidth*Sqrt(RavlConstN::pi));
}
