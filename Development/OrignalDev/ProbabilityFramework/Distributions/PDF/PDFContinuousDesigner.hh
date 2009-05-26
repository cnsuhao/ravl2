// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PDFCONTINUOUSDESIGNER_HEADER
#define RAVLPROB_PDFCONTINUOUSDESIGNER_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Prob/PDFContinuousAbstract.hh"
#include "Ravl/DList.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Base class for continuous probability distribution designers
  class PDFContinuousDesignerBodyC
    : public RCBodyVC {
  public:
    PDFContinuousDesignerBodyC();
    //: Constructor

    virtual ~PDFContinuousDesignerBodyC();
    //: Destructor
    
    virtual PDFContinuousAbstractC CreatePDF(const VariableContinuousC& variable, const DListC<RealT>& realSamples) const=0;
    //: Create a probability distribution according to the real samples
    //!param: variable - the random variable
    //!param: realSamples - a sample of real values
    //!return: the continuous probability distribution

  };

  //! userlevel=Normal
  //: Base class for continuous probability distribution designers
  //!cwiz:author
  
  class PDFContinuousDesignerC
    : public RCHandleC<PDFContinuousDesignerBodyC>
  {
  public:
    PDFContinuousDesignerC()
    {}
    //: Default constructor makes invalid handle

    PDFContinuousAbstractC CreatePDF(const VariableContinuousC& variable, const DListC<RealT>& realSamples) const
    { return Body().CreatePDF(variable, realSamples); }
    //: Create a probability distribution according to the real samples
    //!param: variable - the random variable
    //!param: realSamples - a sample of real values
    //!return: the continuous probability distribution

  protected:
    PDFContinuousDesignerC(PDFContinuousDesignerBodyC &bod)
     : RCHandleC<PDFContinuousDesignerBodyC>(bod)
    {}
    //: Body constructor. 
    
    PDFContinuousDesignerC(const PDFContinuousDesignerBodyC *bod)
     : RCHandleC<PDFContinuousDesignerBodyC>(bod)
    {}
    //: Body constructor. 
    
    PDFContinuousDesignerBodyC& Body()
    { return static_cast<PDFContinuousDesignerBodyC &>(RCHandleC<PDFContinuousDesignerBodyC>::Body()); }
    //: Body Access. 
    
    const PDFContinuousDesignerBodyC& Body() const
    { return static_cast<const PDFContinuousDesignerBodyC &>(RCHandleC<PDFContinuousDesignerBodyC>::Body()); }
    //: Body Access. 
    
  };

}

#endif
