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

#include "Ravl/FIndex.hh" 
#include "Ravl/Assert.hh"

//====================================================================
//======= Index3dC ===================================================
//====================================================================

namespace RavlN {
  //: Index of a 3-D array
  // The class Index3dC is a triple of integer values. It is usually used
  // as a three dimensional index of three dimensional arrays. <p>
  // SMALL OBJECT.
  
  class Index3dC 
    : public FIndexC<3>
  {
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
    
    // Special member functions
    // ------------------------
        
  };
  
  //====================================================================
  //======= Index3dC ===================================================
  //====================================================================
  

  inline 
  Index3dC::Index3dC(SizeT dim) 
  { RavlAssert(dim == 3); }
  
  inline
  IndexC
  Index3dC::I() const
  { return (*this)[0]; }
  
  inline
  IndexC
  Index3dC::J() const
  { return (*this)[1]; }
  
  inline
  IndexC
  Index3dC::K() const
  { return (*this)[2]; }
  
  inline
  IndexC &
  Index3dC::I()
  { return (*this)[0]; }

  inline
  IndexC &
  Index3dC::J()
  { return (*this)[1]; }

  inline
  IndexC &
  Index3dC::K()
  { return (*this)[2]; }
  
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
  
}  
#endif
  
