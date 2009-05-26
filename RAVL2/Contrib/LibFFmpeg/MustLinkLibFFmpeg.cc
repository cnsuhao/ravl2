// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, Omniperception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
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
