// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_DLIST_HEADER
#define RAVL_DLIST_HEADER 1
/////////////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Lists"
//! file="Ravl/Core/Container/DList/DList.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Radek Marik, Charles Galambos"
//! example=exDList.cc

// DListC is based on code written by Radek Marik.

#include "Ravl/DLink.hh"
#include "Ravl/Assert.hh"
#include "Ravl/RefCounter.hh"

//: Ravl global namespace.

namespace RavlN {

  class BinIStreamC;
  class BinOStreamC;
  
  template<class DataT> class DLIterC;
  template<class DataT> class DListC;
  template<class DataT> class DListBodyC;
  template<class DataT> ostream &operator<<(ostream &,const DListBodyC<DataT> &);
  template<class DataT> istream &operator>>(istream &,DListBodyC<DataT> &);
  template<class DataT> BinOStreamC &operator<<(BinOStreamC &,const DListBodyC<DataT> &);
  template<class DataT> BinIStreamC &operator>>(BinIStreamC &,DListBodyC<DataT> &);
  
  //! userlevel=Develop
  //: Double linked list body.
  // Implementation: <p>
  // The list contains a head element and a chain of
  // elements. Empty list contains just its head element.
  // Because of efficiency references to elements of a list are not
  // checked if they are proper elements of a list or its head.
  
