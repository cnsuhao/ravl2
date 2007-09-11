#include "Ravl/Image/NewGrabfileWriter.hh"
#include <stdint.h>
#include "Ravl/Image/GrabfileWriterV1.hh"

namespace RavlImageN {

//==========================================================================//

GrabfileWriter* NewGrabfileWriter(const int version)
{
  GrabfileWriter* p = 0;
  switch(version) {
  case 1:
    p = new GrabfileWriterV1();
    break;
  }

  return p;
}

//==========================================================================//

}

