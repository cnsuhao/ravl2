// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! userlevel=Normal
//! rcsid="$Id: ImgIOdvsrgb.cc 3594 2003-10-24 16:56:01Z simone $"
//! lib=RavlVideoIO
//! file="Ravl/Image/VideoIO/ImgIOdvsrgb.cc"

#include "Ravl/Image/ImgIOdvsrgb.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/TypeName.hh"
#include   "Ravl/Image/Deinterlace.hh"
#include "Ravl/Image/NewGrabfileReader.hh"
#include "Ravl/Image/NewGrabfileWriter.hh"
#include "Ravl/Image/Utilities.hh"
#include "Ravl/DP/SequenceIO.hh"
#include "Ravl/BufStream.hh"
#include "Ravl/StrStream.hh"
#include "Ravl/BinStream.hh"
#include "Ravl/PointerManager.hh"
#include <fstream>
#include "Ravl/IO.hh"

#if RAVL_HAVE_UNISTD_H
#include <unistd.h>
#endif
#if RAVL_OS_WIN32
#include <stdio.h>
#endif
#if RAVL_HAVE_IO_H
#include <io.h>
#endif
#include <fcntl.h>

namespace RavlImageN {
 
  //: Constructor.
  // This constructs with the basic yuv format.
  
  DPImageDVSRGBBaseBodyC::DPImageDVSRGBBaseBodyC(const Index2dC &size)
    : frameSize(0),
      frameNo(0),
      seqSize((UIntT) -1),
      blockSize(512),
      rawMode(false),
      doneHdr(false)
  { 
    SetupForVariant(size);
  }
  
  //: Setup for rgb variant.
  // Where size in the size of the Y image.
  
  bool DPImageDVSRGBBaseBodyC::SetupForVariant(const Index2dC &size) {
    // Work out frame size.
    frameSize = (size.Row().V() * size.Col().V()) * 3;
    // Setup image rectangle.
    rect.RowRange() = IndexRangeC(0,size.Row()-1);
    rect.ColRange() = IndexRangeC(0,size.Col()-1);
    
    padSize = frameSize % blockSize;
    return true;
  }  
  
  ///////////////////////////
  //: Constructor from stream 
  
  DPIImageDVSRGBBodyC::DPIImageDVSRGBBodyC(GrabfileReader& file_reader,const IStreamC &nStrm,const Index2dC &size)
    : DPImageDVSRGBBaseBodyC(size),
      strm(nStrm),
      file_read(file_reader)
  {
    if(!file_reader.Ok()) {
      cerr << "DPIImageDVSRGBBodyC::DPIImageDVSRGBBodyC(GrabfileReader), Passed bad file writer. \n";
    }
  }
  
  //: Constructor from stream 
  
  DPIImageDVSRGBBodyC::DPIImageDVSRGBBodyC(const StringC &fn,bool useHdr) : file_read()  {
    rawMode = true;
    fd = open(fn.chars(),O_RDONLY);
  }
  
  ///////////////////////////
  //: Seek to location in stream.
  // Returns false, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occured (Seek returned False) then stream
  // position will not be changed.
  
  bool DPIImageDVSRGBBodyC::Seek(UIntT off) {
    if(off == ((UIntT) -1))
      return false; // File to big.
    strm.is().clear(); // Clear any errors.
    strm.Seek(CalcOffset(off));
    frameNo = off;// Wait to after seek in case of exception.
    return true;
  }
  
  //: Delta Seek, goto location relative to the current one.
  
  bool DPIImageDVSRGBBodyC::DSeek(IntT off) {
    if(off < 0) {
      if((-off) > (IntT) frameNo)
	return false; // Seek off begining of data.
    }
    UIntT nfrmno = frameNo + off;
    strm.is().clear(); // Clear any errors.
    strm.Seek(CalcOffset(nfrmno));
    frameNo = nfrmno; // Wait till after seek in case of exception.
    return true;
  }
  
  //: Find current location in stream.
  UIntT DPIImageDVSRGBBodyC::Tell() const
  { return frameNo; }

  //: Find the total size of the stream.
  UIntT DPIImageDVSRGBBodyC::Size() const
  { return SeqSize(); }
  
  /////////////////////////


  //: Get next image.
  
  ImageC<ByteRGBValueC> DPIImageDVSRGBBodyC::Get() {
    ImageC<ByteRGBValueC> head;
    if(!Get(head)) {
      throw DataNotReadyC("Failed to get image. ");
    }
    return head;
  }
  
  //////////////////////////
  //: Get next image.
  
  bool DPIImageDVSRGBBodyC::Get(ImageC<ByteRGBValueC> &head) { 
    if(!file_read.Ok() || file_read.HaveMoreFrames()) {
      return false;
    }
    // Check input image.
    if(head.Stride() != ((IntT) rect.Cols()) || head.Rectangle().Origin() != rect.Origin()){
      head = ImageC<ByteRGBValueC>(rect);
    }

    BufferC<char> res;
    res = file_read.GetNextFrame();
  
    //: Image dimensions for PAL.
    UIntT xDim=0, yDim=0 ;
    if(!GetDimensions(IdToVideoMode(file_read.VideoMode()),xDim,yDim)) {
  	xDim = 576 ; 
	yDim = 720 ;
        RavlIssueWarning("\nDont know which image size to use for this format ! will try 576x720"); 
    }
   
    // create an image from the buffer.
    ImageC<ByteRGBValueC> image1( xDim, yDim, (ByteRGBValueC*) & res.BufferAccess()[0], false); // image is only valid while buffer exists !

    ImageC<ByteRGBValueC> tmp;
    tmp = image1.Copy();
    head = ImageC<ByteRGBValueC>(Interlace(tmp));
    frameNo++;
    
    return true; 
  }
  
