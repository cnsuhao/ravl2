///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/RealRGBValue.hh"
#include "Ravl/TypeName.hh"
//#include "Ravl/DP/Converter.hh"
//#include "Ravl/Array2dIter2.hh"

namespace RavlN {

  void InitImgIORealRGB()
  {}
  
  static TypeNameC type1(typeid(ImageC<RealRGBValueC>),"ImageC<RealRGBValueC>");  

  FileFormatStreamC<ImageC<RealRGBValueC> > FileFormatStream_ImageC_RealRGBValueC;
  FileFormatBinStreamC<ImageC<RealRGBValueC> > FileFormatBinStream_ImageC_RealRGBValueC;
}
