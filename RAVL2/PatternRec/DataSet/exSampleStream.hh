//! author="Charles Galambos"

#include "Ravl/PatternRec/SampleStreamVector.hh"
#include "Ravl/RandomMersenneTwister.hh"

using namespace RavlN;

class RandomVectorStreamBodyC
  : public DPISPortBodyC<VectorC>
{
public:
  RandomVectorStreamBodyC(UIntT vectorSize,UIntT numSamples) 
    : n(vectorSize),
      size(numSamples),
      offset(0)
  {
    twister.Seed(1);
  }
  //: Default constructor.
  
  bool Seek(UIntT off) {
    // Can only seek to offset 0 in stream.
    if(off != 0)
      return false; 
    twister.Seed(1); // Re-seed random number generator.
    offset = 0;
    return true;
  }
  //: Seek to element.
  
  virtual bool Get(VectorC &ret) {
    if(offset >= size)
      return false;
    offset++;
    ret = VectorC(n);
    for(int i = 0;i < n;i++)
      ret[i] = twister.Double();
    return true;
  }
  //: Get next piece of data.
  
protected:
  UIntT n;
  UIntT size;
  UIntT offset;
  RandomMersenneTwisterC twister;
};


class RandomVectorStreamC
  : public SampleStreamC
{
public:
  RandomVectorStreamC(UIntT vectorSize,UIntT numSamples)
    : DPEntityC(*new RandomVectorStreamBodyC(vectorSize,numSamples))
  {}
  //: Constructor.
  // n is size of vector to return.
};


int main(int nargs,char **argv) {
  RandomVectorStreamC randomVectorStream(5,10000);
  MeanCovarianceC meanCov = randomVectorStream.MeanCovariance();
  cerr << "Mean and Coverance of random stream =" << meanCov << "\n";
  return 0;
}
