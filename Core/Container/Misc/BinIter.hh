#ifndef RAVLBINITER_HEADER
#define RAVLBINITER_HEADER 1
///////////////////////////////////////////////////////////////
//! file="amma/Statist/SparHist/BinIter.hh"
//! userlevel=Normal
//! author="Charles Galambos"
//! docentry="Ravl.Core.Misc"
//! date="27/11/1996"
//! rcsid="$Id$"
//! lib=SparHist

#include "Ravl/BinTable.hh"
#include "Ravl/HashIter.hh"
#
namespace RavlN {

  //: Bin table iterator.
  // SMALL OBJECT
  
  template<class IT,class DIT,class BT>
  class BinIterC : public HashIterC<DIT,BT> {
  public:
    BinIterC(const BinTableC<IT,DIT,BT> &Tab)
      : HashIterC<DIT,BT>(Tab.bins) {}
    // Constructor.
    
    BinIterC(const BinIterC<IT,DIT,BT> &anoth)
      : HashIterC<DIT,BT>(anoth) {}
    // Copy Constructor.
    
    BinIterC<IT,DIT,BT> &operator=(const BinIterC<IT,DIT,BT> &oth) {
      HashIterC<DIT,BT>::operator=(oth);
      return *this;
    }
    // Assignment to another iterator.
    
    BinIterC<IT,DIT,BT> &operator=(const BinTableC<IT,DIT,BT> &oth) {
      HashIterC<DIT,BT>::operator=(oth.Bins);
      return *this;
    }
    // Assignment to another table.
    
  };
  
  template<class IT,class DIT,class BT>
  ostream &operator<<(ostream &out,const BinIterC<IT,DIT,BT> &) {
    RavlAssertMsg(0,"operator<<(ostream &out,const BinIterC<IT,DIT,BT> &), NOT IMPLEMENTED ");
    return out;
  }
}

#endif


