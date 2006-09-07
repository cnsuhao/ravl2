// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html

%include "Ravl/Swig/Image.i"

%{
#include "Ravl/Image/Font.hh"

// The following is a fix for windows.
#ifdef DrawText
#undef DrawText
#endif
%}

namespace RavlImageN {

  class FontC {
  public:
    FontC();
    
    bool IsValid() const;
    // Is this a valid font ?
    
    Index2dC Center(StringC text) const;
    //: Get the offset to the center of the string.
    
    Index2dC Size(StringC text) const;
    //: Compute the size of image required to render 'text'.
    
    UIntT Count() const;
  };
  
  
  FontC DefaultFont();
  //: Access default font.
  
  void DrawText(const FontC &font,const ByteRGBValueC &value,const Index2dC &offset,const StringC &text,ImageC<ByteRGBValueC> &image);
  void DrawText(const FontC &font,const ByteT &value,const Index2dC &offset,const StringC &text,ImageC<ByteT> &image);
  void DrawTextCenter(const FontC &font,const ByteRGBValueC &value,const Index2dC &offset,const StringC &text,ImageC<ByteRGBValueC> &image);
  void DrawTextCenter(const FontC &font,const ByteT &value,const Index2dC &offset,const StringC &text,ImageC<ByteT> &image);
}
