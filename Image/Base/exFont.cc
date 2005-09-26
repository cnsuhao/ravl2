
#include "Ravl/Image/Font.hh"
#include "Ravl/Option.hh"
#include "Ravl/IO.hh"


using namespace RavlImageN;

int main(int nargs,char **argv) {
  OptionC opt(nargs,argv); 
  StringC fontName = opt.String("f","","Font to load ");
  IntT maxWidth = opt.Int("w",600,"Maximum width of the image ");
  opt.Check();
  
  FontC font;
  if(fontName.IsEmpty())
    font = DefaultFont();
  else {
    if(!(font = LoadPSF1(fontName)).IsValid())
      font = LoadPSF2(fontName);
  }
  
  if(!font.IsValid()) {
    cerr << "No font loaded. \n";
    return 1;
  }
  
  IndexRange2dC fsize(1,1);
  Index2dC at(1,1);
  UIntT vsize = 1;
  UIntT hsize = 1;
  for(UIntT i = 0;i < font.Count();i++) {
    vsize = Max(vsize,font[i].Rows());
    hsize += font[i].Cols() + 1; 
  }
  vsize++;
  IntT crows = (hsize / maxWidth) + 1;
  IndexRange2dC imgSize(crows * (vsize+1) + 1,maxWidth);
  
  ImageC<ByteT> img(imgSize);
  img.Fill(0);
  ByteT val = 255;
  hsize = 1;
  IntT hpos = 1;
  for(UIntT i = 0;i < font.Count();i++) {
    IntT row = (hsize / maxWidth);
    if((hpos + (font[i].Cols() + 1))  > maxWidth)
      hpos = 1;
    Index2dC at(row * (vsize+1),hpos);
    StringC let(" ");
    let[0] = i;
    DrawText(font,val,at,let,img);
    hpos += font[i].Cols() + 1;
    hsize += font[i].Cols() + 1;
  }  
  
  Save("@X",img);
  
  return 0;
}
