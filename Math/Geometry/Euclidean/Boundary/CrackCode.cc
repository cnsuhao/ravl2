//! rcsid="$Id$"
//! date="26/10/1992"
//! author="Radek Marik"

#include "Ravl/CrackCode.hh"
#include "Ravl/Assert.hh"

namespace RavlN {

  const CrackCodeT CrackCodeC::clockWiseTurn[5]  = 
    {CR_LEFT, CR_DOWN, CR_RIGHT, CR_UP, CR_NODIR};
  
  const CrackCodeT CrackCodeC::cClockWiseTurn[5] = 
    {CR_RIGHT, CR_UP, CR_LEFT, CR_DOWN, CR_NODIR};
  
  const CrackCodeT CrackCodeC::backTurn[5] = 
    {CR_UP, CR_LEFT, CR_DOWN, CR_RIGHT, CR_NODIR};

  const IndexC CrackCodeC::offsetRow[5] = { 1, 0,-1, 0, 0 };
  const IndexC CrackCodeC::offsetCol[5] = { 0, 1, 0,-1, 0 };
  
  CrackCodeC::CrackCodeC(const IntT i)
  {
    switch (i) {
    case 0: crackCode = CR_DOWN;  break;
    case 1: crackCode = CR_RIGHT; break;
    case 2: crackCode = CR_UP;    break;
    case 3: crackCode = CR_LEFT;  break; 
    case 4: crackCode = CR_NODIR; break;
    default:
      RavlAssertMsg(0,"CrackCodeC(const IntT i), Invalid code. ");
    }
  }

}
