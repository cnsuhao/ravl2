// This file is part of RAVL, Recognition And Vision Library 
// Copyright (C) 2001, University of Surrey
// This code may be redistributed under the terms of the GNU Lesser
// General Public License (LGPL). See the lgpl.licence file for details or
// see http://www.gnu.org/copyleft/lesser.html
// file-header-ends-here
#include"Ravl/PatternRec/SampleVector.hh"
#include"Ravl/PatternRec/SampleLabel.hh"
#include"Ravl/PatternRec/DataSet1.hh"
//! rcsid="$Id$"
//! lib=RavlPatternRec


using namespace RavlN;

int main() {

  
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
