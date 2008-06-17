
#include "Ravl/VectorUtils.hh"
#include "Ravl/Stream.hh"
#include "Ravl/SArray1d.hh"

template<class DataT> int TestDot();
template<class DataT> int TestQuad();

int main() {
  int ln;
  if((ln = TestDot<float>()) != 0) {
    std::cerr << "Test failed on line " << ln << "\n";
    return ln;
    }
  if((ln = TestDot<double>()) != 0) {
    std::cerr << "Test failed on line " << ln << "\n";
    return ln;
  }
  if((ln = TestQuad<double>()) != 0) {
    std::cerr << "Test failed on line " << ln << "\n";
    return ln;
  }
  std::cout << "Test passed ok. \n";
  return 0;
}

template<class DataT>
int TestDot() {
  RavlN::SArray1dC<DataT> data(32);
  for(int i = 0;i < 32;i++)
    data[i] = i;
  
  for(int l = 0;l <= 16;l++) {
    for(int i = 0;i < 16;i++) {
      for(int j = 0;j < 16;j++) {
        // Compute true answer
        DataT trueProduct = 0;
        for(int k = 0;k < l;k++)
          trueProduct += data[k+i] * data[k+j];
        // Compute dot product.
        DataT dp = RavlBaseVectorN::DotProduct(&data[i],&data[j],l);
        DataT diff = trueProduct - dp;
        if(RavlN::Abs(diff) > 1e-12) {
          std::cerr << "Failed l=" << l << " i=" << i << " j=" << j << " True=" << trueProduct << " Sum=" << dp << "\n";
          return __LINE__;
        }
      }
    }
  }
  return 0;
  
}

template<class DataT>
int TestQuad() {
  RavlN::SArray1dC<DataT> data(32);
  for(int i = 0;i < 32;i++)
    data[i] = i;
  
  for(int l = 0;l <= 16;l++) {
    for(int i = 0;i < 16;i++) {
      for(int j = 0;j < 16;j++) {
        for(int j2 = 0;j2 < 16;j2++) {
          // Compute true answer
          DataT trueDotAndResult = 0;
          for(int k = 0;k < l;k++)
            trueDotAndResult += data[k+i] * (data[k+j] + data[k+j2]*data[k+i]);
          // Compute dot and add.
          DataT qp = RavlBaseVectorN::QuadProduct(&data[i],&data[j],&data[j2],l);
          DataT diff = trueDotAndResult - qp;
          if(RavlN::Abs(diff) > 1e-12) {
            std::cerr << "Failed l=" << l << " i=" << i << " j=" << j << " j2=" << j2 << " True=" << trueDotAndResult << " Sum=" << qp << " Diff= " << diff << "\n";
            return __LINE__;
          }
        }
      }
    }
  }
  return 0;
  
}
