// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DLITER_HEADER
#define RAVL_DLITER_HEADER 1
////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Lists"
//! file="Ravl/Core/Container/DList/DLIter.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Radek Marik, Charles Galambos"
//! example=exDList.cc

// DLIterC is based on code written by Radek Marik.

#include "Ravl/DList.hh"

namespace RavlN {

  //! userlevel=Normal
  //: Double linked list iterator.
  // Note: This iterator holds a refrence to the list it is iterating.
  // (Unlike some other iterators.)
  
  template<class DataT> 
  class DLIterC  {
  public:
    DLIterC()
      { place = &lst.Head(); }
    //: Default constructor.
    // Creates an invalid iterator.
    
    bool IsValid() const
      { return lst.IsValid(); }
    //: Is a valid iterator ?
    
    void First() 
      { place = &lst.Head().Next(); }
    //: Goto first item in list.

    void Last() 
      { place = &lst.Head().Prev(); }
    //: Goto last item in list.
    
    DLIterC(const DListC<DataT> &nlst)
      : lst(nlst)
      { First(); }
    //: Construct an iterator from a list.
    // The iterator is placed at the first
    // element in the list. If there is any.
    
    DListC<DataT> Copy() const
      { return Body().Copy(); }
    //: Make a copy of this list.
    
    const DListC<DataT> &List() const
      { return lst; }
    //: Access list we're iterating.
    
    operator bool() const
      { return place != &lst.Head(); }
    //: Is iterator at a valid position ?
    
    bool operator!() const
      { return place == &lst.Head(); }
    //: Is iterator at a invalid position ?
    
    void operator++(int) 
      { place = &place->Next(); }
    //: Goto next element.

    void operator++() 
      { place = &place->Next(); }
    //: Goto next element.
    
    void operator--(int) 
      { place = &place->Prev(); }
    //: Goto previous element.
    
    void operator--() 
      { place = &place->Prev(); }
    //: Goto previous element.
    
    void InsertBef(const DataT &dat)
      { place->LinkBef(*new DLinkDataC<DataT>(dat)); }
    //: Insert data before current element.
    // if at the head of the list  (i.e. operator bool() failes.)
    // then add at end.
    
    void InsertAft(const DataT &dat)
      { place->LinkAft(*new DLinkDataC<DataT>(dat)); }
    //: Insert data after current element.
    // if at the head of the list  (i.e. operator bool() failes.)
    // then add at begining.
    
    void MoveBef(DLIterC<DataT> &it) 
      { place->LinkBef(it.Extract()); }
    //: Move the list element indicated by 'it' to before
    //: the element in this list.
    
    void MoveAft(DLIterC<DataT> &it) 
      { place->LinkAft(it.Extract()); }
    //: Move the list element indicated by 'it' to before
    //: the element in this list.
    
    void Del() {
      RavlAssert(IsValid() && *this);
      DLinkC *next = &place->Prev();
      DListBodyC<DataT>::Delete(*place);
      place = next;
    }
    //: Remove current element from the list.
    // This moves the iterator to the previous element.
    // NB. The iterator must be pointing to a valid element. <p>
    // Because the moves the prevous element it makes it easy
    // to delete elements from a list in a for() loop. e.g. the
    // following will work correctly.
    // <pre>
    // for(DLIterC<DataT> it(x);it;it++) 
    //   if(*it == 2)
    //     it.Del();
    // </pre>
    
    void DelMoveNext() {
      RavlAssert(IsValid() && *this);
      DLinkC *next = &place->Next();
      DListBodyC<DataT>::Delete(*place);
      place = next;
    }
    //: Remove current element from the list.
    // This moves the iterator to the previous element.
    // NB. The iterator must be pointing to a valid element.    
    
    DataT &operator*()
      { return DLinkData().Data(); }
    //: Access data.
    
    const DataT &operator*() const
      { return DLinkData().Data(); }
    //: Constant access to data.
    
    DataT *operator->()
      { return &DLinkData().Data(); }
    //: Access member function of data..
    
    const DataT *operator->() const
      { return &DLinkData().Data(); }
    //: Constant access to member function of data..
    
    bool operator==(const DLIterC<DataT> &oth) const
      { return place == oth.place; }
    //: Are these iterators equal.
    // True if both iterators point to the same element
    // in the same list.  False otherwise.
    
    bool operator!=(const DLIterC<DataT> &oth) const
      { return place != oth.place; }
    //: Are these iterators unequal.
    // True if the iterators point to different elements
    // in any lists.  False otherwise.

    bool IsElm() const
      { return place != &lst.Head(); }
    //: Is iterator at a valid position ?
    // AMMA compatibility function, use cast to bool instread ie if(iter) {..}
    