  template<class DataT>
  class DListBodyC
    : public DLinkHeadC,
      public RCBodyVC
  {
  public:
    DListBodyC()
    {}
    //: Default constructor.
    
    ~DListBodyC()
    { Empty(); }
    //: Destructor.
    
    RCBodyVC &Copy() const;
    //: Make copy of body.
    // This should be provided in derived classes.
    // this funtion will issue an assertion failure if called.
    
    void Empty() {
      while(&head.Next() != &head)
	DListBodyC<DataT>::Delete(head.Next());
    }
    //: Empty the list of all contents
    
    void InsFirst(const DataT &dat)
    { DLinkHeadC::InsFirst(*new DLinkDataC<DataT>(dat)); }
    //: Insert element into the begining of the list.

    void InsLast(const DataT &dat)
    { DLinkHeadC::InsLast(*new DLinkDataC<DataT>(dat)); }
    //: Insert element into the end of the list.

    DataT PopFirst()  { 
      RavlAssert(!IsEmpty());
      DataT tmp(FirstLink().Data());
      DListBodyC<DataT>::Delete(head.Next());  
      return tmp;
    }
    //: Pop item off beginning of this list.

    DataT PopLast()  { 
      RavlAssert(!IsEmpty());
      DataT tmp(LastLink().Data());
      DListBodyC<DataT>::Delete(head.Prev());
      return tmp;
    }
    //: Pop item off end of list.
    
    void operator+=(const DataT &dat)
    { InsLast(dat); }
    //: Add 'dat' to end of this list.
    
    void operator+=(const DListC<DataT> &dat);
    //: Copy contents of other list to end of this one.
    
    void MoveFirst(DListC<DataT> & lst)
    { DLinkHeadC::MoveFirst(lst.Body()); }
    //: Move the entire contents of 'lst' to the front of this one.
    // this leaves 'lst' empty.
    
    void MoveLast(DListC<DataT> & lst)
    { DLinkHeadC::MoveLast(lst.Body()); }
    //: Move the entire contents of 'lst' to the end of this one.
    // this leaves 'lst' empty.
    
    void MoveFirst(DLIterC<DataT> & at) { 
      RavlAssert(at);
      DLinkC &nxt = at.place->Prev();
      DLinkHeadC::MoveFirst(*at.place); 
      at.place = &nxt;
    }
    //: Move the single item 'at' to the front of this list.
    // Leaves iterator pointing to the previous element.
    
    void MoveLast(DLIterC<DataT> & at) { 
      RavlAssert(at);
      DLinkC &nxt = at.place->Prev(); 
      DLinkHeadC::MoveLast(*at.place); 
      at.place = &nxt;
    }
    //: Move the single item 'at' to the end of this list.
    // Leaves iterator pointing to the previous element.
    
    typedef bool (*MergeSortCmpT)(const DataT &l1,const DataT &l2);
    //: Comparison function for merge sort.
    
    bool operator==(const DListBodyC<DataT> &oth) const;
    //: Test if lists are identical.
    // assumes '==' is defined for 'DataT'
    
    bool operator!=(const DListBodyC<DataT> &oth) const
    { return !((*this) == oth); }
    //: Test if lists are different.
    // assumes '==' is defined for 'DataT'

    bool Contains(const DataT &x);
    //: Test if this list contains an element == to 'x'.
    
  protected:    
    static bool MergeSortHelpCmp(DLinkC *l1,DLinkC *l2,void *dat) {
      return ((MergeSortCmpT) dat)(static_cast<const DLinkDataC<DataT> &>(*l1).Data(),
				   static_cast<const DLinkDataC<DataT> &>(*l2).Data());
    }
    //: Comparison helper function.
    
  public:
    //MergeSortCmpT
    void MergeSort(bool (*cmp)(const DataT &l1,const DataT &l2)) // 
    { DLinkHeadC::MergeSort(&DListBodyC<DataT>::MergeSortHelpCmp,(void *) cmp); }
    //: Merge sort the list with comparison function 'cmp'.
    
    DataT &First() 
    { return FirstLink().Data(); }
    //: Get first element in list.
    // Note, list MUST be non-empty.
    
    DataT &Last() 
    { return LastLink().Data();  }
    //: Get last element in list.
    // Note, list MUST be non-empty.
    
    const DataT &First() const 
    { return FirstLink().Data(); }
    //: Get first element in list.
    // Note, list MUST be non-empty.
    
    const DataT &Last() const 
    { return LastLink().Data(); }
    //: Get first element in list.
    // Note, list MUST be non-empty.
    
    bool Del(const DataT &x);
    //: Remove first instance of 'x' found in list.
    // returns true if the item is found and removed, 
    // false otherwise.
    
  protected:
    static void Delete(DLinkC &elm) 
    { delete &static_cast<DLinkDataC<DataT> &>(elm); }
    //: Unlink and delete an element from the list.
    // The delete will unkink the node automaticly.
    
    DLinkDataC<DataT> &FirstLink() { 
      RavlAssert(!IsEmpty());
      return static_cast<DLinkDataC<DataT> &>(head.Next()); 
    }
    //: Get first link in list.
    
    DLinkDataC<DataT> &LastLink() { 
      RavlAssert(!IsEmpty());
      return static_cast<DLinkDataC<DataT> &>(head.Prev()); 
    }
    //: Get the last ilink in the list.
    
    const DLinkDataC<DataT> &FirstLink() const { 
      RavlAssert(!IsEmpty());
      return static_cast<const DLinkDataC<DataT> &>(head.Next()); 
    }
    //: Get first link in list.
    
    const DLinkDataC<DataT> &LastLink() const { 
      RavlAssert(!IsEmpty());
      return static_cast<const DLinkDataC<DataT> &>(head.Prev()); 
    }
    //: Get the last ilink in the list.
    
    DLinkC &Head()
    { return DLinkHeadC::Head(); }
    //: Get head of list.

    const DLinkC &Head() const
    { return DLinkHeadC::Head(); }
    //: Get head of list.
    
    DataT &Nth(int n);
    //: Find the nth element in the list.
    // 0 is the first element, 2 the second etc.
    // -1 is the last, -2 second from last.
    
    const DataT &Nth(int n) const;
    //: Find the nth element in the list.
    // 0 is the first element, 2 the second etc.
    // -1 is the last, -2 second from last.
    
    friend class DListC<DataT>;
    friend class DLIterC<DataT>;
    
#if RAVL_NEW_ANSI_CXX_DRAFT
    friend ostream &operator<< <DataT>(ostream &strm,const DListBodyC<DataT> &lst); 
    friend BinOStreamC &operator<< <DataT>(BinOStreamC &strm,const DListBodyC<DataT> &lst); 
#else
    friend ostream &operator<< (ostream &strm,const DListBodyC<DataT> &lst); 
    friend BinOStreamC &operator<< (BinOStreamC &strm,const DListBodyC<DataT> &lst); 
#endif
  };

