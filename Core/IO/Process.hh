// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DPPROCESS_HEADER
#define RAVL_DPPROCESS_HEADER 1
///////////////////////////////////////////////
//! docentry="Ravl.Core.Data Processing.Processes" 
//! lib=RavlIO
//! rcsid="$Id$"
//! file="Ravl/Core/IO/Process.hh"
//! author="Charles Galambos"
//! date="16/06/1998"
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
    DPProcessBaseBodyC() 
    {}
    //: Default constructor.
    
    DPProcessBaseBodyC(istream &in) 
      : DPEntityBodyC(in)
    {}
    //: Stream constructor.
    
    DPProcessBaseBodyC(BinIStreamC &in) 
      : DPEntityBodyC(in)
    {}
    //: Stream constructor.
    
    DPProcessBaseBodyC(const DPProcessBaseBodyC &oth) 
      : DPEntityBodyC(oth)
    {}
    //: Copy constructor.
    
    virtual bool Save(ostream &out) const;
    //: Save to ostream.
    
    virtual bool Save(BinOStreamC &out) const;
    //: Save to binary stream.  
    
    virtual UIntT NoInputs() const;
    //: Get number of inputs..
    // Defaults to 1.
    
    virtual UIntT NoOutputs() const;
    //: Get number of outputs.
    // Defaults to 1.
    
    virtual const type_info &InputType(int n = 0) const;
    //: Get input types.
    
    virtual const type_info &OutputType(int n = 0) const;
    //: Get output types.
    
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
    
    virtual OutT Apply(const InT &) { 
      RavlAssertMsg(0,"DPProcessBodyC::Apply(), Abstract method called. ");
      return OutT(); 
    }
    
    //: Apply operation.
    
    virtual IntT ApplyArray(const SArray1dC<InT> &in,SArray1dC<OutT>  &out);
    //: Apply operation to an array of elements.
    // returns the number of elements processed.
    
    virtual bool Save(ostream &out) const
    { return DPProcessBaseBodyC::Save(out); }
    //: Save to ostream.
    
    virtual const type_info &InputType(int n = 0) const { 
      if(n != 0) return typeid(void);
      return typeid(InT); 
    }
    //: Get input type.
    
    virtual const type_info &OutputType(int n = 0) const { 
      if(n != 0) return typeid(void);
      return typeid(OutT); 
    }
    //: Get output type.
    
  };
  
  ////////////////////////////////////////////////////////
  
  template<class InT,class OutT>
  IntT DPProcessBodyC<InT,OutT>::ApplyArray(const SArray1dC<InT> &in,SArray1dC<OutT>  &out) {
    RavlAssert(in.Size() <= out.Size());
    for(SArray1dIter2C<InT,OutT> it(in,out);it;it++)
      it.Data2() = Apply(it.Data1());
    return in.Size();
  }
  
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
    
    DPProcessBaseC(BinIStreamC &in);
    //: Binary stream constructor.
    
    ~DPProcessBaseC() 
    {}
    //: Destructor.
    
  protected:
    DPProcessBaseC(DPProcessBaseBodyC &oth) 
      : DPEntityC(oth)
    {}
    //: Body constructor.
    
    DPProcessBaseC(DPProcessBaseBodyC *oth) 
      : DPEntityC(oth)
    {}
    //: Body ptr constructor.
    
    inline DPProcessBaseBodyC &Body() 
    { return static_cast<DPProcessBaseBodyC & > (DPEntityC::Body()); }
    //: Access body.
    
    inline const DPProcessBaseBodyC &Body() const
    { return static_cast<const DPProcessBaseBodyC & > (DPEntityC::Body()); }
    //: Access body.
    
  public:
    inline UIntT NoInputs() const
    { return Body().NoInputs(); }
    //: Get number of inputs.
    
    inline UIntT NoOutputs() const
    { return Body().NoOutputs(); }
    //: Get number of outputs.
    
    inline const type_info &InputType(int n = 0) const 
    { return Body().InputType(n); }
    //: Get input type.
    // n is the input number to query, numbering starts from 0.
    
    inline const type_info &OutputType(int n = 0) const 
    { return Body().OutputType(n); }
    //: Get input type.  
    // n is the output number to query, numbering starts from 0.
    
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
