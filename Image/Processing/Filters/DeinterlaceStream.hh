// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLIMAGE_DEINTERLACE_HEADER
#define RAVLIMAGE_DEINTERLACE_HEADER 1
////////////////////////////////////////////////////////////////////////
//! date="30/1/2003"
//! author="Charles Galambos"
//! docentry="Ravl.Images"
//! rcsid="$Id$"
//! lib=RavlImageProc

#include "Ravl/DP/StreamOp.hh"
#include "Ravl/DP/SPort.hh"
#include "Ravl/DP/SPortAttach.hh"
#include "Ravl/Average.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dSqr311Iter3.hh"

namespace RavlImageN {
  
  //! userlevel=Develop
  //: Deinterlace an incoming stream of images.
  
  template<class PixelT>
  class DeinterlaceStreamBodyC
    : public DPISPortBodyC<ImageC<PixelT> >
  {
  public:
    DeinterlaceStreamBodyC(DPIPortC<ImageC<PixelT> > &inPort,bool nEvenFieldDominant = true)
      : DPISPortBodyC<ImageC<PixelT> >(inPort),
	evenFieldDominant(nEvenFieldDominant),
	input(inPort)
    {
      state = evenFieldDominant ? 0 : 1;
      seekCtrl = DPSeekCtrlAttachC(inPort,true);
    }
    //: Constructor.
    
    DeinterlaceStreamBodyC(DPISPortC<ImageC<PixelT> > &inPort,bool nEvenFieldDominant = true)
      : evenFieldDominant(nEvenFieldDominant),
	input(inPort)
    {
      state = evenFieldDominant ? 0 : 1; 
      seekCtrl = DPSeekCtrlAttachC((const DPSeekCtrlC &) inPort);
    }
    //: Constructor.
    
    virtual StringC OpName() const
    { return StringC("deinterlace"); }
    //: Op type name.
    
    virtual ImageC<PixelT> Get()  {
      ImageC<PixelT> ret;
      if(!Get(ret))
	throw DataNotReadyC("Failed to deinterlace frame. ");
      return ret;
    }
    //: Get next piece of data.
    // May block if not ready, or it could throw an 
    // DataNotReadyC exception.
    
    virtual bool Get(ImageC<PixelT> &buff) {
      ImageC<PixelT> img;
      //cerr << "State=" << state << "\n";
      switch(state) 
	{
	case 0:
	  state = 4; // Mark as error if we get interrupted by an exception.
	  if(!input.Get(img))
	    return false;
	  Deinterlace(img,fields[0],fields[1]);
	  state = evenFieldDominant ? 3 : 2;
	  buff = fields[0];
	  return true;
	case 1:
	  state = 4; // Mark as error if we get interrupted by an exception.
	  if(!input.Get(img))
	    return false;
	  Deinterlace(img,fields[0],fields[1]);
	  state = evenFieldDominant ? 2 : 3;
	  buff = fields[1];
	  return true;
	case 2: 
	  state = evenFieldDominant ? 1 : 0;
	  buff = fields[0];
	  return true;
	case 3:
	  state = evenFieldDominant ? 0 : 1;
	  buff = fields[1];
	  return true;
	case 4:
	  cerr << "ERROR: Attempt to read an invalid field. \n";
	  break;
	default: // Something's going really wrong.
	  RavlAssert(0);
	}
      return false;
    }
    //: Try and get next piece of data.
    
    virtual bool Seek(UIntT off) {
      if(!seekCtrl.Seek(off/2))
	return false;
      state = evenFieldDominant ? (off % 2) : ((off+1) % 2);
      //cerr << "Seek to " << off << " State=" << state << "\n";
      return true;
    }
    //: Seek to location in stream.
    // Returns false, if seek failed. 
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool DSeek(IntT off) {
      IntT at = (IntT) Tell();
      //cerr << "DSeek to " << off << " " << at  << " State=" << state << "\n";
      // There may be slight more efficent ways of doing this, but
      // it will work for now.
      at += off;
      return Seek(at);
    }
    //: Delta Seek, goto location relative to the current one.
    // if an error occurered (DSeek returned False) then stream
    // position will not be changed.
    
    virtual UIntT Tell() const {
      IntT fn = seekCtrl.Tell() * 2;
      switch(state) 
	{
	case 0: 
	case 2:
	  fn += evenFieldDominant ? 0 : 1;
	  break;
	case 1:
	case 3:
	  fn += evenFieldDominant ? 1 : 0;
	  break;
	case 4: // Error.
	  break;
	default: // Fatal error.
	  RavlAssert(0);
	}
      return fn;
    }
    //: Find current location in stream.
    // Defined as the index of the next object to be written or read.
    // May return ((UIntT) (-1)) if not implemented.
    
    virtual UIntT Size() const 
    { return seekCtrl.Size() * 2; }
    //: Find the total size of the stream. (assuming it starts from 0)
    // May return ((UIntT) (-1)) if not implemented.
    
    virtual UIntT Start() const
    { return seekCtrl.Start() * 2; }
    //: Find the offset where the stream begins, normally zero.
    // Defaults to 0

    virtual bool IsGetReady() const {
      if(!input.IsValid())
	return false;
      return input.IsGetReady(); 
    }
    //: Is some data ready ?
    // true = yes.
    
    virtual bool IsGetEOS() const {
      if(!input.IsValid())
	return true;
      return input.IsGetEOS(); 
    }
    //: Has the End Of Stream been reached ?
    // true = yes.
    
    virtual DPPortC ConnectedTo() const
    { return input; }
    //: What does this connect to ?
    
    virtual DListC<DPIPortBaseC> IPorts() const {
      DListC<DPIPortBaseC> lst;
      lst.InsLast(DPIPortBaseC((DPIPortBaseBodyC &)*this));
      return lst;
    }
    //: Input ports.
    
    virtual DListC<DPIPlugBaseC> IPlugs() const {
      DListC<DPIPlugBaseC> lst;
      lst.InsLast(DPIPlugC<ImageC<PixelT> >(input,"In1",DPEntityC((DPEntityBodyC &)*this)));
      return lst;
    }
    //: Input plugs.
    
  protected:
    void Deinterlace(const ImageC<PixelT> &img,ImageC<PixelT> &field0,ImageC<PixelT> &field1);
    //: DeinterlaceStream a frame.
    
    DPSeekCtrlAttachC seekCtrl;
    
    bool evenFieldDominant;
    ImageC<PixelT> fields[2];
    IntT state; // Field number.
    
    DPIPortC<ImageC<PixelT> > input; // Where to get data from.
  };
  
  
  //! userlevel=Normal
  //: Deinterlace an incoming stream of images.
  
