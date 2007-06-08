#ifndef RAVL_PARZENWINDOW_HEADER
#define RAVL_PARZENWINDOW_HEADER 1

//! author="Bill Christmas"
//! docentry="Ravl.API.Math.Statistics"
//! lib=RavlMath
//! file="Ravl/Math/Statistics/Histogram/Parzen.hh"


#include "Ravl/Array1d.hh"

  //! userlevel=Normal

namespace RavlN {

  //: Generate Parzen estimates of a p.d.f. from a set of N samples
  // The smoothing kernel is a Gaussian of unit "variance".<br/>
  // The actual smoothing width used is h<sub>1</sub> / &radic;N.
  
  class ParzenWindowC : private Array1dC<RealT> {
    
  public:
    ParzenWindowC (const Array1dC<RealT>& samples, RealT h_1)
      : Array1dC<RealT>(samples),
      bandwidth(h_1*Sqrt(2.0/this->Size()))
      {}
    //: Constructor
    //!param: samples - array of samples whose density is to be estimated
    //!param: h_1 - smoothing parameter h<sub>1</sub>, typically about 0.25
    
    RealT PdfEstimate(RealT arg) {
      RealT estimate(0.0);
      for (Array1dIterC<RealT> i(*this); i; ++i) 
        estimate += exp(-Sqr((arg-(*i))/bandwidth));
      return estimate/(this->Size()*bandwidth*Sqrt(RavlConstN::pi));
    }
    //: Estimate the pdf at the value "arg"

  private:
    RealT bandwidth;
  };
}

#endif
