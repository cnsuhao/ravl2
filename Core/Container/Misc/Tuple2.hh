// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDPTUPLE2_HEADER
#define RAVLDPTUPLE2_HEADER 1
/////////////////////////////////////////////////
//! rcsid="$Id$"
//! docentry="Ravl.Core.Tuples"
//! userlevel=Normal
//! file="Ravl/Core/Container/Misc/Tuple2.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! date="09/06/98"

#include "Ravl/Types.hh"

class istream;
class ostream;

namespace RavlN {
  class BinIStreamC;
  class BinOStreamC;
  
  //: Class containing two other arbitrary classes
  
  template<class T1,class T2>
  class Tuple2C {
  public:
    Tuple2C() {}
    //: Default constructor.
    
    Tuple2C(const T1 &nd1,const T2 &nd2) 
      : d1(nd1),
      d2(nd2)
      {}
    //: Constructor.
    
    Tuple2C(const Tuple2C<T1,T2> &oth) 
      : d1(oth.d1),
      d2(oth.d2)
      {}
    //: Copy constructor.
    
    T1 &Data1() { return d1; }
    //: Data access.
    
    const T1 &Data1() const { return d1; }
    //: Data access.
    
    T2 &Data2() { return d2; }
    //: Data access.
    
    const T2 &Data2() const { return d2; }
    //: Data access.

    UIntT Hash() const {
      UIntT h2 = StdHash(d2);
      return (StdHash(d1) + h2) ^ (h2 << 7); 
    }
    //: Get hash value for tuple.
    
    bool operator==(const Tuple2C<T1,T2> &oth) const
      { return (oth.d1 == d1) && (oth.d2 == d2); }
    //: Are tuples equal ?
    
    bool operator!=(const Tuple2C<T1,T2> &oth) const
      { return  (oth.d1 != d1) || (oth.d2 != d2);}
    //: Are tuples unequal ?
    
  protected:
    T1 d1;
    T2 d2;
  };
  
  template<class T1,class T2>
  ostream &operator<<(ostream &out,const Tuple2C<T1,T2> &obj) {
    out << obj.Data1() << ' ' << obj.Data2() << ' ';
    return out;
  }
  
  template<class T1,class T2>
  istream &operator>>(istream &in,Tuple2C<T1,T2> &obj) {
    in >> obj.Data1() >> obj.Data2();
    return in;
  }
    
  // Binary stream operators.
  
  template<class T1,class T2>
  BinOStreamC &operator<<(BinOStreamC &out,const Tuple2C<T1,T2> &obj) {
    out << obj.Data1() << obj.Data2();
    return out;
  }
  
  template<class T1,class T2>
  BinIStreamC &operator>>(BinIStreamC &in,Tuple2C<T1,T2> &obj) {
    in >> obj.Data1() >> obj.Data2();
    return in;
  }
}

#endif