  template<class DataT>
  ostream &operator<<(ostream &out,const DListBodyC<DataT> &lst);
  //: Send to stream.
  
  template<class DataT>
  istream &operator>>(istream &out,DListBodyC<DataT> &lst);
  //: Read from stream.
  
  template<class DataT>
  ostream &operator<<(ostream &strm,const DListC<DataT> &lst);
  //: Send to stream.
  
  template<class DataT>
  istream &operator>>(istream &strm,DListC<DataT> &lst);
  //: Read from stream.

  template<class DataT>
  BinOStreamC &operator<<(BinOStreamC &strm,const DListC<DataT> &lst);
  //: Write to a binary stream.
  
  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC &strm,DListC<DataT> &lst);
  //: Read from a binary stream.
  // 
  
  //! userlevel=Normal
  //: Double linked List 
  // This is a refrence counted, doubly linked list. <p>
  // Implementation:<p>
  // The list contains a head element and a chain of
  // elements. Empty list contains just its head element.
  // Because of efficiency references to elements of a list are not
  // checked if they are proper elements of a list or its head.
  //
  // <p> To iterate through a list efficiently, you need to use on of the list
  // iterator class <a href="Ravl.DLIterC.html">DLIterC</a>
  
  template<class DataT>
  class DListC 
    : public RCHandleC<DListBodyC<DataT> > 
  {
  public:
    typedef DLIterC<DataT> IteratorT;
    //: Make iterator type accessible.
    
    typedef DataT ElementT;
    //: Make element type accessible.
    
    DListC()
      : RCHandleC<DListBodyC<DataT> >(*new DListBodyC<DataT>())
    {}
    //: Default constructor.
    // This creates an empty list.
    
  protected:
    DListC(DListBodyC<DataT> &bod)
      : RCHandleC<DListBodyC<DataT> >(bod)
    {}
    //: Body constructor.
    
    DListBodyC<DataT> &Body()
    { return RCHandleC<DListBodyC<DataT> >::Body(); }
    //: Access body.

    const DListBodyC<DataT> &Body() const
    { return RCHandleC<DListBodyC<DataT> >::Body(); }
    //: Constant access to body.
    
    DLinkC &Head()
    { return Body().Head(); }
    //: Get head of list.
    
    const DLinkC &Head() const
    { return Body().Head(); }
    //: Get head of list.
    
  public:
    bool IsEmpty() const
    { return Body().IsEmpty(); }
    //: Test is the list is empty.
    
    UIntT Size() const
    { return Body().Size(); }
    //: Count the number of elements in the list.
    // This is slow! It goes through the list counting the elements.
    
    void Reverse() 
    { Body().Reverse(); }
    //: Reverse the order of the list.
    
    DListC<DataT> Copy() const
    { return DListC<DataT>(static_cast<DListBodyC<DataT> &>(Body().Copy())); }
    //: Make a copy of this list.
    
    void InsFirst(const DataT &dat)
    { Body().InsFirst(dat); }
    //: Push element onto the begining of the list.
    
    void InsLast(const DataT &dat)
    { Body().InsLast(dat); }
    //: Push element onto the end of the list.
    
    DataT PopFirst()  
    { return Body().PopFirst(); }
    //: Pop item off front of list.
    
    DataT PopLast()  
    { return Body().PopLast(); }
    //: Pop item off end of list.
    
    void DelFirst()
    { Body().PopFirst(); }
    //: Delete the first element from the list.
    
    void DelLast()
    { Body().PopLast(); }
    //: Delete the last element from the list.
    
    void Empty()
    { Body().Empty(); }
    //: Empty the list of all its contents.
    
    DListC<DataT> &operator+=(const DataT &dat)
    { Body().InsLast(dat); return *this; }
    //: Add element to the end of the list.
    
    DListC<DataT> & operator+=(const DListC<DataT> &dat)
    { Body() += dat; return *this; }
    //: Copy contents of other list to end of this one.
    
    void MoveFirst(DListC<DataT> & lst)
    { Body().MoveFirst(lst); }
    //: Move the entire contents of 'lst' to the beginning of this one.
    // this leaves 'lst' empty.
    
    void MoveLast(DListC<DataT> & lst)
    { Body().MoveLast(lst); }
    //: Move the entire contents of 'lst' to the end of this one.
    // this leaves 'lst' empty.

    void MoveFirst(DLIterC<DataT> & at)
    { Body().MoveFirst(at); }
    //: Move the single item 'at' to the beginning of this list.
    
    void MoveLast(DLIterC<DataT> & at)
    { Body().MoveLast(at); }
    //: Move the single item 'at' to the end of this list.
    
    void MergeSort(DListBodyC<DataT>::MergeSortCmpT cmp)
    { Body().MergeSort(cmp); }
    //: Merge sort the list with comparison function 'cmp'.

    bool operator==(const DListC<DataT> &oth) const;
    //: Are lists identical ?
    // Test if lists have identical content.
    
    bool operator!=(const DListC<DataT> &oth) const
    { return !((*this) == oth); }
    //: Are lists different ?
    // Test if lists have different content.
    
    DataT &First() 
    { return Body().First(); }
    //: Get first element in list.
    // NB. List MUST be non-empty.
    
    DataT &Last() 
    { return  Body().Last(); }
    //: Get first element in list.
    // NB. List MUST be non-empty.
    
    const DataT &First() const 
    { return Body().First(); }
    //: Get first element in list.
    // NB. List MUST be non-empty.
    
    const DataT &Last() const 
    { return Body().Last(); }
    //: Get first element in list.
    // NB. List MUST be non-empty.
    
    bool Del(const DataT &x)
    { return Body().Del(x); }
    //: Remove first instance of 'x' found in list.
    // returns true if the item is found and removed, 
    // false otherwise.
    
    bool Contains(const DataT &x)
    { return Body().Contains(x); }
    //: Test if this list contains an element == to 'x'.
    
    DataT &Nth(int n)
    { return Body().Nth(n); }
    //: Find the nth element in the list.
    // 0 is the first element, 2 the second etc.
    // -1 is the last, -2 second from last.
    
    const DataT &Nth(int n) const
    { return Body().Nth(n); }
    //: Find the nth element in the list.
    // 0 is the first element, 2 the second etc.
    // -1 is the last, -2 second from last.
    
    friend class DLIterC<DataT>;
    friend class DListBodyC<DataT>;

#if RAVL_NEW_ANSI_CXX_DRAFT
    friend ostream &operator<< <DataT>(ostream &strm,const DListC<DataT> &lst);
    friend istream &operator>> <DataT>(istream &strm,DListC<DataT> &lst);
    friend BinOStreamC &operator<< <DataT>(BinOStreamC &strm,const DListC<DataT> &lst);
    friend BinIStreamC &operator>> <DataT>(BinIStreamC &strm,DListC<DataT> &lst);
#else
    friend ostream &operator<< (ostream &strm,const DListC<DataT> &lst);
    friend istream &operator>> (istream &strm,DListC<DataT> &lst);
    friend BinOStreamC &operator<< (BinOStreamC &strm,const DListC<DataT> &lst);
    friend BinIStreamC &operator>> (BinIStreamC &strm,DListC<DataT> &lst);
#endif
  };
  
}