  template<class PixelT>
  class DeinterlaceStreamC
    : public DPISPortC<ImageC<PixelT> >
  {
  public:
    DeinterlaceStreamC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    DeinterlaceStreamC(DPIPortC<ImageC<PixelT> > &inPort,bool nEvenFieldDominant = false)
      : DPEntityC(*new DeinterlaceStreamBodyC<PixelT>(inPort,nEvenFieldDominant))
    {}
    //: Constructor.
    
    DeinterlaceStreamC(DPISPortC<ImageC<PixelT> > &inPort,bool nEvenFieldDominant = false)
      : DPEntityC(*new DeinterlaceStreamBodyC<PixelT>(inPort,nEvenFieldDominant))
    {}
    //: Constructor.
    
  };
  
  //: DeinterlaceStream a frame.
  
  template<class PixelT>
  void DeinterlaceStreamBodyC<PixelT>::Deinterlace(const ImageC<PixelT> &img,ImageC<PixelT> &field0,ImageC<PixelT> &field1) {
    // Make sure images are allocated.
    field0 = ImageC<PixelT>(img.Frame());
    field1 = ImageC<PixelT>(img.Frame());
    
    for(Array2dSqr311Iter3C<PixelT,PixelT,PixelT> it(img,field0,field1);it;) {
      // Do even lines.
      do {
	it.Data3() = it.DataMM1();
	it.Data2() = Average(it.DataTM1(),it.DataBM1());
      } while(it.Next());
      if(!it)
	break;
      // Do odd lines.
      do {
	it.Data2() = it.DataMM1();
	it.Data3() = Average(it.DataTM1(),it.DataBM1());
      } while(it.Next());
      if(!it)
	break;
    }
  }
  
  
}

#endif
