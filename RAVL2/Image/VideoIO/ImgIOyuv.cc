// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
////////////////////////////////////////////////////
//! userlevel=Normal
//! rcsid="$Id: ImgIOyuv.cc 3813 2003-12-11 12:08:36Z craftit $"
//! lib=RavlVideoIO
//! file="Ravl/Image/VideoIO/ImgIOyuv.cc"

#include "Ravl/Image/ImgIOyuv.hh"
#include "Ravl/OS/Filename.hh"
#include "Ravl/Array2dIter.hh"

namespace RavlImageN {
  
  //: Setup for yuv variant.
  // Where size in the size of the Y image.
  
  bool DPImageYUVBaseBodyC::SetupForVariant(const Index2dC &size) {
    // Work out frame size.
    frameSize = (size.Row().V() * size.Col().V()) * 2;
    // Setup image rectangle.
    rect.RowRange() = IndexRangeC(0,size.Row()-1);
    rect.ColRange() = IndexRangeC(0,size.Col()-1);
    
    RavlAssert(!(rect.Rows() &1)); // Must be even number of rows.
    RavlAssert(!(rect.Cols() &1)); // Must be even number of columns.
    return true;
  }
  
  /////////////////////////////////////////////////////////
  
  ///////////////////////////
  //: Constructor from stream 

  DPIImageYUVBodyC::DPIImageYUVBodyC(const IStreamC &nStrm,const Index2dC &size)
    : DPImageYUVBaseBodyC(size),
      strm(nStrm)
  {
    if(!strm)
      cerr << "DPIImageYUVBodyC::DPIImageYUVBodyC(IStreamC), Passed bad stream. \n";
    else {
      if(!nStrm.Name().IsEmpty()) {
	FilenameC tmp(nStrm.Name());
	// Stream must be good, so if file doesn't exist maybe its
	// some kind of named pipe.
	if(tmp.Exists())
	  SetSequenceSize (tmp.FileSize() / frameSize);
      }
    }
  }
  
