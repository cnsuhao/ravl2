#ifndef RAVLLOGICLITERALINDEXFILTER_HEADER
#define RAVLLOGICLITERALINDEXFILTER_HEADER 1
///////////////////////////////////////////////////////////
//! rcsid="$Id$"

#include "Ravl/Logic/LiteralIndexBase.hh"
#include "Ravl/Logic/Var.hh"
#include "Ravl/Logic/BindSet.hh"

namespace RavlLogicN {
  
  //! userlevel=Develop
  //: Filter choice point.
  // Internal use only <p>
  // Used to store points in the tree search its worth backtracking to.
  
  class LiteralIndexFilterChoicePointBodyC 
    : public RCBodyVC
  {
  public:
    LiteralIndexFilterChoicePointBodyC()
      {}
    
  protected:
    LiteralIndexElementC node; // Place in tree.
    BindMarkT bindMark;        // Bind Marker, where to unwinde the stack to.
    VarC var;                  // Variable we're binding values to.
    LiteralIterC iter;         // Iterator.  Iterator used to go through possible matches.
  };

  //! userlevel=Develop
  //: Filter choice point.
  // Internal use only <p>
  // Used to store points in the tree search its worth backtracking to.
  
  class LiteralIndexFilterChoicePointC 
    : public  RCHandleC<LiteralIndexFilterChoicePointBodyC>
  {
  public:
    LiteralIndexFilterChoicePointC()
      {}
    //: Default constructor.
    // creates an invalid handle.
    
  };
  
  //! userlevel=Advanced
  //: Filter contents of index.
  
  class LiteralIndexBaseFilterBodyC 
    : public RCBodyC
  {
  public:
    LiteralIndexBaseFilterBodyC()
    {}
    //: Default constructor
    
    LiteralIndexBaseFilterBodyC(const LiteralC &nfilter,const LiteralIndexBaseC &nindex) 
      : filter(nfilter),
	index(nindex)
    {}
    //: Construct a new filter.
    
  protected:
    LiteralC filter;
    LiteralIndexBaseC index;
  };
  

  //! userlevel=Advanced
  //: Filter contents of index.
  
  class LiteralIndexBaseFilterC 
    : public RCHandleC<LiteralIndexBaseFilterBodyC>
  {
  public:
    LiteralIndexBaseFilterC()
    {}
    //: Default constructor
    // creates an invalid handle.
    
    LiteralIndexBaseFilterC(const LiteralC &filter,const LiteralIndexBaseC &index)
    {}
    //: Default constructor
    // creates an invalid handle.

  };
  
}


#endif
