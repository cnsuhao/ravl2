#include "Ravl/Image/GaborComplex.hh"
#include "Ravl/Math.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter3.hh"
#include "Ravl/FFT2d.hh"

using namespace RavlImageN;
using namespace RavlConstN;


GaborComplexC::GaborComplexC (const ImageRectangleC& size, IntT ntheta, IntT nscale, bool isOffset)
  : Size(size), Ntheta(ntheta), Nscale(nscale), sratio(2),
    sigma_factor(1.0), lambda_factor(1.0),
    isoffset(isOffset), mask(ntheta,nscale), init(false)
{ SetFreq(0.4); }

Array2dC<ImageC<RealT> > GaborComplexC::Apply(const ImageC<RealT>& in)
{
  if (!init) Init();
  Array2dC<ImageC<ComplexC> > tmp(mask.Frame());
  Array2dC<ImageC<RealT> > out(mask.Frame());
  FFT2dC fft(in.Rows(), in.Cols());
  FFT2dC fft_inv(in.Rows(), in.Cols(), true);
  ImageC<ComplexC> fft_im = FFT2dC::FFTShift(fft.Apply(in));
  fft_im.ShiftArray(-(fft_im.Frame().Center()));
  for (Array2dIter3C<ImageC<ComplexC>,ImageC<ComplexC>, ImageC<RealT> > i(mask,tmp,out); i; ++i) {
    i.Data2() = i.Data1()*fft_im;
    i.Data2().ShiftArray(i.Data2().Frame().Center());
    i.Data2() = FFT2dC::FFTShift(i.Data2());
    i.Data2() = fft_inv.Apply(i.Data2());
    i.Data3() = FFT2dC::Mag(i.Data2());
  }
  return out;
}


void GaborComplexC::Init()
{
  // sigma is tangential filter size
  RealT sigma = 1.0/(3.0*U*sin(pi/(2.0*Ntheta))) * sigma_factor; 
  // lambda is ratio of radial to tangential size.
  RealT lambda(1.0); 
  if (isoffset) {
    RealT t  = Sin(pi*(Ntheta+1)/(2*Ntheta));
    // s_c is scale ratio to generate circular filters
    RealT s_c = (1.0+t-t*t + Sqrt((1+2.0*t)*(1.0-t*t)))/(t*t);
    if (sratio <= 0.0) sratio = s_c;
    else lambda = (sratio+1.0)/(sratio-1.0) * (s_c-1.0)/(s_c+1.0);
  }
  else
    if (sratio <= 0.0) sratio = (1.0+sin(pi/(2.0*Ntheta))) / (1.0-sin(pi/(2.0*Ntheta)));
    else lambda = sin(pi/(2.0*Ntheta)) * (sratio+1.0)/(sratio-1.0);
  lambda *= lambda_factor;

  for (IntT iscale=0; iscale < Nscale; ++iscale) {
    RealT scale = pow(sratio, iscale);
    RealT offset = isoffset ? (iscale%2) * pi/(2*Ntheta) : 0;
    for (IntT itheta=0; itheta < Ntheta; ++itheta) {
      RealT theta = itheta*pi/Ntheta + offset;
      mask[itheta][iscale] = ImageC<ComplexC>(Size);
      mask[itheta][iscale].ShiftArray(-(Size.Center()));
      mask[itheta][iscale].Fill(0.0);
      for (Array2dIterC<ComplexC> i(mask[itheta][iscale]); i; ++i) {
        Index2dC p(i.Index());
        RealT r1 =  p[0]*Cos(theta) + p[1]*Sin(theta);
        RealT c1 = -p[0]*Sin(theta) + p[1]*Cos(theta);
        *i = exp(-2.0*pi*Sqr(sigma)*(Sqr(lambda*(scale*c1-U))+Sqr(scale*r1)));
      }
    }
  }
  init = true;
}

