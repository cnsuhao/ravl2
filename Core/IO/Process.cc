// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
///////////////////////////////////////////////
//! docentry="Algorithms.Data Processing"
//! lib=RavlIO
//! rcsid="$Id$"
//! file="Ravl/Core/IO/Process.cc"

#include "Ravl/DP/Process.hh"

namespace RavlN {

  //: Save to ostream.
  
  bool DPProcessBaseBodyC::Save(ostream &out) const 
  { return DPEntityBodyC::Save(out); }
  
  //: Save to binary stream.  
  
  bool DPProcessBaseBodyC::Save(BinOStreamC &out) const
  { return DPEntityBodyC::Save(out); }

  //: Get input type.
  
  const type_info &DPProcessBaseBodyC::InputType() const  { 
    return typeid(void); 
  }
  
  //: Get Output type.
  
  const type_info &DPProcessBaseBodyC::OutputType() const  { 
    return typeid(void); 
  }
  
  //////////////////////////////////////////////////////////
  
  //: Constructor from an abstract handle.
  
  DPProcessBaseC::DPProcessBaseC(const RCAbstractC &abst) 
    : DPEntityC(abst) 
  { CheckHandleType(Body()); }
  
  //: Stream constructor.
  
  DPProcessBaseC::DPProcessBaseC(istream &strm) 
    : DPEntityC(RAVL_VIRTUALCONSTRUCTOR(strm,DPProcessBaseBodyC))
  {}
  
  
  DPProcessBaseC::DPProcessBaseC(BinIStreamC &strm)
    : DPEntityC(RAVL_VIRTUALCONSTRUCTOR(strm,DPProcessBaseBodyC))
  {}

}

