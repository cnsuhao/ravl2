// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: InitLib1394dc.cc 4777 2005-01-18 14:28:18Z ees1wc $"
//! lib=RavlImgIO1394dc
//! file="Ravl/Contrib/dc1394/InitLib1394dc.cc"


namespace RavlImageN {
  extern void Init1394dcFormat();
}

void Init1394dc() {
  RavlImageN::Init1394dcFormat();
}
