#include "Ravl/Image/GaborComplex.hh"
#include "Ravl/Math.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"
#include "Ravl/Array2dIter3.hh"
#include "Ravl/FFT2d.hh"

using namespace RavlImageN;
using namespace RavlConstN;


GaborComplexC::GaborComplexC (const ImageRectangleC& size, IntT ntheta, IntT nscale, bool isOffset)
  : Size(size), Ntheta(ntheta), Nscale(nscale), sratio(2), subsample(1.0),
    sigma_factor(1.0), lambda_factor(1.0), isoffset(isOffset),
    mask(ntheta,nscale), centreFreq(ntheta,nscale), init(false)
{ SetFreq(0.4); }

Array2dC<ImageC<RealT> > GaborComplexC::Apply(const ImageC<RealT>& in)
{
  if (!init) Init();
  Array2dC<ImageC<RealT> > out(mask.Frame());    // modulus of result
  FFT2dC fft(in.Rows(), in.Cols());              // forward FFT
  // FFT i/p image and rotate so that d.c. is at centre to match mask
  ImageC<ComplexC> fft_im(FFT2dC::FFTShift(fft.Apply(in)));
  FFT2dC fft_inv;    // inverse FFT
  if (subsample > 1.0) 
    fft_inv = FFT2dC(in.Rows()/subsample, in.Cols()/subsample, true);
  else
    fft_inv = FFT2dC(in.Rows(), in.Cols(), true);

  for (Array2dIter3C<ImageC<ComplexC>, ImageC<RealT>, Point2dC> i(mask,out,centreFreq); i; ++i) {
    // image * mask in freq domain
    ImageC<ComplexC> result = i.Data1()*fft_im;
    // Coords of result follow 1st template, so are those of mask (i.e. origin
    // in centre)
    // NB we don't bother to rotate freqs back again as we are taking modulus
    // of complex result (so frequency shifts have no effect)
    if (subsample > 1.0) { 
      // just FFT around filter area to save time -> smaller resulting image
      ImageRectangleC smallFrame(i.Data3(), (int)(result.Rows()/subsample), (int)(result.Cols()/subsample));
      if (!result.Frame().Contains(smallFrame)) {
        if (smallFrame.TRow() < result.Frame().TRow()) {
          smallFrame.BRow() += result.Frame().TRow() - smallFrame.TRow();
          smallFrame.TRow() += result.Frame().TRow() - smallFrame.TRow();
        }
        else if (smallFrame.BRow() > result.Frame().BRow()) {
          smallFrame.TRow() += result.Frame().BRow() - smallFrame.BRow();
          smallFrame.BRow() += result.Frame().BRow() - smallFrame.BRow();
        }
        if (smallFrame.LCol() < result.Frame().LCol()) {
          smallFrame.RCol() += result.Frame().LCol() - smallFrame.LCol();
          smallFrame.LCol() += result.Frame().LCol() - smallFrame.LCol();
        }
        else if (smallFrame.RCol() > result.Frame().RCol()) {
          smallFrame.LCol() += result.Frame().RCol() - smallFrame.RCol();
          smallFrame.RCol() += result.Frame().RCol() - smallFrame.RCol();
        }
        if (!result.Frame().Contains(smallFrame)) {
          cerr << "Gabor filter panick! filter " << i.Index()
               << "\nOriginal: " << result.Frame()
               << "; Small frame: " << smallFrame << endl;
          smallFrame.ClipBy(result.Frame());
        }
      }
      // apply inverse FFT & take modulus of reduce size complex image
      i.Data2() = FFT2dC::Mag(fft_inv.Apply(ImageC<ComplexC>(result, smallFrame))); 
    }
    else {
      // apply inverse FFT & take modulus of complex image
      i.Data2() = FFT2dC::Mag(fft_inv.Apply(result));
    }
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
      // put origin at spectrum image centre
      mask[itheta][iscale].ShiftArray(-(Size.Center())); 
      for (Array2dIterC<ComplexC> i(mask[itheta][iscale]); i; ++i) {
        Index2dC p(i.Index());
        RealT r1 =  p[0]*Cos(theta) + p[1]*Sin(theta);
        RealT c1 = -p[0]*Sin(theta) + p[1]*Cos(theta);
        *i = exp(-2.0*pi*Sqr(sigma)*(Sqr(lambda*(scale*c1-U))+Sqr(scale*r1)));
      }
      centreFreq[itheta][iscale] = Point2dC(-Sin(theta),Cos(theta))*U/scale;
    }
  }

  init = true;
}

