#include "Ravl/Image/NewGrabfileReader.hh"

#include "Ravl/Image/LegacyGrabfileReader.hh"
#include "Ravl/Image/GrabfileReaderV1.hh"

namespace RavlImageN {

//==========================================================================//

GrabfileReader* NewGrabfileReader(const char* const filename, bool legacy)
{
  GrabfileReader* p = 0;

  if(legacy) {
    p = new LegacyGrabfileReader();
  } else {
    const int version = GrabfileReader::FileVersion(filename);
    switch(version) {
    case 1:
      p = new GrabfileReaderV1();
      break;
    }
  }

  return p;
}

//==========================================================================//

}