#include "Ravl/DLIter.hh"

namespace RavlN {
  
  ///// DListBodyC //////////////////////////////////////////////////////
  
template<class DataT> 
RCBodyVC &DListBodyC<DataT>::Copy() const {
  DListBodyC<DataT> *ret = new DListBodyC<DataT>();
  for(DLIterC<DataT> it(*this);it;it++)
    ret->InsLast(*it);
  return *ret;
}
  
  template<class DataT> 
  void DListBodyC<DataT>::operator+=(const DListC<DataT> &dat) {
    for(DLIterC<DataT> it(dat);it;it++)
      (*this) += *it;
  }


  template<class DataT>
  bool DListBodyC<DataT>::Del(const DataT &x) {
    for(DLIterC<DataT> it(*this);it;it++)
      if(*it == x) {
	it.Del();
	return true;
      }
    return false;
  }

  //: Test if lists are identical.
  // assumes '==' is defined for 'DataT'
  
  template<class DataT> 
  bool DListBodyC<DataT>::operator==(const DListBodyC<DataT> &oth) const {
    DLIterC<DataT> oit(oth),it(*this);
    for(;it && oit;it++,oit++)
      if(!(*it == *oit))
	return false;
    return !(it || oit);
  }
  
  template<class DataT> 
  bool DListBodyC<DataT>::Contains(const DataT &x) {
    for(DLIterC<DataT> it(*this);it;it++)
      if(*it == x)
	return true;
    return false;
  }

