// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLCOLLECTIONITER_HEADER
#define RAVLCOLLECTIONITER_HEADER 1
//////////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Misc"
//! author="Charles Galambos"
//! lib=RavlCore

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
