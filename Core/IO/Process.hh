// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDPPROCESS_HEADER
#define RAVLDPPROCESS_HEADER 1
///////////////////////////////////////////////
//! docentry="Ravl.Core.Data Processing" 
//! lib=RavlIO
//! rcsid="$Id$"
//! file="Ravl/Core/IO/Process.hh"
//! author="Charles Galambos"
//! date="16/06/98"
//! userlevel=Default

#include "Ravl/DP/Entity.hh"
#include "Ravl/Exception.hh"
#include "Ravl/SArr1Iter2.hh"
#include "Ravl/Assert.hh"

#if RAVL_HAVE_ANSICPPHEADERS
#include <typeinfo>
#else
#include <typeinfo.h>
#endif 

namespace RavlN {
  
  //! userlevel=Develop
  //: Process Base body.
  // A process performs a transformation on a data stream. This base
  // class provides a way of handling processes as abstract entities.
  
  class DPProcessBaseBodyC 
    : public DPEntityBodyC 
  {
  public:
    DPProcessBaseBodyC() {}
    //: Default constructor.
    
    DPProcessBaseBodyC(istream &in) 
      : DPEntityBodyC(in)
      {}
    //: Stream constructor.
  
    DPProcessBaseBodyC(const DPProcessBaseBodyC &oth) 
      : DPEntityBodyC(oth)
      {}
  //: Copy constructor.
    
    virtual bool Save(ostream &out) const 
      { return DPEntityBodyC::Save(out); }
    //: Save to ostream.
    
    virtual const type_info &InputType() const;
    //: Get input type.
    
    virtual const type_info &OutputType() const;
    //: Get input type.
    
    enum ProcTypeT { ConversionT,ConversionLossyT,LossyT };
    // ConversionT      - Lossless type conversion.
    // ConversionLossyT - Lossy conversion.
    // LossyT           - Lossy operation.
    
    virtual ProcTypeT OpType() const { return LossyT; }
    //: Operation type lossy/lossless.
    
    virtual bool IsStateless() const 
      { return false; }
    //: Is operation stateless ?
  };
  
  
  //! userlevel=Develop
  //: Process body.
  // This class provides a way of handling processes having a particular
  // input and output type as abstract entity.
  
  template<class InT,class OutT>
  class DPProcessBodyC 
    : public DPProcessBaseBodyC 
  {
  public:
    inline DPProcessBodyC()
      {}
    //: Default constructor.
    
    inline DPProcessBodyC(istream &in)
      : DPProcessBaseBodyC(in)
      {}
    //: Stream constructor.
    
    ~DPProcessBodyC()
      {}
    //: Destructor. 
    // To see if this helps gcc-1.0.3 sort itself out.
    
    virtual OutT Apply(const InT &);
    //: Apply operation.
    
    virtual IntT ApplyArray(const SArray1dC<InT> &in,SArray1dC<OutT>  &out);
    //: Apply operation to an array of elements.
    // returns the number of elements processed.
    
    virtual bool Save(ostream &out) const;
    //: Save to ostream.
    
    virtual const type_info &InputType() const;
    //: Get input type.
    
    virtual const type_info &OutputType() const; 
    //: Get input type.
    
  };
  
  
  ////////////////////////////////////////////////////////
  
  template<class InT,class OutT>
  OutT 
  DPProcessBodyC<InT,OutT>::Apply(const InT &) { 
    RavlAssert(0); // This should never be called.
    return OutT(); 
  }
  
  template<class InT,class OutT>
  IntT DPProcessBodyC<InT,OutT>::ApplyArray(const SArray1dC<InT> &in,SArray1dC<OutT>  &out) {
    RavlAssert(in.Size() <= out.Size());
    for(SArray1dIter2C<InT,OutT> it(in,out);it;it++)
      it.Data2() = Apply(it.Data1());
    return in.Size();
  }
  
  template<class InT,class OutT>
  bool 
  DPProcessBodyC<InT,OutT>::Save(ostream &out) const  { 
    return DPProcessBaseBodyC::Save(out); 
  }
  
  template<class InT,class OutT>
  const type_info &
  DPProcessBodyC<InT,OutT>::InputType() const  { 
    return typeid(InT); 
  }
  
  template<class InT,class OutT>
  const type_info &
  DPProcessBodyC<InT,OutT>::OutputType() const  { 
    return typeid(OutT); 
  }

  //////////////////////////////
  //! userlevel=Advanced
  //: Process handle base.
  // A process performs a transformation on a data stream. This base
  // class provides a way of handling processes as abstract entities.
  
