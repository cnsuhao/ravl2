// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImage

#include "Ravl/Image/BlueScreen.hh"
#include "Ravl/Array2dIter2.hh"

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {
  
  ImageC<bool> BlueScreenC::Apply(const ImageC<ByteRGBValueC> &img) {
    ImageC<bool> ret(img.Frame());
    for(Array2dIter2C<bool,ByteRGBValueC> it(ret,img);it;it++) {
      ByteRGBValueC &px = it.Data2();
      it.Data1() = ((((int) px.Blue() * 2) - ((int) px.Red() + px.Green())) < thresh);
    }
    return ret;
  }

}
