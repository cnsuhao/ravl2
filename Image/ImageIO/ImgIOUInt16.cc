///////////////////////////////////////////////////
//! author="Charles Galambos"
//! rcsid="$Id$"

#include "Ravl/DP/FileFormatStream.hh"
#include "Ravl/DP/FileFormatBinStream.hh"
//#include "Ravl/DP/Converter.hh"
#include "Ravl/Image/Image.hh"
//#include "Ravl/Array2dIter2.hh"
#include "Ravl/TypeName.hh"

namespace RavlN {

  void InitImgIOUInt16()
    {}
  
  static TypeNameC type1(typeid(ImageC<UIntT>),"ImageC<UInt16T>");
  
  FileFormatStreamC<ImageC<UInt16T> > FileFormatStream_ImageC_UInt16T;
  FileFormatBinStreamC<ImageC<UInt16T> > FileFormatBinStream_ImageC_UInt16T;
  
}
