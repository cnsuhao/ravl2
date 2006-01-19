#include "HiddenMarkovModel.hh"
#include "Ravl/Option.hh"


using namespace RavlN;
int main()
{
  RealT initTrans[] = {
    0.5, 0.2, 0.3,
    0.4, 0.2, 0.4,
    0.1, 0.6, 0.3
  };
  
  RealT initObs[] = {
    0.6, 0.2, 0.15, 0.05,
    0.25, 0.25, 0.25, 0.25,
    0.05, 0.1, 0.35, 0.5,
  };
  
  HiddenMarkovModelC hmm(MatrixC(3, 3, initTrans), MatrixC(3, 4, initObs));
  cout << "HMM has the transition matrix: " << hmm.Transition() << "\n"
      << "and observation matrix: " << hmm.Observation() << endl;
  
  VectorC istate(1.0/3, 1.0/3, 1.0/3); //Initial state probabilities
  
// Observations specified as vectors:
  VectorC observations[] = {
    VectorC(0,0,1,0),
    VectorC(0,1,0,0),
    VectorC(1,0,0,0), 
    VectorC(0,0,0,1),
    VectorC(0,0,1,0),
    VectorC(1,0,0,0),
    VectorC(1,0,0,0),
    VectorC(1,0,0,0),
    VectorC(1,0,0,0),
    VectorC(0,1,0,0),
    VectorC(0,1,0,0),
    VectorC(0,1,0,0),
  };
  
  UIntT T = sizeof(observations)/sizeof(observations[0]);
  SArray1dC<VectorC> obsvecarray(observations, T, false);
  cout << "Observed sequence (as simple array of vectors): " << obsvecarray;
  RealT prob1 = hmm.ObsSeqProbability( obsvecarray, istate );
  cout << "Probability of observing the sequence is " << prob1 << endl;
  
  SArray1dC<UIntT> path1;
  hmm.Viterbi( obsvecarray, istate, path1);
  cout << "Most likely path through states is " << path1 << endl;
  
  // Same observation as above, but specified as indices between 0 and observationM.size()-1
  
  UIntT obsseq[] = { 2, 1, 0, 3, 2, 0, 0, 0, 0, 1, 1, 1 };
  SArray1dC<UIntT> obsindices(obsseq, T, false); 
  cout << "**************************************************\n";
  cout << "Observed sequence (as simple array of indices): \n" << obsindices;
  RealT prob2 = hmm.ObsSeqProbability( obsindices, istate );
  cout << "Probability of observing the sequence is " << prob2 << endl;
  SArray1dC<UIntT> path2;
  hmm.Viterbi( obsindices, istate, path2);
  cout << "Most likely path through states is \n" << path2 << endl;
}
