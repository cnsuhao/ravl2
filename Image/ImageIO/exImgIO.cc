/////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/Option.hh"
#include "amma/DP/FileFormatIO.hh"
#include "amma/ByteImag.hh"
#include "amma/RGBImage.hh"
#include "amma/Image/ImgIO.hh" // For InitDPImageIO().

int main(int argc,char **argv) {  
  OptionC option(argc,argv,TRUE);
  FilenameC infile = option.String("i","testi.pgm","Input filename");
  FilenameC output = option.String("o","testo.pgm","Output filename");
  StringC ifmt = option.String("if","","Input format");
  StringC ofmt = option.String("of","","Output format");
  BooleanT viaByte = option.Boolean("bw",TRUE,"Convert via grey scale image. ");
  BooleanT verbose = option.Boolean("v",FALSE,"Verbose mode ");
  option.Check();

  // The follow function is needed to initalise the Image IO library.
  // it need only be called once in your main program.  Hopefully
  // the need for this will be removed in the near future.
  
  InitDPImageIO();
  
  // The following line says use the amma StdIO Load() and Save() functions.
  // you can also use these functions as StdIO::Load() StdIO::Save(), but
  // its cleaner to do it this way.  See C++ documentation on namespaces for
  // more information.
  
  using namespace StdIO;
  
  if(viaByte) {
    // Convert via a byte image.
    
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
