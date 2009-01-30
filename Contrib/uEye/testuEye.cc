
#include "Ravl/Image/ImgIOuEye.hh"
#include <iostream>
#include "Ravl/IO.hh"

using RavlN::ByteT;

int main() {
  RavlImageN::ImgIOuEyeC<ByteT> imgStrm(0);
  int i = 0;
  while(1) {
    RavlImageN::ImageC<ByteT> img;
    if(!imgStrm.Get(img)) {
      std::cerr << "Failed to get image. \n";
      break;
    }
    //RavlN::Save(RavlN::StringC("test") + RavlN::StringC(i++) + ".ppm",img);
    RavlN::Save("@X",img);
    //break;
  }
  return 0;
}

