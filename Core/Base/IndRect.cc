//! rcsid="$Id$"

#include <iostream.h>
#include "Ravl/IndRect.hh"

namespace RavlN {
  /*-------------------------------------------------------------------*/
  /********* IndexRectangleC *******************************************/
  /*-------------------------------------------------------------------*/
  
  IndexRectangleC &
  IndexRectangleC::Erode(){
    if (originIndex==endIndex) return(*this);
    originIndex.Right().Down();
    if (originIndex==endIndex) return(*this);
    endIndex.Left().Up();
    return(*this);
  }
  
  IndexRectangleC 
  IndexRectangleC::Shrink(IndexC offset) const {
    IndexRectangleC rec(*this);
    rec.originIndex.Row() += offset;
    rec.originIndex.Col() += offset;
    rec.endIndex.Row() -= offset;
    rec.endIndex.Col() -= offset;
    return(rec);
  }
  
  void 
  IndexRectangleC::ErrIfNotSame(const IndexRectangleC & rect,
				char *                  fnc) const {
    if (*this != rect)
      {
#if 0	
	errMaMa << "the image rectangles have not the same size\n"
		<< "1. rect: " << *this << '\n'
		<< "2. rect: " << rect;
	errMaMa.Function(fnc).Exit();
#else
	IssueError(__FILE__,__LINE__,"the image rectangles have not the same size.");
#endif
      }
  }
  
  void 
  IndexRectangleC::ErrIfNotInside(const IndexRectangleC & rect,
                               char *                   fnc) const {
    if (!IsInside(rect))
      {
#if 0	
	errMaMa << "the image rectangle is not inside\n"
		<< "1. rect: " << *this << '\n'
		<< "2. rect: " << rect;
	errMaMa.Function(fnc).Exit();
#else
	IssueError(__FILE__,__LINE__,"the image rectangle is not inside.");
#endif
      }
  }
  
  istream & operator>>(istream & is, IndexRectangleC & rect) {
    is >> rect.Origin() >> rect.End();
    return is;
  }
}

