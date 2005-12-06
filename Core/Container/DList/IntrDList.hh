// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_INTRDLIST_HEADER
#define RAVL_INTRDLIST_HEADER 1
//////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.API.Core.Lists"
//! userlevel=Advanced
//! file="Ravl/Core/Container/DList/IntrDList.hh"
//! lib=RavlCore
//! author="Radek Marik, Charles Galambos"

// IntrDListC is based on code written by Radek Marik.

#include "Ravl/DLink.hh"
#include "Ravl/Assert.hh"
#include "Ravl/Types.hh"

namespace RavlN {

  template <class DataT> class IntrDListC;
  template <class DataT> class IntrDLIterC;
  template <class DataT>
  ostream & operator<<(ostream & s, const IntrDListC<DataT> & list);
    
  //: Double-linked circular list
  // The IntrDListC class represents intrusive double-linked list of elements 
  // The list contains a head element and a chain of
  // elements. Empty list contains just its head element.
  // Because of efficiency references to elements of a list are not
  // checked if they are proper elements of a list or its head.
  // The class serves as a base class for more complex dynamic structures
  // as graphs. <p>
  // NB. This is a SMALL object.
  
  template <class DataT>
  class IntrDListC
    : public DLinkHeadC
  {
  public:
    inline IntrDListC(bool ndeleteEntries = true)
      : deleteEntries(ndeleteEntries)
    {}
    //: Construct an empty list.
    
    IntrDListC(const IntrDListC<DataT> &oth);
    //: Copy constructor.
    // This makes a copy of each entry in the list. <p>
    // NB. This will only work on intrinsic lists which 
    // manage the destruction of there own entries. i.e.
    // deleteEntries is true.

    const IntrDListC<DataT> &operator=(const IntrDListC<DataT> &oth);
    //: Assignment.
    // The contents of this list are replaced by a copy of the contents 
    // of 'oth'.
    // NB. This will only work on intrinsic lists which 
    // manage the destruction of there own entries. i.e.
    // deleteEntries is true.
    
    inline ~IntrDListC() 
    { Empty(); }
    // Destructor, each list element is destroyed.
    
    void Empty() {
      if(deleteEntries) {
	while(&head.Next() != &head)
	  IntrDListC<DataT>::Delete(head.Next());
      } else {
	// Unlink all items in the list to stop
	// the unlink destructors doing anything silly.
	DLinkC *place = &head.Next();
	while(place != &head) {
	  DLinkC *np = &place->Next();
	  place->SetSelfPointing();
	  place = np;
	}
      }
    }
    //: Empty the list of all contents
    
    //---------- Access to the elements -----------------------------
    
    DataT &First()
    { return static_cast<DataT &>(head.Next()); }
    //: Get first link in list.
    
    DataT &Last()
    { return static_cast<DataT &>(head.Prev()); }
    //: Get the last ilink in the list.
    
    const DataT &First() const
    { return static_cast<const DataT &>(head.Next()); }
    //: Get first link in list.
    
    const DataT &Last() const
    { return static_cast<const DataT &>(head.Prev()); }
    //: Get the last ilink in the list.
    
    //---------- Elementary changes in the list -------------
    
    void InsFirst(DataT &dat)
    { DLinkHeadC::InsFirst(dat); }
    //: Push element onto the begining of the list.
    
    void InsLast(DataT &dat)
    { DLinkHeadC::InsLast(dat); }
    //: Push element onto the end of the list.
    
    DataT &PopFirst()  { 
      RavlAssert(!IsEmpty());
      DataT &tmp = First();
      head.Next().Unlink();
      return tmp;
    }
    //: Pop item off front of list.
    // It is up to the user to ensure the object is deleted.
    
    DataT &PopLast()  { 
      RavlAssert(!IsEmpty());
      DataT &tmp = Last();
      head.Prev().Unlink();
      return tmp;
    }
    //: Pop item off back of list.
    // It is up to the user to ensure the object is deleted.

    void DelFirst()  { 
      RavlAssert(!IsEmpty());
      IntrDListC<DataT>::Delete(head.Next());
    }
    //: Pop item off front of list.
    // It is up to the user to ensure the object is deleted.
    
    void DelLast()  { 
      RavlAssert(!IsEmpty());
      IntrDListC<DataT>::Delete(head.Prev().Unlink());
    }
    //: Pop item off back of list.
    // It is up to the user to ensure the object is deleted.
    
  protected:
    
    static void Delete(DLinkC &elm) 
    { delete &static_cast<DataT &>(elm); }
    //: Unlink and delete an element from the list.
    
    DLinkC &Head()
    { return DLinkHeadC::Head(); }
    //: Get head of list.
  
    const DLinkC &Head() const
    { return DLinkHeadC::Head(); }
    //: Get head of list.
    
    bool deleteEntries; // Delete entries when finished with them ?

    friend class IntrDLIterC<DataT>;
  };

}

#include "Ravl/IntrDLIter.hh"

namespace RavlN {  
  
  template <class DataT>
  IntrDListC<DataT>::IntrDListC(const IntrDListC<DataT> &oth)
    : deleteEntries(oth.deleteEntries)
  {
    RavlAssert(deleteEntries); // A way to check this makes sense.
    for(IntrDLIterC<DataT> it(oth);it;it++)
      InsLast(*new DataT(*it));
  }
  
  template <class DataT>
  const IntrDListC<DataT> &IntrDListC<DataT>::operator=(const IntrDListC<DataT> &oth) {
    Empty();
    deleteEntries = oth.deleteEntries;
    RavlAssert(deleteEntries); // A way to check this makes sense.
    for(IntrDLIterC<DataT> it(oth);it;it++)
      InsLast(*new DataT(*it));
    return *this;
  }

}



#endif
