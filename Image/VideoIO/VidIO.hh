// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef VIDIOINIT_HEADER
#define VIDIOINIT_HEADER 1
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! file="amma/Image/VidIO/VidIO.hh"
//! lib=RavlImage
//! docentry="Ravl.Images.Video.Formats"
//! userlevel=Develop
//! example=exImgSeq.cc
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
  
}
#endif