    void Next()
      { (*this)++; }
    //: Goto next element.
    // AMMA compatibility function, use ++ operator.
    
    void Prev()
      { (*this)--; }
    //: Goto next element.
    // AMMA compatibility function, use -- operator.
    
    DLIterC<DataT> &RelNth(IntT n) {
      if (n > 0)
	while (n--) Next();
      else
	while (n++) Prev();
      return (*this);
    }
    //: Move to the n-th element from the current element. 
    // The index 'n' can be positive, zero, or negative. 
    // Particularly, the n = 0 means no move,
    // n = 1 means the move to the next element, 
    // and n = -1 means the move to the previous element. <p>
    // Returns a refrence to this iterator.
    
    DLIterC<DataT> &Nth(IntT n) {
      First();
      return RelNth(n);
    }
    //: Sets to the n-th element of the list. 
    // The index 'n' can be 
    // negative. The first element of the list has the index 0,
    // the last element has the index -1. It does not skip the head
    // of the list.<p>
    // Returns a refrence to this iterator.
    
    DataT &Data()
      { return DLinkData().Data(); }
    //: Access data 
    // AMMA compatibility function, use unary * operator.

    const DataT &Data() const
      { return DLinkData().Data(); }
    //: Constant access to data.
    // AMMA compatibility function, use unary * operator.

    DListC<DataT> Tail() {
      DListC<DataT> ret;
      ret.Body().Head().CutPaste(place->Next(),lst.Body().LastLink());
      return ret;
    }
    //: Clip out the tail of the list.
    // Return all of the elements after this element in the list.
    
    DListC<DataT> Head() {
      DListC<DataT> ret;
      ret.Body().Head().CutPaste(lst.Body().FirstLink(),*place);
      return ret;
    }
    //: Clip out the head of the list.
    // Return all of the elements before this element in the list.
    
    DListC<DataT> InclusiveTail() {
      DListC<DataT> ret;
      DLinkC *nv = &place->Prev();
      ret.Body().Head().CutPaste(*place,lst.Body().LastLink());
      place = nv;
      return ret;
    }
    //: Clip out the tail of the list including this element.
    // Returns this element and the following elements
    // from the list. The interator is left point to
    // the last element in the remaining list.
    
    DListC<DataT> InclusiveHead() {
      DListC<DataT> ret;
      DLinkC *nv = &place->Next();
      ret.Body().Head().CutPaste(lst.Body().FirstLink(),*nv);
      place = nv;
      return ret;
    }
    //: Clip out the head of the list including this element.
    // Returns this element and the following elements
    // from the list. The interator is left point to
    // the last element in the remaining list.
    
    DListC<DataT> Clip(const DLIterC<DataT> &end) {
      DListC<DataT> ret;
      RavlAssertMsg(&end.List().Body() == &lst.Body(),"Iterators must be from the same list.");
      DLinkC *nv = &place->Prev();
      ret.Body().Head().CutPaste(*place,*end.place);
      place = nv;
      return ret;
    }
    //: Clip out section of the list
    // Returns the elements starting from this one to the element before
    // the end. This iterator is moved the previous element. <p>
    // NB. It is the user's responsibility to ensure 'end' is an 
    // element following this element in the same list.
    
  protected:
    DLIterC(const DListBodyC<DataT> &nlst)
      : lst(const_cast<DListBodyC<DataT> &>(nlst)) // A bit evil, but it make life alot easier.
      { First(); }
    //: Construct from a list body.
    
    DLinkDataC<DataT> &DLinkData()
      { return static_cast<DLinkDataC<DataT> &>(*place); }
    //: Access as data element.
    
    const DLinkDataC<DataT> &DLinkData() const
      { return static_cast<const DLinkDataC<DataT> &>(*place); }
    //: Access as data element.
    
    DLinkDataC<DataT> &Extract() {
      RavlAssert(*this); // Have to be at a valid element.
      DLinkDataC<DataT> &cur(DLinkData());
      place->Unlink();
      place = &cur.Prev();
      return cur;
    }
    //: Extract the current element, move the iterator back 1.

    DLinkDataC<DataT> &ExtractNext() {
      RavlAssert(*this); // Have to be at a valid element.
      DLinkDataC<DataT> &cur(DLinkData());
      place->Unlink();
      place = &cur.Next();
      return cur;
    }
    //: Extract the current element, move the iterator to the next element in the list.
    
    DListC<DataT> lst;
    DLinkC *place;
    
    friend class DListBodyC<DataT>;
#if RAVL_NEW_ANSI_CXX_DRAFT
    friend ostream &operator<< <DataT>(ostream &strm,const DListBodyC<DataT> &lst); 
#else
    friend ostream &operator<<(ostream &strm,const DListBodyC<DataT> &lst); 
#endif
  };

}

#endif
