// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPSPORT_HEADER
#define RAVL_DPSPORT_HEADER 1
/////////////////////////////////////////////////////
//! docentry="Ravl.Core.Data Processing.Seekable Ports" 
//! rcsid="$Id$"
//! file="Ravl/Core/IO/SPort.hh"
//! lib=RavlIO
//! author="Charles Galambos"
//! date="27/10/1998"
//! userlevel=Default

#include "Ravl/DP/Port.hh"

namespace RavlN {
  
  //////////////////////////////////////////////////
  //! userlevel=Develop
  //: Stream position control body class.
  // This class provides an abstract base class which allows
  // the streams position to be queried and manipulated.

  class DPSeekCtrlBodyC 
    : virtual public DPEntityBodyC 
  {
  public:
    DPSeekCtrlBodyC()
    {}
    //: Default constructor.
    
    virtual bool Seek(UIntT off);
    //: Seek to location in stream.
    // Returns false, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    virtual bool DSeek(IntT off);
    //: Delta Seek, goto location relative to the current one.
    // The default behavour of this functions is :
    // Do some error checking then:
    //   Seek((UIntT)((IntT) Tell() + off));
    // if an error occurered (DSeek returned False) then stream
    // position will not be changed.
    
    virtual UIntT Tell() const; 
    //: Find current location in stream.
    // Defined as the index of the next object to be written or read.
    // May return ((UIntT) (-1)) if not implemented.
    
    virtual UIntT Size() const; 
    //: Find the total size of the stream. (assuming it starts from 0)
    // May return ((UIntT) (-1)) if not implemented.
    
    virtual UIntT Start() const; 
    //: Find the offset where the stream begins, normally zero.
    // Defaults to 0
  };
  
  //////////////////////////////////////////////////
  //! userlevel=Develop
  //: Stub Stream position control body class.
  // This is like the main body class, but doesn't issue errors
  // when unimplemented functions are called.
  
  class DPSeekCtrlStubBodyC 
    : public DPSeekCtrlBodyC  
  {
  public:
    DPSeekCtrlStubBodyC();
    //: Default constructor.
   
    DPSeekCtrlStubBodyC(const DPPortC &pb);
    //: Constructor.
   
    virtual bool Seek(UIntT off);
    //: Seek to location in stream.
    // Returns false, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
   
    virtual bool DSeek(IntT off);
    //: Delta Seek, goto location relative to the current one.
    // The default behavour of this functions is :
    // Do some error checking then:
    //   Seek((UIntT)((IntT) Tell() + off));
    // if an error occurered (DSeek returned False) then stream
    // position will not be changed.
   
    virtual UIntT Tell() const; 
    //: Find current location in stream.
    // May return ((UIntT) (-1)) if not implemented.
   
    virtual UIntT Size() const; 
    //: Find the total size of the stream.  (assuming it starts from 0)
    // May return ((UIntT) (-1)) if not implemented.
   
  protected:
    DPPortC pb;
  };
  
  //////////////////////////////////////////////////
  //! userlevel=Normal
  //: Stream position control handle class.
  // This class provides an abstract base class which allows
  // the streams position to be queried and manipulated.
  
