// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlGUI
//! author="Charles Galambos"
//! date="24/9/2003"

#include "Ravl/GUI/Pixbuf.hh"

#if RAVL_USE_GTK2
#include <gdk/gdk.h>
#endif

#define DODEBUG 0
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlGUIN {
  
#if RAVL_USE_GTK2

  static void DeleteImageRef(guchar *pixels, gpointer data) {
    ONDEBUG(cerr << "DeleteImageRef(), Called. \n");
    delete ((ImageC<ByteRGBValueC> *) data);
  }

  //: Handle raw pixbuf.
  
  PixbufC::PixbufC(GdkPixbuf *rawPixBuf) 
    : pixbuf(rawPixBuf)
  { if(pixbuf != 0) gdk_pixbuf_ref(pixbuf); }
  
  //: Create from an image.
  
  PixbufC::PixbufC(const ImageC<ByteRGBValueC> &img) {
    ONDEBUG(cerr << "PixbufC::PixbufC(const ImageC<ByteRGBValueC> &), Called. \n");
    if(img.Frame().Area() > 0) {
      void *imgHandle = new ImageC<ByteRGBValueC>(img); // Create a refrence to the image.
      pixbuf = gdk_pixbuf_new_from_data ((guchar *) (&img[img.Frame().Origin()]),
					 GDK_COLORSPACE_RGB,false,8,img.Cols(),img.Rows(),img.Stride() * sizeof(ByteRGBValueC),&DeleteImageRef,imgHandle);
      gdk_pixbuf_ref(pixbuf);
    }
  }
  
  //: Create from XPM data.
  
  PixbufC::PixbufC(const char **data) {
    pixbuf = gdk_pixbuf_new_from_xpm_data (data);
    if (pixbuf != 0)
      gdk_pixbuf_ref(pixbuf);
  }
  
  //: Create from filename.
  
  PixbufC::PixbufC(const StringC &name) {
    pixbuf = gdk_pixbuf_new_from_file(name, NULL);
    if (pixbuf != 0)
      gdk_pixbuf_ref(pixbuf);
  }

  //: Destructor.
  
  PixbufC::~PixbufC() {
    if(pixbuf != 0)
      gdk_pixbuf_unref(pixbuf);
  }

  const IntT PixbufC::Rows() const
  {
    return (pixbuf != 0 ? gdk_pixbuf_get_height(pixbuf) : 0);
  }
  
  const IntT PixbufC::Cols() const
  {
    return (pixbuf != 0 ? gdk_pixbuf_get_width(pixbuf) : 0);
  }
  
#endif
}
