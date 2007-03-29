// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlImage
//! file="Ravl/Image/Base/ImageConv.cc"

#include "Ravl/Image/ImageConvSSE.hh"

#include "Ravl/CPUID.hh"

namespace RavlImageN
{

//magic trick which changes the usual image convertion behaviour
typedef ImageC<ByteT> DoubleImageCT2ByteImageCT_T(const ImageC< RealT> &Dat);
extern DoubleImageCT2ByteImageCT_T *DoubleImageCT2ByteImageCT_F;

static int SetNewFunctions()
{
  if(SSE2())
  {
    //cout << "ImageConvSSE: Using SSE instructions." << endl;
    DoubleImageCT2ByteImageCT_F = &RealImage2ByteImageSSE2;
  }
  else
  {
    //cout << "ImageConvSSE: CPU does not have SSE instructions." << endl;
  }
  return 1;
}

static int a = SetNewFunctions();

}
