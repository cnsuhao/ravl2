// This file is part of RAVL, Recognition And Vision Library
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////
//! rcsid="$Id: RAVLVidIMPEG.cc 1121 2002-05-13 16:52:55Z craftit $"
//! lib=RavlMPEG
//! file="Ravl/Image/ExternalImageIO/ExtImgIO.cc"

namespace RavlImageN {

  extern void InitMPEGIFormat();

  void ExtVidIO_Init() {
    InitMPEGIFormat();
  }
}