  template<class DataT> 
  DataT &DListBodyC<DataT>::Nth(int n) {
    DLIterC<DataT> it(*this);
    it.Nth(n);
    RavlAlwaysAssertMsg(it.IsElm(),"DListC::Nth(int), Invalid index.");
    return *it;
  }
  
  template<class DataT> 
  const DataT &DListBodyC<DataT>::Nth(int n) const {
    DLIterC<DataT> it(*this);
    it.Nth(n);
    RavlAlwaysAssertMsg(it.IsElm(),"DListC::Nth(int), Invalid index.");
    return *it;    
  }
  
  
  template<class DataT>
  ostream &operator<<(ostream &strm,const DListBodyC<DataT> &lst) {
    strm << lst.Size() << "\n";
    for(DLIterC<DataT> it(lst);it;it++)
      strm << *it << "\n";
    return strm;
  }
  //: Send to stream.
  
  template<class DataT>
  istream &operator>>(istream &strm,DListBodyC<DataT> &lst) {
    UIntT i;
    lst.Empty();
    strm >> i;
    for(;i > 0;i--) {
      DataT tmp;
      strm >> tmp;
      lst.InsLast(tmp);
    }
    return strm;
  }
  //: Read from stream.

  template<class DataT>
  BinOStreamC &operator<<(BinOStreamC &strm,const DListBodyC<DataT> &lst) {
    strm << lst.Size();
    for(DLIterC<DataT> it(lst);it;it++)
      strm << *it;
    return strm;
  }
  //: Send to a binary stream.
  
  template<class DataT>
  BinIStreamC &operator>>(BinIStreamC &strm,DListBodyC<DataT> &lst) {
    UIntT i;
    lst.Empty();
    strm >> i;
    for(;i > 0;i--) {
      DataT tmp;
      strm >> tmp;
      lst.InsLast(tmp);
    }
    return strm;
  }
  //: Read from a binary stream.

  ///// DListC //////////////////////////////////////////////////////

  template<class DataT>
  bool DListC<DataT>::operator==(const DListC<DataT> &oth) const {
    if(&Body() == &oth.Body()) // Short cut ?
      return true;
    return Body() == oth.Body();
  }
    
  template<class DataT>
  inline ostream &operator<<(ostream &strm,const DListC<DataT> &lst) 
  { return strm << lst.Body(); }
  //: Send to stream.
  
  template<class DataT>
  inline istream &operator>>(istream &strm,DListC<DataT> &lst) {
    DListC<DataT> ret;
    strm >> ret.Body();
    lst = ret;
    return strm;
  }
  //: Read from stream.
    
  template<class DataT>
  inline BinOStreamC &operator<<(BinOStreamC &strm,const DListC<DataT> &lst)
  { return strm << lst.Body(); }
  //: Send to a binary stream.
  
  template<class DataT>
  inline BinIStreamC &operator>>(BinIStreamC &strm,DListC<DataT> &lst) {
    DListC<DataT> ret;
    strm >> ret.Body();
    lst = ret;
    return strm;
  }
  //: Read from a binary stream.
 
}

#endif
