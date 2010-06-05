////////////////////////////////////////////////////////
//! rcsid="$Id: ImgIOStreams.cc 4 2001-04-11 12:45:55Z craftit $"

// Streaming file format for some standard images.

#include "amma/DP/FileFormatStream.hh"
#include "amma/ByteImag.hh"
#include "amma/RGBImage.hh"
#include "amma/YUVImage.hh"
#include "amma/IntImage.hh"

void ForceIncStdImageStream()
{ 
  //  ForceIncFileFormatConv(); 
}


// File formats.
// Stream formats for those type that don't have another convient format.
