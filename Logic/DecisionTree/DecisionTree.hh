#ifndef RAVLLOGICDECISIONTREE_HEADER
#define RAVLLOGICDECISIONTREE_HEADER 1
/////////////////////////////////////////////////////////////////
//! rcsid="$Id$"

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
    
    DecisionTreeBodyC &Body()
    { return static_cast<DecisionTreeBodyC<DataT> &>(DecisionTreeBaseC::Body()); }
    //: Access body.

    const DecisionTreeBodyC &Body() const
    { return static_cast<const DecisionTreeBodyC<DataT> &>(DecisionTreeBaseC::Body()); }
    //: Access body.
    
  public:

  };
  
}

#endif
