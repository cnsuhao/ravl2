// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLEXTIMGIO_HEADER
#define RAVLEXTIMGIO_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id: ExtImgIO.hh 5240 2005-12-06 17:16:50Z plugger $"
//! userlevel=Develop
//! file="Ravl/Image/ExternalImageIO/ExtImgIO.hh"
//! lib=RavlExtImgIO
//! docentry="Ravl.API.Images.IO.Formats"
//! author="Charles Galambos"
//! date="25/05/2000"

namespace RavlImageN {
  extern void InitJPEGCompressConv();
  extern void InitTIFFFormat();
  extern void InitJPEGFormat();
  extern void InitPNGFormat();
}

#endif
