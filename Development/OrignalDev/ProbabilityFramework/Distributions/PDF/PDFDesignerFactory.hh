// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_PDFDESIGNERFACTORY_HEADER
#define RAVLPROB_PDFDESIGNERFACTORY_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Prob/PDFContinuousDesigner.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Class used for choosing probability distribution designers
  class PDFDesignerFactoryBodyC
    : public RCBodyVC {
  public:
    PDFDesignerFactoryBodyC();
    //: Constructor

    virtual ~PDFDesignerFactoryBodyC();
    //: Destructor
    
    PDFContinuousAbstractC DesignPDFContinuous(const VariableContinuousC& variable, const DListC<RealT>& realSamples) const;
    //: Fit the best distribution to the given sample
    //!param: variable - the type of continuous random variable
    //!param: realSamples - real sample values
    //!return: the continuous probability distribution

  private:
    RealT MeasureError(const PDFContinuousAbstractC& pdf, const DListC<RealT>& realSamples) const;
    //: Measure how well the pdf fits the samples

  private:
    DListC<PDFContinuousDesignerC> m_continuousDesigners;
    //: List of continuous PDF designers
  };

  //! userlevel=Normal
  //: Class used for choosing probability distribution designers
  //!cwiz:author
  
  class PDFDesignerFactoryC
    : public RCHandleC<PDFDesignerFactoryBodyC>
  {
  public:
    PDFDesignerFactoryC()
    {}
    //: Default constructor makes invalid handle

    static PDFDesignerFactoryC GetInstance();
    //: Get an instance of the factory

    PDFContinuousAbstractC DesignPDFContinuous(const VariableContinuousC& variable, const DListC<RealT>& realSamples) const
    { return Body().DesignPDFContinuous(variable, realSamples); }
    //: Fit the best distribution to the given sample
    //!param: variable - the type of continuous random variable
    //!param: realSamples - real sample values
    //!return: the continuous probability distribution

  private:
    PDFDesignerFactoryC(bool)
      : RCHandleC<PDFDesignerFactoryBodyC>(new PDFDesignerFactoryBodyC())
    {}
    //: Private constructor
    
  protected:
    PDFDesignerFactoryC(PDFDesignerFactoryBodyC &bod)
     : RCHandleC<PDFDesignerFactoryBodyC>(bod)
    {}
    //: Body constructor. 
    
    PDFDesignerFactoryC(const PDFDesignerFactoryBodyC *bod)
     : RCHandleC<PDFDesignerFactoryBodyC>(bod)
    {}
    //: Body constructor. 
    
    PDFDesignerFactoryBodyC& Body()
    { return static_cast<PDFDesignerFactoryBodyC &>(RCHandleC<PDFDesignerFactoryBodyC>::Body()); }
    //: Body Access. 
    
    const PDFDesignerFactoryBodyC& Body() const
    { return static_cast<const PDFDesignerFactoryBodyC &>(RCHandleC<PDFDesignerFactoryBodyC>::Body()); }
    //: Body Access. 
   
  private:
    static PDFDesignerFactoryC m_instance;
    //: The instance of the factory 
  };

}

#endif
