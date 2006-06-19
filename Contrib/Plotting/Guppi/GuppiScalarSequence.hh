// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPLOT_GUPPISCALARSEQEUNCE_HEADER
#define RAVLPLOT_GUPPISCALARSEQEUNCE_HEADER 1
//! docentry="Ravl.GUI.Data_Plotting.Guppi"
//! author="Charles Galambos"
//! rcsid="$Id: GuppiScalarSequence.hh 3401 2003-09-06 08:11:47Z craftit $"
//! lib=RavlGuppi
//! file="Ravl/Contrib/Plotting/Guppi/GuppiScalarSequence.hh"

#include "Ravl/RefCounter.hh"
#include "Ravl/Plot/GuppiTypes.hh"
#include "Ravl/Array1d.hh"
#include "Ravl/SArray1d.hh"
#include "Ravl/Point2d.hh"

namespace RavlPlotN {
  using namespace RavlN;

  enum GuppiScalarSequenceTypeT { GSSLinear,GSSLog };
  
  //! userlevel=Develop
  //: Scalar sequence body
  
  class GuppiScalarSequenceBodyC 
    : public RCBodyC
  {
  public:
    GuppiScalarSequenceBodyC();
    //: Constructor.
    
    GuppiScalarSequenceBodyC(GuppiScalarSequenceTypeT seqType,RealT start,RealT inc,UIntT size);
    //: Constructor.
    
    GuppiScalarSequenceBodyC(const Array1dC<RealT> &data);
    //: Construct from an array of values.
    
    ~GuppiScalarSequenceBodyC();
    //: Destructor.
    
    bool Generate(GuppiScalarSequenceTypeT seqType,RealT start,RealT inc,UIntT size);
    //: Generate a sequence
    // Note: This is NOT thread safe.
    
    bool Set(const Array1dC<RealT> &data);
    //: Set sequence to contents of 'data'.
    // Note: This is NOT thread safe.
    
    bool Set(const Array1dC<Point2dC> &data,int index);
    //: Set sequence to either the first or second element of an array of points2d's.
    // Note: This is NOT thread safe.
    
    bool Append(RealT value);
    //: Append a value to the sequence.
    // Note: This is NOT thread safe.
    
    GuppiSeqScalar *Sequence()
    { return seq; }
    //: Access sequence.
    
  protected:
    GuppiSeqScalar *seq;
  };

  //! userlevel=Normal
  //: Scalar sequence 
  
  class GuppiScalarSequenceC 
    : public RCHandleC<GuppiScalarSequenceBodyC>
  {
  public:
    GuppiScalarSequenceC()
    {}
    //: Default constructor

    GuppiScalarSequenceC(bool)
      : RCHandleC<GuppiScalarSequenceBodyC>(*new GuppiScalarSequenceBodyC())
    {}
    //: Constructor
    
    GuppiScalarSequenceC(GuppiScalarSequenceTypeT seqType,RealT start,RealT inc,UIntT size)
      : RCHandleC<GuppiScalarSequenceBodyC>(*new GuppiScalarSequenceBodyC(seqType,start,inc,size))
    {}
    //: Constructor.
    
    GuppiScalarSequenceC(const Array1dC<RealT> &data)
      : RCHandleC<GuppiScalarSequenceBodyC>(*new GuppiScalarSequenceBodyC(data))
    {}
    //: Construct from an array of values.
    
  protected:
    GuppiScalarSequenceBodyC& Body()
    { return RCHandleC<GuppiScalarSequenceBodyC>::Body(); }
    //: Access body.
    
    const GuppiScalarSequenceBodyC& Body() const
    { return RCHandleC<GuppiScalarSequenceBodyC>::Body(); }
    //: Access body.
    
  public:
    GuppiSeqScalar *Sequence()
    { return Body().Sequence(); }
    //: Access sequence.
    // Note: This is NOT thread safe.
    
    bool Append(RealT value)
    { return Body().Append(value); }
    //: Append a value to the sequence.
    // Note: This is NOT thread safe.
    
    bool Set(const Array1dC<RealT> &data)
    { return Body().Set(data); }
    //: Set sequence to contents of 'data'.
    // Note: This is NOT thread safe.
    
    bool Set(const Array1dC<Point2dC> &data,int index)
    { return Body().Set(data,index); }
    //: Set sequence to either the first or second element of an array of points2d's.
    // Note: This is NOT thread safe.
    
  };
  
}


#endif
