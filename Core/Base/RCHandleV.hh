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
//! example=exRefCounterInherit.cc
//! file="Ravl/Core/Base/RCHandleV.hh"

#include "Ravl/RefCounter.hh"
#include "Ravl/Exception.hh"

namespace RavlN {
  class RCAbstractC;
 
  template<class BodyT> class RCHandleVC;  
  template<class BodyT> istream &operator>>(istream &strm,RCHandleVC<BodyT> &obj);  
  template<class BodyT> BinIStreamC &operator>>(BinIStreamC &strm,RCHandleVC<BodyT> &obj);
  
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
      : RCHandleC<BodyT>(oth.IsValid() ? dynamic_cast<BodyT *>(const_cast<RCBodyVC *> (&oth.Body())) : (BodyT *) 0)
    {}
    //: Copy Constructor.
    // Creates a new reference to 'oth'
    
  protected:    
    RCHandleVC(BodyT &bod)
      : RCHandleC<BodyT>(bod)
    {}
    //: Body constructor.
    
    RCHandleVC(BodyT *bod)
      : RCHandleC<BodyT>(bod)
    {}
    //: Construct from a body pointer.
    // The pointer may be 0.
    
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
#if !RAVL_COMPILER_VISUALCPP  
    RCAbstractC Abstract() 
    { return RCAbstractC(Body()); }
    //: Create an abstract handle.    
#endif    
    RCHandleVC<BodyT> Copy() const
    { return RCHandleVC<BodyT>(Body().Copy()); }
    //: Make copy of body.
    
    RCHandleVC<BodyT> DeepCopy(UIntT levels = ((UIntT) -1)) const
    { return RCHandleVC<BodyT>(Body().DeepCopy(levels)); }
    //: Make a deep copy of body.
    
#if RAVL_NEW_ANSI_CXX_DRAFT
    friend istream &operator>> <BodyT>(istream &strm,RCHandleVC<BodyT> &obj);
    friend BinIStreamC &operator>> <BodyT>(BinIStreamC &strm,RCHandleVC<BodyT> &obj);
#else
    friend istream &operator>> (istream &strm,RCHandleVC<BodyT> &obj);
    friend BinIStreamC &operator>> (BinIStreamC &strm,RCHandleVC<BodyT> &obj);
#endif
  };
  
  typedef RCHandleC<RCBodyVC> AbstractC;
  //: Abstract object handle.
  // Note: Objects which used abstract handles MUST be derived
  // from RCBodyVC.
  
  RCBodyVC *VCLoad(istream &s);
  //: Load object from a stream via a virtual constructor
  
  RCBodyVC *VCLoad(BinIStreamC &s);
  //: Load object from a binary stream via a virtual constructor

  template<class BodyT>
  BodyT *VCLoad(istream &s,BodyT *) { 
    RCBodyVC *bp = VCLoad(s);
    BodyT *ret = dynamic_cast<BodyT *>(bp);
    if(ret == 0) {
      delete bp;
      throw ExceptionErrorCastC("Virtual constructor failed.",typeid(RCBodyVC),typeid(BodyT));
    }
    return ret; 
  }
  
  template<class BodyT>
  BodyT *VCLoad(BinIStreamC &s,BodyT *) { 
    RCBodyVC *bp = VCLoad(s);
    BodyT *ret = dynamic_cast<BodyT *>(bp);
    if(ret == 0) {
      delete bp; 
      throw ExceptionErrorCastC("Virtual construction failed.",typeid(RCBodyVC),typeid(BodyT));
    }
    return ret; 
  }
  
#define RAVL_VIRTUALCONSTRUCTOR(strm,targType) VCLoad(strm,(targType *) 0)
  
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
    obj = RCHandleVC<BodyT>(dynamic_cast<BodyT *>(VCLoad(strm)));
    return strm;
  }
  //: Read a handle from a stream.
  
  template<class BodyT>
  BinIStreamC &operator>>(BinIStreamC &strm,RCHandleVC<BodyT> &obj) {
    obj = RCHandleVC<BodyT>(dynamic_cast<BodyT *>(VCLoad(strm)));
    return strm;
  }
  //: Read a handle from a binary stream.
  
};

#endif
