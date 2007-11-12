#ifndef GABORCOMPLEXC
#define GABORCOMPLEXC 1

//! docentry="Ravl.API.Images.Filtering"
//! author="Bill Christmas"
//! example="exGaborComplex.cc"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Filters/GaborComplex.hh"

#include "Ravl/Image/Image.hh"
#include "Ravl/Array2d.hh"
#include "Ravl/Complex.hh"

namespace RavlImageN {
using namespace RavlN;

  //! userlevel=Normal
  //! example = exGaborComplex.cc

  //: Gabor filters

  // This class generates a set of complex Gabor filters of varying
  // frequency and orientation.  For more detail, see <a
  // href="../../../html/Gabor.pdf">complex Gabor filter theory</a>.

  class GaborComplexC {
    
  public:

  GaborComplexC (const ImageRectangleC& size, IntT ntheta, IntT nscale, bool isOffset=false);
  //: Constructor on size of image, no. of orientations, no. of scales
  //!param: isOffset - if true, every other scale is offset by &frac12; angular spacing 

  Array2dC<ImageC<RealT> > Apply(const ImageC<RealT>& in_img);
  //: Filters image <code>in_img<code> using Gabor filter bank
  // Returns the modulus of the complex images<br>
  // Array is organised as: no. of angles &times; no. of scales

  void SetFreq(RealT offset)
  { U = Min(Size.Rows(),Size.Cols())*offset; init=false; }
  //: Sets centre frequency magnitude of highest frequency filters
  // Centre frequency is expressed as fraction of sampling frequency of shorter axis<br>
  // Default is 2/5 

  void SetRadialScale(RealT ratio)
    { sratio = ratio; init = false;}
  //: Sets the ratio of centre frequencies of successive scales
  // <code>ratio</code> should be &gt; 1.<br> 
  // If <code>ratio</code> &lt; 0, ratio is instead chosen to make filters circular.<br>
  // Default is 2

  void AdjustSigma(RealT factor)
    { sigma_factor = factor; init=false; }
  //: Multiplies size of filter in <i>spatial</i> domain by <code>factor</code>

  void AdjustLambda(RealT factor)
    { lambda_factor = factor; init=false; }
  //: Adjusts &sigma;_r so that  ratio of radial to tangential filter widths in <i>spatial</i> domain is increased by <code>factor</code>
  // This is in addition to the adjustment to &sigma;_r provided by <code>AdjustSigma()</code>

  const Array2dC<ImageC<ComplexC> > Mask() const
    { return mask; }
  //: Const access to frequency masks as 2D array
  // Array is organised as: no. of angles &times; no. of scales

 protected:

  ImageRectangleC Size; // FFT size
  IntT Ntheta; // no. of filter angles
  IntT Nscale; // no. of filter scales
  RealT U;       // offset of prototype filter centre frequency as proportion of sampling frequency
  RealT sratio;  // ratio of filter scales: consecutive sigma_r's
  RealT sigma_factor; // manual adjustment to sigma
  RealT lambda_factor; // manual adjustment to lambda

  bool isoffset; // if true, alternate scales are offset by 1/2 filter separation
  Array2dC<ImageC<ComplexC> > mask;
  bool init;

  void Init();
  //: Initialises frequency domain masks

};

}

#endif
