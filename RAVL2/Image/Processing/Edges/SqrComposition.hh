// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_SQRCOMPOSITION_HEADER
#define RAVLIMAGE_SQRCOMPOSITION_HEADER 1
//////////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="Ravl/Image/Processing/Edges/SqrComposition.hh"
//! lib=RavlImageProc
//! docentry="Ravl.API.Images.Misc"
//! author="Charles Galambos"
//! date="04/07/2000"

#include "Ravl/Types.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Tuple2.hh"

namespace RavlImageN {
  
  //! userlevel=Develop
  //: Square Composition.
  // 
  
  class SqrCompositionC  {
  public:
    SqrCompositionC()
    {}
    //: Default constructor.
    
    bool Apply(const ImageC<RealT> &inImgDx,const ImageC<RealT> &inImgDy,ImageC<RealT> &out) const;
    //: Square composition of inImg1 and inImg2.

    bool Apply(const ImageC<TFVectorC<RealT,2> > &inImg,ImageC<RealT> &out) const;
    //: Calculate the maginute image.
    
    bool Apply(const Tuple2C<ImageC<RealT>,ImageC<RealT> > &inImg,ImageC<RealT> &out) const
    { return Apply(inImg.Data1(),inImg.Data2(),out); }
    //: Square composition of inImg1 and inImg2.
    
  protected:
    void DoSqrComp(ImageC<RealT> &res,ImageC<RealT> &img1,ImageC<RealT> &img2,IntT startRow,IntT endRow) const;
    
  };

}

#endif
