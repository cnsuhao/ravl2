// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI2D

#include "Ravl/GUI/RawCanvas.hh"
#include <gtk/gtk.h>
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

// Some raw canvas ops that use images....

namespace RavlGUIN {
  
  //: Draw an image into the canvas with its origin offset by 'offset'.
  // Note: You have to include the RavlGUI2d library to use this function.
  
  void RawCanvasBodyC::GUIDrawImage(const ImageC<ByteRGBValueC> &img,const Index2dC &offset,bool ignoreImageOrigin) {
    //cerr << "RawCanvasBodyC::GUIDrawImage(), Called.  Img=" << img.Frame() << " Offset=" << offset << "\n";
    if(img.IsEmpty())
      return;
    Index2dC at = offset;
    if(!ignoreImageOrigin)
      at += img.Frame().Origin();
    gdk_draw_rgb_image(DrawArea(),
		       widget->style->black_gc,
		       at[1].V(),at[0].V(),
		       img.Cols(),img.Rows(),
		       GDK_RGB_DITHER_NORMAL,
		       (unsigned char *) const_cast<ImageC<ByteRGBValueC> &>(img).Row(img.TRow()),
		       img.Stride() * sizeof(ByteRGBValueC));
    
  }

  //: Draw an image into the canvas with its origin offset by 'offset'.
  // Note: You have to include the RavlGUI2d library to use this function.
  
  void RawCanvasBodyC::GUIDrawImage(const ImageC<ByteT> &img,const Index2dC &offset,bool ignoreImageOrigin) {
    if(img.IsEmpty())
      return;
    Index2dC at = offset;
    if(!ignoreImageOrigin)
      at += img.Frame().Origin();
    gdk_draw_gray_image(DrawArea(),
			widget->style->black_gc,
			at[1].V(),at[0].V(),
			img.Cols(),img.Rows(),
			GDK_RGB_DITHER_NORMAL,
			const_cast<ImageC<ByteT> &>(img).Row(img.TRow()),
			img.Stride());
  }
  
}
