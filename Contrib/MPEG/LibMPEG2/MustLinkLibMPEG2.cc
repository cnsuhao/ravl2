// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//! rcsid="$Id: MustLinkLibMPEG2.cc 4777 2005-01-18 14:28:18Z ees1wc $"
//! lib=RavlLibMPEG2
//! file="Ravl/Contrib/MPEG/LibMPEG2/MustLinkLibMPEG2.cc"

namespace RavlImageN
{
  extern void InitLibMPEG2Format();
  
  void MustLinkLibMPEG2()
  { 
    InitLibMPEG2Format();
  }
}
