// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////
//! rcsid="$Id: testXMLVideoIO.cc 7435 2009-12-17 11:57:53Z alexkostin $"
//! lib=RavlImageIO
//! file="Ravl/Image/ImageIO/exImgIO.cc"
//! userlevel=Normal
//! author="Kieron Messer"
//! date="09/09/09"
//! docentry="Ravl.API.Images"

//: Loading and saving images.

#include "Ravl/Option.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/XMLFactory.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/DP/PlayControl.hh"

int main(int argc,char **argv) {  
  using namespace RavlImageN;
  
  OptionC option(argc,argv);
  StringC xmlFile = option.String("i","video.xml","Input XML factory file");
  option.Check();
  
  XMLFactoryC::RefT mainFactory = new XMLFactoryC(xmlFile);
  XMLFactoryContextC factory(*mainFactory);

  DPIPortC<ImageC<ByteT> > video;
  
  if(!factory.UseComponent("Video", video)) {
    cerr << "Failed to open video \n";
    return 1;
  }
  
  // and display
  ImageC<ByteT>im;
  while(video.Get(im))
    Save("@X", im);
  
  std::cerr << "Done. \n";
  
  
  return 0;
}
