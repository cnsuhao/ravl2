// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id: MustLinkAVIFile.cc 4777 2005-01-18 14:28:18Z ees1wc $"
//! lib=RavlAVIFile
//! file="Ravl/Contrib/AVIFile/MustLinkAVIFile.cc"


namespace RavlImageN {
  extern void InitAVIFileFormat();
  void MustLinkAVIFile() { 
    InitAVIFileFormat();
  }
}
