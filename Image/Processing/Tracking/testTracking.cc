
#include "Ravl/Image/MatchNormalisedCorrelation.hh"
#include "Ravl/Image/GaussConvolve.hh"
#include "Ravl/Random.hh"

using namespace RavlImageN;

int testNormalisedCorrelation();

int main(int nargs,char **argv) {
  int ln;
  if((ln = testNormalisedCorrelation()) != 0) {
    cerr << "Test failed on line " << ln << "\n";
    return 1;
  }
  
  cout << "Test passed ok. \n";
  return 0;
}

int testNormalisedCorrelation() {
  cerr << "testNormalisedCorrelation(), Called. \n";
  ImageC<ByteT> img(200,200);
  for(Array2dIterC<ByteT> it(img);it;it++)
    *it = (RandomInt() % 200);
  
  GaussConvolveC<ByteT> filt(11);
  img = filt.Apply(img);
  
  IndexRange2dC targFrame(Index2dC(50,50),8);
  ImageC<ByteT> targ(ImageC<ByteT>(img,targFrame).Copy());
  targ.ShiftIndexes1(50);
  targ.ShiftIndexes2(50);
  //cerr << "Targ=" << targ.Frame() << "\n";
  
  MatchNormalisedCorrelationC match(img);
  
  // Add some noise...
  for(Array2dIterC<ByteT> it(targ);it;it++)
    *it += (IntT) (RandomInt() % 5) - 2;
  
  RealT score;
  Index2dC at;
  match.Search(targ,img.Frame(),score,at);
  cerr << "At=" << at << " Score=" << score << "\n";
  if((at - Index2dC(50,50)).SumOfSqr() > 1)
    return __LINE__;
  
  return 0;
}
