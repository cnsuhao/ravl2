// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2003, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_TRAITS_HEADER
#define RAVL_TRAITS_HEADER 1
//! author="Charles Galambos, based on ideas from sigc++"
//! date="27/4/2003
//! docentry="Ravl.Core.Misc"
//! rcsid="$Id$"
//! lib=RavlCore

#include "Ravl/config.h"

namespace RavlN {
  
  //! userlevel=Advanced
  //: Traits for type
  // Used for decomposing types into there components.
  // i.e. const, reference and base types.
  
  template<typename DataT>
  struct TraitsC {
  public:
    typedef DataT &RefT;     //: Non-const reference to type.
    typedef DataT TypeT;     //: Unmodified type.
    typedef DataT BaseTypeT; //: Base type ignoring const and reference.
  };
  
  //! userlevel=Advanced
  //: Traits for type
  // Used for decomposing types into there components.
  // i.e. const, reference and base types.
  
  template<typename DataT >
  struct TraitsC<DataT &> {
  public:
    typedef DataT &RefT;     //: Non-const reference to type.
    typedef DataT &TypeT;    //: Unmodified type.
    typedef DataT BaseTypeT; //: Base type ignoring const and reference.
  };

  //! userlevel=Advanced
  //: Traits for type
  // Used for decomposing types into there components.
  // i.e. const, reference and base types.
  
  template<typename DataT >
  struct TraitsC<const DataT &> {
  public:
    typedef DataT &RefT;        //: Non-const reference to type.
    typedef const DataT &TypeT; //: Unmodified type.
    typedef DataT BaseTypeT;    //: Base type ignoring const and reference.
  };
  
}

#endif
