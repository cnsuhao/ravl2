// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlExtImgIO
//! file="Ravl/Image/ExternalImageIO/exExtImgIO.cc"
//! docentry="Ravl.API.Images.IO.Formats"
//! userlevel=Normal
//! author="Charles Galambos"

#include "Ravl/Option.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

//: This is just here for convienance... same as exImgIO.cc

using namespace RavlImageN;

extern void InitPNGFormat();
extern void InitJPEGFormat();

int main(int argc,char **argv) {  
  OptionC option(argc,argv);
  StringC ifmt = option.String("if","","Input format");
  StringC ofmt = option.String("of","","Output format");
  bool viaByte = option.Boolean("bw",false,"Convert via grey scale image. ");
  bool verbose = option.Boolean("v",false,"Verbose mode ");
  StringC infile = option.String("","testi.pgm","Input filename");
  StringC output = option.String("","testo.pgm","Output filename");
  option.Check();
  
  // The following line says use the Ravl StdIO Load() and Save() functions.
  // you can also use these functions as StdIO::Load() StdIO::Save(), but
  // its cleaner to do it this way.  See C++ documentation on namespaces for
  // more information.
  
  if(viaByte) {
    // Convert via a byte image.
    if(verbose)
      cerr << "Using grey image. \n";
    
    ImageC<ByteT> bi;
    
    if(!Load(infile,bi,ifmt,verbose)) {
      cerr << "Failed to load data. \n";
      return 1;
    }
    if(verbose)
      cout << "Image size:" << bi.Rectangle() << endl;
    if(!Save(output,bi,ofmt,verbose)) {
      cerr << "Failed to save data. \n";
      return 1;
    }
  } else {
    // Convert via an rgb image.
    
    if(verbose)
      cerr << "Using colour image. \n";
    ImageC<ByteRGBValueC> rgb;
    
    if(!Load(infile,rgb,ifmt,verbose)) {
      cerr << "Failed to load data. \n";
      return 1;
    }
    if(verbose)
      cout << "Image size:" << rgb.Rectangle() << endl;
    if(!Save(output,rgb,ofmt,verbose)) {
      cerr << "Failed to save data. \n";
      return 1;
    }
  }
  
  return 0;
}
