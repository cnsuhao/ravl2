// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU
// General Public License (GPL). See the gpl.licence file for details or
// see http://www.gnu.org/copyleft/gpl.html
// file-header-ends-here
//////////////////////////////////////////////////////////////////
//! rcsid = "$Id: exFFmpeg.cc 5123 2005-09-27 08:39:26Z ees1wc $"
//! lib=RavlLibFFmpeg
//! author = "Warren Moore"
//! file="Ravl/Contrib/LibFFmpeg/exFFmpeg.cc"

#include "Ravl/Option.hh"
#include "Ravl/Image/LibFFmpegFormat.hh"
#include "Ravl/IO.hh"
#include "Ravl/DP/SPort.hh"
#include "Ravl/OS/Date.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/Random.hh"

using namespace RavlN;
using namespace RavlImageN;

int main(int nargs, char **argv)
{
  OptionC opts(nargs,argv);
  StringC filename = opts.String("", "in.avi", "Input AVI file.");
  bool seekStart = opts.Boolean("ss",false,"Seek to Start. ");
  opts.Check();
  
  // Check the file exists
  FilenameC fn(filename);
  if (!fn.Exists())
  {
    cerr << "Error opening file (" << filename << ")\n";
    return 1;
  }

  // Select the correct opening method
  FileFormatLibFFmpegC format;
  DPISPortC< ImageC<ByteRGBValueC> > in = format.CreateInput(filename,typeid(ImageC<ByteRGBValueC>));
  if (!in.IsValid())
  {
    cerr << "Unable to open file (" << filename << ")\n";
    return 1;
  }

  // Display the stream attributes
  DListC<StringC> attrs;
  if (in.GetAttrList(attrs))
  {
    DLIterC<StringC> it(attrs);
    while (it)
    {
      StringC value;
      if (in.GetAttr(*it, value))
        cerr << *it << " : " << value << endl;
      it++;
    }
  }
  
  if(seekStart)
    in.Seek(in.Start()+1);
  
  // Delay in seconds
  // const RealT delay = 0.1;
  
  // Load the stream
  ImageC<ByteRGBValueC> rgb;
  
  // Keep playing til the end
  while (!in.IsGetEOS())
  {
    if(!in.Get(rgb))
      break;
    
    RavlN::Save("@X", rgb);

    //Sleep(delay);
  }

  return 0;
}
