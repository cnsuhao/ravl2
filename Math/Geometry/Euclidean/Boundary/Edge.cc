//! date="26.10.1992"
//! author="Radek Marik"
// elementary boundary edge based on crack code

#include <iostream.h>
#include "Ravl/Edge.hh"

namespace RavlN {
  
  EdgeC::EdgeC(const BVertexC & begin, const BVertexC & end)
    : BVertexC(begin)
  {
#if 0
    if (begin.RightN() == end) CrackCodeC::Set(CR_RIGHT);
    if (begin.LeftN() == end) CrackCodeC::Set(CR_LEFT);
    if (begin.UpN() == end) CrackCodeC::Set(CR_UP);
    if (begin.DownN() == end) CrackCodeC::Set(CR_DOWN);
#endif
  }
  
  EdgeC::EdgeC(const Index2dC &pxl, const CrackCodeC & cc)
    : BVertexC(pxl), CrackCodeC(cc)
  {
    switch (cc.Code()) {
      case CR_DOWN :                 break;
      case CR_RIGHT: Down();         break;
      case CR_UP   : Down().Right(); break;
      case CR_LEFT : Right();        break;
      case CR_NODIR:                 break;
      }
  }
  
  Index2dC EdgeC::RPixel(void) const {
    /* return the pixel on the right side of the edge */
    Index2dC px(*this);
    
    switch (crackCode)
      {
      case CR_DOWN : px = CrackStep(px,CR_LEFT);  break;
      case CR_RIGHT:                              break;
      case CR_UP   : px = CrackStep(px,CR_UP);    break;
      case CR_LEFT : px = px.Step(NEIGH_DOWN_LEFT);  break;
      case CR_NODIR:                              break;
      }
    return px; 
  }
  
  Index2dC EdgeC::LPixel(void) const
  {
    /* return the pixel on the left side of the edge */
    Index2dC px(*this);

    switch (crackCode)
      {
      case CR_DOWN :                                    break;
      case CR_RIGHT: px = CrackStep(px,CR_UP);                    break;
      case CR_UP   : CrackStep(px,CR_UP); CrackStep(px,CR_LEFT);  break;
      case CR_LEFT : px = CrackStep(px,CR_LEFT);                  break;
      case CR_NODIR:                                    break;
      }
    return px; 
  }
  
  ostream & operator<<(ostream & s, const EdgeC & edge)
  { return s << Index2dC(edge) << ' ' << ((int) edge.Code()); }

}


  
