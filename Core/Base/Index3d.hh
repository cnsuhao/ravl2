// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef Index3d_HH
#define Index3d_HH
///////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Base/Index3d.hh"
//! lib=RavlCore
//! userlevel=Normal
//! author="Radek Marik"
//! docentry="Ravl.Core.Indexing"
//! date="2/8/1994"
//! rcsid="$Id$"

#include "Ravl/Index.hh" 
#include "Ravl/Assert.hh"

//====================================================================
//======= Index3dC ===================================================
//====================================================================

namespace RavlN {
  //: Index of a 3-D array
  // The class Index3dC is a triple of integer values. It is usually used
  // as a three dimensional index of three dimensional arrays. <p>
  // SMALL OBJECT.
  
  class Index3dC {
  public:
    
    // Constructor, assigment, copies, and destructor
    // ----------------------------------------------
    
    explicit Index3dC(SizeT dim);
    //: Creates an index
    // This is for compatibilty with N-D indexes, which 
    // need to be told there dimentionality.
    
    inline Index3dC(IndexC i = 0, IndexC j = 0, IndexC k = 0);
    // Creates index <i,j,k>.
  
    inline Index3dC(RealT ir, RealT jr, RealT kr);
    // Creates index <i,j,k> where i,j,k are cut value of ir, jr, kr 
    // respectivily.
    
    inline Index3dC(const Index3dC & index);
    // Copy constructor.
    
    inline bool operator==(const Index3dC & index) const;
    // Returns TRUE if indexes have the same values.
    
    inline bool operator!=(const Index3dC & index) const;
    // Returns TRUE if indexes have different values.
    
    inline void Set(IndexC i, IndexC j, IndexC k);
    // Sets this index to be <i,j,k>.
    
    inline void Set(const Index3dC & index);
    // Sets this index to be equal to 'index'.
    
    // Access to the member items
    // --------------------------
    
    inline IndexC I() const;
    // Returns the first index.
    
    inline IndexC J() const;
    // Returns the second index.
    
    inline IndexC K() const;
    // Returns the third index.
    
    inline IndexC & I();
    // Access to the first index.
    
    inline IndexC & J();
    // Access to the second index.
    
    inline IndexC & K();
    // Access to the third index.
    
    inline IndexC operator[](IndexC i) const;
    // Returns the i-th index.
    
    inline IndexC & operator[](IndexC i);
    // Access to the i-th index.
    
    
    // Access to the neighbouring 3D indexes
    // -------------------------------------
    
    inline Index3dC & Right();
    // Shifts the index to the right.
    
    inline Index3dC & Left();
    // Shifts the index to the left.
    
    inline Index3dC & Up();
  // Shifts the index to the up.
    
    inline Index3dC & Down();
    // Shifts the index to the down.
    
    inline Index3dC RightN() const;
    // Returns the index of the right neighbour.
    
    inline Index3dC LeftN() const;
    // Returns the index of the left neighbour.
    
    inline Index3dC UpN() const;
    // Returns the index of the upper neighbour.
    
    inline Index3dC DownN() const;
    // Returns the index of the down neighbour.
    
    // Arithmetic operations
    // ---------------------
    
    inline const Index3dC & operator+=(const Index3dC & ind);
    // Adds 'ind' to this index'.
    
    inline const Index3dC & operator-=(const Index3dC & ind);
    // Subtract index 'ind' from this index.
    
    inline const Index3dC & operator*=(const Index3dC & ind);
    // Multiplies this index by index 'ind' item by item.
    
    inline const Index3dC & operator/=(const Index3dC & ind);
    // Divides this index by index 'ind' item by item.
    
    inline Index3dC operator+(const Index3dC & ind) const;
    // Adds this index and 'ind'.
  
    inline Index3dC operator-(const Index3dC & ind) const;
    // Subtract index 'ind' from this index.
    
    inline Index3dC operator*(const Index3dC & ind) const;
    // Returns this index multiplied by index 'ind' item by item.
    
    inline Index3dC operator/(const Index3dC & ind) const;
    // Returns this index divided by index 'ind' item by item.
    
    inline Index3dC operator*(const IntT alpha) const;
    // Multiplies this index by number 'alpha'.
    
    inline Index3dC operator*(const RealT alpha) const;
    // Multiplies this index by real number 'alpha'.
    
    inline Index3dC operator/(const IntT alpha) const;
    // Divides this index by number 'alpha'.
    
    inline Index3dC operator/(const RealT alpha) const;
    // Divides this index by real number 'alpha'.
    
    // Special member functions
    // ------------------------
    
    inline UIntT Hash(void) const;
    // Generates a randomised hash value for this index.
    
    inline SizeT Dim(void) const;
    // Returns a number of dimensions indexed.
    
  private:
    
    // Object representation
    // ---------------------
    
    enum {dim = 3};  // number of indexes     
    IndexC ii[dim];  // the indexes
  };
  
  ostream & operator<<(ostream & outS, const Index3dC & index);
  // Sends the index into the output stream.
  
  istream & operator>>(istream & inS, Index3dC & index);
  // Reads the index values from the input stream.
  
  
  //====================================================================
  //======= Index3dC ===================================================
  //====================================================================
  

  inline 
  Index3dC::Index3dC(SizeT dim) 
  { RavlAssert(dim == 3); }
  
  inline 
  SizeT 
  Index3dC::Dim(void) const
  { return dim; }
  
  inline
  IndexC
  Index3dC::I() const
  { return ii[0]; }
  
  inline
  IndexC
  Index3dC::J() const
  { return ii[1]; }
  
