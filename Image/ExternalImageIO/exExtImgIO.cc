/////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/Option.hh"
#include "amma/DP/FileFormatIO.hh"
#include "amma/ByteImag.hh"
#include "amma/RGBImage.hh"
//#include "amma/DP/ImgIO.hh" // For InitDPImageIO().

// This is just here for convienance... same as exImgIO.cc

extern void InitPNGFormat();

extern void InitJPEGFormat();
int main(int argc,char **argv) {  
  OptionC option(argc,argv,TRUE);
  StringC ifmt = option.String("if","","Input format");
  StringC ofmt = option.String("of","","Output format");
  BooleanT viaByte = option.Boolean("bw",FALSE,"Convert via grey scale image. ");
  BooleanT verbose = option.Boolean("v",FALSE,"Verbose mode ");
  FilenameC infile = option.String("","testi.pgm","Input filename");
  FilenameC output = option.String("","testo.pgm","Output filename");
  option.Check();
  
  InitJPEGFormat();
  InitPNGFormat();
  // The following line says use the amma StdIO Load() and Save() functions.
  // you can also use these functions as StdIO::Load() StdIO::Save(), but
  // its cleaner to do it this way.  See C++ documentation on namespaces for
  // more information.
  
  using namespace StdIO;
  
  if(viaByte) {
    // Convert via a byte image.
    if(verbose)
      cerr << "Using grey image. \n";
    
    ByteImageC bi;
    
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
    RGBImageC rgb;
    
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
