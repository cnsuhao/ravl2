// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLLOGICDECISIONTREE_HEADER
#define RAVLLOGICDECISIONTREE_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! lib=RavlLogic
//! file="Ravl/Logic/DecisionTree/DecisionTree.hh"
//! author="Charles Galambos"
//! docentry="Ravl.Logic.Decision Tree"

#include "Ravl/Logic/Literal.hh"
#include "Ravl/Logic/DecisionTreeBase.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Decision tree body.

  template<class DataT>
  class DecisionTreeBodyC 
    : public DecisionTreeBaseBodyC
  {
  public:
    DecisionTreeBodyC()
      {}
    //: Default constructor.
    
  protected:
    
  };
  
  //! userlevel=Develop
  //: Decision tree.
  
  template<class DataT>
  class DecisionTreeC 
    : public DecisionTreeBaseC 
  {
  public:
    DecisionTreeC()
      {}
    //: Default constructor.
    // creates an invalid handle.
    
  protected:
    DecisionTreeC(DecisionTreeBodyC<DataT> &bod)
      : DecisionTreeElementC(bod)
      {}
    //: Body constructor.
    
    DecisionTreeBodyC<DataT> &Body()
    { return static_cast<DecisionTreeBodyC<DataT> &>(DecisionTreeBaseC::Body()); }
    //: Access body.
    
    const DecisionTreeBodyC<DataT> &Body() const
    { return static_cast<const DecisionTreeBodyC<DataT> &>(DecisionTreeBaseC::Body()); }
    //: Access body.
    
  public:

  };
  
}

#endif
