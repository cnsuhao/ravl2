// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//! rcsid="$Id: MustLinkLibFFmpeg.cc 4896 2005-04-22 15:01:34Z robowaz $"
//! lib=RavlLibFFmpeg
//! file="Ravl/Contrib/LibFFmpeg/MustLinkLibFFmpeg.cc"

namespace RavlImageN
{
  extern void InitLibFFmpegFormat();
  
  void MustLinkLibFFmpeg()
  { 
    InitLibFFmpegFormat();
  }
}