  inline
  IndexC
  Index3dC::K() const
  { return ii[2]; }
  
  inline
  IndexC &
  Index3dC::I()
  { return ii[0]; }

  inline
  IndexC &
  Index3dC::J()
  { return ii[1]; }

  inline
  IndexC &
  Index3dC::K()
  { return ii[2]; }

  inline 
  IndexC 
  Index3dC::operator[](IndexC i) const {
#if RAVL_CHECK
    if (i<0 ||  i >= ((int) dim)) 
      IssueError(__FILE__,__LINE__,"bad index value %d ",i.V());
#endif
    return ii[i.V()];
  }
  
  inline 
  IndexC & 
  Index3dC::operator[](IndexC i) {
#if RAVL_CHECK
    if (i<0 || i >= ((int) dim)) 
      IssueError(__FILE__,__LINE__,"bad index value %d ",i.V());
#endif
    return ii[i.V()];
  }
  
  inline
  void
  Index3dC::Set(IndexC i, IndexC j, IndexC k) {
    I() = i;
    J() = j;
    K() = k;
  }
  
  inline
  Index3dC::Index3dC(IndexC i, IndexC j, IndexC k)
 { Set(i, j, k); }
   
  inline 
  Index3dC::Index3dC(RealT ir,
		     RealT jr,
		     RealT kr) {
    Set(IntT(ir),
	IntT(jr),
	IntT(kr));
  }
  
  inline
  Index3dC::Index3dC(const Index3dC & index)
  { Set(index.I(), index.J(), index.K()); }
  
  inline
  bool
  Index3dC::operator==(const Index3dC & index) const 
  { return (index.I()==I()) && (index.J()==J()) && (index.K()==K()); }
  
  inline
  bool
  Index3dC::operator!=(const Index3dC & index) const
  { return (index.I()!=I()) || (index.J()!=J()) || (index.K()!=K()); }
  
  inline
  void
  Index3dC::Set(const Index3dC & index)
  { *this = index; }
 
  inline
  Index3dC &
  Index3dC::Right() {
    J()++;
    return *this;
  }
  
  inline
  Index3dC & 
  Index3dC::Left() {
    J()--;
    return *this;
  }
  
  inline
  Index3dC &
  Index3dC::Up() {
    I()--;
    return *this;
  }
  
  inline
  Index3dC &
  Index3dC::Down() {
    I()++;
    return *this;
  }
  
  inline
  Index3dC
  Index3dC::RightN() const {
    Index3dC id(*this);
    id.Right();
    return(id);
  }
  
  inline
  Index3dC
  Index3dC::LeftN() const {
    Index3dC id(*this);
    id.Left();
    return id;
  }

  inline
  Index3dC
  Index3dC::UpN() const {
    Index3dC id(*this);
    id.Up();
    return id;
  }
  
  inline
  Index3dC
  Index3dC::DownN() const {
    Index3dC id(*this);
    id.Down();
    return id;
  }
  
  inline 
  const Index3dC &
  Index3dC::operator+=(const Index3dC & ind) {
    I() += ind.I();
    J() += ind.J();
    K() += ind.K();
    return *this;
  }
  
  inline 
  const Index3dC &
  Index3dC::operator-=(const Index3dC & ind) {
    I() -= ind.I();
    J() -= ind.J();
    K() -= ind.K();
    return *this;
  }
  
  inline 
  const Index3dC &
  Index3dC::operator*=(const Index3dC & ind) {
    I() *= ind.I();
    J() *= ind.J();
    K() *= ind.K();
    return *this;
  }
  
  inline 
  const Index3dC &
  Index3dC::operator/=(const Index3dC & ind){
    I() /= ind.I();
    J() /= ind.J();
    K() /= ind.K();
    return *this;
  }
  
  inline 
  Index3dC 
  Index3dC::operator+(const Index3dC & ind) const 
  { return Index3dC(I()+ind.I(), J()+ind.J(), K()+ind.K()); }

  inline 
  Index3dC 
  Index3dC::operator-(const Index3dC & ind) const 
  { return Index3dC(I()-ind.I(), J()-ind.J(), K()-ind.K()); }

  inline 
  Index3dC 
  Index3dC::operator*(const Index3dC & ind) const
  { return Index3dC(I()*ind.I(), J()*ind.J(), K()*ind.K()); }

  inline 
  Index3dC 
  Index3dC::operator/(const Index3dC & ind) const
  { return Index3dC(I()/ind.I(), J()/ind.J(), K()/ind.K()); }

  inline 
  Index3dC 
  Index3dC::operator*(const IntT alpha) const
  { return Index3dC(I()*alpha, J()*alpha, K()*alpha); }

  inline 
  Index3dC 
  Index3dC::operator*(const RealT alpha) const {
    return Index3dC((IndexC)(I()*alpha),
		    (IndexC)(J()*alpha),
		    (IndexC)(K()*alpha));
  }
  
  inline 
  Index3dC 
  Index3dC::operator/(const IntT alpha) const
  { return Index3dC(I()/alpha, J()/alpha, K()/alpha); }

  inline 
  Index3dC 
  Index3dC::operator/(const RealT alpha) const
  { return Index3dC(I()/alpha, J()/alpha, K()/alpha); }

  inline 
  UIntT
  Index3dC::Hash(void) const  { 
    UIntT HVal = ii[0].V();
    // The compiler should unroll this.
    for(IndexC i = 1;i < 3;i++) { 
      HVal += ((UIntT) ii[i.V()].V());
      HVal ^= ii[i.V()].V() << (i.V() * (sizeof(IndexC) * 2));
    }
    return HVal;
  }

}  
#endif
  
