// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2002, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#ifndef RAVL_CRACKCODE_HEADER
#define RAVL_CRACKCODE_HEADER 1
//////////////////////////////////////////////////////////////////////////
//! file="Ravl/StdType/Entity/CrackCod.hh"
//! lib=RavlMath
//! userlevel=Normal
//! author="Radek Marik"
//! date="26.10.1992"
//! docentry="Ravl.Math.Geometry.2D.Boundry"
//! rcsid="$Id$"

#include "Ravl/Types.hh"
#include "Ravl/Index2d.hh"

namespace RavlN {
  
  //: CrackCode 
  // Symbol names of crack code, ordered counter-clockwise.
  
  enum  CrackCodeT {
    CR_DOWN  = 0,
    CR_RIGHT = 1,
    CR_UP    = 2,
    CR_LEFT  = 3,
    CR_NODIR = 4
  };
  
  //: Relative crackCode 
  // Symbol names of crack code, ordered counter-clockwise.
  
  enum  RelativeCrackCodeT {
    CR_AHEAD     = 0,
    CR_TO_LEFT   = 1,
    CR_BACK      = 2,
    CR_TO_RIGHT  = 3,
    CR_RNODIR    = 4
  };
  
  Index2dC CrackStep(const Index2dC &pixel,CrackCodeT crackCode);
  Index2dC CrackDirection(CrackCodeT crackCode);
  
  // ----------------------------------------------------------------------
  // ******** CrackCodeC **************************************************
  // ----------------------------------------------------------------------
  
  //: Crackcode or Freeman code 
  
  class CrackCodeC {
  public:
    CrackCodeC()
    {}
    //: Default constructor.
    // Direction is undefined.
    
    CrackCodeC(const IntT i);
    //: Constructs object from an integer 'i'.
    
    CrackCodeC(CrackCodeT cc)
      : crackCode(cc)
    {}
    //: Constructs and set value to be 'cc'.
    
    inline CrackCodeT Code() const
    { return crackCode; }
    //: Returns the crack code.
    
    inline bool operator==(const CrackCodeC & cc) const
    { return cc.Code() == Code(); }
    //: Equality test
    
    inline bool operator!=(const CrackCodeC & cc) const
    { return (bool)(cc.Code() != Code()); }
    //: Returns true if the object content is not equal to 'cc'.
    
    inline const CrackCodeC & operator+=(const CrackCodeC & cc);
    // The crackcode 'cc' is taken as a relative crackcode. The relative
    // crackcode is added to this crackcode.

    inline const CrackCodeC & operator-=(const CrackCodeC & cc);
    // The crackcode 'cc' is taken as a relative crackcode. The relative
    // crackcode is subtracted from this crackcode.
    
    const CrackCodeC &operator=(const CrackCodeC & cc) {
      crackCode=cc.crackCode;
      return *this;
    }
    //: Assignment.
    
    const CrackCodeC &operator=(const CrackCodeT & cc) {
      crackCode=cc;
      return *this;
    }
    //: Assignment.
    
    // ----------   turning -----------------------

    inline CrackCodeC & TurnClock()
    { crackCode = clockWiseTurn[crackCode]; return *this; }
    //: Turns the crackcode clockwise.
    // This is an inplace operation.
    
    inline CrackCodeC & TurnCClock()
    { crackCode = cClockWiseTurn[crackCode]; return *this; }
    //: Turns the crackcode counterclockwise.
    // This is an inplace operation.
    
    inline CrackCodeC & TurnBack()
    { crackCode = backTurn[crackCode]; return *this; }
    //: Turns the crackcode backward.
    // This is an inplace operation.
    
    Index2dC Next(const Index2dC &pixel) const {
      return Index2dC(pixel.Row() + offsetRow[crackCode],
		      pixel.Col() + offsetCol[crackCode]);
    }
    //: Get pixel in the direction of the crack code.
    
  protected:
    static const CrackCodeT clockWiseTurn[5];
    static const CrackCodeT cClockWiseTurn[5];
    static const CrackCodeT backTurn[5];
    static const IndexC offsetRow[5];
    static const IndexC offsetCol[5];
    
    CrackCodeT crackCode;  // The code.
    friend Index2dC CrackStep(const Index2dC & ,CrackCodeT );
    friend Index2dC CrackDirection(CrackCodeT );
  };
  
  inline
  Index2dC CrackStep(const Index2dC &pixel,CrackCodeT crackCode) {
    return Index2dC(pixel.Row() + CrackCodeC::offsetRow[crackCode],
		    pixel.Col() + CrackCodeC::offsetCol[crackCode]);
  }
  //: Step one pixel in the direction of the crack code.
  
  inline
  Index2dC CrackDirection(CrackCodeT crackCode) 
  { return Index2dC(CrackCodeC::offsetRow[crackCode],CrackCodeC::offsetCol[crackCode]); }
  //: Direction in the form of an offset for a crack code.
  
  inline 
  const CrackCodeC & CrackCodeC::operator+=(const CrackCodeC & cc) {
    IntT result = crackCode + cc.crackCode;
    crackCode = (CrackCodeT)(result % 4);
    return(*this);
  }
  
  inline 
  const CrackCodeC & CrackCodeC::operator-=(const CrackCodeC & cc) { 
    IntT result = crackCode - cc.crackCode + 4;
    crackCode = (CrackCodeT)(result % 4);
    return(*this);
  }
  
}
#endif
