// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PDFCONTINUOUSDESIGNERNORMAL_HEADER
#define RAVLPROB_PDFCONTINUOUSDESIGNERNORMAL_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/PDFContinuousDesigner.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Designer for normal gaussian pdf
  class PDFContinuousDesignerNormalBodyC
    : public PDFContinuousDesignerBodyC {
  public:
    PDFContinuousDesignerNormalBodyC();
    //: Constructor

    virtual ~PDFContinuousDesignerNormalBodyC();
    //: Destructor
    
    virtual PDFContinuousAbstractC CreatePDF(const VariableContinuousC& variable, const DListC<RealT>& realSamples) const;
    //: Create a probability distribution according to the real samples
    //!param: variable - the random variable
    //!param: realSamples - a sample of real values
    //!return: the continuous probability distribution

  };

  //! userlevel=Normal
  //: Designer for normal gaussian pdf
  //!cwiz:author
  
  class PDFContinuousDesignerNormalC
    : public PDFContinuousDesignerC
  {
  public:
    PDFContinuousDesignerNormalC()
    {}
    //: Default constructor makes invalid handle

    static PDFContinuousDesignerNormalC GetInstance();
    //: Get an instance of the designer

  private:
    PDFContinuousDesignerNormalC(bool)
      : PDFContinuousDesignerC(new PDFContinuousDesignerNormalBodyC())
    {}
    //: Private constructor
    
  private:
    static PDFContinuousDesignerNormalC m_instance;
    //: The instance of the designer 
  };

}

#endif
