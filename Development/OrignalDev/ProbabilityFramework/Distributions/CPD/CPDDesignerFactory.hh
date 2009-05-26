// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2006, OmniPerception Ltd.
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLPROB_CPDDESIGNERFACTORY_HEADER
#define RAVLPROB_CPDDESIGNERFACTORY_HEADER 1
//! rcsid="$Id$"
//! lib=RavlProb
//! author="Robert Crida"
//! docentry="Ravl.API.Math.Statistics.Probability Framework"

#include "Ravl/RCHandleV.hh"
#include "Ravl/Prob/CPDDesigner.hh"

namespace RavlProbN {
  using namespace RavlN;

  //! userlevel=Develop
  //: Class used for choosing conditional probability distribution designers
  class CPDDesignerFactoryBodyC
    : public RCBodyVC {
  public:
    CPDDesignerFactoryBodyC();
    //: Constructor

    virtual ~CPDDesignerFactoryBodyC();
    //: Destructor
    
    CPDDesignerC GetCPDDesigner(const VariableC& variable, const VariableSetC& parentVariableSet) const;
    //: Find a distribution designer for the specified domain
    //!param: variable - the type of dependent random variable
    //!param: parentVariableSet - set of parent variables
    //!return: the conditional probability distribution designer
  };

  //! userlevel=Normal
  //: Class used for choosing conditional probability distribution designers
  //!cwiz:author
  
  class CPDDesignerFactoryC
    : public RCHandleC<CPDDesignerFactoryBodyC>
  {
  public:
    CPDDesignerFactoryC()
    {}
    //: Default constructor makes invalid handle

    static CPDDesignerFactoryC GetInstance();
    //: Get an instance of the factory

    CPDDesignerC GetCPDDesigner(const VariableC& variable, const VariableSetC& parentVariableSet) const
    { return Body().GetCPDDesigner(variable, parentVariableSet); }
    //: Find a distribution designer for the specified domain
    //!param: variable - the type of dependent random variable
    //!param: parentVariableSet - set of parent variables
    //!return: the conditional probability distribution designer

  private:
    CPDDesignerFactoryC(bool)
      : RCHandleC<CPDDesignerFactoryBodyC>(new CPDDesignerFactoryBodyC())
    {}
    //: Private constructor
    
  protected:
    CPDDesignerFactoryC(CPDDesignerFactoryBodyC &bod)
     : RCHandleC<CPDDesignerFactoryBodyC>(bod)
    {}
    //: Body constructor. 
    
    CPDDesignerFactoryC(const CPDDesignerFactoryBodyC *bod)
     : RCHandleC<CPDDesignerFactoryBodyC>(bod)
    {}
    //: Body constructor. 
    
    CPDDesignerFactoryBodyC& Body()
    { return static_cast<CPDDesignerFactoryBodyC &>(RCHandleC<CPDDesignerFactoryBodyC>::Body()); }
    //: Body Access. 
    
    const CPDDesignerFactoryBodyC& Body() const
    { return static_cast<const CPDDesignerFactoryBodyC &>(RCHandleC<CPDDesignerFactoryBodyC>::Body()); }
    //: Body Access. 
   
  private:
    static CPDDesignerFactoryC m_instance;
    //: The instance of the factory 
  };

}

#endif
