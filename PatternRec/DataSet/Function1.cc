// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec
//! file="Ravl/PatternRec/DataSet/Function1.cc"


#include "Ravl/PatternRec/Function1.hh"
#include "Ravl/VirtualConstructor.hh"

namespace RavlN {
  
  //: Load from stream.

  Function1BodyC::Function1BodyC(istream &strm) 
    : FunctionBodyC(strm)
  {}
  
  //: Load from binary stream.
  
  Function1BodyC::Function1BodyC(BinIStreamC &strm) 
    : FunctionBodyC(strm)
  {}
  
  //: Writes object to stream, can be loaded using constructor
  
  bool Function1BodyC::Save (ostream &out) const {
    if(!FunctionBodyC::Save(out))
      return false;
    //...
    return true;
  }
  
  //: Writes object to stream, can be loaded using constructor
  
  bool Function1BodyC::Save (BinOStreamC &out) const {
    if(!FunctionBodyC::Save(out))
      return false;
    //...
    return true;
  }
  
  //: Apply function to 'data'
  
  VectorC Function1BodyC::Apply(const VectorC &data) const {
    VectorC ret(1);
    ret[0] = Apply1(data);
    return ret;
  }
  
  //: Apply function to 'data'
  
  RealT Function1BodyC::Apply1(const VectorC &data) const {
    RavlAssertMsg(0,"Function1BodyC::Apply1(), Abstract method called. \n");
    return 0;
  }

  ///////////////////////////////////////////////////////////

  //: Load from stream.
  
  Function1C::Function1C(istream &strm)
    : FunctionC(RAVL_VIRTUALCONSTRUCTOR(strm,Function1BodyC))    
  {}
  
  //: Load from binary stream.
  
  Function1C::Function1C(BinIStreamC &strm)
    : FunctionC(RAVL_VIRTUALCONSTRUCTOR(strm,Function1BodyC))
  {}

  //: Setup virtual constructor.
  // As this is an abstract class its not really needed, but its usefull to
  // have an example of how it should work here.
  
  //RAVL_INITVIRTUALCONSTRUCTOR(Function1BodyC);
  
}

  
