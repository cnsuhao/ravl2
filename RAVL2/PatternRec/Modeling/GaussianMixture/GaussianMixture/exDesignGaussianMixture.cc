
#include "Ravl/PatternRec/DesignGaussianMixture.hh"
#include "Ravl/PatternRec/Function.hh"

using namespace RavlN;

// This trivial example generates a normally distributed sample, and then fits
// a single Gaussian to it.

int main(int argc, char **argv) 
{
  IntT SampleSize = 1000;
  SampleC<VectorC> Samples(SampleSize);
  
  for (RealT counter=0; counter<SampleSize; ++counter){
    VectorC sample(1);
    sample[0] = RandomGauss();
    Samples.Append(sample);
  }
  
  DesignGaussianMixtureC gmm(1,true);
  GaussianMixtureC func = gmm.Apply(Samples);
  
  MeanCovarianceC mc = func.MeanCovariances()[0];
  cout << "Means:" << mc.Mean() << endl;
  cout << "Covs:" << mc.Covariance() << endl;
}