  //////////////////////////////////////////////////////////////////////////////////////
  
  //: Constructor from stream.  
  
  DPOImageDVSRGBBodyC::DPOImageDVSRGBBodyC(GrabfileWriter& file_write,const OStreamC &nStrm,const Index2dC &size)
    : DPImageDVSRGBBaseBodyC(size),
      strm(nStrm),
      file_writer(file_write)
  {
    if(!file_write.Ok()) {
      cerr << "DPOImageRGBBodyC::DPOImageRGBBodyC(OStreamC), Passed bad stream. \n";
    }
  }
  
  //: Constructor from filename
  
  DPOImageDVSRGBBodyC::DPOImageDVSRGBBodyC(GrabfileWriter& file_write,const StringC &fn,bool useHdr) : file_writer(file_write)
  {
    cerr << "DPOImageRGBBodyC::DPOImageRGBBodyC(), WARNING: Not fully implemented. \n";
    rawMode = true;
    fd = open(fn.chars(),O_RDONLY);
  }
  
  //: Seek to location in stream.
  // Returns false, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool DPOImageDVSRGBBodyC::Seek(UIntT off) {
    if(off == ((UIntT)-1))
      return false; 
    strm.Seek(CalcOffset(off));
    frameNo = off;// Wait to after seek in case of exception.
    if(frameNo > seqSize)
      seqSize = frameNo;
    return true;
  }
  
  //: Delta Seek, goto location relative to the current one.
  
  bool DPOImageDVSRGBBodyC::DSeek(IntT off) {
    if(off < 0) {
      if((-off) > ((IntT) frameNo))
	return false; // Seek off begining of data.
    }
    UIntT nfrmno = frameNo + off;
    strm.Seek(CalcOffset(nfrmno));
    frameNo = nfrmno; // Wait to after seek in case of exception.
    if(frameNo > seqSize)
      seqSize = frameNo;
    return true;
  }
  
  //: Find current location in stream.
  
  UIntT DPOImageDVSRGBBodyC::Tell() const
  { return frameNo; }
  
  //: Find the total size of the stream.
  
  UIntT DPOImageDVSRGBBodyC::Size() const
  { return SeqSize(); }
  
  /////////////////////////////////
  // Put next frame into stream.
  // Returns false if can't.
  
  bool DPOImageDVSRGBBodyC::Put(const ImageC<ByteRGBValueC> &Img) {
   
    Imgcopy = Img;
    //Work out if it is a PAL sized image or SMTPE sized image.
    if(Imgcopy.Size() == (576*720)) {
       //PAL
       if(file_writer.VideoBuffer() != 1245184) {
          //reset the video mode on the new grab file.
	  vmode = PAL;
	  bformat = BITS_8;
	  vbuffer = 1245184;
	  file_writer.Reset(vmode,bformat,vbuffer);
       }
    }
    if(Imgcopy.Size() == (1080*1920)) {
       //SMPTE274_25I
       if(file_writer.VideoBuffer() != 8294400) {
          //reset the video mode on the new grab file.
          vmode = SMPTE274_25I;
          bformat = BITS_10_DVS;
          vbuffer = 8294400;
	  file_writer.Reset(vmode,bformat,vbuffer);
       }

    }
   
    SArray1dC<char> chararray(Imgcopy.Size() * 3);
    int i =0;
    ImageC<ByteRGBValueC> dimage;
    
    dimage = DeInterlace(Imgcopy);
   
    for(Array2dIterC<ByteRGBValueC> it(dimage);it;it++)  {
       ByteRGBValueC rgc = it.Data();
       chararray[i] = (char)rgc.Red();
       chararray[i+1] = (char)rgc.Green();
       chararray[i+2] = (char)rgc.Blue();
       i+=3;
    }   
 
    file_writer.PutFrameA(chararray);
    frameNo++;
    /*if(frameNo > seqSize)
      seqSize = frameNo;
    return strm.good();*/
    return file_writer.Ok();
  }
  
  //////////////////////////////////////////////////////
  
  //: Constructor from filename.  
  
  DPIImageDVSRGBC::DPIImageDVSRGBC(GrabfileReader& file_reader,const StringC &fn)
    : DPEntityC(*new DPIImageDVSRGBBodyC(file_reader,IStreamC(fn)))
  {}
  
  //: Constructor from filename.  
  
  DPOImageDVSRGBC::DPOImageDVSRGBC(GrabfileWriter& file_write,const StringC &fn)
    : DPEntityC(*new DPOImageDVSRGBBodyC(file_write,OStreamC(fn)))
  {}
}