  class DPProcessBaseC 
    : public DPEntityC 
  {
  public:
    DPProcessBaseC() 
      : DPEntityC(true)
      {}
    //: Default constructor.
    
    DPProcessBaseC(const DPProcessBaseC &oth) 
      : DPEntityC(oth)
      {}
    //: Copy constructor.
    
    DPProcessBaseC(const RCAbstractC &abst);
    //: Constructor from an abstract handle.
    
    DPProcessBaseC(istream &in);
    //: Stream constructor.
    
    ~DPProcessBaseC() {}
    //: Destructor.
    
  protected:
    DPProcessBaseC(DPProcessBaseBodyC &oth) 
      : DPEntityC(oth)
      {}
    //: Body constructor.
    
    inline DPProcessBaseBodyC &Body() 
      { return static_cast<DPProcessBaseBodyC & > (DPEntityC::Body()); }
    //: Access body.
    
    inline const DPProcessBaseBodyC &Body() const
      { return static_cast<const DPProcessBaseBodyC & > (DPEntityC::Body()); }
    //: Access body.
    
  public:
    inline const type_info &InputType() const 
      { return Body().InputType(); }
    //: Get input type.
    
    inline const type_info &OutputType() const 
      { return Body().OutputType(); }
    //: Get input type.  
    
    inline bool IsStateless() const 
      { return Body().IsStateless(); }
    //: Is operation stateless ?
    
    inline DPProcessBaseBodyC::ProcTypeT OpType() const 
      { return Body().OpType(); }
    //: Operation type lossy/lossless.
    
    inline const DPProcessBaseC &operator= (const DPProcessBaseC &oth) 
      { DPEntityC::operator= (oth); return *this; }
    //: Assignment operator.
    
  };
  
  /////////////////////////////////
  //! userlevel=Normal
  //: Templated process handle.
  // This class provides a way of handling processes having a particular
  // input and output type as abstract entity.
  
  template<class InT,class OutT>
  class DPProcessC 
    : public DPProcessBaseC 
  {
  public:  
    DPProcessC() {}
    //: Default constructor.
    
    DPProcessC(const DPProcessC<InT,OutT> &oth)
      : DPProcessBaseC(oth)
      {}
    //: Copy constructor.

  protected:  
    DPProcessC(DPProcessBodyC<InT,OutT> &bod)
      : DPProcessBaseC(bod)
      {}
    //: Body constructor.
    
    inline DPProcessBodyC<InT,OutT> &Body() 
      { return dynamic_cast<DPProcessBodyC<InT,OutT> & > (DPEntityC::Body()); }
    //: Access body.
    
    inline const DPProcessBodyC<InT,OutT> &Body() const
      { return dynamic_cast<const DPProcessBodyC<InT,OutT> & > (DPEntityC::Body()); }
    //: Access body.
    
  public:  
    DPProcessC(const RCAbstractC &abst) 
      : DPProcessBaseC(abst) 
      { CheckHandleType(Body()); }
    //: Constructor from an abstract handle.
    
    DPProcessC(const DPProcessBaseC &base) 
      : DPProcessBaseC(base) 
      { CheckHandleType(Body()); }
    //: Base constructor.
    
    DPProcessC(istream &in)
      : DPProcessBaseC(in) 
      { CheckHandleType(Body()); }
    //: Stream constructor.
    
    inline OutT Apply(const InT &dat) { return Body().Apply(dat); }
    //: Apply operation.
    // NB. This may become constant in the future, but the situation isn't
    // clear at the moment.
  
    inline IntT ApplyArray(const SArray1dC<InT> &in,SArray1dC<OutT>  &out)
      { return Body().ApplyArray(in,out); }
    //: Apply operation to an array of elements.
    // returns the number of elements processed.
    
    //inline OutT operator>>(const InT &dat) { return Body().Apply(dat); }
    //: Streaming version.
    
    inline const DPProcessC<InT,OutT> operator= (const DPProcessC<InT,OutT> &in) 
      { DPProcessBaseC::operator= (in); return *this; }
    //: Assignment operator
    
    inline const DPProcessC<InT,OutT> Copy() const 
      { return DPProcessC<InT,OutT>(static_cast<DPProcessBodyC<InT,OutT> &>(Body().Copy())); }
    //: Make a copy of this process.
    
    //: Some type defs.
    typedef InT ProcInputT;
    typedef OutT ProcOutputT;
  };
  
}
#endif
