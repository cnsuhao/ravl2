// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_FUNCPDFNORMAL_HEADER
#define RAVL_FUNCPDFNORMAL_HEADER 1
//! docentry="Ravl.Pattern Recognition.Numerical Modeling"
//! author="Charles Galambos"
//! rcsid="$Id$"
//! lib=RavlPatternRec

#include "Ravl/PatternRec/FuncPDF.hh"
#include "Ravl/Normal.hh"

namespace RavlN {
  
  //! userlevel=Develop
  //: Set of normal distributions.

  class FuncPDFNormalBodyC
    : public FuncPDFBodyC
  {
  public:
    FuncPDFNormalBodyC()
    {}
    //: Default constructor.
    
    FuncPDFNormalBodyC(const SArray1dC<NormalC> &ndists);
    //: Create from an array of distributions.
    
    virtual VectorC Apply(const VectorC &data) const;
    //: Apply function to 'data'
    
  protected:
    SArray1dC<NormalC> dists; // Array of distributions.
  };
  
  //! userlevel=Normal
  //: Set of normal distributions.
  
  class FuncPDFNormalC
    : public FuncPDFC
  {
  public:
    FuncPDFNormalC()
    {}
    //: Default constructor.
    // Creates an invalid handle.
    
    FuncPDFNormalC(const SArray1dC<NormalC> &ndists)
      : FuncPDFC(*new FuncPDFNormalBodyC(ndists))
    {}
    //: Create from an array of distributions.
    
  protected:
    FuncPDFNormalC(FuncPDFNormalBodyC &bod)
      : FuncPDFC(bod)
    {}
    //: Body constructor.
    
  };

  
}



#endif
