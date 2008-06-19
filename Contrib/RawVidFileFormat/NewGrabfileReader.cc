#include "Ravl/Image/NewGrabfileReader.hh"

#include "Ravl/Image/LegacyGrabfileReader.hh"
#include "Ravl/Image/GrabfileReaderV1.hh"

namespace RavlImageN {

//==========================================================================//

GrabfileReaderC* NewGrabfileReader(const char* const filename, bool legacy)
{
  GrabfileReaderC* p = 0;

  if(legacy) {
    p = new LegacyGrabfileReaderC();
  } else {
    const int version = GrabfileReaderC::FileVersion(filename);
    switch(version) {
    case 1:
      p = new GrabfileReaderV1C();
      break;
    default:
       cout <<"Error unrecognised version number" << endl;
       exit(1);
    }
  }

  return p;
}

//==========================================================================//

}