  class DPSeekCtrlC 
    : virtual public DPEntityC 
  {
  public:
    DPSeekCtrlC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    
    DPSeekCtrlC(bool stubIt,const DPPortC &pb = DPPortC());
    //: Constructor.
    // If stubIt is true, a body the produces no
    // error message is used, otherwise its a noisy one.
    
    DPSeekCtrlC(const DPSeekCtrlC &oth)
      : DPEntityC(oth)
    {}
    //: Copy constructor.
    
    DPSeekCtrlC(const DPEntityC &oth)
      : DPEntityC(oth)
    {
      if(dynamic_cast<DPSeekCtrlBodyC *>(&DPEntityC::Body()) == 0)
	Invalidate(); // Incorrect type.
    }
    //: Base Constructor.
  protected:
    DPSeekCtrlC(DPSeekCtrlBodyC &bod)
      : DPEntityC(bod)
    {}
    
    //: Body constructor.
    inline DPSeekCtrlBodyC &Body()
    { return dynamic_cast<DPSeekCtrlBodyC &>(DPEntityC::Body()); }
    //: Access body class.
    
    inline const DPSeekCtrlBodyC &Body() const
    { return dynamic_cast<const DPSeekCtrlBodyC &>(DPEntityC::Body()); }  
    //: Access body class.

  public:    
    inline bool Seek(UIntT off)
    { return Body().Seek(off); }
    //: Seek to location in stream.
    // Returns false, if seek failed. (Maybe because its
    // not implemented.)
    // if an error occurered (Seek returned False) then stream
    // position will not be changed.
    
    inline bool DSeek(IntT off)
    { return Body().DSeek(off); }
    //: Delta Seek, goto location relative to the current one.
    // The default behavour of this functions is :
    // Do some error checking then:
    //   Seek((UIntT)((IntT) Tell() + off));
    // if an error occurered (DSeek returned False) then stream
    // position will not be changed.
    
    inline UIntT Tell() const
    { return Body().Tell(); }
    //: Find current location in stream.
    // Defined as the index of the next object to be written or read.
    // May return ((UIntT) (-1)) if not implemented.
    
    inline UIntT Size() const
    { return Body().Size(); }
    //: Find the total size of the stream.  (assuming it starts from 0)
    // May return ((UIntT) (-1)) if not implemented.
    
    inline UIntT Start() const
    { return Body().Start(); }
    //: Find the offset where the stream begins, normally zero.
    // Defaults to 0
    
  };
  
  //////////////////////////////////////////////////
  //! userlevel=Develop
  //: Seekable port input body.
  
  template<class DataT>
  class DPISPortBodyC
    : public DPIPortBodyC<DataT>, 
      virtual public DPSeekCtrlBodyC
  {
  public:
    DPISPortBodyC()
    {}
    //: Default constructor.
  };
  
  //////////////////////////////////////////////////
  //! userlevel=Develop
  //: Seekable port ouput body.
  
  template<class DataT>
  class DPOSPortBodyC
    : public DPOPortBodyC<DataT>, 
      virtual public DPSeekCtrlBodyC
  {
  public:
    DPOSPortBodyC()
    {}
    //: Default constructor.
  };

  //////////////////////////////////////////////////
  //! userlevel=Normal
  //: Seekable port input handle.
  
  template<class DataT>
  class DPISPortC 
    : public DPIPortC<DataT>, 
      public DPSeekCtrlC
  {
  public:
    DPISPortC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    
    DPISPortC(const DPISPortC<DataT> &oth)
      : DPEntityC(oth)
    {}
    //: Copy constructor.
    
    DPISPortC(const DPIPortBaseC &oth)
      : DPEntityC(oth)
    {
      if(dynamic_cast<DPISPortBodyC<DataT> *>(&DPEntityC::Body()) == 0)
	Invalidate();
    }
    //: Base constructor.
    
    const DPISPortC<DataT> &operator= (const DPISPortC<DataT> &obj) {
      DPEntityC::operator=(obj);
      return *this;
    }
    //: Assigment.  
  };
  
  //////////////////////////////////////////////////
  //! userlevel=Normal
  //: Seekable port ouput handle.
  
  template<class DataT>
  class DPOSPortC 
    : public DPOPortC<DataT>, 
      public DPSeekCtrlC
  {
  public:
    DPOSPortC()
      : DPEntityC(true)
    {}
    //: Default constructor.
    
    DPOSPortC(const DPOSPortC<DataT> &oth)
      : DPEntityC(oth)
    {}
    //: Copy constructor.
    
    DPOSPortC(const DPOPortBaseC &oth)
      : DPEntityC(oth)
    {
      if(dynamic_cast<DPOSPortBodyC<DataT> *>(&DPEntityC::Body()) == 0)
	Invalidate();
    }
    //: Base constructor.
    
    const DPOSPortC<DataT> &operator= (const DPOSPortC<DataT> &obj) {
      DPEntityC::operator=(obj);
      return *this;
    }
    //: Assigment.
  };
}

#endif