  ///////////////////////////
  //: Seek to location in stream.
  // Returns false, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool DPIImageYUVBodyC::Seek(UIntT off) {
    if(off == ((UIntT) -1))
      return false; // File to big.
    strm.Seek(CalcOffset(off));
    frameNo = off;// Wait to after seek in case of exception.
    return true;
  }
  
  //: Delta Seek, goto location relative to the current one.
  
  bool DPIImageYUVBodyC::DSeek(IntT off) {
    if(off < 0) {
      if((-off) > (IntT) frameNo)
	return false; // Seek off begining of data.
    }
    UIntT nfrmno = frameNo + off;
    strm.Seek(CalcOffset(nfrmno));
    frameNo = nfrmno; // Wait till after seek in case of exception.
    return true;
  }
  
  //: Find current location in stream.
  UIntT DPIImageYUVBodyC::Tell() const { 
    return frameNo; 
  }
  
  //: Find the total size of the stream.
  UIntT DPIImageYUVBodyC::Size() const { 
    return SeqSize(); 
  }

  /////////////////////////
  //: Get next image.
  
  ImageC<ByteYUVValueC> DPIImageYUVBodyC::Get() {
    ImageC<ByteYUVValueC> head;
    Get(head);
    return head;
  }
  
  //////////////////////////
  //: Get next image.
  
  bool DPIImageYUVBodyC::Get(ImageC<ByteYUVValueC> &head) { 
    if(!strm.good())
      return false;
    
    // Check input image.
    if(head.Rectangle() != rect)
      head = ImageC<ByteYUVValueC>(rect);
    
    
    // --------------------
    
    char buff[4];
    for(Array2dIterC<ByteYUVValueC> it(head);it.IsElm();it.Next()) {
      strm.read(buff,4);
      const char u = buff[0] - 128;
      const char v = buff[2] - 128;
      it.Data().U() = u;
      it.Data().V() = v;
      it.Data().Y() = buff[1];
      it.Next();
      it.Data().U() = u;
      it.Data().V() = v;
      it.Data().Y() = buff[3];
    }
    
    // --------------------
    if(!strm.good())
      return false;
    frameNo++;
    return true; 
  }
  
  //////////////////////////////////////////////////////////////////////////////////////
  
  //: Constructor from stream.  
  
  DPOImageYUVBodyC::DPOImageYUVBodyC(const OStreamC &nStrm,const Index2dC &size)
    : DPImageYUVBaseBodyC(size),
      strm(nStrm)
  {
    if(!strm)
      cerr << "DPOImageYUVBodyC::DPOImageYUVBodyC(OStreamC), Passed bad stream. \n";
  }
  
  //: Seek to location in stream.
  // Returns false, if seek failed. (Maybe because its
  // not implemented.)
  // if an error occurered (Seek returned False) then stream
  // position will not be changed.
  
  bool DPOImageYUVBodyC::Seek(UIntT off) {
    if(off == ((UIntT)-1))
      return false; 
    strm.Seek(CalcOffset(off));
    if(!strm.good())
      return false;
    frameNo = off;// Wait to after seek in case of exception.
    if(frameNo > seqSize)
      seqSize = frameNo;
    return true;
  }
  
  //: Delta Seek, goto location relative to the current one.
  
  bool DPOImageYUVBodyC::DSeek(IntT off) {
    if(off < 0) {
      if((-off) > ((IntT) frameNo))
	return false; // Seek off begining of data.
    }
    UIntT nfrmno = frameNo + off;
    strm.Seek(CalcOffset(nfrmno));
    if(!strm.good())
      return false;
    frameNo = nfrmno; // Wait to after seek in case of exception.
    if(frameNo > seqSize)
      seqSize = frameNo;
    return true;
  }
  
  //: Find current location in stream.
  
  UIntT DPOImageYUVBodyC::Tell() const { 
    return frameNo; 
  }

  //: Find the total size of the stream.
  
  UIntT DPOImageYUVBodyC::Size() const { 
    return SeqSize(); 
  }

  /////////////////////////////////
  // Put next frame into stream.
  // Returns false if can't.
  
  bool DPOImageYUVBodyC::Put(const ImageC<ByteYUVValueC> &Img) {
    const IntT rows = rect.Rows();
    const IntT cols = rect.Cols();
    if(!strm.good())
      return false;
    // -----------
    
    IntT v_offset = (rows - Img.Rows()) / 2;
    IntT h_offset = (cols - Img.Cols()) / 2;
    
    for (IndexC r = -v_offset; r < rows-v_offset; ++r) {
      if ((r >= 0) && (r < Img.Rows())) {
	for (IndexC c = -h_offset; c < cols-h_offset; ++c) {
	  if ((c >= 0) && (c < Img.Cols())) {
	    if (is_odd(c))  
	    strm.put(Img[r+Img.TRow()][c+Img.LCol()].V()+128);
	  else  
	    strm.put(Img[r+Img.TRow()][c+Img.LCol()].U()+128);
	    strm.put(Img[r+Img.TRow()][c+Img.LCol()].Y());
	  } else { 
	    strm.put(128); 
	    strm.put(0); 
	  }
	}
      } else {
	for (IndexC c = -h_offset; c < cols-h_offset; ++c) { 
	  strm.put(128);
	  strm.put(0);
	}
      }
    }
    
    // -----------
    
    frameNo++;
    if(frameNo > seqSize)
      seqSize = frameNo;
    return strm.good();
  }
  
  
  
  //////////////////////////////////////////////////////
  
  //: Constructor from filename.  
  
  DPIImageYUVC::DPIImageYUVC(const StringC &fn)
    : DPEntityC(*new DPIImageYUVBodyC(IStreamC(fn)))
  {}

  //: Constructor from filename.  
  
  DPOImageYUVC::DPOImageYUVC(const StringC &fn)
    : DPEntityC(*new DPOImageYUVBodyC(OStreamC(fn)))
  {}
}
