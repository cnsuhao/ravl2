/////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Option.hh"
#include "Ravl/DP/FileFormatIO.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Image/ByteRGBValue.hh"

int main(int argc,char **argv) {  
  using namespace RavlImageN;
  
  OptionC option(argc,argv);
  StringC infile = option.String("i","testi.pgm","Input filename");
  StringC output = option.String("o","testo.pgm","Output filename");
  StringC ifmt = option.String("if","","Input format");
  StringC ofmt = option.String("of","","Output format");
  bool viaByte = option.Boolean("bw",true,"Convert via grey scale image. ");
  bool verbose = option.Boolean("v",false,"Verbose mode ");
  option.Check();
  
  // The following line says use the Ravl StdIO Load() and Save() functions.
  // you can also use these functions as Load() Save(), but
  // its cleaner to do it this way.  See C++ documentation on namespaces for
  // more information.
  
  
  if(viaByte) {
    // Convert via a byte image.
    
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
