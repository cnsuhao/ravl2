// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVLINDEX2D_HH
#define RAVLINDEX2D_HH
//////////////////////////////////////////////////////////////////////////
//! file="Ravl/Core/Base/Index2d.hh"
//! lib=RavlCore
//! userlevel=Basic
//! author="Radek Marik"
//! docentry="Ravl.Core.Indexing"
//! date="20/10/1995"
//! rcsid="$Id$"

#include "Ravl/Index.hh"
#include "Ravl/FIndex.hh"
#include "Ravl/Assert.hh"

namespace RavlN {


  //     5 6 7
  //     4 8 0
  //     3 2 1
  
  enum NeighbourOrderT { NEIGH_RIGHT      = 0,
			 NEIGH_DOWN_RIGHT = 1,
			 NEIGH_DOWN       = 2,
			 NEIGH_DOWN_LEFT  = 3,
			 NEIGH_LEFT       = 4,
			 NEIGH_UP_LEFT    = 5,
			 NEIGH_UP         = 6,
			 NEIGH_UP_RIGHT   = 7,
			 NEIGH_CENTER     = 8};
  
  enum GridMetricT {CITY_BLOCK, MAX_VALUE, SQUARE_EUCLID};
  typedef UIntT GridDistanceT;
  
  //====================================================================
  //======= Index2dC ===================================================
  //====================================================================
  
  class IndexRange2dC;
  class IndexRectangleC;
  class DirectionRLUDC;
  class BinIStreamC;
  class BinOStreamC;
  
  //: 2 Dimensional index
  // The class Index2dC is a pair of IndexC values. It is usually used
  // as a two-dimensional index of two dimensional objects like arrays and
  // images.
  
  class Index2dC 
    : public FIndexC<2>
  {
  public:
    
    // Constructor, assigment, copies, and destructor
    // ----------------------------------------------
    
    inline Index2dC();
    // Creates index <0, 0>.

    inline Index2dC(const FIndexC<2> &oth)
      : FIndexC<2>(oth)
      {}
    // Creates index from its base class.
    
    inline Index2dC(const TFVectorC<IndexC,2> &oth)
      : FIndexC<2>(oth)
      {}
    // Creates index from its base class.
    
    explicit inline Index2dC(SizeT dim)
      { RavlAssert(dim == 2); }
    //: Creates an index
    // This is for compatibilty with N-D indexes, which 
    // need to be told there dimentionality.
    
    inline Index2dC(IndexC row, IndexC column);
    // Creates index <row, column>.
    
    // Object modification
    // -------------------
    
    inline void Set(IndexC r, IndexC c);
    // Sets this index to be <r,c>.
    
    Index2dC & Step(const DirectionRLUDC & dir);
    // Translates the index into direction 'dir'.
    
    inline Index2dC Swapped() const;
    // Returns the 2-dimensional index with swapped value I() and J().

    inline Index2dC & Abs();
    // Changes both indexes to their absolute values.

    // Access to the member items
    // ----------------------------

    inline const IndexC & Row() const
      { return data[0]; }
    // Constant access to the row index

    inline const IndexC & Col() const
      { return data[1]; }
    // Constant access to the column index

    inline IndexC & Row()
      { return data[0]; }
    // Access to the row index

    inline IndexC & Col()
      { return data[1]; }
    // Access to the column index
      
    // Logical conditions
    // ------------------
    
    bool IsInside(const IndexRange2dC & range) const;
    // Returns TRUE, if this index is in the 'range'.
    
    inline bool IsMoreUpperLeft(const Index2dC & i) const;
    // Returns TRUE, if Row() < i.Row() or 
    // (Row() == i.Row() and Col() < i.Col()).

    inline bool operator<(const Index2dC & i) const;
    // A nick name for the member function IsMoreUpperLeft(i).

    // Operations on the neighbourhood
    // -------------------------------

    inline Index2dC & Right();
    // Shifts the index to the right.

    inline Index2dC & Left();
    // Shifts the index to the left.

    inline Index2dC & Up();
    // Shifts the index to the up.

    inline Index2dC & Down();
    // Shifts the index to the down.

    inline Index2dC RightN() const;
    // Returns the index of the right neighbour.

    inline Index2dC LeftN() const;
    // Returns the index of the left neighbour.

    inline Index2dC UpN() const;
    // Returns the index of the upper neighbour.

    inline Index2dC DownN() const;
    // Returns the index of the down neighbour.

    inline Index2dC LowerLeftN() const;
    // Returns the coordinates of the downleft neighbouring pixel 

    inline Index2dC LowerRightN() const;
    // Returns the coordinates of the downright neighbouring pixel 

    inline Index2dC UpperLeftN() const;
    // Returns the coordinates of the upperleft neighbouring pixel 

    inline Index2dC UpperRightN() const;
    // Returns the coordinates of the upperright neighbouring pixel 

    inline Index2dC Neighbour(const DirectionRLUDC & dir) const;
    // Returns the index of the neighbour in the direction 'dir'.

    inline bool IsRelNeighbour8() const;
    // Is '*this' a relative index from 8-neighbourhood?

    inline bool IsNeighbour8(const Index2dC & pxl) const;
    // Is the 'pxl' a neighbouring index of '*this'?

    inline Index2dC Neighbour(const NeighbourOrderT neighOrder) const;
    // Returns the coordinates of the neighbouring index. 

    IndexC NeighbourOrder() const;
    // Returns the order of the relative index.

    IndexC NeighbourOrder(const Index2dC & ind) const;
    // Returns the order of the neighbouring index 'ind'.


    // Distance calculations
    // ---------------------
    
    inline UIntT SumSqr() const;
    // Returns the sum of coordinate squares.
    
    inline UIntT Distance(const Index2dC & i, GridMetricT m) const;
    // Returns the distance of two indexes in the specified metric 'm'.
    
    // Special member functions
    // ------------------------
    
    inline 
      IntT Area2(const Index2dC & second, const Index2dC & third) const;
    // Returns twice the signed area of the triangle determined
    // by this, the second, and the third points. Positive if 'this',
    // 'second', 'third' are oriented counter-clockwise, and negative if
    // clockwise.
    // Ref.: -  O'Rourke,J.: Computatinal geometry in C;
    //          Cambridge University Press, 1994, pp. 19-20
    
  private:

    // Object representation
    // ---------------------

  };
  
