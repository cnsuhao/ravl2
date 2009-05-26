// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id$"
//! lib=RavlAVIFile
//! author = "James Smith"
//! file="Ravl/Contrib/AVIFile/testAVIFile.cc"
//! docentry="Ravl.API.Images.Video.Video IO"

#include "Ravl/Option.hh"
#include "Ravl/EntryPnt.hh"
#include "Ravl/IO.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/DP/IOConnect.hh"

using namespace RavlN;
using namespace RavlImageN;

int testAVIFile(int nargs, char **argv)
{
  OptionC opts(nargs,argv);
  FilenameC input  = opts.String("i", "in.pgm", "Input video file.");
  FilenameC output = opts.String("o", "out.avi", "Output AVI file.");
  StringC strfourcc = opts.String("f", "mjpg", "Codec FOURCC value.");
  opts.Check();
  
  // Fix up FOURCC
  if (strfourcc.Size()!=4) {
    cerr << "The FOURCC value must have four characters!" << endl;
  }

  // Open file
  DPISPortC<ImageC<ByteRGBValueC> > in;
  if (!OpenISequence(in,input)) {
    cerr << "Error opening file (" << input << ")\n";
    return 1;
  }
  
  // Open AVI output
  DPOPortC<ImageC<ByteRGBValueC> > out;
  if (!OpenOSequence(out,output)) {
    cerr << "Error opening file (" << output << ")\n";
    return 1;
  }
  out.SetAttr("fourcc",strfourcc);

  // Convert
  in >> out;
  cerr << "Conversion complete!" << endl;    
  return 0;
}

RAVL_ENTRY_POINT(testAVIFile);
