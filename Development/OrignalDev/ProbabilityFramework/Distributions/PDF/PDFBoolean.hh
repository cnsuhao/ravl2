// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PDFBOOLEAN_HEADER
#define RAVLPROB_PDFBOOLEAN_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/PDFDiscrete.hh"
#include "Ravl/Prob/VariableBoolean.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Probability distribution class for a boolean variable
  class PDFBooleanBodyC
    : public PDFDiscreteBodyC {
  public:
    PDFBooleanBodyC(const VariableBooleanC& variable, RealT probabilityTrue);
    //: Constructor
    //!param: variable - the random variable for the distribution
    //!param: probabilityTrue - the probability that the variable is true
    // Note that probabilityFalse = 1-probabilityTrue

    virtual ~PDFBooleanBodyC();
    //: Destructor
    
  };

  //! userlevel=Normal
  //: Probability distribution class for a boolean variable
  //!cwiz:author
  
  class PDFBooleanC
    : public PDFDiscreteC
  {
  public:
    PDFBooleanC()
    {}
    //: Default constructor makes invalid handle
    
    PDFBooleanC(const VariableBooleanC& variable, RealT probabilityTrue)
      : PDFDiscreteC(new PDFBooleanBodyC(variable, probabilityTrue))
    {}
    //: Constructor
    //!param: variable - the random variable for the distribution
    //!param: probabilityTrue - the probability that the variable is true
    // Note that probabilityFalse = 1-probabilityTrue

  };

}

#endif
