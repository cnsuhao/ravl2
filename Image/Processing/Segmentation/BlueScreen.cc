// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImageProc
//! file="Ravl/Image/Processing/Segmentation/BlueScreen.cc"

#include "Ravl/Image/BlueScreen.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN
{
  void BlueScreenC::Apply(ImageC<ByteT>& mask, 
			  const ImageC<ByteRGBValueC> &image) const
  {
    const int const_thresh(thresh);
    for(Array2dIter2C<ByteT,ByteRGBValueC> i(mask,image); i; i++)
    {
      ByteRGBValueC &px = i.Data2();
      i.Data1() = ((((int) px.Blue() * 2) - ((int) px.Red() + px.Green())) < const_thresh);
    }
  }

  void BlueScreenC::Apply(ImageC<ByteT>& mask,
			  const ImageC<ByteYUV422ValueC> &image) const
  {
    const int const_thresh(100*thresh);
    Array2dIterC<ByteT> idest(mask);
    Array2dIterC<ByteYUV422ValueC> isrc(image);

    while (isrc && idest)
    {
      int u = (*isrc).UV();
      isrc++;
      int v = (*isrc).UV();
      isrc++;
      ByteT b = ((100*u-23*v) < const_thresh) ? 255 : 0;
      idest.Data() = b;
      idest++;
      idest.Data() = b;
      idest++;
      
    }
  }
}
