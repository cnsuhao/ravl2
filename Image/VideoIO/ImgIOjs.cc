// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! userlevel=Normal
//! rcsid="$Id$"
//! lib=RavlVideoIO
//! author="Charles Galambos"
//! date="24/03/2002"

#include "Ravl/Image/ImgIOjs.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/Array2dIter.hh"
#include "Ravl/BinStream.hh"

#define DODEBUG 1
#if DODEBUG
#define ONDEBUG(x) x
#else
#define ONDEBUG(x)
#endif

namespace RavlImageN {

  //: Constructor.
  // This constructs with the basic yuv format.
  
  DPImageJSBaseBodyC::DPImageJSBaseBodyC()
    : frameSize(0),
      frameNo(0),
      seqSize((UIntT) -1)
  { }

  //: Read header from stream.
  
  bool DPImageJSBaseBodyC::ReadHeader(IStreamC &is) {
    ByteT magic[4];
    is.read((char *) magic,4);
    BinIStreamC bis(is);
    if((((int) magic[0]) != 0) || (((int) magic[1]) != 0x6) || 
       (((int) magic[2]) != 0x9) || (((int) magic[3]) != ((int) 0xce))) {
      cerr << "DPImageJSBaseBodyC::ReadHeader(), Bad magic number. \n";
      return false;
    }
    int chan,unk[10],width,height;
    bis >> chan;   // Typical 3.
    bis >> unk[0]; // Typical 3007 2989 ...
    bis >> blockSize; // 16384, offset of first frame.
    bis >> unk[1]; // Typical 1
    bis >> width; // width.
    bis >> height; // height.
    bis >> unk[2]; // Typical 1008
    bis >> unk[3]; // Typical 14656
    bis >> unk[4]; // Typical ???
    
    pad = 0;
#if DODEBUG
    cerr << "Unknown :";
    for(int i = 0;i < 5;i++)
      cerr << " " << unk[i];
    cerr << "\n";
#endif
    ONDEBUG(cerr << "Channels=" << chan << " BlockSize=" << blockSize << " Width=" << width << " Height=" << height << "\n");
    rect = ImageRectangleC(height,width);
    UIntT imgSize = (height * width * 2);
    
    // Fixme: The image size may be slightly larger, as it might contain out of frame info.
    
    UIntT rem = (imgSize % blockSize);
    if(rem != 0)
      frameSize = imgSize + (blockSize - rem);
    else 
      frameSize = imgSize;
    
    offset = frameSize;
    
    ONDEBUG(cerr << "FrameSize=" << frameSize << "  ImageSize=" << imgSize << " rem=" << (blockSize - rem) << "\n");
    return true;
  }
  
  
  /////////////////////////////////////////////////////////
  

  ///////////////////////////
  //: Constructor from stream 

  DPIImageJSBodyC::DPIImageJSBodyC(const IStreamC &nStrm)
    : strm(nStrm)
  {
    if(!strm) {
      cerr << "DPIImageJSBodyC::DPIImageJSBodyC(IStreamC), Passed bad stream. \n";
      return ;
    }
    ReadHeader(strm);
    ONDEBUG(cerr << "DPIImageJSBodyC::DPIImageJSBodyC(const IStreamC &), Sequence size=" << seqSize << "\n");
  }

  //: Constructor from a file.

