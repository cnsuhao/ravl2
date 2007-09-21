#include "Ravl/Image/NewGrabfileWriter.hh"
#include <stdint.h>
#include "Ravl/Image/GrabfileWriterV1.hh"

namespace RavlImageN {

//==========================================================================//

GrabfileWriterC* NewGrabfileWriter(const int version)
{
  GrabfileWriterC* p = 0;
  switch(version) {
  case 1:
    p = new GrabfileWriterV1C();
    break;
  }

  return p;
}

//==========================================================================//

}

