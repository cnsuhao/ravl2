#ifndef RAVLCOLLECTIONITER_HEADER
#define RAVLCOLLECTIONITER_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Misc"

#include "Ravl/Collection.hh"
#include "Ravl/SArr1Iter.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Collection iterator.
  // Iterates through the contents of a collection.
  
  template<class DataT>
  class CollectionIterC 
    : public SArray1dIterC<DataT>
  {
  public:
    CollectionIterC(CollectionC<DataT> &c)
      : SArray1dIterC<DataT>(c.Array())
    {}
    //: Constructor.
    
  };

  //! userlevel=Normal
  //: Collection iterator.
  // Iterates through the contents of a collection.
  
  template<class DataT>
  class CollectionConstIterC 
    : public SArray1dIterC<DataT>
  {
  public:
    CollectionConstIterC(const CollectionC<DataT> &c)
      : SArray1dIterC<DataT>(c.Array())
    {}
    //: Constructor.
    
  };
  
}


#endif