  inline
  Index2dC::Index2dC() {
    Row() = 0;
    Col() = 0;
  }
  
  inline
  Index2dC::Index2dC(IndexC row, IndexC column) {
    Row() = row;
    Col() = column;
  }
  
  
  inline
  void
  Index2dC::Set(IndexC r, IndexC c) {
    Row() = r;
    Col() = c;
  }
  
  inline
  Index2dC &
  Index2dC::Right() {
    Col()++;
    return *this;
  }
  
  inline
  Index2dC & 
  Index2dC::Left() {
    Col()--;
    return *this;
  }
  
  inline
  Index2dC &
  Index2dC::Up() {
    Row()--;
    return *this;
  }
  
  inline
  Index2dC &
  Index2dC::Down() {
    Row()++;
    return *this;
  }
  
  inline
  Index2dC
  Index2dC::RightN() const {
    Index2dC id(*this);
    id.Right();
    return id;
  }
  
  inline
  Index2dC
  Index2dC::LeftN() const {
    Index2dC id(*this);
    id.Left();
    return id;
  }
  
  inline
  Index2dC
  Index2dC::UpN() const {
    Index2dC id(*this);
    id.Up();
    return id;
  }
  
  inline
  Index2dC
  Index2dC::DownN() const {
    Index2dC id(*this);
    id.Down();
    return id;
  }
  
  inline 
  Index2dC 
  Index2dC::LowerLeftN() const
  { return Index2dC(*this).Down().Left(); }

  inline 
  Index2dC
  Index2dC::LowerRightN() const
  { return Index2dC(*this).Down().Right(); }

  inline 
  Index2dC 
  Index2dC::UpperLeftN() const
  { return Index2dC(*this).Up().Left(); }

  inline 
  Index2dC 
  Index2dC::UpperRightN() const
  { return Index2dC(*this).Up().Right(); }
  
  inline 
  bool
  Index2dC::IsRelNeighbour8() const {
    return    Row() >= -1 && Row() <= 1
      && Col() >= -1 && Col() <= 1;
  }
  
  inline
  bool
  Index2dC::IsNeighbour8(const Index2dC & ind) const {
    Index2dC relCoo(*this - ind);
    return relCoo.IsRelNeighbour8();
  }
  
  inline
  Index2dC
  Index2dC::Neighbour(const DirectionRLUDC & dir) const {
    Index2dC id(*this);
    id.Step(dir);
    return id;
  }
  
  inline 
  Index2dC
  Index2dC::Neighbour(const NeighbourOrderT neighOrder) const {
    switch(neighOrder)
      {
      case NEIGH_RIGHT:      return Index2dC(Row()  , Col()+1);
      case NEIGH_DOWN_RIGHT: return Index2dC(Row()+1, Col()+1);
      case NEIGH_DOWN:       return Index2dC(Row()+1, Col()  );
      case NEIGH_DOWN_LEFT:  return Index2dC(Row()+1, Col()-1);
      case NEIGH_LEFT:       return Index2dC(Row()  , Col()-1);
      case NEIGH_UP_LEFT:    return Index2dC(Row()-1, Col()-1);
      case NEIGH_UP:         return Index2dC(Row()-1, Col()  );
      case NEIGH_UP_RIGHT:   return Index2dC(Row()-1, Col()+1);
      case NEIGH_CENTER:     return Index2dC(Row()  , Col()  );
      };
    return Index2dC(-1000,-1000);
  }
  
  inline 
  bool Index2dC::IsMoreUpperLeft(const Index2dC & i) const 
  { return (Row() < i.Row()) || (Row() == i.Row() && Col() < i.Col()); }

  inline 
  bool Index2dC::operator<(const Index2dC & i) const  
  { return IsMoreUpperLeft(i); }
  
  inline 
  Index2dC Index2dC::Swapped() const
  { return Index2dC(Col(), Row()); }
  
  inline 
  IntT Index2dC::Area2(const Index2dC & second, const Index2dC & third) const {
    // Area of tringle (*this, second, third) is equal to the area
    // of the tringle which the first point represents the origin
    // of the coordinate system. In fact the points 'aa' and 'bb'
    // represents two vectors and the computed area is equal to
    // the size of the cross product of these two vectors.
    Index2dC aa(second - *this);   // O'Rourke 1.2
    Index2dC bb(third  - *this);
    return (IntT) aa.Row().V()*bb.Col().V() - aa.Col().V()*bb.Row().V();
  }
  
  inline
  UIntT Index2dC::Distance(const Index2dC & i, GridMetricT m) const {
    switch (m) {
    case CITY_BLOCK:    return CityBlockDistance(i).V();
    case MAX_VALUE:     return MaxValueDistance(i).V();
    case SQUARE_EUCLID: return SqrEuclidDistance(i).V();
    default:            return 0;
    }
  }
  
}
#endif
