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
//! file="Ravl/Image/Processing/Filters/DeinterlaceStream.hh"

#include "Ravl/DP/StreamOp.hh"
#include "Ravl/DP/SPort.hh"
#include "Ravl/DP/SPortAttach.hh"
#include "Ravl/Average.hh"
#include "Ravl/Image/Image.hh"
#include "Ravl/Array2dSqr311Iter3.hh"

namespace RavlImageN {

  //! userlevel=Develop
  //: Deinterlace base class.
  
  class DeinterlaceStreamBaseC {
  public:
    DeinterlaceStreamBaseC(const DPSeekCtrlC &newSeekCtrl,bool evenFieldDom = false);
    //: Constructor.
    
    virtual ~DeinterlaceStreamBaseC();
    //: Destructor.
    
    bool HandleGetAttr(const StringC &attrName,bool &attrValue);
    //: Get bool attribute.
    
    bool HandleSetAttr(const StringC &attrName,const bool &attrValue);
    //: Set bool attribute.
    
    bool HandleGetAttr(const StringC &attrName,RealT &attrValue);
    //: Get a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
    bool HandleSetAttr(const StringC &attrName,const RealT &attrValue);
    //: Set a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
  protected:
    void RegisterAttribs(AttributeCtrlC &attrCtrl);
    //: Register attributes.
    
    DPSeekCtrlC seekCtrl;
    bool evenFieldDominant;
    IntT state; // Field number.
    DPIPortBaseC inputBase; 
  };
  
  //! userlevel=Develop
  //: Deinterlace an incoming stream of images.
  
  template<class PixelT>
  class DeinterlaceStreamBodyC
    : public DPISPortBodyC<ImageC<PixelT> >,
      public DeinterlaceStreamBaseC
  {
  public:
    DeinterlaceStreamBodyC(DPIPortC<ImageC<PixelT> > &inPort,bool nEvenFieldDominant = true)
      : DPISPortBodyC<ImageC<PixelT> >(inPort),
	DeinterlaceStreamBaseC(DPSeekCtrlAttachC(inPort,true),nEvenFieldDominant),
	input(inPort)
    { 
      inputBase = input;
      RegisterAttribs(inPort); 
    }
    //: Constructor.
    
    DeinterlaceStreamBodyC(DPISPortC<ImageC<PixelT> > &inPort,bool nEvenFieldDominant = true)
      : DeinterlaceStreamBaseC(DPSeekCtrlAttachC((const DPSeekCtrlC &) inPort),nEvenFieldDominant),
	input(inPort)
    { 
      inputBase = input;
      RegisterAttribs(inPort); 
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
      //cerr << "State=" << state << " Tell=" << Tell() << "\n";
      switch(state) 
	{
	case 0:
	  state = 10; // Mark as error if we get interrupted by an exception.
	  if(!input.Get(img))
	    return false;
	  Deinterlace(img,fields[0],fields[1]);
	  state = 1;
	  buff = fields[evenFieldDominant ? 1 : 0];
	  return true;
	case 1:
	  buff = fields[evenFieldDominant ? 0 : 1];
	  state = 0;
	  return true;
	case 2: // Load frame for second field.
	  state = 10; // Mark as error if we get interrupted by an exception.
	  if(!input.Get(img))
	    return false;
	  Deinterlace(img,fields[0],fields[1]);
	  buff = fields[evenFieldDominant ? 0 : 1];
	  state = 0;
	  return true;
	default: // Something's going really wrong.
	  RavlAssert(0);
	}
      return false;
    }
    //: Try and get next piece of data.
    
    virtual bool Seek(UIntT off) {
      if(!seekCtrl.Seek(off/2))
	return false;
      state = (off % 2);
      if(state == 1)
	state = 2; // Make sure we load the appropriate frame.
      //cerr << "Seek to " << off << " Frame=" << (off/2) << " State=" << state << "\n";
      return true;
    }
    //: Seek to location in stream.
    // Returns false, if seek failed. 
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool DSeek(IntT off) {
      IntT at = (IntT) Tell();
      //cerr << "DSeek by " << off << " " << at  << " State=" << state << "\n";
      // There may be slight more efficent ways of doing this, but
      // it will work for now.
      if(off < 0 && (-off) > at)
	return false;
      at += off;
      return Seek(at);
    }
    //: Delta Seek, goto location relative to the current one.
    // if an error occurered (DSeek returned False) then stream
    // position will not be changed.
    
    virtual UIntT Tell() const {
      IntT fn = seekCtrl.Tell() * 2;
      switch(state) {
      case 2: fn += 1; break;
      case 1: fn -= 1; break;
      case 0:
      case 10: // Error.
	break;
      default: // Fatal error.
	RavlAssert(0);
      }
      return fn;
    }
    //: Find current location in stream.
    // Defined as the index of the next object to be written or read.
    // May return ((UIntT) (-1)) if not implemented.
    
    virtual UIntT Size() const { 
      UIntT size = seekCtrl.Size();
      if(size == ((UIntT) -1))
	return size;
      return size * 2; 
    }
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
    
    virtual bool GetAttr(const StringC &attrName,bool &attrValue) {
      if(HandleGetAttr(attrName,attrValue))
	return true;
      return AttributeCtrlBodyC::GetAttr(attrName,attrValue);
    }
    //: Get bool attribute.
    
    virtual bool SetAttr(const StringC &attrName,const bool &attrValue) {
      if(HandleSetAttr(attrName,attrValue))
	return true;
      return AttributeCtrlBodyC::SetAttr(attrName,attrValue);
    }
    //: Set bool attribute.
    
    virtual bool GetAttr(const StringC &attrName,RealT &attrValue) {
      if(HandleSetAttr(attrName,attrValue))
	return true;
      return AttributeCtrlBodyC::GetAttr(attrName,attrValue);
    }
    //: Get a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.
    
    virtual bool SetAttr(const StringC &attrName,const RealT &attrValue) {
      if(HandleSetAttr(attrName,attrValue))
	return true;
      return AttributeCtrlBodyC::SetAttr(attrName,attrValue);
    }
    //: Set a stream attribute.
    // Returns false if the attribute name is unknown.
    // This is for handling stream attributes such as frame rate, and compression ratios.

  protected:
    void Deinterlace(const ImageC<PixelT> &img,ImageC<PixelT> &field0,ImageC<PixelT> &field1);
    //: DeinterlaceStream a frame.
    
    ImageC<PixelT> fields[2];
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
