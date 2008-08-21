#ifndef EX_HH
#define EX_HH

#include "Ravl/RefCounter.hh"
#include "Ravl/Stream.hh"

using namespace RavlN;

//! userlevel=Develop
//: Example body class.

class AnObjectBodyC
  : public RCBodyC
{
public:
  AnObjectBodyC(int a)
    : someData(a)
  {}
  //: Constructor.
  
  int Data()
  { return someData; }
  //: Access data.
  
  void SetData(int x)
  { someData = x; }
  //: Set member data.
  
protected:
  int someData;
};
  
    
  
#endif

