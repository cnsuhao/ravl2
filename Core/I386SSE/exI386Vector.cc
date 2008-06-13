
#include "Ravl/Vector.hh"
#include "Ravl/Option.hh"
#include "Ravl/OS/Date.hh"

template<class DataT>
static DataT PlainDotProduct(const DataT* v1, const DataT* v2, size_t Size) {
  DataT sum = 0.0;
  const DataT* ptr1 = v1;
  const DataT* ptr2 = v2;
  for(unsigned int i=Size; i>0; --i)
    sum += *ptr1++ * *ptr2++;
  return sum;  
}

// Small program usefull for checking SSE usage

int main (int nargs,char **argv) {
  RavlN::OptionC opts(nargs,argv);
  bool testFloat = opts.Boolean("f",false,"Test floats");
  int vectorLen = opts.Int("vl",1024,"Vector length. ");
  int loops = opts.Int("l",100000,"Test loops. ");
  bool lengthTest = opts.Boolean("lt","Do length test. ");
  opts.Check();
  
  using namespace RavlN;
  if(testFloat) 
    std::cerr << "Testing float. \n";
  else
    std::cerr << "Testing double. \n";
  
  RealT r = 0;
  int startLen = 1;
  if(!lengthTest)
    startLen = vectorLen;
  for(int vl = startLen;vl <= vectorLen;vl++) {
    RavlN::DateC start = RavlN::DateC::NowUTC();
    if(testFloat) {
      TVectorC<float> a(vl);
      a.Fill(0.96);
      double s = 0;
      for (IntT i=0; i<loops; ++i) 
        s += a.Dot(a);
      r += s;
    } else {
      VectorC a(vl); 
      a.Fill(0.96);
      RealT s = 0;
      for (IntT i=0; i<loops; ++i) 
        s += a.Dot(a);
      r += s;
    }
    RavlN::DateC finish = RavlN::DateC::NowUTC();
    RavlN::DateC startr = RavlN::DateC::NowUTC();
    if(testFloat) {
      TVectorC<float> a(vl);
      a.Fill(0.96);
      float s = 0;
      for (IntT i=0; i<loops; ++i) 
        s += PlainDotProduct(&a[0],&a[0],vl);
      r += s;
    } else {
      TVectorC<double> a(vl);
      a.Fill(0.96);
      double s = 0;
      for (IntT i=0; i<loops; ++i) 
        s += PlainDotProduct(&a[0],&a[0],vl);
      r += s;
    }
    RavlN::DateC finishr = RavlN::DateC::NowUTC();
    
    std::cout << " " << vl << " " << (finish - start).Double() << " " << (finishr - startr).Double() << "\n";
  }
  cout << r << endl;
  
}
