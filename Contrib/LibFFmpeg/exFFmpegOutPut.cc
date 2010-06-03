// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id: exFFmpegOutPut.cc 6742 2008-04-21 16:37:43Z robowaz $"
//! lib=RavlLibFFmpeg
//! author = "Simon"
//! file="Ravl/Contrib/LibFFmpeg/exFFmpegOutPut.cc"
//! docentry = "Ravl.API.Images.Video.Video IO.LibFFmpeg"

#include "Ravl/Option.hh"
#include "Ravl/IO.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

using namespace RavlN;
using namespace RavlImageN;

int main(int argc,char **argv) 
{  
  OptionC option(argc,argv);
  StringC fn = option.String("i","grabfile.grab","Input filename");
  StringC output = option.String("o","out.mpg","Output file name.");
  option.Check();
  
  RealT val;
  val = 21;
  
    DPIPortC<ImageC<ByteRGBValueC>  > in;
    if(!OpenISequence(in,fn)) {
      // Failed to open input file.
      // Report an error...
      cerr << "error opening input file" << endl;
      return 1;
    }

    DPOPortC<ImageC<ByteRGBValueC>  > out;
    if(!OpenOSequence(out,output)) {
      // Failed to open output file.
      // Report an error..
      cerr << "error opening output file" << endl;
      return 1;
    }

    //set compression.

    val = 27;
    out.SetAttr("compression",val);

    ImageC<ByteRGBValueC> value;
    while(in.Get(value)) { // Get next image, stop if none.
      out.Put(value);
    }
  
  return 0;
}

