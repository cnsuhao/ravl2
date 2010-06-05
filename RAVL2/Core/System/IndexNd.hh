// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_INDEXND_HEADER
#define RAVL_INDEXND_HEADER 1
////////////////////////////////////////////////////////////////////////
//! userlevel=Normal
//! date="1/10/1996"
//! author="Charles Galambos"
//! docentry="Ravl.API.Core.Indexing"
//! rcsid="$Id: IndexNd.hh 7546 2010-02-18 13:28:49Z craftit $"
//! lib=RavlCore
//! file="Ravl/Core/System/IndexNd.hh"

#include "Ravl/Index.hh"
#include "Ravl/SArray1d.hh"

namespace RavlN {

  //! userlevel=Normal
  //: N-dimensional index
  
  class IndexNdC 
    : public SArray1dC<IndexC>
  {
  public:
    IndexNdC()
    {}
    //: Empty index.
  
    IndexNdC(SizeT dim) 
      : SArray1dC<IndexC>(dim) 
    {}
    //: A uninitialized array with the range <0, 'dim'-1>.
  
    IndexNdC(IndexC * data, SizeT dim) 
      : SArray1dC<IndexC>(data, dim) 
    {}
    //: An array is created from the memory location 'data' with the range of access in <0, 'dim'-1>.
    // 'data' is not deallocated during destruction of the array.
    
    IndexNdC(const IndexNdC & nd) 
      : SArray1dC<IndexC>(nd) 
    {}
    //: Another access to the index 'ND'.
    
    inline bool operator!=(const IndexNdC & index) const
    { return !operator==(index); }
    //: Returns true if indexes have different values.
    
    //:---------------------------------
    // Arithmetic operation on N-D index
  
    inline IndexNdC operator*(const RealT alpha) const;
    //: Multiplies this index by real number 'alpha'.
    
    inline IndexNdC operator/(const RealT alpha) const;
    //: Divides this index by real number 'alpha'.
    
    SizeT Hash() const;
    //: Return an almost unqiue hash value for this index.
    
  };
  
  inline 
  IndexNdC IndexNdC::operator*(const RealT alpha) const {
    IndexNdC ret(Size());
    for(BufferAccessIter2C<IndexC,IndexC> it(ret,*this);it;it++)
      it.Data1() = (IntT) ((RealT) it.Data2() * alpha);
    return ret;
  }
  
  inline 
  IndexNdC IndexNdC::operator/(const RealT alpha) const {
    IndexNdC ret(Size());
    for(BufferAccessIter2C<IndexC,IndexC> it(ret,*this);it;it++)
      it.Data1() = (IntT) ((RealT) it.Data2() / alpha);
    return ret;
  }

}


#endif
