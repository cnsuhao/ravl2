#include"Ravl/PatternRec/SampleVector.hh"
#include"Ravl/PatternRec/SampleLabel.hh"
#include"Ravl/PatternRec/DataSet1.hh"


using namespace RavlN;


int main(){

  
  SampleVectorC input;
  SampleLabelC output;
  
  VectorC v(2);
  v[0] = 0.0; v[1] = 1.0;

  input.Insert(v);
  output.Insert(0);


  cout << input.Pick() << endl;
  cout << output.Pick() << endl;


  DataSet1C<VectorC>dset(input);

  return 0;
}
