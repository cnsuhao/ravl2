// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PDFCONTINUOUSDESIGNERUNIFORM_HEADER
#define RAVLPROB_PDFCONTINUOUSDESIGNERUNIFORM_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/Prob/PDFContinuousDesigner.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Designer for uniform pdf
  class PDFContinuousDesignerUniformBodyC
    : public PDFContinuousDesignerBodyC {
  public:
    PDFContinuousDesignerUniformBodyC();
    //: Constructor

    virtual ~PDFContinuousDesignerUniformBodyC();
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
  
  class PDFContinuousDesignerUniformC
    : public PDFContinuousDesignerC
  {
  public:
    PDFContinuousDesignerUniformC()
    {}
    //: Default constructor makes invalid handle

    static PDFContinuousDesignerUniformC GetInstance();
    //: Get an instance of the designer

  private:
    PDFContinuousDesignerUniformC(bool)
      : PDFContinuousDesignerC(new PDFContinuousDesignerUniformBodyC())
    {}
    //: Private constructor
    
  private:
    static PDFContinuousDesignerUniformC m_instance;
    //: The instance of the designer 
  };

}

#endif