  DPIImageJSBodyC::DPIImageJSBodyC(const StringC &fileName) 
    : strm(fileName)
  {
    FilenameC fn(fileName);
    ReadHeader(strm);
    seqSize = (StreamSizeT) fn.FileSize() / (StreamSizeT) frameSize;
    ONDEBUG(cerr << "DPIImageJSBodyC::DPIImageJSBodyC(const StringC &), Sequence size=" << seqSize << "\n");
  }

  
  ///////////////////////////
  //: Seek to location in stream.
  // Returns false, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool DPIImageJSBodyC::Seek(UIntT off) {
    if(off == ((UIntT) -1))
      return false; // File to big.
    frameNo = off;// Wait to after seek in case of exception.
    return true;
  }
  
  //: Delta Seek, goto location relative to the current one.
  
  bool DPIImageJSBodyC::DSeek(IntT off) {
    if(off < 0) {
      if((-off) > (IntT) frameNo)
	return false; // Seek off begining of data.
    }
    frameNo = frameNo + off; // Wait till after seek in case of exception.
    return true;
  }
  
  //: Find current location in stream.
  UIntT DPIImageJSBodyC::Tell() const { 
    return frameNo; 
  }
  
  //: Find the total size of the stream.
  UIntT DPIImageJSBodyC::Size() const { 
    return SeqSize(); 
  }

  /////////////////////////
  //: Get next image.
  
  ImageC<ByteYUV422ValueC> DPIImageJSBodyC::Get() {
    ImageC<ByteYUV422ValueC> head;
    Get(head);
    return head;
  }
  
  //////////////////////////
  //: Get next image.
  
  bool DPIImageJSBodyC::Get(ImageC<ByteYUV422ValueC> &head) { 
    if(!strm.good())
      return false;
    
    strm.Seek(CalcOffset(frameNo));
    
    // Check input image.
    
    if(head.Rectangle() != rect) {
      head = ImageC<ByteYUV422ValueC>(rect);
      strm.read((char *) &(head[rect.Origin()]),rect.Area() * sizeof(ByteYUV422ValueC));
    } else {
      IntT width = head.Cols() * sizeof(ByteYUV422ValueC);
      IndexC atrow = head.TRow();
      IndexC offset = head.LCol();
      IndexC brow = head.BRow();
      for(;atrow <= brow;atrow++) 
	strm.read((char *) &(head[atrow][offset]),width);
    }
    //ONDEBUG(cerr << "Reading image... \n");
    
    frameNo++;
    return true; 
  }
  
  //////////////////////////////////////////////////////////////////////////////////////
  
  //: Constructor from stream.  
  
  DPOImageJSBodyC::DPOImageJSBodyC(const OStreamC &nStrm)
    : strm(nStrm)
  {
    RavlAssertMsg(0,"Not implemented. ");
    if(!strm)
      cerr << "DPOImageJSBodyC::DPOImageJSBodyC(OStreamC), Passed bad stream. \n";
  }
  
  //: Seek to location in stream.
  // Returns false, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool DPOImageJSBodyC::Seek(UIntT off) {
    if(off == ((UIntT)-1))
      return false; 
    strm.Seek(CalcOffset(off));
    frameNo = off;// Wait to after seek in case of exception.
    if(frameNo > seqSize)
      seqSize = frameNo;
    return true;
  }
  
  //: Delta Seek, goto location relative to the current one.
  
  bool DPOImageJSBodyC::DSeek(IntT off) {
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
  
  UIntT DPOImageJSBodyC::Tell() const { 
    return frameNo; 
  }

  //: Find the total size of the stream.
  
  UIntT DPOImageJSBodyC::Size() const { 
    return SeqSize(); 
  }

  /////////////////////////////////
  // Put next frame into stream.
  // Returns false if can't.
  
  bool DPOImageJSBodyC::Put(const ImageC<ByteYUV422ValueC> &Img) {
    if(!strm.good())
      return false;
    
    RavlAssertMsg(0,"DPOImageJSBodyC::Put(), Not implemented. ");
    // -----------
    
    frameNo++;
    if(frameNo > seqSize)
      seqSize = frameNo;
    return strm.good();
  }
  
  
  
  //////////////////////////////////////////////////////
  
  //: Constructor from filename.  
  
  DPIImageJSC::DPIImageJSC(const StringC &fn)
    : DPEntityC(*new DPIImageJSBodyC(fn))
  {}

  //: Constructor from filename.  
  
  DPOImageJSC::DPOImageJSC(const StringC &fn)
    : DPEntityC(*new DPOImageJSBodyC(fn))
  {}
}
