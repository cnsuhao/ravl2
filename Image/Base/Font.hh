// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_FONT_HEADER
#define RAVLIMAGE_FONT_HEADER 1
////////////////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImage

#include "Ravl/SArray1d.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter2.hh"

namespace RavlImageN {
  
  //! userlevel=Normal
  //: Font.
  
  class FontC {
  public:
    FontC()
    {}
    //: Default constructor.
    // Creates an empty font.
    
    FontC(bool);
    //: Load default font.
    
    FontC(SArray1dC<ImageC<ByteT> > &nGlyphs)
      : glyphs(nGlyphs)
    {}
    //: Constructor from array of image.
    
    ImageC<ByteT> &operator[](IntT let)
    { return glyphs[let]; }
    //: Access charactor.
    
    const ImageC<ByteT> &operator[](IntT let) const
    { return glyphs[let]; }
    //: Access charactor.
    
    SArray1dC<ImageC<ByteT> > &Glyphs()
    { return glyphs; }
    //: Access image array.
    
    const SArray1dC<ImageC<ByteT> > &Glyphs() const
    { return glyphs; }
    //: Access image array.
    
    bool IsValid() const
    { return glyphs.Size() != 0; }
    //: Is this a valid font.
    
  protected:
    SArray1dC<ImageC<ByteT> > glyphs;
  };
  
  FontC LoadPSF1(const StringC &fontFile);
  //: Load PSF1 font.

  template<class DataT>
  void DrawFrame(const FontC &font,
		 ImageC<DataT> &image,
		 const DataT &value,
		 const Index2dC &offset,
		 char *text) 
  {
    Index2dC at(offset);
    const char *p = text;
    for(;*p != 0;p++) {
      const ImageC<ByteT> &gylph = font[*p];
      IndexRange2dC drawRect(at,Index2dC(at.Row() + gylph.Frame().Rows() - 1,
					 at.Col() + gylph.Frame().Cols() - 1));
      drawRect.ClipBy(image.Frame());
      if(drawRect.Area() > 0) {
	for(Array2dIter2C<DataT,ByteT> it(Array2dC<DataT>(image,drawRect),gylph);it;it++) {
	  if(it.Data2() != 0)
	    it.Data1() = value;
	}
      }
      at.Col() += gylph.Frame().Cols();
    }
  }
}

#endif
