// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_RCHANDLEV_HEADER
#define RAVL_RCHANDLEV_HEADER 1
//! docentry="Ravl.Core.Reference Counting"
//! lib=RavlCore
//! userlevel=Normal
//! rcsid="$Id$"
//! author="Charles Galambos"
//! example=exRefCounter.cc

#include "Ravl/RefCounter.hh"

namespace RavlN {
  class RCAbstractC;
  
  //! userlevel=Normal
  //: Base class for all reference counted objects, where derivation is expected.
  // This holds a count of the number of handles that
  // are available for this object.
  
  class RCBodyVC 
    : public RCBodyC
  {
  public:
    virtual ~RCBodyVC();
    //: Destructor.
    
    virtual bool Save(ostream &out) const;
    //: Save to stream 'out'.
    
    virtual bool Save(BinOStreamC &out) const;
    //: Save to binary stream 'out'.
    
    virtual RCBodyVC &Copy() const;
    //: Make copy of body.
    // This should be provided in derived classes.
    // this funtion will issue an assertion failure if called.

    virtual RCBodyC &DeepCopy(UIntT levels = ((UIntT) -1)) const;
    //: Make a deep copy of body.
    // This should be provided in derived classes.
    // this funtion will issue an assertion failure if called.

  protected:
    RCBodyVC()
    {}
    //: Default constructor.
    // Creates a handle with 0 reference counts.
    
    RCBodyVC(istream &strm)
    {}
    //: Construct from a stream.
    
    RCBodyVC(BinIStreamC &strm)
    {}
    //: Construct from a binary stream.
    
    friend class RCAbstractC ;
  };
  
  istream &operator>>(istream &,RCBodyVC &obj);
  //: Input virtual body.
  // No-op.

  ostream &operator<<(ostream &,const RCBodyC &obj);
  //: Output virtual body.
  // No-op.

  //! userlevel=Normal
  //: Handle from objects derived from RCBodyVC.
  
  template<class BodyT>
  class RCHandleVC
    : public RCHandleC<BodyT>
  {
  public:
    RCHandleVC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    RCHandleVC(const RCAbstractC &oth)
      : RCHandleC<BodyT>(*dynamic_cast<BodyT *>(const_cast<RCBodyVC *> (&oth.Body())))
    {}
    //: Copy Constructor.
    // Creates a new reference to 'oth'
    
  protected:    
    RCHandleVC(BodyT &bod)
      : RCHandleC<BodyT>(bod)
    {}
    //: Body constructor.
    
    const BodyT &Body() const 
    { return RCHandleC<BodyT>::Body(); }
    //: Constant access to body of object.
    
    BodyT &Body()
    { return RCHandleC<BodyT>::Body(); }
    //: Constant access to body of object.
    
  public:

    bool Save(ostream &out) const
    { return Body().Save(out); }
    //: Save to stream 'out'.
    
    bool Save(BinOStreamC &out) const
    { return Body().Save(out); }
    //: Save to binary stream 'out'.
    
    RCAbstractC Abstract() 
    { return RCAbstractC(Body()); }
    //: Create an abstract handle.    
    
    
  };

  typedef RCHandleC<RCBodyVC> AbstractC;
  //: Abstract object handle.
  // Note: Objects which used abstract handles MUST be derived
  // from RCBodyVC.

  template<class BodyT>
  ostream &operator<<(ostream &strm,const RCHandleVC<BodyT> &obj) {
    obj.Save(strm);
    return strm;
  }
  //: Write a handle to a stream.
  
  template<class BodyT>
  BinOStreamC &operator<<(BinOStreamC &strm,const RCHandleVC<BodyT> &obj) {
    obj.Save(strm);
    return strm;
  }
  //: Write binary handle to a stream.
  
  template<class BodyT>
  istream &operator>>(istream &strm,RCHandleVC<BodyT> &obj) {
    //Load(strm,obj,"stream");
    return strm;
  }
  //: Read a handle from a stream.
  
  template<class BodyT>
  BinIStreamC &operator>>(BinIStreamC &strm,RCHandleVC<BodyT> &obj) {
    //Load(strm,obj,"abs");
    return strm;
  }
  //: Read a handle from a stream.

};

#endif
