#ifndef RAVLBINLIST_HEADER
#define RAVLBINLIST_HEADER 1
///////////////////////////////////////////////////////////////
//! file="amma/Statist/SparHist/BinList.hh"
//! userlevel=Normal
//! author="Charles Galambos"
//! date="11/2/97"
//! docentry="Ravl.Core.Misc"
//! rcsid="$Id$"
//! lib=SparHist

#include "Ravl/BinTable.hh"
#include "Ravl/BinIter.hh"
#include "Ravl/DList.hh"

namespace RavlN {
  

  template<class IT,class DIT,class BT> class BinListC;
  template<class IT,class DIT,class BT> ostream &operator<<(ostream &s,const BinListC<IT,DIT,BT> &);
  template<class IT,class DIT,class BT> istream &operator>>(istream &s,BinListC<IT,DIT,BT> &);

  //: Binned table of lists.
  // SMALL OBJECT <P>
  // This is simplified the creation of tables with lists in each of the bins.
  
  template<class IT,class DIT,class BT>
  class BinListC {  
  public:
    BinListC(const IT &BinSize ) 
      : table(BinSize) {}
    //: Constructor.
    
    inline void Insert(const IT &Key,const BT &Data)
      { table[Key].InsLast(Data); }
    //: Insert into table.
    
    inline DListC<BT> &ListBin(const IT &Key)
       { return table[Key]; }
    //: List items in same bin as key.
    
    inline void Empty(); 
    //: Empty all bins.
  
    inline DListC<BT> &operator[](const IT &Key) 
      { return table[Key]; }
    //: Array access to lists.
    
    inline DListC<BT> &Bin(const DIT &Key) 
      { return table.Bin(Key); }
    //: Direct access to bin, use result of BinKey(...).
    
    DListC<BT> *GetBin(const IT &Pnt) { return table.GetBin(Pnt); }
    //: See if bins present.
    
    inline BinIterC<IT,DIT,DListC<BT > > Iter() 
      { return BinIterC<IT,DIT,DListC<BT> >(table); }
    //: Create an iterator.
    
    inline DIT BinKey(const IT &Oth) const 
      { return table.Scale(Oth); }
    //: Descritise a point.
    
    inline IT BinSize() const 
      { return table.BinSize(); }
    //: Get size of bins.
    
    inline IT BinCentre(const IT &at) const
      { return table.BinCentre(at); }  
    //: Get centre of bin containing point at.
    
    void SetBinSize(const IT &nBinSize) 
      { table.SetBinSize(nBinSize); }
    //: Set the bin size.
    // NB. The table MUST be empty.
    
  protected:
    BinTableC<IT,DIT,DListC<BT> > table;
    
#if !defined(__sgi__) && !defined(VISUAL_CPP)
    friend ostream &operator<< <>(ostream &s,const BinListC<IT,DIT,BT> &);
    friend istream &operator>> <>(istream &s,BinListC<IT,DIT,BT> &);
#else
    friend ostream &operator<<(ostream &s,const BinListC<IT,DIT,BT> &);
    friend istream &operator>>(istream &s,BinListC<IT,DIT,BT> &);
#endif
  };
  
  ///////////////////////////////////////
  
  template<class IT,class DIT,class BT>
  inline void BinListC<IT,DIT,BT>::Empty() {
    for(BinIterC<IT,DIT,DListC<BT > > It(table);It.IsElm();It.Next()) {
      DListC<BT> Lst = It.Data();
      Lst.Empty();
    }
  }
  
  template<class IT,class DIT,class BT>
  ostream &operator<<(ostream &s,const BinListC<IT,DIT,BT> &tab) {
    s << tab.table;
    return s;
  }
  //: Write bin list to a stream.
  
  template<class IT,class DIT,class BT>
  istream &operator>>(istream &s,BinListC<IT,DIT,BT> &tab) {
    s >> tab.table;
    return s;
  }
  //: Read bin list from a stream.
  
}


#endif
