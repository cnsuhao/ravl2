// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLSAMPLELABEL_HEADER
#define RAVLSAMPLELABEL_HEADER 1
//! rcsid="$Id$"
//! author="Kieron Messer"
//! docentry="Ravl.Pattern Recognition.Data Set"

#include"Ravl/PatternRec/Sample.hh"
#include"Ravl/Vector.hh"


namespace RavlN {
  
  //! userlevel=Normal
  //: Sample of labels.
  
  class SampleLabelC 
    : public SampleC<UIntT>
  {
  public:
    SampleLabelC(SizeT maxSize=10)
      : SampleC<UIntT>(maxSize)
      {}
    //: Create a sample of data with a maximum size
    
    SampleLabelC(const SArray1dC<UIntT> & dat)
      : SampleC<UIntT>(dat)
      {}
    //: Create a sample of data from an array
    
    
    
  }; // end of class SampleVectorC 
  
}

#endif
