// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlMath


#include "Ravl/EntryPnt.hh"
#include "Ravl/SquareIter.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/Option.hh"

using namespace RavlN;
using namespace RavlImageN;

int Main(int argc, char* argv[])
{
  OptionC opt(argc,argv);
  IntT size = opt.Int("s",1,"size of square. ");
  bool label = opt.Boolean("l",false,"Label test. ");
  opt.Check();
  
  ImageC<ByteT> image(512,512);
  image.Fill(0);
  if(label) {
    int i = 1;
    for (SquareIterC it(size, Index2dC(255,255)); it.IsElm(); it.Next()) 
      image[it.Data()] = i++;
  } else {
    for (SquareIterC it(size, Index2dC(255,255)); it.IsElm(); it.Next()) 
      image[it.Data()]++;
  }
  if (!Save("square.pgm", image))
     cerr << "Image saving failed" << endl;

  return 0;
}

RAVL_ENTRY_POINT(Main);

