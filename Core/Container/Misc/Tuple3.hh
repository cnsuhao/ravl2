// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLDPTUPLE3_HEADER
#define RAVLDPTUPLE3_HEADER 1
/////////////////////////////////////////////////
//! userlevel=Normal
//! rcsid="$Id$"
//! file="Ravl/Core/Container/Misc/Tuple3.hh"
//! lib=RavlCore
//! author="Charles Galambos"
//! docentry="Ravl.Core.Tuples"
//! date="09/06/98"

#include "Ravl/Types.hh"

class istream;
class ostream;

namespace RavlN {
  class BinIStreamC;
  class BinOStreamC;
  
  //: Class containing 3 other classes.
  
  template<class T1,class T2,class T3>
  class Tuple3C {
  public:
    Tuple3C() {}
    //: Default constructor.
    
    Tuple3C(istream &in) 
      { in >> d1 >> d2 >> d3; }
    //: Stream constructor.
    
    Tuple3C(BinIStreamC &in) 
      { in >> d1 >> d2 >> d3; }
    //: Binary Stream constructor.
    
    Tuple3C(const T1 &nd1,const T2 &nd2,const T3 &nd3) 
      : d1(nd1),
      d2(nd2),
      d3(nd3)
      {}
    //: Constructor.
    
    Tuple3C(const Tuple3C<T1,T2,T3> &oth) 
      : d1(oth.d1),
      d2(oth.d2),
      d3(oth.d3)
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
    
    T3 &Data3() { return d3; }
    //: Data access.
    
    const T3 &Data3() const { return d3; }
    //: Data access.

    UIntT Hash() const { 
      UIntT h2 = d2.Hash();
      UIntT h3 = d3.Hash();
      return (d1.Hash() + h2 + h3) ^ (h2 << 7)  ^ (h3 << 11);
    }
    //: Get hash value for tuple.
    
    bool operator==(const Tuple3C<T1,T2,T3> &oth) const
      { return (oth.d1 == d1) && (oth.d2 == d2) && (oth.d3 == d3); }
    //: Are tuples equal ?
    
    bool operator!=(const Tuple3C<T1,T2,T3> &oth) const
      { return  (oth.d1 != d1) || (oth.d2 != d2) || (oth.d3 != d3);}
    //: Are tuples unequal ?
    
  protected:
    T1 d1;
    T2 d2;
    T3 d3;
  };
  
  template<class T1,class T2,class T3>
  ostream &operator<<(ostream &out,const Tuple3C<T1,T2,T3> &obj) {
    out << obj.Data1() << ' ' << obj.Data2() << ' ' << obj.Data3() << ' ';
    return out;
  }
  
  template<class T1,class T2,class T3>
  istream &operator>>(istream &in,Tuple3C<T1,T2,T3> &obj) {
    obj = Tuple3C<T1,T2,T3>(in);
    return in;
  }
  
  // Binary stream operators.
  
  class BinIStreamC;
  class BinOStreamC;
  
  template<class T1,class T2,class T3>
  BinOStreamC &operator<<(BinOStreamC &out,const Tuple3C<T1,T2,T3> &obj) {
    out << obj.Data1() << obj.Data2() << obj.Data3();
    return out;
  }
  
  template<class T1,class T2,class T3>
  BinIStreamC &operator>>(BinIStreamC &in,Tuple3C<T1,T2,T3> &obj) {
    obj = Tuple3C<T1,T2,T3>(in);
    return in;
  }
}

#endif
