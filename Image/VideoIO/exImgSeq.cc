////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "amma/Option.hh"
#include "amma/DP/SequenceIO.hh"
#include "amma/ByteImag.hh"
#include "amma/Image/VidIO.hh"
#include "amma/Image/ImgIO.hh"

int main(int argc,char **argv) 
{
  // Initalise IO code...
  
  InitDPImageIO();
  InitVidIO();
  
  // Process options.
  OptionC option(argc,argv,TRUE);
  FilenameC ifilename = option.String("i","","Input stream.");
  FilenameC ofilename = option.String("o","out.abs","Output stream.");
  StringC  ifmt = option.String("if","","Input format. ");
  StringC  ofmt = option.String("of","","Output format. ");
  BooleanT verbose = option.Boolean("v",FALSE,"Verbose mode. \n");
  option.Check();
  
  using namespace StdIO;
  
  DPIPortC<ByteImageC> inputStream;
  DPOPortC<ByteImageC> outputStream;
  
  if(!OpenISequence(inputStream,ifilename,ifmt,verbose)) {
    cerr << "Failed to open input sequence '" << ifilename << "' \n";
    return 1;
  }
  
  if(!OpenOSequence(outputStream,ofilename,ofmt,verbose)) {
    cerr << "Failed to open output sequence '" << ofilename << "' \n";
    return 1;
  }
  
  // Copy stream of images from input to output.
  
  for(;;) {
    ByteImageC buff;
    if(!inputStream.Get(buff)) // End of stream ?
      break; 
    if(!outputStream.Put(buff)) {
      cerr << "ERROR: Failed to write output. \n";
      break;
    }
  }
  
  ////////////////////////////////////////////
  // Alernate main loop...
#if 0
  for(;!inputStream.IsGetEOS();) { // Is End Of Stream ?
    ByteImageC buff = inputStream.Get();
    if(!outputStream.Put(buff)) {
      cerr << "ERROR: Failed to write output. \n";
      break;
    }    
  }  
#endif  
  
  return 0;
}
