// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
//! rcsid="$Id$"
//! lib=RavlPatternRec


#include "Ravl/PatternRec/Function1.hh"

namespace RavlN {
  
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

}
  
