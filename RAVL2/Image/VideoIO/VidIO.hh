// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_VIDIOINIT_HEADER
#define RAVL_VIDIOINIT_HEADER 1
//////////////////////////////////////////////////
//! rcsid="$Id: VidIO.hh 6326 2007-09-17 10:31:24Z simondennis $"
//! file="Ravl/Image/VideoIO/VidIO.hh"
//! lib=RavlVideoIO
//! docentry="Ravl.API.Images.Video.Video IO"
//! userlevel=Develop
//! author="Charles Galambos"
//! date="13/05/1999"

namespace RavlImageN {
  
  extern void InitVidIO(); // This calls all the following functions.
  
  extern void InitCifFormat(); // Cif file formats
  extern void InitYUVFormat(); // Abakes yuv formats.
  extern void InitRGBFormat(); // raw rgb formats.
  extern void InitRawIOFormat(); // raw image formats.
  extern void InitSYUVFormat(); // Abekas Sequence in a single file
  extern void InitImgIOComposites(); // Composite image streams.
  extern void InitJSFormat(); // Initalise format for js files. 
  extern void InitAviFormat(); // Initalise AVI IO.
  
}
#endif
