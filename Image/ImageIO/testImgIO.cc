// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
/////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlImage
//! file="Ravl/Image/ImageIO/testImgIO.cc"

#include "Ravl/Option.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/Array2dIter2.hh"


using namespace RavlN;

//extern void InitDPImageIO(void);

int main(int argc,char **argv) {  
  OptionC option(argc,argv,true);
  StringC filename = option.String("f","/tmp/testImgIO.abs","Working filename");
  StringC fmt = option.String("ff","","File format to use. ");
  bool verbose = option.Boolean("v",false,"Verbose mode. ");
  option.Check();
  
  //filename = filename.MkTemp();
  
  //InitDPImageIO();
  
  ImageC<IntT> x1(100,100);
  IntT counter = 1;
  for(Array2dIterC<IntT> it(x1);it.IsElm();it.Next()) 
    it.Data() = counter++;
  
  if(!Save(filename,x1,fmt,verbose)) {
    cerr << "Failed to save data. \n";
    return 1;
  }

  ImageC<IntT> x2;
  
  if(!Load(filename,x2,"",verbose)) {
    cerr << "Failed to load data. \n";
    return 1;
  }
  if(verbose)
    cout << "Image size:" << x2.Rectangle() << endl;
  for(Array2dIter2C<IntT,IntT> it(x1,x2);it.IsElm();it.Next()) {
    if(it.Data1() != it.Data2()) {
      cerr << "Image contents mis-match \n";
      return 1;
    }
  }
  cout << "TEST PASSED. \n";
  return 0;
}
